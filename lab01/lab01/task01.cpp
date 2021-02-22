#include <boost/timer.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<size_t> v = { 7, 1, 12, 20, 30, 22, 10, 55, 1};
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        //copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        //std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
    double duration = t.elapsed();
    std::cout << duration << std::endl;
    return 0;
}

// for 10 - 0.045s
// for 13 - 52.5s
// for 20 ~ 235d
