#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Generator
{
        std::string m_input_string;

        std::string GetInput();
        std::vector<std::string> SplitInput();
        void ShuffleVector(std::vector<std::string> &vec);
        void ResizeVector(std::vector<std::string> &vec, int length);
        void CopyVector(
                        std::vector<std::string> &vec,
                        std::vector<std::string> &temp_vector,
                        int length
                        );

    public:

        std::vector<std::string> m_input_vector;

        Generator();
        std::string GeneratePassword(int length);

};

#endif // GENERATOR_H
