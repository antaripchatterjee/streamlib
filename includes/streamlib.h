#if !defined(__STREAMLIB_H__)
#define __STREAMLIB_H__

#include "stream.h"
#include "filter.h"
#include "map.h"
#include "reduce.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void cleanup_default(void* ptr);
void cleanup_common(void* ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#define cleanup(PTR) _Generic((PTR), \
    struct stream_t*: cleanup_stream, \
    struct filter_t*: cleanup_common, \
    struct map_t*: cleanup_common, \
    struct reduce_t*: cleanup_default, \
    default: cleanup_default \
)(PTR)

#endif // __STREAMLIB_H__
