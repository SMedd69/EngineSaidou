#include <Utilities/Logger.h>

#if defined(_WIN32) || defined(_WIN64)
void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
void setConsoleColor(int color)
{
    std::cout << "\033[" << color << "m";
}
#endif
