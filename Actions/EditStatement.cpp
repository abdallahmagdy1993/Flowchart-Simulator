#include "EditStatement.h"



#include "..\ApplicationManager.h"
#include "..\Statements\Statement.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
EditStatement::EditStatement(ApplicationManager *pAppManager):Action(pAppManager)
{Stat=NULL;}


void EditStatement::ReadActionParameters()
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
void EditStatement::Execute()
{
		ReadActionParameters();


	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	if(Stat==NULL)
	return;
	if(Stat->GetStatType()=="VAR"||Stat->GetStatType()=="SNGLOP"||Stat->GetStatType()=="COND")
	{
		pManager->deleteVariable(Stat->getVar(0));
		pManager->deleteVariable(Stat->getVar(1));
	}
	else pManager->deleteVariable(Stat->getVar(0));

	Stat->Edit(pOut,pIn);
	if(Stat->GetStatType()=="VAR"||Stat->GetStatType()=="SNGLOP"||Stat->GetStatType()=="COND")
	{
		Variable *V=pManager->AddVariable(Stat->getVar(0));
		if(V)
			Stat->setVar(V,0);
		V=pManager->AddVariable(Stat->getVar(1));
		if(V)
			Stat->setVar(V,1);
	}
	else {
		Variable *V= pManager->AddVariable(Stat->getVar(0));
	if(V)
		Stat->setVar(V,0);
	
	}	
	if(Stat->GetStatType()!="STRT"&&Stat->GetStatType()!="END")
		Stat->PrintInfo(pOut);

	pManager->setEditedDesign(true);
	pManager->UndoRedo();
}

