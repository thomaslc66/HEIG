//
// Created by Thomas on 06.04.2018.
//

#ifndef DLINKEDLIST_LISTIMPL_H
#define DLINKEDLIST_LISTIMPL_H

#include "List.h"

/** ---------------------------- CLASSE CONSTITERATOR ----------------------------------------------*/

template<typename T>
std::ostream& operator << (std::ostream& stream, const List<T>& liste) {
    typename List<T>::ConstIterator it = liste.begin();
    typename List<T>::ConstIterator fin = liste.end();

    stream << "[";
    if(!liste.isEmpty()) {

        while(it != fin){
            stream << *it ;
            if (++it != liste.end()) {
                stream << ", ";
            }
        }
    }
    stream << "]";

    return stream;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(): ptr(nullptr) {}


template<typename T>
List<T>::ConstIterator::ConstIterator(List<T>::Node* p): ptr(p) {}

template<typename T>
bool List<T>::ConstIterator::operator==(const typename List<T>::ConstIterator &o) const {
    return ptr == o.ptr;
}

template<typename T>
bool List<T>::ConstIterator::operator!=(const typename List<T>::ConstIterator &o) const {
        return  !(*this == o); //appel l'operateur ==
};


template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int i) {
    typename List<T>::ConstIterator copie = *this;
    ptr = ptr->next;
    return copie;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() {
    ptr = ptr->prev;
    return *this;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int i) {
    auto copie = *this;
    ptr = ptr->prev;
    return copie;
}

template<typename T>
const T& List<T>::ConstIterator::operator*() {
    return ptr->data;
}

template<typename T>
const T* List<T>::ConstIterator::operator->() {
    return &ptr->data;
}



/** ---------------------------- CLASSE ITERATOR ----------------------------------------------*/

template<typename T>
T & List<T>::Iterator::operator*() {
    return this->ptr->data;
}

template <typename T>
const T& List<T>::Iterator::operator*() const{
    return this->ptr->data;
}

template<typename T>
T* List<T>::Iterator::operator->() {
    return this->ptr->data;
}

template<typename T>
const T* List<T>::Iterator::operator->() const {
    return this->ptr->data;
}

template<typename T>
typename List<T>::Iterator & List<T>::Iterator::operator++()  {  // increment,prefix
    ConstIterator::operator ++(); //this->ptr = this->ptr->next;
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int i)  {  // postfix incrementer
    auto copy = *this;
    ConstIterator::operator++(i); //this->ptr = this->ptr->next;
    return copy;
}

template<typename T>
typename List<T>::Iterator & List<T>::Iterator::operator--()  {  // prefix décrémenter
    ConstIterator::operator--(); //this->ptr = this->ptr->prev;
    return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int i)  {  // postfix décrémenter
    auto copy = *this;
    ConstIterator::operator--(i);  //this->ptr = this->ptr->prev;
    return *this;
}

template<typename T>
List<T>::Iterator::Iterator( typename List<T>::Node* p ) : List<T>::ConstIterator{p} {}

/** ---------------------------- CLASSE LIST ----------------------------------------------*/

//Constructeur
template<typename T>
List<T>::List() {
    iniListe();
}

template <typename T>
List<T>::~List(){
    deleteList();
    delete _begin;
    delete _end;
}

//Initialisation de la liste
template<typename T>
void List<T>::iniListe(){
    _end = new Node;
    _begin = new Node;
    _begin->next = _end;
    _end->prev = _begin;
    taille = 0;
}

//Effacement de la liste
template<typename T>
void List<T>::deleteList(){
    while(!isEmpty()){
        erase(--end());
    }
}

//Copie de la liste
template<typename T>
List<T>& List<T>::copyOfList(const List<T>& liste){
    iniListe();
    ConstIterator it = liste.begin();
    ConstIterator _end = liste.end();
    while(it != _end){
        append(*it++);
    }

    return *this;
}

//Constructeur de copie de la liste
template<typename T>
List<T>& List<T>::operator=(const List<T> &liste) {
    if(this != &liste){
        deleteList();
        copyOfList(liste);
    }

    return *this;
}

//Constructeur de copie
template<typename T>
List<T>::List(const List<T>& cpList): List() {
    if(this != & cpList)
        copyOfList(cpList);
}

template<typename T>
List<T>::List(std::initializer_list<T> liste): taille(liste.size()){
    newListFromInitializerList(liste);
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    typename List<T>::Iterator iter(_begin->next);
    return iter;
}

template<typename T>
typename List<T>::ConstIterator List<T>::begin() const{
    typename List<T>::ConstIterator const_iter(_begin->next);
    return const_iter;
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    typename List<T>::Iterator iter(_end);
    return iter;
}

template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
    typename List<T>::ConstIterator citer(_end);
    return citer;
}

template<typename T>
int List<T>::find(const T& o) {
    int found = -1;
    int index = 0;

    ConstIterator it = begin();
    while(it != end()){
        if(*it == o)
            return index;
        index++;
        it++;
    }

    return found;
}

template< typename T>
typename List<T>::ConstIterator List<T>::chercher(const T& o) const{
    ConstIterator it = begin();
    while(it != end()){
        if(*it == o)
            return it;
        it++;
    }
}

template<typename T>
typename List<T>::ConstIterator List<T>::chercher(const size_t index) const{
    if(index >= taille){
        throw std::out_of_range("Index is out of range");
    }

    ConstIterator curr = begin();
    for (size_t i = 0; i < index ; ++i) {
        ++curr;
    }
    return curr;
}

template<typename T>
void List<T>::remove(const T &o) {
    erase(chercher(o));
}

template<typename T>
void List<T>::removeAt(const size_t index) {
    erase(chercher(index));
}

template<typename T>
void List<T>::erase(typename List<T>::ConstIterator iter){
    List<T>::Node* p = iter.ptr;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    taille--;
}

template<typename T>
void List<T>::append(const T &o) {
    insert(end(),o);
 }

template<typename T>
void List<T>::insert(typename List<T>::Iterator it, const T &o) {
    List<T>::Node* pointer = it.ptr; //pointer courrant
    increaseSize();

    List<T>::Node * tmp = new Node;
    tmp->data =o;
    tmp->prev = pointer->prev;
    tmp->next = pointer;
    pointer->prev->next = tmp;
    pointer->prev = tmp;
}

template<typename T>
void List<T>::insert(const T &o) {
    insert(begin(), o);
}


template<typename T>
T& List<T>::operator[](const size_t index) {
    return chercher(index).ptr->data;
}

template<typename T>
T List<T>::operator[](const size_t index) const {
    return chercher(index).ptr->data;
}

template<typename T>
void List<T>::increaseSize() {
    taille++;
}

template<typename T>
size_t List<T>::size() const {
    return taille;
}

template<typename T>
bool List<T>::isEmpty() const{
    return taille == 0;
}

template<typename T>
void List<T>::newListFromInitializerList(const std::initializer_list<T> &liste) {
    iniListe();
    auto it = liste.begin();
    auto end = liste.end();

    while(it != end){
        append(*it++);
    }
}


#endif //DLINKEDLIST_LISTIMPL_H
