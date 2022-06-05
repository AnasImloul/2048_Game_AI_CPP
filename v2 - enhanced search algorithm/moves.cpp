#include "MoveObjects.cpp"
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



void random_add(long* grid, int rows, int columns){
	
	int value = 2;
	
	int size = rows*columns;
	
	int start = rand()%size;
	
	for (int i = 0; i<size; i++){
		if (grid[(start + i)%size] == 0){ 
			grid[(start + i)%size] = value;
			break;
		}
	}
}
