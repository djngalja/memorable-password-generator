#include "Generator.h"
#include <cassert>

#undef NDEBUG

void pswd::test() {
    // Test pswd::resize_vec function
    {
        std::vector<std::string> vec = {"barbecue", "Salad"};
        resize_vec(14, vec);
        std::vector<std::string> vec2 = {"barbecue", "Sala"};
        assert(vec == vec2);
    }
    {
        std::vector<std::string> vec = {"barbecue", "Salad"};
        resize_vec(1, vec);
        std::vector<std::string> vec2 = {};
        assert(vec == vec2);
    }
    {
        std::vector<std::string> vec = {"barbecue", "Salad"};
        resize_vec(24, vec);
        std::vector<std::string> vec2 = {"barbecue", "Salad", "barbecue"};
        assert(vec == vec2);
    }
    // Test pswd::add_digit function
    {
        std::vector<std::string> vec = {"barbecue", "Salad"};
        add_digit(vec);
        std::vector<std::string> vec2 = {"6ar6ecue", "Salad"};
        assert(vec == vec2);
    }
    // Test pswd::add_letters function
    {
        std::vector<std::string> vec = {"123", "456", "798"};
        add_letters(vec);
        std::vector<std::string> vec2 = {"l23", "4Sb", "7q8"};
        assert(vec == vec2);
    }
    {
        std::vector<std::string> vec = {"5"};
        add_letters(vec);
        std::vector<std::string> vec2 = {"S"};
        assert(vec == vec2);
    }
    {
        std::vector<std::string> vec = {"7"};
        add_letters(vec);
        std::vector<std::string> vec2 = {"7"};
        assert(vec == vec2);
    }
    const std::string sp_chars = R"( !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
    // Test pswd::join_vec function
    {
        std::vector<std::string> vec = {"swimming", "spaghetti"};
        std::size_t len = 20;
        std::string str = join_vec(sp_chars, vec, len);
        assert(str.size() == len);
    }
    {
        std::vector<std::string> vec = {"swimming", "spaghetti"};
        std::size_t len = 19;
        std::string str = join_vec(sp_chars, vec, len);
        assert(str.size() == len);
    }
    // Test pswd::add_char function
    {
        std::string str = "Abc*";
        std::vector<std::string> vec {};
        char ch = add_char(sp_chars, str, vec, true);
        assert(std::isdigit(ch));
    }
    {
        std::string str = "8bc*";
        std::vector<std::string> vec {"def", "gh"};
        char ch = add_char(sp_chars, str, vec);
        assert(std::isupper(ch));
    }
    {
        std::string str = "*!=_";
        std::vector<std::string> vec {"def", "gh"};
        char ch = add_char(sp_chars, str, vec);
        assert(std::isdigit(ch));
    }
    // Test pswd::final_check function
    {
        std::string str = "A!6!";
        final_check(sp_chars, str);
        assert(std::islower(str[3]));
    }
    {
        std::string str = "A!a!";
        final_check(sp_chars, str);
        assert(std::isdigit(str[3]));
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
