#include "interpreter.h"
#include <iostream>

bool executeString(const std::string& line, std::vector<char>& memory, size_t& memory_pointer)
{
	bool hadOutput = false;

	bool hasInputWaiting = false;
	char inputWaiting;

	size_t program_counter = 0;
	size_t line_length = line.size();

	size_t loop_end;
	std::string loop;

	while (program_counter < line_length)
	{
		switch (line[program_counter])
		{
		case '+':
			++memory[memory_pointer];
			break;
		case '-':
			--memory[memory_pointer];
			break;
		case '>':
			++memory_pointer;
			if (memory_pointer == memory.size())
			{
				memory.push_back(0);
			}
			break;
		case '<':
			if (memory_pointer != 0)
			{
				if (memory_pointer == memory.size() - 1 && memory[memory_pointer] == 0)
				{
					memory.pop_back();
				}
				--memory_pointer;
			}
			break;
		case '.':
			std::cout << memory[memory_pointer];
			hadOutput = true;
			break;
		case ',':
			if (hasInputWaiting)
			{
				memory[memory_pointer] = inputWaiting;
			}
			else
			{
				std::cin.get(memory[memory_pointer]);
			}
			std::cin.get(inputWaiting);
			hasInputWaiting = inputWaiting != '\n';
			break;
		case '[':
			loop_end = find_matching_loop_end_bracket(line, program_counter);
			loop = line.substr(program_counter + 1, loop_end - program_counter - 1);

			while (memory[memory_pointer] != 0)
			{
				bool temp = executeString(loop, memory, memory_pointer);
				hadOutput = hadOutput || temp;
			}

			program_counter = loop_end;
			break;
		default:
			//any character that isn't a vrainfuck command is treated as a comment - ignored
			break;
		}
		++program_counter;
	}

	return hadOutput;
}

size_t find_matching_loop_end_bracket(const std::string& line, const size_t& program_counter)
{
	unsigned int line_length = line.size();
	int depth = 0;

	for (size_t i = program_counter + 1; i < line_length; ++i)
	{
		switch (line[i])
		{
		case '[':
			++depth;
			break;
		case ']':
			if (depth == 0)
			{
				return i;
			}
			--depth;
			break;
		}
	}

	//TODO: add warning
	return line_length;
}