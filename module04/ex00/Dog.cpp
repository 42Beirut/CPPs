#include "Dog.hpp"

Dog::Dog(void) {
    std::cout << "Dog constructor called" << std::endl;
    this->type = "Dog";
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    *this = other;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Dog::~Dog(void) {
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const {
    std::cout << "Woof! Woof!" << std::endl;
}