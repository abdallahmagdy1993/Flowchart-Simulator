#include "Load.h"
#include "AddSmplAssign.h"
#include "AddVarAssign.h"
#include "AddSOAssign.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddRead.h"
#include "AddWrite.h"
#include "AddCondition.h"
#include "AddConnector.h"
#include "EditConnector.h"
#include "EditStatement.h"
#include "AddComment.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Load::Load(ApplicationManager *pAppManager):Action(pAppManager)
{
	Stat=NULL;
	Conn=NULL;
	V=NULL;
}

void Load::ReadActionParameters()
{
	
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("Load From <Test.txt> ");
}

void Load::Execute()
{
	ReadActionParameters();
	string line,S;
	int x,y,z;
	Point P; P.x=200; P.y=200;
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	while(pManager->GetStatList(0))
		pManager->DeleteStat(pManager->GetStatList(0));
	ifstream myfile("Test.txt");
	if (myfile.is_open())
	{
		myfile>>x;
		for(int i=0;i<x;i++)
		{
			V=new Variable;
			myfile>>V->name;
			pManager->AddVariable(V);
		}
		myfile>>y;
		if(y==0)
			return;
		else
		{
			for(int j=0;j<y;j++)
			{
				myfile>>line;
				if(line=="STRT")
				{
					Stat=new Start(P);
				}
				else if(line=="COND")
				{
					Stat=new Condition(P);
				}
				else if(line=="END")
				{
					Stat=new End(P);
				}
				else if(line=="SMPL")
				{
					Stat=new SmplAssign(P);
				}
				else if(line=="READ")
				{
					Stat=new Read(P);
				}
				else if(line=="WRITE")
				{
					Stat=new Write(P);
				}
				else if(line=="SNGLOP")
				{
					Stat=new SOAssign(P);
				}
				else if(line=="VAR")
				{
					Stat=new VarAssign(P);
				}
				Stat->Load(myfile);
				pManager->AddStatement(Stat);
			}
			myfile>>z;
			for(int i=0;i<z;i++)
			{
				Conn=new Connector(NULL,NULL);
				Conn->Load(myfile);
				pManager->SetConnector(Conn);
			}
			pManager->LoadModify();
		}
    myfile.close();
	}
	pManager->UpdateInterface();
	pManager->setEditedDesign(false);
	pManager->UndoRedo();
}

