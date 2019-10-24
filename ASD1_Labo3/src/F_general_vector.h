/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : F_general_vector.h
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Declaration de diverses fonctions utiles pour l'interaction avec un vector

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef F_GENERAL_VECTOR_H_
#define F_GENERAL_VECTOR_H_

#include <ctime>
#include <iostream>
#include <vector>

using namespace std;


/**
 *  @fn void fillVector(vector<int>& vectorToFill, size_t size, size_t max = 100)
 *
 *  @brief Remplit le vector de size nombres aleatoire entre 0 et max
 *
 *  @author Antoine Russbach, Thomas Léchaire
 *          et Michaël Brouchoud
 *
 *  @param[in] vector<int>& vectorToFill Le tableau a remplir
 *  @param[in] size_t size La taille du vector
 *  @param[in] size_t max Le nombre le plus grand aleatoire. Par defaut : 100
 *
 */
template <typename T>
void fillVector(vector<T>& vectorToFill, size_t size, size_t max = 100);


/**
 *  @fn void displayVector(vector<int>& vectorToDisplay);
 *
 *  @brief Affiche le vector vectorToDisplay
 *
 *  @author Antoine Russbach, Thomas Léchaire
 *          et Michaël Brouchoud
 *
 *  @param[in] vector<int>& vectorToDisplay Le tableau a afficher
 *
 */
template <typename T>
void displayVector(vector<T>& vectorToDisplay);

#include "F_general_vectorImpl.h"

#endif /* F_GENERAL_VECTOR_H_ */
