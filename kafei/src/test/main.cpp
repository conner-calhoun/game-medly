#include <iostream>

#include "kafei.h"

// Engine Testing Code
int main(void) {
    kafei::Config cfg{};
    cfg.SetTitle("kafei");

    kafei::Kafei game{cfg};
}