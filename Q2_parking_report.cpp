
/*
 * Name       : Khadija Tul Kubra
 * Reg No     : L1S26BSCS0067
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("parking.txt");

    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;

    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    ofstream outFile("receipts.txt");

    outFile << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[30], longestPlate[30];
    char type;
    char inTime[10], outTime[10];

    char plates[30][30];
    int minutesList[30], fees[30];
    int count = 0, cars = 0, bikes = 0;
    int totalCollected = 0, longest = -1;

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    while (count < 30 &&
        inFile >> plate >> type >> inTime >> outTime) {

        int inHour, inMinute, outHour, outMinute;

        inHour = (inTime[0] - '0') * 10 + (inTime[1] - '0');
        inMinute = (inTime[3] - '0') * 10 + (inTime[4] - '0');

        outHour = (outTime[0] - '0') * 10 + (outTime[1] - '0');
        outMinute = (outTime[3] - '0') * 10 + (outTime[4] - '0');

        int start = inHour * 60 + inMinute;
        int finish = outHour * 60 + outMinute;
        int minutes = finish - start;

        int hoursCharged = (minutes + 59) / 60;

        if (hoursCharged == 0) {
            hoursCharged = 1;
        }

        int fee;
        char vehicleName[10];

        if (type == 'C') {
            fee = hoursCharged * 100;
            cars++;
            // FIXED: car ka naam output mein Car hona chahiye.
            vehicleName[0] = 'C';
            vehicleName[1] = 'a';
            vehicleName[2] = 'r';
            vehicleName[3] = '\0';
        }
        else {
            fee = hoursCharged * 40;
            bikes++;
            vehicleName[0] = 'B';
            vehicleName[1] = 'i';
            vehicleName[2] = 'k';
            vehicleName[3] = 'e';
            vehicleName[4] = '\0';
        }

        int actualHours = minutes / 60;
        int actualMinutes = minutes % 60;

        cout << plate << " " << vehicleName << " "
            << actualHours << " h " << actualMinutes
            << " min Fee: " << fee << endl;

        outFile << plate << " " << fee << endl;

        int i = 0;
        while (plate[i] != '\0') {
            plates[count][i] = plate[i];
            i++;
        }
        plates[count][i] = '\0';

        minutesList[count] = minutes;
        fees[count] = fee;

        totalCollected += fee;

        if (minutes > longest) {
            longest = minutes;

            i = 0;
            while (plate[i] != '\0') {
                longestPlate[i] = plate[i];
                i++;
            }
            longestPlate[i] = '\0';
        }

        count++;
    }

    inFile.close();
    outFile.close();

    if (count == 0) {
        cout << "Vehicles: 0" << endl;
        cout << "Cars: 0 Bikes: 0" << endl;
        cout << "Total collected: 0" << endl;
        cout << "Longest stay: None" << endl;
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " ("
        << longest / 60 << " h " << longest % 60
        << " min)" << endl;

    return 0;
}
