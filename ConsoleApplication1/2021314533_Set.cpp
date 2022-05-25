#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

template<class T>
class Graph
{
private:
	int n_vertex;
	int n_op;
	int* op_given;

	std::vector< pair<int, T> > sets;

public:
	Graph() {};
	Graph(const char* filename)
	{
		FILE* input_p = fopen(filename, "r");
		if (input_p == NULL)	
			exit(EXIT_FAILURE);
		fscanf(input_p, "%d", &n_vertex);
		fscanf(input_p, "%d", &n_op);
		op_given = new int[n_op];

		for (int i = 0; i < n_op; i++)
		{
			fscanf(input_p, "%d", &op_given[i]);
			int vertex1;
			int vertex2;
			fscanf(input_p, "%d", &vertex1);
			fscanf(input_p, "%d", &vertex2);
			sets.push_back( make_pair(vertex1, (T)vertex2) );
		}

		fclose(input_p);
	}
	~Graph()
	{
		delete[] op_given;
	}

	int getNVertex()
	{
		return n_vertex;
	}
	int getNOP()
	{
		return n_op;
	}
	int* getOPGiven()
	{
		return op_given;
	}
	std::vector< pair<int, T> > getSet()
	{
		return sets;
	}
};

template<class T>
class Disjoint_Set
{
private:
	int n;
	int* parent;
	int* height;
public:
	Disjoint_Set() {}
	Disjoint_Set(int n)
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
	~Disjoint_Set()
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

	void writeAnswer(Graph<T> &_g, char* output_File)
	{
		FILE* output_file_p = fopen(output_File, "w");
		if (output_file_p == NULL)
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






int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("not enough arguments\n");
		exit(EXIT_FAILURE);
	}

	Graph<int> input_Graph(argv[1]);
	Disjoint_Set<int> ds(input_Graph.getNVertex());
	ds.writeAnswer(input_Graph, argv[2]);
	return 0;
}