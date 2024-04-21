#include "Chords.h"
#include "InterfaceGPT.h"
#include "../libraries/SimpleJSON/json.hpp"
#include "Interval.h"
#include "Scale.h"
#include "Note.h"

#define API_KEY "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"

using json::JSON;
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
