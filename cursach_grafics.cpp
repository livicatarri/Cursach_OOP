#include <graphics.h>
#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

class coin {
private:
    int X, Y;
    int Sz;
    double Fi;
public:
    coin(int, int, int, double); 
    void SetY(int);
    int GetY();
    void PutFi(double);
    double GetFi();
    void Show();
    void Hide();
    void Slide(int);
    void compress(double);
    void fly(int,double);
};
coin::coin(int X, int Y, int Sz, double Fi) {
    this ->X=X;
    this ->Y=Y;
    this ->Sz=Sz;
    this ->Fi=Fi;
}
int coin ::GetY() { return (Y); }
void coin ::SetY(int Y) { this -> Y=Y; }
double coin ::GetFi() { return (Fi); }
void coin ::PutFi(double Fi) { this -> Fi=Fi; }
void coin ::Show() {
    ellipse(X, Y, 0, 360, Sz, Sz*Fi);
}
void coin::Hide(){
    unsigned TempColor;
    TempColor=getcolor();
    setcolor(getbkcolor()); 
    Show(); 
    setcolor(TempColor); 
}
void coin::Slide(int DY){ 
    Hide(); 
    SetY(Y+DY);
    Show();
}
void coin::compress(double DFi){
   Hide(); 
   PutFi(Fi-DFi);
   Show();
}
void coin::fly(int y, double DF){ 
   compress(DF);
   Slide(y);
}


int main(){
   int gdriver = DETECT, gmode , errorcode;
   initgraph(&gdriver, &gmode, ""); 
   errorcode = graphresult();
   if (errorcode != grOk) {
	  cout<<"Graphics error: "<<grapherrormsg(errorcode)<<endl; cout<<"Press any key to halt:"<<endl;
	  getch();
	  return(1);
   }
   setbkcolor(15);
   setcolor(5);
   double compCoef = 0.1;
   coin t1(100,200,50,1);
   coin t2(320,200,50,1);
   coin t3(560,200,50,1);
   t1.Show();
   t2.Show();
   t3.Show();
   getch();
   int buff = 0;
   double pos = 0;
   while(!kbhit()) {

	  if (t1.GetFi() < 0.0) compCoef = -0.25;
	  if (t1.GetFi() > 1.0) compCoef = 0.25;
	  if (t3.GetFi() < 0.0) compCoef = -0.25;
	  if (t3.GetFi() > 1.0) compCoef = 0.25;
	  pos += 0.1;
    if (pos > 6.2824) pos = 0;
    t1.compress(compCoef);
    t2.Slide(cos(pos)*10);
    t3.fly(cos(pos)*10,compCoef);
    buff = 1 - buff;
      
	  delay(50);
   };
   getch();
   closegraph();
   return(0);
}
