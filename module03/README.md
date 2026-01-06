# C++ Module 03 - Inheritance

*This project has been created as part of the 42 curriculum by afahs.*

## Description

C++ Module 03 introduces **Inheritance**, one of the fundamental pillars of Object-Oriented Programming. Through a series of robot-themed exercises, students learn single inheritance, construction/destruction chaining, and tackle the challenging diamond inheritance problem using virtual inheritance.

The project consists of four exercises:
- **Exercise 00**: Base ClapTrap class with health, energy, and combat mechanics
- **Exercise 01**: ScavTrap - single inheritance with different stats and abilities
- **Exercise 02**: FragTrap - another derived class with unique characteristics
- **Exercise 03**: DiamondTrap - multiple inheritance solving the diamond problem

### What is Inheritance?

Inheritance allows classes to inherit attributes and methods from other classes:
- **Code reuse**: Share common functionality across related classes
- **"is-a" relationships**: ScavTrap *is a* ClapTrap with extra features
- **Hierarchical organization**: Build logical class structures

### The Diamond Problem

```
     ClapTrap
     /      \
ScavTrap  FragTrap
     \      /
   DiamondTrap
```

Without virtual inheritance, DiamondTrap would contain two copies of ClapTrap's attributes. Virtual inheritance ensures only one shared instance exists.

### Learning Objectives

- Implement single and multiple inheritance
- Understand construction/destruction chaining (Base → Derived, then Derived → Base)
- Master the `protected` access specifier
- Override base class methods in derived classes
- Solve the diamond problem with virtual inheritance
- Use the `using` declaration for method selection

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

Exercise 03 adds:
```bash
-Wshadow  # Warns about variable shadowing
```

### Running the Exercises

**Exercise 00: ClapTrap**
```bash
cd ex00/ && make && ./claptrap
```
Base class with attack(0), takeDamage(), beRepaired() mechanics.
Stats: HP(10), Energy(10), Damage(0)

**Exercise 01: ScavTrap**
```bash
cd ex01/ && make && ./scavtrap
```
Inherits from ClapTrap with different stats and guardGate() ability.
Stats: HP(100), Energy(50), Damage(20)

**Exercise 02: FragTrap**
```bash
cd ex02/ && make && ./fragtrap
```
Another derived class with highFivesGuys() ability.
Stats: HP(100), Energy(100), Damage(30)

**Exercise 03: DiamondTrap**
```bash
cd ex03/ && make && ./diamondtrap
```
Multiple inheritance with virtual base classes.
Stats: HP(Frag:100), Energy(Scav:50), Damage(Frag:30)

### Project Structure

```
cpp03/
├── ex00/  # ClapTrap base class
├── ex01/  # + ScavTrap
├── ex02/  # + FragTrap
└── ex03/  # + DiamondTrap (diamond inheritance)
```

## Key Concepts

### Exercise 00: Base Class Design

```cpp
class ClapTrap {
private:  // Change to protected in ex01!
    std::string name;
    unsigned int hitPoints;      // 10
    unsigned int energyPoints;   // 10
    unsigned int attackDamage;   // 0
public:
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
};
```

**Rules:**
- attack() and beRepaired() cost 1 energy
- Cannot act if HP = 0 (dead) or Energy = 0 (exhausted)
- All actions print descriptive messages

### Exercise 01: Single Inheritance

**Change private to protected:**
```cpp
class ClapTrap {
protected:  // Allows derived classes to access
    std::string name;
    // ...
};
```

**ScavTrap inherits and overrides:**
```cpp
class ScavTrap : public ClapTrap {
public:
    ScavTrap(const std::string& name);
    void attack(const std::string& target);  // Override
    void guardGate(void);                     // New ability
};
```

**Construction/Destruction Chaining:**
```
Construction: ClapTrap → ScavTrap
Destruction:  ScavTrap → ClapTrap (reverse!)
```

Why? Derived class needs base to exist first, then cleans up before base.

### Exercise 02: Multiple Derived Classes

FragTrap is independent from ScavTrap, both inherit from ClapTrap:

```
      ClapTrap
      /      \
ScavTrap  FragTrap
```

Each has unique stats and abilities but shares the ClapTrap interface.

