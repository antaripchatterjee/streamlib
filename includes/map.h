#if !defined(__MAP_H__)
#define __MAP_H__

#include "pch.h"
#include "stream.h"

struct map_t {
    void (*apply)(char*, size_t, void*);
    struct stream_t data;
};

#define new_map_t(CB, _T) ({ \
    void apply(char* item_ptr, size_t index, void* cb_res_ptr) { \
        *(_T*) cb_res_ptr = CB(*(_T*) item_ptr, index); \
    } \
    struct map_t this ={ \
        .apply = apply, \
        .data = new_stream_t(_T) \
    }; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

const size_t map(struct map_t* target, struct stream_t* stream);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __MAP_H__
