#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include <windows.h>
#include <Windows.h>
#include <MMSystem.h>
#include <mmsystem.h>
//#pragma comment(lib,"Winmm.lib")

using namespace std;
#define H 83
#define W 83
enum direction { UP, DOWN, LEFT, RIGHT };


//void music()
//{
//	// Load a music file
//	sf::Music music;
//	if (!music.openFromFile("music.ogg"))
//		return 1;
//
//	// Play the music
//	music.play();
//
//	// Run the program as long as the music is playing
//	while (music.getStatus() == sf::Music::Playing)
//	{
//		// Do other things here, such as handle events or update the game state
//	}
//
//	
//}


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position {
	int ri, ci;
};
struct snake {

	position* p;
	int size, score=0,color;
	char sym;
	direction dir;
	int lKey, rKey, uKey, dKey;
	string name;
	bool kill = false;


};
struct food {
	position fp;
	
	char sym;
};
struct stg
{
	position si;
	position ei;


};
struct Stges {
	stg* stage;
	int size;
};
Stges Stage(const string a)
{
	ifstream rdr(a);
	Stges stage{};

	rdr >> stage.size;
	stage.stage = new stg[stage.size];
	for (int i = 0; i < stage.size; i++)
	{
		rdr >> stage.stage[i].si.ri;
		rdr >> stage.stage[i].ei.ri;
		rdr >> stage.stage[i].si.ci;
		rdr >> stage.stage[i].ei.ci;

	}
	return stage;
}
bool isLegalCord(food f, snake& s)
{
	for (int i = 0; i < s.size; i++)
	{
		if ((s.p[i].ri == f.fp.ri && s.p[i].ci == f.fp.ci) )
		{
			return false;
		}

	}
	return true;
}
void generatefood(food& fd, snake*& s,int size, Stges hurdle)
{
	for (int i = 0; i < size; i++) {
		//for (int j = 0; j < hurdle.size; j++) {
			do {
				fd.fp.ri = (rand() % (H - 1)) + 1;
				fd.fp.ci = (rand() % (W - 1)) + 1;
			} while (!isLegalCord(fd, s[i]));//,hurdle.stage[j]));
		//}
	}
	

}
void displayfood(food f)
{
	SetClr(2);
	gotoRowCol(f.fp.ri, f.fp.ci);
	cout << f.sym;
	

}
void undisplayfood(food f)
{
	SetClr(2);
	gotoRowCol(f.fp.ri, f.fp.ci);
	cout << " ";


}
void init(snake* & s, food& f,int size, Stges hurdle)
{
	s = new snake[size];
	for (int i = 0; i < size; i++)
	{
		s[i].p = new position[3];
	}
	for (int i = 0; i < size; i++)
	{
		
		if (i == 0)
		{
			s[0].p[0].ri = H / 2;
			s[0].p[0].ci = W / 2+3;
			s[0].p[1].ri = H / 2;
			s[0].p[1].ci = W / 2 +2;
			s[0].p[2].ri = H / 2;
			s[0].p[2].ci = W / 2 +1;
			s[0].size = 3;
			s[0].score = 0;
			s[0].sym = -37;
			s[0].name = "Player 1";
			s[0].dir = RIGHT;
			s[0].rKey = 77;
			s[0].lKey = 75;
			s[0].uKey = 72;
			s[0].dKey = 80;
			s[0].color = 4;

		}
		if (i == 1)
		{
			s[1].p[0].ri = H / 2;
			s[1].p[0].ci = W / 2-3;
			s[1].p[1].ri = H / 2;
			s[1].p[1].ci = W / 2 - 2;
			s[1].p[2].ri = H / 2;
			s[1].p[2].ci = W / 2 - 1;
			s[1].size = 3;
			s[1].score = 0;
			s[1].sym = -37;
			s[1].name = "Player 2";
			s[1].dir = LEFT;
			s[1].rKey = 115;
			s[1].lKey = 97;
			s[1].uKey = 119;
			s[1].dKey = 122;
			s[1].color = 5;
		}
		if (i == 2)
		{
			s[i].p[0].ri = H / 2-3;
			s[2].p[0].ci = W / 2;
			s[2].p[1].ri = H / 2-2;
			s[2].p[1].ci = W / 2;
			s[2].p[2].ri = H / 2-1;
			s[2].p[2].ci = W / 2;
			s[2].size = 3;
			s[2].score = 0;
			s[2].sym = -37;
			s[2].name = "Player 3";
			s[2].dir = UP;
			s[2].rKey = 103;
			s[2].lKey = 102;
			s[2].uKey = 116;
			s[2].dKey = 118;
			s[2].color = 6;
		}
		if (i == 3)
		{
			s[3].p[0].ri = H / 2 + 3;
			s[3].p[0].ci = W / 2;
			s[3].p[1].ri = H / 2 + 2;
			s[3].p[1].ci = W / 2;
			s[3].p[2].ri = H / 2 + 1;
			s[3].p[2].ci = W / 2;
			s[3].size = 3;
			s[3].score = 0;
			s[3].sym = -37;
			s[3].name = "Player 4";
			s[3].dir = DOWN;
			s[3].rKey = 107;
			s[3].lKey = 106;
			s[3].uKey = 105;
			s[3].dKey = 109;
			s[3].color = 7;
		}

	}
	
	
	generatefood(f, s,size,hurdle);
	f.sym = '@';

}
void displaySnake(snake* s,int size)
{
	//int j = 0;
	for (int j = 0; j < size; j++) {
		gotoRowCol(j, W + 1);
		cout << s[j].name<< "'s score:" << s[j].score;
		for (int i = 0; i < s[j].size; i++)
		{
			if (s[j].kill) {
				gotoRowCol(j, W + 1);
				cout << s[j].name << "'s score:" << s[j].score<<"(DEAD!)";
				continue;

			}

			gotoRowCol(s[j].p[i].ri, s[j].p[i].ci);
			SetClr(s[j].color);
			//SetClr(4);
			if (i == 0) {
				cout << '*';
			}
			else {
				cout << "O"; //s[j].sym;
			}
		}
	}
	
	


}
void undisplaySnake(snake*s,int size)
{
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < s[j].size; i++)
		{
			if (s[j].kill) {
				continue;

			}

			gotoRowCol(s[j].p[i].ri, s[j].p[i].ci);
			cout << " ";
		}
	}
}
void movesnake(snake *& s,int size)
{
	for (int j = 0; j < size; j++) {
		if (s[j].kill)
		{
			continue;
		}
		for (int i = s[j].size - 1; i >= 1; i--)
		{
			s[j].p[i] = s[j].p[i - 1];
		}
		switch (s[j].dir)
		{
		case UP:

			s[j].p[0].ri--;
			if (s[j].p[0].ri == 0)
			{
				s[j].p[0].ri = H - 1;
			}
			break;
		case DOWN:
			s[j].p[0].ri++;
			if (s[j].p[0].ri == H)
			{
				s[j].p[0].ri = 1;
			}
			break;
		case RIGHT:
			s[j].p[0].ci++;
			if (s[j].p[0].ci == W)
			{
				s[j].p[0].ci = 1;
			}
			break;
		case LEFT:
			s[j].p[0].ci--;
			if (s[j].p[0].ci == 0)
			{
				s[j].p[0].ci = W -1;
			}
		}
	}
}
void changedir(snake *& s, char key,int size)
{
	for (int i = 0; i < size; i++)
	{
		if (s[i].kill)
		{
			continue;
		}
		if (key == s[i].lKey)
		{
			if (s[i].dir != RIGHT)
			{
				s[i].dir = LEFT;
			}
		}
		if (key == s[i].rKey) {
			if (s[i].dir != LEFT)
			{
				s[i].dir = RIGHT;
			}
		}
		if (key == s[i].uKey) {
			if (s[i].dir != DOWN)
			{
				s[i].dir = UP;
			}
		}
		if (key == s[i].dKey) {
			if (s[i].dir != UP)
			{
				s[i].dir = DOWN;
			}
		}
	}


}
void expandsnake(snake& s)
{
	position* p = new position[s.size + 1];
	for (int i = 0; i < s.size; i++)
	{
		p[i] = s.p[i];
	}
	p[s.size] = s.p[s.size - 1];
	s.size++;
	delete[]s.p;
	s.p = p;
}
bool foodeaten(snake *&s, food f,int size)
{
	for (int i = 0; i < size; i++) {
		if (s[i].p[0].ri == f.fp.ri && s[i].p[0].ci == f.fp.ci)
		{
			PlaySound(TEXT("eatt"), NULL, SND_ASYNC);
			expandsnake(s[i]);
			s[i].score++;
			
			return true;
		}
	}
	return false;

}

