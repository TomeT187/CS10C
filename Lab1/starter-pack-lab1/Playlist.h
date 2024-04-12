// -*-c++-*-

// CODETURD: Use this pragma in your header files.  It will save
// CODETURD: you a lot of grief in your career.  You sometimes see
// CODETURD: this with #define/#ifdef guards, but this is better
// CODETURD: and safer since it works regardless of where the file
// CODETURD: lives and cannot be spooffed with an accidental
// CODETURD: #define
#pragma once



#include <iostream>
using namespace std;

class PlaylistNode {
  // CODETURD: Printer methods should be defined as const
  // CODETURD: since they don't change anything. Accessors
  // CODETURD: that return internal pointers are normally defined
  // CODETURD: as both const AND non-const.  Accessors that return
  // CODETURD: large structures like strings/vectors typically
  // CODETURD: are const AND return const references (e.g. GetSongName()
  // CODETURD: should return a const string&) Accessors that return
  // CODETURD: small items like ints or doubles are just const that
  // CODETURD: return a non-const value like 'int myIntVal() const;'

/*

This is from the zybook... remove it before turning in... (ProfPat)

Build the PlaylistNode class per the following specifications.
Note: Some functions can initially be function stubs (empty functions),
to be completed in later steps.

Default constructor (1 pt)
Parameterized constructor (1 pt)
Public member functions
InsertAfter() (1 pt)
SetNext() - Mutator (1 pt)
GetID() - Accessor
GetSongName() - Accessor
GetArtistName() - Accessor
GetSongLength() - Accessor
GetNext() - Accessor
PrintPlaylistNode()

Private data members
string uniqueID - Initialized to "none" in default constructor
string songName - Initialized to "none" in default constructor
string artistName - Initialized to "none" in default constructor
int songLength - Initialized to 0 in default constructor
PlaylistNode* nextNodePtr - Initialized to 0 in default constructor

*/
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  //default constructor - sets strings to "none" length and pointer to 0 according to Zybooks
  PlaylistNode() 
    : uniqueID("none"),songName("none"),artistName("none"), songLength(0), nextNodePtr(0) {};
  //Parameterized constructor - takes in inputs for private variables and sets next pointer to nullptr
  PlaylistNode(string IDIn,string SongNameIn,string ArtistNameIn,int SongLengthIn)
    : uniqueID(IDIn),songName(SongNameIn),artistName(ArtistNameIn), songLength(SongLengthIn), nextNodePtr(nullptr) {};
  void InsertAfter(const string& id, const std::string& song, const std::string& artist, int length);
  void SetNext(PlaylistNode* nextNodePtrIn) {nextNodePtr = nextNodePtrIn;}
  
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
  }
};

class Playlist {
  PlaylistNode* head;
  PlaylistNode* tail;
  int songCount = 0; //stores the number of songs in the playlist - changed when a song is added or deleted
  void DeleteSong(PlaylistNode* nodeToRemove);//helper function for remove song
public:
  // CODETURD: Please use the : form to initialize member variables
  // CODETURD: This is the proper, professional way to do it
  // CODETURD: It is also acceptable to use the C++14 style
  // CODETURD: method where you would say 'PlaylistNode* head = nullptr;'
  // CODETURD: above
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  // CODETURD: I added the complete headers for PrintMenu() and
  // CODETURD: AddSong() for you
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

