#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"

struct filtered_object_t{
    void* items;
    size_t length;
    size_t item_size;
};

struct filter_t {
    void (*apply)(char*, size_t, void*);
    struct filtered_object_t dest;
};

#define new_filter_t(CB, _T) ({ \
    struct filter_t *this = (struct filter_t*) malloc(sizeof(struct filter_t)); \
    this->apply = ({ \
        void apply(char* item_ptr, size_t index, void* cb_res_ptr) { \
            *(int*) cb_res_ptr = CB(*(_T*) item_ptr, index); \
        } \
        apply; \
    }); \
    this->dest = (struct filtered_object_t) { NULL, 0L, sizeof(_T)}; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t filter(struct filter_t* target, struct stream_t* stream);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
