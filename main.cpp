#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    Generator g;

    /////////// TEST ///////////

    std::cout << 0 << std::endl;
    g.GeneratePassword(0);

    std::cout << 5 << std::endl;
    g.GeneratePassword(5);

    std::cout << 8 << std::endl;
    g.GeneratePassword(8);

    std::cout << 10 << std::endl;
    g.GeneratePassword(10);


    system("pause");
    return 0;
}
