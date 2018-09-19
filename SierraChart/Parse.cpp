#include "stdafx.h"
#include "Engine.h"

namespace cro = std::chrono;
namespace asio = boost::asio;
using error_code = boost::system::error_code;
using namespace DTC;
using namespace DTCTools;


// *** PARSING *** 
void parsing::parse(std::string input)
{
	// example input: "user:Aaron account:1A4681234 sim"

	// set default values
	user = DEFAULT_USERNAME;
	tradeaccount_main = DEFAULT_ACCOUNT;
	tradeaccount_selected = tradeaccount_main;
	h = DEFAULT_HOST;
	p1 = DEFAULT_PORT1;
	p2 = DEFAULT_PORT2;
	zlib_enabled = DEFAULT_ZLIB_ENABLED;

	// split up space-separated arguments
	std::vector<std::string> arguments;
	const int max = input.length() - 1;
	int i = 0;
	for (int j = 0; j <= max; j++)
	{
		if (input[j] == ' ')
		{
			arguments.push_back(input.substr(i, j - i));
			i = j + 1;
		}
		else if (j == max)
		{
			arguments.push_back(input.substr(i, j - i + 1));
		}
	}

	// parse each argument
	for (auto& argument : arguments)
	{
		if (to_lowercase(argument.substr(0, 3)) == "sa:") // Sierra Account
		{
			user = argument.substr(3, argument.length() - 3);
		}
		else if (to_lowercase(argument.substr(0, 3)) == "ta:") // Trade Account
		{
			tradeaccount_main = argument.substr(3, argument.length() - 3);
			tradeaccount_selected = tradeaccount_main;
		}
		else if (to_lowercase(argument.substr(0, 2)) == "h:") // hostname
		{
			h = argument.substr(2, argument.length() - 2);
		}
		else if (to_lowercase(argument.substr(0, 3)) == "p1:") // port 1 (main)
		{
			p1 = argument.substr(3, argument.length() - 3);
		}
		else if (to_lowercase(argument.substr(0, 3)) == "p2:") // port 2 (history)
		{
			p2 = argument.substr(3, argument.length() - 3);
		}
		else if (to_lowercase(argument.substr(0, 4)) == "zlib") // zlib enabled
		{
			zlib_enabled = true;
		}
	}

}
std::string parsing::to_lowercase(const std::string& input)
{
	std::string out = input;
	std::transform(out.begin(), out.end(), out.begin(), ::tolower);
	return out;
}

