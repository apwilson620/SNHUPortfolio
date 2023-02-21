#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class BankingApp {
public:
    BankingApp(); //Default constructor

    void dataInputMenu(); //public  class functions
    void displayReport();
    void setNumMonths(int);
    void setOpeningAmount(double);
    void setDepositedAmount(double);
    void setInterestRate(double);
    void calculate();
    void calculateWODeposit();
private:
    double initialOpeningAmount; //Private class variables
    int month;
    double openingAmount;
    double depositedAmount;
    double total;
    double interest;
    double interestAmount;
    double closingBalance;
    int years;
    double totalInterestEarned;
};

BankingApp::BankingApp() { //Default constructor, sets all private variables equal to zero
    initialOpeningAmount = 0;
    month = 0;
    openingAmount = 0;
    depositedAmount = 0;
    total = 0;
    interest = 0;
    closingBalance = 0;
    years = 0;
    interestAmount = 0;
    totalInterestEarned = 0;
}

void BankingApp::setOpeningAmount(double openAmount) { //Set functions for variables
    initialOpeningAmount = openAmount;
}

void BankingApp::setDepositedAmount(double depoAmount) {
    depositedAmount = depoAmount;
}

void BankingApp::setInterestRate(double interestRate) { //Divides interest rate by 100 here instead of doing it in calculate functions
    interest = interestRate / 100;
}

void BankingApp::setNumMonths(int numYears) { //Sets num months and years
    month = numYears * 12;
    years = numYears;
}

void BankingApp::calculate() { //Calculates balance and interest rate on a yearly basis with additional monthly deposits
    totalInterestEarned = 0;
    for (int i = 0; i < 12; i++) {
        total = openingAmount + depositedAmount;
        interestAmount = (openingAmount + depositedAmount) * (interest / 12);
        closingBalance = interestAmount + total;
        openingAmount = closingBalance;
        totalInterestEarned += interestAmount;
    }
}

void BankingApp::calculateWODeposit() { //Calculates balance and interest on a yearly basis without additional monthly deposits
    totalInterestEarned = 0;
    for (int i = 0; i < 12; i++) {
        total = openingAmount;
        interestAmount = (openingAmount) * (interest / 12);
        closingBalance = interestAmount + total;
        openingAmount = closingBalance;
        totalInterestEarned += interestAmount;
    }
}

void BankingApp::displayReport() { //Displays the two reports
    openingAmount = initialOpeningAmount; //Sets opening amount as the initial opening amount so the two graphs are not altered by the results of each others results
    cout << "    Balance and Interest Without Additional Monthly Deposits    " << endl;
    cout << "================================================================" << endl;
    cout << " Year         Year End Balance      Year End Earned Interest    " << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 1; i <= years; i++) {
        calculateWODeposit();
        string closingBalanceStr = to_string(closingBalance);
        string totalInterestEarnedStr = to_string(totalInterestEarned);
        for (int j = 0; j < 4; j++) {
            closingBalanceStr.pop_back(); //Removes the last 4 numbers on the string to give the number 2 decimal places
            totalInterestEarnedStr.pop_back();
        }
        cout << "   " << i << setw(24) << "$" + closingBalanceStr << setw(30) << "$" + totalInterestEarnedStr << "    " << endl;
    }

    cout << endl;

    openingAmount = initialOpeningAmount;
    cout << "      Balance and Interest With Additional Monthly Deposits     " << endl;
    cout << "================================================================" << endl;
    cout << " Year         Year End Balance      Year End Earned Interest    " << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 1; i <= years; i++) {
        calculate();
        string closingBalanceStr = to_string(closingBalance);
        string totalInterestEarnedStr = to_string(totalInterestEarned);
        for (int j = 0; j < 4; j++) {
            closingBalanceStr.pop_back();
            totalInterestEarnedStr.pop_back();
        }
        cout << "   " << i << setw(24) << "$" + closingBalanceStr << setw(30) << "$" + totalInterestEarnedStr << "    " << endl;
        //openingAmount = closingBalance;
    }
}

void BankingApp::dataInputMenu() { //The menu for data input
    vector<string>  info{ "Initial Investment Amount", "Monthly Deposit", "Annual Interest", "Number of years" };
    vector<string> values(4, " ");

    for (int i = 0; i < info.size() + 1; i++) {
        cout << "**********************************" << endl;
        cout << "********** Data Input ************" << endl;
        cout << "Initial Investment Amount: $" << values[0] << endl;
        cout << "Monthly Deposit: $" << values[1] << endl;
        cout << "Annual Interest: %" << values[2] << endl;
        cout << "Number of years: " << values[3] << endl;
        system("pause");
        system("cls");
        if (i < 4) {
            cout << "Enter " << info[i] << " value: ";
            cin >> values[i]; //All values elements are just a space and printed as such until they are changed in input to the value the user specifies
            double temp = stoi(values[i]);
            while ((i < 2 && temp < 1) || (i > 1 && temp < 0)) { //Checks if the temp value is less than 1 because the functional requirements document says initial investment amount and monthly deposit both must be positive real numbers
                cout << "That is not a valid value" << endl;
                cout << "Enter " << info[i] << " value: ";
                cin >> values[i];
                temp = stoi(values[i]);
            }
        }
        system("cls");

    }

    //system("pause");
    vector<double> newValues;
    for (int i = 0; i < values.size(); i++) { //Converts the string values back to a double
        double temp = stoi(values[i]);
        newValues.push_back(temp);
    }
    setOpeningAmount(newValues[0]);
    setDepositedAmount(newValues[1]);
    setInterestRate(newValues[2]);
    setNumMonths(newValues[3]);

}

int main()
{
    BankingApp myApp; //Creates a class object
    myApp.dataInputMenu(); //Runs data input menu function
    myApp.displayReport(); //Runs display report function
    return 0;
}