#ifndef ZOOM_H
#define ZOOM_H

#include "..\Statements\Statement.h"
#include "..\ApplicationManager.h"
#include "Action.h"



class Zoom : public Action
{
private:
	char type;	//Position where the user clicks to add the stat.
	//static int G;
	image i;
	Point Position;
public:
	Zoom(ApplicationManager *pAppManager,char c);
	
	//static void setG(int n);
	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif