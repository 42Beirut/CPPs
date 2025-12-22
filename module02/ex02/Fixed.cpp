#include "Fixed.hpp"

Fixed::Fixed(void) : rawBits(0) {
}

Fixed::Fixed(const int intValue) {
    this->rawBits = intValue << this->fractionalBits;
}

Fixed::Fixed(const float floatValue) {
    this->rawBits = roundf(floatValue * (1 << this->fractionalBits));
}

Fixed::Fixed(const Fixed& other) {
    *this = other;
}

Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other) {
        this->rawBits = other.getRawBits();
    }
    return *this;
}

Fixed::~Fixed(void) {
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

// Comparison operators
bool Fixed::operator>(const Fixed& other) const {
    return this->rawBits > other.rawBits;
}

bool Fixed::operator<(const Fixed& other) const {
    return this->rawBits < other.rawBits;
}

bool Fixed::operator>=(const Fixed& other) const {
    return this->rawBits >= other.rawBits;
}

bool Fixed::operator<=(const Fixed& other) const {
    return this->rawBits <= other.rawBits;
}

bool Fixed::operator==(const Fixed& other) const {
    return this->rawBits == other.rawBits;
}

bool Fixed::operator!=(const Fixed& other) const {
    return this->rawBits != other.rawBits;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->rawBits + other.rawBits);
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->rawBits - other.rawBits);
    return result;
}

Fixed Fixed::operator*(const Fixed& other) const {
    Fixed result;
    long long temp = static_cast<long long>(this->rawBits) * static_cast<long long>(other.rawBits);
    result.setRawBits(static_cast<int>(temp >> this->fractionalBits));
    return result;
}

Fixed Fixed::operator/(const Fixed& other) const {
    Fixed result;
    long long temp = (static_cast<long long>(this->rawBits) << this->fractionalBits) / other.rawBits;
    result.setRawBits(static_cast<int>(temp));
    return result;
}

// Increment/Decrement operators
Fixed& Fixed::operator++(void) {
    this->rawBits++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    this->rawBits++;
    return temp;
}

Fixed& Fixed::operator--(void) {
    this->rawBits--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    this->rawBits--;
    return temp;
}

// Static min/max functions
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
