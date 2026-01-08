#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void) {
    std::cout << "=== Testing abstract class ===" << std::endl;
    
    // This line should NOT compile:
    // Animal* animal = new Animal();  // ERROR: cannot instantiate abstract class
    
    std::cout << "Creating Dog and Cat (which are concrete classes):" << std::endl;
    Animal* dog = new Dog();
    Animal* cat = new Cat();
    
    std::cout << "\n=== Making sounds ===" << std::endl;
    dog->makeSound();
    cat->makeSound();
    
    std::cout << "\n=== Deleting animals ===" << std::endl;
    delete dog;
    delete cat;
    
    std::cout << "\n=== Testing with array ===" << std::endl;
    const int arraySize = 4;
    Animal* animals[arraySize];
    
    for (int i = 0; i < arraySize / 2; i++) {
        animals[i] = new Dog();
    }
    for (int i = arraySize / 2; i < arraySize; i++) {
        animals[i] = new Cat();
    }
    
    for (int i = 0; i < arraySize; i++) {
        animals[i]->makeSound();
        delete animals[i];
    }
    
    return 0;
}