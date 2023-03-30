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

SymTable_T SymTable_new(void)
{
  SymTable_T oSymTable;
  size_t i;
  
  oSymTable = (SymTable_T)calloc(sizeof(struct SymTable));
  if (oSymTable == NULL)
  {
    return NULL;
  }

  oSymTable->length = 0;
  oSymTable->numOfBuckets = 509;
  oSymTable->buckets = calloc(sizeof(struct SymTable_Node*) * numOfBuckets);
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
  size_t j;

  assert(oSymTable != NULL);

  for (i = 0; i < oSymTable->numOfBuckets; i++)
  {
    current = oSymTable->buckets[i]
    for (j = 0; current != NULL; j++)
    {
     current = current[j];
     free((void*) current->key);
     free(current);
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
  for (current = oSymTable->buckets[index]->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey) == 0)
    {
      free(defCopyofKey);
      free(newNode);
      return 0;
    }
    forward = current->next;
  }
  newNode->key = defCopyofKey;
  newNode->value = (void*) pvValue;
  newNode->next = oSymTable->buckets[index]->first;
  oSymTable->buckets[index]->first = newNode;
  oSymTable->length++;
  return 1;

  /* expansion */
  if (index % 509 > 0)
  {
    oSymTable->numOfBuckets = oSymTable->numOfBuckets * 2;
    if (oSymTable->numOfBuckets > 65521)
    {
      return 0;
    }
    oSymTable->buckets = (SymTable_Node**)malloc(sizeof(SymTable_Node**) * numOfBuckets);
  }
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

  index = SymTable_hash(defCopyofKey,oSymTable-> numOfBuckets);
  for (current = oSymTable->buckets[index]->first;
       current != NULL;
       current = forward)
  {
    if(strcmp(current->key, defCopyofKey))
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
  for (current = oSymTable->buckets[index]->first;
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
  free(defCopyofKey);
  return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
  struct Binding *current;
  struct Binding *forward;
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
  for (current = oSymTable->buckets[index]->first;
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
  return NULL;

}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
  const void *holdVal;
  struct SymTableNode *previous;
  struct SymTableNode *current;
  struct SymTableNode *forward;
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
 
 /* Base Case: if SymTable_T structure has only one SymTableNode */
 if(strcmp(oSymTable->buckets[index]->first->key, defCopyofKey) == 0)
 {
   free(defCopyofKey);
   holdVal = oSymTable->buckets[index]->value;
   forward = oSymTable->buckets[index]->next;
   free((void*) oSymTable->buckets[index]->key);
   free(oSymTable->buckets[index]);
   oSymTable->buckets[index] = forward;
   oSymTable->length--;
   return (void*) holdVal;
 }

 previous = oSymTable->first;
 
 /* If a binding in the SymTable_T structure has a key that matches pcKey,
 the SymTableNode is removed from the SymTable strucutre and the binding's value is returned.
 Otherwise, NULL is returned. */
   for (current = oSymTable->buckets[index]->first;
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

 /* shrinking */
 if (index % 509 < 0)
 {
   oSymTable->numOfBuckets = numOfBuckets * 2;
   if (numOfBuckets < 509)
   {
     return 0;
   }
   oSymTable->buckets = (SymTable_Node**)malloc(sizeof(SymTable_Node**) * numOfBuckets);
 }
}

void SymTable_map(SymTable_T oSymTable, void(*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra)
{
 struct SymTableNode *current;
 struct SymTableNode *forward;
 size_t i;

 assert(oSymTable != NULL);
 assert(pfApply != NULL);
 for (i = 0; i < oSymTable->numOfBuckets; i++)
 {
   for (current = oSymTable->buckets[i];
       current != NULL;
       current = forward)
   {
     
    (*pfApply)((void*)current->key, (void*)current->value, (void*)pvExtra);
    forward = current->next;
    
   }
 }
 
}









