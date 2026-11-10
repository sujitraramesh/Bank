#include <iostream>
#include <string>
#include <limits>
using namespace std;

class BankAccount {
    int accNo = 0;
    string name;
    double balance = 0;
    int deposits = 0, withdrawals = 0, rejected = 0;

public:
    bool create(int no, string n, double bal) {
        if (bal < 0) { cout << "Error: Opening balance cannot be negative.\n"; return false; }
        accNo = no; name = n; balance = bal;
        deposits = withdrawals = rejected = 0;
        cout << "Account created successfully.\n";
        return true;
    }
    void deposit(double amt) {
        if (amt <= 0) { rejected++; cout << "Rejected: invalid amount.\n"; return; }
        balance += amt; deposits++;
        cout << "Deposit successful.\n";
    }
    void withdraw(double amt) {
        if (amt <= 0) { rejected++; cout << "Rejected: invalid amount.\n"; return; }
        if (amt > balance) { rejected++; cout << "Rejected: insufficient balance.\n"; return; }
        balance -= amt; withdrawals++;
        cout << "Withdrawal successful.\n";
    }
    void checkBalance() const { cout << "Current balance: " << balance << "\n"; }
    void displayAccount() const {
        cout << "Account No: " << accNo << "\nName: " << name << "\nBalance: " << balance << "\n";
    }
    void displayTransactionSummary() const {
        cout << "Successful deposits: " << deposits
             << "\nSuccessful withdrawals: " << withdrawals
             << "\nRejected transactions: " << rejected
             << "\nFinal balance: " << balance << "\n";
    }
};

bool readNum(double &x) {
    if (cin >> x) return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

int main() {
    BankAccount acc;
    bool created = false;
    int choice;
    double amt;

    do {
        cout << "\n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n"
                "4. Balance Enquiry\n5. Display Account Details\n"
                "6. Display Transaction Summary\n7. Exit\nEnter choice: ";
        if (!readNum(amt)) amt = 0;
        choice = (int)amt;

        if (choice == 7) { cout << "Thank you. Exiting safely.\n"; break; }
        if (choice < 1 || choice > 7) { cout << "Invalid choice. Try again.\n"; continue; }

        if (choice == 1) {
            double no, bal; string name;
            cout << "Account number: ";  if (!readNum(no))  { cout << "Invalid input.\n"; continue; }
            cout << "Customer name: ";   cin >> ws; getline(cin, name);
            cout << "Opening balance: "; if (!readNum(bal)) { cout << "Invalid input.\n"; continue; }
            created = acc.create((int)no, name, bal);
            continue;
        }

        if (!created) { cout << "Error: Please create an account first.\n"; continue; }

        if (choice == 2 || choice == 3) {
            cout << "Enter amount: ";
            if (!readNum(amt)) { cout << "Invalid input.\n"; continue; }
            choice == 2 ? acc.deposit(amt) : acc.withdraw(amt);
        }
        else if (choice == 4) acc.checkBalance();
        else if (choice == 5) acc.displayAccount();
        else if (choice == 6) acc.displayTransactionSummary();
    } while (true);

    return 0;
}
