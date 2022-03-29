#pragma once
#include <string>
#include <vector>

bool executeString(const std::string& line, std::vector<char>& memory, size_t& memory_pointer);
size_t find_matching_loop_end_bracket(const std::string& line, const size_t& program_counter);