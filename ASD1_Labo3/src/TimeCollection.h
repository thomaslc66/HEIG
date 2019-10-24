/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : Quick_sort.h
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Declaration de la class TimeCollection permettant de gerer

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef TIMECOLLECTION_H_
#define TIMECOLLECTION_H_

#include <iostream>
#include <vector>

using namespace std;

class TimeCollection {

	friend ostream& operator << (ostream& stream, const TimeCollection& timeCollection);

private:
	vector<int> collection;
	const size_t POWER;

public:
	//Constructeur
	TimeCollection(const size_t& size, const size_t& power);


	/**
	 *  @fn void push_back(const int& time)
	 *
	 *  @brief Permet d'ajouter des temps a la collection
	 *
	 *  @author Antoine Russbach, Thomas Léchaire
	 *          et Michaël Brouchoud
	 *
	 *  @param[in] const int& time Le temps a ajouter
	 *
	 */
	void push_back(const int& time);


	/**
	 *  @fn void push_back(const int& time)
	 *
	 *  @brief Permet de calculer la moyenne des temps de la
	 *         collection
	 *
	 *  @author Antoine Russbach, Thomas Léchaire
	 *          et Michaël Brouchoud
	 *
	 *  @return double average La moyenne des temps
	 *
	 */
	double getAverageTime() const;
};

#endif /* TIMECOLLECTION_H_ */
