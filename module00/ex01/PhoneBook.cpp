#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

PhoneBook::PhoneBook() : currentIndex(0), totalContacts(0) {
}

PhoneBook::~PhoneBook() {
}

std::string PhoneBook::truncateString(const std::string &str) const {
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::displayContactList() const {
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << std::endl;
    for (int i = 0; i < totalContacts; ++i) {
        std::cout << std::setw(10) << i + 1 << "|"
                  << std::setw(10) << truncateString(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << truncateString(contacts[i].getLastName()) << "|"
                  << std::setw(10) << truncateString(contacts[i].getNickname()) << std::endl;
    }
}

bool PhoneBook::isValidIndex(const std::string &input) const {
    if (input.empty())
        return false;
    
    for (size_t i = 0; i < input.length(); ++i) {
        if (!isdigit(input[i]))
            return false;
    }

    std::stringstream ss(input);
    int index;
    ss >> index;
    return index >= 1 && index <= totalContacts;
}

void PhoneBook::addContact() {
    std::string firstName, lastName, nickname, phoneNumber, darkestSecret;
    
    std::cout << "Enter first name: ";
    std::getline(std::cin, firstName);
    if (firstName.empty()) {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter last name: ";
    std::getline(std::cin, lastName);
    if (lastName.empty()) {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter nickname: ";
    std::getline(std::cin, nickname);
    if (nickname.empty()) {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phoneNumber);
    if (phoneNumber.empty()) {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, darkestSecret);
    if (darkestSecret.empty()) {
        std::cout << "Field cannot be empty!" << std::endl;
        return;
    }
    
    contacts[currentIndex].setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
    currentIndex = (currentIndex + 1) % 8;
    if (totalContacts < 8) {
        totalContacts++;
    }
    
    std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContacts() const {
    if (totalContacts == 0) {
        std::cout << "No contacts available." << std::endl;
        return;
    }
    
    displayContactList();
    
    std::string input;
    std::cout << "Enter the index of the contact to view details: ";
    std::getline(std::cin, input);
    
    if (!isValidIndex(input)) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    std::stringstream ss(input);
    int index;
    ss >> index;
    
    contacts[index].displayContact();
}

void PhoneBook::run() {
    std::string command;
    
    while (true) {
        std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);
        
        if (command == "ADD") {
            addContact();
        } else if (command == "SEARCH") {
            searchContacts();
        } else if (command == "EXIT") {
            break;
        } else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
}