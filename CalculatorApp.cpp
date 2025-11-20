#include <iostream>

#include "calc.h"

int main() {
    Calculator calc;
    while (calc.is_running()) {
        calc.Run_Command();
    };
    return 0;
}
