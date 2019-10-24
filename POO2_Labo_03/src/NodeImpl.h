//
// Created by Whiterussian on 23.04.2017.
//

#ifndef POO2_LABO_03_NODEIMPL_H
#define POO2_LABO_03_NODEIMPL_H

template<typename T>
std::ostream& operator <<(std::ostream& stream, const Node<T>& node) {
    stream << node.data;
    return stream;
}

template <typename T>
Node<T>::Node(const T& data) : Node(data, nullptr, nullptr) { }

template <typename T>
Node<T>::Node(const T& data, Node<T>* prev, Node<T>* next) : data(data), prev(prev), next(next) { }

template <typename T>
Node<T>& Node<T>::operator++() {
    return *next;
}

template <typename T>
Node<T> Node<T>::operator++(int) {
    return operator++();
}

template <typename T>
Node<T>& Node<T>::operator--() {
    return *prev;
}

template <typename T>
Node<T> Node<T>::operator--(int) {
    return operator--();
}

template <typename T>
bool Node<T>::operator==(const Node<T>& o) const {
    return this == &o;
}

template <typename T>
bool Node<T>::operator!=(const Node<T>& o) const {
    return !(*this == o);
}

template <typename T>
T& Node<T>::operator*() {
    return data;
}

#endif //POO2_LABO_03_NODEIMPL_H
