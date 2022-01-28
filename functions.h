// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <stdbool.h>

struct Location{
    int x = 0;
    int y = 0;
    char type = '.'; // land, water, start, or treasure
    char dirT; // direction travelled to get to this spot
    bool dis = false; // true if discovered, false if not
};

struct Back{
    int r = 0;
    int c = 0;
};

/*struct Captain{
    Location sailLocation;

};

struct FirstMate{

    Location searchLocation;
};*/

/*struct Stats{
    int numWater = 0;
    int numLand = 0;
    int numAshore= 0;
    // path length should be calculated during backtrace
};*/


class TreasureHunt {
    
public:
    
    // Read in the CSV music file through stdin.
    void create_map();

    // Read and process command line arguments.
    void get_options(int argc, char** argv);

    // captain search
    void cap_search();

    //first mate search, returns true if $found
    bool fm_search(const Location &landLoc, std::deque<Location> &searchMate);

    // captain hunt returns T if $found (calls fm_search when land is hit)
    bool cap_hunt(std::deque<Location> &search, std::deque<Location> &searchMate);

    // fm hunt, breaks when treasure is found
    bool fm_hunt(std::deque<Location> &search);

    //calls the functions for verbose, stats, and show path
    void report();
    void print_verbose(const Location &hitLand, bool found);
    void print_show_pathM();
    void print_show_pathL(std::deque<Location> &path);
    void print_stats();

    std::deque<Location> backtrace();

    
private:

    // 2D map with char, dicovered, and search direction    
    std::vector<std::vector<Location>> map;

    Location startLoc;

    Location treasureLoc;

    Location sailLocation;
    Location searchLocation;
    
    // first mate container
    std::string firstMate = "QUEUE";
    //FirstMate mate;

    // captain container type
    std::string captain = "STACK";
    //Captain cap;

    // Order of hunt type
    std::string huntOrder = "NESW";
    
    

    // contains M or L for output map
    std::string showP = "X";

    

    int numLandI = 0;
    int numWaterI = 0;
    int numAshore = 0;

    // in the hitLand vector dirT says if treasure was found by fm
    //std::vector<Location> hitLand;

    int pathLength = 0;
    // made true for verbose and stats output
    bool vbose = false;
    bool stats = false;

    //contains the path, need to popfront for printing
    //std::deque<Location> Path;
};

// functions to get the location that is N|S|E|W
// these return based on a location not being discovered and it being a valid map location
// other function takes care of chekcing land or water
Location north(const Location &current, std::vector<std::vector<Location>> &map);
Location south(const Location &current, std::vector<std::vector<Location>> &map);
Location east(const Location &current, std::vector<std::vector<Location>> &map);
Location west(const Location &current, std::vector<std::vector<Location>> &map);

