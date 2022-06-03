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



#include<vector>




#ifndef MOVE
#define MOVE

struct Move{

	int merged;
	long score;
	bool blocked;
	long *grid;

	
	
	Move(int merged, long score, bool blocked, long *grid){
		this->merged = merged;
		this->score = score;
		this->blocked = blocked;
		this->grid = grid;
	
	}
	
	int Compare (const Move other) {
		return 
			((merged > other.merged) || (merged == other.merged)&&(score > other.merged)) ? 1:
		
						    (merged == other.merged)&&(score == other.merged) ? 0:
						
												       -1;
	}
	
	
	bool operator == (const Move other) const {
  		return (merged == other.merged)&&(score == other.score);
	}

	bool operator < (const Move other) const {
  		return ((other.merged > merged) || (other.merged == merged)&&(other.score > score));   
	}
	
	bool operator > (const Move other) const {
  		return ((merged > other.merged) || (merged == other.merged)&&(score > other.score));   
	}
};

#endif


#ifndef MOVETRACKER
#define MOVETRACKER


struct MoveTracker{

	int merged = 0;
	long score = 0;
	bool blocked = false;
	long* grid;
	std::vector<int> path;
	
	MoveTracker(long* grid, int merged, long score, bool blocked){
		this->merged = merged;
		this->score = score;
		this->blocked = blocked;
		
		this->grid = grid;

	}
	
	int Compare (const MoveTracker other) {
	
		if (blocked < other.blocked) return 1;
		
		if (blocked == other.blocked){
		
			if (merged > other.merged) return 1;
			
			if (merged == other.merged){
				if (score > other.score) return 1;
				
				if (score == other.score) return 0;
			}
		}
		return -1;
	}
	
	
	bool operator == (const MoveTracker other) const {
  		return (blocked == other.blocked)&&(merged == other.merged)&&(score == other.score);
	}
	

	bool operator < (const MoveTracker other) const {
  		if (blocked > other.blocked) return true;
		
		if (blocked == other.blocked){
		
			if (merged < other.merged) return true;
			
			if (merged == other.merged){
				if (score < other.score) return true;
				
				if (score == other.score) return false;
			}
		}
		return true;
	}
	
	bool operator > (const MoveTracker other) const {
  		if (blocked < other.blocked) return true;
		
		if (blocked == other.blocked){
		
			if (merged > other.merged) return true;
			
			if (merged == other.merged){
				if (score > other.score) return true;
				
				if (score == other.score) return false;
			}
		}
		return false;
	}

};

#endif

#include "move.cpp"
#include<algorithm>
#include<vector>
#include<cstring>
#include<iostream>



typedef Move (*Moves) (long* grid, const int &rows, const int &columns);




Move Up(long* grid, const int &rows, const int &columns){

	//show_grid(grid, rows, columns);
	
	//std::cout << std::endl;


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int col = 0; col < columns; col++){ 
		for (int row = 0; row < rows; row++){
			if (grid[columns * row + col] == 0){
				
				continue;
			}

			int k = row;
			bool merge = true;

			while (k > 0){

				long current = (grid[col + columns * k]);
				long previous = (grid[col + columns * (k - 1)]);

				if (previous == 0){
					
					grid[col + columns * k] = previous;
					grid[col + columns * (k-1)] = current;
					
					blocked = false;
				}

				if (merge and previous == current){
					grid[col + columns * (k-1)] += current;

					score += current * 2;

					grid[col + columns * k] = 0;

					merged += 1;

					blocked = false;

					merge = false;
				}

				k -= 1;
			}
		}
	}

	
	return Move(merged,score,blocked,grid);	
}



Move Down(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int col = 0; col < columns; col++){ 
		for (int row = rows - 1; row >= 0; row--){
			if (grid[columns * row + col] == 0){
				
				continue;
			}

			int k = row;
			bool merge = true;

			while (k < rows - 1){

				long current = (grid[col + columns * k]);
				long previous = (grid[col + columns * (k + 1)]);

				if (previous == 0){
					
					grid[col + columns * k] = previous;
					grid[col + columns * (k+1)] = current;
					
					blocked = false;
				}

				if (merge and previous == current){
					grid[col + columns * (k+1)] += current;

					score += (current << 1);

					grid[col + columns * k] = 0;

					merged += 1;

					blocked = false;

					merge = false;
				}

				k += 1;
			}
		}
	}
	return Move(merged,score,blocked,grid);	
}


