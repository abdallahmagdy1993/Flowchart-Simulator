#ifndef RESIZE_H
#define RESIZE_H

#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"



class Resize : public Action
{
private:
	string type;	//Position where the user clicks to add the stat.
	Statement* Stat;
public:
	Resize(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif