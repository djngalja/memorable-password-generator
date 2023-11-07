#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>

class Generator
{
        std::string m_input_string;
        std::vector<std::string> m_input_vector;
        std::vector<std::string> m_temp_vector;
        const std::string m_special_chars = "'-!\"#\$%&()*,./:;?@[]^_`{|}~+<=>";

        std::string GetInput();
        std::vector<std::string> SplitInput();
        void ShuffleVector();
        void ResizeVector(int length);
        void CopyVector(std::vector<std::string> &temp_vector, int length);
        bool ContainsDigits();
        bool ContainsDigits(const std::string &str);
        bool ContainsLetters();
        bool ContainsUpperCase();
        bool ContainsUpperCase(const std::string &str);
        bool ContainsLowerCase();
        bool ContainsLowerCase(const std::string &str);
        bool ContainsChar(char c);
        bool ContainsSpecialChar();
        bool ContainsSpecialChar(const std::string &str);
        void AddDigitsOrLetters(bool add_letters = false);
        void AddLowerOrUpperCase(bool add_upper = false);
        char RandomSpecialChar();
        char RandomLowerCase();
        char RandomUpperCase();
        char RandomDigit();

    public:
        Generator();
        std::string GeneratePassword(int length);
};

#endif // GENERATOR_H
