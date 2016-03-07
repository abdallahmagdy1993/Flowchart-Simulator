#ifndef DELETE_H
#define DELETE_H
#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class Delete : public Action
{
private:
	Statement *Stat;
	Connector *Conn;
public:
	Delete(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	virtual void Execute() ;

	~Delete();
	
};

#endif