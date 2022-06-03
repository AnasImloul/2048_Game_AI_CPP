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
            
            move_blocked = move_blocked && blocked;
                       
                merged = next_move.merged;
        	score = next_move.score;
        	blocked = next_move.blocked;
        	
        	
        	
        	if (!blocked){
        		
        		random_add(next_grid, rows, columns, 2);
        		
          		
        		MoveTracker next_depth = maxsearch(next_grid, rows, columns, moves, moves_count, depth - 1);
        		
        		
        		next_depth.merged += merged;
        		next_depth.score += score;
        		next_depth.blocked = blocked;
        		next_depth.path.push_back(i);
        		
        		if (next_depth > max_score) max_score = next_depth;
        	}
        	
        }
        if (move_blocked){max_score.path.push_back(rand()%moves_count);}
    }

    
    return max_score;   
}
