
#include "data_types.h"
#include "HashTable.h"
#include "GRAPH_SEARCH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



// =========  YOUR COMPULSORY (BUT SPECIFIC TO THE PROBLEM) FUNCTIONS =======

//___________________ Create unique char key for each state______________________
void Generate_HashTable_Key(const State *const state, unsigned char* key) 
{
    // Concatenate each tile value (0-8) as a character
    for(int i = 0; i < PUZZLE_SIZE; ++i) {
        key[i] = '0' + state->tiles[i];
    }
    key[PUZZLE_SIZE] = '\0';
    
}


// ======= YOU DO NOT NEED TO CHANGE THIS COMPULSORY DECLARATIONS ==============

//___________________ Determine whether x is prime or not______________________
static int is_prime(const unsigned int x) {
	int i;
	
    if(x<2) 
		return FALSE; 
		
	for(i=2; i<=x/2; i++){
		if(x%i==0)
			return FALSE;
	}	
	
	return TRUE; 	   
}

 //________ Return the next prime after x, or x if x is prime_________________
static unsigned next_prime(unsigned int x) {
    while (is_prime(x) == FALSE) {
        x++;
    }
    return x;
}

//___________________ Hash Function __________________________________
static unsigned int hash_func(const char* key, const int size) {
    unsigned int hash = 5381; // Daha iyi dağılım için magic number
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % size;
}

//___________________ Create new Hash Table______________________
Hash_Table* New_Hash_Table(const int size) {      
    Hash_Table* ht = (Hash_Table*)malloc(sizeof(Hash_Table));
    if(ht==NULL)
        Warning_Memory_Allocation(); 

    ht->size = next_prime(size);

    ht->count = 0;
    
    ht->State_Key = (unsigned char**)calloc(ht->size, sizeof(unsigned char*));
    if(ht->State_Key==NULL)
        Warning_Memory_Allocation(); 
        
    return ht;
}

//___________________ Insert __________________________________
void ht_insert(Hash_Table *ht, const State *const state) {
    char key[MAX_KEY_SIZE];    
    	
	Generate_HashTable_Key(state, key);
	ht_insert_key(ht, key);
}

void ht_insert_key(Hash_Table *ht, const char *key) {
    unsigned int index;
    unsigned const int load = ht->count * 100 / ht->size;
    unsigned int new_size;  
    
    if (load > HASH_TABLE_INCREASING_RATE) {
        new_size = ht->size * 2;
        Resize_Hash_Table(ht, new_size);
    }
    
    if(ht->size==ht->count){
    	printf("ERROR: Hash table is full.\n");
		exit(-1);	
	}	
	
	index = hash_func(key, ht->size);
    while (ht->State_Key[index] != NULL) {
    	if(index==ht->size-1)
    		index = 0; 
    	else
		    index++;
    } 
    
    ht->State_Key[index] = (unsigned char*)malloc(MAX_KEY_SIZE*sizeof(unsigned char));
    if(ht->State_Key[index]==NULL)
        Warning_Memory_Allocation();
    strcpy(ht->State_Key[index], key);
    ht->count++;
}

//___________________ Search __________________________________
int ht_search(Hash_Table *ht, const State *const state) {
	char key[MAX_KEY_SIZE]; 
    unsigned int first_index, index;
    
    Generate_HashTable_Key(state, key);
    index       = hash_func(key, ht->size);
    first_index = index; 
    
    printf("key = %s,  index = %u\n", key, index);
    
    while (ht->State_Key[index] != NULL) {
    	if (strcmp(ht->State_Key[index], key) == 0)
    		return TRUE;
    	
    	if(index==ht->size-1)
    		index = 0; 
    	else
		    index++;
		    
		if(index==first_index)
		   return FALSE;	    
    } 
    
    return FALSE;   
}

//________ Resize Hash Table ___________________________________
void Resize_Hash_Table(Hash_Table* ht, const int size) {
	int i;
	unsigned int temp_size, temp_count;
	unsigned char** temp_key;
    Hash_Table *new_ht = New_Hash_Table(size);
    
    // create new larger hash table
    for (i = 0; i < ht->size; i++) {
        if (ht->State_Key[i] != NULL) {
            ht_insert_key(new_ht, ht->State_Key[i]);
        }
    }

    // swap size
    temp_size    = ht->size;
    ht->size     = new_ht->size;
    new_ht->size = temp_size;
    
    // swap count
    temp_count    = ht->count;
    ht->count     = new_ht->count;
    new_ht->count = temp_count;
    
    // swap keys
    temp_key          = ht->State_Key;
    ht->State_Key     = new_ht->State_Key;
    new_ht->State_Key = temp_key;

    Delete_Hash_Table(new_ht);
}

//________ Delete Hash Table ___________________________________
void Delete_Hash_Table(Hash_Table *ht)
{
	int i;

    for (i = 0; i < ht->size; i++) {
        if (ht->State_Key[i] != NULL) {
            free(ht->State_Key[i]);
        }
    }
    free(ht->State_Key);
    free(ht);  
}

//___________________ Show hash table __________________________________
void Show_Hash_Table(Hash_Table *ht) {
    unsigned int i;
    
    printf("\nHASH TABLE IS (Size = %u, Count = %u ): \n", ht->size, ht->count);
    for (i=0; i<ht->size; i++) 
    	if (ht->State_Key[i] != NULL)
    		printf("[%u] --> %s\n", i, ht->State_Key[i]);
}

#include "data_types.h"

// Fonksiyon implementasyonu (dosyanın sonuna ekleyin)
void Compute_State_Hash(State *state) {
    unsigned int hash = 5381;  // Daha iyi dağılım için başlangıç değeri
    for(int i = 0; i < PUZZLE_SIZE; i++) {
        hash = ((hash << 5) + hash) + state->tiles[i];  // hash * 33 + c
    }
    state->hash = hash;
}



