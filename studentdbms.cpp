#include<iostream>
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<iomanip>
#include<cstdlib>
using namespace std;
int main()
{
	FILE *fp,*ft;
	char c,x;
	struct student
	{
		char fname[100],lname[100],course[100];
		int section;
	};
	struct student e;
	char xfname[100],xlname[100];
	long int recsize;
	fp=fopen("users.txt","rb+");
	if(fp==NULL)
	{
		fp=fopen("users.txt","wb+");
		if(fp==NULL)
		{
			puts("Sorry, Cannot open the file");
			return 0;
		}
	}
	recsize=sizeof(e);
	while(1)
	{
		system("cls");
		cout<<"*********STUDENT DATABASE MANAGEMENT SYSTEM*********";
		cout<<"\n\n1.Add Records\n2.List Records\n3.Modify Records\n4.Delete Records\n5.Exit\n\nSelect your choice:";
		fflush(stdin);
		c=getche();
		switch(c)
		{
			case '1':
				fseek(fp,0,SEEK_END);
				x='Y';
				while(x=='Y' || x=='y')
				{
					system("cls");
					cout<<"Enter your first name:";
					cin>>e.fname;
					cout<<"Enter your last name:";
					cin>>e.lname;
					cout<<"Enter the course:";
					cin>>e.course;
					cout<<"Enter your section:";
					cin>>e.section;
					fwrite(&e,recsize,1,fp);
					cout<<"\nAdd another record? (Y/N)";
					fflush(stdin);
					x=getchar();
				}
				break;
			case '2':
				system("cls");
				rewind(fp);
			    cout<<"*********VIEW RECORDS IN DATABASE*********";
			    cout<<"\n";
			    while(fread(&e,recsize,1,fp)==1)
			    {
			    	cout<<"\n";
			    	cout<<"\n"<<e.fname<<setw(10)<<e.lname;
			    	cout<<"\n";
			    	cout<<"\n"<<e.course<<setw(8)<<e.section;
				}
				cout<<"\n\n";
				system("pause");
				break;
			case '3':
				system("cls");
				x='Y';
				while(x=='Y' || x=='y')
				{
					cout<<"Enter last name of the student:";
					cin>>xlname;
					rewind(fp);
					while(fread(&e,recsize,1,fp)==1)
					{
						if(strcmp(e.lname,xlname)==0)
						{
							cout<<"Enter new first name:";
						    cin>>e.fname;
						    cout<<"Enter new last name:";
						    cin>>e.lname;
						    cout<<"Enter new course:";
						    cin>>e.course;
						    cout<<"Enter new section:";
						    cin>>e.section;
						    fseek(fp,-recsize,SEEK_CUR);
						    fwrite(&e,recsize,1,fp);
						    break;
						}
						else
						{
							cout<<"Sorry, Record not found.";
						}
					}
					cout<<"\nModify another record? (Y/N)";
					fflush(stdin);
					x=getchar();
				}
				break;
			case '4':
				system("cls");
				x='Y';
				while(x=='Y' || x=='y')
				{
					cout<<"Enter the last name of the student to delete the record:";
					cin>>xlname;
					ft=fopen("temp.dat","wb");
					rewind(fp);
					while(fread(&e,recsize,1,fp)==1)
						if(strcmp(e.lname,xlname)!=0)
						{
							fwrite(&e,recsize,1,ft);
						}
					fclose(fp);
					fclose(ft);
					remove("users.txt");
					rename("temp.dat","users.txt");
					fp=fopen("users.txt","rb+");
					cout<<"\nDelete another record? (Y/N)";
					fflush(stdin);
					x=getchar();
				}
				break;
			case '5':
				fclose(fp);
				cout<<"*********THANKYOU FOR USING THIS SOFTWARE! BYE*********";
				exit(0);
				break;
		}
	}
	system("pause");
	return 0;
}
