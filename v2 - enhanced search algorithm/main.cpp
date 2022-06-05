#include<iostream>
#include "grid.cpp"
#include<chrono>
#include <algorithm>

int64_t get_time(){ return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }



int main(){
	srand(time(0));
	
	Grid grid = Grid(4,4);
	
	int64_t start = get_time();
	
	
	//grid.play(rounds, depth, print_grid)
	//depth increase result in better score but lower performance
	grid.play(10'000, true);

	std::cout << "Play time "<< (get_time() - start)/1'000'000.f << " seconds."<< std::endl;
}
