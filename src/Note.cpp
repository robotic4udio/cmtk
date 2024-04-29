#include "Note.h"

namespace cmtk {

// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Note Class ---------------------------------------------- //
// -------------------------------------------------------------------------------------------- //

// Constructor to create a note from a string
Note::Note(const std::string& note)
{
    set(note);
}

// Constructor to create a note from a midinote
Note::Note(int note)
{
    set(note);
}


// Function to set the note from a midinote
Note& Note::set(int note)
{
    clear();
    mNote = note;
    return *this;
}

int Note::getPitch() const
{
    return mNote;
}

int Note::getPitchWrap() const
{
    return mNote%12;
}

float Note::getFreq() const 
{
    return 440.0 * pow(2.0, (mNote - 69) / 12.0);
}

int Note::getOctave() const
{
    return (mNote - C0) / 12;
}

Note& Note::setOctave(int octave)
{
    mNote = mNote % 12 + C0 + octave * 12;
    return *this;
}

Note& Note::shiftOctave(int octaves)
{
    mNote += octaves * 12;
    return *this;
}

// Function to set the note from a string
Note& Note::set(std::string noteSymbol)
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
    else return *this;

    // Take care of flats and sharps
    while(noteSymbol.front() == 'B' || noteSymbol.front() == '#'){
        if      (noteSymbol[0] == 'B') { mNoteString += 'b'; mNote -= 1; mSharp--; }
        else if (noteSymbol[0] == '#') { mNoteString += '#'; mNote += 1; mSharp++; }
        noteSymbol.erase(0,1);
    }

    // Add the octave
    mNote += noteSymbol.empty() ? C1 : C0 + std::stoi(noteSymbol) * 12;

    return *this;
}

// Set from Interval with respedt to its RootNote
Note& Note::set(const Note& aNote, const Interval& interval)
{
    *this = aNote.getNoteAt(interval);
    return *this;
}

// Set from Note
Note& Note::set(const Note& aNote)
{
    *this = aNote;
    return *this;
}

// Set from a Roman Chord Symbol with respect to its RootNote
Note& Note::setRoman(std::string aRomanChordString, const Note& aRootNote)
{
    set(aRootNote, Interval::NewFromRoman(aRomanChordString));
    return *this;
}

std::string Note::toString(bool includeOctave, bool simplify) const
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

Note& Note::print(bool includeOctave, bool simplify) const
{
    std::cout << toString(includeOctave,simplify) << ": " << getPitch() << " = " << getFreq() << " Hz" << std::endl;
    return *const_cast<Note*>(this);
}

Note& Note::clear()
{
    mNote = C1;
    mNoteString.clear();
    mSharp = 0;
    return *this;
}

// Equality operator
bool Note::operator==(const Note& other) const
{
    return mNote == other.mNote;
}

bool Note::operator!=(const Note& other) const
{
    return mNote != other.mNote;
}

bool Note::operator<(const Note& other) const
{
    return mNote < other.mNote;
}

bool Note::operator>(const Note& other) const
{
    return mNote > other.mNote;
}

// Assignment operator
Note& Note::operator=(const int& note)
{
    set(note);
    return *this;
}

// Assignment operator
Note& Note::operator=(const std::string& note)
{
    set(note);
    return *this;
}

// Cast to int
Note::operator int() const
{
    return mNote;
}

// Cast to string
Note::operator std::string() const
{
    return toString();
}

// Transpose
Note& Note::transpose(int n)
{
    if(n == 0) return *this;
    n += mNote;
    set(n);
    return *this;
}

// Transpose Interval
Note& Note::transpose(const Interval& interval)
{
    *this = getNoteAt(interval);
    return *this;
}

Note Note::operator+(const int& semitones) const
{
    return Note{mNote + semitones};
}

Note Note::operator-(const int& semitones) const
{
    return Note{mNote - semitones};
}

Note Note::operator+(const Interval& interval) const
{
    return getNoteAt(interval);
}

Notes Note::operator+(const Intervals& intervals) const
{
    Notes notes;
    for(auto& i : intervals) notes.push_back(getNoteAt(i));
    return std::move(notes);
}

// Increment operator
Note& Note::operator++()
{
    mNote++;
    return *this;
}

// Decrement operator
Note& Note::operator--()
{
    mNote--;
    return *this;
}

// Stream operator
std::ostream& operator<<(std::ostream& os, const Note& note)
{
    os << note.toString();
    return os;
}

bool Note::isKey(const std::string& key) const
{
    return toString(false) == key;
}

Note& Note::flatten()
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

Note& Note::sharpen()
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

Notes Note::getMajorNotes()
{
    std::vector<Note> notes;
    auto sv = MajorNoteMap[toString(false)];
    for(auto& s : sv) notes.push_back(s);

    return std::move(notes);
}

Interval Note::getIntervalTo(const Note& otherNote) const
{
    int semitones = otherNote.getPitch() - getPitch();
    return Interval::NewFromSemi(semitones);
}

Notes Note::getNoteAt(const Intervals& interval) const
{
    std::vector<Note> notes;
    for(auto& i : interval) notes.push_back(getNoteAt(i));
    return std::move(notes);
}

bool Note::isOk() const
{
    return mNote >= 0 && mNote <= 127;
}

Note::operator bool() const
{
    return isOk();
}

// Display sharp or flat
bool Note::sharp() const
{
    if(mSharp == 0) return mPreferSharp;
    return mSharp  > 0; 
}

// Get the note as JSON
json::JSON Note::getJSON() const
{
    json::JSON json;
    json["Note"] = toString(true,false);
    return std::move(json);
}


