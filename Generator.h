#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Generator
{
        std::string GetInput();
        std::vector<std::string> SplitInput();
    public:
        std::string m_input_string;
        std::vector<std::string> m_input_vector;

        Generator();

};

#endif // GENERATOR_H
