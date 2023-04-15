#pragma once
#include <cstdint>
#include <string>
#include <regex>
#include <vector>

class SimplerRegex
{
private:
	std::string m_pattern;

public:
	//Constructors
	SimplerRegex();
	SimplerRegex(const std::string& string);

public:

	//Pattern Getter
	std::string pattern();

public:
	//Pulic Regex Buildup Methods
	SimplerRegex& add(const std::string& string);
	SimplerRegex& addAnyFrom(const std::string& characters);
	SimplerRegex& addAnyFrom(const std::vector<char>& characters);
	SimplerRegex& addNoneFrom(const std::string& characters);
	SimplerRegex& addNoneFrom(const std::vector<char>& characters);
	SimplerRegex& addAnyBetween(char left, char right);
	SimplerRegex& word();
	SimplerRegex& any();
	SimplerRegex& optional();
	SimplerRegex& noneOrMore();
	SimplerRegex& oneOrMore();
	SimplerRegex& fixed(std::uint_fast16_t times);
	SimplerRegex& min(std::uint_fast16_t min);
	SimplerRegex& max(std::uint_fast16_t max);
	SimplerRegex& interval(std::uint_fast16_t min, std::uint_fast16_t max);
	SimplerRegex& orPattern(const std::string& pattern);
	SimplerRegex& whiteSpace();
	SimplerRegex& addSimplerRegex(SimplerRegex simplerRegex);
	SimplerRegex& start();
	SimplerRegex& end();

public:
	//Public Functions
	bool match(const std::string& string);
	bool search(const std::string& string);
	void clear();

public:
	//Destructor
	~SimplerRegex();
};

