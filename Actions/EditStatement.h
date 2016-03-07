#ifndef EDIT_STATEMENT_H
#define EDIT_STATEMENT_H

#include "EditStatement.h"
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class EditStatement : public Action
{
private:
	Statement *Stat;
public:
	EditStatement(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif