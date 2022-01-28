// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include "functions.h"
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <stdbool.h>

using namespace std;

////////////////////////////////// CREATE_MAP //////////////////////////////////
void TreasureHunt::create_map(){
    int mapSize;
    char mapT; 
    //char next;
    string line;

    //check for comment on the first line
    while(cin.peek() == '#'){
        getline(cin, line); //read the comment into junk
    }//while

    //read in the mapType and mapSize
    cin >> mapT >> mapSize;

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
            //++numElts;
        }//while
    }//if L
}//create_map

///////////////////////////////////// CAP_SEARCH ////////////////////////////////
void TreasureHunt::cap_search(){
    if(vbose){cout << "Treasure hunt started at: " << startLoc.x << "," << startLoc.y <<'\n';}
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
        if(treasureLoc.type != '$'){cout << "Treasure hunt failed" <<'\n';}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////// CAP_HUNT ///////////////////////////////////////////
bool TreasureHunt::cap_hunt(){
    bool foundT = false; // variable to track if treasure is found

    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(cap.sailLocation.x, cap.sailLocation.y, map); // call appropriate location grabber function
            // check that the newLoc is land
            if(newLoc.type == '.'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                cap.search.push_back(newLoc); // add the location to the captain deque
            }//if
            // check if the newLoc is land or treasure and hand the search off to the firstmate
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'N';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc.x, newLoc.y, foundT);}
                ++numAshore;
            }//else if
        }//if N

        else if(curD == 'S'){
            newLoc = south(cap.sailLocation.x, cap.sailLocation.y, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'S';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm DELETE?
                if(vbose){print_verbose(newLoc.x, newLoc.y, foundT);}
                ++numAshore;
            }//else if
        }//else if S

        else if(curD == 'E'){
            newLoc = east(cap.sailLocation.x, cap.sailLocation.y, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'E';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc.x, newLoc.y, foundT);}
                ++numAshore;
            }//else if
        }//else if E

        else if(curD == 'W'){
            newLoc = west(cap.sailLocation.x, cap.sailLocation.y, map);
            if(newLoc.type == '.'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                cap.search.push_back(newLoc);
            }//if
            else if(newLoc.type == 'o' || newLoc.type == '$'){
                newLoc.dirT = 'W';
                newLoc.dis = true;
                map[newLoc.x][newLoc.y] = newLoc;
                foundT = fm_search(newLoc);
                newLoc.dirT = foundT; // in the hitLand vector dirT says if treasure was found by fm
                if(vbose){print_verbose(newLoc.x, newLoc.y, foundT);}
                ++numAshore;
            }//else if
        }//else if W
    }
    return foundT;
}
/////////////////////////////////////////////////////////////////

