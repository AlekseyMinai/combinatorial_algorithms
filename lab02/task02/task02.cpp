#include "Utils.cpp"
#include <unordered_map>
#include <stack>

struct GraphNode
{
	int exit = 0;
	int value = 0;

	GraphNode(int value) {
		this->value = value;
	}
};

int main()
{
    std::vector<std::vector<int>> adjacency_matrix = read_file("input/input.txt");
	println(adjacency_matrix);
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
		GraphNode *top = dfs_stack.top();


		//std::cout << "top->value = " << top->value + 1 << std::endl;
		//for (std::pair<int, GraphNode*> element : visited_graph_node_map)
		//{
		//	std::cout << element.second->value + 1 << " ";
		//}
		//std::cout << std::endl;


		for (int i = 0; i < adjacency_matrix.size(); i++)
		{
			if (adjacency_matrix[top->value][i] == 1)
			{
				if (visited_graph_node_map[i] == nullptr)
				{
					time++;
					GraphNode *child = new GraphNode(i);
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
						GraphNode *new_top = new GraphNode(i);
						visited_graph_node_map[i] = new_top;
						std::cout << i + 1 << std::endl;
						dfs_stack.push(new_top);
						time++;
						break;
					}
				}
			}
		}
	}
	for (std::pair<int, GraphNode*> element : visited_graph_node_map)
	{
		std::cout << "i = " << element.first + 1 << " exit = " << element.second->exit + 1 << std::endl;
		if (element.second != nullptr)
		{
			delete element.second;
		}
	}
}

