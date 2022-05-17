#include "Log.h"

void Log::Info(std::string s)
{
	printf("%s\n", s.c_str());
}

void Log::Info(std::string format, std::string s)
{
	printf(format.c_str(), s.c_str());
	printf("\n");
}
