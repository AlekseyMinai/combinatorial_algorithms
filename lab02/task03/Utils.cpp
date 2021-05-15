#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

template <typename T>
inline void printVector(std::vector<T> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl << std::endl;
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
	std::cout << std::endl;
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
		int count = 0;
		while (!file.eof())
		{
			std::getline(file, input);
			count++;
			if (count == 1) continue;
			std::vector<std::string> split_input;
			boost::split(split_input, input, boost::is_any_of(" "));
			std::vector<int> adjactive_matrix_row;
			for (int i = 0; i < split_input.size(); i++)
			{
				adjactive_matrix_row.push_back(stoi(split_input[i]));
			}
			graph.push_back(adjactive_matrix_row);
		}
	}
	return graph;
}