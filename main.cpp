#include "reduceShiftParser.h"
#include <iostream>

int main(int argc, char* argv[]) {
	ReduceShiftParser rsp("a+b-c/d*a");
	rsp.addRule({"a", "b", "c", "d"}, "E");
	rsp.addRule({"E+E", "E-E", "E*E", "E/E"}, "S");
	rsp.addRule({"S+E", "S-E", "S*E", "S/E"}, "S");
	rsp.addRule({"E+S", "E-S", "E*S", "E/S"}, "S");
	rsp.addRule({"S+S", "S-S", "S*S", "S/S"}, "S");
	while (!rsp.step()) {
		std::cout << "new step" << std::endl;
	}
    return 0;
}