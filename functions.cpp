#include "functions.h"
#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <stdbool.h>

using namespace std;


void TreasureHunt::create_map(){
    int mapSize;
    char mapT; 
    char next;
    string line;
    while(cin.peek()== '#'){
        getline(cin, line);
    }
    cin >> mapT >> mapSize;

    Location loc;

    //vector< vector<Location> > map(mapSize, vector<Location>(mapSize, loc));
    map.resize(mapSize, vector<Location>(mapSize));
    

    if(mapT == 'M'){
        char let;
        int row = 0;
        int col = 0;
        while(cin >> let){
            Location loc;
            loc.type = let;
            loc.x = row;
            loc.y = col;
            if(let == '@'){startLoc = loc;}
            map[row][col] = loc;


            if(col < mapSize){++col;}
            else if(col >= mapSize){col = 0; ++row;}
        } //while
    } // if M


    if(mapT == 'L'){
        char let;
        int row = 0;
        int col = 0;
        while(cin >> row >> col >> let){
            Location loc;
            loc.type = let;
            loc.x = row;
            loc.y = col;

            if(let == '@'){startLoc = loc;}

            map[row][col] = loc;
        }//while
    }//if L
   
}//create_map


bool TreasureHunt::cap_hunt(){
    bool foundT = false;
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(cap.sailLocation, map); // call appropriate location grabber function
            // check that the newLoc is land
            if(newLoc.type == 'o'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                cap.search.push_back(newLoc); // add the location to the captain deque
            }
            // check if the newLoc is land or treasure and hand the search off to the firstmate
            else if(newLoc.type == '.' || newLoc.type == '$'){foundT = fm_search(newLoc);}
        }

        else if(curD == 'S'){
            newLoc = south(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }
            else if(newLoc.type == '.' || newLoc.type == '$'){foundT = fm_search(newLoc);}
        }

        else if(curD == 'E'){
            newLoc = east(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }
            else if(newLoc.type == '.' || newLoc.type == '$'){foundT = fm_search(newLoc);}
        }

        else if(curD == 'W'){
            newLoc = west(cap.sailLocation, map);
            if(newLoc.type == 'o'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }
            else if(newLoc.type == '.' || newLoc.type == '$'){foundT = fm_search(newLoc);}
        }
    }
    return foundT;
}


void TreasureHunt::fm_hunt(){
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(mate.searchLocation, map); // call appropriate location grabber function
            // check that the newLoc is water or treasure
            if(newLoc.type == '.' || newLoc.type == '$'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                mate.search.push_back(newLoc); // add the location to the first mate dequq
            }
        }

        else if(curD == 'S'){
            newLoc = south(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'E'){
            newLoc = east(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'W'){
            newLoc = west(mate.searchLocation, map);
            if(newLoc.type == '.' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }//if
        }//else if
    }
}



void TreasureHunt::cap_search(){
    bool foundT = false;
    // add start locaiton to deque
    startLoc.dis = true;
    cap.search.push_back(startLoc);

    // while container not empty
    while(!cap.search.empty() && !foundT){
        // set sailLocation to next location
        // if captain is a queue use front and pop front
        if(captain== "QUEUE"){
            cap.sailLocation = cap.search.front();
            cap.search.pop_front();
        }
        //if captain is a stack use back and pop back
        else if(captain == "STACK"){
            cap.sailLocation = cap.search.back();
            cap.search.pop_back();
        }
        // follow hunt order to add new locations
        foundT = cap_hunt();
    }
    // hunt ended, report outcome
}

bool TreasureHunt::fm_search(Location landLoc){
    bool foundT = false;
    mate.search.push_back(landLoc);

    //check if container is empty
    while(!mate.search.empty() && !foundT){

        if(firstMate == "QUEUE"){
            if(mate.search.front().type == '$'){
                foundT = true;
                break;
            }//if
            mate.searchLocation = mate.search.front();
            mate.search.pop_front();
        }//if

        else if(firstMate == "STACK"){
            //check if back is treasure
            if(mate.search.back().type == '$'){
                foundT = true;
                break;
            }//if
            mate.searchLocation = mate.search.back();
            mate.search.pop_back();
        }//else if

        fm_hunt();
        
    }//while
    return foundT;
}