Move Left(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int row = 0; row < rows; row++){ 
		for (int col = 0; col < columns; col++){
			if (grid[columns * row + col] == 0){
				
				continue;
			}
			

			int k = col;
			bool merge = true;

			while (k > 0){

				long current = grid[columns * row + k];
				long previous = grid[columns * row + (k-1)];

				if (previous == 0){
					
					grid[columns * row + k] = previous;
					grid[columns * row + (k-1)] = current;
					
					blocked = false;
				}

				if (merge and previous == current){
					grid[columns * row + (k-1)] += current;

					score += (current << 1);

					grid[columns * row + k] = 0;

					merged += 1;

					blocked = false;

					merge = false;
				}

				k -= 1;
			}
		}
	}
	return Move(merged,score,blocked,grid);	
}


Move Right(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int row = 0; row < rows; row++){ 
		for (int col = columns - 1; col >= 0; col--){
			if (grid[columns * row + col] == 0){
				
				continue;
			}

			int k = col;
			bool merge = true;

			while (k < columns - 1){

				long current = grid[columns * row + k];
				long previous = grid[columns * row + (k+1)];
				if (previous == 0){
					
					grid[columns * row + k] = previous;
					grid[columns * row + (k+1)] = current;
					
					blocked = false;
				}

				if (merge and previous == current){
					grid[columns * row + (k+1)] += current;

					score += (current << 1);

					grid[columns * row + k] = 0;

					merged += 1;

					blocked = false;

					merge = false;
				}

				k += 1;
			}
		}
	}
	return Move(merged,score,blocked,grid);	
}



void random_add(long* grid, int rows, int columns, long value){
	
	
	int size = rows*columns;
	
	int start = rand()%size;
	
	for (int i = 0; i<size; i++){
		if (grid[(start + i)%size] == 0){ 
			grid[(start + i)%size] = value;
			break;
		}
	}
}



MoveTracker maxsearch(long *grid, int rows, int columns, Moves* moves, int moves_count, int depth=6){

    long temp_grid[rows*columns];      
    for (int i = 0; i<rows*columns; i++){
	
		temp_grid[i] = grid[i];
	    }
	    
	    
    MoveTracker max_score = MoveTracker(temp_grid, -1, -1, true);
    
    int merged;
    long score;
    bool blocked;
    
    if (depth == 1){
	
        for (int i = 0; i<moves_count; i++){
        	
            long next_grid[rows*columns];
            memset(next_grid, 0, sizeof(next_grid));
           
            for (int i = 0; i<rows*columns; i++){
	
		next_grid[i] = grid[i];
	    }
     
            
            Move next_move = moves[i](next_grid, rows, columns);
            
                             
            MoveTracker move_tracker = MoveTracker(next_grid, next_move.merged, next_move.score, next_move.blocked);
            
            //std::cout << move_tracker.blocked << " " << move_tracker.merged << " " << move_tracker.score << std::endl;
            
            move_tracker.path.push_back(i);
           
            if (move_tracker > max_score) max_score = move_tracker;            
        }
        
        //std::cout << std::endl;
        //std::cout << max_score.blocked << " " << max_score.merged << " " << max_score.score << std::endl;
        //std::cout << std::endl;

   } else {
   	std::vector<MoveTracker> next_states;

    	bool move_blocked = true;
    	
    	
    	
    	for (int i = 0; i<moves_count; i++){
        	
            long next_grid[rows*columns];
            memset(next_grid, 0, sizeof(next_grid));
           
            for (int i = 0; i<rows*columns; i++){
	
		next_grid[i] = grid[i];
	    }
            
            
            Move next_move = moves[i](next_grid, rows, columns);
            
                       
                merged = next_move.merged;
        	score = next_move.score;
        	blocked = next_move.blocked;
        	
        	
        	
        	if (!blocked){
        		move_blocked = false;
        		
        		random_add(next_grid, rows, columns, 2);
        		
          		
        		MoveTracker next_depth = maxsearch(next_grid, rows, columns, moves, moves_count, depth - 1);
        		
        		
        		next_depth.merged += merged;
        		next_depth.score += score;
        		next_depth.blocked = blocked;
        		next_depth.path.push_back(i);
        		
        		if (next_depth > max_score) max_score = next_depth;
        	}
        	
        }
        
        if (move_blocked) max_score.path.push_back(rand()%moves_count);
}

    
    return max_score;   
}
