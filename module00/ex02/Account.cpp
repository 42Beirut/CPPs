#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
    _nbAccounts++;
    _totalAmount += initial_deposit;
    
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";created" << std::endl;
}

Account::~Account(void) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount << ";closed" << std::endl;
}

int Account::getNbAccounts(void) {
    return _nbAccounts;
}

int Account::getTotalAmount(void) {
    return _totalAmount;
}

int Account::getNbDeposits(void) {
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
    return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void) {
    _displayTimestamp();
    std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount 
              << ";deposits:" << _totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount;
    
    this->_amount += deposit;
    this->_nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;
    
    std::cout << ";deposit:" << deposit << ";amount:" << this->_amount 
              << ";nb_deposits:" << this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount;
    
    if (this->_amount >= withdrawal) {
        this->_amount -= withdrawal;
        this->_nbWithdrawals++;
        _totalAmount -= withdrawal;
        _totalNbWithdrawals++;
        
        std::cout << ";withdrawal:" << withdrawal << ";amount:" << this->_amount 
                  << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
        return true;
    } else {
        std::cout << ";withdrawal:refused" << std::endl;
        return false;
    }
}

int Account::checkAmount(void) const {
    return this->_amount;
}

void Account::displayStatus(void) const {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount 
              << ";deposits:" << this->_nbDeposits << ";withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::_displayTimestamp(void) {
    std::time_t now = std::time(0);
    std::tm* timeinfo = std::localtime(&now);
    
    std::cout << "[" << (timeinfo->tm_year + 1900)
              << std::setfill('0') << std::setw(2) << (timeinfo->tm_mon + 1)
              << std::setfill('0') << std::setw(2) << timeinfo->tm_mday
              << "_"
              << std::setfill('0') << std::setw(2) << timeinfo->tm_hour
              << std::setfill('0') << std::setw(2) << timeinfo->tm_min
              << std::setfill('0') << std::setw(2) << timeinfo->tm_sec
              << "] ";
}