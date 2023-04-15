#include "SimplerRegex.h"
#include <iostream>

int main()
{
	SimplerRegex linkRegex;
	linkRegex
		.add("https://")
		.optional()
		.add("www.")
		.addSimplerRegex(SimplerRegex()
			.word()
			.orPattern(SimplerRegex()
				.addAnyBetween('0', '9')
				.pattern())
			.noneOrMore())
		.add(".com")
		.addSimplerRegex(SimplerRegex()
			.add("/")
			.addSimplerRegex(SimplerRegex()
				.word()
				.orPattern(SimplerRegex()
					.addAnyBetween('0', '9')
					.pattern())
				.noneOrMore())
			.optional());

	std::cout << "The pattern : " << linkRegex.pattern() << std::endl;
	std::cout << (linkRegex.match("www.google.com") ? "Matches " : "Does not match ") << "The string \"www.google.com\"." << std::endl;
	std::cout << (linkRegex.match("https://www.google.com") ? "Matches " : "Does not match ") << "The string \"https://www.google.com\"." << std::endl;
	std::cout << (linkRegex.match("www.google.com/helloworld123") ? "Matches " : "Does not match ") << "The string \"www.google.com/helloworld123\"." << std::endl;

	std::cout << std::string(50, '-') << std::endl;

	SimplerRegex numberRegex;
	numberRegex
		.addAnyBetween('1', '9')
		.addSimplerRegex(SimplerRegex()
			.addAnyBetween('0', '9')
			.noneOrMore()
			.optional())
		.orPattern("0");

	std::cout << "The pattern : " << numberRegex.pattern() << std::endl;
	std::cout << (numberRegex.match("0") ? "Matches " : "Does not match ") << "The string \"0\"." << std::endl;
	std::cout << (numberRegex.match("5") ? "Matches " : "Does not match ") << "The string \"5\"." << std::endl;
	std::cout << (numberRegex.match("12345") ? "Matches " : "Does not match ") << "The string \"12345\"." << std::endl;

	std::cout << std::string(50, '-') << std::endl;

	SimplerRegex floatingPointNumbers;
	floatingPointNumbers
		.add("-")
		.optional()
		.addSimplerRegex(numberRegex)
		.add(".")
		.addSimplerRegex(SimplerRegex().addAnyBetween('0', '9').oneOrMore());

	std::cout << "The pattern : " << floatingPointNumbers.pattern() << std::endl;
	std::cout << (floatingPointNumbers.match("0.31") ? "Matches " : "Does not match ") << "The string \"0.31\"." << std::endl;
	std::cout << (floatingPointNumbers.match("3.14") ? "Matches " : "Does not match ") << "The string \"3.14\"." << std::endl;
	std::cout << (floatingPointNumbers.match("-100.01") ? "Matches " : "Does not match ") << "The string \"-100.01\"." << std::endl;

	std::cout << std::string(50, '-') << std::endl;

	SimplerRegex scientificNotationRegex;
	scientificNotationRegex
		.addSimplerRegex(floatingPointNumbers)
		.addAnyFrom("eE")
		.addSimplerRegex(SimplerRegex()
			.add("-")
			.optional())
		.addSimplerRegex(numberRegex);

	std::cout << "The pattern : " << scientificNotationRegex.pattern() << std::endl;
	std::cout << (scientificNotationRegex.match("0.31e-1000") ? "Matches " : "Does not match ") << "The string \"0.31e-1000\"." << std::endl;
	std::cout << (scientificNotationRegex.match("3.14e3") ? "Matches " : "Does not match ") << "The string \"3.14e3\"." << std::endl;
	std::cout << (scientificNotationRegex.match("-100.0e-34") ? "Matches " : "Does not match ") << "The string \"-100.0e-34\"." << std::endl;

	return 0;
}
