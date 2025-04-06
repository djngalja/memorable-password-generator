#include "Generator.h"

Generator::Generator() : m_input_vector{}, m_length{} {
    m_input_vector = get_input();
    m_length = get_len();
}

void Generator::SetInput() {
    m_input_vector = get_input();
}

void Generator::SetLength() {
    m_length = get_len();
}

bool has_letter(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        for (char c : str) {
            if (isalpha(c)) { return true; }
        }
    }
    return false;
}

bool has_up_case(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        if (has_up_case(str)) { return true; }
    }
    return false;
}

bool has_low_case(const std::vector<std::string>& vec) {
    for (const std::string& str : vec) {
        if (has_low_case(str)) { return true;}
    }
    return false;
}

bool has_low_case(const std::string& str) {
    for (char c : str) {
        if (islower(c)) { return true; }
    }
    return false;
}

bool has_char(const std::vector<std::string>& vec, char c) {
    for (const std::string& str : vec) {
        for (char i : str) {
            if (i == c) { return true; }
        }
    }
    return false;
}

bool has_sp_char(const std::string& sp_chars, const std::vector<std::string>& vec) {
    for (const std::string& str : vec) {
        if (has_sp_char(sp_chars, str)) { return true; }
    }
    return false;
}

bool has_sp_char(const std::string& sp_chars, const std::string& str) {
    for (char c : sp_chars) {
        if (str.find(c) != std::string::npos) {
                return true;
        }
    }
    return false;
}

void add_digit_or_letters(std::vector<std::string>& vec, bool add_letters) {
    std::map<char, char> replacements =
    { {'b', '6'},{'q', '9'},{'S', '5'},{'l', '1'},{'O', '0'} };
    for (const auto& i : replacements) {
        if (has_char(vec, i.first)) { // TODO: combine this f with v
            for (std::string& str : vec) {
                for (char& c : str) {
                    if (c == i.first) { c = i.second; }
                }
            }
            // only 1 character replaced so that password remains human-readable
            break;
        }
    }
    if (add_letters) {
        for (const auto& i : replacements) {
            if (has_char(vec, i.second)) {
                for (std::string& str : vec) {
                    for (char& c : str) {
                        if (c == i.second) { c = i.first; }
                    }
                }
            }
        }

    }
}

void add_low_or_up_case(std::vector<std::string>& vec, bool add_up) {
    if (add_up) {
        for (auto& str: vec) {
            for (char& c: str) {
                // probability is only 33% so that password is easier to memorise
                if ((rand()%100) < 33) { c = toupper(c); }
            }
        }
    } else {
        for (auto& str: vec) {
            for (char& c: str) {
                if ((rand()%100) < 33) { c = tolower(c); }
            }
        }
    }
}

char rand_sp_char(const std::string& sp_chars) {
    return sp_chars[rand()%sp_chars.size()];
}

char rand_low_case() {
    return (char)(rand() % 26 + 97);
}

char rand_up_case() {
    return (char)(rand() % 26 + 65);
}

char rand_digit() {
    return (char)(rand() % 10 + 48);
}

char rand_char(const std::string& sp_chars) {
    int b = rand() % 4;
    switch (b) {
        case 0: return rand_digit();
        case 1: return rand_up_case();
        case 2: return rand_low_case();
        default: return rand_sp_char(sp_chars);
    }
}

char add_char(const std::string& sp_chars, const std::string& str,
              const std::vector<std::string>& vec, bool last) {
    if (last) {
        if (!has_sp_char(sp_chars, str)) return rand_sp_char(sp_chars);
        else if (!has_digit(str)) return rand_digit();
        else if (!has_up_case(str)) return rand_up_case();
        else if (!has_low_case(str)) return rand_low_case();
        else return rand_char(sp_chars);
    }
    else {
        if (!(has_sp_char(sp_chars, str) || has_sp_char(sp_chars, vec))) return rand_sp_char(sp_chars);
        else if (!(has_digit(str) || has_digit(vec))) return rand_digit();
        else if (!(has_up_case(str) || has_up_case(vec))) return rand_up_case();
        else if (!(has_low_case(str) || has_low_case(vec))) return rand_low_case();
        else return rand_char(sp_chars);
    }
}

