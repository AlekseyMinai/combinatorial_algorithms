#include "Utils.cpp"
#include <unordered_map>
#include <stack>
#include <map>
#include <unordered_set>

const std::string INPUT_FILE_NAME = "input/input1.txt";

struct GraphNode
{
	int exit = 0;
	int value = 0;

	GraphNode(int value) {
		this->value = value;
	}
};


std::unordered_map<int, GraphNode*> calculate_end_times(std::vector<std::vector<int>> adjacency_matrix)
{
	std::unordered_map<int, GraphNode*> visited_graph_node_map;
	std::stack<GraphNode*> dfs_stack;
	int curent_node = 0;
	int time = 0;
	int start_node_value = 0;
	GraphNode* node = new GraphNode(0);
	visited_graph_node_map[start_node_value] = node;
	dfs_stack.push(node);
	while (dfs_stack.size() != 0)
	{
		GraphNode* top = dfs_stack.top();
		for (int i = 0; i < adjacency_matrix.size(); i++)
		{
			if (adjacency_matrix[top->value][i] == 1)
			{
				if (visited_graph_node_map[i] == nullptr)
				{
					time++;
					GraphNode* child = new GraphNode(i);
					dfs_stack.push(child);
					visited_graph_node_map[i] = child;
					break;
				}
			}
			if (i == adjacency_matrix.size() - 1)
			{
				time++;
				top->exit = time;
				dfs_stack.pop();
			}
			if (dfs_stack.size() == 0 && adjacency_matrix.size() > visited_graph_node_map.size())
			{
				for (int i = 0; i < visited_graph_node_map.size() + 1; i++)
				{
					if (visited_graph_node_map[i] == nullptr)
					{
						GraphNode* new_top = new GraphNode(i);
						visited_graph_node_map[i] = new_top;
						dfs_stack.push(new_top);
						time++;
						break;
					}
				}
			}
		}
	}
	return visited_graph_node_map;
}


std::vector<int> sort_by_value(std::unordered_map<int, GraphNode*> map)
{
	std::vector<std::pair<int, GraphNode*>> vector;
	std::copy(map.begin(), map.end(), std::back_inserter<std::vector<std::pair<int, GraphNode*>>>(vector));
	std::sort(vector.begin(), vector.end(),
			[](const std::pair<int, GraphNode*>& l, const std::pair<int, GraphNode*>& r)
			{
				if (l.second->exit != r.second->exit)
				{
					return l.second->exit > r.second->exit;
				}
				return l.first < l.first;
			}
		);

	std::vector<int> values;

	for (int i = 0; i < vector.size(); i++)
	{
		values.push_back(vector[i].first);
	}
	return values;
}

bool is_strongly_connected(
	std::vector<std::vector<int>> inverted_graph, 
	std::vector<int> ordered_nodes
)
{
	std::unordered_set<int> visited_nodes;
	int ordered_nodes_cursor = 0;
	int node = ordered_nodes[ordered_nodes_cursor];
	visited_nodes.insert(node);
	while (visited_nodes.size() < ordered_nodes.size())
	{
		for (int i = 0; i < inverted_graph.size(); i++)
		{
			if (inverted_graph[node][i] == 1 && visited_nodes.count(i) == 0)
			{
				visited_nodes.insert(i);
				node = i;
				break;
			}
			if (i == inverted_graph.size() - 1)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
    std::vector<std::vector<int>> adjacency_matrix = read_file(INPUT_FILE_NAME);
	std::unordered_map<int, GraphNode*> visited_graph_node_map = calculate_end_times(adjacency_matrix);
	std::vector<int> sorted_values = sort_by_value(visited_graph_node_map);
	std::vector<std::vector<int>> transposed_matrix = transpose(adjacency_matrix);
	bool result = is_strongly_connected(transposed_matrix, sorted_values);
	std::cout << result << std::endl;
}

