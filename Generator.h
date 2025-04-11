#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Generator {
    const std::string m_special_chars = R"( !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
    std::vector<std::string> m_input_vec {};
    std::size_t m_len {};
    void Test();
public:
    Generator();
    void get_input();
    void get_len();
    void generate_password();
};


class Rand {
    std::default_random_engine re {};
    std::uniform_int_distribution<> dist;
public:
    Rand(int min_num, int max_num) : dist {min_num, max_num} {}
    int operator()() { return dist(re); };
};

bool get_questions(const std::string&, std::vector<std::string>&);
void shuffle_vec(std::vector<std::string>&);
void split_input(const std::string&, std::vector<std::string>&);
void resize_vec(std::size_t, std::vector<std::string>&);
void resize_vec_recur(const std::vector<std::string>&,
                      std::size_t, std::vector<std::string>&);
bool has_digit(const std::string&);
bool has_digit(const std::vector<std::string>&);
void add_digit_or_letters(std::vector<std::string>&, bool = false);
bool has_char(const std::vector<std::string>&, char);
bool has_letter(const std::vector<std::string>&);
bool has_up_case(const std::string&);
bool has_up_case(const std::vector<std::string>&);
void add_low_or_up_case(std::vector<std::string>&, bool = false);
bool has_low_case(const std::string&);
bool has_low_case(const std::vector<std::string>&);
std::string join_vec(const std::string&,
                     const std::vector<std::string>&, std::size_t);
char add_char(const std::string&, const std::string&,
              const std::vector<std::string>&, bool = false);
bool has_sp_char(const std::string&, const std::string&);
bool has_sp_char(const std::string&, const std::vector<std::string>&);
char rand_sp_char(const std::string&);
char rand_digit();
char rand_up_case();
char rand_low_case();
char rand_char(const std::string&);
void final_check(const std::string&, std::string& str);
void replace_char(std::string&, char);

#endif // GENERATOR_H_INCLUDED
