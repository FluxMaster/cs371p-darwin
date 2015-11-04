#include "Darwin.h"
#define DEBUG_GRID false

//------------------
// Species Functions
//------------------

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

char Species::render()
{
	return symbol;
}

bool Species::real()
{
	if (name.empty())
		return false;
	return true;
}

//-------------------
// Creature Functions
//-------------------
void Creature::infect_me(Species s)
{
	spec = s;
	pc = 0;
}
char Creature::render()
{
	ostringstream os;
	os << spec;
	string str = os.str();
	const char* chr = str.c_str();
	return chr[0];
}

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

bool Creature::real()
{
	if (spec.real())
		return true;
	return false;
}


//-----------------
// Darwin Functions
//-----------------
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





