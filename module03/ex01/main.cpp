#include "ScavTrap.hpp"

int main(void) {
    std::cout << "=== Creating ClapTrap ===" << std::endl;
    ClapTrap clap("CT-01");
    
    std::cout << "\n=== Creating ScavTrap ===" << std::endl;
    ScavTrap scav("ST-01");
    
    std::cout << "\n=== Testing ClapTrap attack ===" << std::endl;
    clap.attack("Target-A");
    
    std::cout << "\n=== Testing ScavTrap attack ===" << std::endl;
    scav.attack("Target-B");
    
    std::cout << "\n=== Testing ScavTrap special ability ===" << std::endl;
    scav.guardGate();
    
    std::cout << "\n=== Testing ScavTrap damage and repair ===" << std::endl;
    scav.takeDamage(30);
    scav.beRepaired(20);
    
    std::cout << "\n=== Destructors (reverse order) ===" << std::endl;
    return 0;
}