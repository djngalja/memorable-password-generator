#include "Generator.h"

void pswd::Generator::Test()
{
    for (int i=0; i<100; i++)
        if (!isdigit(rand_digit()))
        {
            std::cout << "function RandomDigit() failed" << std::endl;
            break;
        }

    for (int i=0; i<100; i++)
        if (!islower(rand_low_case()))
        {
            std::cout << "function RandomLowerCase() failed" << std::endl;
            break;
        }

    for (int i=0; i<100; i++)
        if (!isupper(rand_up_case()))
        {
            std::cout << "function RandomUpperCase() failed" << std::endl;
            break;
        }
/*
    for (int i=0; i<100; i++)
        if (isalnum(RandomSpecialChar()))
        {
            std::cout << "function RandomSpecialChar() failed" << std::endl;
            break;
        }
        */
}
