#include "filter.h"

int filter(struct stream_t* stream, struct stream_t* this, filter_cb_t cb_ptr) {
    size_t index = 0UL;
    if(stream == NULL || stream->state != SS_SET) {
        return 0; // input stream error
    }
    if(this == NULL || this->state != SS_ALLOC) {
        cleanup_stream(stream);
        return -1; // output stream error
    }
    if(stream->item_size != this->item_size) {
        cleanup_stream(stream); // item_size mismatch
        return -2;
    }
    if(this->capacity < stream->capacity) {
        return -3; // output capacity error
    }
    char* item_ptr = (char*) malloc(stream->item_size);
    if(item_ptr == NULL) {
        cleanup_stream(stream);
        return -4; // item_ptr error
    }
    stream->state = SS_INUSE;
    while(next_item_from_stream(stream, item_ptr)) {
        int cb_res = cb_ptr(item_ptr, (const size_t) index);
        if(cb_res) {
            memmove(this->items + ((this->length++) * this->item_size), item_ptr, this->item_size);
        }
        index++;
    }
    free(item_ptr);
    this->items = realloc(this->items, this->item_size * this-> length);
    if(this->items == NULL) {
        this->state = SS_ERR;
        return -5;
    }
    this->capacity = this->length;
    this->state = SS_SET;
    return 1;
}