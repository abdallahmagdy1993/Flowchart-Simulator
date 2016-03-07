
#ifndef CUT_H
#define CUT_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class Cut : public Action
{
private:
	//static type=2;
	Point Position;
	Statement *Stat;
public:
	Cut(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif