//
// Created by Whiterussian on 23.04.2017.
//

#ifndef POO2_LABO_03_NODE_H
#define POO2_LABO_03_NODE_H

#include <iosfwd>
#include <ostream>

template <typename T>
class Node;

template<typename T>
std::ostream& operator <<(std::ostream& stream, const Node<T>& node);

template <typename T>
class Node {
    friend std::ostream& operator << <T>(std::ostream& stream, const Node<T>& node);

public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& data);
    Node(const T& data, Node<T>* prev, Node<T>* next);
    Node<T>& operator++();
    Node<T> operator++(int);
    Node<T>& operator--();
    Node<T> operator--(int);
    bool operator==(const Node<T>& o) const;
    bool operator!=(const Node<T>& o) const;
    T& operator*();
};

#include "NodeImpl.h"

#endif //POO2_LABO_03_NODE_H
