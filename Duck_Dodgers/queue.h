#ifndef _QUEUE_H
#define _QUEUE_H

#include <exceptions.h>

const int QUEUE_SIZE = 16;

template <class QueueType>
class Queue {
 public:
  Queue() {

    data = new QueueType[QUEUE_SIZE];
    capacity = QUEUE_SIZE;
    count = 0;
    head = QUEUE_SIZE - 1;
    tail = 0;
  }

  ~Queue() {

    delete[] data;
  }

  int size() { return count; }
  bool isEmpty() { return !count; }

  void clear() {

    count = tail = 0;
    head = capacity - 1;
  }

  void enqueue(QueueType d) {

    if (count == QUEUE_SIZE) {
      QueueType *tmpData = new QueueType[2*capacity];

      for (int i=0;i<count;i++)
        tmpData[i] = data[++head%capacity];

      tail = count;
      head = 2*capacity - 1;

      capacity *= 2;

      delete[] data;
      data = tmpData;
    }

    data[tail] = d;
    tail = ++tail % capacity;
    count++;
  }



  QueueType dequeue() {

   if (count == 0)
     throw ContainerEmptyException();

    count--;
    return data[++head % capacity];
  }

 private:
  QueueType
    *data;
  int
    capacity,
    count,
    head,
    tail;
};

#endif
