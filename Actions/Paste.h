#ifndef PASTE_H
#define PASTE_H

#include "Copy.h"
#include "Action.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"

class Paste : public Action 
{
private:
	Point Position;	//Position where the user clicks to add the stat.
	Statement *Stat;
public:
	Paste(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif