#ifndef DIALOG_H
#define DIALOG_H
#include <limits>
namespace Dialog {
    int get_int(int min = std::numeric_limits<int>::lowest(), int max = std::numeric_limits<int>::max());
    void D_arr_to_yaml();
    void D_yaml_to_arr();
}
#endif