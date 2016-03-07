#include "Start.h"
#include <sstream>
#include "..\ApplicationManager.h"
using namespace std;

Start::Start(Point center)
{

	Center=center;
	StatType="STRT";
	
	pConn = NULL;	//No connectors yet
	height=UI.ASSGN_HI;
	width=UI.ASSGN_WDTH;

	Outlet.x = Center.x ;
	Outlet.y = Center.y + (UI.ASSGN_HI/2);	
}


void Start::setStatConnector(Connector *Conn,int ConnType)
{
pConn=Conn;
}

Connector* Start::getStatConnector(int ConnType)
{
return pConn;
}


void Start::Draw(Output* pOut) const
{
	//Call Output::DrawStart_End function to draw start 	
	Point P;
	P.x=Center.x-(width/2);
	P.y=Center.y-(height/2);
	pOut->DrawStart_End(P,width,height,"START",Selected);
	
}

void Start::Move(Output *pOut,ApplicationManager *pManager)
{
	
window* pWind=pOut->getwindow();
	
    pWind->SetBuffering(true);   
    
    
    bool bDragging = false;

    Point P;
	P.x=0; P.y=0;
    int iXOld = 0;
    int iYOld = 0;
	char cKeyData;
    // Loop until there escape is pressed
    while(pWind->GetKeyPress(cKeyData) != ESCAPE)
    {pOut->PrintMessage("move the statement every where,press ESC to exit"); 
		
        pWind->SetPen(WHITE);    
        pWind->SetBrush(WHITE);
		pWind->DrawRectangle(80, 50,pWind->GetWidth() - 1, pWind->GetHeight() - UI.StBrWdth);          
     
       // Dragging voodoo
        if(bDragging == false) {
            if(pWind->GetButtonState(LEFT_BUTTON, P.x, P.y) == BUTTON_DOWN) {
				if(IsOnStat(P)) {
                   bDragging = true; 
                   iXOld = P.x; iYOld = P.y;
                }
            }
        } else {
            if(pWind->GetButtonState(LEFT_BUTTON, P.x, P.y) == BUTTON_UP) {
                bDragging = false; 
            } else {
                if(P.x != iXOld) {
					if(Center.x + (P.x - iXOld)-UI.ASSGN_WDTH/2>UI.MnItWdth&&Center.x + (P.x - iXOld)+UI.ASSGN_WDTH/2<UI.width)
					{Center.x = Center.x + (P.x - iXOld);
					iXOld = P.x;}
                }
                if(P.y != iYOld) {
					if(Center.y + (P.y - iYOld)-UI.ASSGN_HI/2>UI.TlBrWdth&&Center.y + (P.y - iYOld)+UI.ASSGN_HI/2<UI.height-UI.StBrWdth)
					{Center.y = Center.y + (P.y - iYOld);
					iYOld = P.y;}
                }
            }
        
        }
       
        // Draw rectangle
	
	Outlet.x = Center.x ;
	Outlet.y = Center.y + (UI.ASSGN_HI/2);
	if(pConn!=NULL)
		pConn->setStartPoint(Outlet);
	pManager->EditConnectors(this);
	pManager->UpdateInterface();
		pOut->CreateDesignToolBar();
		
        // Update the screen buffer
        pWind->UpdateBuffer();
 
    }
    
	pWind->SetBuffering(false);
   }

void Start::Resize(char R) 
{
	if(R=='+')
	{
		if(width>=1.5*UI.ASSGN_WDTH)
		return;
	   height*=1.5;
	   width*=1.5;
	   
	   	
    }
	else if(R=='-')
	{
		if(width<=(2.0/3)*UI.ASSGN_WDTH)
		return;
		   height/=1.5;
	       width/=1.5;
	}
  
	
	
	Outlet.x = Center.x ;
	Outlet.y = Center.y + (height/2);	
	   
	if(pConn!=NULL)
		  pConn->setStartPoint(Outlet);


}



bool Start::IsOnStat(Point P)
{
	if(((float)((P.x-Center.x)*(P.x-Center.x))/((UI.ASSGN_WDTH/2)*(UI.ASSGN_WDTH/2))+((float)(P.y-Center.y)*(P.y-Center.y))/((UI.ASSGN_HI/2)*(UI.ASSGN_HI/2)))<=1)
		return true;
	else return false;
}
Point Start::GetConnPoint(int Order,int connType)
{
	return Outlet;
}

void Start::Edit(Output *pOut,Input *pIn)
{

	pOut->PrintMessage("The Start Statement can't be edited");
}

void Start::GenerateCode(ofstream &OutFile)
{
if(Comment!="")
	OutFile<<"#include <iostream>\t// "<<Comment<<endl;
else 
	OutFile<<"#include <iostream>"<<endl;
		
	OutFile<<"using namespace std;"<<endl;
	OutFile<<"int main()"<<endl;
	OutFile<<"{"<<endl;
}

void Start::Save(ofstream &OutFile)
{
	OutFile<<StatType<<"\t"<<ID<<"\t"<<Center.x<<"\t"<<Center.y<<"\t“"<<Comment<<"”"<<endl;
}

void Start::Load(ifstream &Infile)
{
	Infile>>ID>>Center.x>>Center.y;
	getline(Infile,Comment);
	Comment=Comment.substr(Comment.find('“')+1);
	Comment.resize(Comment.size() -1 );
	Outlet.x = Center.x ;
	Outlet.y = Center.y + (UI.ASSGN_HI/2);
}