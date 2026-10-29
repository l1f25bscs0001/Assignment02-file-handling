/*
 * Name       : Student Name
 * Reg No     : L1F24BSCS0081
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

/*
 * ===== NOTES (how this program works) =====
 * Purpose : Reads stock.txt, counts items, adds up total stock value,
 *           and appends items with quantity < 10 to reorder.txt.
 *
 * INPUT FILE  : stock.txt   (keep in same folder as this .cpp)
 *   Code Qty Price
 *   P101 25 120.5
 *   P102 6 80
 *   P103 40 15.25
 *   P104 3 999.99
 *   P105 9 45
 *
 * reorder.txt BEFORE running (old line is kept):
 *   P099 2
 *
 * SCREEN OUTPUT:
 *   Items: 5
 *   Total stock value: 7507.47
 *   Low stock items: 3
 *
 * reorder.txt AFTER running:
 *   P099 2
 *   P102 6
 *   P104 3
 *   P105 9
 *
 * ERROR: stock.txt missing -> "stock.txt not found!"
 * Tip: put reorder.txt back to its single original line before each test.
 */


#include <iostream>
// FIX 1: <fstream> was missing, so ifstream and ofstream were unknown (compile error)
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: the condition was reversed; the file is missing when !inFile is true
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: a plain ofstream erases old lines; ios::app adds new lines at the end
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: total was an int, so decimals were cut off; it must be a double
    double total = 0;

    // FIX 5: the first line (header) was never skipped, so the first read failed
    inFile.ignore(100, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            // FIX 6: endl was missing, so all reorder items joined on one line
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
