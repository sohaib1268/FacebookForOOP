#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<windows.h>

using namespace std;


class Base;
class Page;
class User;
class Facebook;
class Date;
class Post;
class Activity;
class Comments;
class Helper;


class Helper
{
public:
	static int strlen(const char* str)
	{
		int i = 0;
		for(; str[i] != '\0';i++);
		return i;
	}

	static char* GetStringFromBuffer(const char* str1)
	{
		if(str1 == NULL)
			return NULL;

		int size = strlen(str1);
		char* str = new char[size + 1];
		for(int i = 0; str1[i] != '\0';i++)
			str[i] = str1[i];
		str[size] = '\0';
		return str;
	}

	static inline char* StringConcatenate(char* string1, char* string2) //used by + operator to concatenate 2 strings without space
	{
		int lengthString1 , lengthString2 , newStringLength = 0; 
		int stringIndex = 0;

		lengthString1 = strlen(string1);
		lengthString2 = strlen(string2);
		newStringLength = (lengthString1 + lengthString2) + 1;

		char *newString; 
		newString = new char[newStringLength];
	
	

		for(int i = 0 ; i < lengthString1 ;)
		{
			newString[stringIndex] = string1[i];
			stringIndex++;
			i++;
		}
	
		for(int j = 0 ; j < lengthString2 ; )
		{
			newString[stringIndex] = string2[j];
			stringIndex++;
			j++;
		}
	
		newString[stringIndex] = '\0';
		
		return newString;
	}

	static inline bool StringCompare(char* str1,char* str2) //comparing roll numbers 
	{
		bool check = true;
		if(strlen(str1) == strlen(str2))
		{
			for(int i = 0 ; i < strlen(str1) ; i++) //userlist is str1 idtosearch is str2
			{
				if(str2[i] != str1[i]) 
				{
					return false;
				}
				else
				{
					check = true;
				}
			}
		}
		else if(strlen(str1) != strlen(str2))
		{
			return false;
		}
		if(check == true)
		{
			return true; 
		}
		return false;
	}
};

class Base
{
protected:
	char* ID;
public:
	
	Base()
	{
		ID = 0;
	}

	void setBaseID(char* sentID)
	{
		ID = sentID;
	}

	char* getID()
	{
		return ID;
	}
	
	virtual ~Base()
	{
		if(ID)
		{
			delete[] ID;
		}
	}

	virtual void AddPostToTimeLine(Post* ptr) = 0;

	virtual void PrintName() = 0;
	
};

class Date
{
private:
	static Date CurrentDate;
	int day;
	int month;
	int year;
public:
	Date()
	{
		day = 0; //this ka day
		month = 0;
		year = 0;
		//Date = this->CurrentDate;
	}

	static void SetCurrentDate(int sentday , int sentmonth , int sentyear)
	{
		CurrentDate.day = sentday;
		CurrentDate.month = sentmonth;
		CurrentDate.year = sentyear;
	}

	void LoadDataFromFile(ifstream& fileopenforposts)
	{
		fileopenforposts>>day;
		fileopenforposts>>month;
		fileopenforposts>>year;
	}

	bool checklatestdate()
	{
		if((CurrentDate.day == day || CurrentDate.day-1 == day) && CurrentDate.month == month && CurrentDate.year == year)
		{
			return true;
		}
		return false;
	}

	int getDay()
	{
		return day;
	}

	int getMonth()
	{
		return month;
	}

	int getYear()
	{
		return year;
	}

	static Date GetDate()
	{
		return CurrentDate;
	}

	bool checkmemory()
	{
		if(CurrentDate.day == day && CurrentDate.month == month)
		{
			return true;
		}
		return false;
	}

	int calculateyears()
	{
		return CurrentDate.year - year;
	}

	void SetDay(int sentday)
	{
		day = sentday;
	}

	void SetMonth(int sentmonth)
	{
		month = sentmonth;
	}

	void SetYear(int sentyear)
	{
		year = CurrentDate.year;
	}


};

class Activity{
private:
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = 0;
	}

	~Activity()
	{
		if(value)
		{
			delete[] value;
		}
	}

	void LoadActivityFromFile(ifstream& fileopenforposts)
	{
		fileopenforposts>>type;
		char tempval[25];
		fileopenforposts.getline(tempval,25);
		value = Helper::GetStringFromBuffer(tempval);
	}
	
	void PrintActivity()
	{
		if(type == 1)
		{
			cout<<"feeling"<<"  ";
			cout<<value<<endl;
		}
		if(type == 2)
		{
			cout<<"thinking about"<<"  ";
			cout<<value<<endl;
		}
		if(type == 3)
		{
			cout<<"Making"<<"  ";
			cout<<value<<endl;
		}
		if(type == 4)
		{
			cout<<"celebrating"<<"  ";
			cout<<value<<endl;
		}
	}
};

