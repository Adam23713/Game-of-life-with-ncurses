//Készítette Kertész Ádám
//2014.05.25
#ifndef WINDOWS__H
#define WINDOWS__H
#include<ncurses.h>

inline void panelek(WINDOW*,int);
inline int sejt_hozza_adas(WINDOW *,int**,int,int);
inline void leiras();
inline void settings();
inline int alakzatok(WINDOW*,int**,int*,int*);
inline void null(int**,int,int);
inline void alakzat_rajzolo(WINDOW*,int**,int,int,int,int);
inline void space_writter(WINDOW*,int**,int**,int,int);

inline void null(int** tomb, int x, int y)
{
	int i,j;
	
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			tomb[i][j]=0;
}

inline void space_writter(WINDOW *space, int **alakzat, int **sejtek, int x , int y) //x és y az alakzat tömb mérete
{
	int maxy,maxx;
	int x_kord=0,y_kord=0;

	//A segéd tömb bevezetése
	int** seged_tomb = new int*[x];
	for(int i=0; i<11; ++i)
		seged_tomb[i] = new int[y];
	null(seged_tomb,x,y);
	//*****************************

	getmaxyx(space,maxy,maxx);
	alakzat_rajzolo(space,alakzat,x,y,maxy,maxx);
	
}

inline void alakzat_rajzolo(WINDOW* rank_space, int** tomb, int x , int y, int maxy, int maxx)
{
	int i,j;
	
	int starty = (maxy - y) / 2;
	int	startx = (maxx - x)/2;

	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
		{
			if(tomb[i][j]==1)
			{
				wattron(rank_space,COLOR_PAIR(7));
				mvwaddch(rank_space,j+starty,i+startx,'X'); //y  x
				wattroff(rank_space,COLOR_PAIR(7));
			}
		}
		wrefresh(rank_space);
}

