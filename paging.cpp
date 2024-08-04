#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

class Page {
public:
    int p1;
    int p2;
    int pageoffset;
    int address;

    Page() {
        p1 = 0;
        p2 = 0;
        address = 0;
        pageoffset = 0;
    }
};

struct Page2 {
    int index;
    int value;

    void init(int i, int v) {
        index = i;
        value = v;
    }
};

int main() {
    vector<Page2> PageTable;
    vector<Page2> PageDirectory;
    vector<Page2> PhysMemory;

    Page2 obj;
    vector<Page2>::iterator it;

    // P1 PAGE DIRECTORY
    obj.init(123, 1);
    PageDirectory.push_back(obj);
    obj.init(124, 2);
    PageDirectory.push_back(obj);
    obj.init(125, 3);
    PageDirectory.push_back(obj);
    obj.init(126, 4);
    PageDirectory.push_back(obj);
    obj.init(127, 5);
    PageDirectory.push_back(obj);
    obj.init(128, 6);
    PageDirectory.push_back(obj);

    obj.init(12, 1);
    PageTable.push_back(obj);
    obj.init(13, 2);
    PageTable.push_back(obj);
    obj.init(14, 3);
    PageTable.push_back(obj);
    obj.init(15, 4);
    PageTable.push_back(obj);
    obj.init(16, 5);
    PageTable.push_back(obj);
    obj.init(17, 6);
    PageTable.push_back(obj);

    // PHYSICAL MEMORY
    obj.init(1, 100);
    PhysMemory.push_back(obj);
    obj.init(2, 200);
    PhysMemory.push_back(obj);
    obj.init(3, 300);
    PhysMemory.push_back(obj);
    obj.init(4, 400);
    PhysMemory.push_back(obj);
    obj.init(5, 500);
    PhysMemory.push_back(obj);
    obj.init(6, 600);
    PhysMemory.push_back(obj);
    obj.init(7, 700);
    PhysMemory.push_back(obj);
    obj.init(8, 800);
    PhysMemory.push_back(obj);
    obj.init(9, 900);
    PhysMemory.push_back(obj);
    obj.init(10, 999);
    PhysMemory.push_back(obj);

    cout << "\nDisplaying the Page Directory: \n";
    cout << "Index" << '\t' << "Offset\n";
    for (it = PageDirectory.begin(); it != PageDirectory.end(); ++it) {
        cout << it->index << '\t' << it->value << endl;
    }

    cout << "\nDisplaying the Page Table: \n";
    cout << "Index" << '\t' << "Offset\n";
    for (it = PageTable.begin(); it != PageTable.end(); ++it) {
        cout << it->index << '\t' << it->value << endl;
    }

    cout << "\nDisplaying the Physical Memory: \n";
    cout << "Index" << '\t' << "Offset\n";
    for (it = PhysMemory.begin(); it != PhysMemory.end(); ++it) {
        cout << it->index << '\t' << it->value << endl;
    }

    Page logicaladdress;
    int pagesize = 4;

    cout << "\nEnter the Logical Address: ";
    cin >> logicaladdress.address;

    cout << "\n\nExtracting the offset: ";
    logicaladdress.pageoffset = logicaladdress.address % 1000;
    cout << logicaladdress.pageoffset;

    // Extract the middle three digits
    cout << "\n\nExtracting p1: ";
    logicaladdress.p1 = (logicaladdress.address / 1000) % 1000;
    cout << logicaladdress.p1;

    std::string numberStr = std::to_string(logicaladdress.address);
    // Extract the first two digits
    cout << "\n\nExtracting p2: ";
    std::string firstTwoDigits = numberStr.substr(0, 2);
    logicaladdress.p2 = std::stoi(firstTwoDigits);
    cout << logicaladdress.p2;

    int p1offset = 0;

    for (it = PageDirectory.begin(); it != PageDirectory.end(); ++it) {
        if (it->index == logicaladdress.p1) {
            cout << "\n\nThe entry corresponding to P1 is found";
            cout << "\nThe value at this index is: " << it->value;
            p1offset = it->value;
            break;
        }
    }

    int p2offset = 0;

    for (it = PageTable.begin(); it != PageTable.end(); ++it) {
        if (it->index == logicaladdress.p2 + p1offset) {
            cout << "\n\nThe entry corresponding to P2 is found";
            cout << "\nThe value at this index is: " << it->value;
            p2offset = it->value;
            break;
        }
    }

    int physval = 0;
    for (it = PhysMemory.begin(); it != PhysMemory.end(); ++it) {
        if (it->index == p2offset) {
            cout << "\n\nThe entry corresponding to Physical Memory is found";
            cout << "\nThe value at this index is: " << it->value;
            physval = it->value;
            break;
        }
    }

    cout << "\nThe physical address generated is: " << physval + logicaladdress.pageoffset;

    return 0;
}
