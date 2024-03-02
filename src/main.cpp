#include "Chords.h"
#include "InterfaceGPT.h"

#define API_KEY "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"

int main() {
    // Create a Chords object
    Chords chord;

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
*/

    chord.printProgression({"C7", "d7", "e7", "F7", "G7", "a7", "b°7", "C7"});

    // Create a InterfaceGPT object
    InterfaceGPT gpt;
    // Print the response from the OpenAI API
    std::cout << gpt.sendPrompt("What is the meaning of life?", API_KEY) << std::endl;


    return 0;
}
