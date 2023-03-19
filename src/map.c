#include "map.h"

size_t map(struct map_t* target, struct stream_t* stream){
    size_t index = 0;
    stream->state = SS_INPROGRESS;
    target->dest.items = malloc(stream->length * stream->item_size);
    target->dest.length = stream->length;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            void* cb_res_ptr = target->dest.items + index * target->dest.item_size;
            target->apply(item_ptr, index, cb_res_ptr);            
            free(item_ptr);
            index++;
        }
    }
    return index;
}
