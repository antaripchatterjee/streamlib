#include "reduce.h"

void reduce(struct reduce_t* this, struct stream_t* stream, void* cb_ptr, void* init_ptr) {
    size_t index = -1L;
    stream->state = SS_INPROGRESS;
    if(init_ptr != NULL) {
        memmove(this->data.item, init_ptr, this->data.item_size);
    }
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            this->apply(item_ptr, (const size_t) (++index), cb_ptr, this->data.item);
            free(item_ptr);
        }
    }
}