#include "Chord.h"

// Include the TIMER
#include <chrono>

using namespace std::chrono;
using namespace cmtk;

int main() {


  // Create a chord

  auto c = Chord("C13",-2);
  
  auto intervals = c.getIntervals();
  intervals.print().printSemi();



  auto n = Note(62);
  n.print();

  //chord.print();
  auto notes = Notes(60, 63, 67, 70, 74, 77);
  notes.print();
  notes.getChordSymbol();

  Notes n2(NoteVector{Note{"C"}, Note{"D"}, Note{"G"}, Note{"Eb4"}, Note{"A4"}});
  n2.print();

  n2.getChordSymbol();

  




  return 0;

}
