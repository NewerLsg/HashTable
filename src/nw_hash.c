#include "nw_hash.h"
#include "nw_util.h"

void * 
hs_init(int bucketsize, int maxsize) 
{
	if (bucketsize > maxsize) bucketsize = maxsize;

	unsigned int size =  sizeof(hash_table) + sizeof(hs_bucket_node) * bucketsize + sizeof(hs_data_node) * maxsize;

	srand(time(NULL));

	key_t  key = rand();

	int shmid =  shmget(key, size, 0666 | IPC_CREAT);

	if (shmid < 0) {
		printf("fail to init shm,msg[%s]\n", strerror(errno));
		return NULL;
	}

	char* ptr = (char*) shmat(shmid, NULL, 0);

	if (ptr == NULL) {
		printf("failt to shmat. msg[%s]\n", strerror(errno));
		return NULL;
	}  

	hash_table *hstable  = (hash_table *) ptr;
	hstable->key 					= key;
	hstable->bucketsize	= bucketsize;
	hstable->maxsize		= hstable->freesize		= maxsize;
	hstable->bucket 		   = (hs_bucket_node *) (ptr + sizeof(hash_table));
	hstable->hashfunc    = ELFHash;

	int i = 0;
	for (; i < bucketsize; ++i) {
		hstable->bucket[i].head = NULL;
	}

	hstable->free = (hs_data_node *) (ptr + sizeof(hash_table) + sizeof(hs_bucket_node)  * ( hstable->bucketsize));

	for (i = 0; i < maxsize - 1; i++) {
		hstable->free[i].next = hstable->free + i + 1;
	}

	hstable->free[i].next = NULL;

	return hstable;
}

int 
hs_add(hash_table *hstable, char *key, char *data) 
{
	if (hstable == NULL || key == NULL) return -1; 

	hs_data_node *node = (hs_data_node *)hs_fetch_data_node(hstable, key, 0);
	//hs_data_node *node = NULL;
	if (node == NULL) {
		 node = (hs_data_node *) hs_fetch_free_node(hstable);

		 if (node == NULL) return -1;

		unsigned long mode =  hstable->hashfunc(key) % hstable->bucketsize;

		node->next = hstable->bucket[mode].head;
		hstable->bucket[mode].head = node;

		memset(node->ref, 0, sizeof(node->ref));
		snprintf(node->ref,  sizeof(node->ref), "%s", key);
	}

	memset(node->data, 0, sizeof(node->data));
	snprintf(node->data,  sizeof(node->data), "%s", data);

	return 0;
}

char* 
hs_get(hash_table * hstable, char *key)
{
	hs_data_node *node = hs_fetch_data_node(hstable, key, 0);

	if (node != NULL)  return node->data;

	return NULL;
}

hs_data_node* 
hs_fetch_data_node(hash_table *hstable, char *key, int flag) 
{
	if (hstable == NULL || key == NULL) return NULL;

	unsigned long mode = hstable->hashfunc(key) % hstable->bucketsize;

	hs_data_node *node = hstable->bucket[mode].head;

	hs_data_node *before = NULL;

	while(node) {
	
		if (strcmp(node->ref, key) == 0) break;
		
		before = node;
		
		node = node->next; 
	}

	//remove from bucket
	if (flag == 1 && node != NULL) {
		if (node == hstable->bucket[mode].head) {
			hstable->bucket[mode].head = node->next;

		} else {
			before->next = node->next;
		}
	}

	return node;
}

int 
hs_remove(hash_table *hstable, char *key)
{
	hs_data_node *node = hs_fetch_data_node(hstable, key, 1);

   return	hs_release_node(hstable, node);
}

int 
hs_destroy(hash_table **hstable) 
{
	if (*hstable == NULL) return -1;

	shmdt(*hstable);

	*hstable = NULL;
}

 hs_data_node* 
 hs_fetch_free_node(hash_table *hstable) 
 {
 		if (hstable->freesize <= 0 || hstable->free == NULL) {
 			printf("no free node!\n");
 			return NULL;
 		}
 	   hs_data_node *free_node = hstable->free;	

 	   hstable->free = hstable->free->next;

 	   hstable->freesize--;

 	   return free_node;
 }

 int 
 hs_release_node(hash_table *hstable, hs_data_node* node) 
 {
 	if (hstable == NULL || node == NULL) return -1;

 	hstable->freesize++;
 	node->next = hstable->free;
 	hstable->free = node;

 	return 0;
 }

void 
hs_dump_info(hash_table *hstable) {
 	if (hstable == NULL) return ;

 	printf("bucketsize:%d\n", hstable->bucketsize);
 	printf("maxsize:%d\n", hstable->maxsize);
 	printf("freesize:%d\n", hstable->freesize);
 	printf("node:\n" );

 	int i;
 	for (i = 0; i < hstable->bucketsize; ++i)
 	{
 		hs_data_node *node = hstable->bucket[i].head;

 		if( node != NULL)
 			printf("mode:[%d]\n", i);

 		while(node) {
 			printf("key:[%s]\t", node->ref);
 			printf("value:[%s]\n",node->data);
 			node = node->next;
 		}
 	}
}