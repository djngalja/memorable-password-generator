#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    std::cout << "GENERATE STRONG AND EASY-TO-REMEBER PASSWORDS\n" << std::endl;
    Generator g;
    g.GeneratePassword();

    int choice = 0;
    do
    {
        std::cout << " 0. Exit\n 1. New password length\n 2. New questions" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 0: break;
        case 1:
            {
                g.GeneratePassword();
                break;
            }
        default:
            {
                std::cin.ignore();
                g.Reset();
                g.GeneratePassword();
            }
        }
    }
    while (choice != 0);


    system("pause");
    return 0;
}
