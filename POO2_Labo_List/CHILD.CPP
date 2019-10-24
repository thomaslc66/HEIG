//
// Created by Whiterussian on 30.04.2017.
//

#include "Child.h"

Child::Child(const std::string& firstname, const std::string& lastname) : Person(firstname, lastname) {}

void Child::description() const {
    std::cout << "Ce message provient de la class Child";
}