void drawstage(Stges hurdle)
{
	for (int i = 0; i < hurdle.size; i++)
	{
		for (int j = hurdle.stage[i].si.ci; j < hurdle.stage[i].ei.ci; j++)
		{
			SetClr(12);
			gotoRowCol(hurdle.stage[i].si.ri, j);
			cout << char(-37);
		}
		for (int j = hurdle.stage[i].si.ri; j < hurdle.stage[i].ei.ri; j++)
		{
			SetClr(12);
			gotoRowCol(j,hurdle.stage[i].si.ci);
			cout << char(-37);
		}
		

	}
}
void drawBound()
{
	for (int i = 0; i < H; i++)
	{
		gotoRowCol(i, 0);
		SetClr(8);
		cout << char(-37);
	}
	for (int i = 0; i <= H; i++)
	{
		gotoRowCol(i, W);
		SetClr(8);
		cout << char(-37);
	}
	for (int i = 0; i < W; i++)
	{
		gotoRowCol(0, i);
		SetClr(8);
		cout << char(-37);
	}

	for (int i = 0; i < W; i++)
	{
		gotoRowCol(W, i);
		SetClr(8);
		cout << char(-37);
	}



}
void killcheck(snake *&s,int size,Stges hurdle)
{
	int count = 0;
	for (int j = 0; j < size; j++)
	{

		for (int i = s[j].size; i > 0; i--)
		{
			if (s[j].kill)
			{
				count++;
				continue;
			}
			if (s[j].p[0].ci == s[j].p[i].ci && s[j].p[0].ri == s[j].p[i].ri)
			{
				delete[]s[j].p;
				//s[j].p = nullptr;
				s[j].kill = true;
				PlaySound(TEXT("kill"), NULL, SND_ASYNC);
				
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (s[i].kill)
		{
			count++;
			continue;
		}
		for (int j = 0; j < size; j++)
		{
			if (s[j].kill)
			{
				count++;
				continue;
			}
			for (int k = 1; k < s[j].size; k++)
			{
				if (s[i].p[0].ci == s[j].p[k].ci && s[i].p[0].ri == s[j].p[k].ri)
				{
					//delete[]s[j].p;
					delete[]s[i].p;
					//s[j].kill = true;
					s[i].kill = true;
					PlaySound(TEXT("kill"), NULL, SND_ASYNC);
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (s[i].kill)
		{
			count++;
			continue;
		}
		for (int j = 0; j <hurdle.size; j++)
		{
			for (int k = hurdle.stage[j].si.ci; k < hurdle.stage[j].ei.ci; k++)
			{
				if (s[i].p[0].ci == k && s[i].p[0].ri == hurdle.stage[j].si.ri)
				{
					delete[]s[i].p;
					s[i].kill = true;
					PlaySound(TEXT("kill"), NULL, SND_ASYNC);
				}
			}
			for (int k = hurdle.stage[j].si.ri; k < hurdle.stage[j].ei.ri; k++)
			{
				if (s[i].p[0].ci == hurdle.stage[j].si.ci && s[i].p[0].ri == k)
				{
					delete[]s[i].p;
					s[i].kill = true;
					PlaySound(TEXT("kill"), NULL, SND_ASYNC);
				}
				
			}
		}
	}

	

}
bool isGameover(snake* s, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!(s[i].kill))
		{
			return false;

		}
	}
	return true;
}
void l2r(int r, int cs, int ce, char sym = -37)
{
	for (int c = cs; c < ce; c++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void t2b(int c, int rs, int re, char sym = -37)
{
	for (int r = rs; r <= re; r++)
	{
		gotoRowCol(r, c);
		cout << sym;
	}
}
void N(int cr, int cc, int scale, char sym = -37)
{
	
		int r = cr, c = cc;
		for (int i = 0; i < scale / 2; i++)
		{
			gotoRowCol(r, c);
			cout << sym;
			r++; c++;
		}
		r = cr, c = cc;
		for (int i = 0; i < scale / 2; i++)
		{
			gotoRowCol(r, c);
			cout << sym;
			r--; c--;
		}
		r = r - scale / 2;
		c = cc;

		c = cc - scale / 2 + 1;
		r = cr;
		for (int i = 0; i < scale / 2; i++) {
			gotoRowCol(r, c);
			cout << sym;
			r++;
		}
		for (int i = 0; i <= scale; i++) {
			gotoRowCol(r, c);
			cout << sym;
			r--;
		}
		c = cc + scale / 2 - 1;
		r = cr;
		for (int i = 0; i < scale / 2; i++) {
			gotoRowCol(r, c);
			cout << sym;
			r++;
		}
		for (int i = 0; i <= scale; i++) {
			gotoRowCol(r, c);
			cout << sym;
			r--;
		}
	
}
void gameover()
{
	SetClr(4);
	l2r(20, 10, 30);
	l2r(40, 10, 30);
	l2r(60, 10, 30);
	l2r(21, 10, 30);
	l2r(41, 10, 30);
	l2r(61, 10, 30);
	l2r(22, 10, 30);
	l2r(42, 10, 30);
	l2r(62, 10, 30);
	t2b(10, 20, 60);
	N(40, 60, 40);
	t2b(90, 20, 60);
	t2b(110, 20, 62);
	l2r(20, 90, 110);
	l2r(60, 90, 110);
	l2r(21, 90, 110);
	l2r(61, 90, 110);
	l2r(22, 90, 110);
	l2r(62, 90, 110);


}
void drawboxes()
{
	

	for (int i = 0; i < 10; i++)
	{

		SetClr(1);
		for (int j = 0; j < 30; j++)
		{
			gotoRowCol(i+0, j);
			cout << char(-37);
			
		}
		SetClr(20);
		gotoRowCol(5, 8);
		cout << "No Of Players";
		/*SetClr(4);
		N(5,3,6);
		O(5, 9, 6);*/
		
		SetClr(2);
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 12, j);
			cout << char(-37);
			if (j == 15 && i>1 &&i<9)
			{
				SetClr(36);
				gotoRowCol(i + 12, j);
				cout << char(-37);
			}

		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 24, j);
			cout << char(-37);
			if ((j == 14 ||j==16 )&&( i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 24, j);
				cout << char(-37);
			}
		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 36, j);
			cout << char(-37);
			if ((j == 13 || j == 15||j==17) && (i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 36, j);
				cout << char(-37);
			}
		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 48, j);
			cout << char(-37);
			if ((j == 12 || j == 14 || j == 16 || j == 18) && (i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 48, j);
				cout << char(-37);
			}

			
		}
		
		
	}


	
	

	
	
}
void drawboxes2()
{
	
	for (int i = 0; i < 10; i++)
	{

		SetClr(1);
		for (int j = 0; j < 30; j++)
		{
			gotoRowCol(i + 0, j);
			cout << char(-37);

		}
		SetClr(20);
		gotoRowCol(5, 13);
		cout << "Stage";
		/*SetClr(4);
		N(5,3,6);
		O(5, 9, 6);*/

		SetClr(2);
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 12, j);
			cout << char(-37);
			if (j == 15 && i > 1 && i < 9)
			{
				SetClr(36);
				gotoRowCol(i + 12, j);
				cout << char(-37);
			}

		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 24, j);
			cout << char(-37);
			if ((j == 14 || j == 16) && (i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 24, j);
				cout << char(-37);
			}
		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 36, j);
			cout << char(-37);
			if ((j == 13 || j == 15 || j == 17) && (i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 36, j);
				cout << char(-37);
			}
		}
		for (int j = 0; j < 30; j++)
		{
			SetClr(2);
			gotoRowCol(i + 48, j);
			cout << char(-37);
			if ((j == 12 || j == 14 || j == 16 || j == 18) && (i > 1 && i < 9))
			{
				SetClr(36);
				gotoRowCol(i + 48, j);
				cout << char(-37);
			}


		}


	}





	


}
int retrnInt()
{
	int row,col;
	getRowColbyLeftClick(row, col);
	

	if (row >= 12 && row <= 22 && col >= 0 && col <= 30)
	{
		return 1;
	}
	if (row >= 24 && row <= 34 && col >= 0 && col <= 30)
	{
		return 2;
	}
	if (row >= 36 && row <= 46 && col >= 0 && col <= 30)
	{
		return 3;

	}
	if (row >= 48 && row <= 58 && col >= 0 && col <= 30)
	{
		return 4;
	}

	


}
int maxscore(snake* s, int size,int &x)
{
	int mx = 0;
	for (int i = 0; i < size; i++)
	{
		if (s[i].score > mx)
		{
			mx = s[i].score;
			x = i;
		}

	}
	return mx;

}
void game()
{
	srand(time(0));
	Stges hurdle{};
	int x,mx,i;
	cout << "Input Max score: ";
	cin >> mx;
	
	//cout << hurdle.stage[1].si.ri;
	//int ch;
	food f;
	snake* s;
	int size{};
	PlaySound(TEXT("gme"), NULL, SND_ASYNC);
	drawboxes();
	size = retrnInt();
	system("cls");
	drawboxes2();
	x= retrnInt();
	if (x == 1)
	{
		hurdle = Stage("bscs22109-input1.txt");

	}
	if (x == 2)
	{
		hurdle = Stage("bscs22109-input2.txt");

	}
	if (x == 3)
	{
		hurdle = Stage("bscs22109-input3.txt");

	}
	if (x == 4)
	{
		hurdle = Stage("bscs22109-input4.txt");

	}
	system("cls");

	init(s, f, size,hurdle);
	for (int i = 0; i < size; i++)
	{
		cout << "Player " << i + 1<<" 'sname:";
		cin >> s[i].name;
	}
	//PlaySound(TEXT("snk"), NULL, SND_ASYNC);
	displayfood(f);
	drawBound();
	drawstage(hurdle);
	int fd = 0;
	while (true)
	{
		fd++;
		if (_kbhit())
		{
			//ch = _getch();
			changedir(s, _getch(), size);
			
		}
		displaySnake(s, size);

		Sleep(50);
		undisplaySnake(s, size);


		movesnake(s, size);
		if (foodeaten(s, f, size))
		{


			generatefood(f, s, size,hurdle);
			displayfood(f);
			


		}
		if (fd > 100)
		{
			undisplayfood(f);
			generatefood(f, s, size, hurdle);
			displayfood(f);
			fd = 0;
		}
		killcheck(s, size, hurdle);
		if (maxscore(s, size,i) == 3)
		{
			hurdle = Stage("bscs22109-input2.txt");
			drawstage(hurdle);
		}
		if (maxscore(s, size,i) == 5)
		{
			hurdle = Stage("bscs22109-input3.txt");
			drawstage(hurdle);
		}
		if (maxscore(s, size,i) ==7)
		{
			hurdle = Stage("bscs22109-input4.txt");
			drawstage(hurdle);
		}
		if (maxscore(s, size,i) > mx)
		{
			system("cls");
			cout << s[i].name << " is winner!";
			break;

		}
		if (isGameover(s,size))
		{

			system("cls");
			PlaySound(TEXT("gameover"), NULL, SND_ASYNC);
			gameover();
			break;

		}



	}
}
int main()
{
	
	game();
	
	//drawboxes2();
	//();
	/*for (int i = 0; i < 50; i++)
	{
		SetClr(i);
		cout << "fuck\n";
	}*/
	
	_getch();
}