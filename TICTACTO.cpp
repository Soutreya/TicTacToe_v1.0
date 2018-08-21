#include<fstream.h>
#include<conio.h>
#include<stdlib.h>

#define X 30

int lines[][3]={ 1,2,3,
		 4,5,6,
		 7,8,9,
		 1,4,7,
		 2,5,8,
		 3,6,9,
		 1,5,9,
		 3,5,7 };
int rec[9];
int crec[4];
int gno,y=15,ctr;
ifstream f;

struct Game
{
	int sl;
	int moves[9];
}G;

void intro();		// Introduction to the game
void instructions();	// How to play the game...
void grid();		// Displays the grid
int hasWon(int);	// Checks whether the game has been won (if yes,by whom)
int isValid(int);	// Checks whether a move is valid or not
void user();
void computer();
int defend();
int attack();
int randomove();
void output(int,char);	// Displays intended move and invokes next player (function)
void save();		// Saves the last played game
void load();		// To view saved games
void loadGnumber();	// Computes the current game number

void intro()
{
	clrscr();
	if (y!=15)
		goto l0;
	{
	f.open("intro.txt");
	char c;
	while(!f.eof())
	{
		f.get(c);
		cout<<c;
	}
	f.close();
	getch();
	}
l0:	clrscr();
	for (int i=1;i<=9;rec[i-1]=i++);
	crec[0]=0;
	y=11;
	ctr=0;
	cout<<"\n\n\n";
	cout<<"\t\t\t\t ____ ____"<<endl;
	cout<<"\t\t\t\t MAIN MENU"<<endl;
	cout<<"\t\t\t\t ~~~~ ~~~~"<<endl;
	cout<<"\n\n\n";
	cout<<"\t\t\t     1. PLAY THE GAME"<<endl;
	cout<<"\t\t\t     2. INSTRUCTIONS"<<endl;
	cout<<"\t\t\t     3. VIEW SAVED GAMES"<<endl;
	cout<<"\t\t\t     4. QUIT"<<endl<<endl;
	int ch;
	cout<<"\t\t\t        Enter your choice: ";
	cin>>ch;
l1:	switch (ch)
	{
		case 1:         loadGnumber();
				return;
		case 2:		instructions();
				goto l0;
		case 3:		load();
				goto l0;
		case 4:		exit(0);
		default:	cout<<"\n\n\t\tWrong entry! Please re-enter your choice: ";
				cin>>ch;
				goto l1;
	}
}

void instructions()
{
	clrscr();
	f.open("instruct.txt");
	char c;
	while(!f.eof())
	{
		f.get(c);
		cout<<c;
	}
	f.close();
	getch();
	return;
}

void grid()
{
	clrscr();
	cout<<"Game Number: "<<gno<<endl;
	f.open("grid.txt");
	char c;
	while(!f.eof())
	{
		f.get(c);
		cout<<c;
	}
	f.close();
	gotoxy(1,y++);
}

int hasWon(int c)
{
	for (int i=0,flag=0;i<8;i++,flag=0)
	{
		for (int j=0;j<3;j++)
		{
			if (rec[lines[i][j]-1]==c)
				flag++;
		}
		if (flag==3)
			return 1;
	}
	return 0;
}

int isValid(int n)
{
	if (n>=1 && n<=9)
	{
		if (rec[n-1]==-1 || rec[n-1]==-2)
			return 0;
		else
			return 1;
	}
	else
		return 0;
}

void user()
{
	int m;
l2:	gotoxy(1,y++);
	cout<<"Enter your move:        ";
	gotoxy(18,y-1);
	cin>>m;
	if (isValid(m))
	{
		rec[m-1]=-1;
		gotoxy(19,y-1);
		cout<<"                                                         ";
	}
	else
	{
		gotoxy(25,y-1);
		cout<<"You have entered an invalid move. Try Again!";
		--y;
		goto l2;
	}
	output(m,'x');
	return ;
}

void computer()
{
	ctr++;
	if (ctr==5)
	{
		gotoxy(1,y++);
		save();
		cout<<"\n\t\tTHE MATCH IS DRAWN";
		gotoxy(1,25);
		cout<<"<Press any key to go back to Main Menu>";
		getch();
		return ;
	}
	int w=randomove();
	rec[w-1]=-2;
	if (hasWon(-2))
	{
		output(w,'o');
		return ;
	}
	rec[w-1]=w;
	int m=defend();
	if (m==0)
		m=attack();
	rec[m-1]=-2;
	crec[ctr-1]=m;
	output(m,'o');
	return ;
}

int defend()
{
	int m=0;
	for (int i=0,flag=0;i<8;i++,flag=0)
	{
		if (rec[lines[i][0]-1]==-1 && rec[lines[i][1]-1]==-1)
		{	m=rec[lines[i][2]-1]; flag++;	}
		else if (rec[lines[i][1]-1]==-1 && rec[lines[i][2]-1]==-1)
		{ 	m=rec[lines[i][0]-1]; flag++;	}
		else if (rec[lines[i][2]-1]==-1 && rec[lines[i][0]-1]==-1)
		{	m=rec[lines[i][1]-1]; flag++;	}
		if (flag==1)
		{
			if (m==-2)
				continue;
			else
				return m;
		}
	}
	return 0;
}

