#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Interval.h"
#include "Note.h"
#include "Scale.h"

namespace cmtk {

// Forward declaration
class Scale;
class ChordVoicing;


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordType Class ----------------------------------------- //
// -------------------------------------------------------------------------------------------- //
class ChordType : public CMTK {
public:
    // Constructor
    ChordType() = default;
    ChordType(const std::string& chordSymbol);

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
        Quartal,
        Quintal,
        NA
    };

    // Set the ChordType from a set string representing the ChordType
    ChordType& set(const std::string& aChordType);

    // Get Normalized Semi from ChordType and Inversion
    std::vector<int> getSemiSignature(const std::string& chordType, int inv);

    // Set from semi
    ChordType& setSemi(const std::vector<int>& aX);

    // Is the Chord a Minor Chord
    bool isKindOfMinor() const;

    // Get the chord symbol
    std::string getChordType();

    // Get the intervals
    const Intervals& getIntervals() const;

    // ChordType to string
    std::string toString() const;

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const ChordType& ct);

    // Print the chordType
    ChordType& print();

    // Size of ChordType
    size_t size() const;


private:
    std::string mChordType = "";
    Intervals mIntervals = Intervals({Interval(1), Interval(3), Interval(5)});
};


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Chord Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //

// The Chord Class is a class that represents a chord. It is the composition of a Note and a ChordType
class Chord : public CMTK {
public:
    // Constructor
    Chord() = default;

    // Constructor from RootNote, ChordType and BassNote
    Chord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote);

    // Constructor from RootNote and ChordType - BassNote is set to the RootNote
    Chord(const Note& aRootNote, const ChordType& chordType);

    // Constructor from note and chordType expressed as strings
    Chord(const std::string& note, const std::string& chordType, const std::string& aBassNote = "");

    // Constructor from a combined chord symbol
    Chord(const std::string& chordSymbol);

    // Set the chord from a Note and a ChordType
    Chord& setChord(const Note& aRootNote, const ChordType& chordType, const Note& aBassNote);

    // Set the chord from a Note and a ChordType
    Chord& setChord(const Note& aRootNote, const ChordType& chordType);

    // Set from a note and a chordType expressed as strings
    Chord& setChord(const std::string& aRootNote, const std::string& aChordType, const std::string& aBassNote = "");

    // Set the Chord from a combined chord symbol, e.g. "Cm7/E"
    Chord& setChord(const std::string& chordSymbol);

    // Create a new Chord from a Roman Chord String and a Tonic
    static Chord NewRoman(const std::string& chordSymbol, const Note& aTonic);

    // Create a new Chord from a Roman Chord String and a Tonic
    static Chord NewRoman(const std::string& chordSymbol, const std::string& aTonic);

    // Set the Chord from a Roman Chord String and a Tonic
    Chord& setRoman(const std::string& romanChordSymbol, const Note& aTonic);

    // Set the Chord from a Roman Chord String and a Tonic
    Chord& setRoman(const std::string& aRomanChordSymbol, const std::string& aTonic);

    // Set the Chord from a Roman Chord String and a Tonic given as an integer semitone
    Chord& setRoman(const std::string& aRomanChordSymbol, int aTonic);

    // Set the Chord from a Roman Chord String
    Chord& setRoman(const std::string& aRomanChordSymbol);

    // Get Roman Chord Symbol from Chord and Tonic
    std::string getRoman(const Note& aTonic) const;

    // Print the Roman Chord
    Chord& printRoman(const Note& aTonic);

    // Set Chord Type
    Chord& setType(const ChordType& chordType);

    // Set Chord Type
    Chord& setType(const std::string& chordType);
    
    // Get the chord type
    const ChordType& getType() const;

    // Set the RootNote
    Chord& setRoot(const Note& note, bool keepOctave=false);

    // Set the RootNote
    Chord& setRoot(const std::string& note);

    Chord& setRoot(int note);

    // Get the note
    const Note& getRoot() const;

    // Set the BassNote
    Chord& setBass(const Note& note, bool keepOctave=false);

    // Set the BassNote
    Chord& setBass(const std::string& note);

    // Set Bass from Semitone
    Chord& setBass(int note);

    // Set Bass from Interval with respect to the root note
    Chord& setBass(const Interval& interval, bool keepOctave=false);

    // Set Bass from Root
    Chord& rootBass();

    bool isSlashChord() const;

    // Force bass into range
    Chord& forceBassInRange(int min=0, int max=127);

    // Get the Bass note
    const Note& getBass() const;

    // Set Octave
    Chord& setOctave(int octave, bool keepBass=false);

    // Get Octave
    int getOctave() const;

    // Set Bass Octave
    Chord& setBassOctave(int octave);

    // Get Bass Octave
    int getBassOctave() const;

    // Get Intervals
    const Intervals& getIntervals() const;

    // Get the Notes of the chord
    Notes getNotes() const;

    // Transpose the Chord
    Chord& transpose(int semitones);
    Chord& transpose(const Interval& interval);

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Chord& Chord);

    // Get Chord as string
    std::string toString() const;

    // Print the chord
    Chord& print(bool simplify=true);

    // Size of Chord
    size_t size() const;

