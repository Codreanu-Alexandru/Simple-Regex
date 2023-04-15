#include "SimplerRegex.h"

SimplerRegex::SimplerRegex()
	:m_pattern("") {}

SimplerRegex::SimplerRegex(const std::string& pattern)
	:m_pattern(pattern) {}

std::string SimplerRegex::pattern()
{
	return m_pattern;
}

SimplerRegex& SimplerRegex::add(const std::string& string)
{
	for (char ch : string)
	{
		if (ch == '.' || ch == '*' || ch == '+' || ch == '?')
		{
			m_pattern += "\\";
		}

		m_pattern += std::string(1, ch);
	}
	return *this;
}

SimplerRegex& SimplerRegex::addAnyFrom(const std::string& characters)
{
	m_pattern += "[";
	for (char ch : characters)
	{
		if (ch == '.' || ch == '*' || ch == '+' || ch == '?')
		{
			m_pattern += "\\";
		}

		m_pattern += std::string(1, ch);
	}

	m_pattern += "]";
	return *this;
}

SimplerRegex& SimplerRegex::addAnyFrom(const std::vector<char>& characters)
{
	if (characters.size())
	{
		m_pattern += "[";
		for (char ch : characters)
		{
			if (ch == '.' || ch == '*' || ch == '+' || ch == '?')
			{
				m_pattern += "\\";
			}

			m_pattern += std::string(1, ch);
		}
		m_pattern += "]";
	}
	return *this;
}

SimplerRegex& SimplerRegex::addNoneFrom(const std::string& characters)
{
	m_pattern += "[^" + characters + "]";
	return *this;
}

SimplerRegex& SimplerRegex::addNoneFrom(const std::vector<char>& characters)
{
	if (characters.size())
	{
		m_pattern += "[^";
		for (char ch : characters)
		{
			m_pattern += std::string(1, ch);
		}
		m_pattern += "]";
	}
	return *this;
}

SimplerRegex& SimplerRegex::addAnyBetween(char left, char right)
{
	if (left > right)
	{
		std::swap(left, right);
	}

	m_pattern += "[" + std::string(1, left) + "-" + std::string(1, right) + "]";
	return *this;
}

SimplerRegex& SimplerRegex::word()
{
	m_pattern += "[A-Za-z]+";
	return *this;
}

SimplerRegex& SimplerRegex::any()
{
	m_pattern += ".";
	return *this;
}

SimplerRegex& SimplerRegex::optional()
{
	m_pattern = "(" + m_pattern + ")";
	m_pattern += "?";
	return *this;
}

SimplerRegex& SimplerRegex::noneOrMore()
{
	m_pattern += "*";
	return *this;
}

SimplerRegex& SimplerRegex::oneOrMore()
{
	m_pattern += "+";
	return *this;
}

SimplerRegex& SimplerRegex::fixed(std::uint_fast16_t times)
{
	m_pattern += "{" + std::to_string(times) + "}";
	return *this;
}

SimplerRegex& SimplerRegex::min(std::uint_fast16_t min)
{
	m_pattern += "{" + std::to_string(min) + ",}";
	return *this;
}

SimplerRegex& SimplerRegex::max(std::uint_fast16_t max)
{
	m_pattern += "{," + std::to_string(max) + "}";
	return *this;
}

SimplerRegex& SimplerRegex::interval(std::uint_fast16_t min, std::uint_fast16_t max)
{
	m_pattern += "{" + std::to_string(min) + "," + std::to_string(max) + "}";
	return *this;
}

SimplerRegex& SimplerRegex::orPattern(const std::string& pattern)
{
	m_pattern = "(" + m_pattern + "|" + pattern + ")";
	return *this;
}

SimplerRegex& SimplerRegex::whiteSpace()
{
	m_pattern += "\\s";
	return *this;
}

SimplerRegex& SimplerRegex::addSimplerRegex(SimplerRegex simplerRegex)
{
	m_pattern += simplerRegex.pattern();
	return *this;
}

SimplerRegex& SimplerRegex::start()
{
	m_pattern += "^";
	return *this;
}

SimplerRegex& SimplerRegex::end()
{
	m_pattern += "$";
	return *this;
}

bool SimplerRegex::match(const std::string& string)
{
	return std::regex_match(string, std::regex(m_pattern));
}

bool SimplerRegex::search(const std::string& string)
{
	return std::regex_search(string, std::regex(m_pattern));
}

void SimplerRegex::clear()
{
	m_pattern = "";
}

SimplerRegex::~SimplerRegex()
{
	clear();
}

