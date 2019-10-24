//
// Created by Whiterussian on 30.04.2017.
//

#ifndef POO2_LABO_03_CHILD_H
#define POO2_LABO_03_CHILD_H

#include "Person.h"

/*
 * @class Child : Person
 */
class Child : public Person {
public:

    /*
     * @fn Child(const std::string& firstname, const std::string& lastname)
     *
     * @brief Constructeur a partir d'un firstname et d'un lastname
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     * @param std::string& firstname Le firstname
     * @param std::string& lastname Le lastname
     *
     */
    Child(const std::string& firstname, const std::string& lastname);

    /*
     * @fn void description() const
     *
     * @brief Permet d'afficher une description de la Child
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     */
    void description() const;
};


#endif //POO2_LABO_03_CHILD_H
