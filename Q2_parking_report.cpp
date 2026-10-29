
/*
 * ===== NOTES (how this program works) =====
 * Purpose : Reads parking.txt, calculates fee of each vehicle,
 *           writes receipts.txt and prints a report.
 * Rules   : minutes = Out - In; hours charged = (minutes + 59) / 60
 *           (minimum 1 hour); Car = 100/hour, Bike = 40/hour.
 *           Date is read as integers so 09/10/2026 prints as 9/10/2026.
 *
 * INPUT FILE  : parking.txt
 *   09/10/2026
 *   Plate Type In Out
 *   LEA1234 C 08:15 10:45
 *   LHR552 B 09:00 09:40
 *   RIK77 C 09:30 13:30
 *   LEB908 B 10:05 12:20
 *   MNA4410 C 11:50 12:35
 *   LHR9001 C 13:00 17:10
 *
 * SCREEN OUTPUT:
 *   Parking report for 9/10/2026
 *   LEA1234 Car 2 h 30 min Fee: 300
 *   LHR552 Bike 0 h 40 min Fee: 40
 *   RIK77 Car 4 h 0 min Fee: 400
 *   LEB908 Bike 2 h 15 min Fee: 120
 *   MNA4410 Car 0 h 45 min Fee: 100
 *   LHR9001 Car 4 h 10 min Fee: 500
 *   Vehicles: 6
 *   Cars: 4 Bikes: 2
 *   Total collected: 1460
 *   Longest stay: LHR9001 (4 h 10 min)
 *
 * OUTPUT FILE : receipts.txt (overwritten every run)
 *   Receipts for 9/10/2026
 *   LEA1234 300 / LHR552 40 / RIK77 400 / LEB908 120 / MNA4410 100 / LHR9001 500
 *
 * ERRORS: file missing -> "parking.txt not found!"
 *         no vehicle lines -> report heading, then "No vehicles found!"
 */


#include <iostream>
#include <fstream>
#include <cstring>
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
    inFile.ignore(100, '\n');   // rest of line 1
    inFile.ignore(100, '\n');   // header line

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;
    ofstream out("receipts.txt");
    out << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], type, colon;
    int h1, m1, h2, m2;
    int count = 0, cars = 0, bikes = 0, total = 0;
    int longest = -1;
    char longPlate[15] = "";

    while (count < 30 && inFile >> plate >> type >> h1 >> colon >> m1 >> h2 >> colon >> m2) {
        int minutes = (h2 * 60 + m2) - (h1 * 60 + m1);
        int hours = (minutes + 59) / 60;
        if (hours == 0) hours = 1;
        int fee;
        if (type == 'C') {
            fee = hours * 100;
            cars++;
            cout << plate << " Car ";
        } else {
            fee = hours * 40;
            bikes++;
            cout << plate << " Bike ";
        }
        cout << minutes / 60 << " h " << minutes % 60 << " min Fee: " << fee << endl;
        out << plate << " " << fee << endl;
        total += fee;
        if (minutes > longest) {
            longest = minutes;
            strcpy(longPlate, plate);
        }
        count++;
    }
    inFile.close();
    out.close();

    if (count == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << longPlate << " (" << longest / 60 << " h " << longest % 60 << " min)" << endl;
    return 0;
}
