#include <irrlicht/irrlicht.h>

#include <string>
#include <sstream>

#include "Utils.hpp"

float Utils::toFloat(const std::string& s)
{
	std::istringstream iss(s);
	float f;
	return (iss >> f).fail() ? 0.0 : f;
}

int Utils::toInt(const std::string& s)
{
	std::istringstream iss(s);
	int i;
	return (iss >> i).fail() ? 0 : i;
}

std::string Utils::toString(irr::u32 num)
{
	if(num < 10 )
	{
		std::string ret = "000";
		return ret.append( irr::core::stringc(num).c_str() );
	}
}
