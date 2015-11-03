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


class Species
{
	private:
		std::vector<std::string> program;
		char symbol;
		string name;
	public:
		pair<string,int> parse_line(string line)
		{
			//cout << "parse line\n";
			//print_program();
			//cout << "line: " << line << "\n";
			string command(line.substr(0,line.size()-2));
			//cout << "command: " << command << "\n";
			if(strcmp(command.c_str(), "if_empty")==0)
			{
				char chr = line[line.size()];
				int num = chr - '0';
				pair<string,int> result(command,num);
				return result;
			}
			else if(strcmp(command.c_str(), "if_wall")==0)
			{
				char chr = line[line.size()];
				int num = chr - '0';
				pair<string,int> result(command,num);
				return result;
			}
			else if(strcmp(command.c_str(), "if_random")==0)
			{
				char chr = line[line.size()];
				int num = chr - '0';
				pair<string,int> result(command,num);
				return result;
			}
			else if(strcmp(command.c_str(), "if_enemy")==0)
			{
				char chr = line[line.size()];
				int num = chr - '0';
				pair<string,int> result(command,num);
				return result;
			}
			else if(strcmp(command.c_str(), "g")==0)
			{
				char chr = line[line.size()];
				int num = chr - '0';
				pair<string,int> result(command,num);
				return result;
			}
			else
			{
				pair<string,int> result(line,0);
				return result;
			}
		};
		
		string next_instruction(int pc)
		{
			pair<string,int> line = parse_line(program[pc]);
			return get<0>(line);
		}

		Species(std::vector<std::string> p, char s, string n)
		{
			symbol = s;
			program = p;
			name = n;
		};
		Species(){};
		char render()
		{
			return symbol;
		}
		bool operator==(Species s)
		{
			if((render()) == s.render())
				return true;
			return false;
		}
		bool real()
		{
			if (name.empty())
				return false;
			return true;
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

class Creature
{
	private:
		Species spec;
		int pc = 0;
		int dir; /* 0-N 1-E 2-S 3-W */
		bool turntaken = false;
	public:
		Creature(Species s, int d)
		{
			//cout << "Creation\n";
			spec = s;
			//(*spec).print_program();
			dir = d;
		}
		char render()
		{
			ostringstream os;
			os << spec;
			string str = os.str();
			const char* chr = str.c_str();
			//printf("chr[0]:%c\n",chr[0]);
			return chr[0];
		}
		void take_turn()
		{
			//cout << "take turn\n";
			//(spec).print_program();
			//cout << "Got past it\n";
			(spec).next_instruction(pc);
			turntaken = true;
		}
		Creature()
		{
			Species spec();
		}
		bool real()
		{
			if (spec.real())
				return true;
			return false;
		}
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
		void next_turn();
		Creature& operator[](int x)
		{
			return creature_grid[x];
		}
};