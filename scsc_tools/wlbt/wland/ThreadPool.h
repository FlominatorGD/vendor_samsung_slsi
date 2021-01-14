#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <cstdlib>            // std::exit
#include <atomic>             // std::atomic
#include <condition_variable> // std::condition_variable
#include <functional>         // std::function
#include <iostream>           // std::cout
#include <mutex>              // std::mutex, std::unique_lock
#include <thread>             // std::thread
#include <deque>              // std::queue
#include <vector>             // std::vector
#include <set>                // std::set

namespace dujeonglee
{
namespace basiclibrary
{
template <const uint32_t INITIAL_PRIORITY, const uint32_t INITIAL_THREAD>
class ThreadPool
{
  private:
    enum POOL_STATE : uint8_t
    {
        STARTED,
        STOPPED
    };
    // State of ThreadPool. 'm_State' must be updated by Start and Stop function.
    POOL_STATE m_State;

    // Synchronization of access on 'm_TaskQueue'.
    std::mutex m_TaskQueueLock;
    // Condition variable to wake up threads. The signal is generated by 'Enqueue' and 'FireWorker' functions.
    std::condition_variable m_Condition;
    // Task queue
    std::vector<std::deque<std::function<void()>>> m_TaskQueue;

    // Priority levels
    uint32_t m_Priorities;

    // Number of threads
    uint32_t m_Workers;
    // Actual number of threads. 'HireWorker' increments 'm_ActualWorkers' by one, and 'FireWorker' decrements 'm_ActualWorkers' by one.
    std::atomic<uint32_t> m_ActualWorkers;
    // Worker Set
    std::set<std::thread::id> m_WorkerIDs;

    // API synchronization among applications.
    std::mutex m_APILock;

  private:
    // Check if a worker has tasks to serve or has to wait.
    bool ShouldWakeup()
    {
        for (uint32_t i = 0; i < m_TaskQueue.size(); i++)
        {
            if (m_TaskQueue[i].size() > 0)
            {
                return true;
            }
        }
        return false;
    }

    // Hire one thread.
    void HireWorker()
    {
        ThreadPool *const self = this;
        try
        {
            std::thread([self]() {
                {
                    std::unique_lock<std::mutex> TaskQueueLock(self->m_TaskQueueLock);
                    self->m_WorkerIDs.insert(std::this_thread::get_id());
                }
                self->m_ActualWorkers++;
                for (;;)
                {
                    std::function<void()> task = nullptr;
                    {
                        std::unique_lock<std::mutex> TaskQueueLock(self->m_TaskQueueLock);
                        while (!self->ShouldWakeup())
                        {
                            self->m_Condition.wait(TaskQueueLock);
                        }
                        for (uint32_t priority = 0; priority < self->m_TaskQueue.size(); priority++)
                        {
                            if (self->m_TaskQueue[priority].size() > 0)
                            {
                                task = std::move(self->m_TaskQueue[priority].front());
                                self->m_TaskQueue[priority].pop_front();
                                break;
                            }
                        }
                    }
                    if (task)
                    {
                        task();
                        std::this_thread::sleep_for(std::chrono::milliseconds(0));
                    }
                    else
                    {
                        // "null task" is used as a fire worker signal.
                        // Any threads getting "null task" will exit the loop.
                        break;
                    }
                }
                self->m_ActualWorkers--;
                {
                    std::unique_lock<std::mutex> TaskQueueLock(self->m_TaskQueueLock);
                    self->m_WorkerIDs.erase(std::this_thread::get_id());
                }
            })
                .detach();
        }
        catch (const std::system_error &ex)
        {
            std::cout << ex.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    // Fire one thread
    void FireWorker()
    {
        std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
        do
        {
            try
            {
                m_TaskQueue[0].push_front(nullptr);
                m_Condition.notify_one();
                return;
            }
            catch (const std::bad_alloc &ex)
            {
                std::cout << ex.what() << std::endl;
            }
        } while (1);
    }

  public:
    // Ctor. Initialize member variables and call 'Start'.
    ThreadPool() : m_State(STOPPED),
                   m_Priorities(INITIAL_PRIORITY > 1 ? INITIAL_PRIORITY : 1),
                   m_Workers((INITIAL_THREAD > 1 ? INITIAL_THREAD : 1))
    {
        m_ActualWorkers = 0;
        Start();
    }

    // Dtor. Call 'Stop'
    ~ThreadPool()
    {
        Stop();
    }

    // Create 'm_Workers' of worker threads and 'm_Priorities' of task queues.
    void Start()
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        if (m_State == POOL_STATE::STARTED)
        {
            return;
        }
        // 1. Create TaskQueue
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            do
            {
                try
                {
                    m_TaskQueue.resize(m_Priorities);
                }
                catch (const std::bad_alloc &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
            } while (m_TaskQueue.size() != m_Priorities);
        }

        // 2. Create workers
        for (unsigned int i = 0; i < m_Workers; i++)
        {
            HireWorker();
        }
        while (m_ActualWorkers != m_Workers)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        };
        m_State = POOL_STATE::STARTED;
    }

