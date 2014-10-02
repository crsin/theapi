#include "taVector.h"

#include <stdlib.h>

typedef struct {
  taHandle* handles;
  uint32_t length;
  uint32_t size;
} vector_t;

taHandle taVectorMake(uint32_t nslots)  {
  vector_t* v = malloc(sizeof(vector_t));
  if (v == NULL) return NULL;

  v->handles = malloc(sizeof(taHandle) * nslots);
  if (v->handles == NULL) {
    free(v);
    return NULL;
  }

  v->size = nslots;
  v->length = 0;
  return (taHandle)v;
}

void taVectorDestroy(taHandle self) {
  vector_t* v = self;
  if (v->handles != NULL)
    free(v->handles);
  free(v);
}

uint32_t taVectorSize(taHandle self) {
  vector_t* v = self;
  return v->size;
}

uint32_t taVectorLength(taHandle self) {
  vector_t* v = self;
  return v->length;
}

void taVectorAllocate(taHandle self, uint32_t nslots) {
  vector_t* v = self;
  v->size += nslots;
  v->handles = realloc(v->handles, v->size);
}

void potentialResize(vector_t* v, int32_t dslots) {
  uint32_t oldsize = v->size;
  while (v->size < v->length + dslots) {
    // have to resize
    v->size *= 2;
  }

  if (oldsize != v->size) {
    v->handles = realloc(v->handles, v->size);
  }
  // TODO: make resizing more stable
}

// make sure there's enough space before using this with potentialResize
void moveHandles(vector_t* v, uint32_t start, int32_t dslots) {
  uint32_t i;
  if (dslots > 0) {
    for (i = v->length; i >= start; i -= 1) {
      v->handles[i+dslots] = v->handles[i];
    }
  }
  else if (dslots < 0) {
    for (i = start; i < v->length; i += 1) {
      v->handles[i] = v->handles[i-dslots];
    }
  }
}

void taVectorPush(taHandle self, taHandle item) {
  vector_t* v = self;
  potentialResize(v, 1);

  v->handles[v->length] = item;
  ++v->length;
}

void taVectorUnshift(taHandle self, taHandle item) {
  vector_t* v = self;
  potentialResize(v, 1);
  moveHandles(v, 0, 1);

  v->handles[0] = item;
  ++v->length;
}

taHandle taVectorPop(taHandle self) {
  vector_t* v = self;
  potentialResize(v, -1);

  return v->handles[--v->length];
}

taHandle taVectorShift(taHandle self) {
  vector_t* v = self;
  potentialResize(v, -1);
  taHandle val = v->handles[0];

  moveHandles(v, 1, -1);
  --v->length;
  return val;
}

taHandle taVectorGet(taHandle self, uint32_t i) {
  vector_t* v = self;
  if (i > v->size) return NULL; // TODO: THIS IS AN ERROR

  return v->handles[i];
}

void taVectorSet(taHandle self, uint32_t i, taHandle value) {
  vector_t* v = self;
  if (i > v->size) return; // TODO: THIS IS AN ERROR

  v->handles[i] = value;
}

