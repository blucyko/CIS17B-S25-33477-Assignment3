// Ash Nguyen
// CIS-17B-S25-33477
// 3/22/25
// Assignment 3 Bank Account Management

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ======================== //
// Custom Exception Classes //
// ======================== //

// NegativeDepositException (for negative deposit attempts)
class NegativeDepositException : public runtime_error
{
public:
    NegativeDepositException() : runtime_error("Cannot deposit a negative amount!") {}
};

// OverdrawException (for withdrawing more than the balance)
class OverdrawException : public runtime_error
{
public:
    OverdrawException() : runtime_error("Insufficient funds!") {}
};

// InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public runtime_error
{
public:
    InvalidAccountOperationException() : runtime_error("Account is closed for transactions!") {}
};

// ================== //
// Bank Account Class //
// ================== //
class BankAccount
{
private:
    string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(string accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount)
    {
        if (!isActive)
        {
            throw InvalidAccountOperationException();
        }
        if (amount < 0)
        {
            throw NegativeDepositException();
        }
        balance += amount;
        cout << "Deposited $" << amount << " successfully.\n";
    }

    // Withdraw method
    void withdraw(double amount)
    {
        if (!isActive)
        {
            throw InvalidAccountOperationException();
        }
        if (amount > balance)
        {
            throw OverdrawException();
        }
        balance -= amount;
        cout << "Withdrew $" << amount << " successfully.\n";
    }

    // Method to get current balance
    double getBalance() const
    {
        return balance;
    }

    // Method to close the account
    void closeAccount()
    {
        if (!isActive)
        {
            throw InvalidAccountOperationException();
        }
        isActive = false;
        cout << "Account closed successfully.\n";
    }

    // Method to check if account is active
    bool getIsActive() const
    {
        return isActive;
    }
};

// =================== //
// Function Prototypes //
// =================== //
void displayMenu();
string generateAccountNumber(); 
void deposit(unique_ptr<BankAccount>& account);
void withdraw(unique_ptr<BankAccount>& account);
void getBalance(const unique_ptr<BankAccount>& account);
void closeAccount(unique_ptr<BankAccount>& account);

int main()
{
    // Constants for menu choices
    const int DEPOSIT_MONEY_CHOICE = 1;
    const int WITHDRAW_MONEY_CHOICE = 2;
    const int CHECK_BALANCE_CHOICE = 3;
    const int CLOSE_ACCOUNT_CHOICE = 4;
    const int QUIT_CHOICE = 5;

    try
    {
        double initialBalance;
        cout << "Enter initial balance: ";
        cin >> initialBalance;

        // Generate a random 6-digit account number
        string accountNumber = generateAccountNumber();

        // Create BankAccount object using smart pointers
        auto account = make_unique<BankAccount>(accountNumber, initialBalance);
        cout << "Bank Account Created: #" << accountNumber << "\n";

        int choice;

        while (true)
        {
            displayMenu(); // Menu of choices for user to select in bank account management system
            cin >> choice;

            switch (choice)
            {
            case DEPOSIT_MONEY_CHOICE: // choice for depositing money
                deposit(account);
                break;
            case WITHDRAW_MONEY_CHOICE: // choice for withdrawing money
                withdraw(account);
                break;
            case CHECK_BALANCE_CHOICE: // choice for checking account balance
                getBalance(account);
                break;
            case CLOSE_ACCOUNT_CHOICE: // choice for closing account
                closeAccount(account);
                break;
            case QUIT_CHOICE:          // choice for quitting the program
                cout << "Thank you for using the Bank Account Management System!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}

//******************************************//
//				   Functions				//
//******************************************//

// ====================== //
// Menu Function for User //
// ====================== //
void displayMenu()
{
    cout << "\nWelcome to the Bank Account Management System" << endl;
    cout << "===============================================" << endl;
    cout << "1. Deposit Funds\n";
    cout << "2. Withdraw Funds\n";
    cout << "3. Check Balance\n";
    cout << "4. Close Account\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}
// ************************************************************* //

// ================================================== //
// Function to generate random 6-digit account number //
// ================================================== //
string generateAccountNumber()
{
    srand(time(0)); // Seed random number generator
    int randomNumber = 100000 + rand() % 900000; // Generates a 6-digit number between 100000 and 999999
    return to_string(randomNumber);
}
// ************************************************************* //

// ========================= //
// Function to deposit money //
// ========================= //
void deposit(unique_ptr<BankAccount>& account)
{
    double amount;
    cout << "Enter deposit amount: ";
    cin >> amount;

    try
    {
        account->deposit(amount);                // if no errors caught deposit money into account
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl; // if error caught display error
    }
}
// ************************************************************* //

// ========================== //
// Function to withdraw money //
// ========================== //
void withdraw(unique_ptr<BankAccount>& account)
{
    double amount;
    cout << "Enter withdrawal amount: ";
    cin >> amount;

    try
    {
        account->withdraw(amount);               // if no errors caught withdraw money from account
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl; // if error caught display error
    }
}
// ************************************************************* //

// ================================= //
// Function to check account balance //
// ================================= //
void getBalance(const unique_ptr<BankAccount>& account)
{
    cout << "Current Balance: $" << account->getBalance() << endl; // display current account balance
}
// ************************************************************* //

// ========================= //
// Function to close account //
// ========================= //
void closeAccount(unique_ptr<BankAccount>& account)
{
    try
    {
        account->closeAccount();                 // if no errors caught close account
    }
    catch (const exception& e)
    {
        cerr << "\nError: " << e.what() << endl; // if error caught display error
    }
}
// ************************************************************* //



