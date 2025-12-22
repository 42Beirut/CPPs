#include "Zombie.hpp"

int main() {
    std::cout << "=== Testing newZombie (heap allocation) ===" << std::endl;
    Zombie* heapZombie = newZombie("HeapZombie");
    heapZombie->announce();
    delete heapZombie;
    
    std::cout << "\n=== Testing randomChump (stack allocation) ===" << std::endl;
    randomChump("StackZombie");
    
    std::cout << "\n=== Program ending ===" << std::endl;
    return 0;
}
