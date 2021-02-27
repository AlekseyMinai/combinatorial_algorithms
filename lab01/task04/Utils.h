#pragma once
#include <vector>

std::vector<int> create_first(int n, int k);

void create_all_combination(int n, int k, void(*output)(std::vector<int>));