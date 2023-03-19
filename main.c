#include "includes/fmr.h"

int filter_evens(int item, size_t index) {
    return item % 2 == 0;
}

int map_squares(int item, size_t index) {
    return item * item;
}

int main() {
    int array[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    struct stream_t stream = new_stream_t(int);
    make_stream(&stream, array, sizeof(array));
    struct filter_t* evens = new_filter_t(filter_evens, int);
    filter(evens, &stream);
    printf("Found %lld evens\n", evens->dest.length);
    for(size_t i = 0; i < evens->dest.length; i++) {
        printf("Item %lld -> %d\n", i+1, ((int*) (evens->dest.items))[i]);
    }
    
    printf("Stream with original values automatically cleaned up? %s\n", stream.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&stream); // Does not do anything since stream has been cleaned up automatically

    struct stream_t s_evens = new_stream_t(int);
    to_stream(&s_evens, &(evens->dest));
    free(evens);
    // cleanup_fmr(&evens);
    
    struct map_t* squares = new_map_t(map_squares, int);
    map(squares, &s_evens);
    printf("Found %lld squares\n", squares->dest.length);
    for(size_t i = 0; i < squares->dest.length; i++) {
        printf("Item %lld -> %d\n", i+1, ((int*) (squares->dest.items))[i]);
    }
    printf("Stream with even values automatically cleaned up? %s\n", s_evens.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&s_evens); // Does not do anything since stream has been cleaned up automatically
    // cleanup_fmr(&squares);
    return 0;
}