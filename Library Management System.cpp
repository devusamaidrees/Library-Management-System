#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
fstream f1,f2,f3;
class Book{
	public:
	char Book_Id[20],Book_Name[20],Book_Auther_Name[20];
	void Create_Book();
	void Show_Book();
	void Store_Book();
	void Display_All_Books();
	void Display_Specific_Book(char* s);
	void Modify_Book(char* s);
	void Modify();
	void Delete_Book(char* s);
	char* retid()
	{
		return Book_Id;
	}
};
Book b1;
class Student:public Book{
	public:
	char Student_Name[20],Student_Admission_No[20],Book_Id[20]="Empty";
	int Book_Issue=0;
		void Create_Student_Record();
		void Show_Data();
		void Store_Record();
		void Display_All_Students();
		void Display_Specific_Student_Record(char*);
		void Modify_Student_Record(char*);
		void Modify_Record();
		void Delete_Student_Record(char*);
		char* retadmno()
		{
			return Student_Admission_No;
		}
		char* retBId()
		{
			strcpy(Book_Id,b1.Book_Id);
			return Book_Id;
		}
		char* retBID()
		{
			strcpy(Book_Id,"Empty");
			return Book_Id;
		}
		int retbno()
		{
			return Book_Issue;
		}
		void retbi()
		{
			Book_Issue=1;
		}
		void retBi()
		{
			Book_Issue=0;
		}
};
Student s1;
int Count=0,Exist=0;
void Student::Delete_Student_Record(char* s)
{
	int count=0,Exist=0;
	f1.open("Student",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(!strcmp(Student_Admission_No,s))
		{
			if(s1.retbno()==1)
			{
				Exist++;
			}
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	if(Exist==0)
	{
	f2.open("tempstudent",ios::out|ios::binary);
	f1.open("Student",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(strcmp(Student_Admission_No,s))
		{
			f2.write((char*)this,sizeof(*this));
		}
		else
		{
			count++;
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	f2.close();
	remove("Student");
	rename("tempstudent","Student");
	}
	else
	{
		cout<<"*******************************************************"<<endl;
		cout<<"    You Can't Delete Record Unless You Return Book"<<endl;
		cout<<"*******************************************************"<<endl;
	}
	if(count==0 && Exist==0)
	{
		cout<<"****************************"<<endl;
		cout<<"Record Not Found"<<endl;
		cout<<"****************************"<<endl;
	}
	else if(Exist==0 && count!=0)
	{
		cout<<"****************************"<<endl;
		cout<<"Record Deleted Successfully"<<endl;
		cout<<"****************************"<<endl;
	}
}
void Student::Modify_Record()
{
	if(s1.Book_Issue==0)
{
	Count=0;
	Exist=0;
	char X[20]="Empty";
	cout<<"Enter New Admission Number of Student :";
	cin.getline(Student_Admission_No,20);
	strcpy(X,s1.Student_Admission_No);
	f2.open("Student",ios::in|ios::binary);
	f2.read((char*)this,sizeof(*this));
	while(!f2.eof())
	{
		if(!strcmp(s1.retadmno(),X))
		{
			Count++;
		}
		f2.read((char*)this,sizeof(*this));
	}
	f2.close();
	if(Count==0)
	{
		strcpy(s1.Student_Admission_No,X);
		cout<<"Enter New Name of Student:";
		cin.getline(Student_Name,20);
	}
	else
	{
		cout<<"************************************"<<endl;
		cout<<"  This Admission No. Already Exist"<<endl;
		cout<<"************************************"<<endl;
	}
}
else
{
	Exist++;
}
}
void Student::Modify_Student_Record(char* s)
{
	int count=0;
	f1.open("Student",ios::out|ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
{
	if(!strcmp(Student_Admission_No,s))
	{
		f1.seekp(f1.tellp()-sizeof(*this));
		Modify_Record();
		if(Count==0)
		{
		f1.write((char*)this,sizeof(*this));
		count++;
		}
	}
	f1.read((char*)this,sizeof(*this));
}
	f1.close();
	if(count==0)
	{
		cout<<"********************"<<endl;
		cout<<"Record Not Found"<<endl;
		cout<<"********************"<<endl;
	}
	else if(Exist!=0)
	{
	cout<<"****************************************************************"<<endl;
	cout<<"     You Cannot Modify Student Record Before Returning Book"<<endl;
	cout<<"****************************************************************"<<endl;
	}
	else if(count==0 && Count==0)
	{
		cout<<"*****************************"<<endl;
		cout<<"Record Modified Successfully"<<endl;
		cout<<"*****************************"<<endl;
	}
}
void Student::Display_Specific_Student_Record(char* s)
{
	int count=0;
	f1.open("Student",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));	
	while(!f1.eof())
	{
		if(!strcmp(Student_Admission_No,s))
		{
			cout<<"***************************************************************************************************"<<endl;
			cout<<"                                           Student Details"<<endl;
			cout<<"***************************************************************************************************"<<endl;
			cout<<setw(20)<<"Student Name"<<setw(25)<<"Student Admission"<<setw(20)<<"Book_Issue"<<setw(20)<<"Book_Id"<<endl;
			cout<<"***************************************************************************************************"<<endl;
			Show_Data();
			count++;
		}
		f1.read((char*)this,sizeof(*this));	
	}
	f1.close();
	if(count==0)
	{
		cout<<"********************************"<<endl;
		cout<<"Student Record Not Found"<<endl;
		cout<<"********************************"<<endl;
	}
}
void Student::Display_All_Students()
{
	f1.open("Student",ios::in|ios::binary);
	f1.seekg(0);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		Show_Data();
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
}
void Student::Store_Record()
{
	if(Count==0)
	{
		s1.Book_Issue=0;
		strcpy(s1.Book_Id,"Empty");
		
	f1.open("Student",ios::app|ios::binary);
	f1.write((char*)this,sizeof(*this));
	f1.close();
	cout<<"\n****************************************"<<endl;
	cout<<"    Record Created Successfully"<<endl;
	cout<<"****************************************"<<endl;
	}
	else
	{
	cout<<"***************************************"<<endl;
	cout<<"   This Admission No. Already Exist"<<endl;
	cout<<"***************************************"<<endl;
	}
	
}
void Student::Show_Data()
{
	cout<<setw(20)<<Student_Name<<setw(20)<<Student_Admission_No<<setw(20)<<Book_Issue<<setw(25)<<Book_Id<<endl;
}
void Student::Create_Student_Record()
{
	Count=0;
	char X[20]="Empty";
	strcpy(X,"Empty");
	cout<<"Enter Admission Number of Student:";
	cin.ignore();
	cin.getline(Student_Admission_No,20);
	strcpy(X,Student_Admission_No);
	f1.open("Student",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
{	
	if(!strcmp(s1.Student_Admission_No,(X)))
	{
	Count++;
	}
	f1.read((char*)this,sizeof(*this));
}
f1.close();
	if(Count==0)
	{
		strcpy(s1.Student_Admission_No,X);
		cout<<"Enter Name of Student:";
		cin.getline(Student_Name,20);
	}
}
void Book::Delete_Book(char* s)
{
	int count=0;
	f2.open("tempbook",ios::out|ios::binary);
	f1.open("Book",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(strcmp(Book_Id,s))
		{
			f2.write((char*)this,sizeof(*this));
		}
		else
		{
			count++;
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	f2.close();
	remove("Book");
	rename("tempbook","Book");
	if(count==0)
	{
		cout<<"**************************"<<endl;
		cout<<"   Record Not Found"<<endl;
		cout<<"**************************"<<endl;	
	}
	else
	{
		cout<<"**********************************"<<endl;
		cout<<"   Record Deleted Successfully"<<endl;
		cout<<"**********************************"<<endl;
	}
}
void Book::Modify()
{
	Count=0;
	Exist=0;
	char X[20];
	strcpy(X,"Empty");
	cout<<"Enter New Book Id :";
	cin.getline(Book_Id,20);
	strcpy(X,b1.Book_Id);
	f2.open("Book",ios::in|ios::binary);
	f2.read((char*)this,sizeof(*this));
	while(!f2.eof())
	{
		if(!strcmp(b1.retid(),X))
		{
			Count++;
		}
		f2.read((char*)this,sizeof(*this));
	}
	f2.close();
	if(Count==0)
	{
		f2.open("Student",ios::in|ios::binary);
		f2.read((char*)&s1,sizeof(Student));
		while(!f2.eof())
		{
			if(!strcmp(s1.Book_Id,X))
			{
				Exist++;
			}
			f2.read((char*)&s1,sizeof(Student));
		}
		f2.close();
		if(Exist==0 && Count==0)
		{
			strcpy(b1.Book_Id,X);
			cout<<"Enter New Book Name :";
			cin.getline(Book_Name,20);
			cout<<"Enter New Book Auther Name :";
			cin.getline(Book_Auther_Name,20);
		}
		if(Exist!=0)
		{
		cout<<"****************************************************************************************"<<endl;
		cout<<"    The Record of This Book Id Already Exist in Student Record,Please Try Another Id"<<endl;
		cout<<"****************************************************************************************"<<endl;	
		}
	}
	if(Count!=0)
	{
		cout<<"************************************************"<<endl;
		cout<<"        This Book Id Already Exist"<<endl;
		cout<<"************************************************"<<endl;
	}
}
void Book::Modify_Book(char* s)
{
	int count=0;
	f1.open("Book",ios::in|ios::out|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(!strcmp(Book_Id,s))
		{
			count++;
			f1.seekp(f1.tellp()-sizeof(*this));
			Modify();
			if(Count==0 && Exist==0)
			{
			f1.write((char*)this,sizeof(*this));
			}
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();	
	if(count==0)
	{
		cout<<"**************************"<<endl;
		cout<<"   Record Not Found"<<endl;
		cout<<"**************************"<<endl;
	}
	else
	{
		cout<<"********************************"<<endl;
		cout<<"   Record Modified Successfully"<<endl;
		cout<<"********************************"<<endl;
	}

}
void Book::Display_Specific_Book(char* s)
{
	int count=0;
	f1.open("Book",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(!strcmp(Book_Id,s))
		{
			cout<<"******************************************************************"<<endl;
			cout<<"                         Book Details"<<endl;
			cout<<"******************************************************************"<<endl;
			cout<<setw(20)<<"Book Id"<<setw(20)<<"Book Name"<<setw(20)<<"Auther Name"<<endl;
			cout<<"******************************************************************"<<endl;
			Show_Book();
			count++;
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	if(count==0)
	{
		cout<<"**************************"<<endl;
		cout<<"   Record Not Found"<<endl;
		cout<<"**************************"<<endl;
	}
}
void Book::Display_All_Books()
{
	f1.open("Book",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		Show_Book();
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
}
void Book::Store_Book()
{
	if(Count==0 && Exist==0)
	{
	f1.open("Book",ios::app|ios::binary);
	f1.write((char*)this,sizeof(*this));
	f1.close();
	cout<<"*********************************"<<endl;
	cout<<"    Record Created Successfully"<<endl;
	cout<<"*********************************"<<endl;
	}
	else if(Count!=0)
	{
		cout<<"********************************"<<endl;
		cout<<"   This Book Id Already Exist"<<endl;
		cout<<"********************************"<<endl;
	}
	else if(Exist!=0)
	{
		cout<<"*******************************************************************************************"<<endl;
		cout<<"   The Record of This Book Id is Already Stored in Student Record, Please Try Another Id"<<endl;
		cout<<"*******************************************************************************************"<<endl;
	}
}
void Book::Show_Book()
{
	cout<<setw(20)<<Book_Id<<setw(20)<<Book_Name<<setw(20)<<Book_Auther_Name<<endl;
}
void Book::Create_Book()
{
	Count=0;
	Exist=0;
	char X[20];
	strcpy(X,"Empty");
	cout<<"Enter Book Id :";
	cin.ignore();
	cin.getline(Book_Id,20);
	strcpy(X,b1.Book_Id);
	f1.open("Book",ios::in|ios::binary);
	f1.read((char*)this,sizeof(*this));
	while(!f1.eof())
	{
		if(!strcmp(b1.Book_Id,X))
		{
			Count++;
		}
		f1.read((char*)this,sizeof(*this));
	}
	f1.close();
	if(Count==0)
	{
	f1.open("Student",ios::in|ios::binary);
	f1.read((char*)&s1,sizeof(Student));
	while(!f1.eof())
	{
		if(!strcmp(s1.Book_Id,X))
		{
			Exist++;
		}
		f1.read((char*)&s1,sizeof(Student));
	}
	f1.close();
	if(Exist==0 && Count==0)
	{
		strcpy(b1.Book_Id,X);
		cout<<"Enter Name of Book :";
		cin.getline(Book_Name,20);
		cout<<"Enter Auther Name :";
		cin.getline(Book_Auther_Name,20);
	}
}
}
class IssuedBooks{
	public:
	char Book_Id[20],Book_Name[20],Book_Auther_Name[20];
	void Show_Book()
{
	cout<<"Book Id :"<<Book_Id<<endl;
	cout<<"Book Name :"<<Book_Name<<endl;
	cout<<"Book Auther Name :"<<Book_Auther_Name<<endl;
}
char * retBId()
{
	return Book_Id;
}
};
IssuedBooks ib1;
int Admin_Menu()
{
	int b;
	char t[20];
	while(true)
	{
	cout<<endl<<endl<<"*******************************************************"<<endl;
	cout<<"                   ADMINISTRATOR MENU   "<<endl;
	cout<<"*******************************************************"<<endl<<endl;
	cout<<"1.CREATE STUDENT RECORD"<<endl;
	cout<<"2.DISPLAY ALL STUDENTS RECORD"<<endl;
	cout<<"3.DISPLAY SPECIFIC STUDENT RECORD"<<endl;
	cout<<"4.MODIFY STUDENT RECORD"<<endl;
	cout<<"5.DELETE STUDENT RECORD"<<endl;
	cout<<"6.CREATE BOOK"<<endl;
	cout<<"7.DISPLAY ALL BOOKS"<<endl;
	cout<<"8.DISPLAY SPECIFIC BOOK"<<endl;
	cout<<"9.MODIFY BOOK"<<endl;
	cout<<"10.DELETE BOOK"<<endl;
	cout<<"11.BACK TO MAIN MENU"<<endl;
	cout<<"please enter your choice (1-11)"<<endl;
	cin>>b;
	system("cls");
	switch(b)
	{
		case 1:{
			s1.Create_Student_Record();
			s1.Store_Record();
			break;
		}
		case 2:{
			cout<<"****************************************************************************************************"<<endl;
			cout<<"                                        Student Details"<<endl;
			cout<<"****************************************************************************************************"<<endl;
			cout<<setw(20)<<"Student Name"<<setw(25)<<"Student Admission"<<setw(20)<<"Book_Issue"<<setw(20)<<"Book_Id"<<endl;
			cout<<"****************************************************************************************************"<<endl;
			s1.Display_All_Students();
			break;
		}
		case 3:{
			cout<<"Enter Admission Number of Student :";
			cin.ignore();
			cin.getline(t,20);
			s1.Display_Specific_Student_Record(t);
			break;
		}
		case 4:{
			cout<<"Enter Admission Number of Student :";
			cin.ignore();
			cin.getline(t,20);
			s1.Modify_Student_Record(t);
			break;
		}
		case 5:{
			cout<<"Enter Admission Number of Student :";
			cin.ignore();
			cin.getline(t,20);
			s1.Delete_Student_Record(t);
			break;
		}
		case 6:{
			b1.Create_Book();
			b1.Store_Book();
			break;
		}
		case 7:{
			cout<<"******************************************************************"<<endl;
			cout<<"                           Book Details"<<endl;
			cout<<"******************************************************************"<<endl;
			cout<<setw(20)<<"Book Id"<<setw(20)<<"Book Name"<<setw(20)<<"Auther Name"<<endl;
			cout<<"******************************************************************"<<endl;
			b1.Display_All_Books();
			break;
		}
		case 8:{
			cout<<"Enter Book Id :";
			cin.ignore();
			cin.getline(t,20);
			b1.Display_Specific_Book(t);
			break;
		}
		case 9:{
			cout<<"Enter Book Id :";
			cin.ignore();
			cin.getline(t,20);
			b1.Modify_Book(t);
			break;
		}
		case 10:{
			cout<<"Enter Book Id :";
			cin.ignore();
			cin.getline(t,20);
			b1.Delete_Book(t);
			break;
		}
		case 11:{
			return(false);
			break;
		}
		default:{
			cout<<"*****************************"<<endl;
			cout<<"       Wrong Input"<<endl;
			cout<<"*****************************"<<endl;
			break;
		}
	}
}
}
void Issue(char* s,char* b)
{
	cout<<endl<<endl<<"*******************************************************"<<endl;
	cout<<"                    Book Issue "<<endl;
	cout<<"*******************************************************"<<endl<<endl;
	int count=0,t=0,counter=0;
	f1.open("Student",ios::in|ios::out|ios::binary);
	f2.open("Book",ios::in|ios::binary);	
	f1.read((char*)&s1,sizeof(Student));
	while(!f1.eof())
	{
		if(!strcmp(s1.retadmno(),s))
		{
			count++;
				f2.read((char*)&b1,sizeof(Book));
				while(!f2.eof())
				{
					if(!strcmp(b1.retid(),b))
					{
						t++;
						if(s1.retbno()==0)
						{
							counter++;
							f1.seekp(f1.tellp()-sizeof(Student));
							s1.retbi();
							s1.retBId();
							f1.write((char*)&s1,sizeof(Student));
						}
						else
						{
							cout<<"***********************************"<<endl;
							cout<<"You Haven't Return Previous Book"<<endl;
							cout<<"***********************************"<<endl;
						}
					}
					f2.read((char*)&b1,sizeof(Book));
				}
			break;
		}
		f1.read((char*)&s1,sizeof(Student));
	}
	f1.close();
	f2.close();
	if(count!=0 && t!=0 && counter!=0)
	{
		cout<<"*********************************"<<endl;
		cout<<"           Book Issued"<<endl;
		cout<<"*********************************"<<endl;
		f1.open("IssuedBooks",ios::app|ios::binary);
		f2.open("Book",ios::in|ios::binary);
		f2.read((char*)&b1,sizeof(Book));
		while(!f2.eof())
		{
			if(!strcmp(b1.retid(),b))
			{
				cout<<"Book Auther Name :"<<b1.Book_Auther_Name<<endl;
				cout<<"Book Id :"<<b1.Book_Id<<endl;
				cout<<"Book Name :"<<b1.Book_Name<<endl<<endl;
				f1.write((char*)&b1,sizeof(IssuedBooks));
			}
			f2.read((char*)&b1,sizeof(Book));
		}
		f1.close();
		f2.close();
		f1.open("TempBook",ios::out|ios::binary);
		f2.open("Book",ios::in|ios::binary);
		f2.read((char*)&b1,sizeof(Book));
		while(!f2.eof())
		{
			if(strcmp(b1.retid(),b))
			{
				f1.write((char*)&b1,sizeof(Book));
			}
			f2.read((char*)&b1,sizeof(Book));
		}
		f1.close();
		f2.close();
		remove("Book");
		rename("TempBook","Book");
	}
	else if(count!=0 && t==0)
	{
		cout<<"***************************"<<endl;
		cout<<"   Book No. Doesn't Exist"<<endl;
		cout<<"***************************"<<endl;
	}
	else if(count==0 && t==0)
	{
		cout<<"***************************"<<endl;
		cout<<" Admission No. Doesn't"<<endl;
		cout<<"***************************"<<endl;
	}
	
}
void Book_Issue()
{
	char x[20],y[20];
	cout<<"Enter Student Admission Number :";
	cin.ignore();
	cin.getline(x,20);
	cout<<"Enter Book Id :";
	cin.getline(y,20);
	Issue(x,y);
}
void Deposit(char* s,char* b)
{
	cout<<endl<<endl<<"*******************************************************"<<endl;
	cout<<"                    Deposit Book "<<endl;
	cout<<"*******************************************************"<<endl<<endl;
	int count=0,counter=0;
	f1.open("Student",ios::in|ios::out|ios::binary);
	f1.read((char*)&s1,sizeof(Student));
	while(!f1.eof())
	{
		if(!strcmp(s1.retadmno(),s))
		{
			count++;
			if(s1.retbno()==1)
			{
		f2.open("IssuedBooks",ios::in|ios::binary);
		f3.open("Book",ios::app|ios::binary);
		f2.read((char*)&ib1,sizeof(IssuedBooks));
		while(!f2.eof())
		{
			if(!strcmp(ib1.retBId(),b))
			{
				if(!strcmp(s1.Book_Id,b))
				{
			cout<<"*********************************************"<<endl;
			cout<<"                  Book Detail"<<endl;
			cout<<"*********************************************"<<endl;
			cout<<"Book Id :"<<ib1.Book_Id<<endl;
			cout<<"Book Name :"<<ib1.Book_Name<<endl;
			cout<<"Book Auther Name :"<<ib1.Book_Auther_Name<<endl<<endl;
			cout<<"**************************************************"<<endl;
			cout<<"          Book Deposited"<<endl;
			cout<<"**************************************************"<<endl;
			f3.write((char*)&ib1,sizeof(IssuedBooks));
			counter++;
			f1.seekp(f1.tellp()-sizeof(Student));
			s1.retBi();
			s1.retBID();
			f1.write((char*)&s1,sizeof(Student));
				}
			}
			f2.read((char*)&ib1,sizeof(IssuedBooks));
		}
		f2.close();
		f3.close();
			}
		}
		f1.read((char*)&s1,sizeof(Student));
	}
	f1.close();
	if(count!=0 && counter!=0)
	{
		f1.open("TempIssue",ios::out|ios::binary);
		f2.open("IssuedBooks",ios::in|ios::binary);
		f2.read((char*)&ib1,sizeof(IssuedBooks));
		while(!f2.eof())
		{
			if(strcmp(ib1.retBId(),b))
			{
				f1.write((char*)&ib1,sizeof(IssuedBooks));
			}
			f2.read((char*)&ib1,sizeof(IssuedBooks));
		}
		f1.close();
		f2.close();
		remove("IssuedBooks");
		rename("TempIssue","IssuedBooks");
	}
	if(count==0 && counter ==0)
	{
		cout<<"*********************************"<<endl;
		cout<<"   Admission No. Doesn't Exist"<<endl;
		cout<<"*********************************"<<endl;
	}
	if(count!=0 && counter==0)
	{
		cout<<"**************************************"<<endl;
		cout<<"     Wrong Book Id or Admisson No."<<endl;
		cout<<"**************************************"<<endl;
	}
}
void Deposit_Book()
{
	char x[20],y[20];
	cout<<"Enter Student Admission Number :";
	cin.ignore();
	cin.getline(x,20);
	cout<<"Enter Book Id :";
	cin.getline(y,20);
	Deposit(x,y);
}
int main()
{
	int a;
	while(true)
	{
	cout<<endl<<endl<<"***************************************************"<<endl;
	cout<<"            LIBRARY MANAGEMENT SYSTEM"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"1.ISSUE BOOK"<<endl;
	cout<<"2.DEPOSIT BOOK"<<endl;
	cout<<"3.ADMINISTRATOR MENU"<<endl;
	cout<<"4.EXIT"<<endl;
	cin>>a;
	system("cls");
	switch(a)
	{
		case 1:Book_Issue(); break;
		case 2:Deposit_Book();break;
		case 3:Admin_Menu(); break;
		case 4: return(false); break;
		default:
			cout<<"**************************"<<endl;
			cout<<"      Wrong Input"<<endl; break;
			cout<<"**************************"<<endl;
	}
}
}