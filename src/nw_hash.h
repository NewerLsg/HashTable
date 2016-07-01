#ifndef NW_HASH
#define NW_HASH

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "nw_util.h"

typedef struct _hs_data_node
{
	char ref[128];	
	char data[1024];
	struct _hs_data_node *next;
}hs_data_node;

typedef struct _hs_bucket_node
{
		hs_data_node *head;
}hs_bucket_node;

typedef struct _hash_table
{
		key_t key;
		unsigned int bucketsize;
		unsigned int maxsize;
		unsigned int freesize;
		hs_bucket_node *bucket;
		hs_data_node *free;
		unsigned long (*hashfunc)(char*);
}hash_table;

void* hs_init( int buckets, int maxsize);

int hs_add(hash_table *hstable, char *key, char *data);

char* hs_get(hash_table * hstable, char *key);

static hs_data_node* hs_fetch_data_node(hash_table *hstable, char *key, int flag);

int hs_remove(hash_table *hstable, char *key);

int hs_destroy(hash_table **hstable);

static hs_data_node* hs_fetch_free_node(hash_table *hstable);

static int hs_release_node(hash_table *hstable, hs_data_node* node);

void hs_dump_info(hash_table *hstable);

#endif //enf of NW_HASH 
