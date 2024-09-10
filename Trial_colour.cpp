#include <iostream>
#include <windows.h>

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to get the current text color
int getCurrentColor() {
    // Get the handle to the console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Structure to hold console buffer information
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get the current console screen buffer information
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // Extract and return the current text attribute (color)
        return csbi.wAttributes;
    }

    return -1; // Return -1 if getting the information fails
}

int main() {
    // try all colours
    for (int i = 0; i < 16; i++) {
        setColor(i);
        printf("This is colour %d\n", i);
    }
}
