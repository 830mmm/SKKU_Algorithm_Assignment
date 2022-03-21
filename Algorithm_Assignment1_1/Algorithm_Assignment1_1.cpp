#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <queue>

//this function validates input data from input1.txt
bool Is_Valid(int boardsize, int source_pos[2], int dest_pos[2]);
//this function finds the minimum number of steps 
//from the source position to the destination with BFS
int BFS_Queue(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2]);

int main(int argc, char** argv)
{
	FILE* fp_input;
	int board_size = 0;//stores chess board size
	int knight_init_loc[2] = { 0, 0 };// stores start point of knight
	int dest_loc[2] = { 0, 0 }; // stores the coordinate of destination
	int move[8][2] = { {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2} };
	fp_input = fopen(argv[1], "r"); //read only
	//check if the fopen was successfully done
	if (fp_input == NULL) {
		exit(EXIT_FAILURE);
	}
	//receives data from input file
	fscanf(fp_input, "%d", &board_size);
	fscanf(fp_input, "%d %d", &knight_init_loc[0], &knight_init_loc[1]);
	fscanf(fp_input, "%d %d", &dest_loc[0], &dest_loc[1]);

	fclose(fp_input);
	fp_input = nullptr;
	//validate input data
	if (Is_Valid(board_size, knight_init_loc, dest_loc) == false) {
		exit(EXIT_FAILURE);
	}
	//find the shortest path count
	int shortest_path = BFS_Queue(board_size, knight_init_loc, dest_loc, move);

	FILE* fp_output = fopen(argv[2], "w");
	if (fp_output == NULL) {
		exit(EXIT_FAILURE);
	}
	fprintf(fp_output, "%d", shortest_path);
	fclose(fp_output);
	fp_output = nullptr;

	return 0;
}

bool Is_Valid(int boardsize, int source_pos[2], int dest_pos[2])
{
	if (boardsize < 4 || boardsize > 20) {
		return false;
	}
	else if (source_pos[0] < 0 || source_pos[0] >= boardsize || source_pos[1] < 0 || source_pos[1] >= boardsize) {
		return false;
	}
	else if (dest_pos[0] < 0 || dest_pos[1] < 0 || dest_pos[0] >= boardsize || dest_pos[1] >= boardsize) {
		return false;
	}
	else return true;
}

int BFS_Queue(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2])
{
	int path_count = 1; // minimum number of steps
	int visit_pos[2]; // currently visiting position
	int visit_num = 1; // the number of positions visited at each height(path_count)
	std::queue<std::array<int, 2>> to_visit;
	int Iteration_Num = 0;
	to_visit.push({ source_pos[0], source_pos[1] }); // initialize as start point
	while (1)
	{
		visit_pos[0] = to_visit.front()[0];
		visit_pos[1] = to_visit.front()[1];
		to_visit.pop(); // visit then pop!
		for (auto& counter : move) {

			int temp_pos[2] = { visit_pos[0] + counter[0], visit_pos[1] + counter[1] };

			//if finds the destination
			if ((temp_pos[0] == dest_pos[0]) && (temp_pos[1] == dest_pos[1])) {
				return path_count;
			}
			else {
				//check if the coordinate of new position has any negative number
				if (temp_pos[0] < 0 || temp_pos[0] >= board_size || temp_pos[1] < 0 || temp_pos[1] >= board_size) {
					Iteration_Num++;
					continue;
				}
				//push the next position to queue
				to_visit.push({ temp_pos[0], temp_pos[1] });
				Iteration_Num++;
			}
		}
		//If visited all the corresponding positions in queue with respect to height(path_count)
		if (8 * visit_num == Iteration_Num) {
			Iteration_Num = 0;
			visit_num = to_visit.size(); // count the number of to-be-visited positions
			path_count++; // increase the minimum number by 1
		}

	}
	return path_count; // this code will never be executed unless the previous while loop somehow breaks
}