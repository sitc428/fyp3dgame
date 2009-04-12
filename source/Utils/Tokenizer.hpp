#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__

#include <string>

/*!		
	A simple string tokenizer
*/
class Tokenizer
{
public:
	/*!
		Constructor - create a  tokenizer to parse the input string
		\param str The string you are going to tokenize
		\param delim The delimiter of a string
	*/
	Tokenizer(const std::string& str, const std::string& delim);
	
	/*!
		Reset the position. After calling reset, getNextToken will return the first token
	*/
	void reset() ;
	
	/*!
		Set the string you are going to parse
	*/
	void setString(const std::string& s) ;
	
	/*!
		Set the delimiter of the tokenizer
	*/
	void setDelimiter(const std::string& s) ;
	
	/*!
		Grab the next token
	*/
	std::string getNextToken() ;
	
	/*!
		Check there exists next token
	*/
	bool hasNextToken() const ;

private:
	int m_prev;
	int m_cur ;
	std::string m_str ;
	std::string m_delimiter ;
};


#endif // __TOKENIZER_HPP__
