#include "InterfaceGPT.h"
#include "Scale.h"


using namespace cmtk;

int main() {

  // Scale("F-Lydian").print(4);
  Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
  Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();

  Scale::GetChordProg("C-Dorian-14141374",4).print().printChords();
  Scale::GetChordProg("C-Doian-1425",4).print().printChords();

  Scale("C-Phrygian").getChordProg("1235",4).print().printChords();

  ChordProg::Get("F-Dorian-143576-4").print().printChords();
  ChordProg::Get("Christiania").print().printChords();
  ChordProg::Get("LayLadyLayA1").print().printChords();
  ChordProg::Get("D-Phrygian-15634145").print().printChords();

  return 0;

}
