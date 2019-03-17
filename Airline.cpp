#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

FILE*reservations, *flights , *crew , *tmpf , *fp  ;

struct flight //flight management
	{
		char fnumber[10];
		char date[10];
		char time[10];
		char destination[20];
		char crew[30];
		char pilot[10];
		int fare;
	}f1;
struct res //reservation management
	{
		char name[20];
		char fname[20];
		char passno[20];
		char nation[15];
		char contact[20];
	}e1;
struct crew //passenger record management
	{
		char name[100];
		char fathername[100];
		char CNIC[15];
		char DOB[50];
		char phone[50];
		char license[50];
		char profession[15];
	}c1;



reservation() //add new reservation
	{
	char flight_choice[10];
	char dest[20];
	flights=fopen("flights.txt" , "a+");
	printf("Enter your destination: ");
	gets(dest);
	system("CLS");
	rewind(flights);
	
	while(fread(&f1,sizeof(f1),1,flights)==1)
	{
	if(strcmpi(f1.destination , dest)==0)
	printf("\n| Flight Number= %s |\n| Date= %s |\n| Time= %s |\n| Destination=%s |\nFare= %d |\n",f1.fnumber,f1.date,f1.time,f1.destination,f1.fare);
	}
	rewind(flights);
	printf("Enter flight number to select the flight: ");
	gets(flight_choice);
	while(fread(&f1,sizeof(f1),1,flights)==1)
	{
	if(strnicmp(f1.fnumber , flight_choice , 5)==0)
	{
			printf("%s",f1.fnumber);
			strcat(flight_choice , ".txt");
			FILE *flight_file=fopen(flight_choice , "a+");
			
			reservations=fopen("reservations.txt" , "a+");
			system("CLS");
			printf("Enter your name: \n");
			gets(e1.name);
			fflush(stdin);
			printf("Enter your father's name /husband's name: \n");
			gets(e1.fname);
			fflush(stdin);
			printf("Enter your passport's number: \n");
			gets(e1.passno);
			fflush(stdin);
			printf("Enter your contact number:\n");
			gets(e1.contact);
			printf("Enter your nationality: \n");
			gets(e1.nation);
			fwrite(&e1, sizeof(e1),1,reservations);
			fwrite(&e1, sizeof(e1),1,flight_file);
			printf("\n\t\tRecord Added!");
			fflush(stdin);
			fclose(flight_file);
			break;
		}
		else 
		printf("\nFlight doesn't exists!");
		
	}
	
			fclose(flights);
			printf("\n\nPress y to enter another record or press m to show the main menu.\n");
			char temp=getch();
			if(temp=='y' || temp=='Y')
			reservation();
			fclose(reservations);	
	}
	
	edit_flight(){//flight_edit 
		
		char flight_edit[20];
				printf("Enter the flight number of the flight to edit: ");
				gets(flight_edit);
				
		flights=fopen("flights.txt" , "a+");
		rewind(flights);
		
				while(fread(&f1 , sizeof(f1) ,1 ,flights)==1)
				{
					if(strcmp(flight_edit,f1.fnumber )>0)
					{
						printf("Enter the new date: ");
						gets(f1.date);
						fwrite(&f1.date , sizeof(f1.date) , 1 ,flights);
						printf("Enter new time: ");
						gets(f1.time);
							fwrite(&f1.time , sizeof(f1.time) , 1 ,flights);
						
						
					}
				}
		
	}
				
	
new_flight()
{			char file_name[10];
			char ch[50];
			flights=fopen("flights.txt" , "a+");
			system("CLS");
			printf("Enter flight Number:");
			fflush(stdin);
			scanf("%s",ch);

			int r = strlen(ch);
			ch[r] = '.';
			ch[r+1] = 't';
			ch[r+2] = 'x';
			ch[r+3] = 't';
			memset(f1.fnumber, '\0', sizeof(f1.fnumber));
    		strncpy(f1.fnumber, ch , 5 );
	
	
			FILE *file_ptr;
			file_ptr = fopen(ch,"w");
	
	
			fflush(stdin);
			
			printf("Enter the date: ");
			scanf("%s",&f1.date);
			fflush(stdin);
			printf("Enter the time: ");
			scanf("%s",&f1.time);
			fflush(stdin);
			printf("Enter the destination: ");
			scanf("%s",&f1.destination);
			fflush(stdin);
			printf("Enter the crew: ");
			scanf("%s",&f1.crew);
			fflush(stdin);
			printf("Enter the name of pilot: ");
			scanf("%s",&f1.pilot);
			fflush(stdin);
			printf("Enter the fare: ");
			scanf("%d",&f1.fare);
			fflush(stdin);
			fwrite(&f1, sizeof(f1),1,flights);
			printf("\n\t\tRecord Added!");
			printf("\n\t\t============");
			printf("\nPress any key to continue");
			getch();
			fflush(stdin);
			fclose(flights);
}


