#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <set>
#include <cctype>
#include "Interval.h"
#include "CMTK.h"
#include "Note.h"

namespace cmtk {

// Get Note Number from beginnign of string
inline int getNoteNumber(const std::string& s, int root=0)
{
    if(s.empty()) throw std::runtime_error("Error: Unrecognized note");

    // Is the note expressed in roman numerals
    if(isRomanChordSymbol(s)) return romanPitchToSemitone(s,root);

    // Is the note expressed in arabic numerals
    if(isArabicChordSymbol(s)) return arabicPitchToSemitone(s,root);

    // Convert to lower case
    std::string n = s;
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);    

    // Get the note number
    if     (n == "c")  return 0;
    else if(n == "d")  return 2;
    else if(n == "e")  return 4;
    else if(n == "f")  return 5;
    else if(n == "g")  return 7;
    else if(n == "a")  return 9;
    else if(n == "b")  return 11;
    else if(n == "cb") return 11;
    else if(n == "c#") return 1;
    else if(n == "db") return 1;
    else if(n == "d#") return 3;
    else if(n == "eb") return 3;
    else if(n == "e#") return 5;
    else if(n == "fb") return 4;
    else if(n == "f#") return 6;
    else if(n == "gb") return 6;
    else if(n == "g#") return 8;
    else if(n == "ab") return 8;
    else if(n == "a#") return 10;
    else if(n == "bb") return 10;
    else if(n == "b#") return 0;

    // Throw error
    throw std::runtime_error("Error: getNoteNumber(): Unrecognized note: " + s);
}




// ----------------------------------------------------------------------- //
// ---------------------------- ChordType Class -------------------------- //
// ----------------------------------------------------------------------- //
class ChordType : public CMTK {
public:
    // Constructor
    ChordType() = default;
    ChordType(const std::string& chordSymbol)
    {
        set(chordSymbol);
    }

    // Enum class to represent the quality of the chord
    enum class Quality {
        Major,
        Minor,
        Diminished,
        HalfDiminished,
        Augmented,
        Sus2,
        Sus4,
        PowerChord,
        Dominant,
        NA
    };

    // Set the ChordType from a set string representing the ChordType
    void set(const std::string& aChordType){
        auto chordType = aChordType;
        mChordType = chordType;

        // Initialize the quality of the chord
        Quality quality = Quality::NA;

        // Check for the quality of the chord
        if     (chordType.empty()                    ){ quality = Quality::Major;          }
        else if(removePrefix(chordType, "maj" ,false)){ quality = Quality::Major;          }
        else if(removePrefix(chordType, "M"         )){ quality = Quality::Major;          }
        else if(removePrefix(chordType, "min" ,false)){ quality = Quality::Minor;          }
        else if(removePrefix(chordType, "m"         )){ quality = Quality::Minor;          }
        else if(removePrefix(chordType, "5"   ,false)){ quality = Quality::PowerChord;     }
        else if(removePrefix(chordType, "dom" ,false)){ quality = Quality::Dominant;       }
        else if(startsWithNumber(chordType)          ){ quality = Quality::Dominant;       }
        else if(removePrefix(chordType, "aug" ,false)){ quality = Quality::Augmented;      }
        else if(removePrefix(chordType, "+"   ,false)){ quality = Quality::Augmented;      }
        else if(removePrefix(chordType, "dim" ,false)){ quality = Quality::Diminished;     }
        else if(removePrefix(chordType, "°"   ,false)){ quality = Quality::Diminished;     }
        else if(removePrefix(chordType, "hdim",false)){ quality = Quality::HalfDiminished; }
        else if(removePrefix(chordType, "ø"   ,false)){ quality = Quality::HalfDiminished; }
        else if(removePrefix(chordType, "sus2",false)){ quality = Quality::Sus2;           }
        else if(removePrefix(chordType, "sus4",false)){ quality = Quality::Sus4;           }

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
            case Quality::NA: break;            // TODO: Throw Error;
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
            mIntervals.add(Interval(9),Interval(11));
        }
        else if(removePrefix(chordType, "13")){ 
            mIntervals.add(maj ? Interval(7) : dim ? Interval(7,-2) : Interval(7,-1));
            mIntervals.add(Interval(9),Interval(11),Interval(13));
        }
        else if(removePrefix(chordType,"Maj7",false) || removePrefix(chordType,"M7")){
            mIntervals.add(Interval(7));
        }
        else if(removePrefix(chordType,"Maj9",false) || removePrefix(chordType,"M9")){
            mIntervals.add(Interval(7),Interval(9));
        }
        else if(removePrefix(chordType,"Maj11",false) || removePrefix(chordType,"M11")){
            mIntervals.add(Interval(7),Interval(9),Interval(11));
        }
        else if(removePrefix(chordType,"Maj13",false) || removePrefix(chordType,"M13")){
            mIntervals.add(Interval(7),Interval(9),Interval(11),Interval(13));
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
            std::cerr << "setChord(): Warning: Error parsing chord symbol: " << aChordType << " - Remaining: " << chordType << std::endl;
        }
    }

    // Is the Chord a Minor Chord
    bool isKindOfMinor() const
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
    std::string getChordType()
    {
        return mChordType;
    }

    // Get the intervals
    const Intervals& getIntervals() const
    {
        return mIntervals;
    }

    // ChordType to string
    std::string toString() const
    {
        return mChordType;
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const ChordType& ct)
    {
        os << ct.mChordType;
        return os;
    }

    // Print the chordType
    void print()
    {
        std::cout << "ChordType: " << mChordType << " ---> (" << mIntervals << ")" << std::endl;
    }

    // Size of ChordType
    size_t size() const 
    {
        return mIntervals.size();
    }

