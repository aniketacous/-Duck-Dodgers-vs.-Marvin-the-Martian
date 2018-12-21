#ifndef _LINEARLIST_H
#define _LINEARLIST_H

#include <exceptions.h>

template <class ListType>
class LinearList;

template <class ListType>
class ListNode {
 public:
  friend class LinearList<ListType>;
 private:
  ListType
   datum;
  ListNode<ListType>
   *next;
};

template <class ListType>
class LinearList {
 public:
  LinearList() {

    head = nullptr;
    count = 0;
  }

  ~LinearList() { clear(); }

  bool isEmpty() { return !count; }
  int size() { return count; }

  void clear() {
    ListNode<ListType>
      *tmp;

//    tmp = head;
    for (int i=0;i<count;i++) {
      tmp = head->next;
      delete head;
      head = tmp;
    }

    head = nullptr;

    count = 0;
  }

  //==

  int search(const ListType &key) {
    ListNode<ListType>
      *tmp = head;
    int i;

    for (i=0;i<count;i++,tmp=tmp->next)
      if (key == tmp->datum)
        return i;

      throw KeyNotFoundException();
  }

  ListType &operator[](int pos) {
    ListNode<ListType>
      *tmp = head;
    int i;

    if (pos < 0 || pos >= count)
      throw IllegalIndexException();

    for (i=0;i<pos;i++)
      tmp = tmp->next;

    return tmp->datum;
  }

  void traverse(void (*fp)(ListType &)) {
    ListNode<ListType>
      *tmp = head;
    int i;

    for (i=0;i<count;i++) {
      (*fp)(tmp->datum);
      tmp = tmp->next;
    }
  }

  void insert(int pos,const ListType &d) {
    ListNode<ListType>
      *tmp,*pred;

    if (pos < 0 || pos > count)
      throw IllegalIndexException();

    tmp = new ListNode<ListType>;
    tmp->datum = d;

    if (pos == 0) {
      tmp->next = head;
      head = tmp;
    } else {
      pred = head;
      for (int i=1;i<pos;i++)
        pred = pred->next;
      tmp->next = pred->next;
      pred->next = tmp;
    }

    count++;
  }

  void remove(int pos) {
    ListNode<ListType>
      *tmp,*pred;

    if (pos < 0 || pos >= count)
      throw IllegalIndexException();

    if (pos == 0) {
      tmp = head;
      head = tmp->next;
    } else {
      pred = head;
      for (int i=1;i<pos;i++)
        pred = pred->next;
      tmp = pred->next;
      pred->next = tmp->next;
    }

    delete tmp;

    count--;
  }

private:
  int count;
  ListNode<ListType> *head;
};

#endif
