#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<time.h>
#include<process.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>

#define FOUR 1
#define TWO 2

int parkinfo[4][10] ;  		/* a 2-D array to store number of vehicle parked */
int vehcount ;  			/* to store total count of vehicles */
int fourcount ;				/* stores total count of cars */
int twocount ;  			/*stores total count of two wheelers*/
int choice1;				/* stores total count of four wheelers */

void option();

/*--------------------- This give time to/from the system--------------------------------------*/
struct tm* datetime()
{
        time_t ts;
        struct tm *ct;

        ts = time(NULL);
        ct = localtime(&ts);
		return ct ;
}


class checkin
{
	protected:	
		int type, number;
		int row, col;
		int tarr[2];
		int h1,m1,s1,mint,d1,y1;

	public:
		checkin()
		{row=0;col=0;}
		void displaymenu();
		void entry();
		int getfreerowcol();
		void add();
		void addonstart();
		void insertrecord(struct tm *ct );
		void displaytotal();
		void backupr();
		void backupw();
		void writearrival();
		void readarrival();
		void writedepart();
		void readdepart();
		void writebackup();
		void readbackup();
		};


	
class checkout : public checkin
{
	private:
		int SECOND, MINUTE, HOUR;
		int h2,m2,s2,mint2,d2,y2;
		double total;
	
	public:
		void leave();
		int getrcbyinfo();
		void insertrecord2(struct tm *ct);
		void getarrivaltime(int);
		void timemoney();
		void del();
};

class order
{
	private:
		int r, c ;

	public:
		void displayorder();
};


void checkin::writearrival()
{
	ofstream fout;
	fout.open("arrival1.txt", ios::app);
	fout.write((char *)this,sizeof(*this));
	fout.close();
}

void checkin::readarrival()
{
	ifstream fin;
	fin.open("arrival1.txt");
	fin.read((char *)this,sizeof(*this));
	fin.close();
}


void checkin::writedepart()
{
	ofstream fout;
	fout.open("depart1.txt", ios::app);
	fout.write((char *)this,sizeof(*this));
	fout.close();
}

void checkin::readdepart()
{
	ifstream fin;
	fin.open("depart1.txt");
	fin.read((char *)this,sizeof(*this));
	fin.close();
}


void checkin::writebackup()
{
	ofstream fout;
	fout.open("backupwr1.txt", ios::app);
	fout.write((char *)this,sizeof(*this));
	fout.close();
}

void checkin::readbackup()
{
	ifstream fin;
	fin.open("backupwr1.txt");
	fin.read((char *)this,sizeof(*this));
	fin.close();
}




/*----------------------------DISPLAY MENU----------------------------*/
void checkin::displaymenu()
{
	clrscr();
	cout<<"\t\t\t\t Parking Management System\n";
	cout<<"\t\t\t\t   Kantipur City College\n";
	cout<<"\t\t\t\t-----------------------------\n";
	cout<<"Main Menu\n";
	cout<<"1. Check In\n";
	cout<<"2. Total Vehicles Parked\n";
	cout<<"3. Display order in which vehicles are parked\n";
	cout<<"4. Check Out\n";
	cout<<"5. Exit\n";
	cout<<"\n---------------------------------------\n";	
	cout<<"Enter the corresponding number :";
	cin>>choice1;
}


void order::displayorder()
{	
	clrscr();
	cout<<"\n-------------Four Wheelers Available Slot---------------------\n";
	for ( r = 0 ; r < 4 ; r++ )
	{
		if ( r == 2 )
		cout<<"\n\n-------------Two Wheelers Available Slot ---------------------\n";
		for ( c = 0 ; c < 10 ; c++ )
			cout<<"\t"<<parkinfo[r][c]<<"\t";    
		cout<<"\n";
	}
	cout<<"Press any key to continue:"<<endl;
}


/*------------------------------------------------------ CHECKIN PORTION--------------------------------------------- */


