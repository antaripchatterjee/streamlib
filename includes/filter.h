#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"

struct filter_t {
    struct stream_t data;
    int(*check)(char*, const size_t, void*);
};

#define new_filter_t(_IT) ({ \
    int check(char* item_ptr, const size_t index, void* cb_ptr) { \
        return ((int(*)(_IT, const size_t))cb_ptr)((*(_IT*) item_ptr), index); \
    } \
    struct filter_t this = { \
        .data = new_stream_t(_IT)() \
    }; \
    struct filter_t init() { \
        this.check = check; \
        return this; \
    } \
    init; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void filter(struct filter_t* this, struct stream_t* stream, void* cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
