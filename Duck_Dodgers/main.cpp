#include <iostream>
#include<string>
#include "queue.h"
#include "linearList.h"

using namespace std;

struct HexCoordinate
{
    int row, col;
    HexCoordinate(int row, int col) : row(row), col(col) {}
    HexCoordinate() {
      row = 0;
      col = 0;
    }
    bool isEven;
    int distance;
    bool isLava;
};

const int ROWS = 20 , COLS = 20;
int mapSize = 20;
int dC[] = {0,1,1,0,-1,-1};
int dREven[] =  {-1,-1,0,1,0,-1};
int dROdd[] =  {-1,0,1,1,1,0};
int *dR;
HexCoordinate hexMap[ROWS][COLS];
Queue <HexCoordinate> hexQueue;

int start_DuckX, start_DuckY;
int start_MarvinX, start_MarvinY;
int start_PhosdexX, start_PhosdexY;

HexCoordinate Lava;
int numOfLava;

LinearList<HexCoordinate> lavaCells;
LinearList<HexCoordinate> duckPath;
LinearList<HexCoordinate> marvinPath;
LinearList<HexCoordinate> oldMarvinPath;
LinearList<HexCoordinate> marvinPathNew;
LinearList<HexCoordinate> gandalfCell;
void GetInput()
{
    cin >> start_DuckX >> start_DuckY;
    cin >> start_MarvinX >> start_MarvinY;
    cin >> start_PhosdexX >> start_PhosdexY;
    cin >> numOfLava;

    for(int i = 0; i <= numOfLava - 1; i++)
    {
        int row, col;
        cin >> row >> col;
        hexMap[row][col].isLava = true;
        lavaCells.insert(i,HexCoordinate(row,col));
        
        
    }
}
void GenerateMap()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            hexMap[i][j].row = i;
            hexMap[i][j].col = j;
            hexMap[i][j].isEven = true;
            hexMap[i][j].distance = -1;
            hexMap[i][j].isLava = false;
            if (i % 2 == 0)
                hexMap[i][j].isEven = true;
            else
                hexMap[i][j].isEven = false;
        }

}

    int lavaCellsCount = lavaCells.size();
    for(int i = 0; i < lavaCellsCount; i++) 
    {
       Lava = lavaCells[i];
      hexMap[Lava.row][Lava.col].distance = -2;
    }
    for(int i = 0; i < gandalfCell.size(); i++) {
      HexCoordinate Gandalf = gandalfCell[i];
      hexMap[Gandalf.row][Gandalf.col].distance = -2;
    }

    hexMap[start_PhosdexX][start_PhosdexY].distance = 0;
}


void PrintBoardDistances()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j= 0; j < COLS; j++)
        {
            cout << hexMap[i][j].distance << " ";
        }
        cout << endl;
    }
}
void BreadthFirstSearch(int startX, int startY)
{
    hexQueue.clear();
    hexMap[startX][startY].distance = 0;

    hexQueue.enqueue(hexMap[startX][startY]);
    while(!hexQueue.isEmpty())
    {
        HexCoordinate front = hexQueue.dequeue();
        if (front.col >= 1)
        {
               HexCoordinate top = hexMap[front.row][front.col-1];
            	 if (top.distance == -1)
			         {
			             //cout << "TOP: " << top.row << " " << top.col <<  endl;
			             hexMap[top.row][top.col].distance = front.distance + 1;
			             hexQueue.enqueue(hexMap[top.row][top.col]);
			         }
                
           
        }

        // Process Top-right neighbor
        if( (!front.isEven && front.row < ROWS-1) || (front.isEven && front.col > 0))
        {

               HexCoordinate topRight;
               if(front.isEven)
                   topRight = hexMap[front.row+1][front.col-1];
               else
                   topRight = hexMap[front.row+1][front.col];
               	   if(topRight.distance == -1)
	               {
	                   //cout << "TOP Right: " << topRight.row << " " << topRight.col <<  endl;
	                   hexMap[topRight.row][topRight.col].distance = front.distance + 1;
	                   hexQueue.enqueue(hexMap[topRight.row][topRight.col]);
	               }
               
               
		 }

        //Process Bottom Right neighbor
        if((!front.isEven && front.row < ROWS-1 && front.col < COLS-1) || (front.isEven))
        {
        	
	             HexCoordinate BottomRight;
	             if(front.isEven)
	                 BottomRight = hexMap[front.row+1][front.col];
	             else
	                 BottomRight = hexMap[front.row+1][front.col+1];
	             	 if(BottomRight.distance == -1)
		             {
		                 hexMap[BottomRight.row][BottomRight.col].distance = front.distance + 1;
		                 hexQueue.enqueue(hexMap[BottomRight.row][BottomRight.col]);
		             }

	             
	             	         	
        }
        //Process Bottom neighbor
        if(front.col < COLS -1)
        {
           
	             HexCoordinate Bottom = hexMap[front.row][front.col+1];

	             	if(Bottom.distance == -1)
	             	{
	 
	                 //cout << "BOTTOM: " << Bottom.row << " " << Bottom.col <<  endl;
	                 hexMap[Bottom.row][Bottom.col].distance = front.distance + 1;
	                 hexQueue.enqueue(hexMap[Bottom.row][Bottom.col]);
	            	 }

	         
        }

        //Process Bottom-Left neighbor
        if( (front.isEven && front.row > 0) || (!front.isEven && front.col < COLS-1) )
        {
               HexCoordinate BottomLeft;
               if(front.isEven)
                   BottomLeft = hexMap[front.row - 1][front.col];
               else
                   BottomLeft = hexMap[front.row - 1][front.col + 1];

               		if(BottomLeft.distance == -1)
	                {
	                   //cout << "BOTTOM-LEFT: " << BottomLeft.row << " " << BottomLeft.col <<  endl;
	                   hexMap[BottomLeft.row][BottomLeft.col].distance = front.distance + 1;
	                   hexQueue.enqueue(hexMap[BottomLeft.row][BottomLeft.col]);
	                }

              
		  }

        //Process Top-Left neighbor
        if( (front.isEven && front.row > 0 && front.col > 0) || (!front.isEven)  ) 
        {
        	
   				//cout << "Looking at top left" << endl;
               HexCoordinate TopLeft;
               if(front.isEven)
                   TopLeft = hexMap[front.row - 1][front.col - 1];
               else
                   TopLeft = hexMap[front.row -1][front.col];
               	 if(TopLeft.distance == -1) 
               	 {
                   //cout << "TOP-LEFT: " << TopLeft.row << " " << TopLeft.col <<  endl;
                   hexMap[TopLeft.row][TopLeft.col].distance = front.distance + 1;
                   hexQueue.enqueue(hexMap[TopLeft.row][TopLeft.col]);
                 
			           }
         }
     }
  }