class Comments
{
private:
	char* ID;
	Base* CommentBy;
	Post* PostedOn;
	char* Text;
public:
	Comments()
	{
		ID = 0;
		CommentBy = 0;
		Text = 0;
		PostedOn = 0;
	}

	~Comments()//correct
	{
		if(ID)
		{
			delete[] ID;
		}
		if(Text)
		{
			delete[] Text;
		}
		
	}

	Comments(const Comments& rhs)	// Copy Constructor
	{
		ID = Helper::GetStringFromBuffer(rhs.ID);
		Text = Helper::GetStringFromBuffer(rhs.Text);
	}

	void SetID(char* sentid)
	{
		ID = sentid;
	}

	void PrintComment()
	{
		cout<<"		";
		CommentBy->PrintName();
		cout<<"  wrote :  "<<Text<<endl;
	}

	void SetPost(Post* sentpost)
	{
		PostedOn = sentpost;//
	}

	void SetCommenter(Base* sentcommenter)
	{
		CommentBy = sentcommenter;
	}

	void SetCommentedText(char* senttext)
	{
		Text = senttext;
	}
	
};

class Post
{
protected:
	char* ID;
	Base* SharedBy;
	char* text;
	Date SharedDate;
	Base** LikedBy;
	Activity* activity;
	Comments** comments;
	int totalcomments;
	int totallikers;
	int activitytype;
	//static int totalposts
public:
	Post()
	{
		SharedBy = 0;
		text = 0;
		LikedBy = 0;
		activity = 0;
		comments = 0;
		totalcomments = 0;
		activitytype = 0;
		totallikers = 0;
	}

	~Post()
	{
		if(ID)
		{
			delete[] ID;
		}
		if(text)
		{
			delete[] text;
		}
		if(comments)//correct
		{
			for(int i = 0 ; i < totalcomments ; i++)
			{
				if(comments[i])
				{
					delete comments[i];
				}
			}
			delete[] comments;
		}
		if(LikedBy)//correct
		{
			delete[] LikedBy;
		}
		if(activity)
		{
			delete activity;
		}
	}

	char* GetPostID()
	{
		return ID;
	}
	
	void SetSharedBy(Base* ptr)
	{
		SharedBy = ptr;
	}

	Date GetSharedDate()
	{
		return SharedDate;
	}

	void SetLikedBy(Base* ptr)
	{
		if(!LikedBy)
		{
			LikedBy = new Base*[10];
			for(int i = 0 ; i < 10 ; i++)
			{
				LikedBy[i] = NULL;
			}
		}
		LikedBy[totallikers] = ptr;
		totallikers++;
	}

	void LoadPostFromFile(ifstream& fileopenforposts)
	{
		fileopenforposts>>activitytype;
		char temparrayforID[20];
		fileopenforposts>>temparrayforID;
		ID = Helper::GetStringFromBuffer(temparrayforID);
		SharedDate.LoadDataFromFile(fileopenforposts);
		char tempfortext[50];
		fileopenforposts.getline(tempfortext,50);
		char temptext2[100];
		fileopenforposts.getline(temptext2,100);
		text = Helper::GetStringFromBuffer(temptext2);
		if(activitytype == 2)
		{
			activity = new Activity;
			activity->LoadActivityFromFile(fileopenforposts);
		}
	}

	void AddComment(Comments* ptr)
	{
		if(totalcomments == 0)
		{
			comments = new Comments*[10];
		}
		comments[totalcomments] = ptr;
		totalcomments++;
	}

	virtual void PrintPost()
	{
		SharedBy->PrintName();
		if(activitytype == 2)
		{
			cout<<"  is  ";
			activity->PrintActivity(); //celebrating
			cout<<"          "<<text<<"("<<SharedDate.getDay()<<"/"<<SharedDate.getMonth()<<"/"<<SharedDate.getYear()<<")"<<endl<<endl; //happy birthday to my dear mom
		}
		else
		{
			cout<<" shared " <<text<<"("<<SharedDate.getDay()<<"/"<<SharedDate.getMonth()<<"/"<<SharedDate.getYear()<<")"<<endl<<endl; 
		}
		for(int i = 0 ; i < totalcomments ; i++)
		{
			comments[i]->PrintComment();
			cout<<endl;
		}
		
	}

