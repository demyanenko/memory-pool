#ifndef _POOL_H
#define _POOL_H

#include "stddef.h"
#include "kernel.h"

struct __pool_node {
	struct __pool_node *next;
	boolean is_allocated;
	char object[];
};

struct __chunk {
	struct __chunk *next;
	char memory[];
};

struct pool {
	struct __pool_node *head_node;
	struct __chunk *head_chunk;
};

extern boolean __pool_destroy(struct pool *pool);

extern struct pool *__pool_create(size_t object_size, size_t count);

extern void *__pool_allocate_obj(struct pool *pool);

extern boolean __pool_free_obj(struct pool *pool, void *object);

#define DECLARE_POOL(obj_type, pool_name)											\
static inline boolean pool_name ## _destroy(struct pool *pool)						\
{																					\
	return __pool_destroy(pool);													\
}																					\
static inline struct pool *pool_name ## _create(size_t count)						\
{																					\
	return __pool_create(sizeof(obj_type), count);									\
}																					\
static inline obj_type *pool_name ## _allocate_obj(struct pool *pool)				\
{																					\
	return (obj_type *)__pool_allocate_obj(pool);									\
}																					\
static inline boolean pool_name ## _free_obj(struct pool *pool, obj_type *object)	\
{																					\
	return __pool_free_obj(pool, object);											\
}

#endif /*_POOL_H*/