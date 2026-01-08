# C++ Module 04 - Subtype Polymorphism, Abstract Classes, and Interfaces

*This project has been created as part of the 42 curriculum by afahs.*

## Description

C++ Module 04 introduces **Polymorphism**, the third pillar of Object-Oriented Programming (after Encapsulation and Inheritance). This module teaches how objects of different types can be treated uniformly through a common interface, enabling flexible and extensible code design. Students learn virtual functions, abstract classes, interfaces, and proper resource management in polymorphic hierarchies.

The project consists of four exercises:
- **Exercise 00**: Virtual functions and polymorphism basics
- **Exercise 01**: Deep copy with polymorphic objects and dynamic memory
- **Exercise 02**: Abstract classes that cannot be instantiated
- **Exercise 03**: Interface design pattern and complex object relationships

### What is Polymorphism?

**Polymorphism** means "many forms" - the ability to treat objects of different types through a common interface:

```cpp
Animal* pet = new Dog();  // Dog is-an Animal
pet->makeSound();         // Calls Dog::makeSound() (not Animal::makeSound())
```

**Key benefit**: Write code once that works with any derived type:
```cpp
void feedAnimal(Animal* animal) {
    animal->makeSound();  // Works for Dog, Cat, or any future Animal type!
}
```

### Learning Objectives

- Understand virtual functions and dynamic dispatch
- Implement and use abstract classes (pure virtual functions)
- Design interfaces in C++98
- Master deep copy with polymorphic objects
- Manage memory correctly with virtual destructors
- Apply SOLID principles (especially Interface Segregation)

## Instructions

### Compilation

Each exercise directory contains a Makefile:

```bash
cd ex00/  # or ex01/, ex02/, ex03/
make
./executable_name
```

All projects compile with:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

### Running the Exercises

**Exercise 00: Polymorphism**
```bash
cd ex00/ && make && ./polymorphism
```
Demonstrates virtual functions vs non-virtual functions.

**Exercise 01: Deep Copy**
```bash
cd ex01/ && make && ./brain
```
Animals with brains - proper deep copying and memory management.

**Exercise 02: Abstract Class**
```bash
cd ex02/ && make && ./abstract
```
Makes Animal abstract - cannot be instantiated directly.

**Exercise 03: Interfaces**
```bash
cd ex03/ && make && ./interface
```
Complete materia system with interfaces and complex relationships.

## Project Structure

```
cpp04/
├── ex00/  # Virtual functions and polymorphism
│   ├── Animal.{hpp,cpp}
│   ├── Dog.{hpp,cpp}
│   ├── Cat.{hpp,cpp}
│   ├── WrongAnimal.{hpp,cpp}
│   └── WrongCat.{hpp,cpp}
├── ex01/  # Deep copy with Brain
│   ├── Brain.{hpp,cpp}
│   ├── Animal.{hpp,cpp}
│   ├── Dog.{hpp,cpp}
│   └── Cat.{hpp,cpp}
├── ex02/  # Abstract Animal class
│   └── (Same as ex01 with pure virtual makeSound)
└── ex03/  # Materia interface system
    ├── AMateria.{hpp,cpp}
    ├── ICharacter.hpp
    ├── Character.{hpp,cpp}
    ├── IMateriaSource.hpp
    ├── MateriaSource.{hpp,cpp}
    ├── Ice.{hpp,cpp}
    └── Cure.{hpp,cpp}
```

## Core Concepts Explained

### Exercise 00: Virtual Functions & Polymorphism

#### The Problem Without Virtual

```cpp
class Animal {
public:
    void makeSound() { cout << "Generic sound"; }
};

class Dog : public Animal {
public:
    void makeSound() { cout << "Woof!"; }
};

Animal* pet = new Dog();
pet->makeSound();  // Prints "Generic sound" - WRONG!
```

**Why?** Compiler uses **static binding** - decides which function to call at compile time based on pointer type (Animal*), not actual object type (Dog).

#### The Solution: Virtual Functions

```cpp
class Animal {
public:
    virtual void makeSound() { cout << "Generic sound"; }
    virtual ~Animal() {}  // CRITICAL!
};

class Dog : public Animal {
public:
    void makeSound() { cout << "Woof!"; }  // Override
};

Animal* pet = new Dog();
pet->makeSound();  // Prints "Woof!" - CORRECT!
delete pet;        // Calls Dog destructor, then Animal destructor
```

