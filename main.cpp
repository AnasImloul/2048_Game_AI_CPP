#include<iostream>
#include "move.cpp"
#include <vector>
#include<chrono>

int64_t get_time(){
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}


int digit(long number){
	int digits = 1;
	while (number >= 10){
		digits++;
		number = number / 10;
	}
	return digits;
}



void show(long* grid, int rows, int columns){
        for (int i = 0; i<rows*columns; i++){
        	std::cout << grid[i] << (((i==0 && columns != 1) || (i+1)%columns) ? " " : "\n");
       }
}

int main(){

	std::vector<Move> arr;
	
	long grid[16] = {2,0,2,0,2,0,2,0,2,0,2,0,2,4,8,8};
	
	show(grid, 4,4);
	
	int64_t start = get_time();
	
	for (int i = 0; i<10'000'000; i++){
	Move move = left(grid,4,4);
	}
	
	std::cout << get_time() - start << std::endl;
	
	//arr.push_back(Move(0,1013,false,grid,0));
	
	//show(move.grid, 4,4);
	
	
		

}