	void PrintLikedList()
	{
		for(int i = 0 ; i < 10 && LikedBy[i] != NULL ; i++)
		{
			cout<<LikedBy[i]->getID();//listview
			cout<<"-";
			LikedBy[i]->PrintName();
			cout<<endl;
		}
	}
	
	void SetText(char* senttext)
	{
		text = senttext;
	}

	void SetDate(Date dateobj)
	{
		SharedDate.SetDay(dateobj.getDay());
		SharedDate.SetMonth(dateobj.getMonth());
		SharedDate.SetYear(dateobj.getYear());
	}

	Post(char* caption, Base* currUser, Date CurrDate,int postID)
	{
		SharedBy = currUser;
		text = Helper::GetStringFromBuffer(caption);
		SharedDate = CurrDate;
		char tempID[5];
		sprintf_s(tempID,"%d",postID);
		char* completeID = Helper::StringConcatenate("p",tempID); //POSTID TRUNCATED
		completeID = ID;
		comments = 0;
		totalcomments = 0;
		activitytype = 0;
		totallikers = 0;
		LikedBy = 0;
	}

};

class Memory:public Post
{
private:
	Post* OriginalPost;
public:
	Memory(Post* ptr,char* caption,Base* currUser,Date CurrDate,int postID):Post(caption,currUser,CurrDate,postID) //make parametrized contructor and no need for setvalues //memory(char* text,base* sharedby,post* ptr):post(text,sharedby) //overload post construc and cheezain null
	{
		OriginalPost = ptr;
	}

	~Memory()
	{
		//if(OriginalPost)//originalpost != 0;
		//{
		//	OriginalPost = 0;
		//}
	}

	void PrintPost()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout<<endl;
		cout<<"******** ";
		SharedBy->PrintName();
		cout<<" ********";
		cout<<"  shared a memory"<<endl;

		Post::PrintPost();
		
		cout<<"              "<<"("<<OriginalPost->GetSharedDate().calculateyears();
		cout<<" YEARS AGO ) "<<endl;
		OriginalPost->PrintPost();
		
		HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole1, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		
	}

};

class Page: public Base
{
private:
	char* Title;
	Post** timeline;
	int totalposts;
public:
	
	Page()
	{
		Title = 0;
		timeline = 0;
		totalposts = 0;
	}

	~Page()
	{
		if(Title)
		{
			delete[] Title;
		}
		if (timeline)
		{
			for(int i = 0 ; i < totalposts ; i++)
			{
				if(timeline[i])//loop
				{
					delete timeline[i];
				}
			}
			delete[] timeline;
		}
	}

	Page& operator=(const Page& rhs)	// Assignment operator
	{
		if (&rhs != this)
		{
			if (ID != 0)
			{
				delete[] ID;
			}
			ID = Helper::GetStringFromBuffer(rhs.ID);

			if (Title != 0)
			{
				delete[] Title;
			}
			Title = Helper::GetStringFromBuffer(rhs.Title);
		}
		return *this;
	}

	Page(const Page& rhs)	// Copy Constructor
	{
		ID = Helper::GetStringFromBuffer(rhs.ID);
		Title = Helper::GetStringFromBuffer(rhs.Title);
	}

	void LoadDataFromFile(ifstream& filein)
	{
		char tempID[10];
		char tempTitle[80];
		filein>>tempID;
		filein.getline(tempTitle,80);
		Base::setBaseID(Helper::GetStringFromBuffer(tempID));
		Title = Helper::GetStringFromBuffer(tempTitle);
	}

	char* getpageid()
	{
		return Base::getID();
	}

	void PrintPageData()
	{
		cout<<Base::getID()<<" - ";
		cout<<Title;
	}

	void AddPostToTimeLine(Post* ptr)
	{
		if(totalposts == 0)
		{
			timeline = new Post*[10];
		}
		timeline[totalposts] = ptr;
		totalposts++;
	}

	void ViewPageTimeLine()
	{
		for(int i = 0 ; i < totalposts ; i++)
		{
			timeline[i]->PrintPost();
		}
	}
	
	void PrintName()
	{
		cout<<"";
		cout<<Title;
	}

	void PrintLatestPost()
	{
		for(int i = 0 ; i < totalposts ; i++)
		{
			if(timeline[i]->GetSharedDate().checklatestdate() == true)
			{
				cout<<"---------------";
				timeline[i]->PrintPost();
			}
		}

	}

};

class User:public Base
{
private:
	char* FirstName;
	char* LastName;
	User** FriendList;
	Page** LikedPages;
	int totalfriends;
	int totallikedpages;
	Post** timeline;
	int totalposts;
public:
	
