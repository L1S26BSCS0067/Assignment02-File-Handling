
/*
 * Name       : Khadija Tul Kubra
 * Reg No     : L1S26BSCS0067
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#include <iostream>
                       // BUG 1- fstream in header for file handling.
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");

                         //BUG 2- check
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // BUG 3: ios::app will write after the saved previous readings .
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;

    // BUG 4- double data type saves decimal values
    double total = 0;

    // BUG 5: firstly skip header lin.
    inFile.ignore(100, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;

        if (qty < 10) {
            // BUG 6: endl har item ko alag line par likhta hai.
            reorder << code << " " << qty << endl;
            low++;
        }
    }

    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;

    return 0;
}
