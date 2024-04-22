#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Interval.h"

namespace cmtk {


class Note;
class Notes;
using NoteVector = std::vector<Note>;

// ----------------------------------------------------------------------- //
// ----------------------- Note Class ------------------------------------ //
// ----------------------------------------------------------------------- //
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
    void set(int note);

    int getPitch() const;

    int getPitchWrap() const;

    int getOctave() const;

    Note& setOctave(int octave);

    Note& shiftOctave(int octaves);

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

    // Equality operator
    bool operator==(const Note& other) const;

    bool operator!=(const Note& other) const;

    bool operator<(const Note& other) const;

    // Assignment operator
    Note& operator=(const int& note);

    // Assignment operator
    Note& operator=(const std::string& note);
    
    // Cast to int
    operator int() const;

    // Cast to string
    operator std::string() const;

    // Transpose
    Note& transpose(int n);

    // Transpose Interval
    Note& transpose(const Interval& interval);

    Note operator+(const int& semitones) const;

    Note operator-(const int& semitones) const;

    Note operator+(const Interval& interval) const;

    Notes operator+(const Intervals& intervals) const;

    // Increment operator
    Note& operator++()
    {
        mNote++;
        return *this;
    }

    // Decrement operator
    Note& operator--()
    {
        mNote--;
        return *this;
    }

    // - operator
    int operator-(const Note& other) const
    {
        return mNote - other.mNote;
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Note& note)
    {
        os << note.toString();
        return os;
    }

    bool isKey(const std::string& key) const
    {
        return toString(false) == key;
    }

    Note& flatten()
    {
        if(mNoteString.back() == '#')
        {
            mNoteString.pop_back();
        }
        else 
        {
            mNoteString.push_back('b');
        }
        mNote-- ;
        mSharp--;
        return *this;
    }

    Note& sharpen()
    {
        if(mNoteString.back() == 'b')
        {
            mNoteString.pop_back();
        }
        else 
        {
            mNoteString.push_back('#');
        }
        mNote++ ;
        mSharp++;
        return *this;
    }

    std::vector<Note> getMajorNotes()
    {
        std::vector<Note> notes;
        auto sv = MajorNoteMap[toString(false)];
        for(auto& s : sv) notes.push_back(s);

        return std::move(notes);
    }

    Note getNoteAt(const Interval& interval) const
    {
        auto octave = getOctave();
        const auto& key = toString(false,true);
        auto deg = interval.getDegree();
        if(deg > 7){
            octave++;
            deg -= 7;
        }

        const auto& s = MajorNoteMapAt(key, deg-1);

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

    Interval getIntervalTo(const Note& otherNote) const
    {
        int semitones = otherNote.getPitch() - getPitch();
        return Interval::NewFromSemi(semitones);
    }

    std::vector<Note> getNoteAt(const Intervals& interval) const
    {
        std::vector<Note> notes;
        for(auto& i : interval) notes.push_back(getNoteAt(i));
        return std::move(notes);
    }

    bool isOk() const
    {
        return mNote >= 0 && mNote <= 127;
    }

    operator bool() const
    {
        return isOk();
    }

private:
    int mNote = -1;
    std::string mNoteString = "";
    int mSharp = 0;

    // Display sharp or flat
    bool sharp() const
    {
        if(mSharp == 0) return mPreferSharp;
        return mSharp  > 0; 
    }

};



class Notes : public NoteVector
{
public:
    Notes() = default;

    Notes(const NoteVector& notes)
    {
        set(notes);
    }

    Notes(const std::string& notes)
    {
        set(notes);
    }

    Notes(const std::vector<int>& notes)
    {
        set(notes);
    }

    Notes(const std::vector<std::string>& notes)
    {
        set(notes);
    }

    Notes(const Intervals& intervals, const Note& root = C1)
    {
        set(intervals,root);
    }

    void set(const NoteVector& notes)
    {
        clear();
        for(auto& note : notes) push_back(note);
    }

    void set(const std::vector<int>& notes)
    {
        clear();
        for(auto& note : notes) push_back(note);
    }

    void set(const std::vector<std::string>& notes)
    {
        clear();
        for(auto& note : notes) push_back(note);
    }

    void set(const std::string& notes)
    {
        clear();
        std::string s = notes;
        while(!s.empty())
        {
            auto pos = s.find_first_of(" ,|");
            if(pos == std::string::npos) pos = s.size();
            std::string note = s.substr(0,pos);
            if(!note.empty()) push_back(note);
            s.erase(0,pos+1);
        }
    }

