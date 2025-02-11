#include "Chord.h"

// #define CMTK_DEBUG

namespace cmtk {

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordType Class ----------------------------------------- //
// -------------------------------------------------------------------------------------------- //
ChordType::ChordType( std::string chordSymbol)
{
    set(chordSymbol);
}

// Set the ChordType from a set string representing the ChordType
ChordType& ChordType::set(const std::string& aChordType){
    auto chordType = aChordType;
    mChordType = chordType;

    // Initialize the quality of the chord
    Quality quality = Quality::NA;

    int n = 0;

    // Check for the quality of the chord
    if     (chordType.empty()                    ){ quality = Quality::Major;          }
    else if(removePrefix(chordType, "maj" ,false)){ quality = Quality::Major;          }
    else if(removePrefix(chordType, "min" ,false)){ quality = Quality::Minor;          }
    else if(removePrefix(chordType, "M"         )){ quality = Quality::Major;          }
    else if(removePrefix(chordType, "m"         )){ quality = Quality::Minor;          }
    else if(removePrefix(chordType, "dom" ,false)){ quality = Quality::Dominant;       }
    else if(removePrefix(chordType, "aug" ,false)){ quality = Quality::Augmented;      }
    else if(removePrefix(chordType, "+"   ,false)){ quality = Quality::Augmented;      }
    else if(removePrefix(chordType, "dim" ,false)){ quality = Quality::Diminished;     }
    else if(removePrefix(chordType, "°"   ,false)){ quality = Quality::Diminished;     }
    else if(removePrefix(chordType, "hdim",false)){ quality = Quality::HalfDiminished; }
    else if(removePrefix(chordType, "ø"   ,false)){ quality = Quality::HalfDiminished; }
    else if(removePrefix(chordType, "sus2",false)){ quality = Quality::Sus2;           }
    else if(removePrefix(chordType, "sus4",false)){ quality = Quality::Sus4;           }
    else if(removePrefix(chordType, "sus4",false)){ quality = Quality::Sus4;           }
    else if(removePrefix(chordType, "4x1" ,false)){ quality = Quality::Quartal;  n=1;  }
    else if(removePrefix(chordType, "4x2" ,false)){ quality = Quality::Quartal;  n=2;  }
    else if(removePrefix(chordType, "4x3" ,false)){ quality = Quality::Quartal;  n=3;  }
    else if(removePrefix(chordType, "4x4" ,false)){ quality = Quality::Quartal;  n=4;  }
    else if(removePrefix(chordType, "4x5" ,false)){ quality = Quality::Quartal;  n=5;  }
    else if(removePrefix(chordType, "4x6" ,false)){ quality = Quality::Quartal;  n=6;  }
    else if(removePrefix(chordType, "4x7" ,false)){ quality = Quality::Quartal;  n=7;  }
    else if(removePrefix(chordType, "5x1" ,false)){ quality = Quality::Quintal;  n=1;  }
    else if(removePrefix(chordType, "5x2" ,false)){ quality = Quality::Quintal;  n=2;  }
    else if(removePrefix(chordType, "5x3" ,false)){ quality = Quality::Quintal;  n=3;  }
    else if(removePrefix(chordType, "5x4" ,false)){ quality = Quality::Quintal;  n=4;  }
    else if(removePrefix(chordType, "5x5" ,false)){ quality = Quality::Quintal;  n=5;  }
    else if(removePrefix(chordType, "5x6" ,false)){ quality = Quality::Quintal;  n=6;  }
    else if(removePrefix(chordType, "5x7" ,false)){ quality = Quality::Quintal;  n=7;  }
    else if(removePrefix(chordType, "5"   ,false)){ quality = Quality::PowerChord;     }
    else if(startsWithNumber(chordType)          ){ quality = Quality::Dominant;       }


    // Remove stuff from the chord symbol
    removeChars(chordType, " ^()"); // Remove spaces

    // Initialize the chord tones vector based on the chord type
    switch (quality){
        case Quality::Major:          mIntervals.set({Interval(1), Interval(3)   , Interval(5)                    }); break;
        case Quality::Dominant:       mIntervals.set({Interval(1), Interval(3)   , Interval(5)                    }); break;
        case Quality::Minor:          mIntervals.set({Interval(1), Interval(3,-1), Interval(5)                    }); break;
        case Quality::Diminished:     mIntervals.set({Interval(1), Interval(3,-1), Interval(5,-1)                 }); break;
        case Quality::HalfDiminished: mIntervals.set({Interval(1), Interval(3,-1), Interval(5,-1), Interval(7,-1) }); break;
        case Quality::Augmented:      mIntervals.set({Interval(1), Interval(3)   , Interval(5, 1)                 }); break;
        case Quality::Sus2:           mIntervals.set({Interval(1), Interval(2)   , Interval(5)                    }); break;
        case Quality::Sus4:           mIntervals.set({Interval(1), Interval(4)   , Interval(5)                    }); break;
        case Quality::PowerChord:     mIntervals.set({Interval(1),                 Interval(5)                    }); break;
        case Quality::Quartal:        mIntervals.set({Interval(1)}); for(int i=0; i<n; i++) mIntervals.addStep(5);    break;
        case Quality::Quintal:        mIntervals.set({Interval(1)}); for(int i=0; i<n; i++) mIntervals.addStep(7);    break;
        case Quality::NA: break;      // TODO: Throw Error;
    }

    // Add Extension to the intervals
    const bool maj = quality == Quality::Major;
    const bool dim = quality == Quality::Diminished;
    if(removePrefix(chordType, "6")){
        mIntervals.add(Interval(6));
    }
    else if(removePrefix(chordType, "7")){
        mIntervals.add(maj ? Interval(7) : dim ? Interval(7,-2) : Interval(7,-1));
    }
    else if(removePrefix(chordType, "9")){ 
        mIntervals.add(maj ? Interval(7) : dim ? Interval(7,-2) : Interval(7,-1));
        mIntervals.add(Interval(9));
    }
    else if(removePrefix(chordType, "11")){ 
        mIntervals.add(maj ? Interval(7) : dim ? Interval(7,-2) : Interval(7,-1));
        mIntervals.add({Interval(9),Interval(11)});
    }
    else if(removePrefix(chordType, "13")){ 
        mIntervals.add(maj ? Interval(7) : dim ? Interval(7,-2) : Interval(7,-1));
        mIntervals.add({Interval(9),Interval(11),Interval(13)});
    }
    else if(removePrefix(chordType,"Maj7",false) || removePrefix(chordType,"M7")){
        mIntervals.add(Interval(7));
    }
    else if(removePrefix(chordType,"Maj9",false) || removePrefix(chordType,"M9")){
        mIntervals.add({Interval(7),Interval(9)});
    }
    else if(removePrefix(chordType,"Maj11",false) || removePrefix(chordType,"M11")){
        mIntervals.add({Interval(7),Interval(9),Interval(11)});
    }
    else if(removePrefix(chordType,"Maj13",false) || removePrefix(chordType,"M13")){
        mIntervals.add({Interval(7),Interval(9),Interval(11),Interval(13)});
    }

    // Handle more complex chords
    bool found = true;
    while(found)
    {   
        found = false;
        // Flatten
        if(removePrefix(chordType, "b3"    )){ mIntervals.setQuality( 3, -1, true); found = true; }
        if(removePrefix(chordType, "b5"    )){ mIntervals.setQuality( 5, -1, true); found = true; }
        if(removePrefix(chordType, "b7"    )){ mIntervals.setQuality( 7, -1, true); found = true; }
        if(removePrefix(chordType, "b9"    )){ mIntervals.setQuality( 9, -1, true); found = true; }
        if(removePrefix(chordType, "b11"   )){ mIntervals.setQuality(11, -1, true); found = true; }
        if(removePrefix(chordType, "b13"   )){ mIntervals.setQuality(13, -1, true); found = true; }
        
        // Sharpen
        if(removePrefix(chordType, "#3"    )){ mIntervals.setQuality(3 ,  1, true); found = true; }
        if(removePrefix(chordType, "#5"    )){ mIntervals.setQuality(5 ,  1, true); found = true; }
        if(removePrefix(chordType, "#7"    )){ mIntervals.setQuality(7 ,  1, true); found = true; }
        if(removePrefix(chordType, "#9"    )){ mIntervals.setQuality(9 ,  1, true); found = true; }
        if(removePrefix(chordType, "#11"   )){ mIntervals.setQuality(11,  1, true); found = true; }
        if(removePrefix(chordType, "#13"   )){ mIntervals.setQuality(13,  1, true); found = true; }

        // Add notes if required
        if(removePrefix(chordType, "add2"  )){ mIntervals.add(Interval( 2));        found = true; }
        if(removePrefix(chordType, "add4"  )){ mIntervals.add(Interval( 4));        found = true; }
        if(removePrefix(chordType, "add6"  )){ mIntervals.add(Interval( 6));        found = true; }
        if(removePrefix(chordType, "add9"  )){ mIntervals.add(Interval( 9));        found = true; }
        if(removePrefix(chordType, "add11" )){ mIntervals.add(Interval(11));        found = true; }
        if(removePrefix(chordType, "add13" )){ mIntervals.add(Interval(13));        found = true; }

        // Remove notes if required
        if(removePrefix(chordType, "no1"   )){ mIntervals.removeDegree( 1);         found = true; }
        if(removePrefix(chordType, "no3"   )){ mIntervals.removeDegree( 3);         found = true; }
        if(removePrefix(chordType, "no5"   )){ mIntervals.removeDegree( 5);         found = true; }
        if(removePrefix(chordType, "no7"   )){ mIntervals.removeDegree( 7);         found = true; }
        if(removePrefix(chordType, "no9"   )){ mIntervals.removeDegree( 9);         found = true; }
        if(removePrefix(chordType, "no11"  )){ mIntervals.removeDegree(11);         found = true; }
        if(removePrefix(chordType, "no13"  )){ mIntervals.removeDegree(13);         found = true; }
    }

    // Sort the chordIntervals
    mIntervals.sort();
    
    // Print warning if there are still characters left
    if(chordType.size() > 0){
        std::cerr << "ChordType::setChord(): Warning: Error parsing chord symbol: " << aChordType << " - Remaining: " << chordType << std::endl;
    }

    return *this;
}

// Get Normalized Semi from ChordType and Inversion
std::vector<int> ChordType::getSemiSignature(const std::string& chordType, int inv)
{
    auto c = ChordType(chordType);
    auto i = c.getIntervals();
    i.simplify();
    auto semi = i.getInversion(inv,1).getSemi();
    return std::move(semi);
}

// Set from semi
ChordType& ChordType::setSemi(const std::vector<int>& aX)
{
    // Notmalize the intervals
    auto X = aX;
    const int min = *std::min_element(X.begin(), X.end());
    for(auto& x : X) x -= min;
    std::sort(X.begin(), X.end());

    // Set the intervals
    mIntervals.setFromSemi(X);


    std::vector<std::string> chordTypeVec;
    int inv = 0;

    // Major Triad
    if     (equals(X,{0,7}  )){ chordTypeVec.push_back("5"); inv = 0; } // Major Triad Root Position 
    else if(equals(X,{0,5}  )){ chordTypeVec.push_back("5"); inv = 1; } // Major Triad Root Position 

    else if(equals(X,{0,4,7})){ chordTypeVec.push_back("M"); inv = 0; } // Major Triad Root Position 
    else if(equals(X,{0,3,8})){ chordTypeVec.push_back("M"); inv = 2; } // Major Triad 1st Inversion
    else if(equals(X,{0,5,9})){ chordTypeVec.push_back("M"); inv = 3; } // Major Triad 2nd Inversion
    // Minor Triad
    else if(remove(X,{0,3,7})){ chordTypeVec.push_back("m"); inv = 0; } // Minor Triad Root Position
    else if(remove(X,{0,4,9})){ chordTypeVec.push_back("m"); inv = 2; } // Minor Triad 1st Inversion
    else if(remove(X,{0,5,8})){ chordTypeVec.push_back("m"); inv = 3; } // Minor Triad 2nd Inversion
    // Diminished Triad
    else if(remove(X,{0,3,6})){ chordTypeVec.push_back("°"); inv = 0; } // Diminished Triad Root Position
    else if(remove(X,{0,3,9})){ chordTypeVec.push_back("°"); inv = 2; } // Diminished Triad 1st Inversion
    else if(remove(X,{0,6,9})){ chordTypeVec.push_back("°"); inv = 3; } // Diminished Triad 2nd Inversion
    // Augmented Triad
    else if(remove(X,{0,4,8})){ chordTypeVec.push_back("+"); } // Augmented Triad Root, 1st and 2nd Inversion
    // Sus2
    else if(remove(X,{0,2,7 })){ chordTypeVec.push_back("sus2"); inv = 0; } // Sus2 Root Position
    else if(remove(X,{0,5,10})){ chordTypeVec.push_back("sus2"); inv = 2; } // Sus2 1st Inversion
    else if(remove(X,{0,5,7 })){ chordTypeVec.push_back("sus2"); inv = 3; } // Sus2 2nd Inversion
    // Sus4
    else if(remove(X,{0,5,7 })){ chordTypeVec.push_back("sus4"); inv = 0; } // Sus4 Root Position
    else if(remove(X,{0,2,7 })){ chordTypeVec.push_back("sus4"); inv = 2; } // Sus4 1st Inversion
    else if(remove(X,{0,5,10})){ chordTypeVec.push_back("sus4"); inv = 3; } // Sus4 2nd Inversion

    std::cout << "Possible Chord Types: ";
    for(auto& c : chordTypeVec) std::cout << c << ", ";
    std::cout << std::endl;

    mChordType = mIntervals.getChordSymbol();

    

    return *this;
}

// Is the Chord a Minor Chord
bool ChordType::isKindOfMinor() const
{   
    if(mIntervals.contains(Interval(3,-1))) return true;
    if(mIntervals.contains(Interval(3)))    return false;
    if(startsWithNumber(mChordType))        return false;
    if(startsWith      (mChordType,"min" )) return true;
    if(startsWith      (mChordType,"m"   )) return true;
    if(startsWith      (mChordType,"dim" )) return true;
    if(startsWith      (mChordType,"°"   )) return true;
    if(startsWith      (mChordType,"hdim")) return true;
    if(startsWith      (mChordType,"ø"   )) return true;
    return false;
}

// Get the chord symbol
std::string ChordType::getChordType()
{
    return mChordType;
}

// Get the intervals
const Intervals& ChordType::getIntervals() const
{
    return mIntervals;
}

// Get the intervals
const Interval& ChordType::getIntervalAt(int i) const
{
    while(i < 0) i += mIntervals.size();
    return mIntervals[i];
}

// ChordType to string
std::string ChordType::toString() const
{
    return mChordType;
}

// Stream operator (friend function)
std::ostream& operator<<(std::ostream& os, const ChordType& ct)
{
    os << ct.mChordType;
    return os;
}

// Print the chordType
ChordType& ChordType::print()
{
    std::cout << "ChordType: " << mChordType << " ---> (" << mIntervals << ")" << std::endl;
    return *this;
}

// Size of ChordType
size_t ChordType::size() const 
{
    return mIntervals.size();
}




// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordVoicing Class -------------------------------------- //
// -------------------------------------------------------------------------------------------- //
//
// No Implementation Yet
// 

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Chord Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //

// The Chord Class is a class that represents a chord. It is the composition of a Note and a ChordType
// Constructor from RootNote, ChordType and BassNote
Chord::Chord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote)
{
    setChord(aRootNote,chordType,aBassNote);
}

