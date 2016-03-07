#ifndef ADD_READ_H
#define ADD_READ_H

#include "Action.h"
#include "..\Statements\Read.h"

class AddRead : public Action
{
private:
	Point Position;	//Position where the user clicks to add the stat.
public:
	AddRead(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	
	virtual void Execute() ;
	
};

#endif