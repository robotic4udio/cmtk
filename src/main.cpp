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
  Scale("F-Dorian").getChordProg("1235",4).print().printChords();
  //

  // Start the timer 


  

  auto cp = ChordProg::Get("C-Hungarian Minor-136251-3");

  cp.print().printChords();


  return 0;

}
