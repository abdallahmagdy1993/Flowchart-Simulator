#include "Copy.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Copy::Copy(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;}

void Copy::ReadActionParameters()
{
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Stat=pManager->GetSelectedStatement();
	if(Stat==NULL)
	{
		pOut->PrintMessage("no selected Statement");
		return;
	}
	else if(Stat->GetStatType()=="STRT"||Stat->GetStatType()=="END")
	{
		Stat=NULL;
		pOut->PrintMessage("Cannot copy this statement");
		return;
	}
	
}

void Copy::Execute()
{
	ReadActionParameters();


	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if(Stat==NULL)
	return;
	pManager->SetCopyType(1);
	pManager->SetCopied(Stat);
	pOut->PrintMessage("Statement is Copied ");
	
	
}

