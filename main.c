#include "includes/streamlib.h"

int select_evens(int item, const size_t index) {
    return item % 2 == 0;
}

int get_squares(int item, const size_t index) {
    return item * item;
}

int sum_squares(int prev_item, int curr_item, const size_t index) {
    return prev_item + curr_item;
}

int main() {
    int data[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    struct stream_t stream = new_stream_t(int)();
    make_stream(&stream, data, sizeof(data));
    struct filter_t evens = new_filter_t(int)();
    filter(&evens, &stream, select_evens);
    if(stream.state == SS_USED) {
        puts("Stream of integers already cleaned up");
    } else {
        cleanup(&stream); // Does not do anything since stream has been cleaned up automatically
    }
    
    struct map_t squares = new_map_t(int, int)();
    map(&squares, &(evens.data), get_squares);
    if(evens.data.state == SS_USED) {
        puts("Stream of evens already cleaned up");
    } else {
        cleanup(&evens); // Does not do anything since stream has been cleaned up automatically
    }

    int sum = 0; // set initial value
    struct reduce_t reducer = new_reduce_t(int, int)(&sum);
    reduce(&reducer, &(squares.data), sum_squares);
    if(squares.data.state == SS_USED) {
        puts("Stream of squares already cleaned up");
    } else {
        cleanup(&squares); // Does not do anything since stream has been cleaned up automatically
    }
    printf("Sum of squares of evens: %d\n", sum);
    return 0;
}
