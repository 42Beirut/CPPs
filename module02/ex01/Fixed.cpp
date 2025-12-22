#include "Fixed.hpp"

Fixed::Fixed(void) : rawBits(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int intValue) {
    std::cout << "Int constructor called" << std::endl;
    this->rawBits = intValue << this->fractionalBits;
}

Fixed::Fixed(const float floatValue) {
    std::cout << "Float constructor called" << std::endl;
    this->rawBits = roundf(floatValue * (1 << this->fractionalBits));
}

Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        this->rawBits = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    return this->rawBits;
}

void Fixed::setRawBits(int const raw) {
    this->rawBits = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(this->rawBits) / (1 << this->fractionalBits);
}

int Fixed::toInt(void) const {
    return this->rawBits >> this->fractionalBits;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
