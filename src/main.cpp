#include "InterfaceGPT.h"
#include "Scale.h"
#include "MidiFile.h"

// Include the TIMER
#include <chrono>

using namespace std::chrono;
using namespace cmtk;

int main() {

  // Scale("F-Lydian").print(4);
  //Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
  //Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
  //
  //Scale::GetChordProg("C-Dorian-14141374",4).print().printChords();
  //Scale::GetChordProg("C-Doian-1425",4).print().printChords();
  //
  Scale("C-Major").getChordProg("1234567",4).print().printChords();
  Scale("C-Dorian").getChordProg("1234567",4).print().printChords();
  Scale("C-Phrygian").getChordProg("1234567",4).print().printChords();
  Scale("C-Lydian").getChordProg("1234567",4).print().printChords();
  Scale("C-Mixolydian").getChordProg("1234567",4).print().printChords();
  Scale("C-Aeolian").getChordProg("1234567",4).print().printChords();
  Scale("C-Locrian").getChordProg("1234567",4).print().printChords();

  // Common Chord Progressions
  Scale("F-Minor").getChordProg("1425",3).print().printChords();
  Scale("F-Minor").getChordProg("1637",3).print().printChords();
  Scale("F-Minor").getChordProg("1345",3).print().printChords();
  Scale("F-Minor").getChordProg("1574",3).print().printChords();

  // Dark Synthwave
  Scale("F-Minor").getChordProg("1425",4).print().printChords();

  // Start the timer 
  auto cp = ChordProg::Get("i|iv|iv|V").setTonic("F");
  cp.print().printChords();


  return 0;

}
