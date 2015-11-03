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
		pair<string,int> parse_line(string line)
		{
			//cout << "parse line\n";
			//print_program();
			//cout << "line: " << line << "\n";
			int space = line.find(' ',0);
			//cout << space << endl;
			string command(line.substr(0,space));
			//cout << command << endl;
			//cout << "command: " << command << "\n";
			if(strcmp(command.c_str(), "if_empty")==0)
			{
				string lnum = line.substr(space+1);
				int num = stoi(lnum);
				pair<string,int> result(command,num);
				//cout<< command << " " << num << endl;
				return result;
			}
			else if(strcmp(command.c_str(), "if_wall")==0)
			{
				string lnum = line.substr(space+1);
				int num = stoi(lnum);
				pair<string,int> result(command,num);
				//cout<< command << " " << num << endl;				
				return result;
			}
			else if(strcmp(command.c_str(), "if_random")==0)
			{
				string lnum = line.substr(space+1);
				int num = stoi(lnum);
				pair<string,int> result(command,num);
				//cout<< command << " " << num << endl;
				return result;
			}
			else if(strcmp(command.c_str(), "if_enemy")==0)
			{
				string lnum = line.substr(space+1);
				int num = stoi(lnum);
				pair<string,int> result(command,num);
				//cout<< command << " " << num << endl;
				return result;
			}
			else if(strcmp(command.c_str(), "go")==0)
			{
				string lnum = line.substr(space+1);
				int num = stoi(lnum);
				pair<string,int> result(command,num);
				//cout<< command << " " << num << endl;
				return result;
			}
			else
			{
				pair<string,int> result(line,0);
				return result;
			}
		};
		inline string next_instruction(int& pc, Creature& fnt, Creature& self);
		
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
			//cout << "Creation\n";
			spec = s;
			//(*spec).print_program();
			dir = d;
		}
		Creature()
		{
			Species spec();
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
		template <std::size_t N, std::size_t M>
		void take_turn(Darwin<N,M>& d, int position, int turn);
		template <std::size_t N, std::size_t M>
		void in_front(Darwin<N,M>& d, int position, Creature& fnt)
		{
			switch(dir)
			{
				case 0:
					if(position-N<0 || position-N > N*M)
						break;
					fnt = d[position-N];
					break;
				case 1:
					if((position+1)/N>position/N || position+1>N*M)
						break;
					fnt = d[position+1];
					break;
				case 2:
					if(position+N>=N*M)
						break;
					fnt = d[position+N];
					break;
				case 3:
					if((position-1)/N<position/N || position-1<0)
						break;
					fnt = d[position-1];
					break;
			}
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
		void next_turn(int turn);
		void request_hop(Creature& c,int dir, int position);
		Creature& operator[](int x)
		{
			return creature_grid[x];
		}
};
