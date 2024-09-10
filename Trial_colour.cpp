#include <iostream>
#include <windows.h>

void setConsoleBackgroundColor(WORD backgroundColor) {
    // Get console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Calculate console size (total character cells)
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Set the starting point for writing
    COORD topLeft = {0, 0};
    DWORD charsWritten;

    // Fill the console with spaces and the background color
    FillConsoleOutputAttribute(hConsole, backgroundColor, consoleSize, topLeft, &charsWritten);
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &charsWritten);

    // Reset the cursor position
    SetConsoleCursorPosition(hConsole, topLeft);
}

int main() {
    // Background color code for white: BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
    WORD whiteBackground = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

    setConsoleBackgroundColor(whiteBackground);

    std::cout << "The entire console background is now white!" << std::endl;

    // You can change text color (here using black foreground with white background)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), whiteBackground | 0); // 0 for black text
    std::cout << "This text is black on a white background!" << std::endl;

    return 0;
}
