#pragma once

/*
`Command` interface of the command pattern
*/
class ICommand {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~ICommand() {}
};

class NoCommand: public ICommand {
	void execute();
	void undo();
};
