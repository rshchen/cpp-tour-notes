#include <stdexcept>
#include <cassert>
#include <iostream>
class BankAccount
{
    double balance_;
public:
    explicit BankAccount(double balance): balance_{balance}
    {
        if (balance < 0) throw std::invalid_argument{"Invalid balance."};
    }

    void deposit(double val)
    {
        if (val <= 0) throw std::invalid_argument{"Invalid deposit."};
        balance_ += val;
    }

    bool withdraw(double val)
    {
        if (val <= 0) throw std::invalid_argument{"Invalid withdraw."};
        if (balance_ < val) return false;
        balance_ -= val;
        return true;
    }

    double balance() const
    {
        return balance_;
    }

};

int main()
{

    BankAccount account1{100};
    assert(account1.balance() == 100);
    
    account1.deposit(50);
    account1.withdraw(30);
    assert(account1.balance() == 120);

    assert(!account1.withdraw(150) && account1.balance() == 120);

    try
    {
        BankAccount{-10};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        BankAccount{0}.deposit(0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        BankAccount{0}.withdraw(-5);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}