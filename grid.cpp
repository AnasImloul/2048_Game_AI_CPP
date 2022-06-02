#include "move.cpp"
#include <cstring>

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
	int rows;
	int columns;
	
	long* grid;
	
	long score;
	
	Moves moves[4] = {up,down,left,right};
	
	public:
	Grid(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
		
		this->grid = (long*) malloc(sizeof(long)*4*4);	
		
		score = 0;
	}
	
	
	void Up(){
		Move move = up(grid, rows, columns);
		
		this->grid = move.grid;
		score += move.score;
	}
	
	void Down(){
		Move move = down(grid, rows, columns);
		
		this->grid = move.grid;
		score += move.score;
	}
	
	void Left(){
		Move move = left(grid, rows, columns);
		
		this->grid = move.grid;
		score += move.score;
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
