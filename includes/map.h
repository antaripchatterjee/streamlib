#if !defined(__MAP_H__)
#define __MAP_H__

#include "pch.h"
#include "stream.h"

struct mapped_object_t{
    void* items;
    size_t length;
    size_t item_size;
};

struct map_t {
    void (*apply)(char*, size_t, void*);
    struct mapped_object_t dest;
};

#define new_map_t(CB, _T) ({ \
    struct map_t *this = (struct map_t*) malloc(sizeof(struct map_t)); \
    this->apply = ({ \
        void apply(char* item_ptr, size_t index, void* cb_res_ptr) { \
            *(_T*) cb_res_ptr = CB(*(_T*) item_ptr, index); \
        } \
        apply; \
    }); \
    this->dest = (struct mapped_object_t) { NULL, 0L, sizeof(_T)}; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t map(struct map_t* target, struct stream_t* stream);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __MAP_H__