	User()
	{
		FirstName = 0;
		LastName = 0;
		LikedPages = 0;
		FriendList = 0;
		totalfriends = 0;
		totallikedpages = 0;
		totalposts = 0;
		timeline = 0;
	}

	~User()
	{

		if(FirstName)
		{
			delete[] FirstName;
		}
		if(LastName)
		{
			delete[] LastName;
		}
		if(FriendList)
		{
			delete[] FriendList;
		}
		if(LikedPages)
		{
			delete[] LikedPages;
		}
		if (timeline)
		{
			for(int i = 0 ; i < totalposts ; i++)
			{
				if(timeline[i])//loop
				{
					delete timeline[i];
				}
			}
			delete[] timeline;
		}
	}

	User& operator=(const User& rhs)	// Assignment operator
	{
		if (&rhs != this)
		{
			if (FriendList != 0)
			{
				for (int i = 0; i < totalfriends; i++)
				{
					delete FriendList[i];
				}
				//FriendList = 0;
			}

			totalfriends = rhs.totalfriends;
			FriendList = new User*[totalfriends];

			for (int i = 0; i < totalfriends; i++)
			{
				FriendList[i] = rhs.FriendList[i];
			}

			if (LikedPages != 0)
			{
				for (int i = 0; i < totallikedpages; i++)
				{
					delete LikedPages[i];
					//LikedPages[i] = 0;
				}
				//LikedPages = 0;
			}

			totallikedpages = rhs.totallikedpages;
			LikedPages = new Page*[totallikedpages];

			for (int i = 0; i < totallikedpages; i++)
			{
				LikedPages[i] = rhs.LikedPages[i];
			}

			if (ID != 0)
			{
				delete[] ID;
				//ID = 0;
			}
			ID = Helper::GetStringFromBuffer(rhs.ID);

			if (FirstName != 0)
			{
				delete[] FirstName;
				//FirstName = 0;
			}
			FirstName = Helper::GetStringFromBuffer(rhs.FirstName);

			if (LastName != 0)
			{
				delete[] LastName;
				//LastName = 0;
			}
			LastName = Helper::GetStringFromBuffer(rhs.LastName);

		}

		return *this;
	}

	User(const User& rhs)	// Copy constructor
	{
		ID = Helper::GetStringFromBuffer(rhs.ID);
		FirstName = Helper::GetStringFromBuffer(rhs.FirstName);
		LastName = Helper::GetStringFromBuffer(rhs.LastName);

		totalfriends = rhs.totalfriends;
		totallikedpages = rhs.totallikedpages;

		FriendList = new User*[totalfriends];
		LikedPages = new Page*[totallikedpages];

		for (int i = 0; i < totalfriends; i++)
		{
			FriendList[i] = rhs.FriendList[i];
		}
		for (int i = 0; i < totallikedpages; i++)
		{
			LikedPages[i] = rhs.LikedPages[i];
		}

	}

	void LoadDataFromFile(ifstream& filein)
	{
		char temp[50];
		char tempID[50];
		filein>>tempID;
		Base::setBaseID(Helper::GetStringFromBuffer(tempID));
		filein>>temp;
		FirstName = Helper::GetStringFromBuffer(temp);
		filein>>temp;
		LastName = Helper::GetStringFromBuffer(temp);
	}

	void settotalfriends(int val)
	{
		totalfriends = val;
	}

	void setlikedpages(int val)
	{
		totallikedpages = val;
	}

	int gettotalfriends()
	{
		return totalfriends;
	}

	int gettotallikedpages()
	{
		return totallikedpages;
	}

	char* getid()
	{
		return Base::getID();
	}

	void userassociate(User*& friendindex,int j)
	{
		if(!FriendList) //if friend list is NOT NULL
		{
			FriendList = new User*[totalfriends]; //if friend list is zero
		}
		FriendList[j] = friendindex; //friendlist's jth index -> tempfriendlist's jth which is friendindex
	}

	void pageassociate(Page*& pageindex , int j)
	{
		if(!LikedPages) //if liked pages is NOT NULL
		{
			LikedPages = new Page*[totallikedpages];
		}
		LikedPages[j] = pageindex;
	}

	void PrintUserData() //called by view friends list
	{
		cout<<Base::getID()<<" - ";
		cout<<FirstName<<"  ";
		cout<<LastName<<"   ";
	}

	void ViewFriendList()
	{
		cout<<FirstName<<"  "<<LastName<<" - Friend List "<<endl;
		for(int i = 0 ; i < totalfriends ; i++)
		{
			FriendList[i]->PrintUserData();
			cout<<endl;
		}
		cout<<" ---------------------------------------------------------"<<endl;
	}