// Constructor from RootNote and ChordType - BassNote is set to the RootNote
Chord::Chord(const Note& aRootNote, const ChordType& chordType)
{
    setChord(aRootNote,chordType);
}

// Constructor from note and chordType expressed as strings
Chord::Chord(const std::string& note, const std::string& chordType, const std::string& aBassNote)
{
    if(aBassNote.empty()) setChord(note,chordType);
    else                  setChord(note,chordType,aBassNote);
}

// Constructor from a combined chord symbol
Chord::Chord(const std::string& chordSymbol)
{
    setChord(chordSymbol);
}

// Constructor from a combined chord symbol and octave
Chord::Chord(const std::string& chordSymbol, int octave)
{
    setChord(chordSymbol);
    setOctave(octave);
}

// Set the chord from a Note and a ChordType
Chord& Chord::setChord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote)
{
    mRootNote = aRootNote;
    mChordType = chordType;
    mBassNote = aBassNote;
    return *this;
}

// Set the chord from a Note and a ChordType
Chord& Chord::setChord(const Note& aRootNote, const ChordType& chordType)
{
    return setChord(aRootNote,chordType,aRootNote);
}

// Set from a note and a chordType expressed as strings
Chord& Chord::setChord(const std::string& aRootNote, const std::string& aChordType, const std::string& aBassNote)
{
    const auto& rootNote  = Note(aRootNote);
    const auto& chordType = ChordType(aChordType);
    const auto& bassNote  = aBassNote.empty() ? rootNote : Note(aBassNote).setOctave(rootNote.getOctave()-1);
    return setChord(rootNote,chordType,bassNote);
}

