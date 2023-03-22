#if !defined(__MAP_H__)
#define __MAP_H__

#include "pch.h"
#include "stream.h"

struct map_t {
    void (*apply)(char*, const size_t, void*, void*);
    struct stream_t data;
};

#define new_map_t(_RT, _IT) ({ \
    void apply(char* item_ptr, const size_t index, void* cb_ptr, void* cb_res_ptr) { \
        *(_RT*) cb_res_ptr = ((_RT(*)(_IT, const size_t))cb_ptr)(*(_IT*) item_ptr, index); \
    } \
    struct map_t this ={ \
        .apply = apply, \
        .data = new_stream_t(_RT) \
    }; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t map(struct map_t* this, struct stream_t* stream, void* cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __MAP_H__
