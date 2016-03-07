#include "End.h"
#include <sstream>
#include "..\ApplicationManager.h"
using namespace std;

End::End(Point center)
{
	Center=center;
	StatType="END";
	
	height=UI.ASSGN_HI;
	width=UI.ASSGN_WDTH;

	Inlet.x = Center.x;
	Inlet.y = Center.y-(UI.ASSGN_HI/2);
	
}


void End::Draw(Output* pOut) const
{
	//Call Output::DrawStart_End function to draw end
	Point P;
	P.x=Center.x-(width/2);
	P.y=Center.y-(height/2);
	pOut->DrawStart_End(P,width,height,"END",Selected);
	
}



void End::setStatConnector(Connector *Conn,int ConnType)
{
return;
}

Connector* End::getStatConnector(int ConnType)
{
return NULL;
}


void End::Move(Output *pOut,ApplicationManager *pManager)
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
		
	Inlet.x = Center.x;
	Inlet.y = Center.y-(UI.ASSGN_HI/2);
	pManager->EditConnectors(this);
	pManager->UpdateInterface();
		
		pOut->CreateDesignToolBar();
		
        // Update the screen buffer
        pWind->UpdateBuffer();
 
    }
    
	pWind->SetBuffering(false);
   
	
	
}

void End::Resize(char R) 
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
  
	
	
	Inlet.x = Center.x ;
	Inlet.y = Center.y - (height/2);	

}
bool End::IsOnStat(Point P)
{
	if(((float)((P.x-Center.x)*(P.x-Center.x))/((UI.ASSGN_WDTH/2)*(UI.ASSGN_WDTH/2))+((float)(P.y-Center.y)*(P.y-Center.y))/((UI.ASSGN_HI/2)*(UI.ASSGN_HI/2)))<=1)
		return true;
	else return false;
}
Point End::GetConnPoint(int Order,int connType)
{
	return Inlet;
}

void End::Edit(Output *pOut,Input *pIn)
{

	pOut->PrintMessage("The End Statement can't be edited");
}

void End::GenerateCode(ofstream &OutFile)
{if(Comment!="")

	OutFile<<"return 0;\t// "<<Comment<<endl;
else

	OutFile<<"return 0;"<<endl;
	OutFile<<"}"<<endl;
}

void End::Save(ofstream &OutFile)
{
	OutFile<<StatType<<"\t"<<ID<<"\t"<<Center.x<<"\t"<<Center.y<<"\t“"<<Comment<<"”"<<endl;
}

void End::Load(ifstream &Infile)
{
	Infile>>ID>>Center.x>>Center.y;
	getline(Infile,Comment);
	Comment=Comment.substr(Comment.find('“')+1);
	Comment.resize(Comment.size() -1 );
	Inlet.x = Center.x ;
	Inlet.y = Center.y - (UI.ASSGN_HI/2);
}

