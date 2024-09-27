#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "prog.hpp"



namespace Prog {
    /// @brief Возвращает длину целого числа.
    /// @param num Целое число.
    /// @return Длина числа.
    size_t len_of_num(int num);
    
    /// @brief Функция для подсчета длины результирующей yaml-строки на основе массива целых чисел.
    /// @param[in] array Массив целых чисел.
    /// @param[in] array_len длина целых чисел.
    /// @param[in] name Имя массива.
    /// @return[in] Длина строки, являющейся представлением массива в yaml-формате.
    size_t all_len(const int *array, size_t array_len, const char *name);
    
    /// @brief Добавляет отступ по yaml-формату в начале строки.
    /// @param str Указатель на строку.
    /// @param ptr Указатель на текущую позицию в строке.
    void add_offset(char *str, size_t& ptr);

    /// @brief Убирает отступы в начале и в конце строки.
    /// @param str Строка, в которой надо удалить отступы.
    /// @return Строка без отступов.
    std::string trim(const std::string& str);


    size_t len_of_num(int elem) {
        size_t r = std::to_string(elem).length();
        return r;
    }

    size_t all_len(const int *arr, size_t arr_len, const char *name) {
        size_t res = strlen(name) + 1;
        for (size_t i = 0; i < arr_len; ++i)
            res += 4 + len_of_num(arr[i]);
        return res;
    }

    void add_offset(char *str, size_t& ptr) {    // Makes offset in yaml format before integer
        str[ptr] = '\n';
        ptr++;
        str[ptr] = '\t';
        ptr++;
        str[ptr] = '-';
        ptr++;
        str[ptr] = ' ';
        ptr++;
    }

    const char *array_to_yaml(const int *arr, const size_t arr_len, const char *name, size_t &str_len) {
        char *res = new char[all_len(arr, arr_len, name)];     // Memory allocating
        std::copy(name, name + strlen(name), res);
        res[strlen(name)] = ':';     // Name of the array added
        str_len = strlen(name)+1;
        for (size_t i = 0; i < arr_len; ++i) {
            add_offset(res, str_len);
            int elem = arr[i];
            int deg = pow(10, len_of_num(elem) - 1);
            while (elem > 0) {
                int digit = elem / deg;
                res[str_len] = '0' + digit;
                elem %= deg;
                deg /= 10;
                str_len++;
            }
        }
        return res;
    }

    std::string array_to_yaml(const int *arr, const size_t arr_len, const std::string name) {
        
        std::ostringstream oss;
        oss << name << ":";
        for (size_t i = 0; i < arr_len; ++i)
            oss << "\n\t- " << arr[i];
        oss << '\0';
        std::string str(oss.str());
        return str;
    }

    const char *array_to_yaml(const int *arr, const size_t arr_len, const char *name) {
        std::string res_str = array_to_yaml(arr, arr_len, std::string(name));
        char *res = new char[res_str.length() + 1];
        std::copy(res_str.begin(), res_str.end(), res);
        return res;
    }

    std::string trim(const std::string& str) {
        auto first = str.find_first_not_of(" \t");
        auto last = str.find_last_not_of(" \t");
        if (first == str.npos)
            return "";
        return str.substr(first, last - first + 1);
    }

    int *yaml_to_array(const std::string yaml_str, size_t& arr_size, std::string &arr_name) {
        std::istringstream iss(yaml_str);
        std::string line;
        getline(iss, line);
        size_t name_end, num_pref, num_end;
        name_end = line.find(":");          // Находим имя массива
        if (name_end == std::string::npos || name_end != line.length() - 1)
            throw std::invalid_argument("Incorrect yaml-format input!");
        arr_name = line.substr(0, name_end);
        int *arr = new int[1] {};
        arr_size = 0;
        while (getline(iss, line)) {
            num_pref = line.find("- ");
            if (num_pref != 1)
            {
                delete[] arr;
                throw std::invalid_argument("Incorrect yaml-format input!");
            }
            std::string num_substr = trim(line.substr(num_pref + 2));
            if (num_substr == "")
            {
                delete[] arr;
                throw std::invalid_argument("Incorrect yaml-format input!");
            }
            try
            {
                int num = std::stoi(num_substr, &num_end);
                if (num_end != num_substr.length())
                {
                    delete[] arr;
                    throw std::invalid_argument("Incorrect yaml-format input!");
                }
                if (arr_size != 0) {
                    int *re_arr = new int[arr_size+1] {};
                    std::copy(arr, arr + arr_size, re_arr);
                    delete[] arr;
                    arr = re_arr;
                }
                arr[arr_size++] = num;
            }
            catch(const std::out_of_range& our)
            {
                throw std::out_of_range("Not an integer num!");
            }
            catch(...)
            {
                throw;
            }
        }
        return arr;
    }
    
    int *yaml_to_array(const char *yaml_str, size_t& arr_size, std::string &arr_name) {
        return yaml_to_array(std::string(yaml_str), arr_size, arr_name);
    }

    int *yaml_to_array(const char *yaml_str, const size_t str_len, size_t& arr_size, std::string &arr_name) {
        return yaml_to_array(std::string(yaml_str, str_len), arr_size, arr_name);
    }
}