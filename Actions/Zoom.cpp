#include "Zoom.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

#include <sstream>

using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Zoom::Zoom(ApplicationManager *pAppManager,char c):Action(pAppManager)
{
	type=c;
}

void Zoom::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	if(type=='+')
	pOut->PrintMessage("Please Click in the area that you want to zoom in");
	else if(type=='-')
	pOut->PrintMessage("Please Click in the area that you want to zoom out");
	pIn->GetPointClicked(Position);	
	pOut->ClearStatusBar();		
}

void Zoom::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	ReadActionParameters();
	Point P1,P2,P3,P4;
	bool b1=false,b2=false;
	if(type=='+')
	{
	if((Position.x>UI.MnItWdth&&Position.x<UI.width)&&(Position.y>UI.TlBrWdth&&Position.y<(UI.height)/2))
	{
		P1.x=UI.MnItWdth;
	P1.y=UI.TlBrWdth;
	P2.x=UI.width-P1.x;
	P2.y=(UI.height/2)-P1.y;
	b1=true;
	}
	else if((Position.x>UI.MnItWdth&&Position.x<UI.width)&&((Position.y>(UI.height)/2)&&Position.y<(UI.height-UI.StBrWdth)))
	{
		P1.x=UI.MnItWdth;
	P1.y=(UI.height)/2;
	P2.x=UI.width-P1.x;
	P2.y=(UI.height/2)-UI.StBrWdth;
	b1=true;
	}
	
	}
	else if(type=='-')
	{
		if((Position.x>UI.MnItWdth&&Position.x<UI.width)&&((Position.y>(UI.TlBrWdth)&&Position.y<(UI.height-UI.StBrWdth))))
		{
			P1.x=UI.MnItWdth;
			P1.y=UI.TlBrWdth;
			P2.x=UI.width-P1.x;
			P2.y=UI.height-UI.TlBrWdth-UI.StBrWdth;
			b2=true;
		}
		
	}

	if(type=='+' && b1)
	{
	P3.x=UI.MnItWdth,P3.y=UI.TlBrWdth,P4.x=UI.width-UI.MnItWdth,P4.y=UI.height-UI.StBrWdth-UI.TlBrWdth;
	pOut->DrawImage(&(pIn->StoreImage(i,P1,P2)),P3,P4);
	}
	else if(type=='-' && b2)
	{
	P3.x=UI.MnItWdth,P3.y=UI.TlBrWdth,P4.x=UI.width-UI.MnItWdth-100,P4.y=UI.height-UI.StBrWdth-UI.TlBrWdth-100;
	pOut->DrawImage(&(pIn->StoreImage(i,P1,P2)),P3,P4);
	}
}
//void Zoom::setG(int n)
//{
//	G=n;
//}