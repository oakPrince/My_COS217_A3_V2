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
    for (current = oSymTable->buckets[i]; current != NULL; current = forward)
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
  struct Binding *current;
  struct Binding *forward;
  struct Binding *newBinding;
  char *defCopyofKey;
  
  assert(oSymTable != NULL):
  assert(pcKey != NULL);

  /* allocate memory for newBinding structure */
  newBinding = malloc(sizeof(struct Binding));
  if (newBinding = NULL)
  {
    return 0;
  }

  /* create defensive copy */
  defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    free(newBinding);
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* search SymTable_T structure to see if there are
 any bindings with keys that are the same as pcKey */

  for (int i = 0; i < uBucketCount; i++)
  {
    for (current = oSymTable->buckets[i]; current != NULL; current = forward)
    {
      if(strcmp(current->key, defCopyofKey) == 0)
      {
	free(defCopyofkey);
	free(newBinding);
	return 0;
      }
      forward = current->next;
    }
  }
  size_t hash = SymTable_hash(defCopyofKey, uBucketCount);
  newBinding->key = defCopyofKey;
  newBinding->value = (void*) pvValue;
  newBinding->next = oSymTable->buckets[hash];
  oSymTable->buckets[hash]->newBinding;
  return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct Binding *current;
  struct Binding *forward;
  void *oldVal;
  char *defCopyofKey;
  
  assert(assert(oSymTable != NULL):
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* Search SymTable_T structure to see if
  it has a binding with a key matching pcKey.
  If it does, change the value of that Binding to pvValue.
  Then, return the old value. */
  for (int i = 0; i < uBucketCount; i++)
  {
    for (current = oSymTable->buckets[i]; current != NULL; current = forward)
    {
      if(strcmp(current->key, defCopyofKey) == 0)
	free();
    }
  }
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
