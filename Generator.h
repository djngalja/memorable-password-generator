#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <random>

class Generator {
    std::vector<std::string> m_input_vector;
    std::size_t m_length;
    const std::string m_special_chars = "'-!\"#$%&()*,./:;?@[]^_`{|}~+<=>";
    void Test();
public:
    Generator();
    void SetInput();
    void SetLength();
    void GeneratePassword();
};

// helper functions:
char add_char(const std::string&, const std::string&,
              const std::vector<std::string>&, bool = false);
void replace_char(std::string&, char);
char rand_char(const std::string&);
char rand_digit();
char rand_up_case();
char rand_low_case();
char rand_sp_char(const std::string&);
bool has_sp_char(const std::string&, const std::vector<std::string>&);
bool has_sp_char(const std::string&, const std::string&);
void final_check(const std::string&, std::string& str);
std::string join_vec(const std::vector<std::string>&, std::size_t);
void add_low_or_up_case(std::vector<std::string>&, bool = false);
void add_digit_or_letters(std::vector<std::string>&, bool = false);
void resize_vec(std::size_t, std::vector<std::string>&);
void resize_vec_recur(const std::vector<std::string>&, std::size_t, std::vector<std::string>&);
void shuffle_vec(std::vector<std::string>&);
bool has_char(const std::vector<std::string>&, char);
bool has_low_case(const std::vector<std::string>&);
bool has_low_case(const std::string&);
bool has_letter(const std::vector<std::string>&);
bool has_digit(const std::string&);
bool has_digit(const std::vector<std::string>&);
bool has_up_case(const std::string&);
bool has_up_case(const std::vector<std::string>&);
bool get_questions(const std::string&, std::vector<std::string>&);
std::vector<std::string> get_input();
std::size_t get_len();
void split_input(const std::string&, std::vector<std::string>&);

#endif // GENERATOR_H_INCLUDED