Chord& Chord::setChord(const std::string& chordSymbol)
{
    // Find the first non note character
    auto pos = chordSymbol.find_first_not_of("ABCDEFGb#");
    auto slashPos = chordSymbol.find_first_of('/');

    // Split the string into Note and ChordType
    std::string noteString  = chordSymbol.substr(0,pos);
    std::string chordString = pos == chordSymbol.npos ? "" : chordSymbol.substr(pos,slashPos-pos);
    std::string slashString = slashPos == chordSymbol.npos ? "" : chordSymbol.substr(slashPos+1);

    #ifdef CMTK_DEBUG
    // Print Debug Info
    std::cout << "NoteString: " << noteString 
                << ", ChordString: " << chordString
                << ", Slash: " << slashString 
                << std::endl;
    #endif

    // Set the chord
    return setChord(noteString,chordString,slashString);
}

Chord Chord::NewRoman(const std::string& chordSymbol, const Note& aTonic)
{
    Chord chord;
    chord.setRoman(chordSymbol,aTonic);
    return std::move(chord);
}

Chord Chord::NewRoman(const std::string& chordSymbol, const std::string& aTonic)
{
    return NewRoman(chordSymbol,Note(aTonic));
}

// Set the Chord from a Roman Chord String 
Chord& Chord::setRoman(const std::string& romanChordSymbol, const Note& aTonic)
{
        
    // Find the first non note character
    auto pos  = romanChordSymbol.find_first_not_of("iIvVxXb#");
    auto spos = romanChordSymbol.find("/");

    // Split the string into Note and ChordType
    std::string romanString  = romanChordSymbol.substr(0,pos);
    std::string chordString = (pos  == romanChordSymbol.npos) ? "" : romanChordSymbol.substr(pos,spos-pos);
    std::string slashString = (spos == romanChordSymbol.npos) ? "" : romanChordSymbol.substr(spos+1);

    // Get the root note from the tonic using the roman string
    const Note& rootNote = aTonic.getNoteAt(Interval::NewFromRoman(romanString));

    // Find out if the chordString is minor or major, it is minor is the iv symbols are lowercase
    if(!isRomanMajorSymbol(romanString))
    {   
        // Find out if chordString starts with minor symbol, i.e. m,°,ø,min,dim,hdim using a std function
        if(chordString.empty() || isdigit(chordString[0]) || chordString[0] == 'M') chordString.insert(0,"m");
    }  

    #ifdef CMTK_DEBUG
    std::cout << "Roman: ("   << romanString << ")"
                << ", Chord: (" << chordString << ")"
                << ", Slash: (" << slashString << ")"
                << ", Tonic: (" << aTonic.toString(false) << ")"
                << ", Root: ("  << rootNote.toString(false) << ")"
                << std::endl;
    #endif

    // Create ChordType Object
    const auto& chordType = ChordType(chordString);

    // Set Chord if no Slash
    if(slashString.empty())
    {
        setChord(rootNote,chordType);
        return *this;
    }

    // Set Chord if Symbol after slash is Arabic
    if(isArabicChordSymbol(slashString))
    {
        const Note& bassNote = aTonic.getNoteAt(Interval(slashString));
        setChord(rootNote,chordType,bassNote);
        return *this;
    } 

    // Set Chord if Symbol after slash is Roman
    if(isRomanChordSymbol(slashString))
    {
        const Note& bassNote = aTonic.getNoteAt(Interval::NewFromRoman(slashString));
        setChord(rootNote,chordType,bassNote);
        return *this;
    }

    return *this;
}

