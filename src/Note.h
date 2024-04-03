#pragma once
// Classes to handle the creation of the music

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cctype>
#include "Interval.h"
#include "Chords.h"

namespace cmtk {


// ----------------------------------------------------------------------- //
// ----------------------- Note Class ------------------------------------ //
// ----------------------------------------------------------------------- //
class Note 
{
public:
    Note() = default;
    // Constructor to create a note from a string
    Note(const std::string& note)
    {
        this->setNoteSymbol(note);
    }

    // Function to set the note from a string
    void setNoteSymbol(std::string noteSymbol, int octave=0)
    {
        // Convert the note to lowercase
        std::transform(noteSymbol.begin(), noteSymbol.end(), noteSymbol.begin(), ::tolower);

        // Remove all spaces from the note symbol
        noteSymbol.erase(std::remove(noteSymbol.begin(), noteSymbol.end(), ' '), noteSymbol.end());

        // Use the note to set the note value
        if      (noteSymbol == "c"                       ){ this->note =  0; } 
        else if (noteSymbol == "c#" || noteSymbol == "db"){ this->note =  1; } 
        else if (noteSymbol == "d"                       ){ this->note =  2; } 
        else if (noteSymbol == "d#" || noteSymbol == "eb"){ this->note =  3; }
        else if (noteSymbol == "e"                       ){ this->note =  4; }
        else if (noteSymbol == "f"                       ){ this->note =  5; }
        else if (noteSymbol == "f#" || noteSymbol == "gb"){ this->note =  6; }
        else if (noteSymbol == "g"                       ){ this->note =  7; }
        else if (noteSymbol == "g#" || noteSymbol == "ab"){ this->note =  8; }
        else if (noteSymbol == "a"                       ){ this->note =  9; }
        else if (noteSymbol == "a#" || noteSymbol == "bb"){ this->note = 10; }
        else if (noteSymbol == "b"                       ){ this->note = 11; }
    }

private:
    int note = -1;
};

} // namespace cmtk
