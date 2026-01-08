#include "Cat.hpp"

Cat::Cat(void) : brain(new Brain()) {
    std::cout << "Cat constructor called" << std::endl;
    this->type = "Cat";
}

Cat::Cat(const Cat& other) : Animal(other), brain(new Brain(*other.brain)) {
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        delete this->brain;
        this->brain = new Brain(*other.brain);
    }
    return *this;
}

Cat::~Cat(void) {
    std::cout << "Cat destructor called" << std::endl;
    delete this->brain;
}

void Cat::makeSound(void) const {
    std::cout << "Meow! Meow!" << std::endl;
}

Brain* Cat::getBrain(void) const {
    return this->brain;
}