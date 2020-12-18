#include <iostream>
#include "src/LinkedList.hpp"

#include <vector>

int main()
{
	LinkedList<int> list = { 1, 2, 3 };

	list.push(4);
	list.push(5);

	std::cout << list[2] << std::endl;
	list[2] = 15;
	std::cout << list[2] << std::endl;

	/* Testing expanded range based */
	for (LinkedList<int>::Iterator i = list.begin(); i != list.end(); i++)
	{
		std::cout << *i << std::endl;
	}

	// Testing minimal range based
	for (int value : list)
	{
		std::cout << value << std::endl;
	}
	return 0;
}