#include "Save.h"
#include<cstdlib>


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Save::Save(ApplicationManager *pAppManager):Action(pAppManager)
{
	Stat=NULL;
}

void Save::ReadActionParameters()
{
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Saved to <Test.txt> ");
}

void Save::Execute()
{
	ReadActionParameters();
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	ofstream myfile;

	myfile.open("Test.txt");
	myfile<<pManager->GetVarCount()<<endl;
	for(int i=0;i<pManager->GetVarCount();i++)
		myfile<<pManager->GetVariable(i)->name<<"		";
	myfile<<endl<<pManager->GetStatCount()<<endl;
	for(int i=0;i<pManager->GetStatCount();i++)
	{
		Stat=pManager->GetStatList(i);
		Stat->Save(myfile);
	}
	myfile<<pManager->GetConnCount()<<endl;
	for(int i=0;i<pManager->GetConnCount();i++)
	{
		Conn=pManager->GetConnList(i);
		Conn->Save(myfile);
	}
	myfile.close();
	system("Test.txt");
	pManager->setEditedDesign(false);
	
}

