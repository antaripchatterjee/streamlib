#include "map.h"

void map(struct map_t* this, struct stream_t* stream, void* cb_ptr) {
    size_t index = 0;
    stream->state = SS_INUSE;
    this->data.items = malloc(stream->length * stream->item_size);
    this->data.length = stream->length;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            void* cb_res_ptr = this->data.items + index * this->data.item_size;
            this->apply(item_ptr, (const size_t) index, cb_ptr, cb_res_ptr);
            free(item_ptr);
            index++;
        }
    }
    if(index > 0L) {
        this->data.state = SS_SET;
    }
}
