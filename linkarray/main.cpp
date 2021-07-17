// #define DEBUG
// #define WARNING
#include "linkarray.h"

using namespace std;
using namespace neduck;

int main() {
    LinkArray<int> arr({1, 2, 3, 4, 5});
    LinkArray<const char*> arr2({"first", "second", "third", "fourth"});

    cout << arr[0] << endl;                     // 1
    arr[2] = 30;                                // -> {1, 2, 30, 4, 5}

    arr.insertAt(0, 40);                        // -> {1, 2, 30, 40, 4, 5}
    arr.insertAt(6, {50, 60, 70});              // -> {1, 2, 30, 40, 4, 5, 50, 60, 70}
    arr.insertAt(0, vector<int>({10, 20, 30})); // -> {10, 20, 30, 1, 2, 30, 40, 4, 5, 50, 60, 70}

    arr.destroyAt(5);                           // -> {10, 20, 30, 1, 2,     40, 4, 5, 50, 60, 70}
    arr.destroyAt(3, 4);                        // -> {10, 20, 30,                  5, 50, 60, 70}
    arr.destroy(50);                            // -> {10, 20, 30,                  5,     60, 70}

    cout << arr.find(5) << endl;                // 3
    cout << arr.size() << endl;                 // 6
    arr.print();                                // {10, 20, 30, 5, 60, 70}
    
    for (LinkArray<int>::iterator iter = arr.begin(); iter != arr.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;                               // 10 20 30 5 60 70

    for (LinkArray<int>::reverse_iterator iter = arr.rbegin(); iter != arr.rend(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;                               // 70 60 5 30 20 10

    return 0;
}