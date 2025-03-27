#include "Generator.h"

Generator::Generator()
{
    m_input_vector = get_input();
    m_length = GetLength();
}

void Generator::SetInput()
{
    m_input_vector = get_input();
}

void Generator::SetLength()
{
    m_length = GetLength();
}

std::size_t Generator::GetLength()
{
    std::size_t length = 0;
    std::cout << "Enter password length: ";
    std::cin >> length;
    return length;
}

void Generator::ResizeVector()
{
    std::vector<std::string> temp_vector;
    CopyVector(temp_vector, m_length);
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
        if (has_digit(str)) return 1;
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
        if(has_up_case(str)) return 1;
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
        else if (!has_digit(str)) return RandomDigit();
        else if (!has_up_case(str)) return RandomUpperCase();
        else if (!ContainsLowerCase(str)) return RandomLowerCase();
        else return RandomChar();
    }
    else
    {
        if (!(ContainsSpecialChar(str) || ContainsSpecialChar())) return RandomSpecialChar();
        else if (!(has_digit(str) || ContainsDigits())) return RandomDigit();
        else if (!(has_up_case(str) || ContainsUpperCase())) return RandomUpperCase();
        else if (!(ContainsLowerCase(str) || ContainsLowerCase())) return RandomLowerCase();
        else return RandomChar();
    }
}

std::string Generator::JoinVector()
{
    std::string password;
    for (const std::string &str: m_temp_vector)
        password += str + AddChar(password);
    if (password.size() != m_length) password += AddChar(password, true);
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
    if (!has_digit(str)) ReplaceChar(str, RandomDigit());
    if (!ContainsLowerCase(str)) ReplaceChar(str, RandomLowerCase());
    if (!has_up_case(str)) ReplaceChar(str, RandomUpperCase());
    if (!ContainsSpecialChar(str)) ReplaceChar(str, RandomSpecialChar());
}

void Generator::GeneratePassword()
{
    m_temp_vector = m_input_vector;
    shuffle_vec(m_temp_vector);
    ResizeVector();
    if (!ContainsDigits()) AddDigitsOrLetters();
    if (!ContainsLetters()) AddDigitsOrLetters(true);
    if (!ContainsUpperCase()) AddLowerOrUpperCase(true);
    if (!ContainsLowerCase()) AddLowerOrUpperCase();
    std::string password = JoinVector();
    FinalCheck(password);
    std::cout << "\nPassword: " << password << "\n\n";
    //Test();
}

void shuffle_vec(std::vector<std::string>& vec) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
}

bool has_up_case(const std::string& str) {
    for (char c : str) {
        if (std::isupper(c)) { return true; }
    }
    return false;
}

bool has_digit(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) { return true; }
    }
    return false;
}

bool get_questions(const std::string& f_name, std::vector<std::string>& questions) {
    std::ifstream file(f_name);
    if (!file) {
        std::cout << "File <" << f_name << "> not found\n";
        return false;
    }
    for (std::string temp; getline(file, temp, '\n');) {
        questions.push_back(temp);
    }
    return true;
}

std::vector<std::string> get_input() {
    std::vector<std::string> questions;
    if (!get_questions("security_questions.txt", questions)) {
        // TODO
    }
    std::vector<std::string> vec;
    int rand_id {};
    for (int i=0; i<3; i++) { // output 3 random questions
        rand_id = rand()%questions.size();
        std::cout << i+1 << ". " << questions[rand_id] << "\n\t";
        split_input(vec);
        questions.erase(questions.begin() + rand_id);
    }
    return vec;
}

void split_input(std::vector<std::string>& vec) {
    std::string str;
    getline(std::cin, str, '\n');
    std::istringstream line(str);
    for (std::string str2; getline(line, str2, ' ');) {
        if (!str2.empty()) {
            vec.push_back(str2);
        }
    }
}
