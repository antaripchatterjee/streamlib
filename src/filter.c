#include "filter.h"

const size_t filter(struct filter_t* this, struct stream_t* stream) {
    size_t index = 0L;
    stream->state = SS_INPROGRESS;
    while(stream->length) {
        char* item_ptr = next_item_from_stream(stream);
        if(item_ptr) {
            int cb_res;
            this->check(item_ptr, index, &cb_res);
            if(cb_res) {
                this->data.items = this->data.length == 0L ?
                    malloc(this->data.item_size) :
                    realloc(this->data.items, this->data.item_size * (this->data.length + 1));
                memmove(this->data.items + this->data.item_size * (this->data.length++), item_ptr, this->data.item_size);
                index++;
            }
            free(item_ptr);
        }
    }
    if(index > 0L) {
        this->data.state = SS_INITIALIZED;
    }
    return (const size_t) index;
}