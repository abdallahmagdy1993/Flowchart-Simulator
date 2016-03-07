#include "Paste.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Paste::Paste(ApplicationManager *pAppManager):Action(pAppManager)
{
	Stat=NULL;

}

void Paste::ReadActionParameters()
{
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pManager->UnSelect();
	
	Stat=pManager->GetCopied();
	if(Stat==NULL)
	{
		pOut->PrintMessage("no Statement to paste");
		return;
	}
	pOut->PrintMessage("Click Anywhere to add the statement");

	pIn->GetPointClicked(Position);
	if(pManager->onBars(Position)||pManager->onObject(Position))
		return;
	
	
	pOut->ClearStatusBar();		
	
}

void Paste::Execute()
{
	ReadActionParameters();
	
	if(pManager->onBars(Position)||pManager->onObject(Position))
		return;
	
	
	if(Stat==NULL)
	{
	return;
	}
	Statement *pStat=Stat->Copy(Position);
	pManager->AddStatement(pStat);
	
	if(pStat->GetStatType()=="VAR"||pStat->GetStatType()=="SNGLOP")
	{
		pManager->AddVariable(pStat->getVar(0));
		pManager->AddVariable(pStat->getVar(1));
	}
	else pManager->AddVariable(pStat->getVar(0));
	

	if(pManager->GetCopyType()==2)
		pManager->SetCopied(NULL);
	pManager->setEditedDesign(true);
	pManager->UndoRedo();
}

