#pragma once
// Classes to handle the creation of the music

#include "CMTK.h"
#include "Interval.h"

#include <string>

namespace cmtk {


class Notes;

// ----------------------------------------------------------------------- //
// ----------------------- Note Class ------------------------------------ //
// ----------------------------------------------------------------------- //
class Note : public CMTK
{
public:
    // Constructor to create a note from a string
    Note(const std::string& note)
    {
        set(note);
    }

    // Constructor to create a note from a midinote
    Note(int note)
    {
        set(note);
    }

    // Function to set the note from a midinote
    void set(int note)
    {
        clear();
        mNote = note;
    }

    int getMidiPitch() const
    {
        return mNote;
    }

    int getOctave() const
    {
        return (mNote - C0) / 12;
    }

    Note& setOctave(int octave)
    {
        mNote = mNote % 12 + C0 + octave * 12;
        return *this;
    }

    // Function to set the note from a string
    void set(std::string noteSymbol)
    {
        clear();

        // Convert the note to uppercase
        std::transform(noteSymbol.begin(), noteSymbol.end(), noteSymbol.begin(), ::toupper);

        // Remove all spaces from the note symbol
        noteSymbol.erase(std::remove(noteSymbol.begin(), noteSymbol.end(), ' '), noteSymbol.end());

        // Use the note to set the note value
        if     (removePrefix(noteSymbol,"C")){ mNoteString = "C"; mNote =  0; } 
        else if(removePrefix(noteSymbol,"D")){ mNoteString = "D"; mNote =  2; } 
        else if(removePrefix(noteSymbol,"E")){ mNoteString = "E"; mNote =  4; } 
        else if(removePrefix(noteSymbol,"F")){ mNoteString = "F"; mNote =  5; } 
        else if(removePrefix(noteSymbol,"G")){ mNoteString = "G"; mNote =  7; } 
        else if(removePrefix(noteSymbol,"A")){ mNoteString = "A"; mNote =  9; } 
        else if(removePrefix(noteSymbol,"B")){ mNoteString = "B"; mNote = 11; } 
        else return;

        // Take care of flats and sharps
        while(noteSymbol.front() == 'B' || noteSymbol.front() == '#'){
            if      (noteSymbol[0] == 'B') { mNoteString += 'b'; mNote -= 1; mSharp--; }
            else if (noteSymbol[0] == '#') { mNoteString += '#'; mNote += 1; mSharp++; }
            noteSymbol.erase(0,1);
        }

        // Add the octave
        mNote += noteSymbol.empty() ? C0 : C0 +std::stoi(noteSymbol) * 12;
    }

    std::string toString(bool includeOctave=true, bool simplify=false) const
    {        
        int octave = -OCTAVES_BELOW_ZERO;
        int note = mNote;
        while(note >= 12)
        {
            note -= 12;
            octave++;
        }            

        std::string res = mNoteString;
        if(res.empty())
        {
            switch(note){
                case 0:  res = "C";                   break;
                case 1:  res = sharp() ? "C#" : "Db"; break;
                case 2:  res = "D";                   break;
                case 3:  res = sharp() ? "D#" : "Eb"; break;
                case 4:  res = "E";                   break;
                case 5:  res = "F";                   break;
                case 6:  res = sharp() ? "F#" : "Gb"; break;
                case 7:  res = "G";                   break;
                case 8:  res = sharp() ? "G#" : "Ab"; break;
                case 9:  res = "A";                   break;
                case 10: res = sharp() ? "A#" : "Bb"; break;
                case 11: res = "B";                   break;
            }
        }

        if(simplify) simplifyNoteName(res);

        if(includeOctave) res += std::to_string(octave);

        return std::move(res);

    }

    Note& print() const
    {
        std::cout << toString(true) << ": " << getMidiPitch() << std::endl;
        return *const_cast<Note*>(this);
    }

    void clear()
    {
        mNote = 0;
        mNoteString.clear();
        mSharp = 0;
    }

    // Equality operator
    bool operator==(const Note& other) const
    {
        return mNote == other.mNote;
    }

    bool operator!=(const Note& other) const
    {
        return mNote != other.mNote;
    }

    bool operator<(const Note& other) const
    {
        return mNote < other.mNote;
    }

    // Assignment operator
    Note& operator=(const int& note)
    {
        set(note);
        return *this;
    }

    // Assignment operator
    Note& operator=(const std::string& note)
    {
        set(note);
        return *this;
    }
    
    // Cast to int
    operator int() const
    {
        return mNote;
    }

    // Cast to string
    operator std::string() const
    {
        return toString();
    }

    // Transpose
    void transpose(int semitones)
    {
        int n = mNote + semitones;
        clear();
        set(n);
    }

    Note operator+(const int& semitones) const
    {
        return Note{mNote + semitones};
    }

    Note operator-(const int& semitones) const
    {
        return Note{mNote - semitones};
    }

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

    void flatten()
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
    }

    void sharpen()
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
    }

    std::vector<Note> getMajorNotes()
    {
        std::vector<Note> notes;
        auto sv = MajorNoteMap[toString(false)];
        for(auto& s : sv) notes.push_back(s);

        return std::move(notes);
    }

    Note getNoteFromInterval(const Interval& interval) const
    {
        const auto& key = toString(false);
        const auto& deg = interval.getDegree();
        const auto& s   = MajorNoteMapAt(key, deg-1);
        Note note(s);
        note.setOctave(getOctave());
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

    std::vector<Note> getNoteFromInterval(const Intervals& interval) const
    {
        std::vector<Note> notes;
        for(auto& i : interval) notes.push_back(getNoteFromInterval(i));
        return std::move(notes);
    }


private:
    int mNote = 0;
    std::string mNoteString = "";
    
    int mSharp = 0;

    // Display sharp or flat
    bool sharp() const
    {
        if(mSharp == 0) return mPreferSharp;
        return mSharp  > 0; 
    }
};



using NoteVector = std::vector<Note>;
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

    Notes(const Intervals& intervals, const Note& root = C0)
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

    void set(const Intervals& intervals, const Note& root = C0)
    {
        clear();
        for(auto& interval : intervals)
        {
            Note note = root + interval.getSemitones();
            push_back(note);
        }
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

    void print() const
    {
        std::cout << "Notes(";
        auto it = begin();
        while(it != end())
        {
            std::cout << it->toString(false);
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
        return at(i).getMidiPitch();
    }

};






} // namespace cmtk