view_flight()
{
	flights=fopen("flights.txt" , "a+");
	system("CLS");
	rewind(flights);
	while(fread(&f1,sizeof(f1),1,flights)==1)
	printf("Flight Number= %s\nDate= %s\nTime= %s\nDestination=%s\nCrew=%s\nPilot=%s\nFare= %d\n\n\n",f1.fnumber,f1.date,f1.time,f1.destination,f1.crew,f1.pilot,f1.fare);
	fflush(stdin);
	fclose(flights);
}

cancel_flight()
{
	FILE *temp_flights;
	flights=fopen("flights.txt","a+");
	char cancelflight[20];
	rewind(flights);
	printf("Enter the number of the flight which you want to cancel: ");
	temp_flights=fopen("temp_flights.txt","a+");
	gets(cancelflight);
	while(fread(&f1, sizeof(f1),1, flights)==1)
	{
		if(strcmpi(f1.fnumber,cancelflight)!=0)
		fwrite(&f1, sizeof(f1),1,temp_flights);
	}
	fclose(flights);
	fclose(temp_flights);
	strcat(cancelflight, ".txt");
	remove("flights.txt");
	remove(cancelflight);
	rename("temp_flights.txt","flights.txt");
}


cancel_res() //cancel reservation
{
	FILE *tmp_res;
	system("CLS");
	char cancel_reser[20];
	reservations = fopen("reservations.txt" , "a+");
	tmp_res = fopen("temp_res.txt" , "a+");
	printf("Enter the name of the reservation which you want to cancel");
	
	gets(cancel_reser);
	while(fread(&f1, sizeof(f1),1,reservations)==1)
	{
		if(strcmpi(e1.passno,cancel_reser)!=0)
		fwrite(&f1, sizeof(f1),1,tmp_res);
	}
	fclose(reservations);
	fclose(tmp_res);
	remove("reservations.txt");
	rename("temp_res.txt","reservations.txt");
	
	printf("\nPress y to cancel another reservation, or press any key to go back to main menu.");
	if(getch()=='y' || getch()=='Y')
	cancel_res();
	
}

view_res()
{
	char action;
	char search[20];
	system("CLS");
	reservations=fopen("reservations.txt" , "a+");
	printf("To view all reservations press 1\n To search for specific reservation press 2\n\nTo go back to main menu press 0");
	action=getch();
	switch(action)
	{
		case '1':
			{
				while(fread(&e1 , sizeof(e1) , 1 , reservations) ==1)
				system("CLS");
				printf("Name: %s\nFather Name: %s\nPassport Number: %s\nNationality: %s\nContact Number: %s" , e1.name,e1.fname,e1.passno,e1.nation,e1.contact);
				
				printf("Press any key to go back to main menu");
			}break;
		case '2':
			{
				system("CLS");
				printf("To search via name press 1\nTo search via passport number press 2");
				if (getch()=='1')
				{
					system("CLS");
					printf("Enter name: ");
					gets(search);
					while((fread(&e1 , sizeof(e1) , 1 , reservations) ==1))
					{
						if(strcmpi(e1.name , search)==0)
						printf("Name: %s\nFather Name: %s\nPassport Number: %s\nNationality: %s\nContact Number: %s" , e1.name,e1.fname,e1.passno,e1.nation,e1.contact);
					}
				}
				else if(getch()=='2')
				{
					system("CLS");
					printf("Enter passport: ");
					gets(search);
					while((fread(&e1 , sizeof(e1) , 1 , reservations) ==1))
					{
						if(strcmpi(e1.passno , search)==0)
						printf("Name: %s\nFather Name: %s\nPassport Number: %s\nNationality: %s\nContact Number: %s" , e1.name,e1.fname,e1.passno,e1.nation,e1.contact);
					}			
				}
			}	
	}
}

