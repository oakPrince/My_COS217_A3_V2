#include <assert.h>
#include <stdlib.h>
#include "symtable.h"

enum { BUCKET_COUNT = 65521 };

struct Binding
{
  const char *key;
  void *value;
  struct Binding *next;
}

struct Table
{
  struct Binding *buckets{BUCKET_COUNT);
}
