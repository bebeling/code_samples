#include "list.h"
#include <iostream>
#include <stdexcept>

using namespace std;


/* main()
 * ------
 * Runs an interactive test of the mylist_arr<int> class
 */

int main()
{
    mylist_arr<int> list;
    int* data;             // pointer to receive item popped from the list
    const int* cdata;      // const pointer to peek at item from the list
    int input;             // value of integer to put in the list
    int menu = 1;          // menu selection value

    while (menu != 0) {
        // print the menu options
        cout << "\n Options:\n";
        cout << " 1. empty()\n 2. size()\n 3. clear()\n";
        cout << " 4. front()\n 5. back()\n 6. push_front()\n 7. push_back()\n";
        cout << " 8. pop_front()\n 9. pop_back()\n";
        cout << " 0. Quit\n\n";
        cout << " Please make a selection: ";
        cin >> menu;
        cout << "\n\n\n   ";

        // handle the user's input
        switch (menu) {
            case 1:
                if (list.empty())
                    cout << "List is empty\n";
                else
                    cout << "List has contents\n";
                break;
            case 2:
                cout << "List has " << list.size() << " elements\n";
                break;
            case 3:
                list.clear();
                cout << "List cleared\n";
                break;
            case 4:
                try {
                    cdata = list.front();
                }
                catch (out_of_range &e) {
                    cout << "Exception: list is empty\n";
                    break;
                }
                cout << "Fist element is: " << *cdata << "\n";
                break;
            case 5:
                try {
                    cdata = list.back();
                }
                catch (out_of_range &e) {
                    cout << "Exception: list is empty\n";
                    break;
                }
                cout << "Last element is: " << *cdata << "\n";
                break;
            case 6:
                cout << "Integer? ";
                cin >> input;
                list.push_front(input);
                break;
            case 7:
                cout << "Integer? ";
                cin >> input;
                list.push_back(input);
                break;
            case 8:
                try {
                    data = list.pop_front();
                }
                catch (out_of_range &e) {
                    cout << "Exception: list is empty\n";
                    break;
                }
                cout << "Removed " << *data << " from list\n";
                delete data;
                break;
            case 9:
                try {
                    data = list.pop_back();
                }
                catch (out_of_range &e) {
                    cout << "Exception: list is empty\n";
                    break;
                }
                cout << "Removed " << *data << " from list\n";
                delete data;
                break;
            case 0:    // ignore, but 0 value will terminate while loop
                break;
            default:
                cout << "Invalid input\n";
                break;
        }

        cout << "\n\n";
    }

    return 0;
}

