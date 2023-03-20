#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"

// struct filtered_object_t{
//     void* items;
//     size_t length;
//     size_t item_size;
// };

struct filter_t {
    void (*check)(char*, size_t, void*);
    // struct filtered_object_t dest;
    struct stream_t data;
};

#define new_filter_t(CB, _T) ({ \
    void check(char* item_ptr, size_t index, void* cb_res_ptr) { \
        *(int*) cb_res_ptr = CB(*(_T*) item_ptr, index); \
    } \
    struct filter_t self = { \
        .check = check, \
        .data = new_stream_t(_T) \
    }; \
    self; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

const size_t filter(struct filter_t* target, struct stream_t* stream);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
