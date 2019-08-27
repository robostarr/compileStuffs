#include "reduceShiftParser.h"

ReduceShiftParser::ReduceShiftParser() {
	std::cout << "default constructor" << std::endl;
}

ReduceShiftParser::ReduceShiftParser(std::string command) {
	m_command = command;
}

bool ReduceShiftParser::step() {
	if (!reduce()) {
		return !shift();
	}
	return false;
}

void ReduceShiftParser::addRule(std::string src, std::string dest) {
	m_rules[src] = dest;
	if(std::find(m_ruleLengths.begin(), m_ruleLengths.end(), (uint32_t) src.length()) == m_ruleLengths.end()) {
		std::cout << "adding new length: " << src.length() << std::endl;
		m_ruleLengths.emplace_back(src.length());
	}
	std::cout << "adding rule with src: " << src << std::endl;
	std::cout << "            and dest: " << m_rules[src] << std::endl;
}

void ReduceShiftParser::addRule(std::vector<std::string> src, std::string dest) {
	for (const std::string& str : src) {
		addRule(str, dest);
	}
}

void ReduceShiftParser::addCommand(std::string command) {
	m_command.append(command);
}

void ReduceShiftParser::printState() {
	std::cout << m_stack << "\t\t\t\t" << m_command << std::endl;
}

bool ReduceShiftParser::shift() {
	if (m_command.empty())
		return false;
	
	m_stack += m_command.front();
	m_command = m_command.substr(1);
	return true;
}

bool ReduceShiftParser::reduce() {
	for (uint32_t length : m_ruleLengths) {
		// will throw if you try to take the substring of other than that
		if (length <= m_stack.length() && !m_rules[m_stack.substr(m_stack.length() - length)].empty()) {
			std::string key = m_stack.substr(m_stack.length() - length);
			std::cout << "found a match with key: " << key << std::endl;
			std::cout << "            and length: " << length << std::endl;
			m_stack.resize(m_stack.length() - length);
			m_stack.append(m_rules[key]);
			return true;
		}
	}
	std::cout << "did not find match in reduce" << std::endl;
	return false;
}