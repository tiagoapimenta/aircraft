#ifndef LEVEL_H
#define LEVEL_H

#include "core.h"

#define COMMENT "#"
#define SPACES " \t"
#define BLANKS " \t\r\n"
#define SIGN '-'
#define NUMBERS "0123456789"
#define END_BLOCK "end"

#define ARGUMENT_TYPE_BOOLEAN          0
#define ARGUMENT_TYPE_NUMBER           1
#define ARGUMENT_TYPE_OPTIONAL_NUMBER  2
#define ARGUMENT_TYPE_NAME             3

struct Instruction
{
	std::string instruction;
	std::vector<std::string> arguments;
	std::vector<Instruction> block;
};

class Level
{
public:
	Level (std::string filename);
	~Level();

	bool end();
	Instruction nextInstruction();

protected:
private:
	std::vector<Instruction> instructions;
	std::map<std::string, std::set<std::string> > instruction_set;
	std::map<std::string, std::vector<int> > instruction_arguments;
	size_t instruction_id;

	Instruction process (std::string line);
	void throwError(int line);
	void loadInstructionSet();
	int validateLevel(Instruction *parent, Instruction &instruction, int line);
	void validateArguments(Instruction &instruction, int line);
};

#endif // LEVEL_H
