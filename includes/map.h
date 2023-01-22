#if !defined(__MAP_H__)
#define __MAP_H__

#include "pch.h"
#include "stream.h"

struct map_t {
    void* ptr;
    size_t length;
    const size_t item_size;
};

#define new_map(_T) ((struct map_t){NULL, 0L, sizeof(_T)})

typedef void(*mapping_callback_t)(void*, size_t, void*);

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t map(struct map_t* dest, struct stream_t* stream, mapping_callback_t maping_callback);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __MAP_H__