private:
    std::string mChordType = "";
    Intervals mIntervals = Intervals({Interval(1), Interval(3), Interval(5)});
};

// ----------------------------------------------------------------------- //
// ---------------------------- ChordVoicing Class ----------------------- //
// ----------------------------------------------------------------------- //
class ChordVoicing : std::vector<int>  {
public:
    // For now it is just a vector of ints representing the order of degrees in the intervals


private:

};

// ----------------------------------------------------------------------- //
// ---------------------------- Chord Class ------------------------------ //
// ----------------------------------------------------------------------- //
// The Chord Class is a class that represents a chord. It is the composition of a Note and a ChordType
class Chord : public CMTK {
public:
    // Constructor
    Chord() = default;

    // Constructor from RootNote, ChordType and BassNote
    Chord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote)
    {
        setChord(aRootNote,chordType,aBassNote);
    }

    // Constructor from RootNote and ChordType - BassNote is set to the RootNote
    Chord(const Note& aRootNote, const ChordType& chordType)
    {
        setChord(aRootNote,chordType);
    }

    // Constructor from note and chordType expressed as strings
    Chord(const std::string& note, const std::string& chordType, const std::string& aBassNote = "")
    {
        if(aBassNote.empty()) setChord(note,chordType);
        else                  setChord(note,chordType,aBassNote);
    }

    // Constructor from a combined chord symbol
    Chord(const std::string& chordSymbol)
    {
        setChord(chordSymbol);
    }

    // Set the chord from a Note and a ChordType
    Chord& setChord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote)
    {
        mRootNote = aRootNote;
        mChordType = chordType;
        mBassNote = aBassNote;
        return *this;
    }

    // Set the chord from a Note and a ChordType
    Chord& setChord(const Note& aRootNote, const ChordType& chordType)
    {
        return setChord(aRootNote,chordType,aRootNote);
    }

    // Set from a note and a chordType expressed as strings
    Chord& setChord(const std::string& aRootNote, const std::string& aChordType, const std::string& aBassNote = "")
    {
        const auto& rootNote  = Note(aRootNote);
        const auto& chordType = ChordType(aChordType);
        const auto& bassNote  = aBassNote.empty() ? rootNote : Note(aBassNote).setOctave(rootNote.getOctave()-1);
        return setChord(rootNote,chordType,bassNote);
    }

    Chord& setChord(const std::string& chordSymbol)
    {
        // Find the first non note character
        auto pos = chordSymbol.find_first_not_of("ABCDEFGb#");
        auto slashPos = chordSymbol.find_first_of('/');

        // Split the string into Note and ChordType
        std::string noteString  = chordSymbol.substr(0,pos);
        std::string chordString = pos == chordSymbol.npos ? "" : chordSymbol.substr(pos,slashPos-1);
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

    static Chord newRoman(const std::string& chordSymbol, const Note& aTonic)
    {
        Chord chord;
        chord.setRoman(chordSymbol,aTonic);
        return std::move(chord);
    }

    static Chord newRoman(const std::string& chordSymbol, const std::string& aTonic)
    {
        return newRoman(chordSymbol,Note(aTonic));
    }

    // Set the Chord from a Roman Chord String 
    Chord& setRoman(const std::string& romanChordSymbol, const Note& aTonic)
    {
         
        // Find the first non note character
        auto pos  = romanChordSymbol.find_first_not_of("iIvVxXb#");
        auto spos = romanChordSymbol.find("/");

        // Split the string into Note and ChordType
        std::string romanString  = romanChordSymbol.substr(0,pos);
        std::string chordString = (pos  == romanChordSymbol.npos) ? "" : romanChordSymbol.substr(pos,spos-pos);
        std::string slashString = (spos == romanChordSymbol.npos) ? "" : romanChordSymbol.substr(spos+1);

        // Get the root note from the tonic using the roman string
        const Note& rootNote = aTonic.getNoteFromInterval(Interval::newFromRoman(romanString));

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
            const Note& bassNote = aTonic.getNoteFromInterval(Interval(slashString));
            setChord(rootNote,chordType,bassNote);
            return *this;
        } 

        // Set Chord if Symbol after slash is Roman
        if(isRomanChordSymbol(slashString))
        {
            const Note& bassNote = aTonic.getNoteFromInterval(Interval::newFromRoman(slashString));
            setChord(rootNote,chordType,bassNote);
            return *this;
        }

        return *this;
    }

    // Set the Chord from a Roman Chord String
    Chord& setRoman(const std::string& aRomanChordSymbol, const std::string& aTonic)
    {
        return setRoman(aRomanChordSymbol,Note(aTonic));
    }

    // Set the Chord from a Roman Chord String
    Chord& setRoman(const std::string& aRomanChordSymbol, int aTonic)
    {
        return setRoman(aRomanChordSymbol,Note(aTonic));
    }

    // Set the Chord from a Roman Chord String
    Chord& setRoman(const std::string& aRomanChordSymbol)
    {
        return setRoman(aRomanChordSymbol,mRootNote);
    }

    // Get Roman Chord Symbol from Chord and Tonic
    std::string getRoman(const Note& aTonic) const
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
    Chord& printRoman(const Note& aTonic)
    {
        std::cout << "Roman: " << getRoman(aTonic) << std::endl;
        return *this;
    }

    // Set Chord Type
    Chord& setType(const ChordType& chordType)
    {
        mChordType = chordType;
        return *this;
    }

    // Set Chord Type
    Chord& setType(const std::string& chordType)
    {
        mChordType = ChordType(chordType);
        return *this;
    }
    
    // Get the chord type
    const ChordType& getType() const
    {
        return mChordType;
    }

    // Set the RootNote
    Chord& setRoot(const Note& note, bool keepOctave=false)
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
    Chord& setRoot(const std::string& note)
    {
        // Keep the octave if none is given in the string
        return setRoot(Note(note),!isdigit(note.back()));
    }

    Chord& setRoot(int note)
    {
        return setRoot(Note(note));
    }

    // Get the note
    const Note& getRoot() const
    {
        return mRootNote;
    }

    // Set the BassNote
    Chord& setBass(const Note& note, bool keepOctave=false)
    {
        mBassNote = note;
        if(keepOctave) mBassNote.setOctave(mRootNote.getOctave());
        return *this;
    }

    // Set the BassNote
    Chord& setBass(const std::string& note)
    {
        // Keep the octave if none is given in the string
        return setBass(Note(note),!isdigit(note.back()));
    }

    // Set Bass from Semitone
    Chord& setBass(int note)
    {
        return setBass(Note(note));
    }

    // Set Bass from Interval with respect to the root note
    Chord& setBass(const Interval& interval, bool keepOctave=false)
    {
        mBassNote = mRootNote.getNoteFromInterval(interval);
        if(keepOctave) mBassNote.setOctave(mBassNote.getOctave()  );
        else           mBassNote.setOctave(mRootNote.getOctave()-1);
        return *this;
    }

    // Set Bass from Root
    Chord& rootBass()
    {
        mBassNote = mRootNote;
        return *this;
    }

    bool isSlashChord() const
    {
        return mBassNote.getPitchWrap() != mRootNote.getPitchWrap();
    }

    // Force bass into range
    Chord& forceBassInRange(int min=0, int max=127)
    {
        while(mBassNote.getMidiPitch() < min) mBassNote.shiftOctave( 1);
        while(mBassNote.getMidiPitch() > max) mBassNote.shiftOctave(-1);
        return *this;
    }

    // Get the Bass note
    const Note& getBass() const
    {
        return mBassNote;
    }

    // Set Octave
    Chord& setOctave(int octave)
    {
        mRootNote.setOctave(octave);
        return *this;
    }

    // Get Octave
    int getOctave() const
    {
        return mRootNote.getOctave();
    }

    // Get Intervals
    const Intervals& getIntervals() const
    {
        return mChordType.getIntervals();
    }

    // Get the Notes of the chord
    Notes getNotes() const
    {
        return mRootNote.getNoteFromInterval(getIntervals());
    }

    // Get the Bass note
    Chord& transpose(int semitones)
    {
        mRootNote.transpose(semitones);
        mBassNote.transpose(semitones);
        return *this;
    }

    Chord& transpose(const Interval& interval)
    {
        mRootNote.transpose(interval);
        mBassNote.transpose(interval);
        return *this;
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Chord& Chord)
    {
        os << Chord.mRootNote << " " << Chord.mChordType;
        return os;
    }

    // Get Chord as string
    std::string toString() const
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
    Chord& print(bool simplify=true)
    {
        bool slashBass = isSlashChord();
        std::cout << getRoot().toString(false) << mChordType;        
        if(slashBass) std::cout << "/" << mBassNote.toString(false);
        std::cout << " -> (" << getIntervals() << ")" 
                  << " -> (";
        std::cout <<  getNotes().toString(false,simplify) << ")" 
                  << " -> (" << getNotes().getPitchString() << ")";

        if(slashBass) std::cout << "\tBass: " << mBassNote.toString(true,simplify) << " -> " << mBassNote.getMidiPitch();

        std::cout << std::endl;

        return *this;
    }

    size_t size() const 
    {
        return mChordType.size();
    }

