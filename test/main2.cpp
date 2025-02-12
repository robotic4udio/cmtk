#include "Chord.h"

// Include the TIMER
#include <chrono>

using namespace std::chrono;
using namespace cmtk;

int main() {


  // Create a chord

  auto c = Chord("C",1);

  c.print();

  auto v = ChordVoicing(c);

  // v.setVoicing("5 9 3 11 13 6 7");
  v.setVoicing("drop2");

  v.print();

  /*
    Open Voicing: 1 7 3 5 9
    C Maj9(13) no5: 1 7 3 13 9
    C 6/9 1 5 3 6 9
    1 7 3 5
    1 5 9 3 7
    1 5 9 3 #11 13 7
  */

  
  for (int i = 0; i < 100; ++i) {
    auto n = c.getRandNote(36,60);
    std::cout << n << " : " << n.getPitch() << std::endl;
  }

  return 0;

}
