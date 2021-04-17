#include <iostream>
#include <vector>

struct Object
{
    int cost;
    int weight;

    Object(int cost, int weight)
    {
        this->cost = cost;
        this->weight = weight;
    }


};

std::vector<int> find(std::vector<Object>)
{

}

int main()
{
    std::vector<Object> objects;
    objects.push_back(Object(5, 6));
    objects.push_back(Object(3, 4));
    objects.push_back(Object(1, 3));
    objects.push_back(Object(2, 3));
    objects.push_back(Object(5, 6));
}

