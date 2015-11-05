// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

#include "Darwin.c++"

using namespace std;

// -----------
// TestDarwin
// -----------

//---------------------
//Creature Construction
//---------------------
TEST(DarwinFixture, creature)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	ostringstream os;
	os << alice;
	string str = os.str();
	const char* chr = str.c_str();
	ASSERT_EQ(*chr, 'f');
}

// -----------------------
// at() and add_creature()
// -----------------------

TEST(DarwinFixture, at_1)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	dar.add_creature(alice,0);
	Creature *bob;
	bob = &dar.at(0);
	ASSERT_EQ(&(*bob), &dar.at(0));
}

TEST(DarwinFixture, at_2)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	dar.add_creature(alice,63);
	Creature *bob;
	bob = &dar.at(63);
	ASSERT_EQ(&(*bob), &dar.at(63));
}


TEST(DarwinFixture, at_3)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	dar.add_creature(alice,20);
	Creature *bob;
	bob = &dar.at(20);
	ASSERT_EQ(&(*bob), &dar.at(20));
}
	


// ----
// begin
// ----
TEST(DarwinFixture, begin)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	dar.add_creature(alice,0);
	Creature *bob;
	bob = dar.begin();
	ASSERT_EQ(&(*bob), &dar.at(0));
}


// ---
// end
// ---
TEST(DarwinFixture, end)
{
	Darwin<8,8> dar;
	Species Food({"left","go 0"},'f',"Food");
	Creature alice(Food,0);
	dar.add_creature(alice,63);
	Creature *bob;
	bob = dar.end();
	ASSERT_EQ(&(*(bob-1)), &dar.at(63));
}


// --------
// Iterable
// --------
TEST(DarwinFixture, iterable_1)
{
	Darwin<1,3> dar;
	Species Alice({"left","go 0"},'a',"Alice");
	Species Bob({"left","go 0"},'b',"Bob");
	Species Charles({"left","go 0"},'c',"Charles");
	dar.add_creature(Creature(Alice,0),0);
	dar.add_creature(Creature(Bob,0),1);
	dar.add_creature(Creature(Charles,0),2);
	ostringstream os;
	for( auto it = dar.begin(); it != dar.end(); it++)
	{
		os << *it;
	}
	string str = os.str();
	ASSERT_EQ(str,"abc");
}

TEST(DarwinFixture, iterable_2)
{
	Darwin<1,3> dar;
	Species Alice({"left","go 0"},'a',"Alice");
	Species Bob({"left","go 0"},'b',"Bob");
	Species Charles({"left","go 0"},'c',"Charles");
	dar.add_creature(Creature(Alice,0),0);
	dar.add_creature(Creature(Bob,0),1);
	dar.add_creature(Creature(Charles,0),2);
	ostringstream os;
	for( auto it = dar.end()-1; it != dar.begin()-1; it--)
	{
		os << *it;
	}
	string str = os.str();
	ASSERT_EQ(str,"cba");
}

//---------------
//add_instruction
//---------------

TEST(DarwinFixture, add_instruction_1)
{
	Species Alice({"left","go 0"},'a',"Alice");
	Alice.add_instruction("right");
	string str = Alice.print_program();
	ASSERT_EQ(str,"left go 0 right ");
}


TEST(DarwinFixture, add_instruction_2)
{
	Species Alice({},'a',"Alice");
	Alice.add_instruction("right");
	string str = Alice.print_program();
	ASSERT_EQ(str,"right ");
}

//---------------
//Run Simulations
//---------------
TEST(DarwinFixture, simulation)
{
	Species Food({"left","go 0"},'f',"Food");
	Species Hopper({"hop","go 0"},'h',"Hopper");
	
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
	
	for(int i = 0; i < 10; i++)
	{
		dar1.next_turn(i);
	}
	string str = dar1.debug_grid();
	ASSERT_EQ(str,"f..h....\n........\n........\n.......h\nh.......\n........\n........\n....h..f\n");
}

