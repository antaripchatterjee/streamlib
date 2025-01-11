#include "stream.h"

int make_stream(struct stream_t* stream, void* data_ptr, size_t alloc_size) {
    stream->items = malloc(alloc_size);
    if(stream->items == NULL) return 0;
    memset(stream->items, 0, alloc_size);
    stream->capacity = alloc_size/stream->item_size;
    if(data_ptr != NULL) {
        memmove(stream->items, data_ptr, alloc_size);
        stream->length = alloc_size/stream->item_size;
        stream->state = SS_SET;
    } else {
        stream->state = SS_ALLOC;
    }
    return 1;
}

void cleanup_stream(struct stream_t* stream) {
    if(stream->state == SS_SET || stream->state == SS_INUSE) {
        if(stream->items) free(stream->items);
        stream->items = NULL;
        stream->capacity = stream->length = 0L;
        stream->state = SS_USED;
    }
}


void* next_item_from_stream(struct stream_t* stream, void* item_ptr) {
    if(stream && stream->state == SS_INUSE && item_ptr) {
        memmove(item_ptr, stream->items, stream->item_size);
        if (stream->length > 1) {
            memmove(stream->items, stream->items + stream->item_size, (stream->length - 1) * stream->item_size);
        }
        stream->length--;
        if(stream->length == 0) {
            cleanup_stream(stream);
        }
        return item_ptr;
    }
    return NULL;
}

// void for_each(struct stream_t* stream, void* cb_ptr) {
//     size_t index = 0;
//     stream->state = SS_INUSE;
//     while(stream->length) {
//         char* item_ptr = next_item_from_stream(stream);
//         if(item_ptr) {
//             stream->call(item_ptr, (const size_t)(index++), cb_ptr);
//             free(item_ptr);
//         }
//     }
// }