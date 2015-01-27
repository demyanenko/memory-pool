#ifndef _DEFINES_H
#define _DEFINES_H

typedef enum {FALSE = 0, TRUE} boolean;

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#endif /*_DEFINES_H*/