inline int alakzatok(WINDOW *space, int **tomb, int *t_x, int *t_y)
{

	int counter;
	int sejtek=0;
	int const item = 7;
	char name[item][20] = {"Sikló (D)","Gun (D)","Frog II (D)","Vészjel (D)","Clock I (D)","Clock II (D)","PinWheel"};

	//--------------Sikló---------------
	int** ship = new int*[3];
	for(int i=0; i<3; ++i)
		ship[i] = new int[3];
	null(ship,3,3);
	ship[1][0] = 1;
	ship[2][1] = 1;
	ship[0][2] = 1;
	ship[1][2] = 1;
	ship[2][2] = 1;
	//-----------------------------------

	//--------------Béka---------------
	int** frog = new int*[11];
	for(int i=0; i<11; ++i)
		frog[i] = new int[13];
	null(frog,11,13);
	frog[2][0] = 1;	frog[4][4] = 1;	 frog[7][7] = 1; frog[3][12] = 1;
	frog[3][0] = 1;	frog[6][4] = 1;	 frog[9][7] = 1; frog[4][12] = 1;
	frog[7][0] = 1;	frog[7][4] = 1;	 frog[0][8] = 1; frog[6][12] = 1;
	frog[8][0] = 1;	frog[1][5] = 1;	 frog[1][8] = 1;
	frog[2][1] = 1;	frog[2][5] = 1;	 frog[3][8] = 1;
	frog[4][1] = 1;	frog[8][5] = 1;	 frog[7][8] = 1;
	frog[6][1] = 1;	frog[9][5] = 1;	 frog[9][8] = 1;
	frog[8][1] = 1;	frog[0][6] = 1;	 frog[10][8] = 1;
	frog[4][2] = 1;	frog[3][6] = 1;	 frog[4][9] = 1;
	frog[6][2] = 1;	frog[5][6] = 1;	 frog[5][9] = 1;
	frog[3][3] = 1;	frog[7][6] = 1;	 frog[6][9] = 1;
	frog[5][3] = 1;	frog[10][6] = 1; frog[3][11] = 1;
	frog[7][3] = 1;	frog[1][7] = 1;	 frog[5][11] = 1;
	frog[3][4] = 1;	frog[3][7] = 1;	 frog[6][11] = 1;

	//-----------------------------------

	//--------------Puska---------------
	int** gun = new int*[36];
	for(int i=0; i<36; ++i)
		gun[i] = new int[9];
	null(gun,36,9);
	gun[0][4] = 1;  gun[15][3] = 1;	gun[24][0] = 1;
	gun[0][5] = 1;  gun[15][7] = 1;	gun[24][1] = 1;
	gun[1][4] = 1;	gun[16][4] = 1;	gun[24][5] = 1;
	gun[1][5] = 1;	gun[16][5] = 1;	gun[24][6] = 1;
	gun[10][4] = 1;	gun[16][6] = 1;	gun[34][2] = 1;
	gun[10][5] = 1;	gun[17][5] = 1;	gun[34][3] = 1;
	gun[10][6] = 1;	gun[20][2] = 1;	gun[35][2] = 1;
	gun[11][3] = 1;	gun[20][3] = 1;	gun[35][3] = 1;
	gun[11][7] = 1;	gun[20][4] = 1;
	gun[12][2] = 1;	gun[21][2] = 1;
	gun[12][8] = 1;	gun[21][3] = 1;
	gun[13][2] = 1;	gun[21][4] = 1;
	gun[13][8] = 1;	gun[22][1] = 1;
	gun[14][5] = 1;	gun[22][5] = 1;
	//-----------------------------------

	//--------------Vészjel---------------
	int** beacon = new int*[4];
	for(int i=0; i<4; ++i)
		beacon[i] = new int[4];
	null(beacon,4,4);
	beacon[0][0] = 1;
	beacon[0][1] = 1;
	beacon[1][0] = 1;
	beacon[2][3] = 1;
	beacon[3][2] = 1;
	beacon[3][3] = 1;
	//-----------------------------------

	//--------------Óra I---------------
	int** clock_1 = new int*[4];
	for(int i=0; i<4; ++i)
		clock_1[i] = new int[4];
	null(clock_1,4,4);
	clock_1[2][0] = 1;	clock_1[1][2] = 1;
	clock_1[0][1] = 1;	clock_1[3][2] = 1;
	clock_1[2][1] = 1;	clock_1[1][3] = 1;
	//-----------------------------------

	//--------------Óra II---------------
	int** clock_2 = new int*[12];
	for(int i=0; i<12; ++i)
		clock_2[i] = new int[12];
	null(clock_2,12,12);
	clock_2[0][4] = 1;	clock_2[5][3] = 1;	clock_2[7][1] = 1;
	clock_2[0][5] = 1;	clock_2[5][7] = 1;	clock_2[7][3] = 1;
	clock_2[1][4] = 1;	clock_2[5][8] = 1;	clock_2[7][8] = 1;
	clock_2[1][5] = 1;	clock_2[5][10] = 1;	clock_2[8][4] = 1;
	clock_2[3][4] = 1;	clock_2[5][11] = 1;	clock_2[8][5] = 1;
	clock_2[3][5] = 1;	clock_2[6][0] = 1;	clock_2[8][6] = 1;
	clock_2[3][6] = 1;	clock_2[6][1] = 1;	clock_2[8][7] = 1;
	clock_2[3][7] = 1;	clock_2[6][3] = 1;	clock_2[10][6] = 1;
	clock_2[3][4] = 1;	clock_2[6][5] = 1;	clock_2[10][7] = 1;
	clock_2[4][8] = 1;	clock_2[6][6] = 1;	clock_2[11][6] = 1;
	clock_2[4][10] = 1;	clock_2[6][8] = 1;	clock_2[11][7] = 1;
	clock_2[4][11] = 1;	clock_2[7][0] = 1;	clock_2[4][3] = 1;
	//-----------------------------------

	//--------------Szélkerék---------------
	int** pinwheel = new int*[12];
	for(int i=0; i<12; ++i)
		pinwheel[i] = new int[12];
	null(pinwheel,12,12);
	pinwheel[0][4] = 1;		pinwheel[5][3] = 1;		pinwheel[7][1] = 1;
	pinwheel[0][5] = 1;		pinwheel[5][7] = 1;		pinwheel[7][3] = 1;
	pinwheel[1][4] = 1;		pinwheel[5][8] = 1;		pinwheel[7][8] = 1;
	pinwheel[1][5] = 1;		pinwheel[5][10] = 1;	pinwheel[8][4] = 1;
	pinwheel[3][4] = 1;		pinwheel[5][11] = 1;	pinwheel[8][5] = 1;
	pinwheel[3][5] = 1;		pinwheel[6][0] = 1;		pinwheel[8][6] = 1;
	pinwheel[3][6] = 1;		pinwheel[6][1] = 1;		pinwheel[8][7] = 1;
	pinwheel[3][7] = 1;		pinwheel[6][3] = 1;		pinwheel[10][6] = 1;
	pinwheel[3][4] = 1;		pinwheel[6][5] = 1;		pinwheel[10][7] = 1;
	pinwheel[4][8] = 1;		pinwheel[7][6] = 1;		pinwheel[11][6] = 1;
	pinwheel[4][10] = 1;	pinwheel[6][8] = 1;		pinwheel[11][7] = 1;
	pinwheel[4][11] = 1;	pinwheel[7][0] = 1;		pinwheel[4][3] = 1;
	//-----------------------------------

	int maxy,maxx,ch;
	WINDOW *rank;
	WINDOW *rank_space;

	getmaxyx(stdscr,maxy,maxx);
	if((rank = newwin(maxy/2,maxx/2,LINES/4,COLS/4))==NULL)
	{
		printw("Nem tölthetőek be az alakzatok!\n");
		getch();
		return 0;
	}
	getmaxyx(rank,maxy,maxx);
	rank_space=derwin(rank,maxy-3,maxx-2,2,1);
	if(rank_space==NULL)
	{
		printw("A segéd ablak nem hozható létre!\n");
		getch();
		delwin(rank);
		return 0;
	}
	box(rank,0,0);
	wbkgd(rank,COLOR_PAIR(1));
	wattron(rank,A_BOLD);
	mvwaddstr(rank,1,1,"Alakzatok: ");
	wattroff(rank,A_BOLD);
	wrefresh(rank);
	wattron(rank,COLOR_PAIR(6) | A_BOLD);
	mvwaddstr(rank,1,12,name[0]);
	wattroff(rank,COLOR_PAIR(6) | A_BOLD);
	wattron(rank,A_BOLD);
	mvwaddstr(rank,1,maxx*2/3,"OK ");
	wattroff(rank,A_BOLD);
	waddstr(rank,"[ENTER]");
	wattron(rank,A_BOLD);
	waddstr(rank,"  Mégse ");
	wattroff(rank,A_BOLD);
	waddstr(rank,"[C]");
	wbkgd(rank_space,COLOR_PAIR(5) | A_BOLD |'.');
	touchwin(rank);
	wrefresh(rank);


	//===============Alakzat választás===============

	keypad(rank,TRUE);
	getmaxyx(rank_space,maxy,maxx);
	alakzat_rajzolo(rank_space,ship,3,3,maxy,maxx);
	counter=0;
	do
	{
		ch = getch();
		switch(ch)
		{
			case KEY_LEFT:
				if(counter==0)
					counter=item-1;
				else
				{
					counter--;
				}
				break;

			case KEY_RIGHT:
				if(counter==item-1)
					counter=0;
				else
				{
					counter++;
				}
				break;

			case 'c':
				*t_x=0;
				*t_y=0;
				tomb=NULL;
				delwin(rank_space);
				delwin(rank);
				touchwin(space);
				wrefresh(space);
				return 0;

			default:
				break;
		}
		//Ablak tartalmának törlése és frissítése
		wclear(rank);
		wrefresh(rank);
		wclear(rank_space);
		wrefresh(rank_space);	
		//----------------------------------------	

		box(rank,0,0);
		wattron(rank,A_BOLD);
		mvwaddstr(rank,1,1,"Alakzatok: ");
		wattroff(rank,A_BOLD);
		wrefresh(rank);
		wattron(rank,COLOR_PAIR(6) | A_BOLD);
		mvwaddstr(rank,1,12,name[0]);
		wattroff(rank,COLOR_PAIR(6) | A_BOLD);
		wattron(rank,A_BOLD);
		mvwaddstr(rank,1,maxx*2/3,"OK ");
		wattroff(rank,A_BOLD);
		waddstr(rank,"[ENTER]");
		wattron(rank,A_BOLD);
		waddstr(rank,"  Mégse ");
		wattroff(rank,A_BOLD);
		waddstr(rank,"[C]");

		mvwaddstr(rank,1,12,"                 ");
		wattron(rank,COLOR_PAIR(6) | A_BOLD);
		mvwaddstr(rank,1,12,name[counter]);
		wattroff(rank,COLOR_PAIR(6) | A_BOLD);
		wrefresh(rank);

		if(counter==0)
			alakzat_rajzolo(rank_space,ship,3,3,maxy,maxx);
		if(counter==1)
			alakzat_rajzolo(rank_space,gun,36,9,maxy,maxx);
		if(counter==2)
			alakzat_rajzolo(rank_space,frog,11,13,maxy,maxx);
		if(counter==3)
			alakzat_rajzolo(rank_space,beacon,4,4,maxy,maxx);
		if(counter==4)
			alakzat_rajzolo(rank_space,clock_1,4,4,maxy,maxx);
		if(counter==5)
			alakzat_rajzolo(rank_space,clock_2,12,12,maxy,maxx);
		if(counter==6)
			alakzat_rajzolo(rank_space,pinwheel,12,12,maxy,maxx);

		wrefresh(rank);
	}while(ch != '\n');

	if(counter==0)	//Sikló
	{	
		for(int u=0;u<3;u++)
			for(int t=0;t<3;t++)
				tomb[u][t]=ship[u][t];

		*t_x=3;
		*t_y=3;
		sejtek=5;
	}
	if(counter==1)	//puska
	{	
		for(int u=0;u<36;u++)
			for(int t=0;t<9;t++)
				tomb[u][t]=gun[u][t];

		*t_x=36;
		*t_y=9;
		sejtek=46;
	}
	if(counter==2) //béka
	{	
		for(int u=0;u<11;u++)
			for(int t=0;t<13;t++)
				tomb[u][t]=frog[u][t];

		*t_x=11;
		*t_y=13;
		sejtek=55;
	}
	if(counter==3)	//Vészjel
	{
		
		for(int u=0;u<4;u++)
			for(int t=0;t<4;t++)
				tomb[u][t]=beacon[u][t];

		*t_x=4;
		*t_y=4;
		sejtek=6;
	}
	if(counter==4)	//Óra 1
	{
		for(int u=0;u<4;u++)
			for(int t=0;t<4;t++)
				tomb[u][t]=clock_1[u][t];

		*t_x=4;
		*t_y=4;
		sejtek=6;
	}
	if(counter==5)	//Óra 2
	{
		
		for(int u=0;u<12;u++)
			for(int t=0;t<12;t++)
				tomb[u][t]=clock_2[u][t];

		*t_x=12;
		*t_y=12;
		sejtek=36;
	}
	if(counter==6)	//szélkerék
	{
		//Tömb másolása
		for(int u=0;u<12;u++)
			for(int t=0;t<12;t++)
				tomb[u][t]=pinwheel[u][t];

		*t_x=12;
		*t_y=12;
		sejtek=36;
	}

	delwin(rank_space);
	delwin(rank);
	touchwin(space);
	wrefresh(space);

	return sejtek;
}