	void ViewLikedPages()
	{
		cout<<FirstName<<"  "<<LastName<<" - Liked Pages List "<<endl;
		for(int i = 0 ; i < totallikedpages ; i++)
		{
			LikedPages[i]->PrintPageData();
			cout<<endl;
		}
		cout<<" ---------------------------------------------------------"<<endl;
	}

	void PrintSharedBy()
	{
		cout<<" shared by ";
		PrintUserData();
	}

	void AddPostToTimeLine(Post* ptr)
	{
		if(totalposts == 0)
		{
			timeline = new Post*[10];
		}
		timeline[totalposts] = ptr;
		totalposts++;
	}

	void ViewUserTimeLine()
	{
		cout<<endl;
		for(int i = 0 ; i < totalposts ; i++)
		{
			cout<<"-----";
			timeline[i]->PrintPost();
		}
	}

	void PrintName()
	{
		cout<<FirstName<<" "<<LastName;
	}
	
	void PrintLatestPost()
	{
		for(int i = 0 ; i < totalposts ; i++)
		{
			if(timeline[i]->GetSharedDate().checklatestdate() == true)
			{
				cout<<"--------";
				timeline[i]->PrintPost();
			}
		}
	}

	void ViewHome()
	{
		if(totalfriends != 0)
		{
			for(int i = 0 ; i < totalfriends ; i++)
			{
				FriendList[i]->PrintLatestPost();
				cout<<endl;
			}
		}
		if(totallikedpages != 0)
		{
			for(int i = 0 ; i< totallikedpages ; i++)
			{
				LikedPages[i]->PrintLatestPost();
				cout<<endl;
			}
	
		}	
		
	}

	void ViewMemory()
	{
		for(int i = 0 ; i < totalposts ; i++)
		{
			if(timeline[i]->GetSharedDate().checkmemory() == true)
			{
				cout<<"On this Day"<<endl;
				cout<<timeline[i]->GetSharedDate().calculateyears()<<" Years Ago ";
				cout<<endl;
				timeline[i]->PrintPost();
			}
		}
	}

};

class Facebook
{
	User** UsersList;
	Page** PageList;
	Post** Posts;
	Comments** comments; 
	int totalpages;
	int totalusers;
	int totalposts;
	int totalcomments;
	int totallikers;
public:

	inline Base* SearchObjectByID(char* id)
	{
		
		if(id[0] == 'u')
		{
			return SearchUserByID(id);
		}
		else if(id[0] == 'p')
		{
			return SearchPageByID(id); 
		}
		return NULL;
	}
	
	Facebook()
	{
		totalpages = 0;
		totalposts = 0;
		totalusers = 0;
		totalcomments = 0;
		UsersList = NULL;
		PageList = NULL;
		Posts = 0;
		comments = 0;
	}

	Facebook(const Facebook& rhs)	// Copy constructor
	{
		//currUser = rhs.CurrentUser;
		totalusers = rhs.totalusers;
		totalpages = rhs.totalpages;

		UsersList = new User*[totalusers];
		PageList = new Page*[totalpages];

		for (int i = 0; i < totalusers; i++)
		{
			UsersList[i] = new User;
			UsersList[i] = rhs.UsersList[i];
		}

		for (int i = 0; i < totalpages; i++)
		{
			PageList[i] = new Page;
			PageList[i] = rhs.PageList[i];
		}
	}

	~Facebook()
	{
		if(UsersList)
		{
			for(int i = 0 ; i < totalusers ; i++)
			{
				if(UsersList[i])
				{
					delete UsersList[i];//correct
				}
			}
			delete[] UsersList;//correct
		}
		
		if(PageList)
		{
			for(int i = 0 ; i < totalpages ; i++)
			{
				if(PageList[i])
				{
					delete PageList[i];
				}
			}
			delete[] PageList;
		}
		
		if(comments)
		{
			delete[] comments;
		}
		
		if(Posts)
		{
			delete[] Posts;
		}


		//if(Posts) //not needed since timeline does this job
		//{
		//	for(int i = 0 ; i < totalposts ; i++)
		//	{
		//		if(Posts[i])
		//		{
		//			delete Posts[i];
		//		}
		//	}
		//	delete[] Posts;
		//}
		
		//if(comments) //not needed done in post
		//{
		//	delete[] comments;
		//}

	}

