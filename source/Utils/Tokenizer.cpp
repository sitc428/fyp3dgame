#include "Tokenizer.hpp"

Tokenizer::Tokenizer(const std::string& str, const std::string& delim)
	:m_prev(0),
	m_cur(0),
	m_str(str),
	m_delimiter(delim)
{
}
	
void Tokenizer::reset()
{
	m_prev = m_cur = 0;
}
	
void Tokenizer::setString(const std::string& s)
{
	m_str = s;
}
	
void Tokenizer::setDelimiter(const std::string& s)
{
	m_delimiter = s;
}
	
std::string Tokenizer::getNextToken()
{
	m_cur = m_str.find(m_delimiter, m_prev);
	std::string s = m_str.substr(m_prev, m_cur - m_prev);
	m_prev = m_cur + 1;
	return s ;		
}	

bool Tokenizer::hasNextToken() const
{
	return m_cur == m_str.size();
}
