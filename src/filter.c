#include "filter.h"

size_t filter(struct filter_t* target, struct stream_t* stream) {
    size_t index = 0;
    stream->state = SS_INPROGRESS;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            int cb_res;
            target->apply(item_ptr, index, &cb_res);
            if(cb_res) {
                target->dest.items = target->dest.length == 0L ?
                    malloc(target->dest.item_size) :
                    realloc(target->dest.items, target->dest.item_size * (target->dest.length + 1));
                memmove(target->dest.items + target->dest.item_size * (target->dest.length++), item_ptr, target->dest.item_size);
            }
            free(item_ptr);
            index++;
        }
    }
    return index;
}