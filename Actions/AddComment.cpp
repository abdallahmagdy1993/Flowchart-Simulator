#include "AddComment.h"



#include "..\ApplicationManager.h"
#include "..\Statements\Statement.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddComment::AddComment(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;}


void AddComment::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	Stat=pManager->GetSelectedStatement();
	if(Stat==NULL)
		{
			pOut->PrintMessage("no selected Statement");
			return;
		}
	

}
void AddComment::Execute()
{
	ReadActionParameters();


	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	if(Stat==NULL)	return;

	pOut->PrintMessage("enter the statement comment");
	
	
	Stat->AddComment(pIn->GetString(pOut,Stat->GetComment()));
	
	pManager->setEditedDesign(true);
	pManager->UndoRedo();
	pOut->ClearStatusBar();
	Stat->PrintInfo(pOut);
	
}