    // Send kill signal (= nullptr) to worker threads and purge all task queues.
    void Stop()
    {
        bool locked = false;
        while ((locked = m_APILock.try_lock()) == false && m_State == STARTED)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (locked == false)
        {
            return;
        }
        const bool WORKER_CALLED_STOP = (m_WorkerIDs.find(std::this_thread::get_id()) != m_WorkerIDs.end());
        if (m_State == STOPPED)
        {
            m_APILock.unlock();
            return;
        }
        m_State = STOPPED;
        for (uint32_t i = 0; i < m_Workers; i++)
        {
            FireWorker();
        }
        while (m_ActualWorkers > (WORKER_CALLED_STOP ? 1 : 0))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            m_TaskQueue.clear();
        }
        m_APILock.unlock();
    }

    // Change priority levels of task queues.
    uint32_t SetPriorities(const uint32_t size)
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        if (m_State == STOPPED)
        {
            m_Priorities = size;
            return m_Priorities;
        }
        if (size == 0 || size == m_Priorities)
        {
            return m_Priorities;
        }
        else
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            try
            {
                m_TaskQueue.resize(size);
                m_Priorities = size;
            }
            catch (const std::bad_alloc &ex)
            {
                std::cout << ex.what() << std::endl;
            }
            return m_Priorities;
        }
    }

    // Change the number of worker threads.
    uint32_t SetWorkers(const uint32_t size)
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        if (m_State == STOPPED)
        {
            m_Workers = size;
            return m_Workers;
        }
        if (size == 0 || size == m_Workers)
        {
            return m_Workers;
        }
        if (size > m_Workers)
        {
            const uint32_t hire = size - m_Workers;
            for (uint32_t i = 0; i < hire; i++)
            {
                HireWorker();
            }
            m_Workers += hire;
        }
        else
        {
            const uint32_t fire = m_Workers - size;
            for (uint32_t i = 0; i < fire; i++)
            {
                FireWorker();
            }
            m_Workers -= fire;
        }
        while (m_ActualWorkers != m_Workers)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        };
        return m_Workers;
    }

    // Enqueue the task.
    // Task queue with '0' priority will be served first, then task queue with '1' priority will be served.
    bool Enqueue(const std::function<void()> task, const uint32_t priority = 0)
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        if (m_State == STOPPED)
        {
            return false;
        }
        if (task == nullptr)
        {
            return false;
        }
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            if (priority >= m_TaskQueue.size())
            {
                return false;
            }
            try
            {
                m_TaskQueue[priority].push_back(task);
                m_Condition.notify_one();
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
                return false;
            }
        }
        return true;
    }

    // Return the number of pending tasks.
    uint32_t Tasks()
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        uint32_t ret = 0;
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            for (uint32_t i = 0; i < m_TaskQueue.size(); i++)
            {
                ret += m_TaskQueue[i].size();
            }
        }
        return ret;
    }

    // Return the number of pending tasks for a specified priority queue.
    uint32_t Tasks(const uint32_t priority)
    {
        std::unique_lock<std::mutex> ApiLock(m_APILock);
        {
            std::unique_lock<std::mutex> TaskQueueLock(m_TaskQueueLock);
            if (priority >= m_TaskQueue.size())
            {
                return 0;
            }
            return m_TaskQueue[priority].size();
        }
    }
};
}
}

#endif