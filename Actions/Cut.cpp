#include "Cut.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Cut::Cut(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;}

void Cut::ReadActionParameters()
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

void Cut::Execute()
{
	ReadActionParameters();


	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if(Stat==NULL)
	return;
	pManager->SetCopyType(2);

	pManager->SetCopied(Stat);
	pOut->PrintMessage("Statement is Cut ");

	
	pManager->DeleteStat(Stat);
	
	pManager->setEditedDesign(true);
	pManager->UndoRedo();
}

