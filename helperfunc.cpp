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


Location north(Location &current,vector<vector<Location>> &map){
    int tempR;
    Location newLoc;
    newLoc.type = '#';
    if(current.x - 1 >= 0){
        tempR = current.x - 1;
        Location validLoc = map[tempR][current.y];
        validLoc.dirT = 'N';
        if(!validLoc.dis){return validLoc;}
    }//if
    return newLoc;
}//north

Location south(Location &current,vector<vector<Location>> &map){
    //row +1
    Location tempLoc;
    tempLoc.type = '#';
    if(current.x != map.size()){
        int tempR = current.x +1;
        Location validLoc = map[tempR][current.y];
        validLoc.dirT = 'S';
        if(!validLoc.dis){return validLoc;}//if
    }//if
    return tempLoc;
}//south

Location east(Location &current,vector<vector<Location>> &map){
    //col +1
    Location tempLoc;
    tempLoc.type = '#'; // initialize it as invalid
    if(current.y != map.size()){
        int tempC = current.y +1;
        Location validLoc = map[current.x][tempC];
        validLoc.dirT = 'E';
        //returns the location if the column is valid and it hasn't already been discovered
        if(!validLoc.dis){return validLoc;} 
    }//if
    return tempLoc;
}//east

Location west(Location &current,vector<vector<Location>> &map){
    Location tempLoc;
    tempLoc.type ='#';
    if(current.y - 1 >= 0 ){
        int tempC = current.y - 1;
        Location validLoc = map[current.x][tempC];
        validLoc.dirT = 'W';
        if(!validLoc.dis){return validLoc;}
    }
    return tempLoc;
}