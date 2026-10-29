
/*
  * Name       : Khadija Tul Kubra
  * Reg No     : L1S26BSCS0067
  * Assignment : 02 - File Handling
  * Question   : Q4 - Heart Rate Cleaner
*/

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    
    ifstream inFile("heart_rate.txt");

   
    if (!inFile) {
        cout << "heart_rate.txt not found!" << endl;
        return 1;
    }

    int rate[100];
    int count = 0;       // Number of valid readings stored
    int bad = 0;         // Number of junk words skipped
    int x;
    char junk[50];
    int reason = 0;      // 1 = sentinel, 2 = EOF, 3 = array full

    
    while (true) {

        //blank 1
        if (count >= 100) {     //the array is full
            reason = 3;
            break;
        }

        if (inFile >> x) {

            // blank 2
            if (x == -1) {         // a number was read
                reason = 1;        // sentinel value
                break;
            }

            rate[count] = x;

            // Blank3
            count++;
        }

        // Blank 4
        else if (inFile.eof()) {     //nothing left in the file
            reason = 2;
            break;
        }

        else {
            //blank 5
            inFile.clear();           // a junk word
            inFile >> junk;
            bad++;
        }
    }
    inFile.close();     //close

    // TODO 1: Write valid readings to the output file
    ofstream outFile("clean_heart_rate.txt");

    for (int i = 0; i < count; i++) {
        outFile << rate[i] << endl;
    }

    outFile.close();

    // TODO 2: Display the number of readings and junk words
    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    // TODO 3: Display the required results
    if (count == 0) {
        cout << "No valid readings!" << endl;
    }
    else {
        int total = 0;
        int highest = rate[0];
        int above = 0;
        int alerts = 0;
        double average;

        // Calculate total and highest reading
        for (int i = 0; i < count; i++) {
            total = total + rate[i];

            if (rate[i] > highest) {
                highest = rate[i];
            }
        }

        // Use double to calculate the decimal average
        average = (double)total / count;

        // Count readings above average and above 100
        for (int i = 0; i < count; i++) {
            if (rate[i] > average) {
                above++;
            }

            if (rate[i] > 100) {
                alerts++;
            }
        }

        cout << "Average: " << average << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << above << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    // TODO 4: Display why reading stopped
    cout << "Stopped because: ";

    if (reason == 1) {
        cout << "sentinel found" << endl;
    }
    else if (reason == 2) {
        cout << "end of file" << endl;
    }
    else if (reason == 3) {
        cout << "array full" << endl;
    }

    return 0;
}
