#include<stdio.h>

struct Move{

	int merged;
	long score;
	bool blocked;
	long *grid;
	int index;
	
	Move(int merged, long score, bool blocked, long *grid, int index){
		this->merged = merged;
		this->score = score;
		this->blocked = blocked;
		this->grid = grid;
		this->index = index;
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


Move up(long* grid, const int &rows, const int &columns){


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

					score += (current << 1);

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



Move down(long* grid, const int &rows, const int &columns){


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
	return Move(merged,score,blocked,grid,0);	
}


Move left(long* grid, const int &rows, const int &columns){


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
	return Move(merged,score,blocked,grid,0);	
}


Move right(long* grid, const int &rows, const int &columns){


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
	return Move(merged,score,blocked,grid,0);	
}



