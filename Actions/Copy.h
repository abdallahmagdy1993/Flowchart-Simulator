#ifndef COPY_H
#define COPY_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class Copy : public Action
{
private:
	Point Position;
	Statement *Stat;
public:
	Copy(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif