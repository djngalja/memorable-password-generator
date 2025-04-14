#include "Generator.h"

pswd::Generator::Generator() {
    get_input();
    get_len();
}

void pswd::Generator::get_input() {
    std::vector<std::string> questions;
    if (!get_questions("security_questions.txt", questions)) {
        return;
    }
    shuffle_vec(questions); // To output questions in random order
    std::vector<std::string> vec;
    for (int i=0; i<3; i++) {
        std::cout << i+1 << ". " << questions[i] << "\n\t";
        std::string str;
        getline(std::cin, str);
        if (!str.empty()) {
            split_input(str, vec);
        }
    }
    if (!vec.empty()) {
        m_input_vec = vec;
    }
}

void pswd::Generator::get_len() {
    std::cout << "Enter password length: ";
    int len {};
    std::cin >> len;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    if (len > 0) { m_len = len; }
}

void pswd::Generator::generate_password() {
    std::vector<std::string> vec_copy {m_input_vec};
    shuffle_vec(vec_copy);
    resize_vec(m_len, vec_copy);
    if (!has_digit(vec_copy)) {
        add_digit(vec_copy);
    }
    if (!has_letter(vec_copy)) {
        add_letters(vec_copy);
    }
    if (!has_up_case(vec_copy)) {
        add_up_case(vec_copy);
    }
    if (!has_low_case(vec_copy)) {
        add_low_case(vec_copy);
    }
    std::string password = join_vec(m_special_chars, vec_copy, m_len);
    final_check(m_special_chars, password);
    std::cout << "\nPassword: " << password << "\n\n";
}


bool pswd::get_questions(const std::string& f_name, std::vector<std::string>& questions) {
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

void pswd::shuffle_vec(std::vector<std::string>& vec) {
    static std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
}

void pswd::split_input(const std::string& str, std::vector<std::string>& vec) {
    std::istringstream line(str);
    for (std::string str2; getline(line, str2, ' ');) {
        if (!str2.empty()) {
            vec.push_back(str2);
        }
    }
}

void pswd::resize_vec(std::size_t len, std::vector<std::string>& vec) {
    std::vector<std::string> temp_vec;
    resize_vec_recur(vec, len, temp_vec);
    vec = temp_vec;
}

void pswd::resize_vec_recur(const std::vector<std::string>& vec, std::size_t len, std::vector<std::string>& temp_vec) {
    std::size_t new_len {};
    for (const std::string& str : vec) {
        new_len += str.size() + 1; // every word will be followed by a random character
        if (new_len < len) {
            temp_vec.push_back(str);
        } else if (new_len == len) {
            temp_vec.push_back(str);
            break;
        } else { // new_len > len
            std::size_t diff = new_len - len;
            if (diff < str.size()) {
                std::string new_str = str.substr(0, str.size() - diff);
                temp_vec.push_back(new_str);
            }
            break;
        }
    }
    if (new_len < len) resize_vec_recur(vec, len - new_len, temp_vec);
}

bool pswd::has_digit(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) { return true; }
    }
    return false;
}

bool pswd::has_digit(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        if (has_digit(str)) { return true; }
    }
    return false;
}

void pswd::add_digit(std::vector<std::string>& vec) {
    std::vector<std::vector<char>> replacements = {
        {'b', '6'}, {'q', '9'}, {'S', '5'}, {'l', '1'}, {'O', '0'}
    };
    for (const auto& rep : replacements) {
        if (has_char(vec, rep[0])) {
            for (std::string& str : vec) {
                for (char& c : str) {
                    if (c == rep[0]) { c = rep[1]; }
                }
            }
            // Only 1 character is replaced so that the password remains human-readable
            break;
        }
    }
}

void pswd::add_letters(std::vector<std::string>& vec) {
    std::vector<std::vector<char>> replacements = {
        {'b', '6'}, {'q', '9'}, {'S', '5'}, {'l', '1'}, {'O', '0'}
    };
    for (const auto& rep : replacements) {
        if (has_char(vec, rep[1])) {
            for (std::string& str : vec) {
                for (char& c : str) {
                    if (c == rep[1]) { c = rep[0]; }
                }
            }
        }
    }
}