	void AssociateFriends(char***& tempfriends)
	{

		for(int i = 0 ; i < totalusers ; i++) //temp friend and users list
		{
			for(int j = 0 ; j < UsersList[i]->gettotalfriends() ; j++)
			{
				int count = 0;
				while(count < totalusers)
				{
					if(Helper::StringCompare(tempfriends[i][j],UsersList[count]->getid())) //tempfriend[i] is u1 and j is u1's friendlist
					{
						UsersList[i]->userassociate(UsersList[count], j);
						break;
					}
					else
					{
						count++;
					}
				}
			}
		}

		for(int i = 0 ; i < totalusers ; i++)
		{
			for(int j = 0 ; j < 10 ; j++)
			{
				if(tempfriends[i][j][0] == '-')
				{
					break;
				}
				else
				{
					delete tempfriends[i][j];
				}
			}
			delete[] tempfriends[i];
			
		}
		delete tempfriends;
	}

	void AssociatePages(char***& temppages)
	{

		for(int i = 0 ; i < totalusers ; i++) //temp friend and users list
		{ 
			for(int j = 0 ; j < UsersList[i]->gettotallikedpages() ; j++)
			{
				int count = 0;
				while(count < totalpages)
				{
					if(Helper::StringCompare(temppages[i][j],PageList[count]->getpageid()))
					{
						UsersList[i]->pageassociate(PageList[count], j);
						break;
					}
					else
					{
						count++;
					}
				}
			}
		}
		for(int i = 0 ; i < totalusers ; i++)
		{
			for(int j = 0 ; j < 10 ; j++)
			{
				if(temppages[i][j][0] == '-')
				{
					break;
				}
				else
				{
					delete temppages[i][j];
				}
			}
			delete[] temppages[i];
		}
		delete temppages;
	}

	void AllocateMemoryToTempArr(char***& tempfriends,char***& templikedpages)
	{
		tempfriends = new char**[totalusers];
		templikedpages = new char**[totalusers];
		
		for(int i = 0 ; i < totalusers ; i++)
		{
			tempfriends[i] = new char*[10];
			templikedpages[i] = new char*[10];
			for(int j = 0 ; j < 10 ; j++)
			{
				tempfriends[i][j] = new char;
				templikedpages[i][j] = new char;
			}
		}
	}

	void LoadComments(ifstream& commentsfileopen)
	{
		commentsfileopen>>totalcomments;
		comments = new Comments*[totalcomments];
		commentsfileopen.ignore();
		
		for(int i = 0 ; i < totalcomments ; i++)
		{
			comments[i] = new Comments;
			char commentid[4];
			commentsfileopen>>commentid;
			comments[i]->SetID(Helper::GetStringFromBuffer(commentid));
			char postid[10];
			commentsfileopen>>postid;
			Post* tempptr = SearchPostByID(postid);
			comments[i]->SetPost(tempptr);
			char commenterid[4];
			commentsfileopen>>commenterid;
			comments[i]->SetCommenter(SearchObjectByID(commenterid));
			char commentedtext[60];
			commentsfileopen.getline(commentedtext,60);
			comments[i]->SetCommentedText(Helper::GetStringFromBuffer(commentedtext));
			tempptr->AddComment(comments[i]);
		}
	}

	void LoadPosts(ifstream& postsfileopen)
	{
		postsfileopen>>totalposts;
		Posts = new Post*[totalposts];
		postsfileopen.ignore();
		for(int i = 0 ; i < totalposts ; i++)
		{
			Posts[i] = new Post;
			Posts[i]->LoadPostFromFile(postsfileopen);
			char tempsharedby[5];
			postsfileopen>>tempsharedby;
			Base* tempsharedbyptr = SearchObjectByID(tempsharedby);
			Posts[i]->SetSharedBy(tempsharedbyptr);
			tempsharedbyptr->AddPostToTimeLine(Posts[i]);
			char temparray[30];
			postsfileopen>>temparray;
			for(int j = 0 ; j < 10 && temparray[0] != '-' ; j++)
			{
				Posts[i]->SetLikedBy(SearchObjectByID(temparray));
				postsfileopen>>temparray;
			}
			postsfileopen.ignore();
		}
	}

