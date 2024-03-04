#include "Chords.h"
#include "InterfaceGPT.h"
#include "../../SimpleJSON/json.hpp"

#define API_KEY "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"

using json::JSON;
using namespace cmtk;

int main() {
    // Create a Chords object
    Chord chord;

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
    std::cout << "Chord Progression: " << std::endl;
    chord.printProgression({"I", "IV", "V", "I"});
    std::cout << "Andalusian Chord Progression: " << std::endl;
    chord.printProgression({"i", "bVII", "bVI", "V7no5"});
    std::cout << "Axis Chord Progression: " << std::endl;
    chord.printProgression({"I", "V7no5", "vi", "iv"});
    std::cout << "Summertime Chord Progression: " << std::endl;
    chord.printProgression({"iv", "ii6no5", "iv7", "bVI7"});

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

    


    ChordProgressions chordProgressions;
    chordProgressions.print();


    // Andalusian
    cp.setChordProgression("i|-bVII|-bVI|-V7");
    cp.print();
    
    ChordSequencer cs;
    cs.setChordProgression(cp);
    
    for(int i = 0; i < 16; i++) {
        auto tmp = cs.next();
        for(auto x : tmp) std::cout << x << " ";
        std::cout << std::endl;
    }

    */


    chord.setChord("CmMaj7");
    chord.printIntervals();
    chord.print();

    // Create a InterfaceGPT object
    // InterfaceGPT gpt;
    // Print the response from the OpenAI API
    // auto response = gpt.generateMusic("Sad piece in D minor", API_KEY, "gpt-4-1106-preview");

    // std::cout << response << std::endl;


    // Create a JSON object and print it
    // JSON Obj = JSON::Load(response);

    // Print the JSON object
    // auto content = Obj["choices"][0]["message"]["content"];
    
    // std::cout << content << std::endl;


    return 0;
}
