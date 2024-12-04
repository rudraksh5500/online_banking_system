#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

// BankAccount class implementation
class BankAccount {
private:
    string account_number;
    double balance;

public:
    BankAccount(string acc_num, double initial_balance = 0.0) {
        account_number = acc_num;
        balance = initial_balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be greater than zero.");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be greater than zero.");
        }
        if (amount > balance) {
            throw runtime_error("Insufficient funds.");
        }
        balance -= amount;
    }

    double check_balance() const {
        return balance;
    }

    void transfer(BankAccount &to_account, double amount) {
        if (amount <= 0) {
            throw invalid_argument("Transfer amount must be greater than zero.");
        }
        withdraw(amount);
        to_account.deposit(amount);
    }
};

// Unit Tests
void test_deposit() {
    BankAccount account("12345", 100.0);
    account.deposit(50.0);
    assert(account.check_balance() == 150.0);
}

void test_withdraw() {
    BankAccount account("12345", 100.0);
    account.withdraw(50.0);
    assert(account.check_balance() == 50.0);

    try {
        account.withdraw(200.0);
        assert(false); // This should not execute
    } catch (runtime_error &e) {
        assert(true); // Exception expected
    }
}

void test_check_balance() {
    BankAccount account("12345", 200.0);
    assert(account.check_balance() == 200.0);
}

// Integration Tests
void test_deposit_then_withdraw() {
    BankAccount account("12345", 100.0);
    account.deposit(50.0);
    account.withdraw(30.0);
    assert(account.check_balance() == 120.0);
}

void test_withdraw_then_deposit() {
    BankAccount account("12345", 100.0);
    account.withdraw(50.0);
    account.deposit(70.0);
    assert(account.check_balance() == 120.0);
}

// System Test
void system_test() {
    BankAccount account1("12345", 100.0);
    BankAccount account2("67890", 50.0);

    account1.deposit(100.0);
    assert(account1.check_balance() == 200.0);

    account1.withdraw(50.0);
    assert(account1.check_balance() == 150.0);

    account1.transfer(account2, 50.0);
    assert(account1.check_balance() == 100.0);
    assert(account2.check_balance() == 100.0);
}

// White-Box Test (Branch Testing)
void test_withdrawal_branches() {
    BankAccount account("12345", 100.0);

    account.withdraw(50.0); // Valid withdrawal
    assert(account.check_balance() == 50.0);

    try {
        account.withdraw(200.0); // Insufficient funds
        assert(false); // Should not execute
    } catch (runtime_error &e) {
        assert(true); // Exception expected
    }

    try {
        account.withdraw(-10.0); // Invalid amount
        assert(false); // Should not execute
    } catch (invalid_argument &e) {
        assert(true); // Exception expected
    }
}

// Main Function
int main() {
    // Run Unit Tests
    test_deposit();
    test_withdraw();
    test_check_balance();

    // Run Integration Tests
    test_deposit_then_withdraw();
    test_withdraw_then_deposit();

    // Run System Test
    system_test();

    // Run White-Box Test
    test_withdrawal_branches();

    cout << "All tests passed!" << endl;
    return 0;
}
