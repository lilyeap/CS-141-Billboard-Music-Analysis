/* ---------------------------------------------
Program 4: Billboard Analysis

Course: CS 141, Spring 2022. Tues 5pm lab
System: Replit
Author: Lily Eap. UIN: 676977984
---------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

using namespace std;

struct songInfo{
  string month;
  string day;
  string year;
  string rank;
  string song;
  string artist;
  string lastWeek;
  string peakRank;
  string wksOnBoard;
};

//fx is called when user types 1
void menuOpt1(vector<songInfo> songList){
  cout << endl << "Total number of rows: " << songList.size() << endl;
  int uniquesongLine = 0;
  
  //creates a vector full of unique songs. the for loop will only append a song if it hasn't been found in the vector
  vector<string> uniqueSongs;
  for (int song = 0; song < songList.size(); song++){
    if (count(uniqueSongs.begin(), uniqueSongs.end(), songList[song].song)){
      continue;
    } else {
      uniqueSongs.push_back(songList[song].song);
      uniquesongLine++; 
    }
  }
  cout << "Number of unique songs represented in the dataset: " << uniquesongLine << endl;
}

//this fx is attached to menuOpt2 fx. this will check what type of time period (year or decade), and will create two vectors with songs in only that period
void menu2Search(vector<songInfo> songList, int searchTime, int typePeriod){

  int topOccurrences = 0;
  int tempTopOccurrences;
  
  //creating 2 vectors of the songs only in the time frame!
  vector<songInfo> timeFrameSongInfo;
  vector<string> timeFrameSongName;


  if (typePeriod == 1){
    for (int x = 0; x < songList.size(); x++){
      if ((songList[x].year.substr(0, 3) == to_string(searchTime).substr(0,3)) && (songList[x].rank == "1")) {
        timeFrameSongInfo.push_back(songList[x]);
        timeFrameSongName.push_back(songList[x].song);
      }
    }
  } else if (typePeriod == 2){
    for (int x = 0; x < songList.size(); x++){
      if ((songList[x].year == to_string(searchTime)) && (songList[x].rank == "1")) {
        timeFrameSongInfo.push_back(songList[x]);
        timeFrameSongName.push_back(songList[x].song);
      }
    }
  }

  //add top occurring songs that we find into the vector. but if we find a song that occurs more than we will clear it
  vector<songInfo> topSongs;
  vector<string> topSongName;
  //iterating through the vector to find the most frequent songs
  for (int idx = 0; idx < timeFrameSongName.size(); idx++){
    tempTopOccurrences = count(timeFrameSongName.begin(), timeFrameSongName.end(), timeFrameSongName[idx]);
    if (tempTopOccurrences > topOccurrences){
      topSongs.clear();
      topSongs.push_back(timeFrameSongInfo[idx]);
      topSongName.clear();
      topSongName.push_back(timeFrameSongInfo[idx].song);
      topOccurrences = tempTopOccurrences;
    } else if (tempTopOccurrences == topOccurrences){
      if (count(topSongName.begin(), topSongName.end(), timeFrameSongInfo[idx].song)){
      } else {
        topSongs.push_back(timeFrameSongInfo[idx]);
        topSongName.push_back(timeFrameSongInfo[idx].song);
      }
    }
  }
  
  cout << "The song(s) with the most #1 occurrences for selected time period is: " << endl;
  for (int i = 0; i < topSongs.size(); i++){
    cout << "        Song Title: " << topSongs[i].song << endl
      << "        Artist: " << topSongs[i].artist << endl
      << "        # of occurrences: " << topOccurrences << endl;
  }
}

//this fx is attached to menuOpt3 fx. this will check what type of time period (year or decade), and will create three vectors with songs in only that period
void menu3Search(vector<songInfo> songList, int searchTime, int typePeriod){

  int topWks = 0;
  int topIDX; 
  int tempTopWks;
  
  //creating 3 vectors of the songs only in the time frame!
  vector<string> timeFrameSongName;
  vector<string> timeFrameSongArtist;
  vector<int> timeFrameSongWksOnBoard;

  if (typePeriod == 1){
    for (int x = 0; x < songList.size(); x++){
      if (songList[x].year.substr(0, 3) == to_string(searchTime).substr(0,3)) {
        timeFrameSongName.push_back(songList[x].song);
        timeFrameSongArtist.push_back(songList[x].artist);
        timeFrameSongWksOnBoard.push_back(stoi(songList[x].wksOnBoard));
      }
    }
  } else if (typePeriod == 2){
    for (int x = 0; x < songList.size(); x++){
      if (songList[x].year == to_string(searchTime)) {
        timeFrameSongName.push_back(songList[x].song);
        timeFrameSongArtist.push_back(songList[x].artist);
        timeFrameSongWksOnBoard.push_back(stoi(songList[x].wksOnBoard));
      }
    }
  }

  //iterating through the vector to find the song with the most weeks
  topWks = timeFrameSongWksOnBoard[0];
  for (int idx = 0; idx < timeFrameSongName.size(); idx++){
    tempTopWks = timeFrameSongWksOnBoard[idx];
    if (tempTopWks > topWks){
      topWks = tempTopWks;
      topIDX = idx;
    }
  }
  
  cout << "The song with the highest number of weeks on the charts is: " << endl
    << "        " << timeFrameSongName[topIDX]<< " by " 
    << timeFrameSongArtist[topIDX] << " with " << timeFrameSongWksOnBoard[topIDX]
    << " weeks on the chart." << endl;
  
}

//this fx is attached to menuOpt4 fx. this will check what type of time period (year or decade), and will create two vectors with songs in only that period
void menu4Search(vector<songInfo> songList, int searchTime, int typePeriod){

  int lastWk = 0;
  int topIDX = 0; 
  int tempLastWk;
  
  //creating 3 vectors of the songs only in the time frame!
  vector<songInfo> songInFrame;
  vector<int> timeFrameSongClimb;
  int currentClimb;

  if (typePeriod == 1){
    for (int x = 0; x < songList.size(); x++){
      if (songList[x].year.substr(0, 3) == to_string(searchTime).substr(0,3)) {
        if (songList[x].rank == ""){
          currentClimb = 0;
        } else if (songList[x].lastWeek == ""){
          currentClimb = 0;
        } else {
          currentClimb = stoi(songList[x].lastWeek) - stoi(songList[x].rank);
          timeFrameSongClimb.push_back(currentClimb);
          songInFrame.push_back(songList[x]);
        }
      }
    }
  } else if (typePeriod == 2){
    for (int x = 0; x < songList.size(); x++){
      if (songList[x].year == to_string(searchTime)) {
        songInFrame.push_back(songList[x]);
        if ((songList[x].rank == "") || (songList[x].lastWeek == "")){
          currentClimb = 0;
        } else {
          currentClimb = stoi(songList[x].lastWeek) - stoi(songList[x].rank);
        }
        timeFrameSongClimb.push_back(currentClimb);
      }
    }
  }

  //iterate through the songs and each iteration we will store the song's climb and compare it to the top song climb vector. if we find a song that has a higher climb, then we will clear the vector and append the higher climb song 
  vector<songInfo> topSongs;
  vector<int> topSongClimb;
  lastWk = timeFrameSongClimb[0];
  for (int idx = 0; idx < timeFrameSongClimb.size(); idx++){
    tempLastWk = timeFrameSongClimb[idx];
    if (tempLastWk > lastWk){
      topSongs.clear();
      topSongs.push_back(songInFrame[idx]);
      topSongClimb.clear();
      topSongClimb.push_back(timeFrameSongClimb[idx]);
      
      lastWk = tempLastWk;
      
    } else if (tempLastWk == lastWk){
      topSongs.push_back(songInFrame[idx]);
      topSongClimb.push_back(timeFrameSongClimb[idx]);
    }
  }
  cout << "The song(s) with the greatest climb from previous week to current week position: " << endl;
  for (int i = 0; i < topSongs.size(); i++){
    cout << "        Song Title: " << topSongs[i].song << endl
    << "         Artist: " << topSongs[i].artist << endl
    << "         Week of: " << topSongs[i].month << "/" << topSongs[i].day << "/" << topSongs[i].year << endl
    << "         Previous Week Position: " << topSongs[i].lastWeek << endl
    << "         Current Week Position: " << topSongs[i].rank << endl
    << "         Difference of " << topSongClimb[i] << " between previous week and current week position" << endl;
  }
  
}

//fx is called when user types 2
void menuOpt2(vector<songInfo> songList, int dataFile){
  bool choseDecade = false;
  bool choseYear = false;
  bool validTime = false;
  char typeTimePD; 

  //asking for decade or year
  while (validTime == false){
    cout << "Enter D to select a decade or Y to select a year." << endl
    << "Your choice --> ";
    cin >> typeTimePD; 
    
    if (tolower(typeTimePD) == 'd'){
      choseDecade = true;
      validTime = true;
    } else if (tolower(typeTimePD) == 'y'){
      choseYear = true;
      validTime = true;
    } else{
      cout << "Invalid entry. Try again." << endl;
      continue;
    }
  }
  
  //asking for the time period
  int searchTime;
  int searchType;
  if (choseDecade == true){
    cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
    cin >> searchTime;
    searchType = 1;
  } else if (choseYear == true){
    cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
    cin >> searchTime;
    searchType = 2;
  }

  //will call menu2Search based on what time frame and file we are looking for 
  if ((dataFile == 1) && (searchTime >= 1960) && (searchTime <= 1980)){
    menu2Search(songList, searchTime, searchType);
  } else if ((dataFile == 2) && (searchTime >= 1980) && (searchTime <= 2000)){
    menu2Search(songList, searchTime, searchType);
  } else if ((dataFile == 3) && (searchTime >= 2000) && (searchTime <= 2020)){
    menu2Search(songList, searchTime, searchType);
  } else {
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
  }

}

void menuOpt3(vector<songInfo> songList, int dataFile){
  bool choseDecade = false;
  bool choseYear = false;
  bool validTime = false;
  char typeTimePD; 
  
  //asking for decade or year
  while (validTime == false){
    cout << "Enter D to select a decade or Y to select a year." << endl
    << "Your choice --> ";
    cin >> typeTimePD; 
    
    if (tolower(typeTimePD) == 'd'){
      choseDecade = true;
      validTime = true;
    } else if (tolower(typeTimePD) == 'y'){
      choseYear = true;
      validTime = true;
    } else{
      cout << "Invalid entry. Try again.";
      continue;
    }
  }

  //asking for the time period
  int searchTime;
  int searchType;
  if (choseDecade == true){
    cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
    cin >> searchTime;
    searchType = 1;
  } else if (choseYear == true){
    cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
    cin >> searchTime;
    searchType = 2;
  }

  //will call menu3Search based on what time frame and file we are looking for 
  if ((dataFile == 1) && (searchTime >= 1960) && (searchTime <= 1980)){
    menu3Search(songList, searchTime, searchType);
  } else if ((dataFile == 2) && (searchTime >= 1980) && (searchTime <= 2000)){
    menu3Search(songList, searchTime, searchType);
  } else if ((dataFile == 3) && (searchTime >= 2000) && (searchTime <= 2020)){
    menu3Search(songList, searchTime, searchType);
  } else {
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
  }

}

void menuOpt4(vector<songInfo> songList, int dataFile){
  bool choseDecade = false;
  bool choseYear = false;
  bool validTime = false;
  char typeTimePD; 

  //asking for decade or year
  while (validTime == false){
    cout << "Enter D to select a decade or Y to select a year." << endl
    << "Your choice --> ";
    cin >> typeTimePD; 
    
    if (tolower(typeTimePD) == 'd'){
      choseDecade = true;
      validTime = true;
    } else if (tolower(typeTimePD) == 'y'){
      choseYear = true;
      validTime = true;
    } else{
      cout << "Invalid entry. Try again.";
      continue;
    }
  }

  //asking for the time period
  int searchTime;
  int searchType;
  if (choseDecade == true){
    cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
    cin >> searchTime;
    searchType = 1;
  } else if (choseYear == true){
    cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
    cin >> searchTime;
    searchType = 2;
  }

  //will call menu4Search based on what time frame and file we are looking for 
  if ((dataFile == 1) && (searchTime >= 1960) && (searchTime <= 1980)){
    menu4Search(songList, searchTime, searchType);
  } else if ((dataFile == 2) && (searchTime >= 1980) && (searchTime <= 2000)){
    menu4Search(songList, searchTime, searchType);
  } else if ((dataFile == 3) && (searchTime >= 2000) && (searchTime <= 2020)){
    menu4Search(songList, searchTime, searchType);
  } else {
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
  }

}

void menuOpt5(vector<songInfo> songList){
  //receive user's desired artist
  string artistName;
  cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " ;
  cin.ignore();
  getline(cin, artistName, '\n');

  //checks if user string is in any artist string in the file. if so, it will append to a vector
  vector<songInfo> artistSongs;
  
  for (int i=0; i < artistName.size(); ++i){
    artistName[i] = tolower(artistName[i]);
  }
  
  string songArtists = "";
  for (int idx = 0; idx < songList.size(); idx++){
    songArtists = "";
    for (int i=0; i < songList[idx].artist.size(); ++i)
      songArtists += tolower(songList[idx].artist[i]);
    if ((songArtists.find(artistName) != string::npos) && (songList[idx].rank == "1")){
      artistSongs.push_back(songList[idx]);
    }
  }

  //if vector is empty then no artist are found. if vector is not empty it will output the artists top songs. checks if the artist has more than 10 songs (which is max to be printed)
  if (artistSongs.empty()){
    cout << "No matching artists were found." << endl;
  } else {
    int loop = 0;
    if (artistSongs.size() < 10){
      loop = artistSongs.size();
    } else {
      loop = 10;
    }
    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
    for (int i = 0; i < loop; i++){
    cout << i+1 << ") Song: " << artistSongs[i].song << endl
      << "    Artist: " << artistSongs[i].artist << endl
      << "    Week of: " << artistSongs[i].month << "/" << artistSongs[i].day << "/" << artistSongs[i].year << endl
      << "    Week Position: " << artistSongs[i].rank << endl;
    }
  } 
}

int main()
{	
  int dataFile, menuOption;

	cout << "Program 4: BillBoard Analysis " << endl
	    << "CS 141, Spring 2022, UIC " << endl << " "<< endl
	    << "This program will analyze weekly Billboard data spanning from 1960 - 2020." << endl << endl
      << "Select file option:" << endl
      << "   1. To analyze charts top 50: 1960 - 1980 data file" << endl
      << "   2. To analyze charts top 50: 1981 - 2000 data file" << endl 
    << "   3. To analyze charts top 50: 2001 - 2020 data file" << endl
    << "Your choice --> \n" ;
  cin >> dataFile;

  
  bool analysis;
  string file;
  if (dataFile == 1){
    file = "charts_top50_1960_1980.csv";
    analysis = true;
  } else if (dataFile == 2){
    file = "charts_top50_1981_2000.csv";
    analysis = true;
  } else if (dataFile == 3){
    file = "charts_top50_2001_2020.csv";
    analysis = true;
  } else {
    cout << "Invalid value. Exiting Program." ;
    analysis = false;
  }

  fstream musicFile;
  musicFile.open(file,ios::in);

  //splits the line in accordance to its data and puts it in a struct which is then stored in a vector of all songs
  string line;
  vector<songInfo> songList;
  getline(musicFile, line); //skip first row
  songInfo songLine;
  while(getline(musicFile, line)){
    stringstream mStream(line);
    getline(mStream, songLine.month, '/');
    getline(mStream, songLine.day, '/');
    getline(mStream, songLine.year, ',');
    getline(mStream, songLine.rank, ',');
    getline(mStream, songLine.song, ',');
    getline(mStream, songLine.artist, ',');
    getline(mStream, songLine.lastWeek, ',');
    getline(mStream, songLine.peakRank, ',');
    getline(mStream, songLine.wksOnBoard, ',');

    songList.push_back(songLine);
  }

  while(analysis == true) {
    cout <<  "\nSelect a menu option: " << endl
    << "   1. Display overall information about the data" << endl
    << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year" << endl
    << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year" << endl
    << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year" << endl
    << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search" << endl
    << "   6. Exit" << endl
    << "Your choice --> ";
  	cin >> menuOption;
    
  	if (menuOption == 1){
  	  menuOpt1(songList);
      continue;
  	}
  	else if (menuOption == 2){
  	  menuOpt2(songList, dataFile);
      continue;
  	}
  	else if (menuOption == 3){
      menuOpt3(songList, dataFile);
  	  continue;
    }
    else if (menuOption == 4){
      menuOpt4(songList, dataFile);
  	  continue;
    }
    else if (menuOption == 5){
      menuOpt5(songList);
  	  continue;
    }
    else if (menuOption == 6){
  	  analysis = false;
    } else {
      cout << "\nInvalid value.  Please re-enter a value from the menu options below.\n"; 
      continue;
    }
  };	
}