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

	Element() {}

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

Pair<int, Element> get_largest_mobile_from(std::vector<Element> &elements, int last_largest_mobile_value)
{
	Element largest_mobile_element = Element(-1, LEFT);
	int index = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		bool is_larger_then_current_largest = elements[i].value > largest_mobile_element.value;
		if (elements[i].direction == LEFT)
		{
			bool is_larger_then_previous = i != 0 && elements[i].value > elements[i - 1].value;
			if ((i == 0 && elements[i].value == last_largest_mobile_value))// || 
				//(elements[i].value < elements[i - 1].value && elements[i].value == last_largest_mobile_value))
			{
				elements[i].direction = RIGHT;
				continue;
			}
			if (is_larger_then_previous && is_larger_then_current_largest)
			{
				largest_mobile_element = elements[i];
				index = i;
			}
		}
		else
		{
			if ((i == elements.size() - 1 && elements[i].value == last_largest_mobile_value)) //||
				//(elements[i].value < elements[i + 1].value && elements[i].value == last_largest_mobile_value))
			{
				elements[i].direction = LEFT;
				continue;
			}
			bool is_larger_then_next = i != elements.size() - 1 && elements[i].value > elements[i + 1].value;
			if (is_larger_then_next && is_larger_then_current_largest)
			{
				largest_mobile_element = elements[i];
				index = i;
			}
		}
	}
	//std::cout << largest_mobile_element.value << std::endl;
	return Pair<int, Element>(index, largest_mobile_element);
}

void generate_all_permutations(
	std::vector<Element> elements,
	void(*return_permutation)(std::vector<Element>))
{
	return_permutation(elements);
	Pair<int, Element> result = get_largest_mobile_from(elements, 0);
	int i = 0;
	while (result.value.value != 1 && i < 25)
	{
		i++;
		switch (result.value.direction)
		{
			case LEFT:
			{
				std::swap(elements[result.key], elements[result.key - 1]);
				break;
			}
			case RIGHT:
			{
				std::swap(elements[result.key], elements[result.key + 1]);
				break;
			}
		}
		result = get_largest_mobile_from(elements, result.value.value);
		return_permutation(elements);
	}
}

int count = 1;

void print(std::vector<Element> result)
{
	std::cout << count << ". ";
	count++;
	for (int i = 0; i < result.size(); ++i)
	{
		std::cout << result[i].value << " " << "(" << result[i].direction << "); ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<Element> elements;
	for (int i = 0; i < 5; ++i)
	{
		elements.push_back(Element(i + 1, LEFT));
	}
	void(*printResult)(std::vector<Element>) = print;
	generate_all_permutations(elements, printResult);
	return 0;
}