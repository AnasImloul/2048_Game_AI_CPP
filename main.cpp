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
	
	Grid grid = Grid(5,5);
	
	int64_t start = get_time();
	
	for (int i = 0; i<2;i++){
		grid.add();
	}


	grid.play(1'000'000'000, 6, true);

	std::cout << get_time() - start << std::endl;
}