private:
    ChordType mChordType;  // Object representing the chord type, i.e. the basic structure of the chord
    Note mRootNote;        // The root note of the chord
    Note mBassNote;        // The bass note of the chord, this is only different from the root note if the chord is a slash chord
};


class ChordVoicing {
public:
    ChordVoicing(Chord& aChord, const std::string aVoicing = ""):mChord(aChord)
    {
        setVoicing(aVoicing);
    }

    ChordVoicing& setVoicing(const std::string& aVoicing)
    {
        mVoicing = aVoicing;
        return *this;
    }

    // Get Notes
    Notes getNotes()
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

    ChordVoicing& setChord(const Chord& aChord)
    {
        mChord = aChord;
        return *this;
    }

    ChordVoicing& print(bool simplify=true)
    {
        std::cout << mChord.toString() << " -> Voicing(" << mVoicing << ") -> (";
        auto notes = getNotes();
        std::cout <<  notes.toString(false,simplify) << ")" 
                << " -> (" << getNotes().getPitchString() << ")";
        std::cout << std::endl;
        return *this;
    }



private:
    // Input
    Chord& mChord;

    // Voicing
    std::string mVoicing;

    // Remove all occurences of a character from a string and return the number of occurences
    int removeCount(std::string& s, char c)
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

};


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- ChordProg Class ----------------------------------------- //
// -------------------------------------------------------------------------------------------- //
using ChordVector = std::vector<Chord>;
class ChordProg : public ChordVector {
public:
    ChordProg() = default;
    // Constructor to create a chord progression from a vector of chords
    ChordProg(const ChordVector& chords, const Note& aTonic=Note());

    // Constructor to create a chord progression from a vector of chord symbols
    ChordProg(const std::vector<std::string>& chordSymbols, const Note& aTonic=Note());

    // Constructor to create a chord progression from a string of chord symbols
    ChordProg(const std::string& chordSymbols, const Note& aTonic=Note());

    // Constructor to create a chord progression from a string of chord symbols
    ChordProg(const std::string& chordSymbols, const std::string& aTonic);

    // Function to set the chord progression from a vector of chords
    ChordProg& set(const ChordVector& chords);

    // Function to set the chord progression from a vector of chord symbols
    ChordProg& set(const std::vector<std::string>& chordSymbols);

    // Function to set the chord progression from a vector of chord symbols
    ChordProg& setRoman(const std::vector<std::string>& chordSymbols, const Note& aTonic);

    // Function to set the chord progression from string of chord symbols
    ChordProg& set(const std::string& chordSymbols);

    // Function to set the chord progression from string of chord symbols
    ChordProg& setRoman(const std::string& chordSymbols, const Note& aTonic = Note());

    // Function to add a chord to the progression
    ChordProg& addChord(const Chord& chord);

    // Function to add a chord to the progression
    ChordProg& addChord(const std::string& chordSymbol);

    // Function to add a Roman chord to the progression
    ChordProg& addRoman(const std::string& romanChordSymbol, const Note& tonic);

    // Function to clear the progression
    ChordProg& clear();

    ChordProg& transpose(int n);

    // Print the chord progression
    ChordProg& printChords();

    // Print the chord progression
    ChordProg& print(bool simplify=false);

    // Get Roman Chord Symbols
    std::string getRoman(const Note& aTonic) const;

    // Print the chord progression as Roman Chords
    ChordProg& printRoman(const Note& aTonic);

    // Print the chord progression as Roman Chords
    ChordProg& printRoman();

    // Set the Tonic
    ChordProg& setTonic(const Note& aTonic);
    ChordProg& setTonic(const std::string& aTonic);

    // Get the Tonic
    const Note& getTonic() const;

    // Change Tonic
    ChordProg& changeKey(const Note& aTonic);
    ChordProg& changeKey(const std::string& aTonic);

    // Get Notes used in the progression
    Notes getNotes() const;

    // A Map of Chord Progressions
    static std::map<std::string, ChordProg> Map;

    // Get a Chord Progression from the Map
    static ChordProg Get(const std::string& aChordProg);

private:
    // Function to convert a string of chord symbols to a vector of chord symbols
    std::vector<std::string> chordStringToVector(std::string chordSymbols);

    // Tonic of the progression
    Note mTonic = Note(); // The Note Object will init in a not ok state, so it can be checked if it is set by mNote.ok() or cast to bool
};










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



