#include "Generator.h"

Generator::Generator()
{
    m_input_string = GetInput();
    m_input_vector = SplitInput();
}

std::string Generator::GetInput()
{
    std::vector<std::string> questions;
    questions.push_back("What's your cellphone wallpaper?");
    questions.push_back("What's an unusual skill you have?");
    questions.push_back("What's your favourite animal?");
    questions.push_back("What book do you own but have never read?");
    questions.push_back("What's your biggest pet peeve?");
    questions.push_back("What's the last song you listened to?");
    questions.push_back("What's the most used emoji on your phone?");

    std::string answers;
    for (int i=0; i<3; i++) // output 3 random questions
    {
        std::string temp_string;
        int rand_index = rand()%questions.size();
        std::cout << questions[rand_index] << std::endl;
        getline(std::cin, temp_string);
        answers.append(temp_string);
        answers.push_back(' ');
        questions.erase(questions.begin()+rand_index);
    }
    return answers;
}

std::vector<std::string> Generator::SplitInput()
{
    std::vector<std::string> input_vector;
    std::string temp_string;
    for (char c: m_input_string)
    {
        if (c != ' ')
            temp_string.push_back(c);
        if (c == ' ' && !temp_string.empty())
        {
            input_vector.push_back(temp_string);
            temp_string.clear();
        }
    }
    return input_vector;
}


