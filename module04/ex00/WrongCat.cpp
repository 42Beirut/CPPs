#include "WrongCat.hpp"

WrongCat::WrongCat(void) {
    std::cout << "WrongCat constructor called" << std::endl;
    this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
    std::cout << "WrongCat copy constructor called" << std::endl;
    *this = other;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
    std::cout << "WrongCat copy assignment operator called" << std::endl;
    if (this != &other) {
        WrongAnimal::operator=(other);
    }
    return *this;
}

WrongCat::~WrongCat(void) {
    std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound(void) const {
    std::cout << "Wrong Meow! Wrong Meow!" << std::endl;
}