// -------------------------------------------------------------------------------------------- //
// ---------------------------------- Notes Class --------------------------------------------- //
// -------------------------------------------------------------------------------------------- //
Notes::Notes(const NoteVector& notes)
{
    set(notes);
}

Notes::Notes(const std::string& notes)
{
    set(notes);
}

Notes::Notes(const std::vector<int>& notes)
{
    set(notes);
}

Notes::Notes(const std::vector<std::string>& notes)
{
    set(notes);
}

Notes::Notes(const Intervals& intervals, const Note& root)
{
    set(intervals,root);
}

void Notes::set(const NoteVector& notes)
{
    clear();
    for(auto& note : notes) push_back(note);
}

void Notes::set(const std::vector<int>& notes)
{
    clear();
    for(auto& note : notes) push_back(note);
}

void Notes::set(const std::vector<std::string>& notes)
{
    clear();
    for(auto& note : notes) push_back(note);
}

void Notes::set(const std::string& notes)
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

void Notes::set(const Intervals& intervals, const Note& root)
{
    clear();
    for(auto& interval : intervals)
    {
        Note note = root + interval.getSemi();
        push_back(note);
    }
}

void Notes::add(const Notes& aNotes)
{
    for(auto& note : aNotes) add(note);
}

void Notes::add(const Note& note)
{
    push_back(note);
}

void Notes::add(const std::string& note)
{
    push_back(note);
}

void Notes::add(const int& note)
{
    push_back(note);
}

Notes& Notes::removeDuplicates()
{
    std::sort(begin(),end());
    erase(std::unique(begin(),end()),end());
    return *this;
}

Notes& Notes::removeOctave()
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
std::string Notes::getPitchString() const
{
    std::string res;
    for(const auto& note : *this) res += std::to_string(note.getPitch()) + " ";
    if(!res.empty()) res.pop_back();
    return std::move(res);
}

// Get a string with the pitch vector
std::string Notes::getFreqString() const
{
    std::string res;
    for(const auto& note : *this) res += std::to_string(note.getPitch()) + " ";
    if(!res.empty()) res.pop_back();
    return std::move(res);
}

// To string
std::string Notes::toString(bool octave, bool simplify) const
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
std::ostream& operator<<(std::ostream& os, const Notes& notes)
{        
    auto it = notes.begin();
    while(it != notes.end())
    {
        os << it->toString(false,false);
        if(++it != notes.end()) os << " ";
    }
    return os;
    }

Notes& Notes::print(bool octave, bool simplify)
{
    std::cout << "Notes(";
    auto it = begin();
    while(it != end())
    {
        std::cout << it->toString(octave,simplify);
        if(++it != end()) std::cout << " ";
    }
    std::cout << ")" << std::endl;
    return *this;
}

Notes& Notes::printFreq()
{
    std::cout << "Freq(";
    auto it = begin();
    while(it != end())
    {
        std::cout << it->getFreq();
        if(++it != end()) std::cout << " ";
    }
    std::cout << ")" << std::endl;

    return *this;
}

Notes& Notes::transpose(int semitones)
{
    for(auto& note : *this) note.transpose(semitones);
    return *this;
}

Notes& Notes::sort()
{
    std::sort(begin(),end());
    return *this;
}

// Assignment operator
Notes& Notes::operator=(const std::string& notes)
{
    set(notes);
    return *this;
}

// Assignment operator
Notes& Notes::operator=(const Intervals& intervals)
{
    set(intervals);
    return *this;
}

// Assignment operator
Notes& Notes::operator=(const NoteVector& notes)
{
    set(notes);
    return *this;
}

// Assignment operator
Notes& Notes::operator=(const std::vector<int>& notes)
{
    set(notes);
    return *this;
}

// at operator
Note& Notes::operator[](int i)
{
    return at(i);
}

// Semi at operator
int Notes::semiAt(int i) const
{
    return at(i).getPitch();
}

// Get Vector of semitones
std::vector<int> Notes::getPitch() const
{
    std::vector<int> semis;
    for(auto& note : *this) semis.push_back(note.getPitch());
    return std::move(semis);
}

// Get Vector of frequencies
std::vector<float> Notes::getFreq() const
{
    std::vector<float> freqs;
    auto it = begin();
    while(it != end())
    {
        freqs.push_back(it->getFreq());
        it++;
    }

    return std::move(freqs);
}

// Get Vector of N
Notes Notes::AllKeys()
{
    Notes notes;
    for(auto& s : KeyNames) notes.push_back(Note(s));
    return std::move(notes);
}

// Contains a specific note
bool Notes::contains(const Note& note) const
{
    return std::find(begin(),end(),note) != end();
}

// Contains a specific note ignoring octave
bool Notes::contains(const Note& note, bool ignoreOctave) const
{
    auto it = std::find_if(begin(),end(),[&note,ignoreOctave](const Note& n){
        return ignoreOctave ? n.getPitchWrap() == note.getPitchWrap() : n == note;
    });

    return it != end();
}

// Contains all the notes in another vector
bool Notes::contains(const Notes& notes) const
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
bool Notes::contains(const Notes& notes, bool ignoreOctave) const
{
    auto it = notes.begin();
    while(it != notes.end())
    {
        if(!contains(*it,ignoreOctave)) return false;
        it++;
    }
    return true;
}

bool Notes::ok() const
{
    for(auto& note : *this) if(!note.isOk()) return false;
    return true;
}

// Cast to bool
Notes::operator bool() const
{
    return ok();
}

// Get the notes as JSON
json::JSON Notes::getJSON() const
{
    json::JSON json;
    json::JSON arr = json::Array();
    for(auto& note : *this) arr.append(note.getJSON());
    json["Notes"] = arr;
    return std::move(json);
}


} // namespace cmtk
