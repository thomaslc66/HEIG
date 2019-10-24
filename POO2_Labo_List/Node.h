//
// Created by Thomas on 06.04.2018.
//

#ifndef DLINKEDLIST_NODE_H
#define DLINKEDLIST_NODE_H

#include <iostream>

template<typename T>
class Node{

    /**
     * @fn friend std::ostream&operator << (std::ostream& stream, const Node<T>& node
     * @brief operator d'affichage de flux
     * @author Thomas Léchaire && Matthieu Girard
     * @param stream
     * @param node
     * @return le flux modifier pour l'affichage
     */
    friend std::ostream&operator << (std::ostream& stream, const Node<T>& node){
        stream << node.data;
        return stream;
    }


    Node<T> *_next;
    Node<T> *_prev;
    T data;

public:



    /**
     * @fn Node(const T& data);
     * @brief constructeur
     * @author Thomas Léchaire && Matthieu Girard
     * @param const T& data
     */
    Node(const T& data);

    /**
     *
     * @param data
     * @param prev
     * @param next
     */
    Node(const T& data, Node<T> * prev, Node<T> * next);

    /**
     *
     * @return
     */
    Node<T>& operator++();

    /**
     *
     * @return
     */
    Node<T>& operator--();


    Node<T>& operator = (const Node<T>* noeud);

    /**
     *
     * @return
     */
    T& operator* ();



    T& getData();

    Node<T>& refSurNext();
    Node<T>* ptrSurNext() ;

    Node<T>& refSurPrev();
    Node<T>* ptrSurPrev();


    void setNext(Node<T> *ptr);
    void setPrev(Node<T> *ptr);
};



#include "NodeImpl.h"

#endif //DLINKEDLIST_NODE_H

