#include <iostream>

#include "Kafei.h"

// Engine Testing Code
int main(void) {
    kafei::Kafei kaf;

    kaf.Load(kaf.BuildConfig("Kafei"));

    /**
     * THe idea is to be able to make calls like:
     *
     * kaf.Load(kaf.Build("WorldName", World object))
     *    .Load(kaf.Build(System object))
     *    .Load(kaf.Build(DataContainer object));
     *
     * kaf.SetDefaultWorld("WorldName");
     */

    kaf.Start();
}