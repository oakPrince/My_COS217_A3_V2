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
  struct Binding **buckets;
  /* Number of buckets in the Symtable  */
  size_t uBucketCount = initialBucketCount;
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

  /* set each bucket to null */
  for (int i = 0; i < uBucketCount; i++)
  {
    oSymTable->buckets[i] = NULL;
  }
  oSymTable->length = 0;
  
  return oSymTable;
}

SymTable_T SymTable_free(SymTable_T oSymTable)
{
  struct Binding *current;
  struct Binding *forward;

  assert(oSymTable != NULL);
  
  for (int i = 0; i < uBucketCount; i++)
  {
    for (current = oSymTable->first; current != NULL; current = forward)
    {
      forward = current->next;
      free((void*) current->key);
      free(current);
    }
  }

  free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable)
{
  assert(oSymTable != NULL);
  
  return oSymTable->length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  
  assert(oSymTable != NULL):
  assert(pcKey != NULL);

  
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  assert(assert(oSymTable != NULL):
  assert(pcKey != NULL);
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
  assert(oSymTable != NULL):
  assert(pcKey != NULL);
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  assert(oSymTable != NULL):
  assert(pcKey != NULL);
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
  assert(oSymTable != NULL):
  assert(pcKey != NULL);
}

void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
  assert(oSymTable != NULL):
  assert(pfApply != NULL);
}
