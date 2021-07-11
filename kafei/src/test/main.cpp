#include <iostream>

#include "Kafei.h"

// Engine Testing Code
int main(void) {
    kafei::Config cfg{};
    cfg.SetWindowTitle("Kafei");

    kafei::Kafei game{cfg};
}