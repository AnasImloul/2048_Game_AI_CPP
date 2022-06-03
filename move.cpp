#include<vector>


#ifndef SHOW
#define SHOW

void show_grid(const long *grid, int rows, int columns){
	std::string result = "";
	for (int i = 0; i<rows*columns; i++){
		result = result + std::to_string(grid[i]) + (((i==0 && columns != 1) || (i+1)%columns) ? " " : "\n");
	}
	std::cout << result;
}

#endif

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
