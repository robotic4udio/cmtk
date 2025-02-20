#include "Chord.h"
#include "Arp.h"

// Include the TIMER
#include <chrono>

using namespace std::chrono;
using namespace cmtk;


int main() {


  // Create a chord

  auto c = Chord("C",1);

  auto a = ChordArp(&c);

  a.setStyle(ChordArp::Style::UpDown);
  a.setSteps(4);
  a.setJump(1);
  a.setOctaves(0);



  for(int i = 0; i < 30; ++i) {
    auto n = a.next();
    std::cout << n << " : " << n.getPitch() << std::endl;
  }



  return 0;

}
