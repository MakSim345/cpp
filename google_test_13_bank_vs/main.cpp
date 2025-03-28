#include "pch.h"
#include "gen.h"
/*
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
*/
int add(int value1, int value2) 
{
    return (value1 + value2);
}

TEST(AddTest, PositiveNos) 
{
    EXPECT_EQ(16, add(8, 8));
}



struct account_state
{
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;
};

account_state ac1;
account_state ac2;

struct BankAccount
{
    int ballance;

    BankAccount()
        :ballance(0)
    {

    }

    explicit BankAccount(const int pBalance)
        : ballance(pBalance)
    {
    }

    void deposit(int amount)
    {
        ballance += amount;
    }

    bool withdraw(int amount)
    {
        if (amount <= ballance)
        {
            ballance -= amount;
            return true;
        }
        return false;
    }
};

struct BankAccountTest
    : testing::Test
{
    BankAccount* account;
    BankAccountTest()
    {
        account = new BankAccount();
    }

    virtual ~BankAccountTest()
    {
        delete account;
    }

};

TEST_F(BankAccountTest, BancAccountStartsEmpty)
{
    EXPECT_EQ(0, account->ballance);
}

TEST_F(BankAccountTest, CanDepositMoney)
{
    account->deposit(100);
    EXPECT_EQ(100, account->ballance);
}

TEST(TestSuite, CreateFileTest)
{
    ifstream fout1;
    char buff1[500];
    // ASSERT_THROW(fout1->open("gen.h"), WinApiException);
    ASSERT_NO_THROW(fout1.open("main.cpp"));
    /*
    while(!fout1.eof()) //read file
    {
        fout1.getline(buff1, 500);
        std::cout << buff1 << endl;
    }
    */
}

/*
TEST(AccountTest, BancAccountStartsEmpty)
{
    BankAccount account;
    EXPECT_EQ(0, account.ballance);
}
*/

struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface <account_state>
{
    WithdrawAccountTest()
    {
        account->ballance = GetParam().initial_balance;
    }
};

TEST_P(WithdrawAccountTest, FinalBalance)
{
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->ballance);
    EXPECT_EQ(as.success, success);
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    int returnValue = RUN_ALL_TESTS();

    printf("Application complete.\n");
    system("PAUSE");

    return returnValue;
 }
