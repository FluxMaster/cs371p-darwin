#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <algorithm> // fill
#include <string>    // string
#include <vector>    // vector
#include <sstream>   // ostringstream

using namespace std;


class Species
{
	private:
		std::vector<std::string> program;
		char symbol;
		string name;
	public:
		Species(std::vector<std::string> p, char s, string n)
		{
			symbol = s;
			program = p;
			name = n;
		};
		char render()
		{
			return symbol;
		}
		//debug
		void print_program()
		{
			cout << name << " " << symbol << "\n";
			for(unsigned int i = 0; i < program.size(); i++)
			{
				cout << program[i] << "\n";
			}
			cout << "\n";
		}
};

inline ostream& operator<<(ostream& os, Species& s)
{ 
	os << s.render();
	return os;
}

class Creature
{
	private:
		Species* spec;
		int pc = 0;
		int dir; /* 0-N 1-E 2-S 3-W */
	public:
		Creature(Species s, int d)
		{
			spec = &s;
			dir = d;
		}
		char render()
		{
			ostringstream os;
			os << *spec;
			string str = os.str();
			const char* chr = str.c_str();
			//printf("chr[0]:%c\n",chr[0]);
			return chr[0];
		}
		Creature()
		{
				spec = NULL;
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
		
		
		
};