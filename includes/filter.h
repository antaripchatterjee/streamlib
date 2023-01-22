#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"


struct filter_t {
    void* ptr;
    size_t length;
    const size_t item_size;
};

typedef int(*filtering_callback_t)(void* item_ptr, size_t index);

#define new_filter(_T) ((struct filter_t){NULL, 0L, sizeof(_T)})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void filter(struct filter_t* dest, struct stream_t* stream, filtering_callback_t filtering_callback);
void cleanup_filter(struct filter_t* filtered_items);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
