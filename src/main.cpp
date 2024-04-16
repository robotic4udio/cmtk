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


    // auto scale = Scale("Major", "D");
    // scale.print(3,true);
    // for(int i=1; i<=7; i++)
    //   scale.getChord(i).print();


    auto ct = Chord("C"); // Cm7/Eb
    ct.setRoman("iv7/2",Note("C")).print();

    ct.getRoman(Note("C"));


    auto rc = RomanChord("iv7");
    rc.print();
    rc.setTonic(Note("A")).print();


    ChordProgression("ii7|V7|I7",Note("G")).print();
    
    ChordProgression("C|F|A|G7").print();

    return 0;
}