// Set the Chord from a Roman Chord String
Chord& Chord::setRoman(const std::string& aRomanChordSymbol, const std::string& aTonic)
{
    return setRoman(aRomanChordSymbol,Note(aTonic));
}

// Set the Chord from a Roman Chord String
Chord& Chord::setRoman(const std::string& aRomanChordSymbol, int aTonic)
{
    return setRoman(aRomanChordSymbol,Note(aTonic));
}

// Set the Chord from a Roman Chord String
Chord& Chord::setRoman(const std::string& aRomanChordSymbol)
{
    return setRoman(aRomanChordSymbol,mRootNote);
}

// Get Roman Chord Symbol from Chord and Tonic
std::string Chord::getRoman(const Note& aTonic) const
{
    // Get the interval from the tonic to the root note
    const auto& interval = aTonic.getIntervalTo(mRootNote);

    // Get the roman numeral from the interval
    const auto& romanString = interval.getRoman(!mChordType.isKindOfMinor());

    auto chordTypeString = mChordType.toString();
    removePrefix(chordTypeString,"min");
    removePrefix(chordTypeString,"m"  );

    // The Result String
    std::string res = romanString + chordTypeString;

    // Handle the Slash Chord
    if(isSlashChord())
    {
        // Get the BassInterval from the tonic to the root note
        const auto& bassInterval = aTonic.getIntervalTo(mBassNote);
        res += "/";
        res += bassInterval.toString();
    }

    // Return the result
    return std::move(res);
}

// Print the Roman Chord
Chord& Chord::printRoman(const Note& aTonic)
{
    std::cout << "Roman: " << getRoman(aTonic) << std::endl;
    return *this;
}

// Set Chord Type
Chord& Chord::setType(const ChordType& chordType)
{
    mChordType = chordType;
    return *this;
}

// Set Chord Type
Chord& Chord::setType(const std::string& chordType)
{
    mChordType = ChordType(chordType);
    return *this;
}

// Get the chord type
const ChordType& Chord::getType() const
{
    return mChordType;
}

// Set the RootNote
Chord& Chord::setRoot(const Note& note, bool keepOctave)
{
    bool bassEqualRoot = mRootNote == mBassNote;
    auto rootOctave    = mRootNote.getOctave();
    auto bassOctave    = mBassNote.getOctave();

    auto diff = note-mRootNote;

    mBassNote.transpose(diff);
    mRootNote = note;
    if(keepOctave){
        mRootNote.setOctave(rootOctave);
        mBassNote.setOctave(bassOctave);
    }

    return *this;
}

// Set the RootNote
Chord& Chord::setRoot(const std::string& note)
{
    // Keep the octave if none is given in the string
    return setRoot(Note(note),!isdigit(note.back()));
}

Chord& Chord::setRoot(int note)
{
    return setRoot(Note(note));
}

// Get the note
const Note& Chord::getRoot() const
{
    return mRootNote;
}

const Note& Chord::getRoot(int low, int high) const
{
    auto root = mRootNote;
    while(root.getPitch() < low)  root.shiftOctave( 1);
    while(root.getPitch() > high) root.shiftOctave(-1);
    return root;
}

// Set the BassNote
Chord& Chord::setBass(const Note& note, bool keepOctave)
{
    mBassNote = note;
    if(keepOctave) mBassNote.setOctave(mRootNote.getOctave());
    return *this;
}

// Set the BassNote
Chord& Chord::setBass(const std::string& note)
{
    // Keep the octave if none is given in the string
    return setBass(Note(note),!isdigit(note.back()));
}

// Set Bass from Semitone
Chord& Chord::setBass(int note)
{
    return setBass(Note(note));
}

// Set Bass from Interval with respect to the root note
Chord& Chord::setBass(const Interval& interval, bool keepOctave)
{
    mBassNote = mRootNote.getNoteAt(interval);
    if(keepOctave) mBassNote.setOctave(mBassNote.getOctave()  );
    else           mBassNote.setOctave(mRootNote.getOctave()-1);
    return *this;
}

// Set Bass from Root
Chord& Chord::rootBass()
{
    mBassNote = mRootNote;
    return *this;
}

bool Chord::isSlashChord() const
{
    return mBassNote.getPitchWrap() != mRootNote.getPitchWrap();
}

// Force bass into range
Chord& Chord::forceBassInRange(int min, int max)
{
    while(mBassNote.getPitch() < min) mBassNote.shiftOctave( 1);
    while(mBassNote.getPitch() > max) mBassNote.shiftOctave(-1);
    return *this;
}

// Get the Bass note
const Note& Chord::getBass() const
{
    return mBassNote;
}

const Note& Chord::getBass(int low, int high) const
{
    auto bass = mBassNote;
    while(bass.getPitch() < low)  bass.shiftOctave( 1);
    while(bass.getPitch() > high) bass.shiftOctave(-1);
    return bass;
}

// Set Octave
Chord& Chord::setOctave(int octave, bool keepBass)
{   
    // Set the octave of the root note
    int prev_octave = mRootNote.getOctave();
    mRootNote.setOctave(octave);

    if(keepBass) return *this;

    int diff = octave - prev_octave;

    if(diff == 0) return *this;

    // Set the octave of the bass note
    mBassNote.shiftOctave(diff);
    return *this;
}

// Get Octave
int Chord::getOctave() const
{
    return mRootNote.getOctave();
}

// Set Bass Octave
Chord& Chord::setBassOctave(int octave)
{
    mBassNote.setOctave(octave);
    return *this;
}

// Get Bass Octave
int Chord::getBassOctave() const
{
    return mBassNote.getOctave();
}

// Get Intervals
const Intervals& Chord::getIntervals() const
{
    return mChordType.getIntervals();
}

// Get Interval at index
const Interval& Chord::getIntervalAt(int index) const
{
    while(index < 0)                  index += mChordType.size();
    while(index >= mChordType.size()) index -= mChordType.size();
    return mChordType.getIntervalAt(index);
}

