#include <stdio.h>

#include "pool.h"

struct aaa
{
	int i;
	char c;
};

DECLARE_POOL(struct aaa, aaas_pool);

void allocate_objs(size_t from, size_t to, struct aaa **ptrs, struct pool *pool)
{
	for (size_t i = from; i <= to; i++) {
		ptrs[i] = aaas_pool_allocate_obj(pool);
		printf("Allocate %zu: %p\n", i, ptrs[i]);
	}
}

void free_objs(size_t from, size_t to, struct aaa **ptrs, struct pool *pool)
{
	for (size_t i = from; i <= to; i++) {
		int result = aaas_pool_free_obj(pool, ptrs[i]);
		printf("Free %zu: %i\n", i, result);
	}
}

int main()
{
	struct pool *pool = aaas_pool_create(10);
	printf("Create pool: %p\n", pool);
	
	struct aaa *ptrs[11];
	allocate_objs(0, 10, ptrs, pool);
	free_objs(5, 10, ptrs, pool);
	allocate_objs(5, 10, ptrs, pool);
	free_objs(0, 10, ptrs, pool);
	
	int result = aaas_pool_destroy(pool);
	printf("Destroy pool: %i", result);
	return 0;
}