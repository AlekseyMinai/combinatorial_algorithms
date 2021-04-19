#include <vector>
#include <iostream>

struct TreeNode
{
	int value;
	int parent;
	int enter;
	int exit;
	std::vector<TreeNode*> children;
	std::vector<TreeNode*> back_edge;

	TreeNode(int value, int parent, int enter)
	{
		this->value = value;
		this->enter = enter;
		this->parent = parent;
		exit = -1;
	}

	~TreeNode()
	{
		for (int i = 0; i < children.size(); i++)
		{
			delete children[i];
		}
	}

};

inline void printTreeNode(TreeNode* node)
{
	std::cout << "[" << node->value + 1 << "] - ";
	std::cout << "{" << node->enter + 1 << "," << node->exit + 1 << "}";

	if (node->back_edge.size() > 0)
	{
		std::cout << " - back_edges - (";
	}
	for (int i = 0; i < node->back_edge.size(); i++)
	{
		std::cout << node->back_edge[i]->value + 1 << "{";
		std::cout << node->back_edge[i]->enter + 1 << ", " << node->back_edge[i]->exit + 1 << "}";
		if (i < node->back_edge.size() - 1)
		{
			std::cout << ", ";
		}
		else
		{
			std::cout << ");";
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < node->children.size(); i++)
	{
		printTreeNode(node->children[i]);
	}
}