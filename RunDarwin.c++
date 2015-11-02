// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <string>    // string
#include "Darwin.c++"  //Darwin Class

#define DEBUG_SPECIES false

// ----
// main
// ----

int main () 
{
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
	Species Food({"left","go 0"},'f',"Food");
	#if DEBUG_SPECIES
	Food.print_program();
	#endif
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species Hopper({"hop","go 0"},'h',"Hopper");
	#if DEBUG_SPECIES
	Hopper.print_program();
	#endif
    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
	Species Rover({"if_enemy 9","if_empty 7","if_random 5","left",
					"go 0","right","go 0","hop","go 0","infect",
					"go 0"},'r',"Rover");
	#if DEBUG_SPECIES
	Rover.print_program();
	#endif	
	
	
    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
	Species Trap({"if_enemy 3","left","go 0","infect","go 0"},'t',"Trap");
	#if DEBUG_SPECIES
	Trap.print_program();
	#endif	

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
	vector<Creature> run1;
	run1.push_back(Creature(Food,1));
	run1.push_back(Creature(Hopper,0));
	run1.push_back(Creature(Hopper,1));
	run1.push_back(Creature(Hopper,2));
	run1.push_back(Creature(Hopper,3));
	run1.push_back(Creature(Food,0));
	
	Darwin<8,8> dar1;
	dar1.add_creature(run1[0],0);
	dar1.add_creature(run1[1],27);
	dar1.add_creature(run1[2],28);
	dar1.add_creature(run1[3],36);
	dar1.add_creature(run1[4],35);
	dar1.add_creature(run1[5],63);
	
	dar1.print_grid();

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
	
	//Darwin<7,9> dar2;
	//dar2.print_grid();

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;
}