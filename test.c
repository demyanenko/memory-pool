#include <stdio.h>

#include "pool.h"

struct aaa
{
	int i;
	char c;
};

DECLARE_POOL(struct aaa, aaas_pool);

int main()
{
	struct pool *pool = aaas_pool_create(10);
	printf("Create pool: %p\n", pool);
	struct aaa *ptrs[11];
	for (size_t i = 0; i < 11; i++) {
		ptrs[i] = aaas_pool_allocate_obj(pool);
		printf("Allocate %zu: %p\n", i, ptrs[i]);
	}
	for (size_t i = 0; i < 11; i++) {
		int result = aaas_pool_free_obj(pool, ptrs[i]);
		printf("Free %zu: %i\n", i, result);
	}
	int result = aaas_pool_destroy(pool);
	printf("Destroy pool: %i", result);
	return 0;
}