	void LoadUsersList(char***& tempfriends, char***& templikedpages,ifstream& usersfileopen)
	{
		int friendofuser = 0;
		int likedofuser = 0;
		char temparray[10];
		
		UsersList = new User*[totalusers];
		for(int i = 0 ; i < totalusers ; i++)
		{
			UsersList[i] = new User;
			UsersList[i]->LoadDataFromFile(usersfileopen);
		
			int j = 0;
			tempfriends[i] = new char*[10]; //
			while(temparray[0] != '-')
			{
				usersfileopen>>temparray;
				tempfriends[i][j] = Helper::GetStringFromBuffer(temparray);
				j++;
				friendofuser++;
			}
			
			UsersList[i]->settotalfriends(friendofuser-1);
			friendofuser = 0;
			temparray[0] = ' ';

			int y = 0;
			templikedpages[i] = new char*[10];
			while(temparray[0] != '-')
			{
				usersfileopen>>temparray;
				templikedpages[i][y] = Helper::GetStringFromBuffer(temparray);
				y++;
				likedofuser++;
			}

			UsersList[i]->setlikedpages(likedofuser-1); //-1 because delimiters count is going aswell  
			likedofuser = 0;
			temparray[0] = ' ';
		}


	}

	void LoadPageList(ifstream& pagesfileopen)
	{
		PageList = new Page*[totalpages];
		for(int i = 0 ; i < totalpages ; i++)
		{
			PageList[i] = new Page;
			PageList[i]->LoadDataFromFile(pagesfileopen);
		}

	}

	void LoadData(char* pagesfile,char* usersfile,char* postsfile,char* commentsfile)
	{
		
		ifstream pagesfileopen(pagesfile);//
		ifstream usersfileopen(usersfile);//
		ifstream postsfileopen(postsfile);//
		ifstream commentsfileopen(commentsfile);//

		
		char*** tempfriends;
		char*** templikedpages;
		
		pagesfileopen>>totalpages;
		usersfileopen>>totalusers;

		AllocateMemoryToTempArr(tempfriends,templikedpages); //phase1
		LoadPageList(pagesfileopen);//phase1
		LoadUsersList(tempfriends,templikedpages,usersfileopen);//phase1
		AssociateFriends(tempfriends); //phase1
		AssociatePages(templikedpages); //phase1
		LoadPosts(postsfileopen);//phase2
		LoadComments(commentsfileopen); //phase2
		
		pagesfileopen.close();
		usersfileopen.close();
		commentsfileopen.close();
		postsfileopen.close();
	}
	
	User* SearchUserByID(char* idtosearch)
	{
		for(int i = 0 ; i < totalusers ;)
		{
			if(Helper::StringCompare(UsersList[i]->getid(),idtosearch))
			{
				return UsersList[i];
			}
			else
			{
				i++;
			}
		}
		return NULL;
	}

	Page* SearchPageByID(char* idtosearch)
	{
		for(int i = 0 ; i < totalpages ;)
		{
			if(Helper::StringCompare(PageList[i]->getpageid(),idtosearch))
			{
				return PageList[i];
			}
			else
			{
				i++;
			}
		}
		return NULL;
	}

	Post* SearchPostByID(char* idtosearch)
	{
		for(int i = 0 ; i < totalposts ;)
		{
			if(Helper::StringCompare(Posts[i]->GetPostID(),idtosearch))
			{
				return Posts[i];
			}
			else
			{
				i++;
			}
		}
		return NULL;
	}

	void ViewTimeline(User* currUser)
	{
		cout<<endl;
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View TimeLine"<<endl;
		cout<<"-------------------------------------------"<<endl;
		currUser->ViewUserTimeLine();
	}

	void ViewHome(User* currUser)
	{
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View HomePage"<<endl;
		cout<<"-------------------------------------------"<<endl;
		currUser->ViewHome();
	}

	void ViewPost(Post* posttoview)
	{
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View Post"<<endl;
		cout<<"-------------------------------------------"<<endl;
		posttoview->PrintPost();
	}

	void ViewPage(Page* currPage)
	{
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View Page"<<endl;
		cout<<"-------------------------------------------"<<endl;
		currPage->ViewPageTimeLine();
	}

	void ViewLikedList(Post* ptr)
	{
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View Liked List"<<endl;
		cout<<"-------------------------------------------"<<endl;
		cout<<"Post Liked By :"<<endl<<endl;
		ptr->PrintLikedList();
		
	}

	void ViewMemory(User* currUser)
	{
		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: View Memory"<<endl;
		cout<<"-------------------------------------------"<<endl<<endl;
		cout<<" We Hope you enjoyed looking back and sharing your memories on Facebook, from the most recent to those long ago"<<endl<<endl;
		currUser->ViewMemory();
	}

	void AddPost(Post* ptr)
	{
		Post** temparray = new Post*[totalposts+1]; //to increase capacity of posts
		for(int i = 0 ; i < totalposts ; i++)
		{
			temparray[i] = Posts[i];
		}
		temparray[totalposts+1] = ptr;
		totalposts++;
		delete[] Posts;
		Posts = temparray;
	}

