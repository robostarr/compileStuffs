#ifndef REDUCE_SHIFT_PARSER_H_
#define REDUCE_SHIFT_PARSER_H_

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class ReduceShiftParser {
public:
	ReduceShiftParser();
	ReduceShiftParser(std::string command);

	bool step();
	void addRule(std::string src, std::string dest);
	void addRule(std::vector<std::string> src, std::string dest);
	void addCommand(std::string command);
	void printState();

private:
	bool reduce();
	bool shift();

	std::string m_command;
	std::string m_stack;
	std::map<std::string, std::string> m_rules;
	std::vector<uint32_t> m_ruleLengths;
};

#endif // REDUCE_SHIFT_PARSER_H_