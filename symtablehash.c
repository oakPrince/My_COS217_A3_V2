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
  oSymTable->length++;
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
      {
	free(defCopyofKey);
	oldVal = current->value;
	current->value = (void*) pvValue;
	return oldVal;
      }
      forward = current->next;
    }

    free(defCopyofKey);
    return NULL;
  }
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
  struct Binding *current;
  struct Binding *forward;
  char *defCopyofKey;
  
  assert(oSymTable != NULL):
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  /* search SymTable_T structure for any key-value pairs that have the key pcKey.
 If there is a match, return 1. If not, return 0 */
  for (int i = 0; i < uBucketCount; i++)
  {
    for (current = oSymTable->buckets[uBucketCount];
       current != NULL;
       current = forward)
      {
	if(strcmp(current->key, defCopyofKey) == 0)
	{
	  free(defCopyofKey);
	  return 1;
	}
	forward = current->next;
      }
  }
  free(defCopyofKey);
  return 0;
 
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct Binding *current;
  struct Binding *forward;
  char *defCopyofKey;
  void *foundVal;
  
  assert(oSymTable != NULL):
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);
  
  /* Search SymTable_T structure for any bindings with pcKey as the key.
     If there is a binding with pcKey, the value of that binding is returned.
     If not, NULL is returned. */
  for (int i = 0; i < uBucketCount; i++)
  {
    for (current = oSymTable->buckets[uBucketCount];
       current != NULL;
       current = forward)
      {
        if(strcmp(current->key, defCopyofKey) == 0)
        {
          free(defCopyofKey);
          foundVal = current->value;
	  return foundVal;
        }
        forward = current->next;
      }
  }
  free(defCopyofKey);
  return NULL;

}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
  const void *holdVal;
  struct SymTableNode *previous;
  struct SymTableNode *current;
  struct SymTableNode *forward;
  char *defCopyofKey;

  assert(oSymTable != NULL):
  assert(pcKey != NULL);

  /* create defensive copy */
 defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
 if (defCopyofKey == NULL)
 {
   return 0;
 }
 strcpy(defCopyofKey, pcKey);

 /* Base Case: if SymTable_T structure has only one SymTableNode */
 if(strcmp(oSymTable->buckets[1]->key, defCopyofKey) == 0)
 {
   free(defCopyofKey);
   holdVal = oSymTable->buckets[1]->value;
   forward = oSymTable->buckets[1]->next;
   free((void*) oSymTable->buckets[1]->key);
   free(oSymTable->buckets[1]);
   oSymTable->buckets[1] = forward;
   oSymTable->length--;
   return (void*) holdVal;
 }

 previous = oSymTable->first;
 
 /* If a binding in the SymTable_T structure has a key that matches pcKey,
 the SymTableNode is removed from the SymTable strucutre and the binding's value is returned.
 Otherwise, NULL is returned. */
 for (int i = 0; i < uBucketCount; i++)
 {
   for (current = oSymTable->buckets[uBucketCount];
	current != NULL;
	current = forward)
   {
     if(strcmp(current->key, defCopyofKey) == 0)
     {
       free(defCopyofKey);
       holdVal = current->value;
       forward = current->next;
       previous->next = forward;
       free((void*) current->key);
       free(current);
       oSymTable->length--;
       return (void*) holdVal;
     }
     forward = current->next;
     previous = current;
   }
 }
 
 free(defCopyofKey);
 return NULL;
}

void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
 struct SymTableNode *current;
 struct SymTableNode *forward;

 assert(oSymTable != NULL);
 assert(pfApply != NULL);

 /* applies pfApply function to every binding in SymTable_T structure */
 for (int i = 0; i < uBucketCount; i++)
 {
   for (current = oSymTable->buckets[uBucketCount];
	current != NULL;
	current = forward)
   {
     (*pfApply)((void*)current->key, (void*)current->value, (void*)pvExtra);
     forward = current->next;
   }
 }
}
