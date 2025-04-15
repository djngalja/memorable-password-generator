#include "Generator.h"
#include <cassert>

#undef NDEBUG

void pswd::test() {
    const std::string sp_chars = R"( !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
    // Test pswd::final_check function
    {
        std::string str = "A!6!";
        final_check(sp_chars, str);
        assert(std::islower(str[3]));
    }
    // Test pswd::replace_char function
    {
        std::string str = "a";
        replace_char(str, '*');
        assert(str == "a");
    }
    {
        std::string str = "Aa6!Aa6!";
        replace_char(str, '*');
        assert(str == "Aa6!*a6!");
    }
}
