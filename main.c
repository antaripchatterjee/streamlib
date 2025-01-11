#include "includes/streamlib.h"

int select_evens(void* item_ptr, const size_t index) {
    return item_ptr && (*(int*)item_ptr) % 2 == 0;
}

int get_squares(int item, const size_t index) {
    return item * item;
}

int sum_squares(int prev_item, int curr_item, const size_t index) {
    return prev_item + curr_item;
}

void for_each_callback(int item, const size_t index) {
    printf("Found %d at %zu\n", item, index);
}

int main() {
    int data[10] = {
        2, 3, 1, 18, 23,
        69, 93, 8, 69, 14
    };
    // struct stream_t stream = new_stream_t(int)();
    struct stream_t stream = init_stream_t(sizeof(int));
    if(!make_stream(&stream, data, sizeof(data))) return -1;
    // printf("%zu %zu\n", stream.length);
    struct stream_t evens = init_stream_t(sizeof(int));
    if(!make_stream(&evens, NULL, sizeof(data)));
    filter(&stream, &evens, &select_evens);
    int i;
    evens.state = SS_INUSE;
    while(next_item_from_stream(&evens, &i)) {
        printf("%d is even\n", i);
    }
    printf("state %d $%zu\n", evens.state, evens.length);
    // struct filter_t evens = new_filter_t(int)();
    // filter(&evens, &stream, select_evens);
    // for_each(&(evens.data), for_each_callback);
    // if(stream.state == SS_USED) {
    //     puts("Stream of integers already cleaned up");
    // } else {
    //     cleanup(&stream); // Does not do anything since stream has been cleaned up automatically
    // }
    
    // struct map_t squares = new_map_t(int, int)();
    // map(&squares, &(evens.data), get_squares);
    // if(evens.data.state == SS_USED) {
    //     puts("Stream of evens already cleaned up");
    // } else {
    //     cleanup(&evens); // Does not do anything since stream has been cleaned up automatically
    // }

    // int sum = 0; // set initial value
    // struct reduce_t reducer = new_reduce_t(int, int)(&sum);
    // reduce(&reducer, &(squares.data), sum_squares);
    // if(squares.data.state == SS_USED) {
    //     puts("Stream of squares already cleaned up");
    // } else {
    //     cleanup(&squares); // Does not do anything since stream has been cleaned up automatically
    // }
    // printf("Sum of squares of evens: %d\n", sum);
    return 0;
}