inline void settings()
{
	int maxy,maxx;
	WINDOW *settings;

	getmaxyx(stdscr,maxy,maxx);
	if((settings = newwin(maxy/2,maxx/2,LINES/4,COLS/4))==NULL)
	{
		printw("A Beállítás ablak nem nyitható meg!\n");
		getch();
		return;
	}
	else	
	{	
		box(settings,0,0);
		wbkgd(settings,COLOR_PAIR(1));
		wrefresh(settings);
		mvwaddstr(settings,1,1,"Beállítások:");
		mvwaddstr(settings,2,1,"Hamarosan...");
		wrefresh(settings);
		getch();
		delwin(settings);

	}
}

inline void leiras()
{
	int maxy,maxx;
	WINDOW *info;

	getmaxyx(stdscr,maxy,maxx);
	if((info = newwin(maxy/2,maxx/2,LINES/4,COLS/4))==NULL)
	{
		printw("A leírás ablak nem nyitható meg!\n");
		getch();
		return;
	}
	else	
	{	
		scrollok(info,TRUE);
		box(info,0,0);
		wbkgd(info,COLOR_PAIR(1));
		wrefresh(info);
		mvwaddstr(info,1,1,"Leírás:");
		mvwaddstr(info,2,1,"Hamarosan...");
		wrefresh(info);
		getch();
		delwin(info);

	}
}

