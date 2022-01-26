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
    //char next;
    string line;

    //check for comment on the first line
    while(cin.peek()== '#'){
        getline(cin, line); //read the comment into junk
    }//while

    //read in the mapType and mapSize
    cin >> mapT >> mapSize;

    //Location loc;

    // resize TreasureHunt::map based on size
    map.resize(mapSize, vector<Location>(mapSize));
    
    // reading in map in grid form
    if(mapT == 'M'){
        // initialize variable for location struct
        char let;
        int row = 0;
        int col = 0;
        // read in all the char in map grid
        while(cin >> let){
            Location loc; // create and modify a location
            loc.type = let;
            loc.x = row;
            loc.y = col;
        
            if(let == '@'){startLoc = loc;} // set start location
            map[row][col] = loc; // add location to map

            if(col < mapSize - 1){++col;} // incriment col until reaching end of a row
            else if(col >= mapSize - 1){col = 0; ++row;} // reset column and change to new row
        } //while
    } // if M

    //reading in map in coordinate form
    if(mapT == 'L'){
        char let;
        int row = 0;
        int col = 0;
        // read in coordinates and symbols
        while(cin >> row >> col >> let){
            Location loc; //create new location
            loc.type = let;
            loc.x = row;
            loc.y = col;
            if(let == '@'){startLoc = loc;} // set start location

            map[row][col] = loc; // add location to map
        }//while
    }//if L
}//create_map


bool TreasureHunt::cap_hunt(){
    bool foundT = false; // variable to track if treasure is found

    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(cap.sailLocation, map); // call appropriate location grabber function
            // check that the newLoc is land
            if(newLoc.type == '.'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                cap.search.push_back(newLoc); // add the location to the captain deque
            }//if
            // check if the newLoc is land or treasure and hand the search off to the firstmate
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//if N

        else if(curD == 'S'){
            newLoc = south(cap.sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
               foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if S

        else if(curD == 'E'){
            newLoc = east(cap.sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if E

        else if(curD == 'W'){
            newLoc = west(cap.sailLocation, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc, foundT);}
                ++numAshore;
            }//else if
        }//else if W
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
            if(newLoc.type == 'o' || newLoc.type == '$'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                mate.search.push_back(newLoc); // add the location to the first mate dequq
            }
        }

        else if(curD == 'S'){
            newLoc = south(mate.searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'E'){
            newLoc = east(mate.searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }
        }

        else if(curD == 'W'){
            newLoc = west(mate.searchLocation, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
            }//if
        }//else if
    }
}



void TreasureHunt::cap_search(){
    if(vbose){cout << "Treasure hunt started at: " << startLoc.x << "," << startLoc.y <<endl;}
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
            ++numWaterI;
        }
        //if captain is a stack use back and pop back
        else if(captain == "STACK"){
            cap.sailLocation = cap.search.back();
            cap.search.pop_back();
            ++numWaterI;
        }
        // follow hunt order to add new locations
        foundT = cap_hunt();
    }
    // hunt ended, report outcome
    if(vbose){
        if(treasureLoc.type != '$'){cout << "Treasure hunt failed" <<endl;}
    }
}

bool TreasureHunt::fm_search(Location landLoc){
    if(vbose){cout << "Searching island... ";}
    bool foundT = false;
    mate.search.push_back(landLoc);

    //check if container is empty
    while(!mate.search.empty() && !foundT){

        if(firstMate == "QUEUE"){
            if(mate.search.front().type == '$'){
                foundT = true;
                treasureLoc = mate.search.front();
                break;
            }//if
            mate.searchLocation = mate.search.front();
            mate.search.pop_front();
            ++numLandI;
        }//if

        else if(firstMate == "STACK"){
            //check if back is treasure
            if(mate.search.back().type == '$'){
                treasureLoc = mate.search.back();
                foundT = true;
                break;
            }//if
            mate.searchLocation = mate.search.back();
            mate.search.pop_back();
            ++numLandI;
        }//else if

        fm_hunt();
        
    }//while
    return foundT;
}