**How it works:**
1. `virtual` enables **dynamic dispatch** (runtime polymorphism)
2. Compiler creates **vtable** (virtual table) with function pointers
3. At runtime, looks up actual object type and calls correct function

#### Why Virtual Destructor is Critical

```cpp
// WITHOUT virtual destructor
class Animal {
    ~Animal() {}  // NOT virtual
};

class Dog : public Animal {
    Brain* brain;
    ~Dog() { delete brain; }  // Never called!
};

Animal* pet = new Dog();
delete pet;  // Only calls Animal destructor - MEMORY LEAK!
```

```cpp
// WITH virtual destructor
class Animal {
    virtual ~Animal() {}  // Virtual
};

delete pet;  // Calls Dog destructor, THEN Animal destructor - CORRECT!
```

**Rule**: If a class has any virtual functions, it MUST have a virtual destructor.

#### WrongAnimal - Demonstrating Broken Polymorphism

```cpp
class WrongAnimal {
public:
    void makeSound() { /* ... */ }  // NOT virtual
};

class WrongCat : public WrongAnimal {
public:
    void makeSound() { /* ... */ }
};

WrongAnimal* cat = new WrongCat();
cat->makeSound();  // Calls WrongAnimal::makeSound - WRONG!
```

This demonstrates that without `virtual`, polymorphism doesn't work.

---

### Exercise 01: Deep Copy with Polymorphism

#### The Brain Class

```cpp
class Brain {
private:
    std::string ideas[100];
public:
    // Orthodox Canonical Form
};
```

Simple class with 100 string ideas. Dogs and Cats will have their own Brain.

#### The Problem: Shallow Copy

```cpp
class Dog {
private:
    Brain* brain;
public:
    Dog() : brain(new Brain()) {}
    ~Dog() { delete brain; }
    // Default copy constructor does shallow copy!
};

Dog dog1;
Dog dog2 = dog1;  // dog1.brain == dog2.brain (SAME ADDRESS!)
// When dog1 destroyed, deletes brain
// When dog2 destroyed, tries to delete ALREADY DELETED brain - CRASH!
```

#### The Solution: Deep Copy

```cpp
class Dog {
private:
    Brain* brain;
    
public:
    Dog() : brain(new Brain()) {}
    
    // Deep copy constructor
    Dog(const Dog& other) : Animal(other), brain(new Brain(*other.brain)) {
        // Creates NEW brain, copies content
    }
    
    // Deep copy assignment
    Dog& operator=(const Dog& other) {
        if (this != &other) {
            Animal::operator=(other);
            delete this->brain;                    // Delete old
            this->brain = new Brain(*other.brain); // Create new copy
        }
        return *this;
    }
    
    ~Dog() { delete brain; }
};
```

**Testing Deep Copy:**
```cpp
Dog original;
original.getBrain()->setIdea(0, "I love bones!");

Dog copy = original;
copy.getBrain()->setIdea(0, "I love treats!");

// original's idea should still be "I love bones!"
// If it changed, you have shallow copy (BUG!)
```

#### Array of Animals

```cpp
Animal* animals[6];

// Fill with dogs and cats
for (int i = 0; i < 3; i++)
    animals[i] = new Dog();
for (int i = 3; i < 6; i++)
    animals[i] = new Cat();

// Delete through base pointer
for (int i = 0; i < 6; i++)
    delete animals[i];  // Calls Dog/Cat destructor (if virtual!)
```

**Critical**: Without virtual destructor in Animal, this leaks Brain memory!

---

### Exercise 02: Abstract Classes

#### Making Animal Abstract

```cpp
class Animal {
public:
    virtual void makeSound() const = 0;  // Pure virtual function
    virtual ~Animal() {}
};
```

**Pure virtual function**: `= 0` means:
- No implementation in base class
- Derived classes MUST implement it
- Class becomes **abstract** - cannot instantiate

```cpp
Animal* animal = new Animal();  // ERROR: cannot instantiate abstract class
Animal* dog = new Dog();        // OK: Dog implements makeSound()
```

**Why make Animal abstract?**
- Animals without a specific type don't make sense
- Forces developers to create specific animal types
- Prevents bugs from using generic Animal objects

