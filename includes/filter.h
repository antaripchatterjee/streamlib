#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"


struct filter_t {
    void* ptr;
    size_t length;
    const size_t item_size;
};

typedef void(*filtering_callback_t)(void*, size_t, int*);

#define new_filter(_T) ((struct filter_t){NULL, 0L, sizeof(_T)})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

size_t filter(struct filter_t* dest, struct stream_t* stream, filtering_callback_t filtering_callback);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
