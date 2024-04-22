#include "InterfaceGPT.h"
#include "Scale.h"


using namespace cmtk;

int main() {

  // Scale("F-Lydian").print(4);
  Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
  Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();

  Scale::GetChordProg("C-Dorian-14141374",4).print().printChords();
  Scale::GetChordProg("C-Dorian-1425",4).print().printChords();

  Scale("C-Lydian").getChordProg("1235",4).print().printChords();

  return 0;

}
