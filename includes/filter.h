#if !defined(__FILTER_H__)
#define __FILTER_H__

#include "pch.h"
#include "stream.h"

typedef int(*filter_cb_t)(void*, const size_t);

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

int filter(struct stream_t* stream, struct stream_t* this, filter_cb_t cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FILTER_H__
