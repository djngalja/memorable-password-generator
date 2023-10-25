#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    Generator g;

    std::vector<std::string> vec = g.m_input_vector;
    for (std::string str: vec) std::cout << str << std::endl;

    system("pause");
    return 0;
}
