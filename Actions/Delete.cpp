#include "Delete.h"



#include "..\ApplicationManager.h"
#include "..\Statements\Statement.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Delete::Delete(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;
Conn = NULL;}

Delete::~Delete()
{
};



void Delete::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	Stat=pManager->GetSelectedStatement();
	Conn=pManager->GetSelectedSConnector();

	if(Stat==NULL && Conn == NULL)
		{
			pOut->PrintMessage("No selection! Please select the statement or connector you want to delete");
			return;
		}
}


void Delete::Execute()
{
	ReadActionParameters();

	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	if(Stat==NULL && Conn == NULL)	return;

	if (Stat != NULL) {
	
		pManager->DeleteStat (Stat);
		Stat = NULL;
		pOut->PrintMessage("the statement is deleted");
	}
	
	if (Conn != NULL) {
		pManager->DeleteConn (Conn);
		Conn = NULL;
		pOut->PrintMessage("the connector is deleted");
	}

	
	pManager->UnSelect();

pManager->setEditedDesign(true);	
pManager->UndoRedo();
}