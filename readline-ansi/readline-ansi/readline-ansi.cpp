// readline-ansi.cpp: 定义应用程序的入口点。
//

#include "readline-ansi.h"

class Console {
public:
    void moveCursorLeft(int n) {
        if (n > 0) {
            std::cout << "\033[" << n << "D";
            std::cout.flush();
        }
    }

    void moveCursorRight(int n) {
        if (n > 0) {
            std::cout << "\033[" << n << "C";
            std::cout.flush();
        }
    }

    void setColor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
};

int main() {
    Console console;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD originalColorAttrs;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    originalColorAttrs = consoleInfo.wAttributes;

    console.setColor(10); // 设置为亮绿色

    std::string input;
    while (true) {
        char ch = std::cin.get();

        if (ch == '\n') {
            break;
        }

        if (ch == '\033') { // ANSI escape sequence
            std::cin.get(); // Read [
            char command = std::cin.get();

            if (command == 'D') { // Left arrow
                console.moveCursorLeft(1);
            }
            else if (command == 'C') { // Right arrow
                console.moveCursorRight(1);
            }
        }
        else {
            input += ch;
            std::cout << ch;
            std::cout.flush();
        }
    }

    console.setColor(originalColorAttrs); // 恢复原来的颜色

    std::cout << "\nInput: " << input << std::endl;

    return 0;
}