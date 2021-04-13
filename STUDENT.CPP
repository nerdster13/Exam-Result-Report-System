#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#include<alloc.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
struct student{
	int roll;
	char name[20];
	int mphy;
	int mchm;
	int mmat;
	int meng;
	int mcs;
	float per;
	char grade;
	struct student* next;
};
struct student* start = NULL;
void create();
void display();
void search();
void modify();
void del();
void menu();
void entry();
void result();
void classr();
void end(){
	FILE* fh;
	struct student* temp;
	temp = start;
	fh = fopen("student.txt","w");
	while(temp != NULL){
		fprintf(fh,"%d ",temp->roll);
		fprintf(fh,"%s ",temp->name);
		fprintf(fh,"%d ",temp->mphy);
		fprintf(fh,"%d ",temp->mchm);
		fprintf(fh,"%d ",temp->mmat);
		fprintf(fh,"%d ",temp->meng);
		fprintf(fh,"%d ",temp->mcs);
		fprintf(fh,"%f ",temp->per);
		fprintf(fh,"%c\n",temp->grade);
		temp = temp->next;
	}
	fclose(fh);
}
void begin(){
	FILE* fh;
	struct student* temp;
	struct student* news;
	struct student* prev;
	int roll = 0;
	char name[20];
	int mphy = 0;
	int mchm = 0;
	int mmat = 0;
	int meng = 0;
	int mcs = 0;
	float per;
	char grade, c;
	int i=0, count = 0;
	fh = fopen("student.txt","r");
	if(fh){
		for(c = getc(fh); c != EOF; c = getc(fh)){
			if(c == '\n'){
				count = count + 1;
			}
		}
		fh = fopen("student.txt","r");
		for(i=0; i<count; i++){
			fscanf(fh,"%d %s %d %d %d %d %d %f %c",&roll,&name,&mphy,&mchm,&mmat,&meng,&mcs,&per,&grade);
			news = (struct student*)malloc(sizeof(struct student));
			news->roll = roll;
			strcpy(news->name,name);
			news->mphy = mphy;
			news->mchm = mchm;
			news->mmat = mmat;
			news->meng = meng;
			news->mcs = mcs;
			news->per = per;
			news->grade = grade;
			if(start == NULL){
				start = news;
				news->next = NULL;
			}
			else{
				temp = start;
				while((temp != NULL) && temp->roll < roll){
					prev = temp;
					temp = temp->next;
				}
				news->next = prev->next;
				prev->next = news;
			}
		}
	}
}
int main(){
	int ch,gd = DETECT, gm;
	char c;
	clrscr();
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	clearviewport();
	setbkcolor(BLACK);
	outtextxy(200,210,"STUDENT REPORT CARD SYSTEM");
	outtextxy(360,360,"MADE BY : ROHIT PATIL");
	getch();
	closegraph();
	begin();
	menu();
	return 0;
}
void entry(){
	int ch;
	char c;
	do{
	clrscr();
	cout<<"\tENTRY MENU";
	cout<<"\n\t1. CREATE STUDENT RECORD\n\t2. DISPLAY ALL STUDENT RECORDS";
	cout<<"\n\t3. SEARCH STUDENT RECORD\n\t4. MODIFY STUDENT RECORD\n\t5. DELETE STUDENT RECORD";
	cout<<"\n\t6. BACK TO MAIN MENU\n\tPlease Enter Your Choice <1-6>";
	c = getch();
	ch = c - 48;
	switch(ch){
		case 1:
		create();
		break;
		case 2:
		display();
		break;
		case 3:
		search();
		break;
		case 4:
		modify();
		break;
		case 5:
		del();
		break;
	}
	}while(ch!=6);
}
void menu(){
	int ch;
	char c;
	do
	{
	clrscr();
	cout<<"\n\tMAIN MENU";
	cout<<"\n\t1. RESULT MENU\n\t2. ENTRY/EDIT MENU\n\t3. EXIT";
	cout<<"\n\tPlease Enter Your Choice <1-3>";
	c = getch();
	switch(c){
		case '1':
		result();
		break;
		case '2':
		entry();
		break;
	}
	}while(c!='3');
}
void classr(){
	int i;
	char buff[100];
	struct student* temp;
	clrscr();
	cout<<"\n\t\t\tALL STUDENTS RESULT";
	cout<<"\n=============================================================================";
	cout<<"\nR.No.\tName\t\tP\tC\tM\tE\tCS\t%age\tGrade";
	cout<<"\n=============================================================================";
	temp = start;
	while(temp != NULL){
		cout<<"\n"<<temp->roll<<"\t"<<temp->name<<"\t\t"<<temp->mphy<<"\t"<<temp->mchm<<"\t"<<temp->mmat<<"\t"<<temp->meng<<"\t"<<temp->mcs<<"\t"<<temp->per<<"\t"<<temp->grade;
		temp = temp->next;
	}
	getch();
}
void result(){
	int ch;
	char c;
	do{
	clrscr();
	cout<<"\n\tRESULT MENU";
	cout<<"\n\t1. Class Result";
	cout<<"\n\t2. Student Report Card";
	cout<<"\n\t3. BACK TO MAIN MENU\n\tPlease Enter Your Choice <1-3>";
	c = getch();
	ch = c - 48;
	switch(ch){
		case 1:
		classr();
		break;
		case 2:
		search();
		break;
	}
	}while(ch!=3);
}
void del(){
	int roll=0, i, flag=0;
	char ch[2],c;
	struct student* temp;
	struct student* prev;
	clrscr();
	cout<<"\n\n\tEnter The Roll No. To Delete: ";
	cin>>roll;
	temp = start;
	while(temp != NULL && temp->roll <= roll)
	{
		if(temp->roll == roll){
			flag = 1;
			break;
		}
		prev = temp;
		temp = temp->next;
	}
	if(flag == 0){
		cout<<"\n\tNot Found!";
		getch();
	}
	else{
		cout<<"\n\tARE YOU SURE?(Y/N)";
		c = getch();
		if(c == 'Y' || c == 'y'){
			if(temp == start){
				start = temp->next;
				free(temp);
			}
			else{
				prev->next = temp->next;
				free(temp);
			}
			end();
		}
	}
}
void modify(){
	int roll=0, i, flag=0;
	char name[20];
	int mphy = 0;
	int mchm = 0;
	int mmat = 0;
	int meng = 0;
	int mcs = 0;
	float per;
	char grade;
	char ch[2];
	struct student* temp;
	clrscr();
	cout<<"\n\tEnter The Roll No. To Modify: ";
	cin>>roll;
	temp = start;
	while(temp != NULL && temp->roll <= roll)
	{
		if(temp->roll == roll){
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	if(flag == 0){
		cout<<"\n\tNot Found!";
	}
	else{
		clrscr();
		cout<<"\n\t\t\tRoll no is "<<temp->roll;
		cout<<"\n\tEnter The Name ";
		cin>>name;
		cout<<"\tEnter Marks in Physics ";
		cin>>mphy;
		cout<<"\tEnter Marks in Chemistry ";
		cin>>mchm;
		cout<<"\tEnter Marks in Maths ";
		cin>>mmat;
		cout<<"\tEnter Marks in English ";
		cin>>meng;
		cout<<"\tEnter Marks in Computer Science ";
		cin>>mcs;
		per = (mphy + mchm + mmat + meng + mcs)/5;
		if(per >= 75){
			grade = 'A';
		}
		else if(per >= 60){
			grade = 'B';
		}
		else if(per >= 50){
			grade = 'C';
		}
		else if(per >= 35){
			grade = 'D';
		}
		else{
			grade = 'F';
		}
		strcpy(temp->name,name);
		temp->mphy = mphy;
		temp->mchm = mchm;
		temp->mmat = mmat;
		temp->meng = meng;
		temp->mcs = mcs;
		temp->per = per;
		temp->grade = grade;
		cout<<"\n\tData Has Been Saved Successfully!";
		end();
	}
	getch();
}
void search(){
	int roll=0, i, flag=0;
	char ch[2];
	struct student* temp;
	clrscr();
	cout<<"\n\tEnter The Roll No. To Search: ";
	cin>>roll;
	temp = start;
	while(temp != NULL && temp->roll <= roll)
	{
		if(temp->roll == roll){
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	if(flag == 0){
		cout<<"\n\tNot Found!";
	}
	else{
		clrscr();
		cout<<"\n\tRoll no is "<<temp->roll;
		cout<<"\n\tName is "<<temp->name;
		cout<<"\n\tMarks in Physics is "<<temp->mphy;
		cout<<"\n\tMarks in Chemistry is "<<temp->mchm;
		cout<<"\n\tMarks in Maths is "<<temp->mmat;
		cout<<"\n\tMarks in English is "<<temp->meng;
		cout<<"\n\tMarks in Computer Science is "<<temp->mcs;
		cout<<"\n\tPercentage is "<<temp->per;
		cout<<"\n\tGrade is "<<temp->grade;
	}
	getch();
}
void display(){
	struct student* temp;
	clrscr();
	temp = start;
	if(temp == NULL){
		cout<<"EMPTY";
		getch();
	}
	else{
		while(temp != NULL){
			cout<<"\n\tRoll no is "<<temp->roll;
			cout<<"\n\tName is "<<temp->name;
			cout<<"\n\tMarks in Physics is "<<temp->mphy;
			cout<<"\n\tMarks in Chemistry is "<<temp->mchm;
			cout<<"\n\tMarks in Maths is "<<temp->mmat;
			cout<<"\n\tMarks in English is "<<temp->meng;
			cout<<"\n\tMarks in Computer Science is "<<temp->mcs;
			cout<<"\n\tPercentage is "<<temp->per;
			cout<<"\n\tGrade is "<<temp->grade;
			cout<<"\n\t------------------------------------------------------------------------";
			getch();
			temp=temp->next;
		}
	}
}
void create(){
	int roll = 0;
	char name[20];
	int mphy = 0;
	int mchm = 0;
	int mmat = 0;
	int meng = 0;
	int mcs = 0;
	float per;
	char grade;
	char ch[2];
	int i;
	FILE* fh;
	struct student* news;
	struct student* temp;
	struct student* prev;
	clrscr();
	cout<<"\n\tEnter The Details of Student";
	cout<<"\n\tEnter The Roll No. ";
	cin>>roll;
	cout<<"\tEnter The Name ";
	cin>>name;
	cout<<"\tEnter Marks in Physics ";
	cin>>mphy;
	cout<<"\tEnter Marks in Chemistry ";
	cin>>mchm;
	cout<<"\tEnter Marks in Maths ";
	cin>>mmat;
	cout<<"\tEnter Marks in English ";
	cin>>meng;
	cout<<"\tEnter Marks in Computer Science ";
	cin>>mcs;
	news = (struct student*)malloc(sizeof(struct student));
	news->roll = roll;
	strcpy(news->name,name);
	news->mphy = mphy;
	news->mchm = mchm;
	news->mmat = mmat;
	news->meng = meng;
	news->mcs = mcs;
	per = (mphy + mchm + mmat + meng + mcs)/5;
	news->per = per;
	if(per >= 75){
		grade = 'A';
	}
	else if(per >= 60){
		grade = 'B';
	}
	else if(per >= 50){
		grade = 'C';
	}
	else if(per >= 35){
		grade = 'D';
	}
	else{
		grade = 'F';
	}
	news->grade = grade;
	if(start == NULL){
		start = news;
		news->next = NULL;
		cout<<"\n\tData Has Been Saved Successfully!";
		end();
	}
	else{
		temp = start;
		while((temp != NULL) && temp->roll < roll){
			prev = temp;
			temp = temp->next;
		}
		if(temp->roll == roll){
			cout<<"\n\tData For This Student Already Exists";
		}
		else{
			news->next = prev->next;
			prev->next = news;
			cout<<"\n\tData Has Been Saved Successfully!";
			end();
		}
	}
	getch();

}