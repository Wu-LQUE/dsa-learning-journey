#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "queueLink.h"

void test_basic_fifo(void) {
    Queue q = createQueue();
    assert(q != NULL);
    addQ(q, 1);
    addQ(q, 2);
    addQ(q, 3);

    assert(!isEmpty(q));
    ElementType x = deleteQ(q);
    assert(x == 1);
    x = deleteQ(q);
    assert(x == 2);
    x = deleteQ(q);
    assert(x == 3);
    assert(isEmpty(q));

    destroyQueue(q);
}

void test_single_element(void) {
    Queue q = createQueue();
    addQ(q, 42);
    assert(!isEmpty(q));
    ElementType x = deleteQ(q);
    assert(x == 42);
    assert(isEmpty(q));
    destroyQueue(q);
}

void test_empty_delete(void) {
    Queue q = createQueue();
    ElementType x = deleteQ(q);
    /* deleteQ 在空队列时返回 INT_MIN */
    assert(x == INT_MIN);
    destroyQueue(q);
}

void test_interleave_operations(void) {
    Queue q = createQueue();
    addQ(q, 10);
    addQ(q, 20);
    ElementType x = deleteQ(q);
    assert(x == 10);
    addQ(q, 30);
    x = deleteQ(q);
    assert(x == 20);
    x = deleteQ(q);
    assert(x == 30);
    assert(isEmpty(q));
    destroyQueue(q);
}

void test_many_elements(void) {
    Queue q = createQueue();
    const int N = 1000;
    for (int i = 0; i < N; ++i) addQ(q, i);
    for (int i = 0; i < N; ++i) {
        ElementType x = deleteQ(q);
        assert(x == i);
    }
    assert(isEmpty(q));
    destroyQueue(q);
}

int main(void) {
    printf("Running queue tests...\n");
    test_basic_fifo();
    test_single_element();
    test_empty_delete();
    test_interleave_operations();
    test_many_elements();
    printf("All tests passed.\n");
    return 0;
}