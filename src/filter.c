#include "filter.h"

void filter(struct filter_t* dest, struct stream_t* stream, filtering_callback_t filtering_callback) {
    size_t index = 0;
    stream->state = SS_INPROGRESS;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            if(filtering_callback(item_ptr, index)) {
                dest->ptr = dest->length == 0L ?
                    malloc(dest->item_size) :
                    realloc(dest->ptr, dest->item_size * (dest->length + 1));
                memmove(dest->ptr + dest->item_size * (dest->length++), item_ptr, dest->item_size);
            }
            free(item_ptr);
            index++;
        }
    }
}

void cleanup_filter(struct filter_t* filtered_items) {
    if(filtered_items->ptr) {
        free(filtered_items->ptr);
        filtered_items->length = 0L;
    }
}