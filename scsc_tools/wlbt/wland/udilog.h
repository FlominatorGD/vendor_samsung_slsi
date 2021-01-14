#ifndef SLSI_UDILOG_H
#define SLSI_UDILOG_H

#include <stdio.h>
#include <functional>
#include "SingleShotTimer.h"

class UdiLog
{
private:
    static volatile bool                                   running;
    static int                                             pid;
    static FILE*                                           readfd;
    static FILE*                                           writefd;
    static int                                             logfilesize;
    static unsigned int                                    logid;
    static char                                            prefix[256];
    static std::function<void()>                           removefilter;
    static dujeonglee::basiclibrary::SingleShotTimer<2, 1> worker;
    static void clear_resource();
public:
    static int start(std::function<void()> addfilter, std::function<void()> rmfilter, const char* prefixstr, std::function<void(char*)> callback = NULL);
    static void stop();
};

#endif