**When to use abstract classes:**
- Base class doesn't have meaningful implementation
- Want to force derived classes to implement certain methods
- Designing a framework or interface

---

### Exercise 03: Interface & Recap (Step-by-Step)

This exercise is the most complex. Let's break it down completely.

#### Step 1: Understanding the Design

We're building a **Materia system** (like magic items):

```
IMateriaSource          ICharacter
    ↑                      ↑
    |                      |
MateriaSource          Character
    |                      |
    +-- learns --------> AMateria ←---- equips
                           ↑
                           |
                    +------+------+
                    |             |
                   Ice          Cure
```

**Relationships:**
- MateriaSource learns materia types (templates)
- Character equips materias (inventory)
- Materias can be used on Characters

#### Step 2: Interfaces in C++98

C++98 doesn't have `interface` keyword. We simulate with **pure abstract classes**:

```cpp
class ICharacter {
public:
    virtual ~ICharacter() {}  // Virtual destructor
    virtual std::string const& getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};
```

**Interface characteristics:**
- All methods are pure virtual (`= 0`)
- No data members (only pure behavior)
- Virtual destructor (even if empty)
- Acts as a contract: "Any class implementing ICharacter must have these methods"

#### Step 3: AMateria (Abstract Base Class)

```cpp
class AMateria {
protected:
    std::string type;

public:
    AMateria(std::string const& type);
    virtual ~AMateria();
    
    std::string const& getType() const;
    virtual AMateria* clone() const = 0;  // Pure virtual
    virtual void use(ICharacter& target);
};
```

**Key points:**
- `clone()` is pure virtual - each concrete materia must implement
- `use()` has default implementation (can be overridden)
- `type` is protected - derived classes can access

**Why clone()?**
- Creates a copy of the materia
- Returns pointer to new object
- Called "prototype pattern"
- Allows copying without knowing exact type

#### Step 4: Concrete Materias (Ice & Cure)

```cpp
class Ice : public AMateria {
public:
    Ice() : AMateria("ice") {}  // Set type to "ice"
    
    AMateria* clone() const {
        return new Ice(*this);  // Return copy of self
    }
    
    void use(ICharacter& target) {
        std::cout << "* shoots an ice bolt at " 
                  << target.getName() << " *" << std::endl;
    }
};
```

**clone() implementation:**
```cpp
Ice original;
AMateria* copy = original.clone();  // Returns new Ice object
delete copy;  // Caller must manage memory
```

**Why return new object?**
- Allows copying through base class pointer
- Caller gets ownership (must delete)
- Works even if we don't know exact type

#### Step 5: Character Implementation

```cpp
class Character : public ICharacter {
private:
    std::string name;
    AMateria* inventory[4];  // 4 slots

public:
    Character(std::string const& name) : name(name) {
        for (int i = 0; i < 4; i++)
            inventory[i] = NULL;
    }
    
    ~Character() {
        for (int i = 0; i < 4; i++)
            if (inventory[i])
                delete inventory[i];
    }
};
```

**equip() - Adding to inventory:**
```cpp
void Character::equip(AMateria* m) {
    if (!m) return;  // Null check
    
    // Find first empty slot
    for (int i = 0; i < 4; i++) {
        if (!inventory[i]) {
            inventory[i] = m;  // Store pointer
            return;
        }
    }
    // Inventory full - do nothing (don't delete m!)
}
```

**Important**: equip() takes ownership but doesn't delete if full!

**unequip() - Removing from inventory:**
```cpp
void Character::unequip(int idx) {
    if (idx < 0 || idx >= 4) return;
    
    // Remove from inventory WITHOUT deleting
    inventory[idx] = NULL;
}
```

**Critical**: unequip() does NOT delete! Caller must save the pointer:

```cpp
AMateria* saved = character->getInventory(0);  // Save pointer
character->unequip(0);                          // Remove from inventory
// ... do something with saved ...
delete saved;  // Caller deletes
```

**use() - Using a materia:**
```cpp
void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx >= 4) return;
    
    if (inventory[idx])
        inventory[idx]->use(target);  // Polymorphic call!
}
```

**Deep Copy Constructor:**
```cpp
Character::Character(const Character& other) : name(other.name) {
    for (int i = 0; i < 4; i++) {
        if (other.inventory[i])
            inventory[i] = other.inventory[i]->clone();  // Clone each!
        else
            inventory[i] = NULL;
    }
}
```

