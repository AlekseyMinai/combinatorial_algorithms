#include <stack>
#include <unordered_map>
#include "TreeNode.cpp"
#include "Utils.cpp"


bool has_back_edge(TreeNode* node, int enter_time)
{
	std::stack<TreeNode*> dfs_stack;
	dfs_stack.push(node);
	while (dfs_stack.size() != 0)
	{
		TreeNode* top = dfs_stack.top();
		dfs_stack.pop();
		for (int i = 0; i < top->back_edge.size(); i++)
		{
			TreeNode* back_edge = top->back_edge[i];
			if (back_edge->enter < enter_time)
			{
				return true;
			}
		}
		for (int i = 0; i < top->children.size(); i++)
		{
			dfs_stack.push(top->children[i]);
		}
	}
	return false;
}

bool is_articulation_point(TreeNode* node)
{
	if (node->children.size() == 0)
	{
		return false;
	}
	bool is_articulation_point = false;
	for (int i = 0; i < node->children.size(); i++)
	{
		is_articulation_point = is_articulation_point || !has_back_edge(node->children[i], node->enter);
	}
	return is_articulation_point;
}

std::vector<int> find_articulation_points(TreeNode* root)
{
	std::vector<int> articulation_points;
	if (root->children.size() > 1)
	{
		articulation_points.push_back(root->value);
	}
	int back_paths_count = 0;
	std::stack<TreeNode*> dfs_stack;
	for (int i = 0; i < root->children.size(); i++)
	{
		dfs_stack.push(root->children[i]);
	}
	while (dfs_stack.size() != 0)
	{
		TreeNode* top = dfs_stack.top();
		dfs_stack.pop();
		if (is_articulation_point(top))
		{
			articulation_points.push_back(top->value + 1);
		}
		for (int i = 0; i < top->children.size(); i++)
		{
			dfs_stack.push(top->children[i]);
		}
	}
	return articulation_points;
}

void print_result(TreeNode* tree_root, std::vector<std::vector<int>> adjacency_matrix)
{
	std::cout << "----ADJACENCY MATRIX----" << std::endl;
	println(adjacency_matrix);
	std::cout << std::endl;
	std::cout << "----DFS TREE----" << std::endl;
	printTreeNode(tree_root);
	std::cout << std::endl;
	std::cout << "----ARICULATION POINTS----" << std::endl;
	println(find_articulation_points(tree_root));
	std::cout << std::endl;
}

TreeNode* build_dfs_tree(std::vector<std::vector<int>> adjacency_matrix)
{
	std::unordered_map<int, TreeNode*> visited_tree_node_map;
	std::stack<TreeNode*> dfs_stack;
	int curent_node = 0;
	int time = 0;
	int start_node_value = 0;
	TreeNode* tree_root = new TreeNode(start_node_value, -1, time);
	visited_tree_node_map[start_node_value] = tree_root;
	dfs_stack.push(tree_root);
	while (dfs_stack.size() != 0)
	{
		TreeNode* top = dfs_stack.top();
		for (int i = 0; i < adjacency_matrix.size(); i++)
		{
			if (adjacency_matrix[top->value][i] == 1)
			{
				if (visited_tree_node_map[i] == nullptr)
				{
					time++;
					TreeNode* child = new TreeNode(i, top->value, time);
					dfs_stack.push(child);
					visited_tree_node_map[i] = child;
					top->children.push_back(child);
					break;
				}
				else
				{
					TreeNode* back_edge = visited_tree_node_map[i];
					bool isNotChildren = !contains(top->children, back_edge);
					bool isNotBackEdgeBackPath = !contains(back_edge->back_edge, top);
					bool isNotBackPath = top->parent != i;
					if (isNotChildren && isNotBackEdgeBackPath && isNotBackPath)
					{
						top->back_edge.push_back(back_edge);
					}
				}
			}
			if (i == adjacency_matrix.size() - 1)
			{
				time++;
				top->exit = time;
				dfs_stack.pop();
			}
		}
	}
	return tree_root;
}

int main()
{
	std::vector<std::vector<int>> adjacency_matrix = read_file("test/input.txt");
	TreeNode* tree_root = build_dfs_tree(adjacency_matrix);
	print_result(tree_root, adjacency_matrix);
	delete tree_root;
	return 0;
}
