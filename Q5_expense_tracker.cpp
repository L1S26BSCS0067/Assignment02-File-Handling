
/*
  * Name       : Khadija Tul Kubra
  * Reg No     : L1S26BSCS0067
  * Assignment : 02 - File Handling
  * Question   : Q5 - Expense Tracker
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int choice;

    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char category[20];
            int amount;

            cout << "Enter category: ";
            cin >> category;

            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                
                ofstream outFile("expenses.txt", ios::app);

                outFile << category << " " << amount << endl;

                outFile.close();

                cout << "Expense saved." << endl;
            }
        }

        else if (choice == 2) {
            char category[100][20];
            int amount[100];
            int count = 0;
            int total = 0;
            int largest = 0;

            
            ifstream inFile("expenses.txt");

            if (inFile) {
                while (count < 100 &&
                    inFile >> category[count] >> amount[count]) {
                    total = total + amount[count];

                    if (count == 0 ||
                        amount[count] > amount[largest]) {
                        largest = count;
                    }

                    count++;
                }

                inFile.close();
            }

            if (count == 0) {
                cout << "No expenses yet." << endl;
            }
            else {
                for (int i = 0; i < count; i++) {
                    cout << i + 1 << ". "
                        << category[i] << " "
                        << amount[i] << endl;
                }

                cout << "Total spent: " << total << endl;
                cout << "Largest expense: "
                    << category[largest] << " ("
                    << amount[largest] << ")" << endl;
            }
        }

        else if (choice == 3) {
            char wanted[20];
            char category[100][20];
            int amount[100];
            int count = 0;
            int total = 0;
            int found = 0;

            cout << "Enter category: ";
            cin >> wanted;

            // Open the file again for the selected category
            ifstream inFile("expenses.txt");

            if (inFile) {
                while (count < 100 &&
                    inFile >> category[count] >> amount[count]) {

                    // strcmp returns 0 when both words are equal
                    if (strcmp(category[count], wanted) == 0) {
                        total = total + amount[count];
                        found++;
                    }

                    count++;
                }

                inFile.close();
            }

            if (found == 0) {
                cout << "No expenses found for "
                    << wanted << endl;
            }
            else {
                cout << "Expenses in " << wanted
                    << ": " << found << endl;

                cout << "Total for " << wanted
                    << ": " << total << endl;
            }
        }

        else if (choice == 4) {
            
            ofstream outFile("expenses.txt");
            outFile.close();

            cout << "All expenses cleared." << endl;
        }

        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }

        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
