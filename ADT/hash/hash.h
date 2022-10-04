typedef struct HashTabRep *HashTable; 

typedef char Item; 

typedef char *Key; 
// make new empty table of size N
HashTable newHashTable(int); 
// add item into collection 
void HashInsert(HashTable, Item);
// find item within a key 
Item *HashGet(HashTable, Key); 
// delete a key from a hash table 
void HashDelete(HashTable, Key);
// Free the hashtable 
void dropHashTable(HashTable);