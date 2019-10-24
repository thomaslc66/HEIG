//
// Created by Thomas on 06.04.2018.
//
#ifndef DLINKEDLIST_LIST_H
#define DLINKEDLIST_LIST_H

#include <initializer_list>
#include <cstdlib>
#include <ostream>
#include <cassert>
#include "Nodes.h"

template <typename T>
class List;

template<typename T>
std::ostream& operator <<(std::ostream& stream, const List<T>& list);

template <typename T>
class List{

    /**
     * @brief Opérateur << de flux permet d'afficher la liste
     * @param stream
     * @param liste
     * @return
     */
    friend std::ostream& operator<< <T>(std::ostream& stream, const List& liste);

private:

    /**
     * @class Node
     * @brief représente un noeud de la double liste chainée
     */
    class Node {
    public:
        Node():next(nullptr), prev(nullptr){}
        ~Node() {}
    public :
        T data;
        Node* next;
        Node* prev;
    };

public:

    /**
     * @class ConstIterator
     * @brief représente un itérateur constant
     */
    class ConstIterator{

    protected:
        friend class List<T>;
        Node* ptr;
        ConstIterator(typename List<T>::Node* p);

    public:
        ConstIterator();

        /**
         * @brief Oprateur == teste l'égalité entre 2 ConstIterator
         * @param o
         * @return bool vrai ou faux selon le résultat du test
         */
        bool operator ==(const ConstIterator& o) const;

        /**
         * @brief Operateur != teste l'inégalité entre 2 ConstIterator
         * @param o
         * @return bool vrai ou faux selon le résultat du test
         */
        bool operator !=(const ConstIterator& o) const;

        /**
         * @biref Operateur ++
         * @param o
         * @return
         */
        ConstIterator& operator ++ ();

        /**
         *
         * @param o
         * @param i
         * @return
         */
        ConstIterator operator ++ (int i);

        /**
         *
         * @param o
         * @return
         */
        ConstIterator& operator -- ();

        /**
         *
         * @param o
         * @param i
         * @return
         */
        ConstIterator operator -- (int i);

        /* pas besoin de retourner une référence car c'est une itérateur const et il ne peut pas modifier la valeur*/
        const T& operator*();

        /* retourne la référence sur le data du noeud*/
        const T* operator->();
    };


    /**
     * @class Iterator
     */
    class Iterator: public ConstIterator{

    protected:
        friend class List<T>;
        Iterator(Node* p);

    public:

        /**
         *
         * @param o
         * @return
         */
        Iterator& operator ++ ();

        /**
         *
         * @param o
         * @param i
         * @return
         */
        Iterator operator ++ (int i);

        /**
         *
         * @param o
         * @return
         */
        Iterator& operator -- ();

        /**
         *
         * @param o
         * @param i
         * @return
         */
        Iterator operator -- (int i);

        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;

    };

private:

    Node*   _begin;
    Node*   _end;
    size_t  taille;

public:


    /**
     *
     */
    List();

    /**
     *
     */
    ~List();

    /**
     *
     * @param liste
     */
    List(const List& liste);

    List(std::initializer_list<T> liste);

    /**
     *
     * @param liste
     * @return
     */
    List& operator = (const List& liste);

    /**
     *
     * @param index
     * @return
     */
    T& operator [](const size_t index);

    /**
     *
     * @param index
     * @return
     */
    T operator [](const size_t index) const;

    /**
     *
     * @return
     */
    size_t size() const;

    /**
     *
     * @param o
     */
    void insert(const T& o);

    /**
     *
     * @param o
     */
    void append(const T& o);

    /**
     *
     * @param index
     */
    void removeAt(const size_t index);

    /**
     *
     * @param o
     */
    void remove(const T& o);

    /**
     *
     * @param iter
     */
    void erase(ConstIterator iter);

    /**
     *
     * @return
     */
    Iterator begin();
    ConstIterator begin() const;
    /**
     *
     * @return
     */
     Iterator end();
     ConstIterator end() const;
    /**
     *
     * @param o
     * @return
     */
    int find(const T& o);
    /**
     *
     * @return
     */
    bool isEmpty() const;

private:


    /**
     *
     */
    void iniListe();
    void newListFromInitializerList(const std::initializer_list<T>& liste);
    ConstIterator chercher(const size_t index) const;
    ConstIterator chercher(const T &o) const;
    void insert(Iterator it, const T &o);
    void deleteList();
    void increaseSize();
    List<T>& copyOfList(const List<T> &liste);

};

#include "ListImpl.hpp"

#endif //DLINKEDLIST_LIST_H
