#ifndef MOVE_H
#define MOVE_H

#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class Move : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	Statement*Stat;
public:
	Move(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif