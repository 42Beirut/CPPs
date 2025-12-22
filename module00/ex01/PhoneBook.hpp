#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
private:
    Contact contacts[8];
    int currentIndex;
    int totalContacts;

    std::string truncateString(const std::string &str) const;
    void displayContactList() const;
    bool isValidIndex(const std::string &input) const;

public:
    PhoneBook();
    ~PhoneBook();   

    void addContact();
    void searchContacts() const;
    void run();
};

#endif