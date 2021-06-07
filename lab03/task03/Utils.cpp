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

void printMatrix(std::vector<std::vector<double>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int k = 0; k < matrix.size(); k++)
		{
			std::cout << std::round(matrix[i][k]) << " ";
		}
		std::cout << std::endl;
	}
}

inline std::vector<std::vector<int>> read_file(std::string path)
{
	std::ifstream file;
	file.open(path);
	std::vector<std::vector<int>> graph;
	if (file.is_open())
	{
		std::string input;
		int read_line = 0;
		while (!file.eof())
		{
			std::getline(file, input);
			std::vector<std::string> split_input;
			boost::split(split_input, input, boost::is_any_of(" "));
			if (read_line > 0)
			{
				std::vector<int> row;
				for (int i = 0; i < split_input.size(); i++)
				{
					row.push_back(stoi(split_input[i]));
				}
				graph.push_back(row);
			}
			read_line++;
		}
	}
	return graph;
}

template <typename T>
inline std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> matrix)
{
	std::vector<std::vector<int>> transposed_matrix;
	for (int i = 0; i < matrix.size(); i++)
	{
		std::vector<int> row;
		for (int k = 0; k < matrix[i].size(); k++)
		{
			row.push_back(matrix[k][i]);
		}
		transposed_matrix.push_back(row);
	}
	return transposed_matrix;
}