////////////////////////////////////////// FM_SEARCH ////////////////////////////////////////
bool TreasureHunt::fm_search(const Location &landLoc){
    bool foundT = false;
    bool tInHunt = false;
    mate.search.push_back(landLoc);

    if(landLoc.type == '$'){
        ++numLandI;
        foundT = true;
        treasureLoc = mate.search.back();
    }

    //check if container is empty
    while(!mate.search.empty() && !foundT && !tInHunt){

        if(firstMate == "QUEUE"){
            mate.searchLocation = mate.search.front();
            mate.search.pop_front();
            ++numLandI;
        }//if

        else if(firstMate == "STACK"){
            mate.searchLocation = mate.search.back();
            mate.search.pop_back();
            ++numLandI;
        }//else if

        tInHunt = fm_hunt();
        if(tInHunt){
            ++numLandI;
            foundT = true;
            treasureLoc = mate.search.back();
        }
        
    }//while
    return foundT;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////// FM_HUNT /////////////////////////////////////////////////////
bool TreasureHunt::fm_hunt(){
    bool found = false;
    for(int i = 0; i < 4; ++i){
        char curD = huntOrder[i];
        Location newLoc;

        // check what direction to search
        if(curD == 'N'){
            newLoc = north(mate.searchLocation.x, mate.searchLocation.y, map); // call appropriate location grabber function
            // check that the newLoc is water or treasure
            if(newLoc.type == 'o' || newLoc.type == '$'){ 
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'N'; // add the direction travelled to find the location
                mate.search.push_back(newLoc); // add the location to the first mate dequq
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'S'){
            newLoc = south(mate.searchLocation.x, mate.searchLocation.y, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'S'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'E'){
            newLoc = east(mate.searchLocation.x, mate.searchLocation.y, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'E'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }
        }

        else if(curD == 'W'){
            newLoc = west(mate.searchLocation.x, mate.searchLocation.y, map);
            if(newLoc.type == 'o' || newLoc.type == '$'){
                map[newLoc.x][newLoc.y].dis = true; //mark as discovered before adding
                map[newLoc.x][newLoc.y].dirT = 'W'; // add the direction travelled to find the location
                mate.search.push_back(newLoc);
                if(newLoc.type == '$'){ return true;}
            }//if
        }//else if
    }
    return found;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////
void TreasureHunt::report(){
    //verbose called during search
    backtrace();
    if(stats){
        //call print_stats
        //backtrace();
        print_stats();
    }

    if(showP == "M" && treasureLoc.type == 'X'){
        //backtrace();
        print_show_pathM();
    }

    if(showP == "L" && treasureLoc.type == 'X'){
        //backtrace();
        print_show_pathL();
    }

    if(treasureLoc.type == '$' || treasureLoc.type == 'X'){
        cout << "Treasure found at " << treasureLoc.x << "," << treasureLoc.y;
        cout << " with path length " << pathLength << "." << '\n';
    }
    if(treasureLoc.type != '$' && treasureLoc.type != 'X'){
        cout << "No treasure found after investigating " << numLandI+numWaterI;
        cout << " locations." << '\n';
        
    }


}
//////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////// BACKTRACE ///////////////////////////////
void TreasureHunt::backtrace(){
    if(treasureLoc.type == '$'){treasureLoc.type = 'X';}
    Location cur = treasureLoc;
    
    //map[treasureLoc.x][treasureLoc.y].type = 'X';
    Path.push_front(cur);
    

    while(!(cur.x == startLoc.x && cur.y == startLoc.y)){
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
}
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////// OPPOSITE_DIRECTION ///////////////////////////////////////////
Back opposite_direction(char direction, Location loc){
    Back prevLoc;
    if(direction == 'N'){
        //backwards is south
        prevLoc.r = loc.x + 1;
        prevLoc.c = loc.y;
    }
    else if(direction == 'S'){
        //backwards is N
        prevLoc.r = loc.x - 1;
        prevLoc.c = loc.y;
    }
    else if(direction == 'E'){
        //backwards is  W
        prevLoc.r = loc.x;
        prevLoc.c = loc.y - 1;
    }
    else if(direction == 'W'){
        //backwards is E
        prevLoc.r = loc.x;
        prevLoc.c = loc.y + 1;
    }
    return prevLoc;
}
///////////////////////////////////////////////////////////////////////////////


void TreasureHunt::print_stats(){
    cout << "--- STATS ---" << '\n';

    cout << "Starting location: " << startLoc.x<< "," << startLoc.y<<'\n';
    cout << "Water locations investigated: " << numWaterI << '\n';
    cout << "Land locations investigated: " << numLandI << '\n';
    cout << "Went ashore: " << numAshore << '\n';

    if(treasureLoc.type == 'X'){
        cout << "Path length: " << pathLength << '\n';
        cout << "Treasure location: " << treasureLoc.x << "," << treasureLoc.y <<'\n';
    }
    
    cout << "--- STATS ---" << '\n';
} 

void TreasureHunt::print_verbose(int hitLandx, int hitLandy, bool found){

    cout << "Went ashore at: " << hitLandx << "," << hitLandy <<'\n';
    cout << "Searching island... ";

    if(found){
        cout << "party found treasure at " << treasureLoc.x << "," << treasureLoc.y << "." <<'\n';
    }
    else{
        cout << "party returned with no treasure." << '\n';
    }
    
}

void TreasureHunt::print_show_pathM(){
    map[treasureLoc.x][treasureLoc.y].type = 'X';
    for(size_t r = 0; r < map.size(); ++r){
        for(size_t c = 0; c < map.size(); ++c){
            cout << map[r][c].type;
        }
        cout << '\n';
    }
    
}

void TreasureHunt::print_show_pathL(){
    cout << "Sail:"<<'\n';
    while(Path.front().type == '.' || Path.front().type == '@'){
       cout << Path.front().x << "," << Path.front().y <<'\n';
       Path.pop_front();
    }
    cout << "Search:" << '\n';
    while(Path.front().type == 'o' || Path.front().type == 'X'){
       cout << Path.front().x << "," << Path.front().y <<'\n';
       Path.pop_front();
    }
}