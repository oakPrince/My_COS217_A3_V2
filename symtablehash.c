/* This code implements a symbol table using a hash table. */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "symtable.h"

/* Each key-value binding pair is stored in a Binding structure.
 Bindings  are linked with pointers to form a linked list. */
struct SymTable_Node
{
  /* Keys stored in constant char pointer. */
  const char *key;
  /* Values stored in void pointer. */
  void *value;
  /* Structure points to next binding in hash table. */
  struct SymTable_Node *next;
};

/* Begins hash table */
struct SymTable
{
  /* Number of bindings is the length  */
  size_t length;
  /* struct Binding begins hash table */
  struct SymTable_Node **buckets;
  /* Number of buckets in the Symtable  */
  size_t numOfBuckets;
};

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

/* SymTable_expand takes a SymTable_T type oSymTable and doubles its size. 
SymTable_T SymTable_expand(SymTable_T oSymTable)
{
  SymTable_T newSymTable;
  size_t doubleNumOfBuckets = oSymTable->numOfBuckets * 2;
  struct SymTable_Node **extra_buckets = calloc(doubleNumOfBuckets, sizeof(struct SymTable_Node*));
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  size_t newIndex;
  char*  defCopyofKey;
  size_t i;
  
  for (i = 0; i < oSymTable->numOfBuckets; i++)
  {
    current = oSymTable->buckets[i];

    create defensive copy
    defCopyofKey = (char*)malloc(strlen(current->key) + 1);
    if (defCopyofKey == NULL)
    {
      return 0;
    }
    
    while(current != NULL)
    {
      forward = current->next;
      strcpy(defCopyofKey, current->key);
      newIndex = SymTable_hash(defCopyofKey, oSymTable->numOfBuckets);
      current->next = extra_buckets[newIndex];
      extra_buckets[newIndex] = current;
    }
  }

  newSymTable = SymTable_new();
  newSymTable->buckets = extra_buckets;
  newSymTable->length = oSymTable->length;
  newSymTable->numOfBuckets = doubleNumOfBuckets;
  free((void*) current->key);
  free(current);
  free(forward);
  free(defCopyofKey);
  free(extra_buckets);
  SymTable_free(oSymTable);
  return newSymTable;
}

*/

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  size_t i;
  
  oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
  if (oSymTable == NULL)
  {
    return NULL;
  }

  oSymTable->length = 0;
  oSymTable->numOfBuckets = 509;
  oSymTable->buckets = calloc(oSymTable->numOfBuckets, sizeof(struct SymTable_Node*));
  if (oSymTable->buckets == NULL)
  {
    free(oSymTable);
    return NULL;
  }

  for (i = 0; i < oSymTable->numOfBuckets; i++)
  {
    oSymTable->buckets[i] = NULL;
  }

  return oSymTable;
}

void SymTable_free(SymTable_T oSymTable)
{
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  size_t i;

  assert(oSymTable != NULL);

  for (i = 0; i < oSymTable->numOfBuckets; i++)
  {
    current = oSymTable->buckets[i];
    while (current != NULL)
    {
      forward = current->next;
      free((void*) current->key);
      free(current);
      current = forward;
    }
  }

  free(oSymTable->buckets);
  free(oSymTable);
}

size_t SymTable_getLength(SymTable_T oSymTable)
{
  assert(oSymTable != NULL);
  
  return oSymTable->length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  struct SymTable_Node *end;
  struct SymTable_Node *newNode;
  char *defCopyofKey;
  size_t index;

  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* allocate memory for newNode structure */
  newNode = malloc(sizeof(struct SymTable_Node));
  if (newNode == NULL)
  {
    return 0;
  }

  /* create defensive copy */
  defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    free(newNode);
    return 0;
  }
  strcpy(defCopyofKey, pcKey);
 
  index = SymTable_hash(defCopyofKey, oSymTable->numOfBuckets);

  /* expansion check 
  if (oSymTable->numOfBuckets < index)
  {
    if (index > 65521)
    {
      return 0;
    }	
    oSymTable = SymTable_expand(oSymTable);
  } */

  current = oSymTable->buckets[index];    
  while (current != NULL)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      free(newNode);
      return 0;
    }
    forward = current->next;
    end = current;
    current = forward;
  }
      
  newNode->key = defCopyofKey;
  newNode->value = (void*) pvValue;
  end->next = newNode;
  oSymTable->length++;
  return 1;
  
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  void *oldVal;
  char *defCopyofKey;
  size_t index;
  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  index = SymTable_hash(defCopyofKey, oSymTable->numOfBuckets);
  current = oSymTable->buckets[index];
  while (current != NULL)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      oldVal = current->value;
      current->value = (void*) pvValue;
      return oldVal;
    }
    forward = current->next;
    current = forward;
  }

  free(defCopyofKey);
  return NULL;
}
    
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  char *defCopyofKey;
  size_t index;
  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  index = SymTable_hash(defCopyofKey, oSymTable->numOfBuckets);
  current = oSymTable->buckets[index];
  while (current != NULL)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      return 1;
    }
    forward = current->next;
    current = forward;
  }
  free(defCopyofKey);
  return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  char *defCopyofKey;
  void *foundVal;
  size_t index;
  
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  /* create defensive copy */
  defCopyofKey = malloc(strlen(pcKey) + 1);
  if (defCopyofKey == NULL)
  {
    return 0;
  }
  strcpy(defCopyofKey, pcKey);

  index = SymTable_hash(defCopyofKey, oSymTable->numOfBuckets);
  current = oSymTable->buckets[index];
  while (current != NULL)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      foundVal = current->value;
      return foundVal;
    }
    forward = current->next;
    current = forward;
  }
  return NULL;

}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
  const void *holdVal;
  struct SymTable_Node *previous;
  struct SymTable_Node *current;
  struct SymTable_Node *forward;
  char *defCopyofKey;
  size_t index;

  assert(oSymTable != NULL);
  assert(pcKey != NULL);

 /* create defensive copy */
 defCopyofKey = (char*)malloc(strlen(pcKey) + 1);
 if (defCopyofKey == NULL)
 {
   return 0;
 }
 strcpy(defCopyofKey, pcKey);

 index = SymTable_hash(defCopyofKey, oSymTable-> numOfBuckets);
 current = oSymTable->buckets[index];
 
 /* Base Case: if SymTable_T structure has only one SymTableNode */
 if(strcmp(current->key, defCopyofKey) == 0)
 {
   free(defCopyofKey);
   holdVal = current->value;
   forward = current->next;
   free((void*) current->key);
   free(current);
   oSymTable->length--;
   return (void*) holdVal;
 }

 previous = oSymTable->buckets[index];
 
 /* If a binding in the SymTable_T structure has a key that matches pcKey,
 the SymTableNode is removed from the SymTable strucutre and the binding's value is returned.
 Otherwise, NULL is returned. */
 while (current != NULL)
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
   current = forward;
 }

 free(defCopyofKey);
 return NULL;

}

void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
 struct SymTable_Node *current;
 struct SymTable_Node *forward;
 size_t i;
 
 assert(oSymTable != NULL);
 assert(pfApply != NULL);

 for (i = 0; i < oSymTable->numOfBuckets; i++)
 {
   current = oSymTable->buckets[i];
   while (current != NULL)
   {
     (*pfApply)((void*)current->key, (void*)current->value, (void*)pvExtra);
     forward = current->next;
     current = forward;
   }
 }
 
}









