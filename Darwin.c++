#include "Darwin.h"
#define DEBUG_GRID FALSE




template <std::size_t N, std::size_t M>
void Darwin<N,M>::print_grid()
{
	#if DEBUG_GRID
	for(int i = 0; i < size; i++)
	{
		printf("Absolute spot %d is %c\n",i,symbol_grid[i]);
	}
	#endif
	
	//Actual Code
	printf(" ");
	for(int j = 0; j < M; j++)
	{
		int mod = j % 10;
		printf("%d",mod);
	}
	printf("\n");
	for(int i = 0; i < N; i++)
	{
		int mod = i % 10;
		printf("%d",mod);
		for(int j = 0; j < M; j++)
		{
			printf("%c",symbol_grid[(i*N)+j]);
		}
		printf("\n");
	}
}

template <std::size_t N, std::size_t M>
void Darwin<N,M>::add_creature(Creature c, int location)
{
	
	//int n = location / N;
	//int m = location % N;
	//printf("Location: %d n: %d m: %d \n",location,n,m);
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
	//(*this)[0].print_program();
	for(int i = 0; i < N*M; i++)
	{
		if((*this)[i].real())
		{	
			try
			{
				//cout << "My turn: " << ((*this)[i]).render() << endl;
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
			creature_grid[position-N] = c;
			symbol_grid[position-N] = chr[0]; 
			break;
		case 1:
			creature_grid[position+1] = c;
			symbol_grid[position+1] = chr[0]; 
			break;
		case 2:
			creature_grid[position+N] = c;
			symbol_grid[position+N] = chr[0]; 
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
void Creature::take_turn(Darwin<N,M>& d, int position, int turn)
{	
	if(turn <= turntaken)
		return;
	turntaken++;
	Species Wall({},'w',"Wall");
	Creature fnt(Wall,0);
	in_front(d,position,fnt);
	string inst = (spec).next_instruction(pc,fnt,(*this));
	if(strcmp(inst.c_str(), "left")==0)
	{
		dir--;
		if(dir<0)
			dir+=4;
		dir%=4;
		//cout << dir << endl;
	}
	else if(strcmp(inst.c_str(), "right")==0)
	{
		dir++;
		if(dir<0)
			dir+=4;
		dir%=4;
		//cout << dir << endl;
	}
	else if(strcmp(inst.c_str(), "hop")==0)
	{
		if(!fnt.real())
		{
			//cout << "request_hop() for: " << (*this) << " (" << this << ") " << endl;
			d.request_hop((*this),dir,position);
		}
	}
	else if(strcmp(inst.c_str(), "infect")==0)
	{
		//request infect
	}
}


string Species::next_instruction(int& pc, Creature& fnt, Creature& self)
{
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
			if(fnt.render() == 'w')
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
			if(fnt.real() && fnt!=self)
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