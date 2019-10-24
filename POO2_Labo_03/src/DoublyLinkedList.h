//
// Created by Whiterussian on 23.04.2017.
//

#ifndef POO2_LABO_03_LIST_H
#define POO2_LABO_03_LIST_H

#include "Iterator.h"
#include "Node.h"

template <typename T>
class DoublyLinkedList {
public:
    typedef Iterator< Node<T> > Iterator;

private:
    Node<T>* _begin;
    Node<T>* _end;

    unsigned short _size;

    void iniList();
    void copyList(const DoublyLinkedList<T>& list);
    void deleteList();
    void remove(const Node<T>* node);

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& o);
    ~DoublyLinkedList();
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& o);
    T& operator[](const unsigned short index);
    const short int size() const;
    void insert(const T& o);
    void append(const T& o);
    void remove(const unsigned short index);
    void remove(const T& o);
    Iterator begin()const;
    Iterator end() const;
    Iterator find(const unsigned short index);
    Iterator find(const T& o);
    bool isEmpty() const;
};

#include "DoublyLinkedListImpl.h"

#endif //POO2_LABO_03_LIST_H
