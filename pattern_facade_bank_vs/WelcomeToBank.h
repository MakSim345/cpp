#pragma once

#include "gen.h"

class WelcomeToBank
{
public:
    WelcomeToBank(void)
    {
        std::cout << "Welcome to ABC bank" << std::endl; 
    }
    ~WelcomeToBank(void);
};


class AccountNumberCheck
{
public:
    AccountNumberCheck(void)
        : accountNumber(12345678)
    {
        // std::cout << "Welcome to ABC bank"; 
    }
    ~AccountNumberCheck(void);

    int getAccountNumber() {return accountNumber; }
    bool isAccountActive(int accToCheckP)
    {
        if (accToCheckP == getAccountNumber())
            return true;
        else 
            return false;
    }

private:
    int accountNumber;
};


class SecurityCodeCheck
{
public:
    SecurityCodeCheck(void)
        :securityCode(1234)
    {
        // std::cout << ""; 
    }
    ~SecurityCodeCheck(void);

    int getSecurityCode() {return securityCode; }

    bool isCodeCorrect(int codeToCheckP)
    {
        if (codeToCheckP == getSecurityCode())
            return true;
        else 
            return false;
    }

private:
    int securityCode;
};


class FundsCheck
{
public:
    FundsCheck(void)
        :cashInAccount(1000.0)
    {
        // std::cout << ""; 
    }
    ~FundsCheck(void);

    double getCashInAccount() {return cashInAccount; }

    void decreaseCashInAccount(double cashWithdraw)
    {
        cashInAccount -= cashWithdraw;
    }

    void increaseCashInAccount(double cashDeposit)
    {
        cashInAccount += cashDeposit;
    }

    bool isHaveEnoughMoney(double cashToWithdrawal)
    {
        if (cashToWithdrawal > getCashInAccount())
        {
            std::cout << "Error: You don't have enough money" << std::endl;
            return false;
        }
        else
        {
            decreaseCashInAccount(cashToWithdrawal);
            std::cout << "Withdrawal complete: Current balance is:" << getCashInAccount() << std::endl;
            return true;
        }
    }

    void makeDeposit(double cashtoDeposit)
    {
        increaseCashInAccount(cashtoDeposit);
        std::cout << "Deposit complete: Current balance is:" << getCashInAccount() << std::endl;
    }

private:
    double cashInAccount;
};


