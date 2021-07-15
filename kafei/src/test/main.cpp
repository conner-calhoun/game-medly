#include <iostream>

#include "kafei.h"

// Engine Testing Code
int main(void) {
    kafei::Kafei kaf;

    kaf.load(kaf.build_config("Kafei"));

    /**
     * THe idea is to be able to make calls like:
     *
     * kaf.load(kaf.build("WorldName", World object))
     *    .load(kaf.build(System object))
     *    .load(kaf.build(DataContainer object));
     *
     * kaf.SetDefaultWorld("WorldName");
     */

    kaf.start();
}