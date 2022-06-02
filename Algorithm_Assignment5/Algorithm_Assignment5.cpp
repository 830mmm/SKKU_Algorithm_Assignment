#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

int find_smallest(vector< pair< pair<int, int>, pair<int, int> > >& vec)
{
	int in_degree = 1000000;
	int index = -2;
	int length = vec.size();

	for (int i = 0; i < length; i++)
	{
		if (in_degree > vec[i].first.first && vec[i].first.first >= 0) {
			in_degree = vec[i].first.first;
			index = i;
		}
	}

	if (index == -2) {
		return -2;
	}
	return index;
}

void critical_path(char** argv)
{
	FILE* input = fopen(argv[1], "r");
	if (input == NULL)
		exit(EXIT_FAILURE);
	int N, M;
	fscanf(input, "%d", &N);
	fscanf(input, "%d", &M);

	vector<pair< pair<int, int>, pair<int, int> >> task_degree; // in-degree, task time, prev, critical time
	vector<int>* adjacency_list = new vector<int>[N + 1];

	int degree = 0;
	int index = 0, dependency = 0;

	for (int i = 0; i < N; i++)
	{
		fscanf(input, "%d", &degree);
		task_degree.push_back(make_pair(make_pair(0, degree), make_pair(0, 0)));
	}
	for (int i = 0; i < M; i++)
	{
		fscanf(input, "%d %d", &index, &dependency);
		if (task_degree[dependency - 1].first.first < task_degree[index - 1].first.first + 1)
			task_degree[dependency - 1].first.first = task_degree[index - 1].first.first + 1;
		adjacency_list[index].push_back(dependency);
	}
	// can be omitted
	/*for (int i = 1; i <= N; i++) 
	{
		for (auto& j : adjacency_list[i])
		{
			if (task_degree[i - 1].first.first >= task_degree[j - 1].first.first) {
				task_degree[j - 1].first.first = task_degree[i - 1].first.first + 1;
			}
		}
	}*/
	fclose(input);

	queue<int> topo_list;

	int smallest = find_smallest(task_degree);
	while (topo_list.size() != N && smallest != -2)
	{
		topo_list.push(smallest + 1);

		// critical time
		task_degree[smallest].second.second += task_degree[smallest].first.second;
		

		for (auto& i : adjacency_list[smallest + 1])
		{
			task_degree[i-1].first.first--;
			if (task_degree[smallest].second.second > task_degree[i-1].second.second) {
				task_degree[i-1].second.second = task_degree[smallest].second.second;
			}
			task_degree[i-1].second.first = smallest + 1;
		}

		task_degree[smallest].first.first = -1;

		smallest = find_smallest(task_degree);
	}
	

	
	FILE* output = fopen(argv[2], "w");
	if (!output)
		exit(EXIT_FAILURE);
	fprintf(output, "%d", task_degree[topo_list.back()-1].second.second);
	fclose(output);
	
	delete[] adjacency_list;
}




int main(int args, char** argv)
{
	if (args != 3)
		exit(EXIT_FAILURE);
	critical_path(argv);

	return 0;
}