#include <stdio.h>
#include <stdbool.h>

// ===== Stack implementation (array-based, fixed size) =====
#define STACK_CAPACITY 10

typedef struct {
    int data[STACK_CAPACITY];
    int top; // index of the top element, -1 when empty
} Stack;

void stack_init(Stack *s) {
    s->top = -1;
}

bool stack_is_empty(const Stack *s) {
    return s->top == -1;
}

bool stack_is_full(const Stack *s) {
    return s->top == STACK_CAPACITY - 1;
}

bool stack_push(Stack *s, int value) {
    if (stack_is_full(s)) {
        return false;
    }
    s->data[++(s->top)] = value;
    return true;
}

bool stack_pop(Stack *s, int *out) {
    if (stack_is_empty(s)) {
        return false;
    }
    *out = s->data[(s->top)--];
    return true;
}

// ===== Queue implementation (array-based circular buffer) =====
#define QUEUE_CAPACITY 10

typedef struct {
    int data[QUEUE_CAPACITY];
    int front; // index of the current front element
    int size;  // number of elements in the queue
} Queue;

void queue_init(Queue *q) {
    q->front = 0;
    q->size = 0;
}

bool queue_is_empty(const Queue *q) {
    return q->size == 0;
}

bool queue_is_full(const Queue *q) {
    return q->size == QUEUE_CAPACITY;
}

bool enqueue(Queue *q, int value) {
    if (queue_is_full(q)) {
        return false;
    }
    int rear = (q->front + q->size) % QUEUE_CAPACITY;
    q->data[rear] = value;
    q->size++;
    return true;
}

bool dequeue(Queue *q, int *out) {
    if (queue_is_empty(q)) {
        return false;
    }
    *out = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->size--;
    return true;
}

int main(void)
{
    // ===== Array copy demo (元のコード) =====
    int array[10] = { 42, 79, 13 };

    printf("array[0] = %d\n", array[0]);
    printf("array[1] = %d\n", array[1]);
    printf("array[2] = %d\n", array[2]);

    // 他の配列へコピーする
    int copy_array[10];
    for (int i = 0; i < 10; i++) {
        copy_array[i] = array[i];
    }
    printf("copy_array[0] = %d\n", copy_array[0]);
    printf("copy_array[1] = %d\n", copy_array[1]);
    printf("copy_array[2] = %d\n", copy_array[2]);

    // ===== Stack demo (LIFO) =====
    printf("\n-- Stack (LIFO) demo --\n");
    Stack s;
    stack_init(&s);
    stack_push(&s, 2);
    stack_push(&s, 5);
    stack_push(&s, 9);

    int popped;
    if (stack_pop(&s, &popped)) printf("pop -> %d\n", popped); // 9
    if (stack_pop(&s, &popped)) printf("pop -> %d\n", popped); // 5
    if (stack_pop(&s, &popped)) printf("pop -> %d\n", popped); // 2
    if (!stack_pop(&s, &popped)) printf("pop failed (empty)\n");

    // ===== Queue demo (FIFO) =====
    printf("\n-- Queue (FIFO) demo --\n");
    Queue q;
    queue_init(&q);
    enqueue(&q, 2);
    enqueue(&q, 5);
    enqueue(&q, 9);

    int frontVal;
    if (dequeue(&q, &frontVal)) printf("dequeue -> %d\n", frontVal); // 2
    if (dequeue(&q, &frontVal)) printf("dequeue -> %d\n", frontVal); // 5
    enqueue(&q, 3);
    if (dequeue(&q, &frontVal)) printf("dequeue -> %d\n", frontVal); // 9
    if (dequeue(&q, &frontVal)) printf("dequeue -> %d\n", frontVal); // 3
    if (!dequeue(&q, &frontVal)) printf("dequeue failed (empty)\n");

    return 0;
}
