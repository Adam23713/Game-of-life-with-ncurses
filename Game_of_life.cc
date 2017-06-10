//Készítette Kertész Ádám
//2014.05.25
#include <ncurses.h>
#include <stdlib.h>
#include "szimulacio.hh"
#include "windows.hh"

/*A négyzetrács mezőit celláknak, a korongokat sejteknek nevezzük. Egy cella környezete a hozzá legközelebb eső 8 mező (tehát a cellához képest „átlósan” elhelyezkedő cellákat is figyelembe vesszük, feltesszük hogy a négyzetrácsnak nincs széle). Egy sejt/cella szomszédjai a környezetében lévő sejtek. A játék körökre osztott, a kezdő állapotban tetszőleges számú (egy vagy több) cellába sejteket helyezünk. Ezt követően a játékosnak nincs beleszólása a játékmenetbe. Egy sejttel (cellával) egy körben a következő három dolog történhet:

A sejt túléli a kört, ha két vagy három szomszédja van.
A sejt elpusztul, ha kettőnél kevesebb (elszigetelődés), vagy háromnál több (túlnépesedés) szomszédja van.
Új sejt születik minden olyan cellában, melynek környezetében pontosan három sejt található.
Fontos, hogy a változások csak a kör végén következnek be, tehát az „elhalálozók” nem akadályozzák a születést és a túlélést (legalábbis az adott körben), és a születések nem mentik meg az „elhalálozókat”. A gyakorlatban ezért a következő lépéseket célszerű ilyen sorrendben végrehajtani:

Az elhaló sejtek megjelölése
A születő sejtek elhelyezése
A megjelölt sejtek eltávolítása*/

void adat_mentes(FILE *fout, int **sejtek, int sor, int oszlop);

int main()
{
	int maxx,maxy,valasz;
	int sejtek_szama=0;
	WINDOW *space;
	FILE *fout=fopen("adatok.txt","a+");

	initscr();
	getmaxyx(stdscr,maxy,maxx);
	int oszlop=maxx-2;
	int sor=maxy-4;
	int max_sejt_szam=sor*oszlop;

	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);

	//Az élettér létre hozzása --------------------------------------------------
	if((space = newwin(maxy-2,maxx,1,0))==NULL)
	{
		printw("Nem sikerült létrehozni a space ablakot!\n");
		getch();
		endwin();
		return -1;
	}
	box(space,0,0);

	start_color();
	refresh();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	init_pair(3,COLOR_RED,COLOR_BLUE);
	init_pair(4,COLOR_GREEN,COLOR_BLUE);
	init_pair(5,COLOR_WHITE,COLOR_MAGENTA);
	init_pair(6,COLOR_BLUE,COLOR_BLACK);
	init_pair(7,COLOR_GREEN,COLOR_MAGENTA);
	bkgd(COLOR_PAIR(1));
	wbkgd(space,COLOR_PAIR(2) | '.');

	//Felső és alsó panelek kiírásai
	panelek(space,sejtek_szama);
	//------------------------------------------------------------------------


	//Sejt tömb létrehozása
	int** sejtek = new int*[oszlop];
	for(int i=0; i<oszlop; ++i)
		sejtek[i] = new int[sor];
	nullazo(sejtek,oszlop,sor);

	wrefresh(space);
	flushinp();
	while((valasz = getch()) != 27)
	{
		switch(valasz)
		{
			case '1':
					sejtek_szama=sejt_hozza_adas(space,sejtek,oszlop,sejtek_szama);
					system("date >>adatok.txt");
					system("echo x  y >>adatok.txt");
					adat_mentes(fout,sejtek,sor,oszlop);
					panelek(space,sejtek_szama);
					break;
			
			case '2' :
				sejtek_szama=szim(space,sejtek,max_sejt_szam,oszlop,sor,sejtek_szama);
				panelek(space,sejtek_szama);
				break;

			case 'l' :
				leiras();
				touchwin(space);
				wrefresh(space);
				break;

			case 'b' :
				settings();
				touchwin(space);
				wrefresh(space);
				break;

		}
	}
	endwin();
	return 1;
	
}

void adat_mentes(FILE *fout, int **sejtek, int sor, int oszlop)
{
	int x,y;

	for(x=0;x<oszlop;x++)
	{
		for(y=0;y<sor;y++)
		{
			if(sejtek[x][y]==1)
			{
				fprintf(fout,"%d %d\n",x,y);
			}
		}
	}
}








