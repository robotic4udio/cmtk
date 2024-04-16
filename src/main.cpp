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


    return 0;
}