	void ShareMemory(char* posttoshare, char* caption,Base* currUser)
	{
		Post* ptr = SearchPostByID(posttoshare);
		Memory* memoryPtr = new Memory(ptr,caption,currUser,Date::GetDate(),totalposts+1);
		currUser->AddPostToTimeLine(memoryPtr);
		AddPost(memoryPtr); 
	}

	void Run()
	{
		
		User* currUser = SearchUserByID("u7");
		if(currUser != NULL)
		{
			cout<<"-------------------------------------------"<<endl;
			cout<<" Command : Set Current User "<<" '' ";currUser->PrintUserData();cout<<" '' "<<endl;
			cout<<"-------------------------------------------"<<endl;
			cout<<" Succesfully set as current User "<<endl<<endl;
			currUser->ViewFriendList();
			currUser->ViewLikedPages();
		}
		else
		{
			cout<<" User Not Found "<<endl;
		}
		
		ViewTimeline(currUser);
		cout<<endl<<endl;
		
		ViewHome(currUser);
		cout<<endl<<endl;
		
		Post* postid = SearchPostByID("post5");
		ViewLikedList(postid);

		Post* likepostID = SearchPostByID("post5");
		likepostID->SetLikedBy(currUser);
		ViewLikedList(postid);

		cout<<"-------------------------------------------"<<endl;//
		cout<<"Command: POST COMMENT"<<endl;
		cout<<"-------------------------------------------"<<endl;
		Comments* commenttopost = new Comments;
		char tempID[5];
		sprintf_s(tempID,"%d",totalcomments+1);
		char* completeID = Helper::StringConcatenate("c",tempID); //commentID TRUNCATED
		commenttopost->SetID(completeID);
		Post* posttocomment = SearchPostByID("post4");
		commenttopost->SetPost(posttocomment);
		char* text = "Good Luck For your Result";
		commenttopost->SetCommentedText(text);
		commenttopost->SetCommenter(currUser);
		posttocomment->AddComment(commenttopost);//


		Post* posttoview = SearchPostByID("post4");
		ViewPost(posttoview);


		cout<<"-------------------------------------------"<<endl;
		cout<<"Command: POST COMMENT"<<endl;
		cout<<"-------------------------------------------"<<endl;
		Comments* commenttopost2 = new Comments;
		char tempID2[5];
		sprintf_s(tempID2,"%d",totalcomments+1);
		char* completeID2 = Helper::StringConcatenate("c",tempID2);
		commenttopost2->SetID(completeID2);
		Post* posttocomment2 = SearchPostByID("post8");
		commenttopost2->SetPost(posttocomment2);
		char* text2 = "Thanks for the Wishes";
		commenttopost2->SetCommentedText(text2);
		commenttopost2->SetCommenter(currUser);
		posttocomment2->AddComment(commenttopost2);


		Post* posttoview2 = SearchPostByID("post8");
		ViewPost(posttoview2);

		Page* currPage = SearchPageByID("p1");
		if(currPage != NULL)
		{
			cout<<"-------------------------------------------"<<endl;
			cout<<" Command : Set Current Page "<<" '' ";currPage->PrintPageData();cout<<" '' "<<endl;
			cout<<"-------------------------------------------"<<endl;
		}
		else
		{
			cout<<" Page Not Found "<<endl;
		}
		ViewPage(currPage);
		cout<<endl<<endl;

		ViewMemory(currUser);
		char* posttoshare = "post10";
		char* captionforpost = " Never Thought I will be specialist in this field...";
		ShareMemory(posttoshare,captionforpost,currUser);
		ViewTimeline(currUser);
		cout<<endl<<endl;

		User* currUser2 = SearchUserByID("u11");
		if(currUser2 != NULL)
		{
			cout<<"-------------------------------------------"<<endl;
			cout<<" Command : Set Current User "<<" '' ";currUser2->PrintUserData();cout<<" '' "<<endl;
			cout<<"-------------------------------------------"<<endl;
		}
		else
		{
			cout<<" User Not Found "<<endl;
		}
		ViewHome(currUser2);
		ViewTimeline(currUser2);


	}

};

Date Date::CurrentDate;

void main()
{
	Date::SetCurrentDate(15,11,2017);
	Facebook fb;
	char* pagesfileopen = "pages.txt";
	char* usersfileopen = "users.txt";
	char* postsfileopen = "posts.txt";
	char* commentsfileopen = "comments.txt";
	fb.LoadData(pagesfileopen,usersfileopen,postsfileopen,commentsfileopen);
	fb.Run();

	
	system("pause");

}