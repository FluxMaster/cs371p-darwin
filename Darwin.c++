#include "Darwin.h"
#define DEBUG_GRID false

//------------------
// Species Functions
//------------------
/**
 * This determines a creature's next instruction
 * returns a string of the next instruction
 * @param pc The Program Counter
 * @param fnt The Creature in front of the Creature that needs next instruction
 * @return self The Creature who needs next instruction
**/
string Species::next_instruction(int& pc, Creature& fnt, Creature& self)
{
	ostringstream os;
	os << fnt;
	string str = os.str();
	const char* chr = str.c_str();
	while(true)
	{
		pair<string,int> line = parse_line(program[pc]);
		//cout << get<0>(line) << " " << get<1>(line) << endl;
		if(strcmp(get<0>(line).c_str(), "if_empty")==0)
		{
			if(!fnt.real())
				pc = get<1>(line);
			else
				pc++;
		}
		else if(strcmp(get<0>(line).c_str(), "if_wall")==0)
		{
			if(chr[0] == 'w')
				pc = get<1>(line);
			else
				pc++;
		}
		else if(strcmp(get<0>(line).c_str(), "if_random")==0)
		{
			if(rand()%2 == 1)
				pc = get<1>(line);
			else
				pc++;
		}
		else if(strcmp(get<0>(line).c_str(), "if_enemy")==0)
		{
			if(fnt.real() && chr[0] != 'w' && fnt!=self)
				pc = get<1>(line);
			else
				pc++;
		}
		else if(strcmp(get<0>(line).c_str(), "go")==0)
		{
			//cout << "go :" << get<1>(line) << endl;
			pc = get<1>(line);
		}
		else
		{
			pc++;
			return get<0>(line);
		}
	}
	return NULL;
}

/**
 * This parses the command into a pair of <instruction,line number>
 * returns a pair<string,int>
 * @param line a command to be parsed
**/
pair<string,int> Species::parse_line(string line)
{
	int space = line.find(' ',0);
	string command(line.substr(0,space));
	if(strcmp(command.c_str(), "if_empty")==0)
	{
		string lnum = line.substr(space+1);
		int num = stoi(lnum);
		pair<string,int> result(command,num);
		return result;
	}
	else if(strcmp(command.c_str(), "if_wall")==0)
	{
		string lnum = line.substr(space+1);
		int num = stoi(lnum);
		pair<string,int> result(command,num);				
		return result;
	}
	else if(strcmp(command.c_str(), "if_random")==0)
	{
		string lnum = line.substr(space+1);
		int num = stoi(lnum);
		pair<string,int> result(command,num);
		return result;
	}
	else if(strcmp(command.c_str(), "if_enemy")==0)
	{
		string lnum = line.substr(space+1);
		int num = stoi(lnum);
		pair<string,int> result(command,num);
		return result;
	}
	else if(strcmp(command.c_str(), "go")==0)
	{
		string lnum = line.substr(space+1);
		int num = stoi(lnum);
		pair<string,int> result(command,num);
		return result;
	}
	else
	{
		pair<string,int> result(line,0);
		return result;
	}
}
/**
 * This determines what character to print out
 * returns a char representing the species
**/
char Species::render()
{
	return symbol;
}

/**
 * This determines if this species is not a "null" construction
 * returns a bool true: constructed false: "null" constructed
**/
bool Species::real()
{
	if (name.empty())
		return false;
	return true;
}
/**
 * This adds an instruction to the program of species
 * @param inst A string containing the instruction to be added
**/
void Species::add_instruction(string inst)
{
	program.push_back(inst);
}

//-------------------
// Creature Functions
//-------------------
/**
 * This is how Darwin infects creatures
 * @param s The species to become
**/
void Creature::infect_me(Species s)
{
	spec = s;
	pc = 0;
}

/**
 * This determines what character to print out
 * returns a char representing the creature
**/
char Creature::render()
{
	ostringstream os;
	os << spec;
	string str = os.str();
	const char* chr = str.c_str();
	return chr[0];
}

/**
 * This is how Darwin requests creatures take their turn
 * @param d A reference to a Darwin object for communication
 * @param position An int that represents where this Creature is
 * @return turn An int telling which turn it is, so creatures don't take multiple turns in one turn
**/
template <std::size_t N, std::size_t M>
void Creature::take_turn(Darwin<N,M>& d, int position, int turn)
{	
	if(turn <= turntaken)
		return;
	turntaken++;
	Species Wall({},'w',"Wall");
	Creature fnt(Wall,0);
	in_front(d,position,fnt);
	string inst = (spec).next_instruction(pc,fnt,(*this));
	
	ostringstream os;
	os << fnt;
	string str = os.str();
	const char* chr = str.c_str();
	
	if(strcmp(inst.c_str(), "left")==0)
	{
		dir--;
		if(dir<0)
			dir+=4;
		dir%=4;
	}
	else if(strcmp(inst.c_str(), "right")==0)
	{
		dir++;
		if(dir<0)
			dir+=4;
		dir%=4;
	}
	else if(strcmp(inst.c_str(), "hop")==0)
	{
		if(!fnt.real())
		{
			d.request_hop((*this),dir,position);
		}
	}
	else if(strcmp(inst.c_str(), "infect")==0)
	{
		if(fnt.real() && chr[0]!='w')
		{
			d.request_infect(fnt,spec,dir,position);
		}
	}
}