add_rec_crew() //crew record
{
	do
		{
			printf("Enter the name: ");
			scanf("%s",&c1.name);
			fflush(stdin);
			printf("Enter profession in airline: ");
			scanf("%s", &c1.profession);
			fflush(stdin);
			printf("Enter Father's name: ");
			scanf("%s",&c1.fathername);
			fflush(stdin);
			printf("Enter CNIC number: ");
			scanf("%s",&c1.CNIC);
			fflush(stdin);
			printf("Enter date of birth: ");
			scanf("%s",&c1.DOB);
			fflush(stdin);
			printf("Enter phone number: ");
			scanf("%s",&c1.phone);
			fflush(stdin);
			fwrite(&e1, sizeof(c1),1,fp);
			printf("\n\t\tRecord Added!");
			printf("\n\t\t============");
			printf("\nPress y to enter another record\n");
		}while(getch()=='y' || getch()=='Y');
}

add_rec_pilot() //pilot record
{
	do
		{
		printf("Enter the name: ");
		scanf("%s",&c1.name);
		fflush(stdin);
		printf("Enter Father's name: ");
		scanf("%s",&c1.fathername);
		fflush(stdin);
		printf("Enter CNIC number: ");
		scanf("%s",&c1.CNIC);
		fflush(stdin);
		printf("Enter date of birth: ");
		scanf("%s",&c1.DOB);
		fflush(stdin);
		printf("Enter phone number: ");
		scanf("%s",&c1.phone);
		fflush(stdin);
		printf("Enter License Number: ");
		scanf("%s",&c1.license);
		fflush(stdin);
		fwrite(&e1, sizeof(c1),1,fp);
		printf("\n\t\tRecord Added!");
		printf("\n\t\t============");
		printf("\nPress y to enter another record\n");
		}while(getch()=='y' || getch()=='Y');
}

main()
{
	{
		system("CLS");
		//reservations=fopen("reservation.txt","a+");
		char action;
		int user;
		char temp;
		printf("Press 1 to add new reservation\nPress 2 to manage flights\nPress 3 to manage reservation.\nPress 4 to manage crew management.\n");
		action=getch();
		
		switch (action)
		{
		case '1': //add reservation
			{
		 		system("CLS");
				reservation();		
				
				main();
				break;
		    }
		
			
		case '2': //manage flights
		{
			system("CLS");
			flights=fopen("flights.txt","a+");
			printf("Press 1 to add a new flight\nPress 2 to view flights\nPress 3 to edit flights\nPress 4 to cancel a flight\n\nTo go back to main menu press 0");
				char temp=getch();
			if(temp=='1')
				{
				new_flight();
				break;
				}	
			
			else if(temp=='2')
			{
				view_flight();
				printf("Press any key to go back to main menu");
				getch();
				main();
				break;	
			}
			
			else if(temp=='3') 				/*    */ //i've not worked on this part of the code 
			{	
			
			edit_flight();
			printf("Flight Updated");
			getch();
			main();
			break;
			}
			
			
			else if(temp=='4')
			{
			cancel_flight();
			printf("\t\t\nFlight Cancelled");
			printf("\nPress any key to continue");
			main();
			break;
			}
			
			else if(temp=='0')
			main();
			
			
		}
			
		case'3': //manage reservation
		{
			system("CLS");
			printf("Enter 1 to cancel a reservation\nEnter 2 to view reservation\n");
			temp=getch();
			if(temp=='1')
			{
				cancel_res();
				main();
			}
			
			else if(temp=='2')
			view_res();
			printf("\n\nPress any key to go back to main menu");
			getche();
			main();
		}
	
	case '4' : //crew management
	{
	system("CLS");
	printf("Press 1 to add crew details.\nPress 2 to add pilot details.\n");
	action=getch();
	FILE*fp;
	fp=fopen("crewmanagement.txt","a+");

	if(action=='1') //crew
	{
		add_rec_crew();
		printf("\nPress any key to continue");
		main();
		break;
	}
	
	else if(action=='2') //pilot
	{
		add_rec_pilot();
		printf("\nPress any key to continue");
		main();
		break;
	}
}
}
}
}



