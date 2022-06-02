#include<vector>


#ifndef SHOW
#define SHOW

void show_grid(const long *grid, int rows, int columns){
	std::string result = "";
	for (int i = 0; i<rows*columns; i++){
		result = result + std::to_string(grid[i]) + (((i==0 && columns != 1) || (i+1)%columns) ? " " : "\n");
	}
	std::cout << result << std::endl;
}

#endif

#ifndef MOVE
#define MOVE

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
		
		path.push_back(-1);
	}
	
	int Compare (const MoveTracker other) {
		return 
			((merged > other.merged) || (merged == other.merged)&&(score > other.merged)) ? 1:
		
						    (merged == other.merged)&&(score == other.merged) ? 0:
						
												       -1;
	}
	
	
	bool operator == (const MoveTracker other) const {
  		return (merged == other.merged)&&(score == other.score);
	}

	bool operator < (const MoveTracker other) const {
  		return ((other.merged > merged) || (other.merged == merged)&&(other.score > score));   
	}
	
	bool operator > (const MoveTracker other) const {
  		return ((merged > other.merged) || (merged == other.merged)&&(score > other.score));   
	}

};

#endif