// Get the Notes of the chord
Notes Chord::getNotes() const
{
    const auto& intervals = getIntervals();
    return mRootNote.getNoteAt(getIntervals());
}

Note Chord::getNoteAt(int index) const
{
    return mRootNote.getNoteAt(getIntervalAt(index));
}

// Transpose the Chord
Chord& Chord::transpose(int semitones)
{
    mRootNote.transpose(semitones);
    mBassNote.transpose(semitones);
    return *this;
}

Chord& Chord::transpose(const Interval& interval)
{
    mRootNote.transpose(interval);
    mBassNote.transpose(interval);
    return *this;
}

// Stream operator (friend function)
std::ostream& operator<<(std::ostream& os, const Chord& Chord)
{
    os << Chord.mRootNote << " " << Chord.mChordType;
    return os;
}

// Get Chord as string
std::string Chord::toString() const
{
    std::string res;
    res += getRoot().toString(false);
    res += mChordType.toString();
    if(isSlashChord()){
        res += "/";
        res += mBassNote.toString(false);
    }

    return std::move(res);
}

// Print the chord
Chord& Chord::print(bool simplify)
{
    bool slashBass = isSlashChord();
    std::cout << getRoot().toString(false) << mChordType;        
    if(slashBass) std::cout << "/" << mBassNote.toString(false);
    std::cout << " -> (" << getIntervals() << ")" 
                << " -> (";
    std::cout <<  getNotes().toString(false,simplify) << ")" 
                << " -> (" << getNotes().getPitchString() << ")";

    if(slashBass) std::cout << "\tBass: " << mBassNote.toString(true,simplify) << " -> " << mBassNote.getPitch();

    std::cout << std::endl;

    return *this;
}

size_t Chord::size() const 
{
    return mChordType.size();
}


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordVoicing Class -------------------------------------- //
// -------------------------------------------------------------------------------------------- //
ChordVoicing::ChordVoicing(Chord& aChord, const std::string aVoicing)
:mChord(aChord)
{
    setVoicing(aVoicing);
}

ChordVoicing& ChordVoicing::setVoicing(const std::string& aVoicing)
{
    mVoicing = aVoicing;
    return *this;
}

// Get Notes
Notes ChordVoicing::getNotes()
{
    // If the voicing is empty, then return the chord notes
    if(mVoicing.empty()) return mChord.getNotes();

    auto intervals = mChord.getIntervals();
    Notes notes;

    auto sv = split(mVoicing, ' ');

    bool addRest = false;
    int last = -1;  
    Note minNote(  0);
    Note maxNote(127);
    std::set<int> usedDegrees;
    for(auto s : sv){
        int transpose = 0;
        transpose += removeCount(s, '+');
        transpose -= removeCount(s, '-');

        if(s == "*"){
            addRest = true;
            continue;
        }
        else if(s == "B"){
            notes.push_back(mChord.getBass());
            if(transpose) notes.back().shiftOctave(transpose);
            continue;
        }
        else if(removePrefix(s,"L:"))
        {
            if(isNumber(s)) minNote.set(std::stoi(s));
            else            minNote.set(s);
        }
        else if(removePrefix(s,"H:"))
        {
            if(isNumber(s)) maxNote.set(std::stoi(s));
            else            maxNote.set(s);
        }
        else if(isNumber(s)){
            int d = std::stoi(s);
            if(intervals.containsDegree(d)){
                usedDegrees.insert(d);
                auto i = intervals.getIntervalFromDegree(d);
                auto n = mChord.getRoot() + i;
                while(n.getPitch() < last) n.shiftOctave(1);
                if(transpose) notes.back().shiftOctave(transpose);
                notes.push_back(n);
                last = n;
            }
        }
    }

    // Remove the used degrees
    for(auto d : usedDegrees){
        intervals.removeDegree(d);
    }

    // Add the rest of the intervals
    if(addRest){
        for(auto i : intervals){
            auto n = mChord.getRoot() + i;
            while(n.getPitch() < last) n.shiftOctave(1);
            notes.push_back(n);
            last = n;
        }
    }

    // Force notes into range
    for(auto& n : notes){
        while(n < minNote) n.shiftOctave(1);
        while(n > maxNote) n.shiftOctave(-1);
    }

    // Remove duplicates
    notes.removeDuplicates().sort();

    // Return the notes
    return std::move(notes);
}

ChordVoicing& ChordVoicing::setChord(Chord& aChord)
{
    mChord = aChord;
    return *this;
}

ChordVoicing& ChordVoicing::print(bool simplify)
{
    std::cout << mChord.toString() << " -> Voicing(" << mVoicing << ") -> (";
    auto notes = getNotes();
    std::cout <<  notes.toString(false,simplify) << ")" 
            << " -> (" << getNotes().getPitchString() << ")";
    std::cout << std::endl;
    return *this;
}

// -----PRIVATE FUNCTIONS----- //
// Remove all occurences of a character from a string and return the number of occurences
int ChordVoicing::removeCount(std::string& s, char c)
{
    int count = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == c)
        {
            count++;
            s.erase(i,1);
            i--;
        }
    }
    return count;
}



// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordProg Class ----------------------------------------- //
// -------------------------------------------------------------------------------------------- //
// Constructor to create a chord progression from a vector of chords
ChordProg::ChordProg(const ChordVector& chords, const Note& aTonic)
{
    mTonic = aTonic;
    this->set(chords);
}

// Constructor to create a chord progression from a vector of chord symbols
ChordProg::ChordProg(const std::vector<std::string>& chordSymbols, const Note& aTonic)
{
    mTonic = aTonic;
    this->set(chordSymbols);
}

// Constructor to create a chord progression from a string of chord symbols
ChordProg::ChordProg(const std::string& chordSymbols, const Note& aTonic)
{
    mTonic = aTonic;
    if(isRomanChordSymbol(chordSymbols)){
        this->setRoman(chordSymbols,aTonic);
    }
    else {
        this->set(chordSymbols);
    }
}

// Constructor to create a chord progression from a string of chord symbols
ChordProg::ChordProg(const std::string& chordSymbols, const std::string& aTonic)
{
    mTonic = Note(aTonic);
    if(isRomanChordSymbol(chordSymbols)){
        this->setRoman(chordSymbols,mTonic);
    }
    else {
        this->set(chordSymbols);
    }
}

// Function to set the chord progression from a vector of chords
ChordProg& ChordProg::set(const ChordVector& chords)
{
    *this = chords;
    return *this;
}

// Function to set the chord progression from a vector of chord symbols
ChordProg& ChordProg::set(const std::vector<std::string>& chordSymbols)
{
    this->clear();
    for (int i = 0; i < chordSymbols.size(); i++) {
        this->push_back(Chord(chordSymbols[i]));
    }
    return *this;
}

