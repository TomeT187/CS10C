#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {

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
  void InsertAfter(PlaylistNode* nextNode);
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
  Playlist()
    : head(nullptr),tail(nullptr)
  {}
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

