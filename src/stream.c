#include "stream.h"

void make_stream(struct stream_t* stream, void* data_ptr, size_t data_size) {
    stream->items = malloc(data_size);
    memmove(stream->items, data_ptr, data_size);
    stream->length = data_size/stream->item_size;
    stream->state = SS_INITIALIZED;
}

void to_stream(struct stream_t* stream, void* src) {
    __auto_type data = (struct {void* items; size_t length; const size_t item_size;} *) src;
    make_stream(stream, data->items, data->length * data->item_size);
}

void cleanup_stream(struct stream_t* stream) {
    if(stream->state == SS_INITIALIZED || stream->state == SS_INPROGRESS) {
        free(stream->items);
        stream->items = NULL;
        stream->length = 0L;
        stream->state = SS_CLEANEDUP;
    }
}

char* next_item_from_stream(struct stream_t* stream) {
    if(stream->state == SS_INPROGRESS) {
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
