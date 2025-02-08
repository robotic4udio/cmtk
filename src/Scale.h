#pragma once
#include "CMTK.h"
#include "Interval.h"
#include "Note.h"
#include "Chord.h"

namespace cmtk {


// Forward declaration
class Chord;
class ChordProg;

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Scale Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
class Scale : public CMTK
{
public:
    Scale() = default;

    // Constructor to set the scale from a given name and root note
    Scale(std::string aName, Note aRootNote);

    // Constructor to set the scale from a given name and root note
    Scale(std::string aName, std::string aRootNote);

    // Constructor to set the scale from a combined root and name, e.g. "C-Major", "Eb-Dorian"
    Scale(const std::string& aName);

    // Set the Root Note of the Scale from a Note Object
    Scale& setRoot(const Note& aRootNote);

    // Set the Root Note of the Scale from a string
    Scale& setRoot(const std::string& aRootNote);

    // Set the Root Note of the Scale from a semi-tone value given as an integer
    Scale& setRoot(int aRootNote);

    // Function to get the Root Note of the Scale
    const Note& getRoot() const;

    // Function to Clear the Scale
    Scale& clear();

    // Function to set the scale from a combined root and name, e.g. "C-Major", "Eb-Dorian"
    Scale& set(const std::string& s);

    // Function to set the scale from a string, e.g. "Major", "Dorian"
    Scale& setScale(std::string aScaleName);

    // Overload the [] operator to get the interval at a given index (degree-1)
    Interval operator[](int index);

    // Function to get the semi-tone of the scale at a given index
    int semiToneAt(int index);

    // Function to get a scale that matches the given intervals
    static Scale GetScale(const Intervals& intervals);

    // Function to get the semi-tones of the scale at given indexes
    std::vector<int> semitoneAt(const std::vector<int> &indexes);

    // Function to get the interval of the scale at a given index
    const Interval intervalAt(int index) const;

    // Function to get the intervals of the scale at given indexes
    const Intervals intervalAt(const std::vector<int> &indexes) const ;

    // Function to get the chord symbol of the scale at a given index
    std::string getChordSymbol(int index, int size = 3, bool roman=false, bool simplify=false) const;

    // Get chord at index
    Chord getChord(int index, int size=3);

    // Get all the chord symbols
    std::vector<std::string> getChordSymbols(int size = 3, bool roman=false);

    // Get ChordProg from a vector of indexes
    ChordProg getChordProg(const std::vector<int>& indexes, int size = 3);

    // Get ChordProg from a vector of indexes and sizes
    ChordProg getChordProg(const std::vector<int>& indexes, const std::vector<int>& aSize);

    // Get ChordProg from a string of indexes and a size
    ChordProg getChordProg(const std::string& s, int size = 3);

    // Get ChordProg from a combined string of Root, Scale and Degrees, e.g. "C-Major-145" -> ChordProg("C|F|G")
    static ChordProg GetChordProg(const std::string& s, int size = 3);

    // Get ChordProg from a combined string of Root, Scale and Degrees, e.g. "C-Major-145" -> ChordProg("C|F|G")
    static std::pair<ChordProg, Scale> GetChordProgAndScale(const std::string& s, int size = 3);

    // Print the chord symbols
    void printChordSymbols(int size = 3);

    // Function to calculate the brightness of the scale
    int getBrightness();

    // Size of the scale
    int size();

    // Stream operator to print the scale
    friend std::ostream &operator<<(std::ostream &os, const Scale &scale);

    // Get Intervals of the scale
    const Intervals& getIntervals() const;

    // Get Intervals of the scale
    Intervals getIntervals();

    // Get Notes of the scale
    const Notes& getNotes() const;

    // Print the scale
    void print(int size = 3, bool simplify = false) const;

    // Print the scale as whole and half steps
    const std::string getWholeHalfPattern() const;

    // Function to test if a chord is diatonic to the scale
    bool isDiatonic(const Chord &chord) const;

    // Functions to test if a chord progression is diatonic to the scale    
    bool isDiatonic(const ChordProg& chordProgression) const;

