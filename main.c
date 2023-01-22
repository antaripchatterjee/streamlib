#include "includes/fmr.h"

void filter_evens(void* item_ptr, size_t index, int* result_ptr) {
    *result_ptr = (*(int*)item_ptr) % 2 == 0;
}

void map_squares(void* item_ptr, size_t index, void* result_ptr) {
    int item = *(int*) item_ptr;
    *(int*)result_ptr = item * item;
}

int main() {
    struct stream_t stream = new_stream(int);
    struct filter_t evens = new_filter(int);
    int array[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    make_stream(&stream, array, sizeof(array));

    filter(&evens, &stream, filter_evens);
    printf("Found %ld evens\n", evens.length);
    for(size_t i = 0; i < evens.length; i++) {
        printf("Item %ld -> %d\n", i+1, ((int*) (evens.ptr))[i]);
    }
    printf("Stream with original values automatically cleaned up? %s\n", stream.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&stream); // Does not do anything since stream has been cleaned up automatically

    struct stream_t s_evens = new_stream(int);
    struct map_t squares = new_map(int);

    to_stream(&s_evens, &evens);
    cleanup_fmr(&evens);

    map(&squares, &s_evens, map_squares);
    printf("Found %ld squares\n", squares.length);
    for(size_t i = 0; i < squares.length; i++) {
        printf("Item %ld -> %d\n", i+1, ((int*) (squares.ptr))[i]);
    }
    printf("Stream with even values automatically cleaned up? %s\n", s_evens.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&s_evens); // Does not do anything since stream has been cleaned up automatically
    cleanup_fmr(&squares);
    return 0;
}