#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    std::cout << "GENERATE STRONG AND EASY-TO-REMEBER PASSWORDS\n\n";
    Generator g;
    g.GeneratePassword();

    int option {};
    do
    {
        std::cout << "\t[0] Exit\n";
        std::cout << "\t[1] Generate new password\n";
        std::cout << "\t[2] Change password length\n";
        std::cout << "\t[3] Change input\n";

        std::cin >> option;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            option = 4;
        }

        switch (option)
        {
        case 0: break;
        case 1:
            {
                g.GeneratePassword();
                break;
            }
        case 2:
            {
                g.SetLength();
                g.GeneratePassword();
                break;
            }
        case 3:
            {
                std::cin.ignore(10000, '\n');
                g.SetInput();
                g.GeneratePassword();
                break;
            }
        default:
            {
                std::cout << "Invalid input. Enter a number between 0 and 3.\n";
                break;
            }
        }

    }
    while (option != 0);

    return 0;
}
