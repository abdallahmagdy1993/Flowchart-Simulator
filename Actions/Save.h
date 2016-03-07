#ifndef SAVE_H
#define SAVE_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class Save : public Action
{
private:
	Statement *Stat;
	Connector *Conn;
public:
	Save(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif