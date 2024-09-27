#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <algorithm>
#include "prog.hpp"

using namespace Prog;
using std::begin, std::end;

TEST_CASE("prog1") {
    SECTION("Array_to_Yaml") {
        const int arr[3] = {1, 2, 3};
        size_t len;
        std::string res_1 = array_to_yaml(arr, 3, "arr");
        REQUIRE(res_1 == std::string("arr:\n\t- 1\n\t- 2\n\t- 3"));

        const char *res2 = array_to_yaml(arr, 3, "arr2");
        REQUIRE(strcmp(res2, "arr2:\n\t- 1\n\t- 2\n\t- 3") == 0);
        delete[] res2;

        const char *res3 = array_to_yaml(arr, 3, "arr3", len);
        char *res3_0 = new char[len + 1];
        std::copy(res3, res3+len, res3_0);
        res3_0[len] = '\0';
        REQUIRE(strcmp(res3_0, "arr3:\n\t- 1\n\t- 2\n\t- 3") == 0);
        delete[] res3;
        delete[] res3_0;
    }
    SECTION("Yaml_to_array_throws") {
        size_t size;
        std::string name;

        const std::string str_throw_1 = "arr \n\t- 1";
        REQUIRE_THROWS(yaml_to_array(str_throw_1, size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_1.c_str(), size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_1.data(), str_throw_1.length(), size, name));

        const std::string str_throw_2 = "arr:\n\t- 1\n\t2\n\t- 3";
        REQUIRE_THROWS(yaml_to_array(str_throw_2, size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_2.c_str(), size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_2.data(), str_throw_2.length(), size, name));

        const std::string str_throw_3 = "arr:\n\t- 1abc\n\t2\n\t- 3";
        REQUIRE_THROWS(yaml_to_array(str_throw_3, size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_3.c_str(), size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_3.data(), str_throw_3.length(), size, name));

        const std::string str_throw_4 = "arr:\n\t- 2147483648\n\t2\n\t- 3";
        REQUIRE_THROWS(yaml_to_array(str_throw_4, size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_4.c_str(), size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_4.data(), str_throw_4.length(), size, name));

        const std::string str_throw_5 = "arr:\n\t-  \t   \n\t- 2\n\t- 3";
        REQUIRE_THROWS(yaml_to_array(str_throw_5, size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_5.c_str(), size, name));
        REQUIRE_THROWS(yaml_to_array(str_throw_5.data(), str_throw_5.length(), size, name));

    }
    SECTION("Yaml_to_array") {
        size_t size;
        std::string name;
        int sample[3] = {1, 2, 3}; 
        const std::string str = "arr:\n\t- 1    \n\t- 2 \n\t- 3";
        
        int *arr_1 = yaml_to_array(str, size, name);
        REQUIRE(std::equal(begin(sample), end(sample), arr_1));
        delete[] arr_1;

        int *arr_2 = yaml_to_array(str.c_str(), size, name);
        REQUIRE(std::equal(begin(sample), end(sample), arr_2));
        delete[] arr_2;

        int *arr_3 = yaml_to_array(str.data(), str.length(), size, name);
        REQUIRE(std::equal(begin(sample), end(sample), arr_3));
        delete[] arr_3;
    }
}