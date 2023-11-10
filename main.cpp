#include "Generator.h"
#include <ctime>

int main()
{
    srand(time(NULL));

    Generator g;

    /////////// TEST ///////////

    std::cout << "Length = " << 0 << std::endl;
    g.GeneratePassword(0);

    std::cout << "Length = " << 1 << std::endl;
    g.GeneratePassword(1);

    std::cout << "Length = " << 2 << std::endl;
    g.GeneratePassword(2);

    std::cout << "Length = " << 3 << std::endl;
    g.GeneratePassword(3);

    std::cout << "Length = " << 4 << std::endl;
    g.GeneratePassword(4);

    std::cout << "Length = " << 5 << std::endl;
    g.GeneratePassword(5);

    std::cout << "Length = " << 6 << std::endl;
    g.GeneratePassword(6);

    std::cout << "Length = " << 7 << std::endl;
    g.GeneratePassword(7);

    std::cout << "Length = " << 15 << std::endl;
    g.GeneratePassword(15);

    /////////// TEST ///////////

    system("pause");
    return 0;
}
