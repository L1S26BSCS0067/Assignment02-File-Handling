#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{

    char path[100];
    char name[30];
    char topName[30];

    int n;
    int count = 0;
    int eligible = 0;

    double cgpa;
    double total = 0;
    double average;
    double topCgpa = -1;

    cout << "Enter the file name: ";
    cin.getline(path, 100);
    //  open 
    ifstream inFile(path);

    // Check 
    if (!inFile)
    {
        cout << "Could not open " << path << "!";
        return 1;
    }
    cout << "Enter the file name: ";
    cin.getline(path, 100);
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30)
    {
        cout << "Too many students!";
        inFile.close();
        return 1;
    }

    //open
    ofstream outFile("scholarship.txt");

    
    while (count < n && inFile.getline(name, 30, ','))
    {
        //reading student gpa
        if (!(inFile >> cgpa))
        {
            break;
        }
        
        inFile.ignore(100, '\n');
        cout << "[" << name << "] CGPA: " << cgpa << endl;

        total = total + cgpa;
        if (cgpa >= 3.50)
        {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }

        
        if (cgpa > topCgpa)
        {
            topCgpa = cgpa;
            strcpy_s(topName, name);
        }
        count++;
    }
    if (count < n)
    {
        cout << "Warning: only " << count
            << " of " << n << " records found." << endl;
    }
    if (count == 0)
    {
        cout << "No students found!" << endl;
    }
    else
    {
        average = total / count;

        cout << "Students: " << count << endl;
        cout << "Average CGPA: " << average << endl;
        cout << "Eligible for scholarship: " << eligible << endl;
        cout << "Top student: " << topName
            << " (" << topCgpa << ")" << endl;
    }
    inFile.close();
    outFile.close();

    return 0;
}