#pragma once
#include <iostream>

#define LOGI(fmt, ...) printf(fmt"\n",__VA_ARGS__)

class Log
{
public:
	static void Info(std::string s);

	static void Info(std::string format, std::string s);
};

