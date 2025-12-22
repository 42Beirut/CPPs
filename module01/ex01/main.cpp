#include "Zombie.hpp"

int main() {
    int hordeSize = 5;
    std::string zombieName = "HordeZombie";
    
    std::cout << "=== Creating a horde of " << hordeSize << " zombies ===" << std::endl;
    Zombie* horde = zombieHorde(hordeSize, zombieName);
    
    if (horde == NULL) {
        std::cout << "Failed to create zombie horde!" << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Making them announce ===" << std::endl;
    for (int i = 0; i < hordeSize; i++) {
        std::cout << "Zombie " << i << ": ";
        horde[i].announce();
    }
    
    std::cout << "\n=== Destroying the horde ===" << std::endl;
    delete[] horde;
    
    return 0;
}