**Deep Copy Assignment:**
```cpp
Character& Character::operator=(const Character& other) {
    if (this != &other) {
        name = other.name;
        
        // Delete old inventory
        for (int i = 0; i < 4; i++) {
            if (inventory[i]) {
                delete inventory[i];
                inventory[i] = NULL;
            }
        }
        
        // Clone new inventory
        for (int i = 0; i < 4; i++) {
            if (other.inventory[i])
                inventory[i] = other.inventory[i]->clone();
        }
    }
    return *this;
}
```

**Why clone() instead of copy?**
- Inventory holds `AMateria*` (base class pointers)
- Could point to Ice, Cure, or future materia types
- `clone()` creates correct type without knowing what it is
- This is **polymorphic copying**!

#### Step 6: MateriaSource Implementation

```cpp
class MateriaSource : public IMateriaSource {
private:
    AMateria* templates[4];  // Learned materia templates

public:
    MateriaSource() {
        for (int i = 0; i < 4; i++)
            templates[i] = NULL;
    }
    
    ~MateriaSource() {
        for (int i = 0; i < 4; i++)
            if (templates[i])
                delete templates[i];
    }
};
```

**learnMateria() - Learning a new type:**
```cpp
void MateriaSource::learnMateria(AMateria* m) {
    if (!m) return;
    
    // Find empty slot
    for (int i = 0; i < 4; i++) {
        if (!templates[i]) {
            templates[i] = m->clone();  // Clone and store
            return;
        }
    }
}
```

**Important**: learnMateria() clones! Original can be deleted:

```cpp
IMateriaSource* src = new MateriaSource();
Ice* ice = new Ice();
src->learnMateria(ice);  // Clones ice
delete ice;              // Can delete original safely
```

**createMateria() - Creating from template:**
```cpp
AMateria* MateriaSource::createMateria(std::string const& type) {
    for (int i = 0; i < 4; i++) {
        if (templates[i] && templates[i]->getType() == type)
            return templates[i]->clone();  // Return new copy
    }
    return NULL;  // Unknown type
}
```

**Usage flow:**
```cpp
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());    // Learn "ice" type
src->learnMateria(new Cure());   // Learn "cure" type

AMateria* ice = src->createMateria("ice");   // Creates new Ice
AMateria* cure = src->createMateria("cure"); // Creates new Cure

character->equip(ice);   // Give to character
character->equip(cure);

delete src;  // Deletes templates, not ice/cure (character owns them)
delete character;  // Deletes ice and cure
```

#### Step 7: Memory Management Rules

**Who owns what?**

| Object | Owner | When deleted |
|--------|-------|--------------|
| Materia created by createMateria() | Caller | Caller must delete |
| Materia equipped to Character | Character | Character destructor |
| Materia unequipped | Caller | Caller must save pointer and delete |
| Materia template in MateriaSource | MateriaSource | MateriaSource destructor |

**Memory leak scenarios:**

```cpp
// BAD: Memory leak
AMateria* ice = src->createMateria("ice");
character->equip(ice);
// If equip fails (full), ice is leaked!

// GOOD: Check result
if (!character->equip(ice))
    delete ice;  // Delete if not equipped

// OR BETTER: Character always takes ownership
// Design equip() to delete if full
```

```cpp
// BAD: Double delete
character->unequip(0);
delete character;  // Character doesn't own it anymore!

// GOOD: Save before unequip
AMateria* saved = character->getInventory(0);
character->unequip(0);
delete saved;  // Manual cleanup
```

#### Step 8: Complete Usage Example

```cpp
int main() {
    // Create source and learn materias
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());   // Source clones and stores
    src->learnMateria(new Cure());
    
    // Create character
    ICharacter* me = new Character("me");
    
    // Create and equip materias
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    
    // Create target
    ICharacter* bob = new Character("bob");
    
    // Use materias on target
    me->use(0, *bob);  // "* shoots an ice bolt at bob *"
    me->use(1, *bob);  // "* heals bob's wounds *"
    
    // Cleanup
    delete bob;
    delete me;   // Deletes equipped materias
    delete src;  // Deletes templates
    
    return 0;
}
```

## Key Design Patterns

### 1. Interface Segregation Principle

