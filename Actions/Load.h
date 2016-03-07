#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class Load : public Action
{
private:
	Statement *Stat;
	Connector *Conn;
	Variable *V;
public:
	Load(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif