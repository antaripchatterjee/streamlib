#if !defined(__STREAM_H__)
#define __STREAM_H__

#include "pch.h"

#if !defined(MINALLOCSIZE)
#define MINALLOCSIZE 1024 
#endif // MINALLOCSIZE

#include <stdio.h>

#define NEAREST_DIVISIBLE(MSZ, IZ) (((IZ) == 0) ? -1 : (((MSZ) % (IZ) == 0) ? (MSZ) : ((MSZ) + ((IZ) - ((MSZ) % (IZ))))))


enum stream_state_t {
    SS_ERR = -1,
    SS_INIT,
    SS_ALLOC,
    SS_SET,
    SS_INUSE,
    SS_USED
};


struct stream_t {
    void* items;
    const size_t item_size;
    size_t length;
    size_t capacity;
    enum stream_state_t state;
};

#define init_stream_t(_ISZ) ((struct stream_t) { NULL, _ISZ, 0UL, 0UL, SS_INIT })

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

int make_stream(struct stream_t* stream, void* data_ptr, size_t alloc_size);
void cleanup_stream(struct stream_t* stream);
void* next_item_from_stream(struct stream_t* stream, void* item_ptr);
void for_each(struct stream_t* stream, void* cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __STREAM_H__