std::string join_vec(const std::string& sp_chars, const std::vector<std::string>& vec, std::size_t len) {
    std::string password;
    for (const std::string& str : vec) {
        password += str + add_char(sp_chars, password, vec);
    }
    if (password.size() != len) {
        password += add_char(sp_chars, password, vec, true);
    }
    return password;
}

void replace_char(std::string& str, char c) {
    int digit_cnt {};
    int low_cnt {};
    int up_cnt {};
    int sp_cnt {};
    for (char& ch : str) {
        if (isdigit(ch)) digit_cnt++;
        else if (islower(ch)) low_cnt++;
        else if (isupper(ch)) up_cnt++;
        else sp_cnt++;
        if (digit_cnt == 2 || low_cnt == 2 || up_cnt == 2 || sp_cnt == 2) {
            ch = c;
            break;
        }
    }
}

void final_check(const std::string& sp_chars, std::string& str) {
    if (!has_digit(str)) {
        replace_char(str, rand_digit());
    }
    if (!has_low_case(str)) {
        replace_char(str, rand_low_case());
    }
    if (!has_up_case(str)) {
        replace_char(str, rand_up_case());
    }
    if (!has_sp_char(sp_chars, str)) {
        replace_char(str, rand_sp_char(sp_chars));
    }
}

void Generator::GeneratePassword() // TODO: return type -> string
{
    std::vector<std::string> vec_copy {m_input_vector};
    shuffle_vec(vec_copy);
    resize_vec(m_length, vec_copy);
    if (!has_digit(vec_copy)) add_digit_or_letters(vec_copy);
    if (!has_letter(vec_copy)) add_digit_or_letters(vec_copy, true);
    if (!has_up_case(vec_copy)) add_low_or_up_case(vec_copy, true);
    if (!has_low_case(vec_copy)) add_low_or_up_case(vec_copy);
    std::string password = join_vec(m_special_chars, vec_copy, m_length);
    final_check(m_special_chars, password);
    std::cout << "\nPassword: " << password << "\n\n";
}

void resize_vec_recur(const std::vector<std::string>& vec_copy, std::size_t len, std::vector<std::string>& temp_vec) {
    std::size_t new_len {};
    for (std::string str: vec_copy)
    {
        new_len += str.size()+1;
        if (new_len < len) temp_vec.push_back(str);
        else if (new_len == len)
        {
            temp_vec.push_back(str);
            break;
        }
        else // new_len > len
        {
            for (std::size_t i=0; i<new_len-len; i++) // TODO: does this have to be a loop?
                if (!str.empty()) str.pop_back();
            if (!str.empty()) temp_vec.push_back(str);
            break;
        }
    }
    if (new_len < len) resize_vec_recur(vec_copy, len-new_len, temp_vec);
}

void resize_vec(std::size_t len, std::vector<std::string>& vec_copy) {
    std::vector<std::string> temp_vec;
    resize_vec_recur(vec_copy, len, temp_vec);
    vec_copy = temp_vec;
}

void shuffle_vec(std::vector<std::string>& vec) {
    static std::random_device rd;
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

bool has_digit(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        if (has_digit(str)) { return true; }
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
    shuffle_vec(questions); // to output questions in random order
    std::vector<std::string> input;
    for (int i=0; i<3; i++) {
        std::cout << i+1 << ". " << questions[i] << "\n\t";
        std::string str;
        getline(std::cin, str);
        split_input(str, input);
    }
    return input;
}

void split_input(const std::string& str, std::vector<std::string>& vec) {
    std::istringstream line(str);
    for (std::string str2; getline(line, str2, ' ');) {
        if (!str2.empty()) {
            vec.push_back(str2);
        }
    }
}

std::size_t get_len() {
    std::size_t len {};
    std::cout << "Enter password length: ";
    std::cin >> len; // TODO: input check
    return len;
}
