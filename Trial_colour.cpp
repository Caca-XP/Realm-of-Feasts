#include <iostream>
#include <windows.h>

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    // try all colours
    for (int i = 0; i < 16; i++) {
        setColor(i);
        cout << "Colour " << i << endl;
    }
}