Instead of one big interface:
```cpp
class IEverything {
    virtual void learn() = 0;
    virtual void equip() = 0;
    virtual void use() = 0;
    // Too many responsibilities!
};
```

Use separate interfaces:
```cpp
class IMateriaSource {
    virtual void learnMateria() = 0;
    virtual AMateria* createMateria() = 0;
};

class ICharacter {
    virtual void equip() = 0;
    virtual void use() = 0;
};
```

### 2. Prototype Pattern (clone())

Creates copies without knowing exact type:

```cpp
AMateria* original = /* could be Ice or Cure */;
AMateria* copy = original->clone();  // Correct type created!
```

### 3. Factory Pattern (MateriaSource)

Creates objects based on string identifier:

```cpp
AMateria* materia = source->createMateria("ice");  // Creates Ice
```

### 4. Polymorphic Copy

Deep copying through base class pointers:

```cpp
AMateria* inventory[4];  // Could hold Ice, Cure, etc.
// Copy each correctly:
for (int i = 0; i < 4; i++)
    if (inventory[i])
        newInventory[i] = inventory[i]->clone();  // Polymorphic copy!
```

## Common Pitfalls

| Problem | Cause | Solution |
|---------|-------|----------|
| Memory leak when deleting Animal* | Non-virtual destructor | Always make destructor virtual |
| Shallow copy of Brain* | Default copy constructor | Implement deep copy constructor/assignment |
| Double delete after unequip | Deleting pointer still in inventory | unequip() sets to NULL |
| Leak from full inventory | equip() doesn't delete when full | Caller checks or equip() deletes |
| Wrong makeSound() called | Non-virtual function | Mark function as virtual |
| Can create Animal objects | Not abstract | Add pure virtual function (`= 0`) |

## Testing Strategies

### Test Virtual Functions
```cpp
Animal* animal = new Dog();
animal->makeSound();  // Should print Dog sound, not Animal sound
```

### Test Virtual Destructor
```cpp
Animal* animal = new Dog();  // Dog has Brain*
delete animal;               // Must call Dog destructor to delete Brain
// Check with valgrind: no leaks?
```

### Test Deep Copy
```cpp
Dog dog1;
dog1.getBrain()->setIdea(0, "Original idea");
Dog dog2 = dog1;
dog2.getBrain()->setIdea(0, "Modified idea");
// dog1's idea should still be "Original idea"
// If it changed, shallow copy bug!
```

### Test Abstract Class
```cpp
// This should NOT compile:
Animal* animal = new Animal();

// This should compile:
Animal* dog = new Dog();
```

### Test Memory Management
```bash
valgrind --leak-check=full ./executable
# Should show: All heap blocks were freed -- no leaks are possible
```

## Resources

