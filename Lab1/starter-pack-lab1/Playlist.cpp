#include "Playlist.h"

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
void PlaylistNode::InsertAfter(const string& id, const std::string& song, const std::string& artist, int length){
  PlaylistNode* newSong = new PlaylistNode(id,song,artist,length);//creates a new song node
  newSong->SetNext(nextNodePtr);                                  //sets the new node's next to the original's next
  SetNext(newSong);                                               //sets original's next to the new node
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  // CODETURD: This is a stub.  You'll remove it and put in code for a
  // CODETURD: real insert here.
  PlaylistNode* newSongNode = new PlaylistNode(id,song,artist,length);
  
  //if the playlist is empty -> sets both head and tail to new song
  if(head == nullptr){
    head = newSongNode;
    tail = newSongNode;
  }else{//otherwise sets tail's next to new song and re assigns tail to new song
    tail->SetNext(newSongNode);
    tail = newSongNode;
  }
  songCount++;
}
//Zybooks step 6
//asks user for the id of a song to remove
void Playlist::RemoveSong() {
  if(head == nullptr){
      cout << "Nothing Deleted, playlist is empty" << endl;
      return;
    }
  string IDtoRemove;
  cout << "Enter song's unique ID:" << endl;
  cin >> IDtoRemove;
  for(PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    if(curr->GetID() == IDtoRemove){
      DeleteSong(curr);
    }
  }
  //DeleteSong(IDtoRemove);
  
  
}
void Playlist::DeleteSong(PlaylistNode* nodeToRemove){
  PlaylistNode* prevToRemove = head;

  if(head == nodeToRemove){//if head is the song to remove
    head = head->GetNext();
    delete nodeToRemove;
    songCount--;
    return;
  }
  for( PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {//will never segfault by dereferencing a nullptr because
    if(curr->GetNext() == nodeToRemove){                                    //the node is garunteed to exist before the function is 
      prevToRemove = curr;                                                  //called
    }
  }
  prevToRemove->SetNext(nodeToRemove->GetNext());                               //sets the previous node's next to current's next
  cout << "\"" << nodeToRemove->GetSongName() << "\" removed" << endl;
  delete nodeToRemove;                                                  //deletes curr
  songCount--;
}
    
  


//Zybooks Step 7
//Asks user for the posistion of a song and the desired new position
//valid positions are 1 to the number of nodes  
//if they enter less than 1, move it to the head
//  else if it is greater than the number of nodes, move it to the tail 
void Playlist::ChangePositionSong() {
  int firstPosistion, secondPosistion;
  cout << "Enter song's current position:" << endl;
  cin >> firstPosistion;
  if(firstPosistion > songCount){
    cout << "invalid song number" << endl;
    return;
  }
  cout << "Enter new position for song:" << endl;
  cin >> secondPosistion;

  PlaylistNode* originalSong = head;
    for(int i = 1; i < firstPosistion; i++){//iterates through the playlist and reasigns original song to the node at
      originalSong = originalSong->GetNext();//the index give by the user
    }

  if(secondPosistion > songCount){// if the new posistion is greater than the playlist length then moves the song to the tail
    //uses AddSong to add original Song to back of the playlist
    tail->InsertAfter(originalSong->GetID(),originalSong->GetSongName(),originalSong->GetArtistName(),originalSong->GetSongLength());
    tail = tail->GetNext();//reasigns tail 
    //deletes original song
    DeleteSong(originalSong);
  }
  else if(secondPosistion < 1){//if the new posistion is less than 1 it moves the song to the head
    PlaylistNode* newSong = new PlaylistNode(originalSong->GetID(),originalSong->GetSongName(),originalSong->GetArtistName(),originalSong->GetSongLength());
    newSong->SetNext(head);
    head = newSong;
    DeleteSong(originalSong);
  }
  else{cout<<"unfinished"<<endl;}


  cout << "change position song" << endl;
}
    
void Playlist::OutputSongsByArtist() const {
  cout << "output songs by artist" << endl;
}
    
void Playlist::OutputTotalTime() const {
  // CODETURD: We write a lot of traversal loops with linked lists
  // CODETURD: They come in a couple of forms, but this is very
  // CODETURD: common.  Since this is a 'const' routine, the head
  // CODETURD: pointer is const, so we use a const curr.
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
  }
  cout << "output total time" << endl;
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
    cout << "Song Length (in seconds): " << curr->GetSongLength();
    cout << endl;
    counter++;
  }
  
}
    

