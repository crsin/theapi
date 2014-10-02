#ifndef __ta_NODE_H__
#define __ta_NODE_H__

#include <stdint.h>

#include "taHandle.h"

taHandle taNodeMakeRoot(taHandle data);
void     taNodeDestroyRoot(taHandle self);

taHandle taNodeGetParent(taHandle self);
taHandle taNodeGetData(taHandle self);

uint32_t taNodeNumChildren(taHandle self);
taHandle taNodeSeekChild(taHandle self, uint32_t i);
taHandle taNodePrevChild(taHandle self);
taHandle taNodeNextChild(taHandle self);
void     taNodeAddChild(taHandle self, taHandle data);

#endif
