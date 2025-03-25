#include "Generator.h"

void Generator::Test()
{
    for (int i=0; i<100; i++)
        if (!isdigit(RandomDigit()))
        {
            std::cout << "function RandomDigit() failed" << std::endl;
            break;
        }

    for (int i=0; i<100; i++)
        if (!islower(RandomLowerCase()))
        {
            std::cout << "function RandomLowerCase() failed" << std::endl;
            break;
        }

    for (int i=0; i<100; i++)
        if (!isupper(RandomUpperCase()))
        {
            std::cout << "function RandomUpperCase() failed" << std::endl;
            break;
        }

    for (int i=0; i<100; i++)
        if (isalnum(RandomSpecialChar()))
        {
            std::cout << "function RandomSpecialChar() failed" << std::endl;
            break;
        }
}
