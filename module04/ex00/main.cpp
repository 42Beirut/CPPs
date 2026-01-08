#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void) {
    std::cout << "=== Testing Correct Implementation ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    std::cout << "\nTypes:" << std::endl;
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    
    std::cout << "\nSounds:" << std::endl;
    i->makeSound(); // Cat sound!
    j->makeSound(); // Dog sound!
    meta->makeSound(); // Animal sound!
    
    std::cout << "\nDeleting animals:" << std::endl;
    delete meta;
    delete j;
    delete i;
    
    std::cout << "\n=== Testing Wrong Implementation ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();
    
    std::cout << "\nTypes:" << std::endl;
    std::cout << wrongCat->getType() << " " << std::endl;
    
    std::cout << "\nSounds:" << std::endl;
    wrongCat->makeSound(); // WrongAnimal sound (not WrongCat)!
    wrongMeta->makeSound();
    
    std::cout << "\nDeleting wrong animals:" << std::endl;
    delete wrongMeta;
    delete wrongCat;
    
    return 0;
}