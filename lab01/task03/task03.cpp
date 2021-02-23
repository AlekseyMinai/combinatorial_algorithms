#include <string>
#include <iostream>
#include <vector>
#include <ctime>

std::vector<int> mix(std::vector<int> data)
{
	std::srand(time(0));
	for (int i = 0; i < data.size(); ++i)
	{
		int rundom_index = rand() % data.size();
		std::swap(data[i], data[rundom_index]);
	}
	return data;
}

int main()
{
	std::vector<int> data;
	for (int i = 0; i < 6; ++i)
	{
		data.push_back(i);
	}
	std::vector<int> mixed_data = mix(data);
	for (int i = 0; i < mixed_data.size(); ++i)
	{
		std::cout << mixed_data[i] << ", ";
	}
	return 0;
}