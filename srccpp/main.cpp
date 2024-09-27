#include <iostream>
#include <functional>

#include "prog.hpp"
#include "dialog.hpp"
using namespace Prog;
using namespace Dialog;

int dialog();

int main()
{
    try
    {
        std::function<void()> dialog_funcs[] = {nullptr, D_arr_to_yaml, D_yaml_to_arr};
        int type;
        while ((type = dialog()) > 0)
            dialog_funcs[type]();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

int dialog() {
    const std::string msgs[] = {"0) Quit;", \
    "1) Array to yaml;", \
    "2) Yaml to array."};

    std::cout << "----------------" << std::endl;
    for (int i = 0; i < 3; ++i)
        std::cout << msgs[i] << std::endl;
    std::cout << "----------------\n" << std::endl;
    std::cout << "Input number: ";
    int res = get_int(0, 2);
    
    return res;
}
