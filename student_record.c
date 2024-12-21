#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	int roll;
	char name[20];
	float mark;
	struct student* next;
}ST;

//DISPLAING AND OPTION FRM USER

void display_table(void)
{

	printf("-----------------------------------------\n");
	printf("|      **** STUDENT RECORD MENU ****    |\n");
	printf("|  -----------------------------------  |\n");
	printf("|                                       |\n");
	printf("|        a/A : Add new record           |\n");
	printf("|        d/D : Delete a record          |\n");
	printf("|        s/S : Show the list            |\n");
	printf("|        m/M : Modify a record          |\n");
	printf("|        v/V : Save                     |\n");
	printf("|        e/E : Exit                     |\n");
	printf("|        t/T : Sort the list            |\n");
	printf("|        l/L : Delete all the records   |\n");
	printf("|        r/R : Reverse the list         |\n");
	printf("|                                       |\n");
	printf("-----------------------------------------\n");
	printf("Enter your Option:");
}

//ADD STUDENT RECORD //////////////

void add(ST**ptr)
{
	static int count=0;
	ST*temp=(ST*)malloc(sizeof(ST));
	count++;
	temp->roll=count;
	printf("Enter studet name and percentage:");
	scanf("%s %f",temp->name,&temp->mark);

	if(*ptr==0)
	{
		temp->next=*ptr;
		*ptr=temp;
	}
	else
	{
		ST*last=(*ptr);
		while(last->next!=0)
			last=last->next;
		temp->next=last->next;
		last->next=temp;
	}

}

//DELETING A SPECIFIC STUDENT DETAILS

void delete(ST**ptr)
{
	char op;
	int r_no;
	char na_me[20];

	printf("------------------------------------------\n");
	printf("|                                        |\n");
	printf("|     R/r:enter the roll no to delete   |\n");
	printf("|     N/n:enter the name to delete       |\n");
	printf("|                                        |\n");
	printf("------------------------------------------\n");
	scanf(" %c",&op);
	if((op=='r')||(op=='R'))
	//roll_based
	{
		printf("Enter the roll number to delete:");
		scanf("%d",&r_no);
                ST*prev;
		ST*temp=(*ptr);
		while((temp->roll!=r_no)&&(temp->next!=0))
		{      
			prev=temp;
			temp=temp->next;
		}
		if(temp->roll==r_no)
		{
			if(temp==*ptr)
				*ptr=(*ptr)->next;
			else{
		prev->next=temp->next;
		free(temp);
		}printf("Deleted succesfully!\n");
		}
		else if(temp->next==0)
			printf("Given roll number doesn't exist\n");
	}
        if((op=='n')||(op=='N'))
	//name based
	{
		int r_no;
		int count1=0;
		printf("Enter the name to delete:");
		scanf("%s",na_me);

		ST*temp=(*ptr);
		ST*prev;

		while(temp->next!=0)
		{
			if(!(strcmp(temp->name,na_me)))
			{
				printf("%d %s %f\n",temp->roll,temp->name,temp->mark);
				count1++;
			}
			temp=temp->next;
		}
		if(count1==0)
			printf("Given student name doesn't exist\n");
		else
		{
		printf("Enter the roll number to delete:");
		scanf("%d",&r_no);
		temp=(*ptr);
		while((temp->roll!=r_no)&&(temp->next!=0))
		{      
			prev=temp;
			temp=temp->next;
		}
		if(temp->roll==r_no)
		{
		prev->next=temp->next;
		free(temp);
        	printf("Removed succesfully\n");
		}
		else if(temp->next==0)
			printf("Given roll number doesn't exist\n");
		}	
	}

}

//SHOWING THE DATA//////////////

