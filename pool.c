#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "pool.h"

#define MAX_ALLOC_SIZE (100)

boolean __pool_destroy(struct pool *pool)
{
	if (!pool) {
		return FALSE;
	}
	while (pool->head_chunk) {
		struct __chunk *to_delete = pool->head_chunk;
		pool->head_chunk = to_delete->next;
		free(to_delete);
	}
	free(pool);
	return TRUE;
}

struct pool *__pool_create(size_t object_size, size_t count)
{
	struct pool *pool = malloc(sizeof(*pool));
	if (!pool) {
		return NULL;
	}
	pool->head_node = NULL;
	pool->head_chunk = NULL;
	size_t node_size = sizeof(struct __pool_node) + object_size;
	while (count != 0) {
		size_t max_alloc_count = (MAX_ALLOC_SIZE - sizeof(struct __chunk)) / node_size;
		size_t alloc_count = count < max_alloc_count ? count : max_alloc_count;
		struct __chunk *chunk = malloc(sizeof(struct __chunk) + alloc_count * node_size);
		printf("Allocated %zu, alloc_count=%zu, count=%zu\n", sizeof(struct __chunk) + alloc_count * node_size, alloc_count, count);
		if (!chunk) {
			__pool_destroy(pool);
			return NULL;
		}
		chunk->next = pool->head_chunk;
		pool->head_chunk = chunk;
		for (size_t i = 0; i < alloc_count; i++) {
			struct __pool_node *node = (struct __pool_node*)(&chunk->memory[i * node_size]);
			node->next = pool->head_node;
			pool->head_node = node;
		}
		count -= alloc_count;
	}
	return pool;
}

void *__pool_allocate_obj(struct pool *pool)
{
	if (!pool->head_node) {
		return NULL;
	}
	struct __pool_node *to_return = pool->head_node;
	pool->head_node = to_return->next;
	return to_return->object;
}

boolean __pool_free_obj(struct pool *pool, void *object)
{
	if (!pool) {
		return FALSE;
	}
	if (!object) {
		return FALSE;
	}
	struct __pool_node *node = container_of(object, struct __pool_node, object);
	node->next = pool->head_node;
	pool->head_node = node;
	return TRUE;
}