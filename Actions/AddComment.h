#ifndef ADD_COMMENT_H
#define ADD_COMMENT_H
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class AddComment : public Action
{
private:
	Statement *Stat;
public:
	AddComment(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	
};

#endif