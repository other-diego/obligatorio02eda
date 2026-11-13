
#ifndef QUEUE_HPP
#define QUEUE_HPP

struct Queue;


Queue* queue_create();


void queue_enqueue(Queue* q, int value);


int queue_dequeue(Queue* q);

int queue_front(const Queue* q);


bool queue_is_empty(const Queue* q);


int queue_size(const Queue* q);


bool queue_contains(const Queue* q, int value);


void queue_print(const Queue* q);


void queue_destroy(Queue* q);

#endif
