#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <algorithm> // fill

template <std::size_t N, std::size_t M>
class Darwin
{
	private:
		char grid[N*M];
		int size;
	public:
		Darwin()
		{ 
			std::fill(&grid[0], &grid[N*M],'.'); 
			size = N*M;
		};
		void print_grid();
};