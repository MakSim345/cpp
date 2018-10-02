#include <iostream>
#include "WelcomeToBank.h"
#include "gen.h"

// This is a facade:
class BankAccountFacade
{
public:
    BankAccountFacade(int accountNumberP, int pinCodeP):
      mMainAccountInUSD(0.0)
    {
        accountNumber = accountNumberP;
        securityCode = pinCodeP;

        acctChecker = new AccountNumberCheck();
        codeChecker = new SecurityCodeCheck();
        fundChecker = new FundsCheck();
        bankWelcome = new WelcomeToBank();

        std::cout << "BankAccountFacade created" << std::endl;
    }
    
   AccountNumberCheck *acctChecker;
   SecurityCodeCheck *codeChecker;
   FundsCheck *fundChecker;
   WelcomeToBank *bankWelcome;
      
   int getAccountNumber() {return accountNumber;}
   int getSecurityCode() {return securityCode;}

   void withdrawCash(double cashToGetP)
   {
       if (acctChecker->isAccountActive(getAccountNumber()) && 
           codeChecker->isCodeCorrect(getSecurityCode()) && 
           fundChecker->isHaveEnoughMoney(cashToGetP))
       {
          std::cout << "Transaction Completed" << std::endl;
       }
       else
       {
          std::cout << "Transaction Failed" << std::endl;
       }
   }


   void depositCash(double cashToDepositP)
   {
       if (acctChecker->isAccountActive(getAccountNumber()) && 
           codeChecker->isCodeCorrect(getSecurityCode()) )
       {
           fundChecker->makeDeposit(cashToDepositP);
           std::cout << "Transaction Completed" << std::endl;
       }      
   }

private:
    long mMainAccountInUSD;
    int accountNumber;
    int securityCode;
};