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
	
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species Hopper({"hop","go 0"},'h',"Hopper");
	
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

	// ----
	// best
	// ----
	/*
	0:"if_enemy 2",
    1:"go 4",
	2:"infect",
	3:"go 0",
	4:"if_enemy 0",
	5:"left",
	6:"if_enemy 0",
	7:"left",
	8:"if_enemy 0",
	9:"left",
	10:"if_enemy 0",
	11:"if_wall 17",
	12:"if_random 15",
	13:"left",
	14:"go 12",
	15:"hop",
	16:"go 12",
	17:"left",
	18:"if_enemy 0",
	19:"left",
	20:"go 10",
	21:"if_enemy 0",
	22:"if_empty 26",
	23:"left",
	24:"go 22",
	25:"infect",
	26:"if_random 21",
	27:"if_random 21",
	28:"if_random 21",
	29:"if_random 21",
	30:"if_random 21",
	31:"if_random 21",
	32:"go 0"
	*/
	Species Best({"if_enemy 2","go 4","infect","go 0","if_enemy 0",
					"left","if_enemy 0","left","if_enemy 0","left",
					"if_enemy 0","if_wall 17","if_random 15","left",
					"go 10","hop","go 10","left","if_enemy 0","left",
					"go 10","if_enemy 0","if_empty 26","left","go 22",
					"infect","if_random 21","if_random 21","if_random 21",
					"if_random 21","if_random 21","if_random 21","go 1"},'b',"Best");
	
	
	
	
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
	
	run1.insert(run1.end(),Creature(Food,1));
	run1.insert(run1.end(),Creature(Hopper,0));
	run1.insert(run1.end(),Creature(Hopper,1));
	run1.insert(run1.end(),Creature(Hopper,2));
	run1.insert(run1.end(),Creature(Hopper,3));
	run1.insert(run1.end(),Creature(Food,0));
	
	
	
	Darwin<8,8> dar1;
	dar1.add_creature(run1[0],0);
	dar1.add_creature(run1[1],27);
	dar1.add_creature(run1[2],28);
	dar1.add_creature(run1[3],36);
	dar1.add_creature(run1[4],35);
	dar1.add_creature(run1[5],63);
	
	//dar1[0].print_program();
	cout << "Turn: 0" << endl;
	dar1.print_grid();
	cout << endl;
	for(int i = 0; i < 10; i++)
	{
		cout << "Turn: " << i+1 << endl;
		dar1.next_turn(i);
		dar1.print_grid();
		cout << endl;
	}
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
	
	
	
	vector<Creature> run2;
	
	run2.insert(run2.end(),Creature(Trap,2));
	run2.insert(run2.end(),Creature(Hopper,1));
	run2.insert(run2.end(),Creature(Rover,0));
	run2.insert(run2.end(),Creature(Trap,3));
	
	Darwin<7,9> dar2;
	
	dar2.add_creature(run2[0],0);
	dar2.add_creature(run2[1],29);
	dar2.add_creature(run2[2],49);
	dar2.add_creature(run2[3],62);
	
	cout << "Turn: 0" << endl;
	dar2.print_grid();
	cout << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << "Turn: " << i+1 << endl;
		dar2.next_turn(i);
		dar2.print_grid();
		cout << endl;
	}
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
	****
	EDIT: I ordered mine "north east south west", so I'll need to do some adjusting. 
	CURSE YOU DIFFERING STANDARDS!
	
	WNES
	NESW
	
	****
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
	
	Darwin<72,72> dar3;

	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar3.add_creature(Creature(Food,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar3.add_creature(Creature(Hopper,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar3.add_creature(Creature(Rover,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar3.add_creature(Creature(Trap,dir),pos);
	}
	
	cout << endl;
	for(int i = 0; i <= 1000; i++)
	{
		if(i<10 || i%100 == 0)
		{
			cout << "Turn: " << i << endl;
			dar3.print_grid();
			cout << endl;
		}
		dar3.next_turn(i);
		
	}
	
	
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
	Darwin<72,72> dar4;

	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar4.add_creature(Creature(Food,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar4.add_creature(Creature(Hopper,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar4.add_creature(Creature(Rover,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar4.add_creature(Creature(Trap,dir),pos);
	}
	for(int i = 0; i < 10; i++)
	{
		int pos = rand()%5184;
		int dir = rand()%4;
		dir--;
		if(dir<0)
			dir+=4;
		dar4.add_creature(Creature(Best,dir),pos);
	}
	
	cout << endl;
	for(int i = 0; i <= 1000; i++)
	{
		if(i<10 || i%100 == 0)
		{
			cout << "Turn: " << i << endl;
			dar4.print_grid();
			cout << endl;
		}
		dar4.next_turn(i);
		
	}
	
    return 0;
}