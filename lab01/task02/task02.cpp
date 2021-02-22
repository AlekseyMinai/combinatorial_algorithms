#include <string>
#include <iostream>
#include <vector>


enum Direction
{
	LEFT, RIGHT
};

struct Element
{
	int value;
	Direction direction;

	Element(int value, Direction direction)
	{
		this->value = value;
		this->direction = direction;
	}

};


template<typename T, typename R>
struct Pair
{
	T key;
	R value;

	Pair(T key, R value)
	{
		this->key = key;
		this->value = value;
	}
};

Pair<int, Element> get_largest_mobile_from(std::vector<Element> elements)
{
	Element largest_mobile_element = elements[0];
	int index = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		bool is_larger_then_current_largest = elements[i].value > largest_mobile_element.value;
		if (elements[i].direction == LEFT)
		{
			bool is_larger_then_previous = i != 0 && elements[i].value > elements[i - 1].value;
			if (is_larger_then_previous && is_larger_then_current_largest)
			{
				largest_mobile_element = elements[i];
				index = i;
			}
		}
		else
		{
			bool is_larger_then_next = i != elements.size() - 1 && elements[i].value > elements[i + 1].value;
			if (is_larger_then_next && is_larger_then_current_largest)
			{
				largest_mobile_element = elements[i];
				index = i;
			}
		}
		//std::cout << largest_mobile_element.value << std::endl;
	}
	return Pair<int, Element>(index, largest_mobile_element);
}

void generate_all_permutations(
	std::vector<Element> elements,
	void(*return_permutation)(std::vector<int>))
{
	Pair<int, Element> result = get_largest_mobile_from(elements);
	while (result.value.value != 1)
	{
		switch (result.value.direction)
		{
		case LEFT:
		{
			//swap(elements[]);
			break;
		}
		case RIGHT:
		{
			break;
		}
		}
	}
}

void print(std::vector<int> result)
{
	for (int i = 0; i < result.size(); ++i)
	{
		std::cout << result[i] << ", ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<Element> elements;
	for (int i = 0; i < 6; ++i)
	{
		elements.push_back(Element(i + 1, LEFT));
	}
	void(*printResult)(std::vector<int>) = print;
	generate_all_permutations(elements, printResult);
	return 0;
}