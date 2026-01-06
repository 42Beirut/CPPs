#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void) {
    std::cout << "=== Creating ClapTrap ===" << std::endl;
    ClapTrap clap("CT-01");
    
    std::cout << "\n=== Creating ScavTrap ===" << std::endl;
    ScavTrap scav("ST-01");
    
    std::cout << "\n=== Creating FragTrap ===" << std::endl;
    FragTrap frag("FT-01");
    
    std::cout << "\n=== Testing attacks ===" << std::endl;
    clap.attack("Target-A");
    scav.attack("Target-B");
    frag.attack("Target-C");
    
    std::cout << "\n=== Testing special abilities ===" << std::endl;
    scav.guardGate();
    frag.highFivesGuys();
    
    std::cout << "\n=== Testing FragTrap combat ===" << std::endl;
    frag.takeDamage(50);
    frag.beRepaired(30);
    frag.attack("Target-D");
    
    std::cout << "\n=== Destructors (reverse order) ===" << std::endl;
    return 0;
}