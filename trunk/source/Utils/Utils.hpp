#ifndef __UTILS_HPP__
#define __UTILS_HPP__

class Utils
{
public:
	static float toFloat(const std::string& s);
	static int toInt(const std::string& s);
	static std::string toString(irr::u32 num);
};

#endif //! __UTILS_HPP__