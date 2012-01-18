#include "level.h"

Level::Level (std::string filename)
{
	loadInstructionSet();

	std::vector<Instruction> enqueue;

	int line_n = 0;

	std::ifstream file (filename.c_str());

	if (!file.is_open()) throw "Level not found.";

	while (file.good())
	{
		line_n++;
		std::string line;
		Instruction instruction;
		std::getline (file, line);
		instruction = process (line);

		if (!instruction.instruction.empty())
		{
			Instruction *parent = NULL;
			if (!enqueue.empty()) parent = &enqueue.back();

			int level = validateLevel(parent, instruction, line_n);

			if (level > 0)
			{
				enqueue.push_back(instruction);
			}
			else if (level < 0)
			{
				instruction = *parent;
				enqueue.pop_back();
				if (enqueue.empty()) instructions.push_back(instruction);
				else enqueue.back().block.push_back(instruction);
			}
			else
			{
				if (parent == NULL) instructions.push_back(instruction);
				else parent->block.push_back(instruction);
			}
		}
	}

	file.close();

	instruction_id = 0;
}

Level::~Level()
{
}

bool Level::end()
{
	return instruction_id >= instructions.size();
}

Instruction Level::nextInstruction()
{
	if (end()) throw "End of instructions";
	return instructions.at(instruction_id++);
}

Instruction Level::process (std::string line)
{
	Instruction instruction;
	size_t size = line.size();
	size_t pos0 = 0, pos1 = 0;

	pos0 = line.find_first_of(COMMENT);
	if (pos0 != std::string::npos)
	{
		line = line.substr(0, pos0);
		size = line.size();
	}

	pos0 = line.find_first_not_of(SPACES);
	if (pos0 == std::string::npos) return instruction;

	pos1 = line.find_first_of(SPACES, pos0 + 1);
	if (pos1 == std::string::npos) pos1 = size;
	instruction.instruction = line.substr(pos0, pos1 - pos0);

	pos0 = line.find_first_not_of(SPACES, pos1 + 1);
	while (pos0 != std::string::npos)
	{
		pos1 = line.find_first_of(SPACES, pos0 + 1);
		if (pos1 == std::string::npos) pos1 = size;

		instruction.arguments.push_back(line.substr(pos0, pos1 - pos0));

		pos0 = line.find_first_not_of(SPACES, pos1 + 1);
	}

	return instruction;
}

void Level::throwError(int line)
{
	std::ostringstream error;
	error << "Syntax error on line " << line;
	std::string str = error.str();
	std::cout << str << std::endl;
	throw str.c_str();
}

void Level::loadInstructionSet()
{
	std::set<std::string> allowed_instructions;

	allowed_instructions.insert("background");
	allowed_instructions.insert("enemies");
	allowed_instructions.insert("music");
	allowed_instructions.insert("delay");
	allowed_instructions.insert("route");
	instruction_set.insert(std::make_pair("", allowed_instructions));

	allowed_instructions.clear();
	allowed_instructions.insert("image");
	instruction_set.insert(std::make_pair("background", allowed_instructions));

	allowed_instructions.clear();
	allowed_instructions.insert("enemy");
	instruction_set.insert(std::make_pair("enemies", allowed_instructions));

	allowed_instructions.clear();
	allowed_instructions.insert("raise");
	instruction_set.insert(std::make_pair("route", allowed_instructions));

	allowed_instructions.clear();
	allowed_instructions.insert("move");
	allowed_instructions.insert("shot");
	//allowed_instructions.insert("fight"); // TODO: only if boss
	instruction_set.insert(std::make_pair("raise", allowed_instructions));

	std::vector<int> allowed_arguments;
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // id
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // image
	instruction_arguments.insert(std::make_pair("image", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_NAME); // name
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // image
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // shot
	allowed_arguments.push_back(ARGUMENT_TYPE_BOOLEAN); // animated
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // damage
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // life
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // speed
	instruction_arguments.insert(std::make_pair("enemy", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_NAME); // level|boss // TODO: option
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // number
	instruction_arguments.insert(std::make_pair("music", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // time
	instruction_arguments.insert(std::make_pair("delay", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_NAME); // enemy
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // left
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // top
	instruction_arguments.insert(std::make_pair("raise", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // left
	allowed_arguments.push_back(ARGUMENT_TYPE_NUMBER); // top
	instruction_arguments.insert(std::make_pair("move", allowed_arguments));

	allowed_arguments.clear();
	allowed_arguments.push_back(ARGUMENT_TYPE_OPTIONAL_NUMBER); // count
	instruction_arguments.insert(std::make_pair("shot", allowed_arguments));
}

int Level::validateLevel(Instruction *parent, Instruction &instruction, int line)
{
	int level = 0;

	if (instruction.instruction.compare(END_BLOCK) == 0)
	{
		if (parent == NULL || parent->instruction.empty() || !instruction.arguments.empty()) throwError(line);
		return -1;
	}
	else if (instruction_set.count(instruction.instruction) > 0)
	{
		level = 1;
	}

	// validate instruction

	validateArguments(instruction, line);

	return level;
}

void Level::validateArguments(Instruction &instruction, int line)
{
	// TODO: use instruction_arguments
}