inline int sejt_hozza_adas(WINDOW *space, int **tomb,int oszlop, int sejtek)
{
	int ch,x,y,s;

	move(0,0);
	deleteln();
	refresh();
	touchwin(space);
	wrefresh(space);
	mvaddstr(0,0,"Sejtek száma: ");
	attron(A_BOLD);
	addstr("0");
	attroff(A_BOLD);
	mvaddstr(0,COLS/3,"Alaktatok: ");
	attron(A_BOLD);
	addstr("[E]");
	attroff(A_BOLD);
	mvaddstr(0,COLS*2/3,"Mentés visszatöltése: ");
	attron(A_BOLD);
	addstr("[B]");
	attroff(A_BOLD);
	refresh();
	wrefresh(space);

	//======================
	attron(COLOR_PAIR(1));
	move(LINES-1,0);
	deleteln();
	mvaddstr(LINES-1,0,"Add: ");
	attron(A_BOLD);
	addstr("A");
	attroff(A_BOLD);
	mvaddstr(LINES-1,COLS/4,"Deleted: ");
	attron(A_BOLD);
	addstr("D");
	attroff(A_BOLD);
	wattron(space,COLOR_PAIR(3));
	x=1;y=1;
	wattron(space,COLOR_PAIR(3) | A_BOLD);
	mvwaddch(space,y,x,'X');
	wattroff(space,COLOR_PAIR(3) | A_BOLD);
	
	//Kiírja a kurzor pozícióját
	mvprintw(LINES-1,COLS*2/4,"y = %d\tx = %d\t",y-1,x-1);

	wmove(space,y,x);
	wrefresh(space);
	refresh();
	keypad(stdscr,TRUE);
	char delet='t'; //true

	int** tomb_2 = new int*[100];
		for(int i=0; i<100; ++i)
			tomb_2[i] = new int[100];

	null(tomb_2,100,100);

	do
	{
		ch = getch();

		switch(ch)
		{
			case 'e' :
				int a,t_x,t_y,maxx,maxy;
				a=alakzatok(space,tomb_2,&t_x,&t_y);
				sejtek=sejtek+a;
				space_writter(space,tomb_2,tomb,t_x,t_y);
				break;

			case KEY_RIGHT:
				if((x+2)==COLS)
					break;

				wmove(space,y,x);
				if(delet=='t')
				{
					wattron(space,COLOR_PAIR(2));
					waddch(space,'.');
					wattroff(space,COLOR_PAIR(2));
					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,y,++x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);
				}
				else
				{
					wattron(space,COLOR_PAIR(4) | A_BOLD);
					mvwaddch(space,y,x,'X');
					wattroff(space,COLOR_PAIR(4) | A_BOLD);

					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,y,++x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);

					wrefresh(space);
					delet='t';
				}
				break;

			case KEY_LEFT:
				if((x-1)==0)
					break;

				wmove(space,y,x);
				if(delet=='t')
				{
					wattron(space,COLOR_PAIR(2));
					waddch(space,'.');
					wattroff(space,COLOR_PAIR(2));
					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,y,--x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);
				}
				else
				{
					wattron(space,COLOR_PAIR(4) | A_BOLD);
					mvwaddch(space,y,x,'X');
					wattroff(space,COLOR_PAIR(4) | A_BOLD);

					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,y,--x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);

					wrefresh(space);
					delet='t';	
				}
				break;

			case KEY_UP:
				if((y-1)==0)
					break;
				wmove(space,y,x);
				if(delet=='t')
				{
					wattron(space,COLOR_PAIR(2));
					waddch(space,'.');
					wattroff(space,COLOR_PAIR(2));
					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,--y,x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);
				}
				else
				{
					wattron(space,COLOR_PAIR(4) | A_BOLD);
					mvwaddch(space,y,x,'X');
					wattroff(space,COLOR_PAIR(4) | A_BOLD);

					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,--y,x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);

					wrefresh(space);
					delet='t';
				}
				break;

			case KEY_DOWN:
				if((y+4)==LINES)
					break;
				wmove(space,y,x);
				if(delet=='t')
				{
					wattron(space,COLOR_PAIR(2));
					waddch(space,'.');
					wattroff(space,COLOR_PAIR(2));
					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,++y,x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);
				}
				else
				{
					wattron(space,COLOR_PAIR(4) | A_BOLD);
					mvwaddch(space,y,x,'X');
					wattroff(space,COLOR_PAIR(4) | A_BOLD);

					wattron(space,COLOR_PAIR(3) | A_BOLD);
					mvwaddch(space,++y,x,'X');
					wattroff(space,COLOR_PAIR(3) | A_BOLD);

					wrefresh(space);
					delet='t';
				}
				break;	

			case 'a' :
				if(tomb[x-1][y-1]!=1)
				{
					tomb[x-1][y-1]=1;
					sejtek++;
					attron(A_BOLD);
					mvprintw(0,14,"%d\t",sejtek);
					attroff(A_BOLD);
					delet='f'; //false
				}
				wattron(space,COLOR_PAIR(4) | A_BOLD);
				mvwaddch(space,y,x,'X');
				wattroff(space,COLOR_PAIR(4) | A_BOLD);
				break;
				
			case 'd' :
				if(tomb[x-1][y-1]!=0)
				{
					tomb[x-1][y-1]=0;
					sejtek--;
					attron(A_BOLD);
					mvprintw(0,14,"%d\t",sejtek);
					attroff(A_BOLD);
					delet='t'; //false
				}
				break;

			default:
				break;
		}
		if(tomb[x-1][y-1]==1)
		{
			delet='f';
			
		}
		mvprintw(LINES-1,COLS*2/4,"y = %d\tx = %d\t",y-1,x-1);
		mvprintw(LINES-1,COLS*3/4,"sejtek[%d][%d] = %d\t",x-1,y-1,tomb[x-1][y-1]);
		wmove(space,y,x);
		wrefresh(space);
	}while(ch != 27);

	//Törli a kurzort az éllettérről
	if(tomb[x-1][y-1]==0)
	{
		wattron(space,COLOR_PAIR(2));
		waddch(space,'.');	
		wattroff(space,COLOR_PAIR(2));
	}
	else
	{
		wattron(space,COLOR_PAIR(4) | A_BOLD);
		mvwaddch(space,y,x,'X');
		wattroff(space,COLOR_PAIR(4) | A_BOLD);
	}
	wrefresh(space);
	return sejtek;
}

inline void panelek(WINDOW *space, int sejtek)
{
	move(0,0);
	deleteln();
	refresh();
	touchwin(space);
	wrefresh(space);
	mvprintw(0,0,"Sejtek száma: ");
	attron(A_BOLD);
	printw("%d",sejtek);
	attroff(A_BOLD);
	mvprintw(0,COLS/3,"Beállítások: ");
	attron(A_BOLD);
	printw("[B]");
	attroff(A_BOLD);
	mvprintw(0,COLS*2/3,"Leírás: ");
	attron(A_BOLD);
	printw("[L]");
	attroff(A_BOLD);
	move(LINES-1,0);
	deleteln();
	refresh();
	addstr("Kilépés: ");
	attron(A_BOLD);
	addstr("[Esc]");
	attroff(A_BOLD);
	mvaddstr(LINES-1,COLS/3,"Sejtek Hozzáadása: ");
	attron(A_BOLD);
	addstr("[1]");
	attroff(A_BOLD);
	mvaddstr(LINES-1,COLS*2/3,"Szimuláció Indítása: ");
	attron(A_BOLD);
	addstr("[2]");
	attroff(A_BOLD);
	refresh();
}

#endif
