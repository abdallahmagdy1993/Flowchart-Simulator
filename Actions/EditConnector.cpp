#include "EditConnector.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
EditConnector::EditConnector(ApplicationManager *pAppManager):Action(pAppManager)
{ConnType=0;}

void EditConnector::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	bool exit=false;

	Conn=pManager->GetSelectedSConnector();
	if(Conn==NULL)
		{
			pOut->PrintMessage("no selected Connector");
			return;
		}
	
	if(Conn->getSrcStat()->GetStatType()=="COND")
		{if(Conn->getSrcStat()->getStatConnector(1)==Conn)
			Conn->getSrcStat()->setStatConnector(NULL,1);
		else if(Conn->getSrcStat()->getStatConnector(2)==Conn)
			Conn->getSrcStat()->setStatConnector(NULL,2);
		}
	else Conn->getSrcStat()->setStatConnector(NULL,0);
	
	
	exit=false;
	while(!exit)
		{
			pOut->PrintMessage("Click on the new first statement");
			pIn->GetPointClicked(Position);
			if(pManager->onBars(Position))
			{pOut->ClearStatusBar(); return;}

			SrcStat=pManager->GetStatement(Position);
			
			if(SrcStat!=NULL)
				exit=true;
			else continue;	
			
			if(SrcStat->GetStatType()=="END")
			{exit=false; continue;}
			

			SrcStat->SetSelected(true);
			pManager->UpdateInterface();
			
					
			if(SrcStat->GetStatType()=="COND")
			{
				again:
				pOut->DrawCondMsg();
				Point P;
				pIn->GetPointClicked(P);
					if(P.x>=531.66&&P.x<=615.38&&P.y>=349.38&&P.y<=378.63)		//true button
						{
							if(SrcStat->getStatConnector(1)!=NULL)
								{
									exit=false;	
									SrcStat->SetSelected(false);
									pManager->UpdateInterface();
									continue;
								}
							pManager->UpdateInterface();
							Start=SrcStat->GetConnPoint(1,1);
							ConnType=1;
						}
					else if(P.x>=411.28&&P.x<=495.72&&P.y>=349.66&&P.y<=378.91)	//false button
						{
							if(SrcStat->getStatConnector(2)!=NULL)
								{
									exit=false;	
									SrcStat->SetSelected(false);
									pManager->UpdateInterface();
									continue;
								}
							pManager->UpdateInterface();
							Start=SrcStat->GetConnPoint(1,2);
							ConnType=2;
						}
					else goto again;
				}
			
			else
			{
					if(SrcStat->getStatConnector(0)!=NULL)
								{
									exit=false;	
									SrcStat->SetSelected(false);
									pManager->UpdateInterface();
									continue;
								}
			
				
				
				Start=SrcStat->GetConnPoint(1);}
	
		}

	exit =false;
	while(!exit)
		{
			pOut->PrintMessage("Click on the new second statement");
			pIn->GetPointClicked(Position);
			if(pManager->onBars(Position))
			{
			pOut->ClearStatusBar(); 
			SrcStat->SetSelected(0);
			return;
			}

			DstStat=pManager->GetStatement(Position);
	
			if(DstStat!=NULL)
				exit=true;
			else continue;
			
			if(DstStat->GetStatType()=="STRT")
			{exit=false; continue;}
			
			End=DstStat->GetConnPoint(2);
			
		}

SrcStat->SetSelected(false);
pOut->ClearStatusBar();

}

void EditConnector::Execute()
{
	ReadActionParameters();
	if(pManager->onBars(Position))
			return;
	
	if(Conn==NULL)
		return;
	Conn->setSrcStat(SrcStat);
	Conn->setDstStat(DstStat);
	Conn->setStartPoint(Start);
	Conn->setEndPoint(End);
	Conn->setSrcID(SrcStat->GetID());
	Conn->setDstID(DstStat->GetID());
	Conn->setConnType(ConnType);

	
	SrcStat->setStatConnector(Conn,ConnType);
	pManager->setEditedDesign(true);

	pManager->UndoRedo();
}

