#include "Dog.hpp"

Dog::Dog(void) : brain(new Brain()) {
    std::cout << "Dog constructor called" << std::endl;
    this->type = "Dog";
}

Dog::Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain)) {
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }
    return *this;
}

Dog::~Dog(void) {
    std::cout << "Dog destructor called" << std::endl;
    delete this->brain;
}

void Dog::makeSound(void) const {
    std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain(void) const {
    return this->brain;
}