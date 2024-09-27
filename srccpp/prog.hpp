#ifndef PROG_HPP
#define PROG_HPP
#include <limits>
/// @brief Содержит основные функции программы
namespace Prog {
    /// @brief Функция для перевода массива целых чисел в строку в yaml-формате.
    /// @details Данная перегрузка работает с массивом символов и его длиной.
    /// @param[in] array Входной массив целых чисел.
    /// @param[in] array_size Длина входного массива.
    /// @param[in] name Имя массива.
    /// @param[out] string_len Длина получившегося массива символов.
    /// @return Массив символов, представляющих собой исходный массив чисел в yaml-формате.
    const char *array_to_yaml(const int *array, const size_t array_size, const char *name, size_t &string_len);
    
    /// @brief Функция для перевода массива целых чисел в строку в yaml-формате.
    /// @details Данная перегрузка работает с экземпляром класса std::string.
    /// @param[in] array Входной массив целых чисел.
    /// @param[in] array_size Длина входного массива.
    /// @param[in] name Имя массива.
    /// @return Экземпляр класса std::string, представляющий собой массив в yaml-формате.
    std::string array_to_yaml(const int *array, const size_t array_size, const std::string name);
    
    /// @brief Функция для перевода массива целых чисел в строку в yaml-формате.
    /// @details Данная перегрузка работает с нуль-терминированной строкой.
    /// @param[in] array Входной массив целых чисел.
    /// @param[in] array_size Длина входного массива.
    /// @param[in] name Имя массива.
    /// @return Нуль-терминированная строка, преставляющая собой исходный массив в yaml-формате
    const char *array_to_yaml(const int *array, const size_t array_size, const char *name);

    /// @brief Функция для составления массива целых чисел на основе данных строки в yaml-формате.
    /// @details Данная перегрузка работает с экземпляром класса std::string.
    /// @param[in] yaml_str Экземпляр класса std::string, содержащий представление массива целых чисел в yaml-формате.
    /// @param[out] array_size Длина получившегося массива целых чисел.
    /// @param[out] name Имя массива.
    /// @return Массив целых чисел.
    int *yaml_to_array(const std::string yaml_str, size_t& array_size, std::string &name);
    
    /// @brief Функция для составления массива целых чисел на основе данных строки в yaml-формате.
    /// @details Данная перегрузка работает с нуль-терминированной строкой.
    /// @param[in] yaml_str Нуль-терминированная строка, содержащая представление массива целых чисел в yaml-формате.
    /// @param[out] array_size Длина получившегося массива целых чисел.
    /// @param[out] name Имя массива.
    /// @return Массив целых чисел.
    int *yaml_to_array(const char *yaml_str, size_t& array_size , std::string &name);

    /// @brief Функция для составления массива целых чисел на основе данных строки в yaml-формате.
    /// @details Данная перегрузка работает с массивом символов и его длиной.
    /// @param yaml_str Массив символов, содержащий представление массива целых чисел в yaml-формате.
    /// @param str_len Размер массива символов.
    /// @param array_size Длина получившегося массива целых чисел.
    /// @param name Имя массива.
    /// @return Массив целых чисел.
    int *yaml_to_array(const char *yaml_str, const size_t str_len, size_t&array_size, std::string &name);
}
#endif