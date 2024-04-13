#include "Playlist.h"
#include <string>
#include <iostream>


//Zybooks Step 3
void Playlist::PrintMenu(const string& title) const {  
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
  cout << endl;
  cout << "Choose an option:" << endl;
}

//Zybooks Step 5
//Adds song to the end of the list
//does not reasign tail - if used on the tail then tail needs to be reasigned manually
void PlaylistNode::InsertAfter(PlaylistNode* nextNode){
  nextNode->SetNext(nextNodePtr);                                  //sets the new node's next to the original's next
  SetNext(nextNode);                                               //sets original's next to the new node
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  PlaylistNode* newSongNode = new PlaylistNode(id,song,artist,length);
  
  //if the playlist is empty -> sets both head and tail to new song
  if(head == nullptr){
    head = newSongNode;
    tail = newSongNode;
  }else{//otherwise sets tail's next to new song and re assigns tail to new song
    tail->SetNext(newSongNode);
    tail = newSongNode;
  }
  songCount++;//used to keep track of number of songs in the playlist
}

//Zybooks step 6
//asks user for the id of a song to remove
void Playlist::RemoveSong() {
  //if the playlist is empty, nothing happens
  if(head == nullptr){
    cout << "Nothing Deleted, playlist is empty" << endl;
    return;
  }
  string IDtoRemove;
  cout << "REMOVE SONG" << endl;
  cout << "Enter song's unique ID:" << endl;
  cin >> IDtoRemove;
  //loops through the playlist until the desired node is found
  //uses delete song helper function
  for(PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    if(curr->GetID() == IDtoRemove){
      DeleteSong(curr);
      cout << "\"" << curr->GetSongName() << "\" removed." << endl << endl;
    }
  }
  
}
void Playlist::DeleteSong(PlaylistNode* nodeToRemove){
  PlaylistNode* prevToRemove = head;//stores the node before one to be removed

  if(head == nodeToRemove){//if head is the song to remove
    head = head->GetNext();//reasigns head and frees memory
    delete nodeToRemove;   
    songCount--;
    return;
  }
  //finds the location of the node to remove
  //and the node before it
  for( PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {//will never segfault by dereferencing a nullptr because
    if(curr->GetNext() == nodeToRemove){                                    //the node is garunteed to exist before the function is 
      prevToRemove = curr;                                                  //called
    }
  }
  prevToRemove->SetNext(nodeToRemove->GetNext());//sets the previous node's next to the node after the deleted one
  delete nodeToRemove;
  songCount--;
}
    
//Zybooks Step 7
//Asks user for the posistion of a song and the desired new position
//valid positions are 1 to the number of nodes  
//if they enter less than 1, move it to the head
//  else if it is greater than the number of nodes, move it to the tail 
void Playlist::ChangePositionSong() {
  int originalPosistion, newPosistion;
  cout << "Enter song's current position:" << endl;
  cin >> originalPosistion;
  //if the chosen song is greater than or less than the size of the playlist then the function does nothing
  if(originalPosistion > songCount || (originalPosistion < 1) ){
    cout << "invalid song number" << endl;
    return;
  }
  cout << "Enter new position for song:" << endl;
  cin >> newPosistion;

  //iterates through the originalPosistion times as entered by the user
  //finds the node of the song to be moved
  PlaylistNode* originalSong = head;
    for(int i = 1; i < originalPosistion; i++){
      originalSong = originalSong->GetNext();
    }
    PlaylistNode* nextNode = new PlaylistNode(originalSong->GetID(),originalSong->GetSongName(),originalSong->GetArtistName(),originalSong->GetSongLength());

  if(newPosistion > songCount){// if the new posistion is greater than the playlist length then moves the song to the tail
    tail->InsertAfter(nextNode);
    songCount++;
    tail = tail->GetNext();//reasigns tail 
    //deletes original song
    DeleteSong(originalSong);
  }
  else if(newPosistion <= 1){//if the new posistion is less than 1 it moves the song to the head
    PlaylistNode* newSong = new PlaylistNode(originalSong->GetID(),originalSong->GetSongName(),originalSong->GetArtistName(),originalSong->GetSongLength());
    newSong->SetNext(head);
    songCount++;
    head = newSong;
    DeleteSong(originalSong);
  }
  else{
    DeleteSong(originalSong);
    PlaylistNode* nodeBeforeMoving = head;
    for(int i = 2; i < newPosistion; i++){
      nodeBeforeMoving = nodeBeforeMoving->GetNext();
    }
    nodeBeforeMoving->InsertAfter(nextNode);
    songCount++;
    if(nodeBeforeMoving == tail){
      tail = tail->GetNext();
    }
  }
  cout << "\"" << nextNode->GetSongName() << "\" moved to position " << newPosistion << endl << endl;
}
    
void Playlist::OutputSongsByArtist() const {
  cout << "Enter artist's name:" << endl << endl;
  string artistNameIn;
  getline(cin,artistNameIn);
  int songNumber = 1;
  //iterates through the list and outputs info of a song if it is written by the chosen artist
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    if(curr->GetArtistName() == artistNameIn){
      cout << songNumber << "." << endl;
      cout << "Unique ID: " << curr->GetID() << endl;
      cout << "Song Name: " << curr->GetSongName() << endl;
      cout << "Artist Name: " << curr->GetArtistName() << endl;
      cout << "Song Length (in seconds): " << curr->GetSongLength() << endl;
      cout << endl;
    }
    songNumber++;
  }
}
    
void Playlist::OutputTotalTime() const {
  int sumSeconds = 0;
  //iterates through the list and adds the time of each song to the sum
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    sumSeconds += curr->GetSongLength();
  }

  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  cout << "Total time: " << sumSeconds << " seconds" << endl << endl;
}

//Zybooks Step 4
//outputs info for each node (song) in playlist
//if empty - outputs playlist is empty and returns
void Playlist::OutputFullPlaylist() const {
  if(head == nullptr){
    cout << "Playlist is empty" << endl;
    cout << endl;
    return;
  }
  int counter = 1;//used to output place of song in playlist
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    cout << counter << "." << endl;
    cout << "Unique ID: " << curr->GetID() << endl;
    cout << "Song Name: " << curr->GetSongName() << endl;
    cout << "Artist Name: " << curr->GetArtistName() << endl;
    cout << "Song Length (in seconds): " << curr->GetSongLength() << endl;
    cout << endl;
    counter++;
  }
  
}
    

