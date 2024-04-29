#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Interval.h"
namespace cmtk {

// Forward declarations
class Notes;

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Note Class ---------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
class Note : public CMTK
{
public:
    // Constructor
    Note() = default;

    // Constructor to create a note from a string
    Note(const std::string& note);

    // Constructor to create a note from a midinote
    Note(int note);

    // Function to set the note from a midinote
    Note& set(int note);

    int getPitch() const;

    int getPitchWrap() const;

    int getOctave() const;

    Note& setOctave(int octave);

    Note& shiftOctave(int octaves);

    float getFreq() const;

    // Function to set the note from a string
    Note& set(std::string noteSymbol);

    // Set from Interval with respedt to its RootNote
    Note& set(const Note& aNote, const Interval& interval);

    // Set from Note
    Note& set(const Note& aNote);

    // Set from a Roman Chord Symbol with respect to its RootNote
    Note& setRoman(std::string aRomanChordString, const Note& aRootNote);

    // Represent the note as a string - allow to in or exclude the octave, and simplify the note
    std::string toString(bool includeOctave=true, bool simplify=false) const;

    // Get the note as a string
    Note& print(bool includeOctave=true, bool simplify=false) const;

    // Clear the note
    Note& clear();

    // Comparison operators
    bool operator==(const Note& other) const;
    bool operator!=(const Note& other) const;
    bool operator<(const Note& other) const;
    bool operator>(const Note& other) const;

    // Assignment operator
    Note& operator=(const int& note);
    Note& operator=(const std::string& note);
    
    // Cast operator
    operator int() const;
    operator std::string() const;
    operator bool() const; // Cast to bool - same as isOk()

    // Transpose
    Note& transpose(int n);
    Note& transpose(const Interval& interval);

    // Math operators
    Note operator+(const int& semitones) const;
    Note operator-(const int& semitones) const;
    Note operator+(const Interval& interval) const;
    Notes operator+(const Intervals& intervals) const;

    // Increment / Decrement operators
    Note& operator++();
    Note& operator--();

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Note& note);

    // Check if note is a specific key, e.g. C or F#, octave is ignored
    bool isKey(const std::string& key) const;

    // Flatten or sharpen the note
    Note& flatten();
    Note& sharpen();

    // Get the notes of the major scale with this as root
    Notes getMajorNotes();

    // Get a note that is a specific interval from this note
    Note getNoteAt(const Interval& interval) const;

    // Get a vector notes from a vector of intervals
    Notes getNoteAt(const Intervals& interval) const;

    // Get the interval between this note and another note
    Interval getIntervalTo(const Note& otherNote) const;

    // Check that the note is ok
    bool isOk() const;

    // Get the note as JSON
    json::JSON getJSON() const;


private:
    int mNote = -1;
    std::string mNoteString = "";
    int mSharp = 0;

    // Display sharp or flat
    bool sharp() const;

};


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Notes Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
using NoteVector = std::vector<Note>;
class Notes : public NoteVector
{
public:
    Notes() = default;

    // Constructor
    Notes(const NoteVector& notes);
    Notes(const std::string& notes);
    Notes(const std::vector<int>& notes);
    Notes(const std::vector<std::string>& notes);
    Notes(const Intervals& intervals, const Note& root = C1);

    // Set Notes
    void set(const NoteVector& notes);
    void set(const std::vector<int>& notes);
    void set(const std::vector<std::string>& notes);
    void set(const std::string& notes);
    void set(const Intervals& intervals, const Note& root = C1);

    // Add notes
    void add(const Notes& aNotes);
    void add(const Note& note);
    void add(const std::string& note);
    void add(const int& note);

    Notes& removeDuplicates();
    Notes& removeOctave();

    // Get a string with the pitch vector
    std::string getPitchString() const;

    // Get a string with the freq vector
    std::string getFreqString() const;

    // To string
    std::string toString(bool octave=false, bool simplify=false) const;

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Notes& notes);

    Notes& print(bool octave=false, bool simplify=false);

    Notes& printFreq();

    Notes& transpose(int semitones);

    Notes& sort();

    // Assignment operator
    Notes& operator=(const std::string& notes);

    // Assignment operator
    Notes& operator=(const Intervals& intervals);

    // Assignment operator
    Notes& operator=(const NoteVector& notes);

    // Assignment operator
    Notes& operator=(const std::vector<int>& notes);

    // at operator
    Note& operator[](int i);

    // Semi at operator
    int semiAt(int i) const;

    // Get Vector of semitones
    std::vector<int> getPitch() const;

    // Get Vector of frequencies
    std::vector<float> getFreq() const;

    // Get Vector of N
    static Notes AllKeys();

    // Contains a specific note
    bool contains(const Note& note) const;

    // Contains a specific note ignoring octave
    bool contains(const Note& note, bool ignoreOctave) const;

    // Contains all the notes in another vector
    bool contains(const Notes& notes) const;

    // Contains all the notes in another vector ignoring octave
    bool contains(const Notes& notes, bool ignoreOctave) const;

    // Return true if all the notes are ok
    bool ok() const;

    // Cast to bool
    operator bool() const;

    // Get the notes as JSON
    json::JSON getJSON() const;
    
};

// This results in a seqentation fault if placed in the cpp file? TODO: Find out why, fix and move to cpp file...
inline Note Note::getNoteAt(const Interval& interval) const
{
    auto octave = getOctave();
    const auto& key = toString(false,true);
    auto deg = interval.getDegree();
    if(deg > 7){
        octave++;
        deg -= 7;
    }

    const auto s = MajorNoteMapAt(key, deg-1);

    Note note(s);
    note.setOctave(octave);
    auto q = interval.getQuality();
    while(q > 0)
    {
        note.sharpen();
        q--;
    }
    while(q < 0)
    {
        note.flatten();
        q++;
    }

    return std::move(note);
}




} // namespace cmtk
