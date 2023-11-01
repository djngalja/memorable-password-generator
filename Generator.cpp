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

    std::string input_string;
    std::string temp_string;
    int rand_index = 0;
    for (int i=0; i<3; i++) // output 3 random questions
    {
        rand_index = rand()%questions.size();
        std::cout << questions[rand_index] << std::endl;
        getline(std::cin, temp_string);
        input_string.append(temp_string);
        input_string.push_back(' ');
        questions.erase(questions.begin()+rand_index);
    }
    return input_string;
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

void Generator::ShuffleVector()
{
    std::string temp_string;
    int rand_index = 0;
    for (std::size_t i=0; i<m_temp_vector.size(); i++)
    {
        rand_index = rand()%m_temp_vector.size();
        temp_string = m_temp_vector[i];
        m_temp_vector[i] = m_temp_vector[rand_index];
        m_temp_vector[rand_index] = temp_string;
    }
}

void Generator::ResizeVector(int length)
{
    std::vector<std::string> temp_vector;
    CopyVector(temp_vector, length);
    m_temp_vector.assign(temp_vector.begin(), temp_vector.end());
}

void Generator::CopyVector(std::vector<std::string> &temp_vector, int length)
{
    int temp_len = 0;
    for (std::string str: m_temp_vector)
    {
        temp_len += str.size()+1;
        if (temp_len < length) temp_vector.push_back(str);
        else if (temp_len == length)
        {
            temp_vector.push_back(str);
            break;
        }
        else // temp_len > length
        {
            for (int i=0; i<temp_len-length-1; i++)
                str.pop_back();
            temp_vector.push_back(str);
            break;
        }
    }
    if (temp_len < length) CopyVector(temp_vector, length-temp_len);
}


bool Generator::ContainsDigit()
{
    for (std::string str: m_temp_vector)
        for (char c: str)
            if (isdigit(c)) return 1;
    return 0;
}


std::string Generator::GeneratePassword(int length)
{
    m_temp_vector = m_input_vector;
    ShuffleVector();
    ResizeVector(length);
    for (std::string str: m_temp_vector) std::cout << str << std::endl; // TEST
    std::cout << "Contains digits: " << ContainsDigit() << std::endl; // TEST
    // TODO
    std::string password;
    return password;
}


