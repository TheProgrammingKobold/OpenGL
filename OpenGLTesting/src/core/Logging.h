#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

class Log
{
public:

	static void Info(std::string input);
	static void Error(std::string input);
	static void ExceptError(std::string input);

private:

	static std::chrono::system_clock::time_point currnetTime;
	static std::string getCurrentTime();

};