void checkin :: entry()
{
	clrscr();
	type = 0 ;
	cout<<"Entry Vehicle Type";
	cout<<"VECHICLE TYPE		    COST(per hour)\n";
	cout<<"1.FOUR WHEELER            100    \n";
	cout<<"2.TWO WHEELER             50   \n" ;
	cout<<"3. Back\n";
	cout<<"\n___________________________________________\n\n";	
		
/* -----------------------------check for vehicle type ----------------------------*/
          
	while ( type != FOUR && type != TWO )
	{
		cout<<"Enter vehicle type (1 for Four Wheeler / 2 for Two Wheeler ): \n";
		cin>>type;
		cout<<"Enter vehicle number: ";
		cin>>number;		
		
		if ( type != FOUR && type != TWO )
		{
			if(type==3)
				option();
			
			else
			{
			 cout<<"\nInvalid vehicle type. TRY AGAIN\n\n";
			 getch();
			}
		}		
	}
	
	
	if ( type == FOUR || type == TWO )
	{
		getfreerowcol();
					
		if ( tarr[0] != -1 && tarr[1] != -1 )
		{
			row = tarr[0] ;
			col = tarr[1] ;
			add();
		}
		
		else
		{
			cout<<"\n*** Sorry, No space available *** \n";
			getch();
			option();
		}
	}
	
	else
	{
		cout<<"Invalid type\n";
		getch();
		option();
	}
				
	cout<<"\nPress any key to continue...";
	getch();
	option();

}		


/*-------------------------------GET ROW and COLUMN FOR PARKING--------------------------------------*/
int checkin :: getfreerowcol()
{
  int r, c, fromrow = 0, torow = 2 ;

  if ( type == TWO )
  {
    fromrow += 2 ;
    torow += 2 ;
  }

	for ( r = fromrow ; r < torow ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkinfo[r][c] == 0 )
			{
				tarr[0] = r ;
				tarr[1] = c ;
				return 0;
			}
		}
	}

	
	if ( r == 2 || r == 4 )
	{
		tarr[0] = -1 ;
		tarr[1] = -1 ;
	}
	return 0;
}


/*----------------------------------- Adds total count of  vehicles parked ------------(GLOBAL)---------------*/
void checkin :: add()
{

 	if ( type == FOUR )
      fourcount++ ;
    else
    	twocount++ ;
	
		vehcount++ ;
	
	parkinfo[row][col] = number ;
		 
	insertrecord(datetime());
	backupw();
	writebackup();
}



/* ------------------- STORES RECORDS IN A FILE----------------------(type, number, row, col, date/time)-------------FILE NAME : arrival.txt ------------------------------------------------------(PROBLEM AREA)*/	 
void checkin :: insertrecord(struct tm *ct)
{
	//ofstream fout("arrival.txt", ios::app);
	
	//fout<<"\n\nVehicle number                         : "<<number<<endl;
	//fout<<"Vehicle Type(4 wheeler =1, 2 wheeler =2) : "<<type<<endl;
	//fout<<"Row    :"<<row<<endl;
	//fout<<"Column :"<<col<<endl;
	
	y1=ct->tm_year + 1900;
	m1=ct->tm_mon + 1;
	d1=ct->tm_mday;
	
	h1=ct->tm_hour;
	mint=ct->tm_min;
	s1=ct->tm_sec;
	
	//fout<<"\nFull Date: "<<y1<<":"<<m1<<":"<<d1<<":"<<h1<<":"<<mint<<":"<<s1<<endl;
	//fout<<"----------------------------------------------"<<endl;
	//fout.close();
	writearrival();
}	



/* -------------------------- KEEPS VEHICLE RECORD BACKUPS FOR FUTURE REFERENCES---------------------------------------FILE NAME : backupwr.txt---------------------- */
void checkin :: backupw()
{
    int r,c ;
	ofstream fout("backupwr.txt");
    
	for(r=0;r<4;r++)
	for(c=0;c<10;c++)
    {
		fout<<"\n";
		fout<<"Vehicle Number :"<<parkinfo[r][c]<<endl;

        fout<<"Row    : "<<r<<endl;
        fout<<"Column : "<<c<<endl;

        fout<<"Total Vehicle Count       : "<<vehcount<<endl;
        fout<<"Total Four Wheelers Count : "<<fourcount<<endl;
        fout<<"Total Two Wheelers Count  : "<<twocount<<endl;
		fout<<"----------------------------------------------"<<endl;
    }
        fout.close();
}	



