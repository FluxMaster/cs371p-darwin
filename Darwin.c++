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
