#include<iostream>
#include "grid.cpp"
#include<chrono>
#include "move.cpp"
#include <algorithm>

int64_t get_time(){
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}


int main(){	
	Grid grid = Grid(4,4);
	
	int64_t start = get_time();
	
	for (int i = 0; i<20;i++){
		grid.add();
	}
	
	
	grid.up();
	
	grid.left();
	
	//grid.play(1,4,true);
	
	
	MoveTracker best_move = maxsearch(grid.grid, grid.rows, grid.columns, grid.empty_slots, grid.moves, 4,10);
	
	
		
	std::cout << best_move.path.size() << std::endl;
	
	std::cout << get_time() - start << std::endl;
}
