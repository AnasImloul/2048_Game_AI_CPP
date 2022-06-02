#include "move.cpp"
#include<algorithm>
#include<vector>
#include<iostream>



typedef Move (*Moves) (long* grid, const int &rows, const int &columns);


void copy(const long* src, long* dest){
	long size = sizeof(src)/sizeof(src[0]);
	for (int i = 0; i<size; i++){
	
		dest[i] = src[i];
	
	}
}



Move Up(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int col = 0; col < columns; col++){ 
		for (int row = 0; row < rows; row++){
			if (grid[columns * row + col] == 0){
				blocked = false;
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

	
	return Move(merged,score,blocked,grid,0);	
}



Move Down(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int col = 0; col < columns; col++){ 
		for (int row = rows - 1; row >= 0; row--){
			if (grid[columns * row + col] == 0){
				blocked = false;
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
	return Move(merged,score,blocked,grid,1);	
}


Move Left(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int row = 0; row < rows; row++){ 
		for (int col = 0; col < columns; col++){
			if (grid[columns * row + col] == 0){
				blocked = false;
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
	return Move(merged,score,blocked,grid,2);	
}


Move Right(long* grid, const int &rows, const int &columns){


	int merged = 0;

	long score = 0;

	bool blocked = true;

	for (int row = 0; row < rows; row++){ 
		for (int col = columns - 1; col >= 0; col--){
			if (grid[columns * row + col] == 0){
				blocked = false;
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
	return Move(merged,score,blocked,grid,3);	
}



void random_add(long* grid, int rows, int columns, int &slots, long value){
	srand(time(0));
	
	if (slots>0){
	
	int size = rows*columns;
	

	
	int* empty_slots = (int*) malloc(slots*sizeof(int));
	
	
	
	int index = 0;
	for (int i = 0; i<size; i++){
		if (grid[i] == 0){ 
			empty_slots[index] = i;
			index++;
		}
	}
	
	
	grid[empty_slots[rand()%slots]] = value;
	
	
	slots -= 1;
	
	
	}
}


MoveTracker maxsearch(long *grid, int rows, int columns, int &slots, Moves* moves, int moves_count, int depth=6){
	
    
    long temp_grid[rows*columns];      
    copy(grid,temp_grid);
    
    MoveTracker max_score = MoveTracker(temp_grid, -1, -1, false);
    
    int merged;
    long score;
    bool blocked;
    
    
    if (depth == 1){
    
	
        for (int i = 0; i<moves_count; i++){
        	
            long next_grid[rows*columns];
           
            copy(grid,next_grid);
            
            Move next_move = moves[i](next_grid, rows, columns);
           
            MoveTracker move_tracker = MoveTracker(next_grid, next_move.merged, next_move.score, next_move.blocked);
            
            move_tracker.path.push_back(i);
           
            max_score = std::max(max_score, move_tracker);
            
        }

   } else {
   
   	std::vector<MoveTracker> next_states;

    	bool move_blocked = false;
    	
    	
    	
    	for (int i = 0; i<moves_count; i++){
        	
            long next_grid[rows*columns];
           
            copy(grid,next_grid);
            
            Move next_move = moves[i](next_grid, rows, columns);
            
            move_blocked = move_blocked || blocked;
           
            MoveTracker move_tracker = MoveTracker(next_grid, next_move.merged, next_move.score, next_move.blocked);
            
            move_tracker.path.push_back(i);
            
            next_states.push_back(move_tracker);
           
        }
        
        
        sort(next_states.begin(), next_states.end(), std::greater<MoveTracker>());
        
        
        if (!move_blocked) next_states.pop_back();
        
        
        
        
        for (const auto &state : next_states){
        	merged = state.merged;
        	score = state.score;
        	blocked = state.blocked;
        	
        	if (!blocked){
        		//random_add(state.grid, rows, columns, slots, 2);
        	
        		MoveTracker next_depth = maxsearch(state.grid, rows, columns, slots, moves, moves_count, depth - 1);
        		
        		next_depth.merged += merged;
        		next_depth.score += score;
        		next_depth.path.push_back(state.path[0]);
        		
        		max_score = std::max(max_score, next_depth);	
        	}
        }
    }
    return max_score;   
}