    void set(const Intervals& intervals, const Note& root = C1)
    {
        clear();
        for(auto& interval : intervals)
        {
            Note note = root + interval.getSemi();
            push_back(note);
        }
    }

    void add(const Notes& aNotes)
    {
        for(auto& note : aNotes) add(note);
    }

    void add(const Note& note)
    {
        push_back(note);
    }

    void add(const std::string& note)
    {
        push_back(note);
    }

    void add(const int& note)
    {
        push_back(note);
    }

    Notes& removeDuplicates()
    {
        std::sort(begin(),end());
        erase(std::unique(begin(),end()),end());
        return *this;
    }

    Notes& removeOctave()
    {
        auto it = begin();
        while(it != end())
        {
            it->setOctave(0);
            it++;
        }
        return *this;
    }

    // Get a string with the pitch vector
    std::string getPitchString() const
    {
        std::string res;
        for(const auto& note : *this) res += std::to_string(note.getPitch()) + " ";
        if(!res.empty()) res.pop_back();
        return std::move(res);
    }

    // To string
    std::string toString(bool octave=false, bool simplify=false) const
    {
        std::string res;
        auto it = begin();
        while(it != end())
        {
            res += it->toString(octave,simplify);
            if(++it != end()) res += " ";
        }
        return std::move(res);
    }

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Notes& notes)
    {        
        auto it = notes.begin();
        while(it != notes.end())
        {
            os << it->toString(false,false);
            if(++it != notes.end()) os << " ";
        }
        return os;
    }

    void print(bool octave=false, bool simplify=false) const
    {
        std::cout << "Notes(";
        auto it = begin();
        while(it != end())
        {
            std::cout << it->toString(octave,simplify);
            if(++it != end()) std::cout << " ";
        }
        std::cout << ")" << std::endl;
    }

    void transpose(int semitones)
    {
        for(auto& note : *this) note.transpose(semitones);
    }

    void sort()
    {
        std::sort(begin(),end());
    }

    // Assignment operator
    Notes& operator=(const std::string& notes)
    {
        set(notes);
        return *this;
    }

    // Assignment operator
    Notes& operator=(const Intervals& intervals)
    {
        set(intervals);
        return *this;
    }

    // Assignment operator
    Notes& operator=(const NoteVector& notes)
    {
        set(notes);
        return *this;
    }

    // Assignment operator
    Notes& operator=(const std::vector<int>& notes)
    {
        set(notes);
        return *this;
    }

    // at operator
    Note& operator[](int i)
    {
        return at(i);
    }

    // Semi at operator
    int semiAt(int i) const
    {
        return at(i).getPitch();
    }

    // Get Vector of semitones
    std::vector<int> getMidiPitches() const
    {
        std::vector<int> semis;
        for(auto& note : *this) semis.push_back(note.getPitch());
        return std::move(semis);
    }

    // Get Vector of N
    static Notes AllKeys()
    {
        Notes notes;
        for(auto& s : KeyNames) notes.push_back(Note(s));
        return std::move(notes);
    }

    // Contains a specific note
    bool contains(const Note& note) const
    {
        return std::find(begin(),end(),note) != end();
    }

    // Contains a specific note ignoring octave
    bool contains(const Note& note, bool ignoreOctave) const
    {
        auto it = std::find_if(begin(),end(),[&note,ignoreOctave](const Note& n){
            return ignoreOctave ? n.getPitchWrap() == note.getPitchWrap() : n == note;
        });

        return it != end();
    }

    // Contains all the notes in another vector
    bool contains(const Notes& notes) const
    {
        auto it = notes.begin();
        while(it != notes.end())
        {
            if(!contains(*it)) return false;
            it++;
        }
        return true;
    }

    // Contains all the notes in another vector ignoring octave
    bool contains(const Notes& notes, bool ignoreOctave) const
    {
        auto it = notes.begin();
        while(it != notes.end())
        {
            if(!contains(*it,ignoreOctave)) return false;
            it++;
        }
        return true;
    }

    bool ok() const
    {
        for(auto& note : *this) if(!note.isOk()) return false;
        return true;
    }

    // Cast to bool
    operator bool() const
    {
        return ok();
    }

    
};




} // namespace cmtk
