#include "filter.h"

size_t filter(struct filter_t* dest, struct stream_t* stream, filtering_callback_t filtering_callback) {
    size_t index = 0;
    stream->state = SS_INPROGRESS;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            int result;
            filtering_callback(item_ptr, index, &result);
            if(result) {
                dest->ptr = dest->length == 0L ?
                    malloc(dest->item_size) :
                    realloc(dest->ptr, dest->item_size * (dest->length + 1));
                memmove(dest->ptr + dest->item_size * (dest->length++), item_ptr, dest->item_size);
            }
            free(item_ptr);
            index++;
        }
    }
    return index;
}