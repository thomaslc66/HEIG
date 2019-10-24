/*
 * TimeCollection.cpp
 *
 *  Created on: 17 avr. 2016
 *      Author: Whiterussian
 */

#include "TimeCollection.h"

ostream& operator << (ostream& stream, const TimeCollection& timeCollection) {

	stream << "Total des temps pour trier un tableau de taille 10e" << timeCollection.POWER << endl;

	//Affichage du vector
	stream << "[";

	const size_t SIZE = timeCollection.collection.size();
	for(size_t i = 0; i < SIZE; i++) {
		stream << timeCollection.collection.at(i);

		if(i + 1 != SIZE) {
			stream << ", ";
		}
	}

	stream << "]" << endl;

	stream << "Moyenne : " << timeCollection.getAverageTime();

	return stream;
}

TimeCollection::TimeCollection(const size_t& size, const size_t& power) : POWER(power) {
	collection.reserve(size);
}

void TimeCollection::push_back(const int& time) {
	collection.push_back(time);
}

double TimeCollection::getAverageTime() const {
	double average = 0;

	for(int time : collection) {
		average = average + time;
	}//for

	return average / double(collection.size());
}
