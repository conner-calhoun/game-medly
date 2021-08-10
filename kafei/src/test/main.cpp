#include <iostream>

#include "kafei.h"

#include <filesystem>

// Engine Testing Code
int main(char argc, char** argv) {
    // This will need to be loaded into the resource manager.
    // That way we know where our config and resources are
    std::filesystem::path exePath = argv[0];

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

    kaf.set_world(kaf.build_world());
    kaf.start();
}