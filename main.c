#include "includes/streamlib.h"

int filter_evens(int item, const size_t index) {
    return item % 2 == 0;
}

int map_squares(int item, const size_t index) {
    return item * item;
}

int main() {
    int data[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    struct stream_t stream = new_stream_t(int);
    make_stream(&stream, data, sizeof(data));
    struct filter_t evens = new_filter_t(int);
    size_t _count = filter(&evens, &stream, filter_evens);
    printf("Found %lld evens\n", _count);
    for(size_t i = 0; i < evens.data.length; i++) {
        printf("Item %lld -> %d\n", i+1, ((int*) (evens.data.items))[i]);
    }
    
    printf("Stream with original values automatically cleaned up? %s\n", stream.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&stream); // Does not do anything since stream has been cleaned up automatically
    
    struct map_t squares = new_map_t(int, int);
    _count = map(&squares, &(evens.data), map_squares);
    printf("Squared %lld values\n",_count);
    for(size_t i = 0; i < squares.data.length; i++) {
        printf("Item %lld -> %d\n", i+1, ((int*) (squares.data.items))[i]);
    }
    printf("Stream with even values automatically cleaned up? %s\n", evens.data.state == SS_CLEANEDUP ? "Yes" : "No");
    cleanup_stream(&(evens.data)); // Does not do anything since stream has been cleaned up automatically

    cleanup_stream(&(squares.data)); // Cleaning squares
    printf("Stream with squares values automatically cleaned up? %s\n", squares.data.state == SS_CLEANEDUP ? "Yes" : "No");
    return 0;
}