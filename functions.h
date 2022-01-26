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

struct Back{
    int r = 0;
    int c = 0;
    char nextDir = 'I';
};

struct Captain{
    std::deque<Location> search;

    Location sailLocation;

};

struct FirstMate{
    std::deque<Location> search;

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

    // captain search
    void cap_search();

    //first mate search, returns true if $found
    bool fm_search(Location landLoc);

    // captain hunt returns T if $found (calls fm_search when land is hit)
    bool cap_hunt();

    // fm hunt, breaks when treasure is found
    void fm_hunt();

    //calls the functions for verbose, stats, and show path
    void report();
    
    // Sort and print the data.
    void run();

    void backtrace();

    
private:

    // 2D map with char, dicovered, and search direction    
    std::vector<std::vector<Location>> map;
    
    // first mate container
    std::string firstMate = "";
    FirstMate mate;

    // captain container type
    std::string captain = "";
    Captain cap;

    // Order of hunt type
    std::string huntOrder;
    
    // made true for verbose and stats output
    bool vbose = false;
    bool stats = false;

    // contains M or L for output map
    std::string showP = "";

    Location startLoc;

    Location treasureLoc;

    int numLandI = 0;
    int numWaterI = 0;
    int numAshore = 0;

    // in the hitLand vector dirT says if treasure was found by fm
    std::vector<Location> hitLand;

    int pathLength = 0;
};

// functions to get the location that is N|S|E|W
// these return based on a location not being discovered and it being a valid map location
// other function takes care of chekcing land or water
Location north(Location &current,std::vector<std::vector<Location>> &map);
Location south(Location &current,std::vector<std::vector<Location>> &map);
Location east(Location &current,std::vector<std::vector<Location>> &map);
Location west(Location &current,std::vector<std::vector<Location>> &map);

