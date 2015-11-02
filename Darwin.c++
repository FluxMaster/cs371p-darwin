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