/*--------------------------- READS THE CONTENT OF BACKUP---------------------------------------- FILE NAME : backupwr.txt---------------------------------------*/
void checkin :: backupr()
{
	int r,c ;
    int park[4][10];
 
	ifstream fin("backupwr.txt");   

	int rr, cc;
	//, veh, four, two, numb;
	for(r=0;r<4;r++)
	for(c=0;c<10;c++)
    {

		fin>>"\n";
		fin>>park[r][c];
		number = park[r][c];

        fin>>rr;
        fin>>cc;

        fin>>vehcount;
        fin>>fourcount;
        fin>>twocount;

		if(number!=0)
		{
		
			if ( r == 0 || r == 1 )
			addonstart();
		else
			addonstart();
		}
    
	}
         fin.close();

}


/*------------------------------- ADDS RECORD IN THE BEGINNING FROM THE FILE---------------------------------------- */
void checkin :: addonstart ()
{
	if ( type == FOUR )
      fourcount++ ;
    else
		twocount++ ;

    vehcount++ ;
	parkinfo[row][col] = number ;
}


/*------------------------------ Displays Total vehicles that are in the lot-----------------------------------*/
void checkin :: displaytotal()
{
		clrscr();
		cout<<"\nTotal no. of vehicles parked     	: "<<vehcount<<endl;
		cout<<"\nTotal no. of Two Wheelers Parked	: "<<twocount<<endl;
		cout<<"\nTotal no. of Four Wheelers Parked	: "<<fourcount<<endl;
		
		cout<<"\n\n Press any key to exit to Menu ...";
		getch();
		option();		
}




/*------------------------------------------------------ CHECKOUT PORTION--------------------------------------------- */

void checkout :: leave()
{
	clrscr();
	cout<<"------------------------Departure of Vehicle----------------------\n";
    type = 0 ;
	
    
	/* check for vehicle type */
    while ( type != FOUR && type != TWO )
    {
		cout<<"VECHICLE TYPE		    COST(per hour)\n";
		cout<<"1.FOUR WHEELER            100    \n";
		cout<<"2.TWO WHEELER             50   \n" ;
		cout<<"3. Back\n";
		cout<<"\n___________________________________________\n\n";	
		cout<<"\nEnter vehicle type : ";
        cin>>type;
	    
		if ( type != FOUR && type != TWO)
		{		
			if(type==3)
				option();
			else
			{
				cout<<"\nInvalid Entry.\n";
				getch();
			}
		}
	}
	
	cout<<"Enter number: ";
	cin>>number;

	
	if ( type == FOUR || type == TWO )
	{
 			getrcbyinfo();
			if ( tarr[0] != -1 && tarr[1] != -1 )
			{
				
				insertrecord2(datetime());
				
				getarrivaltime(number);
				col = tarr[1] ;
              
				/* if the vehicle is four wheeler */
				if ( type == FOUR )
				{
					row = tarr [0] ;
					del() ;
				}
				
				/* if the type is two wheeler*/
				
				else
				{
					row = tarr [0] ;
					del() ;
				}
			}
			
			else 
			{	
				cout<<"\nInvalid Four Wheeler's Number\n";
				getch();
				leave();
			}
	}	
}



/*------------------------------CHECKS THE INPUT NUMBER FROM THE SLOT------------------------------ */

int checkout :: getrcbyinfo()
{
	int r, c, fromrow = 0, torow = 2 ;

	if( type == TWO )
	{
		fromrow += 2 ;
		torow += 2 ;
	}

	for ( r = fromrow ; r < torow ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkinfo[r][c] == number )
			{
				tarr[0] = r ;
				tarr[1] = c ;
				return 0;
			}
		}
	}

	
	if ( r == 2 || r == 4 )
	{
		tarr[0] = -1 ;
		tarr[1] = -1 ;
	}
	return 0;
}


/* -------------------- STORES DEPART TIME NUMBER IN FILE------------------------ FILE NAME: depart.txt-------------------------------------(PROBLEM AREA)*/
void checkout :: insertrecord2(struct tm *ct )
{
	ofstream fout("depart.txt", ios::app);

	fout<<"\nVehicle Number :"<<number<<endl;

	y2=ct->tm_year + 1900;
	m2=ct->tm_mon + 1;
	d2=ct->tm_mday;
	
	h2=ct->tm_hour;
	mint2=ct->tm_min;
	s2=ct->tm_sec;
	
	fout<<"Full Time : "<<y2<<":"<<m2<<":"<<d2<<":"<<h2<<":"<<mint2<<":"<<s2<<endl;
	fout<<"----------------------------------------------"<<endl;
	fout.close();
}



