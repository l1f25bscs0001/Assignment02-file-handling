/*
 * Name       : Student Name
 * Reg No     : L1F24BSCS0081
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

/*
 * ===== NOTES (how this program works) =====
 * Purpose : Asks for a file name, shows every student, writes students
 *           with CGPA >= 3.50 to scholarship.txt, prints a summary.
 * Note    : File name is read with cin.getline so folder names with
 *           spaces work (e.g. my files/class2.txt).
 *
 * INPUT FILE 1 : class1.txt
 *   6
 *   Ali Khan,3.65
 *   Sara Ahmed,3.92
 *   Usman Tariq,2.80
 *   Hina Malik,3.50
 *   Bilal Raza,3.10
 *   Ayesha Noor,3.92
 *
 * INPUT FILE 2 : my files/class2.txt
 *   4
 *   Zara Ali,3.50
 *   Omar Farooq,3.9
 *   Nida Khan,3.90
 *   Ali Raza,3.49
 *
 * SAMPLE RUN 1 (user types class1.txt):
 *   Enter the file name: class1.txt
 *   [Ali Khan] CGPA: 3.65  ... (one line per student)
 *   Students: 6
 *   Average CGPA: 3.48167
 *   Eligible for scholarship: 4
 *   Top student: Sara Ahmed (3.92)
 *   scholarship.txt: Ali Khan,3.65 / Sara Ahmed,3.92 / Hina Malik,3.5 / Ayesha Noor,3.92
 *
 * SAMPLE RUN 2 (user types my files/class2.txt):
 *   Students: 4, Average CGPA: 3.6975, Eligible: 3,
 *   Top student: Omar Farooq (3.9)
 *
 * SAMPLE RUN 3: class9.txt -> "Could not open class9.txt!"
 *
 * OTHER ERRORS: n > 30 -> "Too many students!"
 *   fewer records than n -> "Warning: only X of N records found."
 *   no record at all -> "No students found!"
 */


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    if (!(inFile >> n)) n = 0;
    inFile.ignore(100, '\n');
    if (n > 30) {
        cout << "Too many students!" << endl;
        return 1;
    }

    ofstream out("scholarship.txt");

    char name[30], topName[30] = "";
    double cgpa, sum = 0, top = -1;
    int read = 0, eligible = 0;

    while (read < n) {
        if (!inFile.getline(name, 30, ',')) break;
        if (!(inFile >> cgpa)) break;
        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;
        sum += cgpa;
        if (cgpa >= 3.5) {
            out << name << "," << cgpa << endl;
            eligible++;
        }
        if (cgpa > top) {
            top = cgpa;
            strcpy(topName, name);
        }
        read++;
    }
    inFile.close();
    out.close();

    if (read < n)
        cout << "Warning: only " << read << " of " << n << " records found." << endl;

    if (read == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << read << endl;
    cout << "Average CGPA: " << sum / read << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << top << ")" << endl;
    return 0;
}
