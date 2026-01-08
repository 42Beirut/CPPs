#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main(void) {
    std::cout << "=== Subject Tests ===" << std::endl;
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    
    ICharacter* me = new Character("me");
    
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    ICharacter* bob = new Character("bob");
    
    me->use(0, *bob);
    me->use(1, *bob);
    
    delete bob;
    delete me;
    delete src;
    
    std::cout << "\n=== Additional Tests ===" << std::endl;
    
    std::cout << "\n--- Testing inventory limits ---" << std::endl;
    Character* hero = new Character("Hero");
    AMateria* ice1 = new Ice();
    AMateria* ice2 = new Ice();
    AMateria* cure1 = new Cure();
    AMateria* cure2 = new Cure();
    AMateria* extra = new Ice();
    
    hero->equip(ice1);
    hero->equip(ice2);
    hero->equip(cure1);
    hero->equip(cure2);
    hero->equip(extra);  // Should fail silently (inventory full)
    
    std::cout << "\n--- Testing unequip ---" << std::endl;
    hero->unequip(1);  // Unequip slot 1
    hero->equip(extra);  // Should now succeed
    
    std::cout << "\n--- Testing deep copy ---" << std::endl;
    Character* copy = new Character(*hero);
    
    ICharacter* target = new Character("Target");
    std::cout << "Original using slot 0:" << std::endl;
    hero->use(0, *target);
    std::cout << "Copy using slot 0:" << std::endl;
    copy->use(0, *target);
    
    std::cout << "\n--- Cleanup ---" << std::endl;
    delete target;
    delete hero;
    delete copy;
    delete ice2;  // We unequipped this one, must delete manually
    
    return 0;
}