/**
 * This determines what is in front of the creature
 * Sets fnt to what is in front
 * @param d A reference to a Darwin object for communication
 * @param position An int that represents where this Creature is
 * @return fnt A reference to a creature that represents what is in front of the curent creature
**/
template <std::size_t N, std::size_t M>
void Creature::in_front(Darwin<N,M>& d, int position, Creature& fnt)
{
	switch(dir)
	{
		case 0:
			if(position-M<0 || position-M > N*M)
				break;
			fnt = d[position-M];
			break;
		case 1:
			if((position+1)%M == 0 || position+1>N*M)
			{
				break;
			}
			fnt = d[position+1];
			break;
		case 2:
			if(position+M>=N*M)
				break;
			fnt = d[position+N];
			break;
		case 3:
			if((position-1)/M<position/M || position-1<0)
				break;
			fnt = d[position-1];
			break;
	}
}

/**
 * This determines is the creature is "null" constructed
 * returns a bool true: constructed false: "null" constructed
**/
bool Creature::real()
{
	if (spec.real())
		return true;
	return false;
}


//-----------------
// Darwin Functions
//-----------------
/**
 * This displays the grid
**/
template <std::size_t N, std::size_t M>
void Darwin<N,M>::print_grid()
{
	#if DEBUG_GRID
	for(int i = 0; i < size; i++)
	{
		printf("Absolute spot %d is %c\n",i,symbol_grid[i]);
	}
	#endif
	
	printf(" ");
	for(int i = 0; i < M; i++)
	{
		int mod = i % 10;
		printf("%d",mod);
	}
	printf("\n");
	for(int i = 0; i < N; i++)
	{
		int mod = i % 10;
		printf("%d",mod);
		for(int j = 0; j < M; j++)
		{
			printf("%c",symbol_grid[(i*M)+j]);
		}
		printf("\n");
	}
}

/**
 * This returns the grid as a string for debugging and testing (no numbers either)
 * returns a string, the grid
**/
template <std::size_t N, std::size_t M>
string Darwin<N,M>::debug_grid()
{
	string str;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			str = str + symbol_grid[(i*M)+j];
		}
		str = str + "\n";
	}
	return str;
}

/**
 * This adds a Creature to the Darwin's Creature and Symbol grids
 * @param c A Creature to add
 * @param location An int that represents where to add it
**/
template <std::size_t N, std::size_t M>
void Darwin<N,M>::add_creature(Creature c, int location)
{
	creature_grid[location] = c;
	
	ostringstream os;
	os << c;
	string str = os.str();
	const char* chr = str.c_str();
	symbol_grid[location] = chr[0];
}

/**
 * This tells all the creatures to take their next turn
 * @param turn An int that signifies which turn this is
**/
template <std::size_t N, std::size_t M>
void Darwin<N,M>::next_turn(int turn)
{
	for(int i = 0; i < N*M; i++)
	{
		if((*this)[i].real())
		{	
			try
			{
				((*this)[i]).take_turn((*this), i, turn);
			}
			catch(std::bad_alloc& ba)
			{
				cerr << "bad_alloc caught: " << ba.what() << "\n";
			}
		}
	}
}

/**
 * This lets a Creature request to move forward and moves it forward
 * @param c A Creature that wants to hop
 * @param dir An int that represents which direction to hop it
 * @return int position An int that represents where Creature c is
**/
template <std::size_t N, std::size_t M>
void Darwin<N,M>::request_hop(Creature& c,int dir, int position)
{	
	ostringstream os;
	os << c;
	string str = os.str();
	const char* chr = str.c_str();
	switch(dir)
	{
		case 0:
			creature_grid[position-M] = c;
			symbol_grid[position-M] = chr[0]; 
			break;
		case 1:
			creature_grid[position+1] = c;
			symbol_grid[position+1] = chr[0]; 
			break;
		case 2:
			creature_grid[position+M] = c;
			symbol_grid[position+M] = chr[0]; 
			break;
		case 3:
			creature_grid[position-1] = c;
			symbol_grid[position-1] = chr[0]; 
			break;
	}
	
	creature_grid[position] = Creature();
	symbol_grid[position]='.';
	
	
}

/**
 * This lets a Creature request to infect and infects the creature c
 * @param c A Creature that wants to be infected
 * @param s A Species that c turns into
 * @param dir An int that represents which direction c faces
 * @return int position An int that represents where Creature c is
**/
template <std::size_t N, std::size_t M>
void Darwin<N,M>::request_infect(Creature& c, Species s, int dir, int pos)
{
	c.infect_me(s);
	ostringstream os;
	os << c;
	string str = os.str();
	const char* chr = str.c_str();
	switch(dir)
	{
		case 0:
			creature_grid[pos-M] = c;
			symbol_grid[pos-M] = chr[0];
			break;
		case 1:
			creature_grid[pos+1] = c;
			symbol_grid[pos+1] = chr[0];
			break;
		case 2:
			creature_grid[pos+M] = c;
			symbol_grid[pos+M] = chr[0];
			break;
		case 3:
			creature_grid[pos-1] = c;
			symbol_grid[pos-1] = chr[0];
			break;
	}
}





