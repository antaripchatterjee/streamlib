#if !defined(__REDUCE_H__)
#define __REDUCE_H__

#include "pch.h"
#include "stream.h"

struct reduce_t {
    void (*apply)(char*, const size_t, void*, void*);
    struct {void* item; const size_t item_size; } data;
};

#define new_reduce_t(_RT, _IT) ({ \
    void apply(char* item_ptr, const size_t index, void* cb_ptr, void* data_ptr) { \
        *(_RT*) data_ptr = ((_RT(*)(_RT, _IT, const size_t))cb_ptr)(*(_RT*) data_ptr, *(_IT*) item_ptr, index); \
    } \
    struct reduce_t this = { \
        .apply = apply, \
        .data = { \
            .item = malloc(sizeof(_RT)), \
            .item_size = sizeof(_RT) \
        } \
    }; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void reduce(struct reduce_t* this, struct stream_t* stream, void* cb_ptr, void* init_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __REDUCE_H__
