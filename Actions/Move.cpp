#include "Move.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Move::Move(ApplicationManager *pAppManager):Action(pAppManager)
{}

void Move::ReadActionParameters()
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

void Move::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	if(Stat==NULL)
		return;
	
	
		 
	Stat->Move(pOut,pManager);
	
	pManager->setEditedDesign(true);
	pManager->UndoRedo();
}