// Function to set the chord progression from a vector of chord symbols
ChordProg& ChordProg::setRoman(const std::vector<std::string>& chordSymbols, const Note& aTonic)
{
    this->clear();
    mTonic = aTonic ? aTonic : Note("C");
    for (int i = 0; i < chordSymbols.size(); i++) {
        this->push_back(Chord::NewRoman(chordSymbols[i], mTonic));
    }
    return *this;
}

// Function to set the chord progression from string of chord symbols
ChordProg& ChordProg::set(const std::string& chordSymbols)
{
    // Use the vector-based set function
    set(chordStringToVector(chordSymbols));
    return *this;
}

// Function to set the chord progression from string of chord symbols
ChordProg& ChordProg::setRoman(const std::string& chordSymbols, const Note& aTonic)
{
    // Use the vector-based set function
    setRoman(chordStringToVector(chordSymbols),aTonic);
    return *this;
}

// Function to add a chord to the progression
ChordProg& ChordProg::addChord(const Chord& chord)
{
    ChordVector::push_back(chord);
    return *this;
}

// Function to add a chord to the progression
ChordProg& ChordProg::addChord(const std::string& chordSymbol)
{
    ChordVector::push_back(Chord(chordSymbol));
    return *this;
}

// Function to add a Roman chord to the progression
ChordProg& ChordProg::addRoman(const std::string& romanChordSymbol, const Note& tonic)
{
    ChordVector::push_back(Chord::NewRoman(romanChordSymbol, tonic));
    return *this;
}

// Function to clear the progression
ChordProg& ChordProg::clear()
{
    ChordVector::clear();
    return *this;
}

ChordProg& ChordProg::transpose(int n)
{
    auto it = ChordVector::begin();
    while(it != ChordVector::end())
    {   
        it->transpose(n);
        it++;
    }
    if(mTonic) mTonic.transpose(n); 
    return *this; 
}

// Print the chord progression
ChordProg& ChordProg::printChords()
{
    auto it = this->begin();
    while (it != this->end()) {
        it->print();
        it++;
    }
    return *this;
}

std::string ChordProg::toString() const
{
    std::string res;
    auto it = this->begin();
    while (it != this->end()) {
        res += it->toString();
        if(++it != this->end()) res += "|";
    }
    return std::move(res);
}

// Print the chord progression
ChordProg& ChordProg::print(bool simplify)
{
    std::cout << "ChordProg: (";
    auto it = this->begin();
    int i = 0;
    while (it != this->end()) {
        std::cout << it->toString();
        if(++it != this->end()) std::cout << "|";
    }
    std::cout << ")";
    if(mTonic) std::cout << "  <==>  " << mTonic.toString(simplify) <<  " : (" << getRoman(mTonic) << ")";
    std::cout << std::endl;
    return *this;
}

// Get Roman Chord Symbols
std::string ChordProg::getRoman(const Note& aTonic) const
{
    auto tonic = aTonic ? aTonic : mTonic ? mTonic : Note("C");
    std::string romanChordSymbols;
    auto it = this->begin();
    while (it != this->end()) {
        romanChordSymbols += it->getRoman(tonic);
        if(++it != this->end()) romanChordSymbols += "|";
    }
    return std::move(romanChordSymbols);
}

// Print the chord progression as Roman Chords
ChordProg& ChordProg::printRoman(const Note& aTonic)
{
    std::cout << "Roman: (" << getRoman(aTonic ? aTonic : mTonic ? mTonic : Note("C")) << ")" << std::endl;
    return *this;
}

// Print the chord progression as Roman Chords
ChordProg& ChordProg::printRoman()
{
    return printRoman(mTonic);   
}

// Set the Tonic
ChordProg& ChordProg::setTonic(const Note& aTonic)
{
    mTonic = aTonic;
    return *this;
}
// Set the Tonic
ChordProg& ChordProg::setTonic(const std::string& aTonic)
{
    mTonic = Note(aTonic);
    return *this;
}

// Get the Tonic
const Note& ChordProg::getTonic() const
{
    return mTonic;
}

// Change Tonic
ChordProg& ChordProg::changeKey(const Note& aTonic)
{
    if(!mTonic) mTonic = at(0).getRoot();
    if(mTonic) transpose(aTonic.getPitch()-mTonic.getPitch());
    mTonic = aTonic;
    return *this;
}
// Change Tonic
ChordProg& ChordProg::changeKey(const std::string& aTonic)
{
    return changeKey(Note(aTonic));
}

// Get Notes used in the progression
Notes ChordProg::getNotes() const
{
    Notes notes;
    for(auto& chord : *this){
        notes.add(chord.getNotes());
    }
    // Remove duplicates and octave
    notes.removeDuplicates();

    return std::move(notes);
}

// Get the Chord at index
Chord& ChordProg::chordAt(int index)
{
    return ChordVector::at(index);
}


// static std::map<std::string, ChordProg> Map;

// ------------------------------Private Functions--------------------------------------- //

// Function to convert a string of chord symbols to a vector of chord symbols
std::vector<std::string> ChordProg::chordStringToVector(std::string chordSymbols)
{
    // Remove all spaces from the chord symbols
    chordSymbols.erase(std::remove(chordSymbols.begin(), chordSymbols.end(), ' '), chordSymbols.end());

    std::vector<std::string> chordSymbolsVector;
    std::string chordSymbol;
    for (int i = 0; i < chordSymbols.size(); i++) {
        auto c = chordSymbols[i];
        if (c == '|' || c == ','){
            if(chordSymbol.size() > 0){
                chordSymbolsVector.push_back(chordSymbol);
                chordSymbol = "";
            }
        } 
        else {
            chordSymbol += chordSymbols[i];
        }
    }
    // If a chordSymbol is still present push it to the vector
    if(chordSymbol.size() > 0) chordSymbolsVector.push_back(chordSymbol);

    // Use the vector-based set function
    return std::move(chordSymbolsVector);
}



