#include "taNode.h"

#include <stdlib.h>

#include "taVector.h"

typedef struct {
  taHandle parent;
  taHandle children;
  taHandle data;
  uint32_t ichild;
} node_t;

taHandle taNodeMakeRoot(taHandle data) {
  node_t* n = malloc(sizeof(node_t));
  n->parent = NULL;
  n->children = taVectorMake(4);
  n->ichild = 0;
  n->data = data;
  return (taHandle)n;
}

void taNodeDestroyRoot(taHandle self) {
  node_t* n = self;
  taVectorDestroy(n->children);
  free(n);
}

taHandle taNodeGetParent(taHandle self) {
  node_t* n = self;
  return n->parent;
}

uint32_t taNodeNumChildren(taHandle self) {
  node_t* n = self;
  return taVectorSize(n->children);
}

#define CHECKICHILD() \
  if (n->ichild == 0 || n->ichild + 1 > taVectorLength(n->children)) return NULL

taHandle taNodeSeekChild(taHandle self, uint32_t i) {
  node_t* n = self;
  CHECKICHILD();
  return taVectorGet(n->children, n->ichild = i);
}

taHandle taNodePrevChild(taHandle self) {
  node_t* n = self;
  CHECKICHILD();
  return taVectorGet(n->children, --n->ichild);
}

taHandle taNodeNextChild(taHandle self) {
  node_t* n = self;
  CHECKICHILD();
  return taVectorGet(n->children, ++n->ichild);
}

#undef CHECKICHILD

void taNodeAddChild(taHandle self, taHandle child) {
  node_t* n = self;
  node_t* c = child;

  taVectorPush(n->children, child);

  c->parent = self;
}

void taNodeSetData(taHandle self, taHandle data) {
  node_t* n = self;

  n->data = data;
}

taHandle taNodeGetData(taHandle self) {
  node_t* n = self;

  return n->data;
}
