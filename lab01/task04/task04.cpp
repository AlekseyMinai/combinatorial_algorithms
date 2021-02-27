

#include <boost/timer.hpp>
#include <iostream>
#include "Utils.h"

//#include "Source.cpp"

/*
* Время работы
* k = 5, n = 10 - < 0.001
* k = 5, n = 25 -  0.008s
* k = 5, n = 100 - 10s
*/

void print(std::vector<int> v)
{
    //for (int i = 0; i < v.size(); ++i)
    //{
    //    std::cout << v[i] << " ";
    //}
    //std::cout << std::endl;
}

int main()
{
    boost::timer t;
    t.restart();
    void(*print_result)(std::vector<int>) = print;
    create_all_combination(3, 5, print_result);
    double duration = t.elapsed();
    std::cout << duration << std::endl;
}