/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : Quick_sort.h
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Declaration de la fonction de tri quicksort et de ses differentes
               fonctions utiles a son bon fonctionnement

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_


// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la médiane
// entre le premier, le dernier et l'élément central.
// retourne un iterateur du même type que begin et end
// pointant sur la valeur choisie.
//
// NE RIEN MODIFIER DANS CETTE FONCTION

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin, const RandomAccessIterator end);


/**
 *  @fn RandomAccessIterator partition(RandomAccessIterator begin, RandomAccessIterator end)
 *
 *  @brief Partitionne le tableau de l’indice begin à l’indice
 *         end en utilisant *end comme pivot.
 *
 *  @author Antoine Russbach, Thomas Léchaire
 *          et Michaël Brouchoud
 *
 *  @param[in] RandomAccessIterator begin Le debut du tableau partitionne
 *  @param[in] RandomAccessIterator end La fin du tableau partitionne
 *
 *  @return RandomAccessIterator i Le pivot du tableau partitionne
 *
 */
template < typename RandomAccessIterator >
RandomAccessIterator partition(RandomAccessIterator begin, RandomAccessIterator end);


// quickSort
//
// Effectue le tri rapide des éléments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() après chaque
// partition
//
// A COMPLETER

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin, RandomAccessIterator end);

#include "Quick_sortImpl.h"

#endif /* QUICK_SORT_H_ */
