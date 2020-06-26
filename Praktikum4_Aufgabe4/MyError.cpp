#include "MyError.h"


void error(const std::string& s)
{
	throw std::runtime_error{ s };
}