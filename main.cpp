#include "util.h"
#include <string>
#include <vector>
#include "interpreter.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printStartMessage();

		std::vector<char> memory = { 0 };
		size_t memory_pointer = 0;

		bool isRunning = true;
		while (isRunning)
		{
			std::cout << "### ";
			
			std::string line;
			std::getline(std::cin, line);

			if (line == "help")
			{
				printHelpMessage();
			}
			else if (line == "exit")
			{
				isRunning = false;
			}
			else if (line == "int")
			{
				std::cout << (int)memory[memory_pointer] << '\n';
			}
			else if (line == "flush")
			{
				memory = { 0 };
				memory_pointer = 0;
			}
			else if (line == "memory")
			{
				for (size_t i = 0; i < memory.size(); ++i)
				{
					std::cout << memory[i];
				}
				std::cout << '\n';
			}
			else if (line == "memoryint")
			{
				for (size_t i = 0; i < memory.size(); ++i)
				{
					std::cout << (int) memory[i] << ", ";
				}
				std::cout << "0...\n";
			}
			else
			{
				bool hadOutput = executeString(line, memory, memory_pointer);
				if (hadOutput)
				{
				std::cout << '\n';
				}
			}
		}
	}
	return 0;
}