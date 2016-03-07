#include "Resize.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Resize::Resize(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;}

void Resize::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	Stat=pManager->GetSelectedStatement();
	if(Stat==NULL)
		{
			pOut->PrintMessage("no selected Statement");
			return;
		}
	
	while(1)
	{
	pOut->PrintMessage("pleaze enter '+' to zoom in or enter '-' to zoom out");
	type=pIn->GetString(pOut);
	if(type=="+"||type=="-")
		break;
	}
	pOut->ClearStatusBar();		
}

void Resize::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	ReadActionParameters();
	if(Stat==NULL)
	return;
	
	Stat->Resize(type[0]);
	pManager->EditConnectors(Stat);
	Stat->PrintInfo(pOut);
	pManager->setEditedDesign(true);
	pManager->UndoRedo();
}

