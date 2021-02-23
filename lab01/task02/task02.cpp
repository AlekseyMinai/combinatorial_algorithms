#include <string>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

void generate_all_permutations(
	std::vector<int> current_permutation, 
	void(*return_permutation)(std::vector<int>&)
)
{
	int max_element = current_permutation[current_permutation.size() -  1];
	int border = max_element + 1;
	current_permutation.insert(current_permutation.begin(), border);
	current_permutation.push_back(border);

	std::vector<int> reverse_permutation;
	std::vector<int> directions;

	for (int i = 0; i < current_permutation.size(); i++)
	{
		reverse_permutation.push_back(current_permutation[i]);
		directions.push_back(-1);
	}
	directions[1] = 0;

	int moving_position = max_element;

	boost::timer t;
	t.restart();

	while (moving_position != 1)
	{
		return_permutation(current_permutation);
		moving_position = max_element;
		while (current_permutation[reverse_permutation[moving_position] + directions[moving_position]] > moving_position)
		{
			directions[moving_position] = -directions[moving_position];
			moving_position--;
		}
		std::swap(
			current_permutation[reverse_permutation[moving_position]],
			current_permutation[reverse_permutation[moving_position] + directions[moving_position]]
		);
		std::swap(
			reverse_permutation[current_permutation[reverse_permutation[moving_position]]],
			reverse_permutation[moving_position]
		);
	}

	//loging computation time
	double duration = t.elapsed();
	std::cout << duration << std::endl;
}

void print(std::vector<int> &v)
{
	//for (int i = 1; i < v.size() - 1; i++)
	//{
	//	std::cout << v[i] << " ";
	//}
	//std::cout << std::endl;
}

void generate_all_permutations(int size, void(*return_permutation)(std::vector<int>&))
{
	std::vector<int> first_permutation;
	for (int i = 1; i < size + 1; ++i)
	{
		first_permutation.push_back(i);
	}
	generate_all_permutations(first_permutation, return_permutation);
}

int main() {
	void(*print_result)(std::vector<int>&) = print;
	generate_all_permutations(10, print_result); // = 0.48
	generate_all_permutations(13, print_result); // = 46.04
	//generate_all_permutations(15, print_result); ~ 46 * 14 * 15
	//generate_all_permutations(20, print_result);
	return 0;
}