/* This code implements a symbol table using a hash table. */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symtable.h"

/* Starting value for the bucket count. */
int initialBucketCount = 509;

/* Each key-value binding pair is stored in a Binding structure.
 Bindings  are linked with pointers to form a linked list. */
struct Binding
{
  /* Keys stored in constant char pointer. */
  const char *key;
  /* Values stored in void pointer. */
  void *value;
  /* Structure points to next binding in hash table. */
  struct Binding *next;
}

/* Begins hash table */
struct Table
{
  /* Number of bindings is the length  */
  size_t length;
  /* struct Binding begins hash table */
  struct Binding *buckets[initialBucketCount];
}

/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
   inclusive. */
static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
   const size_t HASH_MULTIPLIER = 65599;
   size_t u;
   size_t uHash = 0;

   assert(pcKey != NULL);

   for (u = 0; pcKey[u] != '\0'; u++)
      uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];

   return uHash % uBucketCount;
}

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
  if (oSymTable == NULL)
  {
    return NULL;
  }
  oSymTable->length = 0;
  oSymTable->first
}
