#include "AMateria.hpp"

AMateria::AMateria(void) : type("unknown") {
}

AMateria::AMateria(std::string const& type) : type(type) {
}

AMateria::AMateria(const AMateria& other) : type(other.type) {
}

AMateria& AMateria::operator=(const AMateria& other) {
    // Type is not copied as per subject requirements
    (void)other;
    return *this;
}

AMateria::~AMateria(void) {
}

std::string const& AMateria::getType(void) const {
    return this->type;
}

void AMateria::use(ICharacter& target) {
    (void)target;
}