#include "Utils.cpp"

const std::string INPUT_FILE_NAME = "input/input.txt";

std::vector<std::vector<double>> create_kirxgof_matrix(std::vector<std::vector<int>> adjacency_matrix)
{
    std::vector<std::vector<double>> kirxgof_matrix;
	for (int i = 0; i < adjacency_matrix.size(); i++)
	{
		int count = 0;
		std::vector<double> row;
		for (int k = 0; k < adjacency_matrix.size(); k++)
		{
			if (adjacency_matrix[i][k] == 1)
			{
				row.push_back(-1);
				count++;
			}
			else
			{
				row.push_back(0);
			}
		}
		row[i] = count;
		kirxgof_matrix.push_back(row);
	}
	return kirxgof_matrix;
}

double calculate_determenant(std::vector<std::vector<double>> matrix)
{
	std::vector<std::vector<double>> minor;
	for (int i = 1; i < matrix.size(); i++)
	{
		std::vector<double> row;
		for (int k = 1; k < matrix.size(); k++)
		{
			row.push_back(matrix[i][k]);
		}
		minor.push_back(row);
	}

	for (int m = 0; m < minor.size() - 1; m++)
	{
		for (int i = m + 1; i < minor.size(); i++)
		{
			double coefficient = -minor[i][m] / minor[m][m];
			for (int k = 0; k < minor.size(); k++)
			{
				minor[i][k] = minor[i][k] + minor[m][k] * coefficient;
			}
		}
	}

	int result = 1;
	for (int i = 0; i < minor.size(); i++)
	{
		result *= minor[i][i];
	}
	return result;
}

int main()
{
    std::vector<std::vector<int>> adjacency_matrix = read_file(INPUT_FILE_NAME);
	std::vector<std::vector<double>> kirxgof = create_kirxgof_matrix(adjacency_matrix);
	println(adjacency_matrix);
	std::cout << std::endl;
	println(kirxgof);
	std::cout << std::endl;
	std::cout << "result = " << calculate_determenant(kirxgof) << std::endl;
}
