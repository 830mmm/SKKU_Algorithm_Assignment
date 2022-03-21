#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <queue>

//this function validates input data from input1.txt
bool Is_Valid(int boardsize, int source_pos[2], int dest_pos[2]);
//this function finds the minimum number of steps 
//from the source position to the destination recursively 
int Find_Shortest_Path(int board_size, int source_pos[2], int dest_pos[2], int (&move)[8][2], std::vector<std::vector<bool>> v_board);
int BFS(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2], std::vector<std::vector<bool>>& v_board);
int BFS_Queue(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2]);
int main(int argc, char** argv)
{
	FILE* fp_input;
	int board_size = 0;//stores chess board size
	int knight_init_loc[2] = { 0, 0 };// stores start point of knight
	int dest_loc[2] = { 0, 0 }; // stores the coordinate of destination
	//std::vector<int> mov[8] = { {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2} };
	int move[8][2] = { {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2} };
	fp_input = fopen(argv[1], "r");
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
	//create new matrix (board_size) * (board_size)
	//and initialize the matrix as false(=not visited)
	std::vector<std::vector<bool>> v_board( board_size, std::vector<bool>(board_size, false) );
	v_board[knight_init_loc[0]][knight_init_loc[1]] = true;
	//find the shortest path count
	//int shortest_path = Find_Shortest_Path(board_size, knight_init_loc, dest_loc, move, v_board);
	//int shortest_path = BFS(board_size, knight_init_loc, dest_loc, move, v_board);
	int shortest_path = BFS_Queue(board_size, knight_init_loc, dest_loc, move);
#if 1
	printf("Minimum number of steps : %d", shortest_path);
#endif
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

int Find_Shortest_Path(int board_size, int source_pos[2], int dest_pos[2], int (&move)[8][2], std::vector<std::vector<bool>> v_board)
{
	int path_num = 0;
	//check if the knight can reach the destination
	for (auto& counter : move) {
		if ( ( source_pos[0] + counter[0] == dest_pos[0] ) && ( source_pos[1] + counter[1] == dest_pos[1] ) ) {
			return ++path_num; // return 1
		}
	}

	for (auto& counter : move) {
		int new_source_pos[2] = { source_pos[0] + counter[0], source_pos[1] + counter[1] };
		//check if the coordinate of new position has any negative number
		if (new_source_pos[0] < 0 || new_source_pos[0] >= board_size || new_source_pos[1] < 0 || new_source_pos[1] >= board_size) {
			continue;
		}
		//check if the location is visited or not
		else if (v_board[new_source_pos[0]][new_source_pos[1]] == true) {
			continue;
		}
		v_board[new_source_pos[0]][new_source_pos[1]] = true;
		int temp = Find_Shortest_Path(board_size, new_source_pos, dest_pos, move, v_board);
		v_board[new_source_pos[0]][new_source_pos[1]] = false;
		if ( temp > 0 ) {
			path_num += temp;
			return path_num + 1;
		}
	}

	return -1;
}

int BFS(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2], std::vector<std::vector<bool>>& v_board)
{
	int path_count = 1;
	int visit_pos[2];
	int visit_num = 1;
	std::vector<std::array<int,2>> to_visit;
	int Iteration_Num = 0;
	to_visit.push_back({ source_pos[0], source_pos[1] });
	while (1)
	{
		visit_pos[0] = to_visit[0][0];
		visit_pos[1] = to_visit[0][1];
		to_visit.erase(to_visit.begin());
		for (auto& counter : move) {
			
			int temp_pos[2] = { visit_pos[0] + counter[0], visit_pos[1] + counter[1] };
			
			//finds the destination
			if ((temp_pos[0] == dest_pos[0]) && (temp_pos[1] == dest_pos[1])) {
#if 1
				std::cout << "destination : (" << temp_pos[0] << " " << temp_pos[1] << ")" << std::endl;
#endif
				return path_count;
			}
			else {
				//check if the coordinate of new position has any negative number
				if (temp_pos[0] < 0 || temp_pos[0] >= board_size || temp_pos[1] < 0 || temp_pos[1] >= board_size) {
					Iteration_Num++;
					continue;
				}
				to_visit.push_back({ temp_pos[0], temp_pos[1] });
				Iteration_Num++;
			}
		}
		if ( 8 * visit_num == Iteration_Num) {
			Iteration_Num = 0;
			visit_num = to_visit.size();
			path_count++;
		}
		
	}
	return path_count;
}
int BFS_Queue(int board_size, int source_pos[2], int dest_pos[2], int(&move)[8][2])
{
	int path_count = 1;
	int visit_pos[2];
	int visit_num = 1;
	std::queue<std::array<int, 2>> to_visit;
	int Iteration_Num = 0;
	to_visit.push({ source_pos[0], source_pos[1] });
	while (1)
	{
		visit_pos[0] = to_visit.front()[0];
		visit_pos[1] = to_visit.front()[1];
		to_visit.pop();
		for (auto& counter : move) {

			int temp_pos[2] = { visit_pos[0] + counter[0], visit_pos[1] + counter[1] };

			//finds the destination
			if ((temp_pos[0] == dest_pos[0]) && (temp_pos[1] == dest_pos[1])) {
#if 1
				std::cout << "destination : (" << temp_pos[0] << " " << temp_pos[1] << ")" << std::endl;
#endif
				return path_count;
			}
			else {
				//check if the coordinate of new position has any negative number
				if (temp_pos[0] < 0 || temp_pos[0] >= board_size || temp_pos[1] < 0 || temp_pos[1] >= board_size) {
					Iteration_Num++;
					continue;
				}
				to_visit.push({ temp_pos[0], temp_pos[1] });
				Iteration_Num++;
			}
		}
		if (8 * visit_num == Iteration_Num) {
			Iteration_Num = 0;
			visit_num = to_visit.size();
			path_count++;
		}

	}
	return path_count;
}