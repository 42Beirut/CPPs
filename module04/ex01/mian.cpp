#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void) {
    std::cout << "=== Creating array of animals ===" << std::endl;
    const int arraySize = 6;
    Animal* animals[arraySize];
    
    // Half dogs, half cats
    for (int i = 0; i < arraySize / 2; i++) {
        animals[i] = new Dog();
    }
    for (int i = arraySize / 2; i < arraySize; i++) {
        animals[i] = new Cat();
    }
    
    std::cout << "\n=== Making sounds ===" << std::endl;
    for (int i = 0; i < arraySize; i++) {
        std::cout << animals[i]->getType() << ": ";
        animals[i]->makeSound();
    }
    
    std::cout << "\n=== Testing deep copy ===" << std::endl;
    Dog originalDog;
    originalDog.getBrain()->setIdea(0, "I love bones!");
    originalDog.getBrain()->setIdea(1, "Squirrels are fun to chase!");
    
    std::cout << "\nCreating copy of dog:" << std::endl;
    Dog copiedDog = originalDog;
    
    std::cout << "\nOriginal dog's ideas:" << std::endl;
    std::cout << "  Idea 0: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "  Idea 1: " << originalDog.getBrain()->getIdea(1) << std::endl;
    
    std::cout << "\nCopied dog's ideas:" << std::endl;
    std::cout << "  Idea 0: " << copiedDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "  Idea 1: " << copiedDog.getBrain()->getIdea(1) << std::endl;
    
    std::cout << "\nChanging original dog's first idea:" << std::endl;
    originalDog.getBrain()->setIdea(0, "I love treats even more!");
    
    std::cout << "Original dog idea 0: " << originalDog.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copied dog idea 0: " << copiedDog.getBrain()->getIdea(0) << std::endl;
    
    if (originalDog.getBrain() != copiedDog.getBrain()) {
        std::cout << "\n✓ Deep copy successful! Different Brain addresses." << std::endl;
    } else {
        std::cout << "\n✗ Shallow copy! Same Brain address." << std::endl;
    }
    
    std::cout << "\n=== Deleting animals ===" << std::endl;
    for (int i = 0; i < arraySize; i++) {
        delete animals[i];
    }
    
    std::cout << "\n=== Testing memory leaks ===" << std::endl;
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    delete j; // Should not create a leak
    delete i;
    
    return 0;
}