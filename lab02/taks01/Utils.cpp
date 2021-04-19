#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

template <typename T>
inline void println(std::vector<T> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
inline bool contains(std::vector<T> vec, const T& elem)
{
	bool result = false;
	if (std::find(vec.begin(), vec.end(), elem) != vec.end())
	{
		result = true;
	}
	return result;
}

template <typename T>
void println(std::vector<std::vector<T>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int k = 0; k < matrix.size(); k++)
		{
			std::cout << matrix[i][k] << " ";
		}
		std::cout << std::endl;
	}
}

inline std::vector<std::vector<int>> read_file(std::string path)
{
	std::ifstream file;
	file.open(path);
	std::vector<std::vector<int>> graph;
	int thing_count = 0;
	if (file.is_open())
	{
		std::string input;
		int read_line = 0;
		while (!file.eof())
		{
			std::getline(file, input);
			std::vector<std::string> split_input;
			boost::split(split_input, input, boost::is_any_of(" "));
			if (read_line == 0)
			{
				int node_count = stoi(split_input[0]);
				for (int i = 0; i < node_count; i++)
				{
					std::vector<int> row;
					for (int k = 0; k < node_count; k++)
					{
						row.push_back(0);
					}
					graph.push_back(row);
				}
			}
			else
			{
				int from_node = stoi(split_input[0]);
				int to_node = stoi(split_input[1]);
				graph[from_node - 1][to_node - 1] = 1;
				graph[to_node - 1][from_node - 1] = 1;
			}
			read_line++;
		}
	}
	return graph;
}