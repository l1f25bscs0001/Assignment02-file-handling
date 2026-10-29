/*
 * Name       : Student Name
 * Reg No     : L1F24BSCS0081
 * Assignment : 02 - File Handling
 * Question   : Q4 - Heart Rate Cleaner
 */

/*
 * ===== NOTES (how this program works) =====
 * Purpose : Reads heart_rate.txt, keeps valid readings, skips junk words,
 *           stops at -1, end of file, or when 100 readings are stored.
 * Key idea: a failed read stays failed until inFile.clear() is called;
 *           check eof() first so end of file is not mistaken for junk.
 *
 * Blanks: (1) count == 100  (2) x == -1  (3) count++
 *         (4) inFile.eof()  (5) inFile.clear()
 *
 * INPUT FILE : heart_rate.txt
 *   70 90 err 80
 *   110 x9 60 100
 *   -1 95
 *
 * SCREEN OUTPUT:
 *   Valid readings: 6
 *   Junk skipped: 2
 *   Average: 85
 *   Highest: 110
 *   Above average: 3
 *   Alerts (above 100): 1
 *   Stopped because: sentinel found
 *
 * OUTPUT FILE clean_heart_rate.txt: 70 90 80 110 60 100 (one per line)
 *
 * MORE EXAMPLES:
 *   "abc 70 80 xyz" -> 2 valid, 2 junk, Average 75, Highest 80,
 *                      Above average 1, Alerts 0, end of file
 *   "err junk"      -> 0 valid, 2 junk, No valid readings!, end of file
 *   (empty file)    -> 0 valid, 0 junk, No valid readings!, end of file
 * ERROR: file missing -> "heart_rate.txt not found!"
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
    int count = 0;      // number of valid readings stored in rate[]
    int bad = 0;        // number of junk words skipped
    int x;
    char junk[50];
    int reason = 0;     // 1 = sentinel found, 2 = end of file, 3 = array full

    while (true) {
        if (count == 100) {                // the array is full
            reason = 3;
            break;
        }
        if (inFile >> x) {                 // a number was read
            if (x == -1) {                 // the sentinel value
                reason = 1;
                break;
            }
            rate[count] = x;
            count++;
        }
        else if (inFile.eof()) {           // nothing left in the file
            reason = 2;
            break;
        }
        else {                             // a junk word
            inFile.clear();
            inFile >> junk;
            bad++;
        }
    }
    inFile.close();

    // TODO 1
    ofstream out("clean_heart_rate.txt");
    for (int i = 0; i < count; i++)
        out << rate[i] << endl;
    out.close();

    // TODO 2
    cout << "Valid readings: " << count << endl;
    cout << "Junk skipped: " << bad << endl;

    // TODO 3
    if (count == 0) {
        cout << "No valid readings!" << endl;
    } else {
        int total = 0, highest = rate[0];
        for (int i = 0; i < count; i++) {
            total += rate[i];
            if (rate[i] > highest) highest = rate[i];
        }
        double avg = (double)total / count;
        int above = 0, alerts = 0;
        for (int i = 0; i < count; i++) {
            if (rate[i] > avg) above++;
            if (rate[i] > 100) alerts++;
        }
        cout << "Average: " << avg << endl;
        cout << "Highest: " << highest << endl;
        cout << "Above average: " << above << endl;
        cout << "Alerts (above 100): " << alerts << endl;
    }

    // TODO 4
    cout << "Stopped because: ";
    if (reason == 1) cout << "sentinel found" << endl;
    else if (reason == 2) cout << "end of file" << endl;
    else cout << "array full" << endl;

    return 0;
}
