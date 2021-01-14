/*
 * Copyright Samsung Electronics Co., LTD.
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

/*
 * rildatabuilder.h
 *
 *  Created on: 2014. 6. 21.
 *      Author: sungwoo48.choi
 */

#ifndef __RIL_DATA_BUILDER_H__
#define __RIL_DATA_BUILDER_H__

#include "rildata.h"

class RilDataBuilder {
private:

public:
    RilDataBuilder() {}
    virtual ~RilDataBuilder();

protected:
    virtual void Clear() {}

};

#endif /* __RIL_DATA_BUILDER_H__ */