### Exercise 03: Diamond Inheritance

**The Problem:**
```cpp
class ScavTrap : public ClapTrap { };
class FragTrap : public ClapTrap { };
class DiamondTrap : public ScavTrap, public FragTrap { };
// DiamondTrap has TWO ClapTraps! → Ambiguity!
```

**The Solution: Virtual Inheritance**
```cpp
class ScavTrap : virtual public ClapTrap { };
class FragTrap : virtual public ClapTrap { };
class DiamondTrap : public ScavTrap, public FragTrap { };
// DiamondTrap has ONE shared ClapTrap ✓
```

**DiamondTrap Design:**
- Private `name` attribute (shadows ClapTrap::name)
- ClapTrap::name = parameter + "_clap_name"
- hitPoints from FragTrap (100)
- energyPoints from ScavTrap (50)
- attackDamage from FragTrap (30)
- attack() from ScavTrap (via `using ScavTrap::attack;`)
- whoAmI() displays both names

**Construction Order with Virtual Inheritance:**
```
1. ClapTrap (virtual base, constructed by most derived)
2. ScavTrap (skips ClapTrap construction)
3. FragTrap (skips ClapTrap construction)
4. DiamondTrap
```

## Technical Choices

### Protected vs Private vs Public

- `private`: Only class itself can access
- `protected`: Class AND derived classes can access
- `public`: Everyone can access

Use `protected` for members that derived classes need to access.

### Method Overriding

Derived classes can replace base class methods:
```cpp
void ScavTrap::attack(const std::string& target) {
    std::cout << "ScavTrap " << name << " ferociously attacks "
              << target << "!" << std::endl;
}
```

### Stats Initialization

Override base stats in derived constructor:
```cpp
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    this->hitPoints = 100;
    this->energyPoints = 50;
    this->attackDamage = 20;
}
```

## Common Pitfalls and Solutions

| Problem | Solution |
|---------|----------|
| Cannot access base members | Change `private:` to `protected:` |
| Ambiguous base class | Add `virtual public` inheritance |
| Wrong construction order | Base always constructs first (check messages) |
| Not calling base constructor | Use initializer list: `: ClapTrap(name)` |
| Ambiguous member access | Use `ClapTrap::name` for explicit access |
| Stats not overridden | Set in derived constructor body |

## Testing

### Verify Construction/Destruction Order
```cpp
{
    ScavTrap scav("Test");
}
// Output should show:
// ClapTrap Test constructor called
// ScavTrap Test constructor called
// ScavTrap Test destructor called
// ClapTrap Test destructor called
```

### Test Each Class's Stats
```cpp
ClapTrap clap("CT");   // HP:10, EP:10, AD:0
ScavTrap scav("ST");   // HP:100, EP:50, AD:20
FragTrap frag("FT");   // HP:100, EP:100, AD:30
DiamondTrap dmd("DT"); // HP:100, EP:50, AD:30
```

### Memory Leak Detection
```bash
valgrind --leak-check=full ./executable
```

## Resources

