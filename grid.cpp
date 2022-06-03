#include "dynamic.cpp"
#include "move.cpp"
#include <cstring>
#include <iostream>
#include <stdlib.h> 
#include<vector>
#include<string>



typedef Move (*Moves) (long* grid, const int &rows, const int &columns);



int digit(long number){
	int digits = 1;
	while (number >= 10){
		digits++;
		number = number / 10;
	}
	return digits;
}

int max_digits(long* grid, int rows, int columns){
	int size = rows*columns;

	int digits = 0;
	for (int i = 0; i<size; i++){
	
		if (digit(grid[i]) > digits) digits = digit(grid[i]);
	}
	return digits;
}


std::string white_spaces(int n){
	std::string s = "";
	for (int i=0;i<n;i++) s += ' ';
	return s;
}


void show_vector(std::vector<int> path){
	for (auto i: path) std::cout << i << ' ';
	
	std::cout << std::endl;
}


void show_grid(long *grid, int rows, int columns){

	int max_digit = max_digits(grid, rows, columns);

	std::string result = "";
	for (int i = 0; i<rows*columns; i++){
		result = result + std::to_string(grid[i]) + white_spaces(max_digit - digit(grid[i])) + (((i==0 && columns != 1) || (i+1)%columns) ? " " : "\n");
	}

	std::cout << result;
}


class Grid{
public:
	int rows;
	int columns;
	
	long* grid;
	
	long score;
	
	Moves moves[4] = {Up,Down,Left,Right};
	
	
	Grid(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
		
		grid = (long*) malloc(sizeof(long)*rows*columns);
		memset(grid, 0,sizeof(grid));	
		
		score = 0;
	}
	
	
	void up(){
		Move move = Up(grid, rows, columns);
		
		grid = move.grid;
		
		score += move.score;
		add();
	}
	
	void down(){
		Move move = Down(grid, rows, columns);
	
		
		
		grid = move.grid;
		score += move.score;
		add();
	}
	
	void left(){
		Move move = Left(grid, rows, columns);
		
		
		grid = move.grid;
		score += move.score;
		add();
	}
	
	void right(){
		Move move = Right(grid, rows, columns);
		
		
		
		grid = move.grid;
		score += move.score;
		add();
		
	}
	
	void add(){
		random_add(grid, rows, columns,2);
	}
	
	
	int next_move(int depth){

	
	MoveTracker best_move = maxsearch(grid, rows, columns, moves, 4, depth);

	return best_move.path[best_move.path.size() - 1]; }
	
	
	void play(long rounds, int depth, bool show = false){
		for (int round = 1; round <= rounds; round++){
		
			if (show){
				show_grid(grid,rows,columns);
				std::cout << "Score: " << score << "\n\n";
				}

			int next = next_move(depth);

			Move move = moves[next](grid, rows, columns);
			

			grid = move.grid;
			score += move.score;

			if (move.blocked){
				std::cout << "Reached a total score of " << score << " after playing " << std::to_string(round) << " rounds." << std::endl;
				break;
			}

			add();
		}
	}
	
	
	private:
	friend std::ostream& operator<<(std::ostream& os, const Grid& g){
		int max_digit = max_digits(g.grid, g.rows, g.columns);
		
		std::string result = "";
		for (int i = 0; i<g.rows*g.columns; i++){
			result = result + std::to_string(g.grid[i]) + white_spaces(2 + max_digit - digit(g.grid[i])) + (((i==0 && g.columns != 1) || (i+1)%g.columns) ? " " : "\n");
		}
		result += "Score: " + std::to_string(g.score);
		
		return os << result;
	}
};
