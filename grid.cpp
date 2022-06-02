#include "dynamic.cpp"
#include "move.cpp"
#include <cstring>
#include <iostream>


typedef Move (*Moves) (long* grid, const int &rows, const int &columns);


int digit(long number){
	int digits = 1;
	while (number >= 10){
		digits++;
		number = number / 10;
	}
	return digits;
}


class Grid{
public:
	int rows;
	int columns;
	
	long* grid;
	
	long score;
	
	int empty_slots;
	
	Moves moves[4] = {Up,Down,Left,Right};
	
	
	Grid(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
		
		grid = (long*) malloc(sizeof(long)*rows*columns);
		memset(grid, 0,sizeof(grid));	
		
		score = 0;
		
		empty_slots = rows*columns;
	}
	
	
	void up(){
		Move move = Up(grid, rows, columns);
		
		empty_slots += move.merged;
		
		grid = move.grid;
		
		score += move.score;
		add();
	}
	
	void down(){
		Move move = Down(grid, rows, columns);
	
		empty_slots += move.merged;
		
		grid = move.grid;
		score += move.score;
		add();
	}
	
	void left(){
		Move move = Left(grid, rows, columns);
		
		empty_slots += move.merged;
		
		grid = move.grid;
		score += move.score;
		add();
	}
	
	void right(){
		Move move = Right(grid, rows, columns);
		
		empty_slots += move.merged;
		
		grid = move.grid;
		score += move.score;
		add();
		
	}
	
	void add(){
		random_add(grid, rows, columns,empty_slots,2);
	}
	
	
	int next_move(int depth){
		
		
		MoveTracker best_move = maxsearch(grid, rows, columns, empty_slots, moves, 4, depth);
		
		std::cout << best_move.path.size() << std::endl;
		
		return best_move.path[1];
	}
	
	
	void play(long rounds, int depth, bool show = false){
		for (int round = 1; round <= rounds; rounds++){
		
			if (show) show_grid(grid,rows,columns);

			int next = next_move(depth);

			Move move = moves[next](grid, rows, columns);

			empty_slots += move.merged;

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
		std::string result = "";
		for (int i = 0; i<g.rows*g.columns; i++){
			result = result + std::to_string(g.grid[i]) + (((i==0 && g.columns != 1) || (i+1)%g.columns) ? " " : "\n");
		}
		result += "Score: " + std::to_string(g.score);
		
		return os << result;
	}
};
