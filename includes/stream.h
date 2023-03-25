#if !defined(__STREAM_H__)
#define __STREAM_H__

#include "pch.h"

enum stream_state_t {
    SS_INIT = -1,
    SS_SET,
    SS_INUSE,
    SS_USED
};


struct stream_t {
    void* items;
    size_t length;
    const size_t item_size;
    enum stream_state_t state;
    void(*call)(char*, const size_t, void*);
};

#define new_stream_t(_T) ({ \
    void call(char* item_ptr, const size_t index, void* cb_ptr) { \
        ((void(*)(_T, const size_t))cb_ptr)(*(_T*) item_ptr, index) ;\
    }\
    struct stream_t init() { \
        return (struct stream_t){NULL, 0L, sizeof(_T), SS_INIT, call}; \
    } \
    init; \
})

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void make_stream(struct stream_t* stream, void* data_ptr, size_t data_size);
void cleanup_stream(struct stream_t* stream);
char* next_item_from_stream(struct stream_t* stream);
void for_each(struct stream_t* stream, void* cb_ptr);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __STREAM_H__
