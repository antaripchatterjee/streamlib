#include "map.h"

size_t map(struct map_t* dest, struct stream_t* stream, mapping_callback_t maping_callback){
    size_t index = 0;
    stream->state = SS_INPROGRESS;
    dest->ptr = malloc(stream->length * stream->item_size);
    dest->length = stream->length;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            void* result = dest->ptr + index * dest->item_size;
            maping_callback(item_ptr, index, result);            
            free(item_ptr);
            index++;
        }
    }
    return index;
}