    // Function to calculate the diatonicity of a set of notes to the scale
    float diatonicity(const Notes& aChordNotes);

    // Function to calculate the diatonicity of a chord to the scale
    float diatonicity(const Chord &chord);

    // Function to calculate the diatonicity of a chordProgression to the scale
    float diatonicity(const ChordProg& chordProgression);
    
    // Return a vector of all the supported scales, with the given root note
    static std::vector<Scale> GetAllScales(const Note& aRoot = Note("C"));

    // Return a vector of all the supported scales, in all keys... A CPU intensive operation
    static std::vector<Scale> GetAllScalesAllKeys();

    // Get the names of the modes of a given scale
    static std::vector<std::string> GetModeNames(std::string s = "Major");

    // Get the Modes of a scale
    static std::vector<Scale> GetModes(std::string s = "Major", const Note& root = Note("C"));

    // Print the names of the modes
    static void PrintModeNames(std::string s = "", int size = 3);

    // Print the modes
    static void PrintModes(std::string s = "",  Note root = Note("C"), int size = 3);

    // Print all the scales
    static void PrintAllScales(int size = 3);

    // Return a vector with all the scales sorted by brightness
    static std::vector<Scale> GetScalesByBrightness();

    // Return a vector with all the scales sorted by Diatonicity to a given chord progression. Only the scales with the given root note are returned
    static std::vector<Scale> GetScalesByDiatonicity(const ChordProg& chordProgression, const Note& aRoot);

    // Return a vector with all the scales sorted by Diatonicity to a given chord progression. All Root notes are considered
    static std::vector<Scale> GetScalesByDiatonicity(const ChordProg& chordProgression);

    // Get the name of the scale
    std::string getName(bool withRoot=true) const;

    // Print the scales sorted by Diatonicity to a ChordProg
    static void PrintScalesByDiatonicity(const ChordProg& chordProgression, int limit = 7);

    // Get a vector of all the diatonic scales to a given chord
    static std::vector<Scale> GetDiatonicScales(const Chord& chord, const Note& aTonic);

    // Get a vector of all the diatonic scales to a given chord progression
    static std::vector<Scale> GetDiatonicScales(const ChordProg& chordProgression, const Note& aTonic);
    
    // Print all the diatonic scales to a given chord
    static void PrintDiatonicScales(const Chord& chord, const Note& aTonic, int size = 3);

    // Print all the diatonic scales to a given chord
    static void PrintDiatonicScales(const Chord& chord, int size = 3);

    // Print all the diatonic scales to a given chord progression
    static void PrintDiatonicScales(const ChordProg& chordProgression, const Note& aTonic, int size = 3);

    // Print all the diatonic scales to a given chord progression
    static void PrintDiatonicScales(const ChordProg& chordProgression, int size = 3);

private:
    // The scale name
    std::string mName;
    // The scale intervals
    Intervals mIntervals;
    // The scale root note
    Note mRootNote = Note("C1");
    // The Notes of the scale
    Notes mNotes;
    // The styles of music the mode is usually used for
    std::string mStyle = "";

    // Function to update the notes of the scale
    void updateNotes();

    // Function to test is a vector contains the values given in the arguments
    const bool inVec(const std::vector<int> &vec, const std::vector<int> &values) const 
    {
        return std::all_of(values.begin(), values.end(), [&vec](int value)
                            { return std::find(vec.begin(), vec.end(), value) != vec.end(); });
    }

    // Function to replace the last n characters of a string
    const void replaceBack(std::string &str, const std::string &toReplace, int size = 1) const 
    {
        str.replace(str.end() - size, str.end(), toReplace);
    }

    // Test is a string ens with another string
    const bool endsWith(const std::string &str, const std::string &ending) const
    {
        if (str.length() >= ending.length())
        {
            return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
        }
        return false;
    }

    // Function to convert semitones to string
    const std::string toString(const std::vector<int>& vec) const
    {
        std::string result = "";
        for (auto x : vec)
        {
            result += std::to_string(x) + " ";
        }
        return std::move(result);
    }
};

} // namespace cmtk
