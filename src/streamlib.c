#include "streamlib.h"

// void cleanup_fmr(void* fmr_object) {
//     __auto_type data = (struct {void*ptr; size_t length;} *) fmr_object;
//     if(data->ptr) {
//         free(data->ptr);
//         data->length = 0L;
//     }
// }