### Official Documentation
- [C++ Reference - Virtual Functions](https://en.cppreference.com/w/cpp/language/virtual)
- [C++ Reference - Abstract Classes](https://en.cppreference.com/w/cpp/language/abstract_class)
- [Polymorphism in C++](https://www.geeksforgeeks.org/polymorphism-in-c/)

### Polymorphism
- [Virtual Functions Explained](https://www.learncpp.com/cpp-tutorial/virtual-functions/)
- [How Virtual Functions Work (vtables)](https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/)
- [Virtual Destructors](https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors)

### Design Patterns
- [Prototype Pattern](https://refactoring.guru/design-patterns/prototype)
- [Factory Pattern](https://refactoring.guru/design-patterns/factory-method)
- [Interface Segregation Principle](https://stackify.com/interface-segregation-principle/)

### Memory Management
- [Deep Copy vs Shallow Copy](https://www.geeksforgeeks.org/shallow-copy-and-deep-copy-in-c/)
- [Smart Pointers (C++11+)](https://en.cppreference.com/w/cpp/memory) - Preview for future
- [RAII Pattern](https://en.cppreference.com/w/cpp/language/raii)

### Video Tutorials
- [The Cherno - Virtual Functions](https://www.youtube.com/watch?v=oIV2KchSyGQ)
- [The Cherno - Interfaces (Pure Virtual)](https://www.youtube.com/watch?v=UWAdd13EfM8)

### Books
- "Effective C++" by Scott Meyers - Items on virtual functions
- "Design Patterns" by Gang of Four - Prototype and Factory patterns

## AI Usage Disclosure

### AI Tools Used
Claude (Anthropic) was used as an educational learning aid throughout this module.

### How AI Was Used

**Conceptual Learning:**
- Understanding virtual functions and vtables
- Learning difference between virtual and pure virtual
- Understanding when virtual destructors are critical
- Clarifying interface design in C++98
- Learning the prototype pattern (clone method)

**Problem Solving:**
- Understanding why WrongAnimal doesn't work
- Debugging memory leaks with polymorphic deletion
- Implementing deep copy with polymorphic objects
- Understanding clone() pattern for polymorphic copying
- Clarifying ownership rules in Exercise 03

**Exercise 03 Specific:**
- Understanding the materia system architecture
- Learning when to clone vs when to take ownership
- Understanding why unequip() doesn't delete
- Implementing deep copy with polymorphic arrays
- Managing complex object relationships

### What I Implemented Independently

- All class designs and implementations
- Memory management strategies
- Deep copy logic for all classes
- Test cases covering edge cases
- Design decisions about ownership
- All materia use() messages
- Character inventory management logic

### Learning Approach

**Questions I Asked AI:**
- "Why do we need a virtual destructor?"
- "How does virtual function dispatch work?"
- "What's the difference between abstract class and interface?"
- "Why does clone() return a pointer instead of object?"
- "When should Character own the materia vs caller?"

**Questions I Didn't Ask:**
- "Write the Character class for me"
- "Implement Exercise 03"
- "Give me the complete solution"

**My Process:**
1. Read subject and understand requirements
2. Draw class diagrams and relationships
3. Ask AI about specific concepts I don't understand
4. Implement solutions myself
5. Test with valgrind for memory leaks
6. Use AI to understand why leaks occur
7. Fix and re-test
8. Discuss with peers to confirm understanding

### Verification of Understanding

I can:
- ✓ Explain how virtual functions work (vtable)
- ✓ Explain why virtual destructors are necessary
- ✓ Implement deep copy with polymorphic objects
- ✓ Design interfaces in C++98
- ✓ Explain ownership and memory management rules
- ✓ Debug memory leaks independently
- ✓ Reproduce solutions without AI
- ✓ Explain design patterns used (Prototype, Factory)

### Honest Assessment

**AI helped me:**
- Understand vtables and dynamic dispatch quickly
- Learn the clone() pattern
- Debug complex memory management issues
- Understand SOLID principles
- See real-world applications of polymorphism

**But I still:**
- Wrote every line myself
- Tested exhaustively with valgrind
- Understood every design decision
- Can explain in evaluation
- Ready for more advanced OOP concepts

## Evaluation Guidelines

### Exercise 00
- ✓ Animal has virtual destructor and virtual makeSound()
- ✓ Dog and Cat override makeSound()
- ✓ Polymorphism works (correct sound through base pointer)
- ✓ WrongAnimal/WrongCat show broken polymorphism
- ✓ Orthodox Canonical Form

### Exercise 01
- ✓ Brain class with 100 ideas
- ✓ Dog and Cat have Brain*
- ✓ Deep copy implemented (new Brain, not pointer copy)
- ✓ Array of Animals works correctly
- ✓ No memory leaks (virtual destructor!)
- ✓ Copy test proves deep copy

### Exercise 02
- ✓ Animal is abstract (pure virtual makeSound)
- ✓ Cannot instantiate Animal
- ✓ Everything else still works

### Exercise 03
- ✓ AMateria abstract with pure virtual clone()
- ✓ Ice and Cure implement clone() and use()
- ✓ ICharacter interface implemented by Character
- ✓ Character has 4-slot inventory
- ✓ equip/unequip/use work correctly
- ✓ IMateriaSource interface implemented
- ✓ MateriaSource learns and creates materias
- ✓ Deep copy everywhere
- ✓ No memory leaks
- ✓ Subject's main() output matches exactly

### Understanding
- ✓ Explain virtual functions
- ✓ Explain virtual destructor necessity
- ✓ Explain deep vs shallow copy
- ✓ Explain abstract classes
- ✓ Explain interfaces in C++98
- ✓ Explain clone() pattern
- ✓ Explain memory ownership in Ex03

---

**Ahmd Fahs** (afahs) | 42 Student | C++ Module 04 - January 2026

*For questions or issues, please contact afahs via the 42 intranet.*