#include <iostream>

#include "jinx.h"

// Engine Testing Code
int main(void) {
    jinx::Config cfg{};
    cfg.SetTitle("Jinx");

    jinx::Jinx game{cfg};
}