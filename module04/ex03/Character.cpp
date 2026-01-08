#include "Character.hpp"

Character::Character(void) : name("unnamed") {
    for (int i = 0; i < 4; i++) {
        this->inventory[i] = NULL;
    }
}

Character::Character(std::string const& name) : name(name) {
    for (int i = 0; i < 4; i++) {
        this->inventory[i] = NULL;
    }
}

Character::Character(const Character& other) : name(other.name) {
    for (int i = 0; i < 4; i++) {
        if (other.inventory[i]) {
            this->inventory[i] = other.inventory[i]->clone();
        } else {
            this->inventory[i] = NULL;
        }
    }
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        this->name = other.name;
        
        // Delete old inventory
        for (int i = 0; i < 4; i++) {
            if (this->inventory[i]) {
                delete this->inventory[i];
                this->inventory[i] = NULL;
            }
        }
        
        // Copy new inventory
        for (int i = 0; i < 4; i++) {
            if (other.inventory[i]) {
                this->inventory[i] = other.inventory[i]->clone();
            }
        }
    }
    return *this;
}

Character::~Character(void) {
    for (int i = 0; i < 4; i++) {
        if (this->inventory[i]) {
            delete this->inventory[i];
        }
    }
}

std::string const& Character::getName(void) const {
    return this->name;
}

void Character::equip(AMateria* m) {
    if (!m) {
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        if (!this->inventory[i]) {
            this->inventory[i] = m;
            return;
        }
    }
}

void Character::unequip(int idx) {
    if (idx < 0 || idx >= 4) {
        return;
    }
    
    // Just remove from inventory, don't delete
    this->inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx >= 4) {
        return;
    }
    
    if (this->inventory[idx]) {
        this->inventory[idx]->use(target);
    }
}