#include <boost/timer.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../task04/Utils.cpp"


void print_replacement(std::vector<int> v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void create_all_replacement(int n, int k)
{
    auto create_all_permutation = [](std::vector<int> combination) {
        do
        {
            print_replacement(combination);
        } while (std::next_permutation(combination.begin(), combination.end()));
    };
    create_all_combination(n, k, create_all_permutation);
}

int main()
{
    boost::timer t;
    t.restart();
    create_all_replacement(5, 25);
    double duration = t.elapsed();
    std::cout << duration << std::endl;
}

/*
* for n = 5 k = 10 - 0.007
* for n = 5 k = 20 - 0.335
* for n = 5 k = 25 - 1.02
*/

