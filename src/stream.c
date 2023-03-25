#include "stream.h"

void make_stream(struct stream_t* stream, void* data_ptr, size_t data_size) {
    stream->items = malloc(data_size);
    memmove(stream->items, data_ptr, data_size);
    stream->length = data_size/stream->item_size;
    stream->state = SS_SET;
}

void cleanup_stream(struct stream_t* stream) {
    if(stream->state == SS_SET || stream->state == SS_INUSE) {
        free(stream->items);
        stream->items = NULL;
        stream->length = 0L;
        stream->state = SS_USED;
    }
}

char* next_item_from_stream(struct stream_t* stream) {
    if(stream->state == SS_INUSE) {
        char* item_ptr = (char*) malloc(stream->item_size);
        memmove(item_ptr, stream->items, stream->item_size);
        if(--stream->length > 0) {
            const size_t memory_block_size = stream->length * stream->item_size;
            void* _temp_ptr = malloc(memory_block_size);
            memmove(_temp_ptr, stream->items + stream->item_size, memory_block_size);
            stream->items = realloc(stream->items, memory_block_size);
            memmove(stream->items, _temp_ptr, memory_block_size);
            free(_temp_ptr);
        } else {
            cleanup_stream(stream);
        }
        return item_ptr;
    }
    return NULL;    
}

void for_each(struct stream_t* stream, void* cb_ptr) {
    size_t index = 0;
    stream->state = SS_INUSE;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            stream->call(item_ptr, (const size_t)(index++), cb_ptr);
            free(item_ptr);
        }
    }
}