### Official Documentation
- [C++ Reference - Derived Classes](https://en.cppreference.com/w/cpp/language/derived_class)
- [Virtual Base Classes](https://en.cppreference.com/w/cpp/language/derived_class#Virtual_base_classes)
- [cplusplus.com - Inheritance](http://www.cplusplus.com/doc/tutorial/inheritance/)

### Learning Materials
- [Inheritance in C++ - GeeksforGeeks](https://www.geeksforgeeks.org/inheritance-in-c/)
- [The Diamond Problem](https://stackoverflow.com/questions/2659116/how-does-virtual-inheritance-solve-the-diamond-problem)
- [Multiple Inheritance - isocpp.org](https://isocpp.org/wiki/faq/multiple-inheritance)

### Video Tutorials
- [The Cherno - Inheritance in C++](https://www.youtube.com/watch?v=X8nYM8wdNRE)
- [The Cherno - Virtual Functions](https://www.youtube.com/watch?v=oIV2KchSyGQ)

### Books
- "C++ Primer" (5th Edition) - Chapter on OOP and Inheritance
- "Effective C++" by Scott Meyers - Items on inheritance design
- "The C++ Programming Language" by Bjarne Stroustrup - Derived Classes chapter

## AI Usage Disclosure

### AI Tools Used
Claude (Anthropic) was used as an educational learning aid.

### How AI Was Used

**Conceptual Learning:**
- Understanding construction/destruction order and reasoning
- Learning when to use `protected` vs `private`
- Understanding the diamond problem and virtual inheritance
- Clarifying inheritance syntax and semantics

**Problem Solving:**
- Debugging "ambiguous base class" errors
- Understanding virtual inheritance construction order
- Resolving name shadowing issues
- Fixing constructor chaining problems

**Best Practices:**
- When to use inheritance vs composition
- Proper access specifier usage
- Method overriding patterns
- Testing strategies

### What I Implemented Independently

- All class designs and implementations
- All test cases and scenarios
- Method implementations (attack, guardGate, highFivesGuys, whoAmI)
- Stats initialization logic
- Construction/destruction message formatting
- Design decisions about class relationships

### Learning Approach

**Questions I Asked:**
- "Why does construction happen Base → Derived?"
- "How does virtual inheritance solve the diamond problem?"
- "What's the memory layout with virtual inheritance?"
- "When should I use protected vs private?"

**Questions I Didn't Ask:**
- "Write the ScavTrap class"
- "Give me the complete solution for exercise 03"
- "Implement the diamond inheritance"

**My Process:**
1. Read subject thoroughly and research concepts
2. Draw class diagrams on paper
3. Ask AI clarifying questions about specific concepts
4. Implement solutions myself
5. Test and verify with constructor/destructor messages
6. Use AI to understand compiler errors
7. Discuss with peers to confirm understanding

### Verification of Understanding

I can:
- ✓ Explain construction/destruction order and why
- ✓ Draw inheritance hierarchies
- ✓ Explain diamond problem and solution
- ✓ Choose between inheritance and composition
- ✓ Debug inheritance issues independently
- ✓ Reproduce solutions without AI assistance
- ✓ Explain every design decision in evaluation

### Honest Assessment

**AI helped me:**
- Understand complex concepts faster
- Debug compilation errors with context
- Learn best practices early
- Save time on syntax confusion

**But I still:**
- Wrote every line of code myself
- Tested thoroughly
- Understood concepts deeply
- Can explain in evaluation
- Ready for Module 04 (polymorphism)

## Evaluation Guidelines

### Checklist for Evaluators

**Exercise 00:**
- ✓ ClapTrap with correct initial stats (10/10/0)
- ✓ attack(), takeDamage(), beRepaired() work correctly
- ✓ Energy and HP validation (can't act when 0)
- ✓ Orthodox Canonical Form implemented

**Exercise 01:**
- ✓ ScavTrap inherits from ClapTrap
- ✓ Protected members in ClapTrap
- ✓ Correct stats (100/50/20)
- ✓ Construction/destruction chaining correct
- ✓ attack() overridden with different message
- ✓ guardGate() works

**Exercise 02:**
- ✓ FragTrap inherits from ClapTrap
- ✓ Correct stats (100/100/30)
- ✓ Different messages from ScavTrap
- ✓ highFivesGuys() works

**Exercise 03:**
- ✓ Virtual inheritance in ScavTrap and FragTrap
- ✓ DiamondTrap name shadowing implemented
- ✓ ClapTrap::name has "_clap_name" suffix
- ✓ Correct attribute sources (HP:Frag, EP:Scav, AD:Frag)
- ✓ Uses ScavTrap's attack()
- ✓ whoAmI() shows both names
- ✓ Only ONE ClapTrap instance

**Understanding:**
- ✓ Can explain construction order
- ✓ Can explain diamond problem
- ✓ Can explain virtual inheritance
- ✓ Can modify code if requested

## Additional Notes

- Exercise 03 is **optional** but highly recommended for learning
- The `-Wshadow` flag warns about intentional name shadowing
- Virtual inheritance has slight performance overhead but solves diamond problem
- Diamond inheritance is rare in production code - understand it but use carefully

---

**Ahmd Fahs** (afahs) | 42 Student | C++ Module 03 - January 2026

*For questions or issues, please contact afahs via the 42 intranet.*