#include "Logging.h"

// Defines the static variable
std::chrono::system_clock::time_point Log::currnetTime;

// Outputs to the console with custom Info format
void Log::Info(std::string input)
{
	std::cout << getCurrentTime() << " [INFO]: " << input << '\n';
}

// Outputs to the console with the custom Error format
void Log::Error(std::string input)
{
	std::cerr << getCurrentTime() << " [ERROR]: " << input << '\n';
}

// Automatically throws an exception with the input
void Log::ExceptError(std::string input)
{
	throw std::runtime_error(input);
}

// For getting the current time, and formating it correctly before returning it as a string
std::string Log::getCurrentTime()
{
	currnetTime = std::chrono::system_clock::now();

	std::time_t time = std::chrono::system_clock::to_time_t(currnetTime);

	struct tm localTime;
	localtime_s(&localTime, &time);

	int hours = localTime.tm_hour, minutes = localTime.tm_min, seconds = localTime.tm_sec;

	std::string output = "[";

	// Used for formating the output properly
	if (hours < 10)
	{
		output += '0' + std::to_string(hours);
	}
	else {
		output += std::to_string(hours);
	}

	output += ':';

	if (minutes < 10)
	{
		output += '0' + std::to_string(minutes);
	}
	else {
		output += std::to_string(minutes);
	}

	output += ':';

	if (seconds < 10)
	{
		output += '0' + std::to_string(seconds);
	}
	else {
		output += std::to_string(seconds);
	}

	output += ']';

	return output;

}