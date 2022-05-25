#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
class Graph2
{
private:
	int n_vertex;
	int n_edge;
	// int* op_given;

	std::vector< pair<int, T> > *sets;

public:
	Graph2() {};
	Graph2(const char* filename)
	{
		FILE* input_p = fopen(filename, "r");
		if (input_p == nullptr)
			exit(EXIT_FAILURE);
		fscanf(input_p, "%d", &n_vertex);
		fscanf(input_p, "%d", &n_edge);
		// op_given = new int[n_op];
		sets = new std::vector< pair<int, T> >[n_edge];

		for (int i = 0; i < n_edge; i++)
		{
			int weight;
			int vertex1, vertex2;
			fscanf(input_p, "%d", &vertex1);
			fscanf(input_p, "%d", &vertex2);
			fscanf(input_p, "%d", &weight);
			vertex1--;
			vertex2--;
			sets[vertex1].push_back(make_pair(vertex2, (T)weight));
			sets[vertex2].push_back(make_pair(vertex1, (T)weight));
		}

		fclose(input_p);
	}
	~Graph2()
	{
		// delete[] op_given;
		delete[] sets;
	}

	int getNVertex()
	{
		return n_vertex;
	}
	int getNOP()
	{
		return n_edge;
	}
	vector<pair<int, T>>* getSet()
	{
		return sets;
	}
};

template<class T>
class Disjoint_Set2
{
private:
	int n;
	int* parent;
	int* height;
public:
	Disjoint_Set2() {}
	Disjoint_Set2(int n)
	{
		this->n = n;
		parent = new int[n];
		height = new int[n];
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
			height[i] = 0;
		}
	}
	~Disjoint_Set2()
	{
		delete[] parent;
		delete[] height;
	}

	int Find_Disjoint_Set(int _ele)
	{
		while (parent[_ele] != _ele)
		{
			_ele = parent[_ele];
		}
		return _ele;
	}

	bool Union_DisJoint_Set(int _x, int _y)
	{
		_x = Find_Disjoint_Set(_x);
		_y = Find_Disjoint_Set(_y);

		if (_x == _y)
			return false;
		if (height[_x] == height[_y]) {
			parent[_x] = _y;
			height[_y]++;
		}
		else if (height[_x] > height[_y]) {
			parent[_y] = _x;
		}
		else if (height[_x] < height[_y]) {
			parent[_x] = _y;
		}
		return true;
	}

	void writeAnswer(Graph2<T>& _g, char* output_File)
	{
		FILE* output_file_p = fopen(output_File, "w");
		if (output_file_p == nullptr)
			exit(EXIT_FAILURE);
		int g_n_op = _g.getNOP();
		int* g_op_given = _g.getOPGiven();
		std::vector< pair<int, T> > set = _g.getSet();

		for (int i = 0; i < g_n_op; i++) {
			switch (g_op_given[i])
			{
			case 0:
				Union_DisJoint_Set(set[i].first, set[i].second);
				break;
			case 1:
				if (this->Find_Disjoint_Set(set[i].first) == this->Find_Disjoint_Set(set[i].second)) {
					fprintf(output_file_p, "Y\n");
				}
				else {
					fprintf(output_file_p, "N\n");
				}
				break;
			default:
				break;
			}
		}

		fclose(output_file_p);
	}
};

template<class T>
T Kruskal_Cost(Graph2<T>& _g)
{
	int nVertex = _g.getNVertex();
	vector<pair<int, T>>* sets = _g.getSet();

	vector< pair < T, pair<int, int> > > tempData;
	for (int i = 0; i < nVertex; i++)
	{
		int vecLength = sets[i].size();
		for (int j = 0; j < vecLength; j++)
		{
			if (i < sets[i][j].first) {
				tempData.push_back( make_pair(sets[i][j].second, make_pair(i, sets[i][j].first) ) );
			}
		}
	}

	sort(tempData.begin(), tempData.end());
	Disjoint_Set2<T> ds(_g.getNVertex());

	T cost = static_cast<T>(0);
	for (int i = 0; i < tempData.size(); i++)
	{
		T weight = tempData[i].first;
		int vertex_1 = tempData[i].second.first;
		int vertex_2 = tempData[i].second.second;

		if (ds.Find_Disjoint_Set(vertex_1) != ds.Find_Disjoint_Set(vertex_2)) {
			cost += weight;
			ds.Union_DisJoint_Set(vertex_1, vertex_2);
		}
	}
	return cost;
}




int main(int argc, char** argv)
{
	Graph2<int> input_Graph(argv[1]);
	//Disjoint_Set2<int> ds(input_Graph.getNVertex());
	//ds.writeAnswer(input_Graph, argv[2]);
	int cost = Kruskal_Cost<int>(input_Graph);

	FILE* outputfile_p = fopen(argv[2], "w");
	if (outputfile_p == NULL) {
		exit(EXIT_FAILURE);
	}
	fprintf(outputfile_p, "%d", cost);
	fclose(outputfile_p);

	return 0;
}