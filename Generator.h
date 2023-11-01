#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Generator
{
        std::string m_input_string;
        std::vector<std::string> m_input_vector;
        std::vector<std::string> m_temp_vector;

        std::string GetInput();
        std::vector<std::string> SplitInput();
        void ShuffleVector();
        void ResizeVector(int length);
        void CopyVector(std::vector<std::string> &temp_vector, int length);
        bool ContainsDigit();

    public:
        Generator();
        std::string GeneratePassword(int length);
};

#endif // GENERATOR_H
