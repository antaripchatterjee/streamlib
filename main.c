#include "includes/fmr.h"

int filter_evens(void* item_ptr, size_t index) {
    return (*(int*)item_ptr) % 2 == 0;
}

int main() {
    struct stream_t stream = new_stream(int);
    int array[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    make_stream(&stream, array, sizeof(array));

    struct filter_t evens = new_filter(int);

    filter(&evens, &stream, filter_evens);
    printf("Found %ld evens\n", evens.length);
    for(size_t i = 0; i < evens.length; i++) {
        printf("Item %ld -> %d\n", i+1, ((int*) (evens.ptr))[i]);
    }
    printf("Stream automatically cleaned up? %s\n", stream.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&stream); // Does not do anything since stream has been cleaned up automatically
    cleanup_filter(&evens);
}