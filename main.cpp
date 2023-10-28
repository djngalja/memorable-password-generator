#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    Generator g;

    /////////// TEST ///////////

    for (std::string str: g.m_input_vector) std::cout << str << std::endl;

    std::cout << 0 << std::endl;
    g.GeneratePassword(0);

    std::cout << 5 << std::endl;
    g.GeneratePassword(5);

    std::cout << 10 << std::endl;
    g.GeneratePassword(10);

    std::cout << 30 << std::endl;
    g.GeneratePassword(30);


    system("pause");
    return 0;
}