Back opposite_direction(char direction, Location loc){
    Back prevLoc;
    if(direction == 'N'){
        //backwards is south
        prevLoc.r = loc.x - 1;
        prevLoc.c = loc.y;
        prevLoc.nextDir = 'S';
    }
    else if(direction == 'S'){
        //backwards is N
        prevLoc.r = loc.x + 1;
        prevLoc.c = loc.y;
        prevLoc.nextDir = 'N';
    }
    else if(direction == 'E'){
        //backwards is  W
        prevLoc.r = loc.x;
        prevLoc.c = loc.y - 1;
        prevLoc.nextDir = 'W';
    }
    else if(direction == 'W'){
        //backwards is E
        prevLoc.r = loc.x;
        prevLoc.c = loc.y + 1;
        prevLoc.nextDir = 'E';
    }
    return prevLoc;
}

void TreasureHunt::backtrace(){
    
    Location cur = treasureLoc;
    treasureLoc.type = 'X';
    Path.push_front(cur);
    

    while(cur.x != startLoc.x && cur.y != startLoc.y){
        Back nextDirection = opposite_direction(cur.dirT, cur);
        Location next = map[nextDirection.r][nextDirection.c];
        Path.push_front(next);
        // we have our current Loc and next Loc
        if((cur.dirT == 'N' || cur.dirT == 'S') &&(next.dirT == 'N' || next.dirT == 'S')){
            map[next.x][next.y].type = '|';
        }
        else if((cur.dirT == 'N' || cur.dirT == 'S') &&(next.dirT == 'E' || next.dirT == 'W')){
            map[next.x][next.y].type = '+';
        }
        else if((cur.dirT == 'E' || cur.dirT == 'W') &&(next.dirT == 'E' || next.dirT == 'W')){
            map[next.x][next.y].type = '-';
        }
        else if((cur.dirT == 'E' || cur.dirT == 'W') &&(next.dirT == 'N' || next.dirT == 'S')){
            map[next.x][next.y].type = '+';
        }
        
        cur = next;
        ++pathLength;
    }
    Path.push_front(startLoc);

}

void TreasureHunt::report(){
    //verbose called during search

    if(stats){
        //call print_stats
        print_stats();
    }

    if(showP == 'M' && treasureLoc.type == '$'){
        backtrace();
        print_show_pathM();
    }

    if(showP == 'L' && treasureLoc.type == '$'){
        backtrace();
        print_show_pathM();
    }

    if(treasureLoc.type == '$' || treasureLoc.type == 'X'){
        cout << "Treasure found at " << treasureLoc.x << "," << treasureLoc.y;
        cout << " with path length " << pathLength << "." << endl;
    }
    if(treasureLoc.type != '$' && treasureLoc.type != 'X'){
        cout << "No treasure found after invesigating " << numLandI+numWaterI;
        cout << " locations." << endl;
        
    }


}

void TreasureHunt::print_stats(){
    cout << "--- STATS ---" << endl;

    cout << "Starting location: " << startLoc.x<< "," << startLoc.y<<endl;
    cout << "Water locations investigated: " << numWaterI << endl;
    cout << "Land locations investigated: " << numLandI << endl;
    cout << "Went ashore: " << numAshore << endl;

    if(treasureLoc.type == '$'){
        cout << "Path length: " << pathLength << endl;
        cout << "Treasure location: " << treasureLoc.x << "," << treasureLoc.y <<endl;
    }
    
    cout << "--- STATS ---" << endl;
} 

void TreasureHunt::print_verbose(Location hitLand, bool found){

    cout << "Went ashore at: " << hitLand.x << "," << hitLand.y <<endl;
    cout << "Searching island... ";

    if(found){
        cout << "party found treasure at " << treasureLoc.x << "," << treasureLoc.y << "." <<endl;
    }
    else{
        cout << "party returned with no treasure." << endl;
    }
    
}

void TreasureHunt::print_show_pathM(){
    for(size_t r = 0; r < map.size(); ++r){
        for(size_t c = 0; c < map.size(); ++c){
            cout << map[r][c].type;
        }
        cout << endl;
    }
    
}

void TreasureHunt::print_show_pathL(){
    cout << "Sail:"<<endl;
    while(Path.front().type == '.' || Path.front().type == '@'){
       cout << Path.front().x << "," << Path.front().y <<endl;
       Path.pop_front();
    }
    cout << "Search:" << endl;
    while(Path.front().type == '.' || Path.front().type == 'X'){
       cout << Path.front().x << "," << Path.front().y <<endl;
       Path.pop_front();
    }
}