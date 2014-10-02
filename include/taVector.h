#ifndef __ta_VECTOR_H__
#define __ta_VECTOR_H__

#include <stdint.h>

#include "taHandle.h"

taHandle taVectorMake(uint32_t nslots);
void taVectorDestroy(taHandle self);

uint32_t taVectorSize(taHandle self);
uint32_t taVectorLength(taHandle self);
void taVectorAllocate(taHandle self, uint32_t nslots);

void taVectorPush(taHandle self, taHandle item);
void taVectorUnshift(taHandle self, taHandle item);

taHandle taVectorPop(taHandle self);
taHandle taVectorShift(taHandle self);

taHandle taVectorGet(taHandle self, uint32_t i);
void taVectorSet(taHandle self, uint32_t i, taHandle value);

#endif
