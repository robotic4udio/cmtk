#include "Chords.h"
#include "InterfaceGPT.h"
#include "../libraries/SimpleJSON/json.hpp"
#include "Interval.h"
#include "Scale.h"
#include "ChordProgression.h"
#include "Note.h"

#define API_KEY "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"

using json::JSON;
using namespace cmtk;




int main() {


    auto scale = Scale("Major", "D");
    scale.print(3,true);
    for(int i=1; i<=7; i++)
      scale.getChord(i).print();




    std::cout << "-------------------" << std::endl;    
    auto prog = ChordProgression("Cm|Ab7|B|G").print().printRoman(Note("C"));
    Scale::printDiatonicScales(prog);


    Chord c = Chord("Cm9/Eb");
    c.setOctave(3).print().forceBassInRange(24, 48).print();

    ChordType ct = ChordType("Maj7");
    ct.print();


    ct.setSemi({0,4,7 }).print(); // major root position
    ct.setSemi({0,3,8 }).print(); // major 1st inversion
    ct.setSemi({0,5,9 }).print(); // major 2nd inversion
    ct.setSemi({0,3,7 }).print(); // minor root position
    ct.setSemi({0,4,9 }).print(); // minor 1st inversion
    ct.setSemi({0,5,8 }).print(); // minor 2nd inversion

 
    return 0;
}
