#include<iostream>
#include "grid.cpp"
#include<chrono>
#include "move.cpp"
#include <algorithm>

int64_t get_time(){
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}


int main(){	
	srand(time(0));
	
	Grid grid = Grid(4,4);
	
	int64_t start = get_time();

	grid.play(1'000'000'000, 6, true);

	std::cout << get_time() - start << std::endl;
}
