#include <iostream>
#include <string>
#include <algorithm>

std::string stripChars(std::string str, std::string chars) {

	for (char c : chars) {
		str.erase(std::remove(str.begin(), str.end(), c), str.end());
	}
	return str;
}

int main()
{
	std::string s = "#Hello #World!!";
	std::string chars = "#!";

	std::string result = stripChars(s, chars);

	std::cout << s << std::endl;
	std::cout << result;

	return 0;
}