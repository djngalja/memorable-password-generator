#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    std::cout << "GENERATE STRONG AND EASY-TO-REMEBER PASSWORDS\n" << std::endl;
    Generator g;
    g.GeneratePassword();

    int option = 0;
    do
    {
        std::cout << "\t[0] Exit" << std::endl;
        std::cout << "\t[1] Generate new password" << std::endl;
        std::cout << "\t[2] Change password length" << std::endl;
        std::cout << "\t[3] Change input" << std::endl;

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
                std::cout << "Invalid input. Enter a number between 0 and 3." << std::endl;
                break;
            }
        }

    }
    while (option != 0);

    return 0;
}