// Initialize the static member variable sProgressions
std::map<std::string, ChordProg> ChordProg::Map = {
//   // Major Progressions
    {"DooWop"         ,ChordProg("I|vi|IV|V"                 )},
    {"Axis"           ,ChordProg("I|V|vi|IV"                 )},
    {"Axis2"          ,ChordProg("vi|IV|I|V"                 )},
    {"M3425"          ,ChordProg("iii|IV|ii|V"               )},
    {"RedHot2"        ,ChordProg("I|V|ii|IV"                 )},
    {"RedHot3"        ,ChordProg("IV|I|V|vi"                 )},
    {"RedHot4"        ,ChordProg("I|V|vi|IV"                 )},
    {"RoyalRoad"      ,ChordProg("I|IV|iii|vi"               )},
    {"Japan"          ,ChordProg("IV|V|iii|vi"               )},
    {"Emotional"      ,ChordProg("vi|IV|V|iii"               )},
    {"MysteryClimb"   ,ChordProg("IV|V|vi"                   )},
    {"Evanescence"    ,ChordProg("I|iii|I|iii"               )},
    {"Christiania"    ,ChordProg("I|iii|vi|V|IV|I|ii|V"      )},
    {"Love"           ,ChordProg("I|V/7|vi|iii/5|IV|I/3|ii|V")},
    {"Canon"          ,ChordProg("D|A|Bm|F#m|G|D|G|A7","D")},
    {"Major 5ths"     ,ChordProg("Am7|Dm7|G7|CM7|FM7|Bm7b5|Em7|Am", Note("C"))},


    {"KissFromARose"     ,ChordProg("bVI|bVII|I"                )}, // Aeolian (Major 1 Chord)
    {"SuperMarioCadence" ,ChordProg("I|bVI|bVII|I"              )}, // Aeolian (Major 1 Chord)

    // Minor Progressions
    {"JonnyMinor1"    ,ChordProg("Am|Dm|B°|E"  ,Note("A"))}, // Harmonic Minor
    {"JonnyMinor2"    ,ChordProg("Am|F|C|G"    ,Note("A"))}, // Natural Minor
    {"JonnyMinor3"    ,ChordProg("Am|C|D|E"    ,Note("A"))}, 
    {"JonnyMinor3"    ,ChordProg("Am|Em|G|D"   ,Note("A"))}, 
    {"Andalusian"     ,ChordProg("i|bVII|bVI|V"          )}, // Aeolian (Major 5th Chord)
    {"Interstellar"   ,ChordProg("F|G|Am|G|F"  ,Note("A"))}, // by Hans Zimmer (Interstellar) - Root A, Scale Minor

    // Aeolian Progressions
    {"AeolianCascade" ,ChordProg("i|bIII|bVII|iv"        )},
    {"AeolianVamp"    ,ChordProg("i|bVII|bVI|bVII"       )},

    // Dorian Progressions
    {"PlagelCascade"  ,ChordProg("i|bIII|bVII|IV")},
    {"DorianVamp"     ,ChordProg("i|IV|i|IV")},
    {"DorianVamp2"    ,ChordProg("i|ii|i|ii")},
    {"Dorian1374"     ,ChordProg("i|bVII|bIII|IV")},
    {"Time"           ,ChordProg("Am|Em|G|D|CM7|Em|G|D", Note("A"))}, // by Hans Zimmer (Inception) - Root A, Scale Dorian
    {"UptownFunk"     ,ChordProg("Dm7|G7"              , Note("D"))}, // Bruno Mars: Uptown Funk (DorianVamp) - https://tabs.ultimate-guitar.com/tab/bruno-mars/uptown-funk-chords-1710737 

    // Mixolydian
    {"MixolydianVamp"     ,ChordProg("I|bVII|IV|I"               )},

    // Mixolydian b6
    {"PrincessLeia"       ,ChordProg("I|iv6")}, // Mixolydian b6, Harmonic Major

    // Progressions Named by the Song they are taken from
    {"Hes A Pirate A"     , ChordProg("Dm|Bb|Am|Dm|Bb|F|C|Dm|Dm|Gm|Bb|Dm|Bb|Dm|A|A7" , Note("D"))}, // by Hans Zimmer (Pirates of the Caribean) - Root D-Aeolian (Major 5th Chord)
    {"Hes A Pirate Bridge", ChordProg("A|Dm|C|Dm|A|Dm|Gm|A"                          , Note("D"))}, // by Hans Zimmer (Pirates of the Caribean) - Root D-Aeolian (Major 5th Chord)
    {"Hes A Pirate B"     , ChordProg("Dm|Dm|C|Dm|Dm|Dm|C|Dm"                        , Note("D"))}, // by Hans Zimmer (Pirates of the Caribean) - Root D-Aeolian (Major 5th Chord)
    {"Hes A Pirate C"     , ChordProg("Dm|C|F|Bb|F|Am|Dm|Dm|Dm|C|F|Bb|Gm|Bb|Am|A"    , Note("D"))}, // by Hans Zimmer (Pirates of the Caribean) - Root D-Aeolian (Major 5th Chord)
    {"Hes A Pirate Chorus", ChordProg("Dm|Bb|F|C|Gm|Dm|A7|Dm"                        , Note("D"))}, // by Hans Zimmer (Pirates of the Caribean) - Root D-Aeolian (Major 5th Chord)
    // https://www.youtube.com/watch?v=WbRtz5Trnbo
    {"Ghibli Marry"       , ChordProg("Cm|D7|Gm|Fm6/D,Bb7|EbM7|F/Eb|Dm|Gm|Em7b5|A7|Dm7|C|Bb|A|D7")}, // Joe Hisaishi - Studio Ghibli
    {"Ghibli Spirited"    , ChordProg("Gb|Ab|Db|Bbm", Note("Db"))}, // Joe Hisaishi - Studio Ghibli Db Major
    {"Ghibli3"            , ChordProg("AbM7|Eb/G",Note("C"))}, // Use C-Minor Pentatonic Scale over this 
    {"2-5-1"              , ChordProg("ii7|V7|I7"                 )},
    {"AugmentedClimb"     , ChordProg("I|I+|I6no5|I7no5|IV"       )},
    {"LastNightOnEarth"   , ChordProg("I|I+|I6no5|I7no5|IV|iv|I|I")},
    {"ClapHands"          , ChordProg("Bm|G7","B")}, // Tom Waits: ClapHands - https://tabs.ultimate-guitar.com/tab/tom-waits/clap-hands-chords-876967
    {"LayLadyLayA1"       , ChordProg("A|C#m|G|Bm", Note("A"))}, // Johnny Cash: Hurt - https://tabs.ultimate-guitar.com/tab/johnny-cash/hurt-chords-108013
    {"LayLadyLayA2"       , ChordProg("E|F#m|A|A" , Note("A"))}, // Johnny Cash: Hurt - https://tabs.ultimate-guitar.com/tab/johnny-cash/hurt-chords-108013
    {"Creep"              , ChordProg("I|III|IV|iv","G")}, // Radiohead: Creep - Original Key G
    {"LayLadyLayA2"       , ChordProg("E|F#m|A|A"                , "A")}, // Hello by Adele https://www.youtube.com/watch?v=rQXendWErCA
    {"Hello Verse"        , ChordProg("Fm|Ab|Eb|Db"              , "F")},
    {"Hello PreChorus"    , ChordProg("Fm|Eb|Cm|Db|Fm|Eb|Db|Db"  , "F")},
    {"Hello Chorus"       , ChordProg("Fm|Db|Ab|Eb"              , "F")},
    {"Hello Bridge"       , ChordProg("Fm|Db|Eb|Ab"              , "F")},


};


