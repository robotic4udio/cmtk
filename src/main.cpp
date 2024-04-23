#include "InterfaceGPT.h"
#include "Scale.h"


using namespace cmtk;

int main() {

  // Scale("F-Lydian").print(4);
  //Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
  //Scale::GetChordProg("F-Dorian-14141374",4).print().printChords();
//
  //Scale::GetChordProg("C-Dorian-14141374",4).print().printChords();
  //Scale::GetChordProg("C-Doian-1425",4).print().printChords();
//
  //Scale("C-Phrygian").getChordProg("1235",4).print().printChords();
//
//  ChordProg::Get("F-Dorian-143576-4").print().printChords();
  auto cp = ChordProg::Get("Christiania").print();

  auto c = Chord("Cm9/Eb").print();

    
  auto cv = ChordVoicing(c).setVoicing("B 5 1 3 * H:C1").print();


  return 0;

}
