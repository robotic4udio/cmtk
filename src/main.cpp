#include "Chords.h"
#include "InterfaceGPT.h"
#include "../libraries/SimpleJSON/json.hpp"
#include "Interval.h"
#include "Scale.h"
#include "Note.h"

#define API_KEY "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"

using json::JSON;
using namespace cmtk;

int main() {







    std::cout << "-------------------" << std::endl;    
    auto prog = ChordProgression("Cm|Ab7|B|G").print().printRoman(Note("C"));
    Scale::printDiatonicScales(prog);


    Chord c = Chord("Cm9/Eb");
    c.setOctave(3).print().forceBassInRange(24, 48).print();

    ChordType ct = ChordType("Maj7");
    ct.print();


    ct.setSemi({0,4,7}).print(); // major root position
    ct.setSemi({0,3,8}).print(); // major 1st inversion
    // ct.setSemi({0,5,9 }).print(); // major 2nd inversion
    // ct.setSemi({0,3,7 }).print(); // minor root position
    // ct.setSemi({0,4,9 }).print(); // minor 1st inversion
    // ct.setSemi({0,5,8 }).print(); // minor 2nd inversion

    ct.setSemi({2,5,9}).print(); // major 1st inversion


    auto ct2 = ChordType("m13");
    auto intervals = ct2.getIntervals();
    intervals.printAllInversions(true,true);

    auto i = ct2.getIntervals().getSemi();
    ct.setSemi(i).print();


    // intervals.getInversion(0,1).printSemi();
    // intervals.getInversion(1,1).printSemi();
    // intervals.getInversion(2,1).printSemi();


    auto scale = Scale("Lydian Dominant", "C");
    // scale.getIntervals().print();  
    // scale.getIntervals().printWH();  

    intervals = scale.getIntervals();
    intervals.printSemiSteps().print();
    intervals.getMode(2).printSemiSteps().print();

    Scale::printModes("Lydian");


    auto time = ChordProgression::Map["LayLadyLayA1"];
    time.print();
    time.printChords();
    time.getNotes().print();
    


    Scale::printScalesByDiatonicity(time,7);


    auto ADorian = Scale("Dorian", "A");


    return 0;
}