void show(ST*ptr)
{
	while(ptr!=0)
	{
		printf("%d %s %f\n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;
	}
	printf("No datas more...\n");
}

//MODIFYING//////////

void modify(ST**ptr)
{
	char op;
	printf("-----------------------------------------------\n");
	printf("|enter which record to search for modification|\n");
	printf("|                                             |\n");
	printf("|           N/n:to search for name            |\n");
	printf("|           P/p:percentage based              |\n");
	printf("|                                             |\n");
	printf("-----------------------------------------------\n");
	scanf(" %c",&op);

	if((op=='n')||(op=='N'))
        //name modify
	{
		int r_no;
		char na_me[20];
		char new_name[20];
		int count1=0;
		printf("Enter the name to modify:");
		scanf("%s",na_me);
		printf("Enter new name:");
		scanf("%s",new_name);

		ST*temp=(*ptr);

		while(temp!=0)
		{
			if(!(strcmp(temp->name,na_me)))
			{
				printf("%d %s %f\n",temp->roll,temp->name,temp->mark);
				count1++;
			}
			temp=temp->next;
		}
		if(count1==0)
			printf("Given student name doesn't exist...\n");
		else
		{
		printf("Enter the roll number to modify:");
		scanf("%d",&r_no);
		temp=(*ptr);
		while(temp->roll!=r_no)
		{ 
			temp=temp->next;
		}
		strcpy(temp->name,new_name);
		printf("Modified succesfully...!\n");
		}
	}
	if((op=='P')||(op=='p'))
        //percentage modify
	{
		int r_no;
		float ma_rk;
		float new_mark;
		int count1=0;
		printf("Enter the percentage to modify:");
		scanf("%f",&ma_rk);
		printf("Enter new percentage:");
		scanf("%f",&new_mark);

		ST*temp=(*ptr);

		while(temp!=0)
		{
			if(temp->mark==ma_rk)
			{
				printf("%d %s %f\n",temp->roll,temp->name,temp->mark);
				count1++;
			}
			temp=temp->next;
		}
		if(count1==0)
			printf("Sorry..!Given mark doesn't exist\n");
		else
		{
		printf("Enter the roll number to modify:");
		scanf("%d",&r_no);
		temp=(*ptr);
		while(temp->roll!=r_no)
		{ 
			temp=temp->next;
		}
		temp->mark=new_mark;
		printf("Modified succesfully\n");
		}
	}
}

//SAVING//////////

void save(ST*ptr)
{
	FILE*fs=fopen("data.txt","w");
	while(ptr!=0)
	{
		fprintf(fs,"%d %s %f \n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;
	}
	printf("Data is saved succesfully\n");
}

//EXIT/////////////////

int Exit(ST*ptr)
{
	char op;
	printf("------------------------------------------\n");
        printf("|      enter                             |\n");
        printf("|                                        |\n");
        printf("|           E/e:exit without saving      |\n");
        printf("|           S/s:save and exit            |\n");
        printf("|                                        |\n");
        printf("------------------------------------------\n");
	scanf(" %c",&op);
        
	if((op=='E')||(op=='e'))
	{
		printf("Are you sure for exiting with out saving! (y/n):\n");
		scanf(" %c",&op);
        	if((op=='y')||(op=='Y'))
			return 0;
		if((op=='n')||(op=='N'))
		{
			//save(ptr);
			return 1;
		}
	}
	else if((op=='S')||(op=='s'))
	{
		save(ptr);
		return 0;
	}
	else
	{
		printf("Invalid option...!\n");
	}
}

/// COUNT OF DATA ////////////

int count(ST*ptr)
{
	int c=0;
	while(ptr!=0)
	{
		c++;
		ptr=ptr->next;
	}
	return c;
}

//SORTING ///////////

void sort(ST*ptr)
{
	char op;
	int i,j,c=count(ptr);
	ST temp;
	int size=sizeof(ST)-sizeof(ST*);
	printf("-------------------------------------------\n");
        printf("|     enter                               |\n");
        printf("|                                         |\n");
        printf("|           N/n:sort by name              |\n");
        printf("|           P/p:sort by percentage        |\n");
        printf("|                                         |\n");
        printf("-------------------------------------------\n");
	scanf(" %c",&op);

	ST**p=(ST**)malloc(c*sizeof(ST*));
	for(i=0;i<c;i++)
	{
		p[i]=ptr;
		ptr=ptr->next;
	}
	
        if((op=='p')||(op=='P'))
	{
        // on basis of percentage
	for(i=0;i<c-1;i++)
	{
		for(j=i+1;j<c;j++)
		{
			if(p[i]->mark<p[j]->mark)
			{
				memcpy(&temp,p[i],size);
				memcpy(p[i],p[j],size);
				memcpy(p[j],&temp,size);
			}
		}
	}
	ptr=p[0];
	while(ptr!=0)
	{
		printf("%d %s %f\n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;
	}
	}
	if((op=='n')||(op=='N'))
	{
        // on basis of name
	for(i=0;i<c-1;i++)
	{
		for(j=i+1;j<c;j++)
		{
			if((strcmp(p[i]->name,p[j]->name))>0)
			{
				memcpy(&temp,p[i],size);
				memcpy(p[i],p[j],size);
				memcpy(p[j],&temp,size);
			}
		}
	}

	ptr=p[0];
	while(ptr!=0)
	{
		printf("%d %s %f\n",ptr->roll,ptr->name,ptr->mark);
		ptr=ptr->next;
	}
	
	}
}
	
//// DELETE ALL /////////

void del_all(ST**ptr)
{
	char op;
	printf("Are you sure to delete all(y/n):");
	scanf(" %c",&op);
	if((op=='y')||(op=='Y'))
	{
	ST*temp;
	while(*ptr!=0)
	{
		temp=(*ptr);
		*ptr=(*ptr)->next;
		free(temp);
	}
	printf("Succesfully deleted all datas!\n");
	}
}

// REVERSE_PRINTING //////////

void reverse(ST*ptr)
{
	ST*temp=ptr;
	int i,j,c=count(ptr);
	for(i=0;i<c;i++)
	{
		ptr=temp;
		for(j=0;j<c-1-i;j++)
			ptr=ptr->next;
		printf("%d %s %f\n",ptr->roll,ptr->name,ptr->mark);
	}
	printf("Data is reversed!\n");
}

//MAIN //////////////

int main()
{
	char op,op1;
	system("clear");
	ST*hptr=0;
	while(1)
	{
        display_table();
	scanf(" %c",&op);
	 if((op=='a')||(op=='A'))
	 {
		do{
		add(&hptr);
		printf("do you want to enter another node\n");
		scanf(" %c",&op1);
		}while((op1=='y')||(op1=='Y'));
	 }
	 else if((op=='d')||(op=='D'))
		delete(&hptr);
	 else if((op=='s')||(op=='S'))
                show(hptr);
	 else if((op=='m')||(op=='M'))
                modify(&hptr);
	 else if((op=='v')||(op=='V'))
                save(hptr);
	 else if((op=='t')||(op=='T'))
                sort(hptr);
	 else if((op=='l')||(op=='L'))
                del_all(&hptr);
	 else if((op=='r')||(op=='R'))
                reverse(hptr);
	 else if((op=='e')||(op=='E'))
	 {
                  if((Exit(hptr))==0)
		  break;
		  else
		 printf("exit canceled,return to choose the option");
	 }

	}
	printf("process completed\n");
}

