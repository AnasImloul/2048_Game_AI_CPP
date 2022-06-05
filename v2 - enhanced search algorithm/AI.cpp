#include "MoveObjects.cpp"
#include<algorithm>
#include<vector>
#include<cstring>
#include<iostream>


void insert(Move* moves,int moves_count, Move move){
    int i = moves_count - 1;
    moves[i] = move;

    while(i > 0){
        if (moves[i] > moves[i - 1]){ 
        	Move temp_move = moves[i];
        	moves[i] = moves[i-1];
        	moves[i-1] = temp_move;
        }
        i -= 1;
    }
}


MoveTracker maxsearch(long *grid, int rows, int columns, Moves* moves, int moves_count, int depth=6){
	    
    MoveTracker max_score = MoveTracker(grid, -1, -1, true);

   
    depth = (depth >= 1 ? depth : 1);
    
    if (depth == 1){
	
        for (int i = 0; i<moves_count; i++){
        	
            //create a copy of grid to not overwrite the original grid
            long next_grid[rows*columns];
            for (int i = 0; i<rows*columns; i++) next_grid[i] = grid[i];
 
            
            Move next_move = moves[i](next_grid, rows, columns);
                             
            MoveTracker move_tracker = MoveTracker(next_grid, next_move.merged, next_move.score, next_move.blocked);
            
            move_tracker.path.push_back(i);
           
            if (move_tracker > max_score) max_score = move_tracker;            
        }
        

   } else {
    	bool move_blocked = true;  	
    	
    	for (int i = 0; i<moves_count; i++){
        	
            //create a copy of grid to not overwrite the original grid
            long next_grid[rows*columns];
            for (int i = 0; i<rows*columns; i++) next_grid[i] = grid[i];
            
            Move next_move = moves[i](next_grid, rows, columns);

        	
        	
        	if (!next_move.blocked){
        		move_blocked = false;
        		
        		random_add(next_grid, rows, columns);
        		
        		MoveTracker next_depth = maxsearch(next_grid, rows, columns, moves, moves_count, depth - 1);
        		
        		next_depth.merged += next_move.merged;
        		next_depth.score += next_move.score;
        		next_depth.blocked = next_move.blocked;
        		next_depth.path.push_back(i);
        		
        		if (next_depth > max_score) max_score = next_depth;
        	}
        }
        
        
       
        if (move_blocked) max_score.path.push_back(rand()%moves_count);
}

    
    return max_score;   
}
