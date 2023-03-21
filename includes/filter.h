#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"

struct filter_t {
    int (*check)(char*, const size_t, void*);
    struct stream_t data;
};

#define new_filter_t(_IT) ({ \
    int check(char* item_ptr, const size_t index, void* cb_ptr) { \
        return ((int(*)(_IT, const size_t))cb_ptr)((*(_IT*) item_ptr), index); \
    } \
    struct filter_t this = { \
        .check = check, \
        .data = new_stream_t(_IT) \
    }; \
    this; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t filter(struct filter_t* this, struct stream_t* stream, void* cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
