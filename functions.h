#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <stdbool.h>

struct Location{
    int x = 0;
    int y = 0;
    char type; // land, water, start, or treasure
    char dirT; // direction travelled to get to this spot
    bool dis = false; // true if discovered, false if not
};

struct Captain{
    deque<Location> search;

    Location sailLocation;

};

struct FirstMate{
    deque<Location> search;

    Location searchLocation;
};

struct Verbose{

};

struct Stats{
    int numWater = 0;
    int numLand = 0;
    int numAshore= 0;
    // path length should be calculated during backtrace
};


class TreasureHunt {
    
public:
    
    // Read in the CSV music file through stdin.
    void create_map();

    // Read and process command line arguments.
    void get_options(int argc, char** argv);

    // captain hunt
    void cap_search();

    //first mate hunt
    void fm_search();
    
    // Sort and print the data.
    void run();

    void hunt(char, deque<Location> &, Location);
    
    
private:

    // 2D map with char, dicovered, and search direction    
    std::vector<std::vector<Location>> map;
    
    // first mate container
    string firstMate = "";
    FirstMate mate;

    // captain container type
    string captain = "";
    Captain cap;

    // Order of hunt type
    string huntOrder;
    
    // made true for verbose and stats output
    bool vbose = false;
    bool stats = false;

    // contains M or L for output map
    string showP = "";

    Location startLoc;

    Location treasureLoc;
};

// functions to get the location that is N|S|E|W
// these return based on a location not being discovered and it being a valid map location
// other function takes care of chekcing land or water
Location north(Location &current,vector<vector<Location>> &map);
Location south(Location &current,vector<vector<Location>> &map);
Location east(Location &current,vector<vector<Location>> &map);
Location west(Location &current,vector<vector<Location>> &map);

