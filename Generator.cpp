#include "Generator.h"

Generator::Generator()
{
    m_input_string = GetInput();
    m_input_vector = SplitInput();
}

std::string Generator::GetInput()
{
    std::vector<std::string> questions
    {
        "What's your cellphone wallpaper?",
        "What's an unusual skill you have?",
        "What's your favourite animal?",
        "What book do you own but have never read?",
        "What's your biggest pet peeve?",
        "What's the last song you listened to?",
        "What's the most used emoji on your phone?"
    };
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


bool Generator::ContainsDigits()
{
    for (std::string str: m_temp_vector)
        for (char c: str)
            if (isdigit(c)) return 1;
    return 0;
}

bool Generator::ContainsLetters()
{
    for (std::string str: m_temp_vector)
        for (char c: str)
            if (isalpha(c)) return 1;
    return 0;
}

bool Generator::ContainsUpperCase()
{
    for (std::string str: m_temp_vector)
        for (char c: str)
            if (isupper(c)) return 1;
    return 0;
}

bool Generator::ContainsLowerCase()
{
    for (std::string str: m_temp_vector)
        for (char c: str)
            if (islower(c)) return 1;
    return 0;
}

bool Generator::ContainsChar(char c)
{
    for (std::string str: m_temp_vector)
        for (char i: str)
            if (i==c) return 1;
    return 0;
}

void Generator::AddDigitsOrLetters(bool add_letters)
{
    std::map<char, char> replacements =
    {
        {'b', '6'},{'q', '9'},{'S', '5'},{'l', '1'},{'O', '0'}
    };
    for (const auto &i: replacements)
        if (ContainsChar(i.first))
        {
            for (std::string &str: m_temp_vector)
                for (char &c: str)
                    if (c == i.first) c = i.second;
            break; // only 1 character replaced so that password remains human-readable
        }
    if (add_letters)
        for (const auto &i: replacements)
            if (ContainsChar(i.second))
                for (std::string &str: m_temp_vector)
                    for (char &c: str)
                        if (c == i.second) c = i.first;
}

void Generator::AddLowerOrUpperCase(bool add_upper)
{
    if (add_upper)
    {
        for (std::string &str: m_temp_vector)
            for (char &c: str)
                if ((rand()%100) < 33) c = toupper(c); // probability is only 33% so that password is easier to memorise
    }
    else
        for (std::string &str: m_temp_vector)
            for (char &c: str)
                if ((rand()%100) < 33) c = tolower(c);
}

std::string Generator::GeneratePassword(int length)
{
    m_temp_vector = m_input_vector;
    ShuffleVector();
    ResizeVector(length);
    if (!ContainsDigits()) AddDigitsOrLetters();
    if (!ContainsLetters()) AddDigitsOrLetters(true);
    if (!ContainsUpperCase()) AddLowerOrUpperCase(true);
    if (!ContainsLowerCase()) AddLowerOrUpperCase();
    //TODO
    for (std::string str: m_temp_vector) std::cout << str << std::endl; // TEST
    std::string password;
    return password;
}


