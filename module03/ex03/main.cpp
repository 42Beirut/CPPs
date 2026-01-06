#include "DiamondTrap.hpp"

int main(void) {
    std::cout << "=== Creating DiamondTrap ===" << std::endl;
    DiamondTrap diamond("DT-01");
    
    std::cout << "\n=== Testing whoAmI ===" << std::endl;
    diamond.whoAmI();
    
    std::cout << "\n=== Testing inherited methods ===" << std::endl;
    diamond.attack("Target-A");
    diamond.takeDamage(30);
    diamond.beRepaired(20);
    
    std::cout << "\n=== Testing special abilities ===" << std::endl;
    diamond.guardGate();
    diamond.highFivesGuys();
    
    std::cout << "\n=== Creating another DiamondTrap ===" << std::endl;
    DiamondTrap diamond2("DT-02");
    diamond2.whoAmI();
    
    std::cout << "\n=== Destructors ===" << std::endl;
    return 0;
}