void ShortestPath(int &startX, int &startY, LinearList<HexCoordinate> &hexList) {
  int end = 0;
  hexList.insert(end,HexCoordinate(startX,startY));
  end += 1;
	HexCoordinate currentCell = hexMap[startX][startY];
	while(currentCell.distance != 0) {
		if(currentCell.row % 2 == 1) 
			dR = dROdd;
		else 
			dR = dREven;
	  for(int i = 0; i < 6; i++) 
	  {
	     	 int nR, nC;
			   nR = currentCell.row + dC[i];
			   nC = currentCell.col + dR[i];
         HexCoordinate nextCell = hexMap[nR][nC];
			   if(hexMap[nR][nC].distance == (currentCell.distance - 1) && nextCell.distance != -2) {
            hexList.insert(end, HexCoordinate(nR,nC));
            end += 1;
				   	currentCell = nextCell;
				   	break;
			   }	  		 
	  }	
	  
  }
 //hexList.insert(end,currentCell);

}



int main() {
    GetInput();
    GenerateMap(); 
    BreadthFirstSearch(start_PhosdexX,start_PhosdexY);
    ShortestPath(start_DuckX,start_DuckY,duckPath);
    ShortestPath(start_MarvinX,start_MarvinY,marvinPath);
    PrintBoardDistances();
    string winner;
    if(duckPath.size() == 1 && marvinPath.size() == 1) 
      cout<<"Nobody can reach the Illudium Phosdex" << endl;
    else if(duckPath.size() == 1)
      cout << "Duck Dodgers cannot reach the Illudium Phosdex." << endl;
    else if(marvinPath.size() == 1)
      cout << "Marvin the Martian cannot reach the Illudium Phosdex." << endl;
    else if(duckPath.size() == marvinPath.size())
        cout << "Duck and Marvin reaches the Illudium Phosdex simultaneously" << endl;
    else {
      if(duckPath.size() != marvinPath.size())
        winner = marvinPath.size() > duckPath.size() ? "Duck Dodgers" : "Marvin the Martian";
      else
        winner = "Marvin the Martian";
      cout << winner << " reaches the Illudium Phosdex First." << endl;
      if(winner == "Marvin the Martian")
      {
        oldMarvinPath = marvinPath;
        bool solutionFound = false;
        for(int i = 0; i < oldMarvinPath.size(); i++) {
          gandalfCell.insert(i,HexCoordinate(marvinPath[i].row,marvinPath[i].col));
          cout << gandalfCell[i].row << ", " << gandalfCell[i].col << endl;
        }

          GenerateMap();
          BreadthFirstSearch(start_PhosdexX,start_PhosdexY);
          duckPath.clear();
          marvinPathNew.clear();
          PrintBoardDistances();
          //
          cout <<"TEST"<<endl;
          ShortestPath(start_DuckX,start_DuckY,duckPath);
          ShortestPath(start_MarvinX,start_MarvinY,marvinPathNew);
          cout <<"TEST"<<endl;
         if(solutionFound == false) {
          cout<< "Gandalf cannot Help" << endl;
         }
        
      }
    }
   return 0;
}







