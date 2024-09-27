#include <iostream>
#include <cstring>
#include <string>
#include <limits>

#include "prog.hpp"
using namespace Prog;

namespace Dialog {
    
    int get_int(int min = std::numeric_limits<int>::lowest(), int max = std::numeric_limits<int>::max()) {
        int num;
        while (true) {
            std::cin >> num;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if(std::cin.fail() || num < min || num > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please: ";
            }
            else
            {
                if (std::cin.peek() == '\n' || std::cin.peek() == ' ') {
                    std::cin.ignore();                
                    break;
                }
                else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "You are wrong; repeat please: ";
                }
            }
        }
        return num;
    }
    
    std::string get_str() {
        std::string res, buffer;
        while (std::getline(std::cin, buffer) && !buffer.empty())
            res += buffer + "\n";
        
        if(std::cin.eof()) // обнаружен конец файла
            throw std::runtime_error("EOF");
        else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
            throw std::runtime_error(std::string("Failed to read string: ") + strerror(errno));

        return res;
    }

    int overload_type() {
        int res;
        std::cout << ">>>>>>>>>>>>>>\n";
        const std::string msgs[] = {"1) std::string;", \
        "2) char* null-terminated;", \
        "3) char* + size_t."};
        for (int i = 0; i < 3; ++i)
            std::cout << msgs[i] << std::endl;
        std::cout << ">>>>>>>>>>>>>>\n" << std::endl;
        std::cout << "Enter the overload type: ";
        res = get_int(1, 3);
        return res;
    }

    void D_arr_to_yaml() {
        int *arr;
        std::string name;
        std::cout << "Enter the array name: ";
        std::getline(std::cin, name);
        if(std::cin.eof()) // обнаружен конец файла
            throw std::runtime_error("EOF");
        try
        {
            std::cout << "Enter the number of integers: ";
            int size = get_int(1);
            arr = new int[size] {};
            std::cout << "Enter items of array (integers): ";
            for (int i = 0; i < size; ++i)
                arr[i] = get_int();
            size_t res_len = 0;
            int type = overload_type();
            switch (type)
            {
                case 1:
                {
                    std::string res_1 = array_to_yaml(arr, size, name);
                    std::cout << res_1 << std::endl;
                    break;
                }
                case 2:
                {
                    const char *res_2 = array_to_yaml(arr, size, name.c_str());
                    std::cout << res_2 << std::endl;
                    delete[] res_2;
                    break;
                }
                case 3:
                {
                    const char *res_3 = array_to_yaml(arr, size, name.c_str(), res_len);
                    for (size_t i = 0; i < res_len; ++i)
                        std::cout << res_3[i];
                    std::cout << std::endl;
                    delete[] res_3;
                    break;
                }
            }
        }
        catch(...)
        {
            delete[] arr;
            throw;
        }
        delete[] arr;
    }

    void output_arr(const int *arr, const size_t size, const std::string name) {
        std::cout << "Name of input array: " << name << std::endl;
        std::cout << "Content of array: ";
        for (size_t i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl; 
    }

    void D_yaml_to_arr() {
        try {
            std::cout << "Enter the string in yaml-format: " << std::endl;
            std::string yaml_string = get_str();
            std::string arr_name;
            size_t res_arr_size;
            int type = overload_type();
            int *arr;
            switch (type)
            {
            case 1:
                arr = yaml_to_array(yaml_string, res_arr_size, arr_name);
                break;
            
            case 2:
                arr = yaml_to_array(yaml_string.c_str(), res_arr_size, arr_name);
                break;

            case 3:
                arr = yaml_to_array(yaml_string.data(), yaml_string.length(), res_arr_size, arr_name);
                break;
            }
            output_arr(arr, res_arr_size, arr_name);
            delete[] arr;
        }
        catch (const std::runtime_error& re) {
            throw;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            D_yaml_to_arr();
        }
    }
}