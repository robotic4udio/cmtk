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
  /*   // Major Scale (Ionian Mode)
    std::cout << "Major Scale Chords: " << std::endl;
    chord.printChordTones("I");
    chord.printChordTones("ii");
    chord.printChordTones("iii");
    chord.printChordTones("IV");
    chord.printChordTones("V");
    chord.printChordTones("vi");
    chord.printChordTones("vii°");
    // Natural Minor Scale (Aeolian Mode)
    std::cout << "Natural Minor Scale Chords: " << std::endl;
    chord.printChordTones("i");
    chord.printChordTones("ii°");
    chord.printChordTones("bIII");
    chord.printChordTones("iv");
    chord.printChordTones("v");
    chord.printChordTones("bVI");
    chord.printChordTones("bVII");
    // Dorain Mode
    std::cout << "Dorian Mode Chords: " << std::endl;
    chord.printChordTones("i");
    chord.printChordTones("ii");
    chord.printChordTones("bIII");
    chord.printChordTones("IV");
    chord.printChordTones("v");
    chord.printChordTones("vi°");
    chord.printChordTones("bVII");
    // Mixolydian Mode
    std::cout << "Mixolydian Mode Chords: " << std::endl;
    chord.printChordTones("I");
    chord.printChordTones("ii");
    chord.printChordTones("iii°");
    chord.printChordTones("IV");
    chord.printChordTones("v");
    chord.printChordTones("vi");
    chord.printChordTones("bVII");
    // Dominant 7th Chords
  
    // Print chord progression


    std::cout << "2-5-1 Chord Progression: " << std::endl;

    chord.printProgression({"ii7", "V7", "I7", "I7"});

    std::cout << "2-5-1 Chord Progression: " << std::endl; 



    ChordProgression cp("Cm|FMaj7|Eb7|B+|G7");
    cp.print();


    // Andalusian
    cp.setChordProgression("i|-bVII|-bVI|-V7");
    cp.print();

    // Axis

    cp.setChordProgression("I|-V|-vi|IV");
    cp.print();

    // Summertime
    cp.setChordProgression("i6|-ii6|");
    cp.print();

    
    

    ChordProgression cp;
    cp.print();


    // Andalusian

    cp.setChordProgression("Cm|G|Cm7|Ab°7|G7b9");
    cp.print();
    
    ChordSequencer cs;
    cs.setChordProgression(cp);
    
    for(int i = 0; i < 16; i++){
        auto tmp = cs.next();
        for(auto x : tmp) std::cout << x << " ";
        std::cout << std::endl;
    }

    */

    // Create a Chord object
    // Chord c3("Dm7/F"); c3.print(); c3.openVoicing(); c3.getGroupRange(30,52,6,true); c3.printIntervals(); c3.print();
    // std::cout << std::endl;
    

    
 


    // Create a InterfaceGPT object
    // InterfaceGPT gpt;
    // Print the response from the OpenAI API
    // auto response = gpt.generateMusic("Sad piece in D minor", API_KEY, "gpt-4-1106-preview");

    // std::cout << response << std::endl;

    // Create a JSON object and print it
    // JSON Obj = JSON::Load(response);

    // Print the JSON object
    // auto content = Obj["choices"][0]["message"]["content"];
    

    // Test romanPitchToSemitone
    // std::cout << "Roman Pitch to Semitone: " << romanPitchToSemitone("vii") << std::endl;


  
    // ChordProgression cp = ChordProgression("i|iv|bVII7|bIII7|bVI7|V7|i");
    // std::cout << "Chord Progression: " << std::endl;
    // cp.print();
    // cp[0].print();
    // 
    // std::cout << "Diatonic Scales: " << std::endl;
    // Scale::printDiatonicScales(cp,4);


    //  Number  -9  -8  -7  -6  -5  -4  -3  -2  -1  | 1   2   3   4   5   6   7   8   9
    //  Interval 5   b6  6   b7  7   1   b2  2   b3 | 3   4   b5  5   b6  6   b7  7   8
    //  Semi     7   8   9   10  11  0   1   2   3  | 4   5   6   7   8   9   10  11  0   

    // auto i = Intervals("3 b6 7");
    // i.print();
    // i.getNegativeHarmonic().print();

    // auto scale = Scale("Phrygian",2);
    // scale.print();
    // scale.getChordProgression({1,2}).print();



    auto chord = Chord("I7");
    chord.print();



 


    // Print the major scale
    // std::cout << "Major Scale: " << std::endl;
    // Notes(MajorNoteMap["F"]).print();

    auto scale = Scale("Double Harmonic Major", "C");
    scale.print();

    scale.getChord(2).print();



    return 0;
}
