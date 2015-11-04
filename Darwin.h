#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <algorithm> // fill
#include <string>    // string
#include <vector>    // vector
#include <sstream>   // ostringstream
#include <cstring>   // strcmp

using namespace std;

class Creature;

class Species
{
	private:
		std::vector<std::string> program;
		char symbol;
		string name;
	public:
		
		inline string next_instruction(int& pc, Creature& fnt, Creature& self);
		inline pair<string,int> parse_line(string line);
		inline char render();
		inline bool real();
		Species(std::vector<std::string> p, char s, string n)
		{
			symbol = s;
			program = p;
			name = n;
		};
		Species(){};
		
		bool operator==(Species s)
		{
			if((render()) == s.render())
				return true;
			return false;
		}
		
		//debug
		void print_program()
		{
			cout << name << " " << symbol << "\n";
			cout << program.size() << "\n";
			//cout << program.at(0) << "\n";
			//cout << program.at(1) << "\n";
			for(unsigned int i = 0; i < program.size(); i++)
			{
				cout << i << ":" << program[i] << "\n";
			}
			cout << "\n";
		}
};

inline ostream& operator<<(ostream& os, Species& s)
{ 
	os << s.render();
	return os;
}

template <std::size_t N, std::size_t M>
class Darwin;

class Creature
{
	private:
		Species spec;
		int pc = 0;
		int dir; /* 0-N 1-E 2-S 3-W */
		int turntaken = -1;
	public:
		Creature(Species s, int d)
		{
			spec = s;
			dir = d;
		}
		Creature()
		{
			Species spec();
		}
		inline void infect_me(Species s);
		inline char render();
		template <std::size_t N, std::size_t M>
		void take_turn(Darwin<N,M>& d, int position, int turn);
		template <std::size_t N, std::size_t M>
		void in_front(Darwin<N,M>& d, int position, Creature& fnt);
		inline bool real();
		bool operator==(Creature c)
		{
			if((render()) == c.render())
				return true;
			return false;
		}
		bool operator!=(Creature c)
		{
			if((render()) == c.render())
				return false;
			return true;
		}
		//Debug
		void print_program()
		{
			(spec).print_program();
		}
};

inline ostream& operator<<(ostream& os, Creature& c)
{ 
	os << c.render();
	return os;
}


template <std::size_t N, std::size_t M>
class Darwin
{
	private:
		char symbol_grid[N*M];
		Creature creature_grid[N*M];
		int size;
	public:
		Darwin()
		{ 
			std::fill(&symbol_grid[0], &symbol_grid[N*M],'.'); 
			size = N*M;
		};
		void print_grid();
		void add_creature(Creature c, int location);
		void next_turn(int turn);
		void request_hop(Creature& c,int dir, int position);
		void request_infect(Creature& c, Species s, int dir, int pos);
		Creature& at(int x)
		{
			return (*this)[x];
		}
		Creature& begin(int x)
		{
			return (*this)[0];
		}
		Creature& end(int x)
		{
			return (*this)[size-1];
		}
		Creature& operator[](int x)
		{
			return creature_grid[x];
		}
};
