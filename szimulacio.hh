//Készítette Kertész Ádám
//2014.05.25
#ifndef SZIMULACIO__H
#define SZIMULACIO__H

#include<ncurses.h>
#include<stdlib.h>

inline int konkluzio(int szomszed);
inline int abs(int);
void nullazo(int** tomb, int oszlop, int sor);
inline int szim(WINDOW *space, int **sejtek, int max_db, int oszlop, int sor, int sejtek_szama)
{
	int ciklus;
	int sebesseg=500;

	//-----===Kiirítás és Bekérés===-----
	move(LINES-1,0);
	deleteln();
	refresh();
	addstr("Mennyi legyen a ciklusok száma? ");
	echo();
	curs_set(1);
	scanw("%d",&ciklus);
	mvprintw(0,COLS*2/3,"Ciklusok számma: ");
	attron(A_BOLD);
	printw("0");
	attroff(A_BOLD);
	noecho();
	curs_set(0);
	move(LINES-1,0);
	deleteln();
	refresh();
	addstr("Kilépés: ");
	attron(A_BOLD);
	addstr("[Esc]");
	attroff(A_BOLD);
	//=========================================

	//------------====Szimuláció====------------
	// Ha a szomszédok < 2 || szomszédok > 3 ======> a sejt elpuszul. Megjelölés: -1
	// Ha a szomszédok = 2 || szomszédok = 3 ======> a sejt életben marad (stagnál)
	// Ha egy cellának a szomszédok = 3      ======> Új sejt

	int x,y,szomszed,i;

	for(i=1;i<=ciklus;i++)
	{
		//A sejtek megjelölése törlésre ha szükséges
		for(x=0;x<oszlop;x++)
		{
			for(y=0;y<sor;y++)
			{
				if(sejtek[x][y]==1)
				{
					//Szomszéd keresés

					//ha az ablak ball felső sarkában van a sejt
					szomszed=0;
					if(x==0 && y==0)
					{
						if(sejtek[x+1][y]==1)
							szomszed++;
						if(sejtek[x+1][y+1]==1)
							szomszed++;
						if(sejtek[x][y+1]==1)
							szomszed++;		
						
						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);								

					}

					//ha az ablak ball szélénél van a sejt
					szomszed=0;
					if((x==0) && (y!=0 && y!=(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;		
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);

					}

					//ha az ablak ball alsó sarkában van a sejt
					szomszed=0;
					if((x==0) && (y==(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;	

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);
					}

					//Ha az ablak tetején van a sejt
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y==0))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);
					}

					//Ha a sejt nincs az ablak szélénél (a közepénnél van valahol)
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y!=0 && (y!=(sor-1))))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;	
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);
					}
					
					//Ha az ablak alján van a sejt
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y==(sor-1)))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x][y-1])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);
					}

					//ha az ablak jobb felső sarkában van a sejt
					szomszed=0;
					if((x==(oszlop-1)) && (y==0))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;		
						
						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);								

					}

					//ha az ablak jobb szélénél van a sejt
					szomszed=0;
					if((x==(oszlop-1)) && ((y!=0) && y!=(oszlop-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y])==1)
							szomszed++;		
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);

					}

					//ha az ablak jobb alsó sarkában van a sejt
					szomszed=0;
					if((x==(oszlop-1)) && (y==(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y])==1)
							szomszed++;

						//Döntés hozzatal
						sejtek[x][y]=konkluzio(szomszed);

					}
				}
			}
		}

		//A cellák átnézése hogy születhet-e új sejt ott
		for(x=0;x<oszlop;x++)
		{
			for(y=0;y<sor;y++)
			{
				if(sejtek[x][y]==0)
				{
					//Szomszéd keresés

					//Ball felső cella
					szomszed=0;
					if(x==0 && y==0)
					{
						if(abs(sejtek[x+1][y])==1)
							szomszed++;
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;		
						
						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}							

					}

					//Az ablak ball szélénél lévő cellák
					szomszed=0;
					if((x==0) && (y!=0 && y!=(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;		
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}

					}

					//Ball alsó cella
					szomszed=0;
					if((x==0) && (y==(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;	

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}
					}

					//Felső cellák
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y==0))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}
					}

					//A középső cellák
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y!=0 && (y!=(sor-1))))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;	
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}
					}
					
					//Alsó cellák
					szomszed=0;
					if((x!=0 && (x!=(oszlop-1))) && (y==(sor-1)))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x][y-1])==1)
							szomszed++;	
						if(abs(sejtek[x+1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x+1][y])==1)
							szomszed++;

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}
					}

					//ha az ablak jobb felső sarkában van a sejt
					szomszed=0;
					if((x==(oszlop-1)) && (y==0))
					{
						if(abs(sejtek[x-1][y])==1)
							szomszed++;
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;		
						
						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}						

					}

					//A jobb szélső cellák
					szomszed=0;
					if((x==(oszlop-1)) && ((y!=0) && y!=(oszlop-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y])==1)
							szomszed++;		
						if(abs(sejtek[x-1][y+1])==1)
							szomszed++;
						if(abs(sejtek[x][y+1])==1)
							szomszed++;	

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}

					}

					//A jobb alsó cella
					szomszed=0;
					if((x==(oszlop-1)) && (y==(sor-1)))
					{
						if(abs(sejtek[x][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y-1])==1)
							szomszed++;
						if(abs(sejtek[x-1][y])==1)
							szomszed++;

						//Döntés hozzatal
						if(szomszed==3)
						{
							sejtek[x][y]=2;
							sejtek_szama++;
						}
					}

				}
			}
		}
		//A sejtek rajzolása az élettérre
		int x2,y2;

		for(x2=0;x2<oszlop;x2++)
		{
			for(y2=0;y2<sor;y2++)
			{
				if(sejtek[x2][y2]==2 || sejtek[x2][y2]==1)
				{
					sejtek[x2][y2]=1;
					wattron(space,COLOR_PAIR(4) | A_BOLD);
					mvwaddch(space,y2+1,x2+1,'X');
					wattroff(space,COLOR_PAIR(4) | A_BOLD);
					wrefresh(space);
				}
				//Törli a sejtet a tömbből és a képernyőből
				if(sejtek[x2][y2]==-1)
				{
					sejtek[x2][y2]=0;
					sejtek_szama--;
					wattron(space,COLOR_PAIR(2));
					mvwaddch(space,y2+1,x2+1,'.');
					wattroff(space,COLOR_PAIR(2));
					wrefresh(space);
				}
			}
		}
		mvprintw(0,0,"Sejtek száma: ");
		attron(A_BOLD);
		mvprintw(0,14,"%d",sejtek_szama);
		attroff(A_BOLD);
		mvprintw(0,COLS*2/3,"Ciklusok számma: ");
		attron(A_BOLD);
		mvprintw(0,(COLS*2/3)+17,"%d",i);
		attroff(A_BOLD);
		refresh();
		napms(sebesseg);
		if(sejtek_szama==0)
			break;

	}//Ciklus vége
	move(LINES-1,0);
	deleteln();
	refresh();
	addstr("Kilépés: ");
	attron(A_BOLD);
	addstr("[Esc]");
	attroff(A_BOLD);
	mvprintw(LINES-1,COLS/3,"Szimuláció Vége!");
	refresh();
	getch();
	return sejtek_szama;

}

int konkluzio(int szomszed)
{
	if((szomszed>3) || (szomszed<2))
		return (-1);

	if((szomszed==3) || (szomszed==2))
		return 1;
}

int abs(int ertek) {
  if (ertek < 0) {
    return ((-1)*ertek);
  }
  else {
    return ertek;  
  }
}

void nullazo(int** tomb, int oszlop, int sor)
{
	int x,y;
	
	for(x=0;x<oszlop;x++)
		for(y=0;y<sor;y++)
			tomb[x][y] = 0;
}

#endif