private:
    ChordType mChordType;  // Object representing the chord type, i.e. the basic structure of the chord
    Note mRootNote;        // The root note of the chord
    Note mBassNote;        // The bass note of the chord, this is only different from the root note if the chord is a slash chord
    ChordVoicing mVoicing; // TODO: Make a ChordVoicing class that contains the voicing of the chord
};



/*
// ----------------------------------------------------------------------- //
// ----------------------------- Chord Class ----------------------------- //
// ----------------------------------------------------------------------- //
class Chord {
public:
    // Constructor
    Chord() = default;
    Chord(const std::string& chordSymbol, int rootNote = 0)
    {
        setChord(chordSymbol, rootNote);
    }

    Chord(const Intervals& intervals, int rootNote=0)
    {
        setChord(intervals,rootNote);
    }

    // Enum class to represent the quality of the chord
    enum class Quality {
        Major,
        Minor,
        Diminished,
        HalfDiminished,
        Augmented,
        Sus2,
        Sus4,
        PowerChord,
    };

    // Create a chord from a set of intervals
    void setChord(const Intervals& aIntervals, int aRootNote)
    {
        auto intervals = aIntervals;
        intervals.print();
        std::string chordSymbol = "";
        bool maj = false;
        if     (intervals.contains("3 b7", "#5 b6")){ chordSymbol = "dom"  ; intervals.remove("3")           ; }
        else if(intervals.contains("3 #5", "b3 5" )){ chordSymbol = "aug"  ; intervals.remove("3")           ; }
        else if(intervals.contains("b3 b5","3 5"  )){ chordSymbol = "dim"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("3"            )){ chordSymbol = "maj"  ; intervals.remove("3"); maj=true ; }
        else if(intervals.contains("b3"           )){ chordSymbol = "min"  ; intervals.remove("b3")          ; }
        else if(intervals.contains("2 5","3 b3"   )){ chordSymbol = "sus2" ; intervals.remove("2")           ; }
        else if(intervals.contains("4 5","3 b3"   )){ chordSymbol = "sus4" ; intervals.remove("4")           ; }
        else if(intervals.contains("5"            )){ chordSymbol = "5"    ;                                 ; }

        // Add Extension
        if     (intervals.contains("b7 9 11 13"  )){ chordSymbol += "13"      ; intervals.remove("b7 9 11 13"   );  }
        else if(intervals.contains("b7 b9 11 13" )){ chordSymbol += "13 b9"   ; intervals.remove("b7 b9 11 13"  );  }
        else if(intervals.contains("b7 9 b11 13" )){ chordSymbol += "13 b11"  ; intervals.remove("b7 9 b11 13"  );  }
        else if(intervals.contains("b7 b9 b11 13")){ chordSymbol += "13 b9b11"; intervals.remove("b7 b9 b11 13" );  }
        else if(intervals.contains("b7 9 11"     )){ chordSymbol += "11"      ; intervals.remove("b7 9 11" );  }
        else if(intervals.contains("b7 b9 11"    )){ chordSymbol += "11 b9"   ; intervals.remove("b7 b9 11");  }
        else if(intervals.contains("b7 9"        )){ chordSymbol += "9"       ; intervals.remove("b7 9" );  }
        else if(intervals.contains("b7"          )){ chordSymbol += "7"       ; intervals.remove("b7" );  }
        else if(intervals.contains("7 9 11 13"   )){ chordSymbol += maj ? "13" : "Maj13" ; intervals.remove("7 9 11 13" );  }
        else if(intervals.contains("7 b9 11 13"  )){ chordSymbol += maj ? "13 b9" : "Maj13 b9" ; intervals.remove("7 b9 11 13" );  }
        else if(intervals.contains("7 9 b11 13"  )){ chordSymbol += maj ? "13 b11" : "Maj13 b11" ; intervals.remove("7 9 b11 13" );  }
        else if(intervals.contains("7 b9 b11 13" )){ chordSymbol += maj ? "13 b9b11" : "Maj13 b9b11" ; intervals.remove("7 b9 b11 13" );  }
        else if(intervals.contains("7 9 11"      )){ chordSymbol += maj ? "11" : "Maj11" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 b9 11"     )){ chordSymbol += maj ? "11 b9" : "Maj11 b9" ; intervals.remove("7 9 11" );  }
        else if(intervals.contains("7 9"         )){ chordSymbol += maj ? "9"  : "Maj9"  ; intervals.remove("7 9" );  }
        else if(intervals.contains("7"           )){ chordSymbol += maj ? "7"  : "Maj7"  ; intervals.remove("7" );  }

        // Check if the 5 is present
        if     (intervals.contains("b3" )){ chordSymbol += " b3"    ; intervals.remove("b3"  );  }
        else if(intervals.contains("#3" )){ chordSymbol += " #3"    ; intervals.remove("#3"  );  }

        if     (intervals.contains("b5" )){ chordSymbol += " b5"    ;                            }
        else if(intervals.contains("#5" )){ chordSymbol += " #5"    ;                            }

        if     (intervals.contains("b7" )){ chordSymbol += " b7"    ; intervals.remove("b7"  );  }
        else if(intervals.contains("#7" )){ chordSymbol += " #7"    ; intervals.remove("#7"  );  }

        if     (intervals.contains("b9" )){ chordSymbol += " b9"    ; intervals.remove("b9"  );  }
        else if(intervals.contains("#9" )){ chordSymbol += " #9"    ; intervals.remove("#9"  );  }

        if     (intervals.contains("b11")){ chordSymbol += " b11"   ; intervals.remove("b11" );  }
        else if(intervals.contains("#11")){ chordSymbol += " #11"   ; intervals.remove("#11" );  }

        if     (intervals.contains("b13")){ chordSymbol += " b13"   ; intervals.remove("b13" );  }
        else if(intervals.contains("#13")){ chordSymbol += " #13"   ; intervals.remove("#13" );  }


        // Check for no 3rd or 5th
        if(!intervals.containsDegree(1)) chordSymbol += " no1";
        else intervals.removeDegree(1);

        if(!intervals.containsDegree(5)) chordSymbol += " no5";
        else intervals.removeDegree(5);


        // Check added notes
        static std::vector<std::string> addedNotes = {
            "b2" , "2" , "#2" , 
            "b3" , "3" , "#3" ,
            "b4" , "4" , "#4" ,
            // "b5" , "5" , "#5" ,
            "b6" , "6" , "#6" ,
            "b7" , "7" , "#7" ,
            "b9" , "9" , "#9" ,
            "b11", "11", "#11",
            "b13", "13", "#13",
        };
            
        for(const auto& note : addedNotes){
            if(intervals.contains(note)){
                chordSymbol += " add" + note;
                intervals.remove(note);
            }
        }

        // Print the chord symbol
        std::cout << "Chord Symbol: " << chordSymbol << std::endl;
    }

    // Get the chord symbol
    std::string getChordSymbol()
    {
        return mChordSymbol;
    }

    const Intervals& getIntervals() const
    {
        return mIntervals;
    }

    // Get Voicing from a list of degrees in the wanted order
    const std::vector<int> getSemitones() const
    {
        auto root = getRoot();
        std::vector<int> voicing;
        for(auto i : mIntervals){
            voicing.push_back(i.getSemitones()+root);
        }
        return std::move(voicing);
    }

    // Overload the index operator
    int operator[](int index)
    {   
        while(index < 0)                      index += this->size();
        while(index >= mIntervals.size()) index -= this->size();

        return mIntervals[index].getSemitones()+getRoot();
    }


    // Get Voicing from a list of degrees in the wanted order
    std::vector<int> getVoicing(std::vector<int> degrees, bool addBass=false, bool addRest=false)
    {
        auto intervals = this->mIntervals;
        std::vector<int> voicing;
        if(addBass) voicing.push_back(getBass());
        int last = -1;  
        std::set<int> usedDegrees;
        for(auto d : degrees){ 
            if(intervals.containsDegree(d)){
                usedDegrees.insert(d);
                auto i = intervals.getIntervalFromDegree(d);
                auto n = i.getSemitones()+getRoot();
                while(n < last) n += 12;
                voicing.push_back(n);
                last = n;
            }
        }

        // Remove the used degrees
        for(auto d : usedDegrees){
            intervals.removeDegree(d);
        }

        // Add the rest of the intervals
        if(addRest){
            for(auto i : intervals){
                auto n = i.getSemitones()+getRoot();
                while(n < last) n += 12;
                voicing.push_back(n);
                last = n;
            }
        }

        return std::move(voicing);
    }
    // Get Voicing from a list of degrees in the wanted order
    std::vector<int> getVoicing(bool addBass=false)
    {
        std::vector<int> voicing;
        if(addBass) voicing.push_back(getBass());
        auto root = getRoot();
        for(auto i : mIntervals){
            voicing.push_back(i.getSemitones()+root);
        }
        return std::move(voicing);
    }

    // Set the chord from a chord symbol - rootNote only used for roman numerals
    void setChord(const std::string& aChordSymbol, int aRoot = 0){
        auto chordSymbol = aChordSymbol;
        mChordSymbol = chordSymbol;

        std::string rootName = "";
        mIntervals.clear();

        // Test if the chors symbol is in roman numerals
        const bool isRoman = isRomanChordSymbol(chordSymbol);

        // Get the root note
        int rootNote = 0;

        // If the first character is a 'b' the the chord is flat and the root is lowered by 1 semitone. 
        // If the first character is a '#' then it is a flat or sharp chord and the root is raised by 1 semitone.
        // Handle this in a while loop to account for multiple flats or sharps
        if(isRoman){
            while(chordSymbol[0] == 'b' || chordSymbol[0] == '#') {
                if      (chordSymbol[0] == 'b') { rootNote -= 1; rootName += "b"; }
                else if (chordSymbol[0] == '#') { rootNote += 1; rootName += "#"; }
                chordSymbol.erase(0,1);
            }
        }

        // Replace start
        if     (replacePrefix(chordSymbol, "Cbm", "cb")){ }
        else if(replacePrefix(chordSymbol, "Cm" , "c" )){ }
        else if(replacePrefix(chordSymbol, "C#m", "c#")){ }
        else if(replacePrefix(chordSymbol, "Dbm", "db")){ }
        else if(replacePrefix(chordSymbol, "Dm" , "d" )){ }
        else if(replacePrefix(chordSymbol, "D#m", "d#")){ }
        else if(replacePrefix(chordSymbol, "Ebm", "eb")){ }
        else if(replacePrefix(chordSymbol, "Em" , "e" )){ }
        else if(replacePrefix(chordSymbol, "E#m", "e#")){ }
        else if(replacePrefix(chordSymbol, "Fbm", "fb")){ }
        else if(replacePrefix(chordSymbol, "Fm" , "f" )){ }
        else if(replacePrefix(chordSymbol, "F#m", "f#")){ }
        else if(replacePrefix(chordSymbol, "Gbm", "gb")){ }
        else if(replacePrefix(chordSymbol, "Gm" , "g" )){ }
        else if(replacePrefix(chordSymbol, "G#m", "g#")){ }
        else if(replacePrefix(chordSymbol, "Abm", "ab")){ }
        else if(replacePrefix(chordSymbol, "Am" , "a" )){ }
        else if(replacePrefix(chordSymbol, "A#m", "a#")){ }
        else if(replacePrefix(chordSymbol, "Bbm", "bb")){ }
        else if(replacePrefix(chordSymbol, "Bm" , "b" )){ }
        else if(replacePrefix(chordSymbol, "B#m", "b#")){ }

        // Test if the first letter of the roman numeral is a lower case letter. If it is then it is a minor chord and the rootNote is lowered by 3 semitones
        // Set chord type
        bool isMajor = isupper(chordSymbol[0]);
        Quality chordQuality = isMajor ? Quality::Major : Quality::Minor;

        // Convert to_lower 
        std::transform(chordSymbol.begin(), chordSymbol.end(), chordSymbol.begin(), ::tolower);

        // Move the rootNote according according to the chord symbol --- Roman Numerals
             if (removePrefix(chordSymbol, "iii" )){ rootNote += 4;  rootName += "III"; }
        else if (removePrefix(chordSymbol, "vii" )){ rootNote += 11; rootName += "VII"; }
        else if (removePrefix(chordSymbol, "ii"  )){ rootNote += 2;  rootName += "II" ; }
        else if (removePrefix(chordSymbol, "iv"  )){ rootNote += 5;  rootName += "IV" ; }
        else if (removePrefix(chordSymbol, "vi"  )){ rootNote += 9;  rootName += "VI" ; }
        else if (removePrefix(chordSymbol, "i"   )){ rootNote += 0;  rootName += "I"  ; }
        else if (removePrefix(chordSymbol, "v"   )){ rootNote += 7;  rootName += "V"  ; }
        // Move the rootNote according according to the chord symbol --- Specific Chords
        else if (removePrefix(chordSymbol, "c#"  )){ rootNote = 1;  rootName = "C#"; }
        else if (removePrefix(chordSymbol, "db"  )){ rootNote = 1;  rootName = "Db"; }
        else if (removePrefix(chordSymbol, "d#"  )){ rootNote = 3;  rootName = "D#"; }
        else if (removePrefix(chordSymbol, "eb"  )){ rootNote = 3;  rootName = "Eb"; }
        else if (removePrefix(chordSymbol, "e#"  )){ rootNote = 5;  rootName = "E#"; }
        else if (removePrefix(chordSymbol, "fb"  )){ rootNote = 5;  rootName = "Fb"; }
        else if (removePrefix(chordSymbol, "f#"  )){ rootNote = 6;  rootName = "F#"; }
        else if (removePrefix(chordSymbol, "gb"  )){ rootNote = 6;  rootName = "Gb"; }
        else if (removePrefix(chordSymbol, "g#"  )){ rootNote = 8;  rootName = "G#"; }
        else if (removePrefix(chordSymbol, "ab"  )){ rootNote = 8;  rootName = "Ab"; }
        else if (removePrefix(chordSymbol, "a#"  )){ rootNote = 10; rootName = "A#"; }
        else if (removePrefix(chordSymbol, "bb"  )){ rootNote = 10; rootName = "Bb"; }
        else if (removePrefix(chordSymbol, "cb"  )){ rootNote = 11; rootName = "Cb"; } 
        else if (removePrefix(chordSymbol, "b#"  )){ rootNote = 0;  rootName = "B#"; }
        else if (removePrefix(chordSymbol, "c"   )){ rootNote = 0;  rootName = "C" ; }
        else if (removePrefix(chordSymbol, "d"   )){ rootNote = 2;  rootName = "D" ; }
        else if (removePrefix(chordSymbol, "e"   )){ rootNote = 4;  rootName = "E" ; }
        else if (removePrefix(chordSymbol, "f"   )){ rootNote = 5;  rootName = "F" ; }
        else if (removePrefix(chordSymbol, "g"   )){ rootNote = 7;  rootName = "G" ; }
        else if (removePrefix(chordSymbol, "a"   )){ rootNote = 9;  rootName = "A" ; }
        else if (removePrefix(chordSymbol, "b"   )){ rootNote = 11; rootName = "B" ; }
    
        // Change notes if the chord is diminished or augmented
        if      (removePrefix(chordSymbol, "°"       )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "dim"     )){ chordQuality = Quality::Diminished;     }
        else if (removePrefix(chordSymbol, "ø"       )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "halfdim" )){ chordQuality = Quality::HalfDiminished; }
        else if (removePrefix(chordSymbol, "aug"     )){ chordQuality = Quality::Augmented;      }
        else if (removePrefix(chordSymbol, "+"       )){ chordQuality = Quality::Augmented;      }
        else if (removePrefix(chordSymbol, "sus2"    )){ chordQuality = Quality::Sus2;           }
        else if (removePrefix(chordSymbol, "sus4"    )){ chordQuality = Quality::Sus4;           }
        else if (removePrefix(chordSymbol, "5"       )){ chordQuality = Quality::PowerChord;     }

        // Remove stuff from the chord symbol
        const std::string chars = " ^()";
        // Remove the chars
        for (char c: chars) {
            chordSymbol.erase(std::remove(chordSymbol.begin(), chordSymbol.end(), c), chordSymbol.end());
        }

        // Initialize the chord tones vector based on the chord type
        switch (chordQuality)
        {
            case Quality::Major:          mIntervals     = {Interval(1), Interval(3)   , Interval(5)             }; break;
            case Quality::Minor:          mIntervals     = {Interval(1), Interval(3,-1), Interval(5)             }; break;
            case Quality::Diminished:     mIntervals     = {Interval(1), Interval(3,-1), Interval(5,-1)          }; break;
            case Quality::HalfDiminished: mIntervals     = {Interval(1), Interval(3,-1), Interval(5,-1), Interval(7,-1) }; break;
            case Quality::Augmented:      mIntervals     = {Interval(1), Interval(3)   , Interval(5, 1)          }; break;
            case Quality::Sus2:           mIntervals     = {Interval(1), Interval(2)   , Interval(5)             }; break;
            case Quality::Sus4:           mIntervals     = {Interval(1), Interval(4)   , Interval(5)             }; break;
            case Quality::PowerChord:     mIntervals     = {Interval(1),          Interval(5)             }; break;
        }

        // Add Extension
        if(removePrefix(chordSymbol, "6")){
            mIntervals.add(Interval(6));
        }
        else if(removePrefix(chordSymbol, "7")){
            mIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
        }
        else if(removePrefix(chordSymbol, "9")){ 
            mIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            mIntervals.add(Interval(9));
        }
        else if(removePrefix(chordSymbol, "11")){ 
            mIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            mIntervals.add(Interval(9),Interval(11));
        }
        else if(removePrefix(chordSymbol, "13")){ 
            mIntervals.add(chordQuality == Quality::Diminished ? Interval(6) : Interval(7,-1));
            mIntervals.add(Interval(9),Interval(11),Interval(13));
        }
        else if(removePrefix(chordSymbol, "maj7")){ 
            mIntervals.add(Interval(7));
        }
        else if(removePrefix(chordSymbol, "maj9")){ 
            mIntervals.add(Interval(7),Interval(9));
        }
        else if(removePrefix(chordSymbol, "maj11")){ 
            mIntervals.add(Interval(7),Interval(9),Interval(11));
        }
        else if(removePrefix(chordSymbol, "maj13")){ 
            mIntervals.add(Interval(7),Interval(9),Interval(11),Interval(13));
        }

        // Handle more complex chords
        bool found = true;
        while(found)
        {   
            found = false;
            // Flatten
            if(removePrefix(chordSymbol, "b3"    )){ mIntervals.setQuality( 3, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b5"    )){ mIntervals.setQuality( 5, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b7"    )){ mIntervals.setQuality( 7, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b9"    )){ mIntervals.setQuality( 9, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b11"   )){ mIntervals.setQuality(11, -1, true); found = true; }
            if(removePrefix(chordSymbol, "b13"   )){ mIntervals.setQuality(13, -1, true); found = true; }
            
            // Sharpen
            if(removePrefix(chordSymbol, "#3"    )){ mIntervals.setQuality(3 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#5"    )){ mIntervals.setQuality(5 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#7"    )){ mIntervals.setQuality(7 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#9"    )){ mIntervals.setQuality(9 ,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#11"   )){ mIntervals.setQuality(11,  1, true); found = true; }
            if(removePrefix(chordSymbol, "#13"   )){ mIntervals.setQuality(13,  1, true); found = true; }

            // Add notes if required
            if(removePrefix(chordSymbol, "add2"  )){ mIntervals.add(Interval( 2));        found = true; }
            if(removePrefix(chordSymbol, "add4"  )){ mIntervals.add(Interval( 4));        found = true; }
            if(removePrefix(chordSymbol, "add6"  )){ mIntervals.add(Interval( 6));        found = true; }
            if(removePrefix(chordSymbol, "add9"  )){ mIntervals.add(Interval( 9));        found = true; }
            if(removePrefix(chordSymbol, "add11" )){ mIntervals.add(Interval(11));        found = true; }
            if(removePrefix(chordSymbol, "add13" )){ mIntervals.add(Interval(13));        found = true; }

            // Remove notes if required
            if(removePrefix(chordSymbol, "no1"   )){ mIntervals.removeDegree( 1);         found = true; }
            if(removePrefix(chordSymbol, "no3"   )){ mIntervals.removeDegree( 3);         found = true; }
            if(removePrefix(chordSymbol, "no5"   )){ mIntervals.removeDegree( 5);         found = true; }
            if(removePrefix(chordSymbol, "no7"   )){ mIntervals.removeDegree( 7);         found = true; }
            if(removePrefix(chordSymbol, "no9"   )){ mIntervals.removeDegree( 9);         found = true; }
            if(removePrefix(chordSymbol, "no11"  )){ mIntervals.removeDegree(11);         found = true; }
            if(removePrefix(chordSymbol, "no13"  )){ mIntervals.removeDegree(13);         found = true; }
        }

        // Sort the chordIntervals
        mIntervals.sort();

        // Print the noteNames
        this->rootNote = rootNote+aRoot;
        this->bassNote = rootNote+aRoot;

        // Handle slash chords
        if(removePrefix(chordSymbol,"/")){
            // Get the note number of the slash note
            bassNote = getNoteNumber(chordSymbol,aRoot);
            chordSymbol.clear();
        }

        // Add the rest of the note names
        for(auto interval : mIntervals){
            if(interval.getDegree() != 1)
                noteNames.push_back(interval.getNoteName(rootNote, isRoman));
            else 
                noteNames.push_back(rootName);
        }
        
        if(chordSymbol.size() > 0){
            std::cerr << "setChord(): Warning: Error parsing chord symbol: " << aChordSymbol << " - Remaining: " << chordSymbol << std::endl;
        }
    }

    // Get the semitone of the Bass Note, same as root if not a slash chord
    int getBass(int min=0, int max=127) const
    {
        auto note = bassNote - 12 + mOctave*12;
        while(note < min) note += 12;
        while(note > max) note -= 12;

        return note;
    }

    int getRoot() const 
    {
        return rootNote+mOctave*12;
    }

    void printIntervals()
    {
        mIntervals.print();
    }

    void printSemitones(){
        // Print the chord intervals
        for(auto interval : mIntervals){
            std::cout << interval.getSemitones() << " ";
        }
        std::cout << std::endl;        
    }

    void printNoteNames()
    {
        // Convert the intervals to chord tones
        std::vector<std::string> noteNames;
        for(auto interval : mIntervals){
            std::cout << interval.getNoteName(rootNote) << " ";
        }
        std::cout << std::endl;
    }

    void print()
    {
        std::cout << getChordSymbol() << "\t";
        const auto& chordTones = getSemitones();

        for (int i = 0; i < chordTones.size(); i++) {
            std::cout << chordTones[i] << "\t";
        }
        std::cout << "BassNote: " << bassNote << "\t";
        std::cout << std::endl;
    }

    // Size function
    size_t size() const
    {
        return mIntervals.size();
    }

    // Empty function
    bool empty() const
    {
        return mIntervals.empty();
    }

private:
    // Chord Symbol
    std::string      mChordSymbol;
    // Chord Intervals
    Intervals        mIntervals;
    // Note Names
    std::vector<std::string> noteNames;

    // Root Note
    int rootNote = 0;
    // Bass Note
    int bassNote = 0;
    // Octave
    int mOctave = 3;


};



*/





} // namespace cmtk
