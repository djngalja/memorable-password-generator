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

void Generator::ResizeVector(std::size_t length)
{
    std::vector<std::string> temp_vector;
    CopyVector(temp_vector, length);
    m_temp_vector.assign(temp_vector.begin(), temp_vector.end());
}

void Generator::CopyVector(std::vector<std::string> &temp_vector, std::size_t length)
{
    std::size_t temp_len = 0;
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
            for (std::size_t i=0; i<temp_len-length; i++)
                if (!str.empty()) str.pop_back();
            if (!str.empty()) temp_vector.push_back(str);
            break;
        }
    }
    if (temp_len < length) CopyVector(temp_vector, length-temp_len);
}


bool Generator::ContainsDigits()
{
    for (std::string str: m_temp_vector)
        if (ContainsDigits(str)) return 1;
    return 0;
}

bool Generator::ContainsDigits(const std::string &str)
{
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
        if(ContainsUpperCase(str)) return 1;
    return 0;
}

bool Generator::ContainsUpperCase(const std::string &str)
{
    for (char c: str)
        if (isupper(c)) return 1;
    return 0;
}

bool Generator::ContainsLowerCase()
{
    for (std::string str: m_temp_vector)
        if (ContainsLowerCase(str)) return 1;
    return 0;
}

bool Generator::ContainsLowerCase(const std::string &str)
{
    for (char c: str)
        if (islower(c)) return 1;
    return 0;
}

bool Generator::ContainsChar(char c)
{
    for (std::string str: m_temp_vector)
        for (char i: str)
            if (i == c) return 1;
    return 0;
}

bool Generator::ContainsSpecialChar()
{
    for (std::string str: m_temp_vector)
        if (ContainsSpecialChar(str)) return 1;
    return 0;
}

bool Generator::ContainsSpecialChar(const std::string &str)
{
    for (char c: m_special_chars)
        if (str.find(c) != std::string::npos) return 1;
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
                if ((rand()%100) < 33) c = toupper(c);
                // probability is only 33% so that password is easier to memorise
    }
    else
        for (std::string &str: m_temp_vector)
            for (char &c: str)
                if ((rand()%100) < 33) c = tolower(c);
}

char Generator::RandomSpecialChar()
{
    return m_special_chars[rand()%m_special_chars.size()];
}

char Generator::RandomLowerCase()
{
    return (char)(rand() % 26 + 97);
}

char Generator::RandomUpperCase()
{
    return (char)(rand() % 26 + 65);
}

char Generator::RandomDigit()
{
    return (char)(rand() % 10 + 48);
}

char Generator::RandomChar()
{
    int b = rand() % 4;
    switch (b)
    {
    case 0: return RandomDigit();
    case 1: return RandomUpperCase();
    case 2: return RandomLowerCase();
    default: return RandomSpecialChar();
    }
}

char Generator::AddChar(const std::string &str, bool last)
{
    if (last)
    {
        if (!ContainsSpecialChar(str)) return RandomSpecialChar();
        else if (!ContainsDigits(str)) return RandomDigit();
        else if (!ContainsUpperCase(str)) return RandomUpperCase();
        else if (!ContainsLowerCase(str)) return RandomLowerCase();
        else return RandomChar();
    }
    else
    {
        if (!(ContainsSpecialChar(str) || ContainsSpecialChar())) return RandomSpecialChar();
        else if (!(ContainsDigits(str) || ContainsDigits())) return RandomDigit();
        else if (!(ContainsUpperCase(str) || ContainsUpperCase())) return RandomUpperCase();
        else if (!(ContainsLowerCase(str) || ContainsLowerCase())) return RandomLowerCase();
        else return RandomChar();
    }
}

void Generator::Test()
{
    for (std::string str: m_temp_vector) std::cout << str << std::endl;
    std::cout << "m_input_vector size: " << m_input_vector.size() << std::endl;
    std::cout << "m_temp_vector size: " << m_temp_vector.size() << std::endl;
    std::cout << "Random digit: " << RandomDigit() << std::endl;
    std::cout << "Random lowercase letter: " << RandomLowerCase() << std::endl;
    std::cout << "Random uppercase letter: " << RandomUpperCase() << std::endl;
    std::cout << "Random special char: " << RandomSpecialChar() << std::endl;
    std::cout << "Random char: " << RandomChar() << std::endl;
}

std::string Generator::JoinVector(std::size_t length)
{
    std::string password;
    for (const std::string &str: m_temp_vector)
        password += str + AddChar(password);
    if (password.size() != length) password += AddChar(password, true);
    return password;
}

void Generator::ReplaceChar(std::string &str, char c)
{
    int digit_count = 0, lower_count = 0, upper_count = 0, special_count = 0;
    for (char &ch: str)
    {
        if (isdigit(ch)) digit_count++;
        else if (islower(ch)) lower_count++;
        else if (isupper(ch)) upper_count++;
        else special_count++;
        if (digit_count == 2 || lower_count == 2 || upper_count == 2 || special_count == 2)
        {
            ch = c;
            break;
        }
    }
}

void Generator::FinalCheck(std::string &str)
{
    if (!ContainsDigits(str)) ReplaceChar(str, RandomDigit());
    if (!ContainsLowerCase(str)) ReplaceChar(str, RandomLowerCase());
    if (!ContainsUpperCase(str)) ReplaceChar(str, RandomUpperCase());
    if (!ContainsSpecialChar(str)) ReplaceChar(str, RandomSpecialChar());
}

std::string Generator::GeneratePassword(std::size_t length)
{
    m_temp_vector = m_input_vector;
    ShuffleVector();
    ResizeVector(length);
    if (!ContainsDigits()) AddDigitsOrLetters();
    if (!ContainsLetters()) AddDigitsOrLetters(true);
    if (!ContainsUpperCase()) AddLowerOrUpperCase(true);
    if (!ContainsLowerCase()) AddLowerOrUpperCase();
    std::string password = JoinVector(length);
    std::cout << "Preliminary password: " << password << std::endl; //TEST
    FinalCheck(password);
    std::cout << "Password: " << password << std::endl << std:: endl; //TEST
    //Test();
    return password;
}


