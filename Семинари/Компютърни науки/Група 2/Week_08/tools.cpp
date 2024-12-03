#include <iostream>
#include <vector>

class Tool {

public:
	virtual void print(int indent = 0) = 0;

};

class SingleTool : public Tool {
	std::string name;
public:
	SingleTool(const std::string& name) : name(name) {}

	virtual void print(int indent = 0) override {
		for(int i = 0; i < indent; i++)
			std::cout << "\t";
		std::cout << "Tool : " << name << std::endl;
	}
};

class ToolBox : public Tool {
	std::vector<Tool*> tools;
public:

	ToolBox() {}

	ToolBox* addTool(Tool* tool) {
		tools.push_back(tool);
		return this;
	}

	virtual void print(int indent = 0) override {
		for(int i = 0; i < indent; i++)
			std::cout << "\t";
		std::cout << "Box : {" << std::endl;
		
		for (auto tool : tools) {
			tool->print(indent + 1);
		}

		for(int i = 0; i < indent; i++)
			std::cout << "\t";
		std::cout << "}" << std::endl;
	}
};


int main() {

	SingleTool *hammer = new SingleTool{"Hammer"};
	SingleTool *screwdriver = new SingleTool{"Screwdriver"};
	SingleTool *scissors = new SingleTool{"Scissors"};


	ToolBox toolbox;
	toolbox.addTool(scissors);
	toolbox.addTool((new ToolBox())->addTool(hammer)->addTool(screwdriver));
	toolbox.print();

	return 0;

}
