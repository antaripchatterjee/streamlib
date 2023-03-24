#include "streamlib.h"

void cleanup_default(void* ptr){
    if(ptr != NULL) {
        free(((struct{struct {void* result_ptr;} data;}*)ptr)->data.result_ptr);
        (&(((struct{struct {void* result_ptr;} data;}*)ptr)->data))->result_ptr = NULL;
    }
}

void cleanup_common(void* ptr) {
    if(ptr != NULL) cleanup_stream(&(((struct {struct stream_t data;}*)ptr)->data));
}