bool pswd::has_char(const std::vector<std::string>& vec, char c) {
    for (const std::string& str : vec) {
        if (str.find(c) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool pswd::has_letter(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        for (char c : str) {
            if (isalpha(c)) { return true; }
        }
    }
    return false;
}

bool pswd::has_up_case(const std::string& str) {
    for (char c : str) {
        if (std::isupper(c)) { return true; }
    }
    return false;
}

bool pswd::has_up_case(const std::vector<std::string>& vec) {
    for (const auto& str : vec) {
        if (has_up_case(str)) { return true; }
    }
    return false;
}

void pswd::add_up_case(std::vector<std::string>& vec) {
    static Rand rand_int {0, 99};
    for (auto& str: vec) {
        for (char& c: str) {
            // probability is only 33% so that password is easier to memorise
            if (rand_int() < 33) { c = toupper(c); }
        }
    }
}

void pswd::add_low_case(std::vector<std::string>& vec) {
    static Rand rand_int {0, 99};
    for (auto& str: vec) {
        for (char& c: str) {
            if (rand_int() < 33) { c = tolower(c); }
        }
    }
}

bool pswd::has_low_case(const std::string& str) {
    for (char c : str) {
        if (islower(c)) { return true; }
    }
    return false;
}

bool pswd::has_low_case(const std::vector<std::string>& vec) {
    for (const std::string& str : vec) {
        if (has_low_case(str)) { return true;}
    }
    return false;
}

std::string pswd::join_vec(const std::string& sp_chars, const std::vector<std::string>& vec, std::size_t len) {
    std::string password;
    for (const std::string& str : vec) {
        password += str + add_char(sp_chars, password, vec);
    }
    if (password.size() != len) {
        password += add_char(sp_chars, password, vec, true);
    }
    return password;
}

char pswd::add_char(const std::string& sp_chars, const std::string& str,
              const std::vector<std::string>& vec, bool last_char) {
    if (last_char) {
        if (!has_sp_char(sp_chars, str)) {
            return rand_sp_char(sp_chars);
        }
        if (!has_digit(str)) { return rand_digit(); }
        if (!has_up_case(str)) { return rand_up_case(); }
        if (!has_low_case(str)) { return rand_low_case(); }
        return rand_char(sp_chars);
    }
    else {
        if (!(has_sp_char(sp_chars, str) || has_sp_char(sp_chars, vec))) {
            return rand_sp_char(sp_chars);
        }
        if (!(has_digit(str) || has_digit(vec))) {
            return rand_digit();
        }
        if (!(has_up_case(str) || has_up_case(vec))) {
            return rand_up_case();
        }
        if (!(has_low_case(str) || has_low_case(vec))) {
            return rand_low_case();
        }
        return rand_char(sp_chars);
    }
}

bool pswd::has_sp_char(const std::string& sp_chars, const std::string& str) {
    for (char c : sp_chars) {
        if (str.find(c) != std::string::npos) {
                return true;
        }
    }
    return false;
}

bool pswd::has_sp_char(const std::string& sp_chars, const std::vector<std::string>& vec) {
    for (const std::string& str : vec) {
        if (has_sp_char(sp_chars, str)) { return true; }
    }
    return false;
}

char pswd::rand_sp_char(const std::string& sp_chars) {
    int sz = sp_chars.size();
    static Rand rand_int {0, sz - 1};
    return sp_chars[rand_int()];
}

char pswd::rand_digit() {
    std::string digits = "0123456789";
    static Rand rand_int {0, 9};
    return digits[rand_int()];
}

char pswd::rand_up_case() {
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static Rand rand_int {0, 25};
    return letters[rand_int()];
}

char pswd::rand_low_case() {
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    static Rand rand_int {0, 25};
    return letters[rand_int()];
}

char pswd::rand_char(const std::string& sp_chars) {
    static Rand rand_int {0, 3};
    switch (rand_int()) {
        case 0: {
            return rand_digit();
        }
        case 1: {
            return rand_up_case();
        }
        case 2: {
            return rand_low_case();
        }
        default: {
            return rand_sp_char(sp_chars);
        }
    }
}

void pswd::final_check(const std::string& sp_chars, std::string& str) {
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

void pswd::replace_char(std::string& str, char c) {
    int digit_cnt {};
    int low_cnt {};
    int up_cnt {};
    int sp_cnt {};
    for (char& ch : str) {
        if (isdigit(ch)) {
            digit_cnt++;
        } else if (islower(ch)) {
            low_cnt++;
        } else if (isupper(ch)) {
            up_cnt++;
        } else { sp_cnt++; }
        if (digit_cnt > 1 || low_cnt > 1 || up_cnt > 1 || sp_cnt > 1) {
            // There is at least 1 more char of the same type --> can replace
            ch = c;
            break;
        }
    }
}
