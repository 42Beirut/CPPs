#include "ClapTrap.hpp"

int main(void) {
    std::cout << "=== Creating ClapTraps ===" << std::endl;
    ClapTrap clap1("CT-01");
    ClapTrap clap2("CT-02");
    
    std::cout << "\n=== Testing attacks ===" << std::endl;
    clap1.attack("Target-A");
    clap1.attack("Target-B");
    
    std::cout << "\n=== Testing damage ===" << std::endl;
    clap2.takeDamage(5);
    clap2.takeDamage(3);
    
    std::cout << "\n=== Testing repair ===" << std::endl;
    clap2.beRepaired(4);
    
    std::cout << "\n=== Testing energy depletion ===" << std::endl;
    for (int i = 0; i < 10; i++) {
        clap1.attack("Target-C");
    }
    
    std::cout << "\n=== Testing death ===" << std::endl;
    clap2.takeDamage(20);
    clap2.attack("Target-D");
    clap2.beRepaired(5);
    
    std::cout << "\n=== Destructors ===" << std::endl;
    return 0;
}