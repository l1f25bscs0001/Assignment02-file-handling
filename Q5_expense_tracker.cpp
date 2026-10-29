/*
 * Name       : Muhammad Tabish
 * Reg No     : L1F25BSCS0001
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

/*
 * ===== NOTES (how this program works) =====
 * Purpose : Menu-driven expense tracker. Data is kept in expenses.txt
 *           so it stays after the program is closed.
 * Options : 1 add (ios::app, amount must be > 0)
 *           2 show all (file re-opened each time) + total + largest
 *           3 total of one category (strcmp, case-sensitive)
 *           4 clear file (plain ofstream, closed straight away)
 *           5 exit (do...while loop ends)
 *           other number -> "Invalid choice!"
 *
 * NO INPUT FILE: the program creates expenses.txt itself.
 *
 * SAMPLE INPUTS TYPED BY USER (run 1):
 *   2 | 1 Food 450 | 1 Transport 1200 | 1 Food 0 | 1 Food 300 | 7 | 5
 * expenses.txt after run 1:
 *   Food 450
 *   Transport 1200
 *   Food 300
 *
 * SAMPLE INPUTS (run 2):
 *   2 -> lists 3 items, Total spent: 1950, Largest expense: Transport (1200)
 *   3 Food  -> Expenses in Food: 2 / Total for Food: 750
 *   3 Books -> No expenses found for Books
 *   4 -> All expenses cleared.   2 -> No expenses yet.   5 -> Goodbye!
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
        if (!(cin >> choice)) break;

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            } else {
                ofstream out("expenses.txt", ios::app);
                out << category << " " << amount << endl;
                out.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            ifstream in("expenses.txt");
            char cat[100][20];
            int amt[100];
            int n = 0;
            if (in) {
                while (n < 100 && in >> cat[n] >> amt[n]) n++;
                in.close();
            }
            if (n == 0) {
                cout << "No expenses yet." << endl;
            } else {
                int total = 0, big = 0;
                for (int i = 0; i < n; i++) {
                    cout << i + 1 << ". " << cat[i] << " " << amt[i] << endl;
                    total += amt[i];
                    if (amt[i] > amt[big]) big = i;
                }
                cout << "Total spent: " << total << endl;
                cout << "Largest expense: " << cat[big] << " (" << amt[big] << ")" << endl;
            }
        }
        else if (choice == 3) {
            char wanted[20], cat[20];
            int amt, count = 0, total = 0;
            cout << "Enter category: ";
            cin >> wanted;
            ifstream in("expenses.txt");
            if (in) {
                while (in >> cat >> amt) {
                    if (strcmp(cat, wanted) == 0) {
                        count++;
                        total += amt;
                    }
                }
                in.close();
            }
            if (count == 0) {
                cout << "No expenses found for " << wanted << endl;
            } else {
                cout << "Expenses in " << wanted << ": " << count << endl;
                cout << "Total for " << wanted << ": " << total << endl;
            }
        }
        else if (choice == 4) {
            ofstream out("expenses.txt");
            out.close();
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