/*--------------------- CALCULATES TIME------------------------------------------------------- */
void checkout :: getarrivaltime(int tnum)
{

    int mon,day,year,hour,min,sec;
    int year1,mon1,day1,hour1,min1,sec1;
    int mon2,day2,year2,hour2,min2,sec2;
    int mon3,day3,year3,hour3,min3,sec3;
	
	
	ifstream fin("arrival.txt");
	while(fin)
	{		
		fin>>number;
		fin>>type;
		fin>>row;
		fin>>col;
		fin>>year >> mon >> day;
		fin>>hour>> min >> sec;
	
	fin.read((char *)this,sizeof(*this)); ////////////////////////////////////////////////////////////////ISWORI DADA
	if(number==tnum)
		{
			sec2=sec;
			min2=min;
			hour2=hour;
			day2=day;
			mon2=mon;
			year2=year;
		}
	}	
	fin.close();
		


	ifstream fin1("depart.txt");

	while(fin1)
	{	
		fin1>>number;
		fin1>>day >> mon >> year;
		fin1>>hour>> min >> sec;
	
		if(number==tnum)
		{
			sec3=sec1;
			min3=min1;
			hour3=hour1;
			day3=day1;
			mon3=mon1;
			year3=year1;
		}
	}	
		fin1.close();
		
		
	int tsec1,tsec2,tsec3;
    tsec1 = sec3;
    tsec1 = tsec1 + min3*60;
    tsec1 = tsec1 + (hour3*60)*60;
	tsec2 = sec2;
    tsec2 = tsec2 + min2*60;
    tsec2 = tsec2 + (hour2*60)*60;

    tsec3 = tsec1 - tsec2 ;
    int second , minute ,hours;
    int secc , temp1,temp2,temp3,temp4;
    second = tsec3 % 60 ;
    temp1 = tsec3 - second ;
    temp2 = temp1/60 ;
    minute = temp2 % 60 ;
    temp4 = temp2 - minute ;
    hours = temp4 /60 ;
	
		HOUR = hours;
		MINUTE = minute;
		SECOND = second;
	
	cout<<"Vehicle Has Been Parked for :"<< hours  <<":" <<minute << ":" << second <<endl;	
	timemoney();
	cout<<"\nPress any key to continue...\n";
	getch();
	option();
}



/* ---------------------------------------------- Calculates Price with respect to time--------------------------------- */
void checkout :: timemoney()
{
	int tsec1,tsec2,tsec3;
    tsec1 = SECOND;
    tsec1 = tsec1 + MINUTE*60;
    tsec1 = tsec1 + (HOUR*60)*60;

	if (type == FOUR)
	{
		total=tsec1*0.0277;
		cout<<"Total price : " <<total;
	}
	
	else
	{
		total=tsec1*0.013889;
		cout<<"Total price : " <<total;
	}
}
	

/* ---------------------------------------------- Clears departed vehicle count from the slot -------------------------------- */

void checkout :: del()
{
	parkinfo[row][col] = 0 ;

	if (type == FOUR)
		fourcount-- ;
  
	else
		twocount-- ;

	vehcount--;
	backupw();
}



void option()
{
	checkout C;	
	C.displaymenu();
	order O;
	
	while((choice1<6&&choice1>0))
	{
    
		
		if(choice1==1)
		{
			C.entry();
			getch();
			option();
		}
	
			
		else if(choice1==2)
		{
			C.displaytotal();
			getch();
			option();
		}	
		
		else if(choice1==3)	
		{	
			O.displayorder();
			getch();
			option();
		}
	
		else if(choice1==4)
		{
			C.leave();
			getch();
			option();
		}
	
		else if(choice1==5)
			exit(0);
	
		
		else
		{
			cout<<"Invalid Input Given.. ";
			getch();
			option();
		}
	}
}


/*-------------------------------MAIN FUNCTION-------------------------------------- */
int main()
{
	checkout X;
	X.backupr();
	clrscr();
	
	option();
	getch();
	return 0;
	
}