int attack()
{
	if (ctr==1)
	{
		if (isValid(5))
			return 5;
		else
			return 1;
	}
	else if (ctr==2)
	{
		if (crec[0]==1 && isValid(9))
			return 9;
		else
			return randomove();
	}
	else if (ctr==3)
	{
		if (crec[0]==1 && crec[1]==9 && isValid(3))
			return 3;
		else if (crec[0]==1 && crec[1]==9 && isValid(7))
			return 7;
		else
			return randomove();
	}
	else
		return randomove();
}

int randomove()
{
	int m=0;
	for (int i=0,flag=0;i<8;i++,flag=0)
	{
		if (rec[lines[i][0]-1]==-2 && rec[lines[i][1]-1]==-2)
		{	m=rec[lines[i][2]-1]; flag++;	}
		else if (rec[lines[i][1]-1]==-2 && rec[lines[i][2]-1]==-2)
		{ 	m=rec[lines[i][0]-1]; flag++;	}
		else if (rec[lines[i][2]-1]==-2 && rec[lines[i][0]-1]==-2)
		{	m=rec[lines[i][1]-1]; flag++;	}
		if (flag==1)
		{
			if (m==-1)
				continue;
			else
				return m;
		}
	}
	randomize();
	while(1)
	{
		int t=random(9);
		if (isValid(rec[t]))
			return rec[t];
	}
}

void output(int m,char ch)
{
	m--;
	int i[]={3,3,3,6,6,6,9,9,9};
	int j[]={3,8,13,3,8,13,3,8,13};
	gotoxy(j[m]-1+X+1,i[m]-1+1);	cout<<" ";
	gotoxy(j[m]+X+1,i[m]+1);	cout<<ch;
	gotoxy(j[m]+1+X+1,i[m]+1);	cout<<ch;
	if (ch=='x')
	{
		if (hasWon(-1))
		{
			gotoxy(1,y++);
			save();
			cout<<"\n\tCONGRATULATIONS! YOU HAVE WON!!!";
			gotoxy(1,25);
			cout<<"<Press any key to go back to Main Menu>";
			getch();
			return ;
		}
	}
	else
	{
		if (hasWon(-2))
		{
			gotoxy(1,y++);
			save();
			cout<<"\n\tSORRY! YOU LOST THE GAME. BETTER LUCK NEXT TIME.";
			gotoxy(1,25);
			cout<<"<Press any key to go back to Main Menu>";
			getch();
			return ;
		}
	}
	(ch=='x')? computer():user();
	return;
}

void save()
{
	ofstream g("game_rec.dat",ios::binary | ios::app);
	G.sl=gno;
	for (int i=0;i<9;i++)
	{
		G.moves[i]=rec[i];
	}
	g.write((char*)&G,sizeof(G));
	g.close();
}

void load()
{
	clrscr();
	f.open("game_rec.dat",ios::binary);
	f.seekg(0L,ios::end);
	int last=f.tellg();
	if (f==NULL || last==0)
	{
		f.close();
		cout<<"NO SAVED GAME";
	}
	else
	{
		int code;
		cout<<"Enter the game number: ";
		cin>>code;
		if (code<1 || (code-1)*sizeof(G)>=last)
		{
			f.close();
			cout<<"\nOoops!!! Invalid Game Number";
		}
		else
		{
			f.seekg((code-1)*sizeof(G),ios::beg);
			f.read((char*)&G,sizeof(G));
			f.close();
			cout<<"\n\n\n";
			f.open("grid.txt");
			char c;
			while(!f.eof())
			{
				f.get(c);
				cout<<c;
			}
			f.close();
			for (int i=0,h=33,k=6;i<9;i++,h+=5)
			{
				if (i==3 || i==6)
				{
					k+=3;
					h=33;
				}
				gotoxy(h,k);
				cout<<" ";
				gotoxy(h+1,k+1);
				(G.moves[i]==-1)? cout<<'x':((G.moves[i]==-2)? cout<<'o':cout<<' ');
				gotoxy(h+2,k+1);
				(G.moves[i]==-1)? cout<<'x':((G.moves[i]==-2)? cout<<'o':cout<<' ');
			}
		}
	}
	gotoxy(1,25);
	cout<<"<Press any key to go back to Main Menu>";
	getch();
}

void loadGnumber()
{
	f.open("game_rec.dat",ios::binary);
	f.seekg(0L,ios::end);
	int nrec=f.tellg()/sizeof(G);
	if (nrec==0)
		gno=0;
	else
	{
		f.seekg((nrec-1)*sizeof(G),ios::beg);
		f.read((char*)&G,sizeof(G));
		gno=G.sl;
	}
	f.close();
	gno++;
}

void main()
{
	clrscr();
l3:	intro();
	grid();
	user();
	goto l3;
}0