ChordProg ChordProg::Get(const std::string& aChordProg)
{
    if(aChordProg == "Christiania") return Scale::GetChordProg("C-Major-13654125"); // Christiania: I kan ikke slå os ihjel - https://www.youtube.com/watch?v=3Z8Y6ZUJ1dA

    // Check if the chord progression is already in the map, if so return it
    auto it = Map.find(aChordProg);
    if(it != Map.end()) return it->second;

    // If the chord progression is not in the map, then create it from Scale
    ChordProg chordProg;
    
    // Try to get the chord progression from the Scale
    try {
        chordProg = Scale::GetChordProg(aChordProg);
        return chordProg;
    } 
    catch (const std::exception& e) {
        // Handle the exception here
        // You can print an error message or take appropriate action
        // For example, you can set chordProg to a default value or throw a new exception
        // depending on your application's requirements
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        chordProg = ChordProg(aChordProg);
        return chordProg;
    }
    catch (const std::exception& e) {
        // Handle the exception here
        // You can print an error message or take appropriate action
        // For example, you can set chordProg to a default value or throw a new exception
        // depending on your application's requirements
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return chordProg;   
}



} // namespace cmtk





/*



// ----------------------------------------------------------------------- //
// ----------------------- ChordSequencer Class -------------------------- //
// ----------------------------------------------------------------------- //
class ChordSequencer {
public:
    // Constructor
    ChordSequencer() = default;

    // Function to set the chord progression
    void set(const ChordProg& aChordProg)
    {
        chordProgression = aChordProg;
        rewind();
    }

    std::vector<int> next(int min=0, int max=127, int mindist=0)
    {
        // If the chord progression is empty then return an empty vector
        if(chordProgression.empty()) return {};
        // Loop through the chord progression
        if(++index >= chordProgression.size()) index = 0;
        // Return the chord tones
        current = chordProgression[index].getSemi();
        return current;
    }

    int getBassNote(int min=0, int max=127)
    {
        return chordProgression[index].getBass(min,max);
    }

    // Function to reset the sequencer
    void rewind()
    {
        index = -1;
    }

private:
    ChordProg chordProgression;
    int index = -1;
    std::vector<int> current = {};
};



// ----------------------------------------------------------------------- //
// ----------------------- ChordProgs Class ----------------------- //
// ----------------------------------------------------------------------- //
class ChordProgs {
public:
    // Constructor
    ChordProgs()
    {
        // Create the chord progressions
        // createChordProgs();
    };

    // Function to create the chord progressions
    void createChordProgs()
    {
        // Sad Chord Progressions from https://www.pianote.com/blog/sad-chord-progressions/
        chordProgressions["PopProgression"]      = ChordProg("vi|IV|I|V");
        chordProgressions["HarmonicMinorAxis"]   = ChordProg("vi|IV|I|bIII");  // Check this progression - Not Harmonic minor
        chordProgressions["Creep"]               = ChordProg("I|III|IV|iv");
        chordProgressions["HarmonicVamp"]        = ChordProg("i|i|bVI|V");
        chordProgressions["HouseOfTheRisingSun"] = ChordProg("i|III|IV|VI");
        chordProgressions["Harmonic Shift"]      = ChordProg("i|iv|III|V");
        chordProgressions["AeolianClosedLoop"]   = ChordProg("i|bVII|iv|i");   // Added to Aeolian
        chordProgressions["LanaProgression"]     = ChordProg("i|III|v|VI");
        chordProgressions["Emotional"]           = ChordProg("vi|IV|V|iii");   // Added to Major
        chordProgressions["MoonlightSonata"]     = ChordProg("i|VI|ii|V");     
        chordProgressions["Sting"]               = ChordProg("i|VII|iv|V");
        chordProgressions["MinorMysteryClimb"]   = ChordProg("IV|V|vi");
        // The 5 Sad Piano Chord Progressions https://pianowithjonny.com/piano-lessons/5-sad-piano-chord-progressions/
        chordProgressions["Evanescence"]         = ChordProg("I|iii|I|iii");
        chordProgressions["PrincessLeia"]        = ChordProg("I|iv6");
        chordProgressions["Sentimental"]         = ChordProg("i|V|i|vi7b5");             // Normally arranged with decending bass line i | V/7 | i/b7 | vi7b5
        chordProgressions["LoveProgression"]     = ChordProg("I|V|vi|iii|IV|I|ii7|V"); // I | V/7 | vi | iii/5 | IV | I/3 | ii7 | V
        // The 12 bar blues progression
        chordProgressions["Blues"]               = ChordProg("I7|IV7|I7|I7|IV7|IV7|I7|I7|V7|IV7|I7|V7");
        // Jazz Progressions
        chordProgressions["RhythmChanges"]       = ChordProg("I|vi|ii|V");
        // Cadence
        chordProgressions["PlagalCadence"]       = ChordProg("IV|I");
        chordProgressions["PerfectCadence"]      = ChordProg("V7|I");

        // Tom Waits
        chordProgressions["JockeyFullOfBourbon"]  = ChordProg("i|V");
        chordProgressions["Jockey"] = ChordProg("i|iv|i|V");
        // Clap Hands
        chordProgressions["??"] = ChordProg("i|V|iv|V");
        chordProgressions["ClapHands"] = ChordProg("i|bVI7"); // 
        chordProgressions["ChocolateJesus"] = ChordProg("i|iv|i|V7"); // Harmonic Minor

        // Hans Zimme
        chordProgressions["Time"] = ChordProg("Am|Em|G|D|CM7|Em|G|D"); // Am Em G D CM7 Em G D

    }

    // Function to add a chord progression to the map
    void add(const std::string& name, const std::string& progression)
    {
        chordProgressions[name] = ChordProg(progression);
    }

    // Function to add a chord progression to the map
    void add(const std::string& name, const ChordProg& progression)
    {
        chordProgressions[name] = progression;
    }

    // Overload index operator to get the chord progression
    ChordProg& operator[](const std::string& chordProgression)
    {
        return chordProgressions[chordProgression];
    }

    // Print all the chord progressions
    void print()
    {
        for (auto& chordProgression : chordProgressions) {
            std::cout << chordProgression.first << ":\n";
            chordProgression.second.print();
        }
    }

    void clear()
    {
        chordProgressions.clear();
    }

private:
    std::map<std::string, ChordProg> chordProgressions; // TODO: Make this into a static private member
};


*/



