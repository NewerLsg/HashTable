#include "nw_hash.h"
#include<stdio.h>

int main(int argc, char const *argv[])
{
	hash_table *hstable;
	
	hstable = (hash_table *)hs_init(10, 10*4);

	char key[10];
	char val[20];

	int i = 0;

	for(; i < 41; i++) {
		memset(key, 0, sizeof(key));
		memset(val, 0, sizeof(val));
		snprintf(key, sizeof(key), "key%d", i);
		snprintf(val, sizeof(val), "val%d", i);

		hs_add(hstable, key, val);
	}

	hs_dump_info(hstable);

	hs_destroy(&hstable);

	printf("process done.\n");

	return 0;
}
