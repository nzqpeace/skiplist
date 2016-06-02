# skiplist
A skiplist written by cpp

# Usage
```cpp
#include <iostream>
#include "skiplist.hpp"

using namespace std;

int main() {
    Skiplist<int> sl;
    sl.Insert(3);
    cout << "length: " << sl.size() << " level: " << sl.level() << endl;

    sl.Insert(5);
    cout << "length: " << sl.size() << " level: " << sl.level() << endl;

    sl.Insert(8);
    cout << "length: " << sl.size() << " level: " << sl.level() << endl;

    sl.Insert(4);
    cout << "length: " << sl.size() << " level: " << sl.level() << endl;

    // traverse
    Skiplist<int>::Node* p = sl.first()->level[0].forward;
    while(p){
        cout << p->value << endl;
        p = p->level[0].forward;
    }

    return 0;
}
```
