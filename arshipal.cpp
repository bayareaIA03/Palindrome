/* This program gives the user two options. 1) to check the text file for any palindrome sentences. 2) the user provides
a word to check if it is palindrome. thenafter the user has a choice to put the palindrome sentences into a seperate file
and name the file. 
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

using std::cout; using std::cin; using std::endl;
struct node{ //the making of nodes
	 std::string data;
	 node *next; 
};

class link
{
    private:
        node* head; //conceled the head and tail pointers 
        node* tail;
        
    public:
        link();
		~link();
		void askName();
		int userChoice();
		std::string menuBook();
		int openfileSize(std::ifstream &in_file, std::string textname);
		void openFile(std::ifstream &in_file,std::string textname, std::string *sentence, std::string *copy);
		void cleanArray(std::string *sentence, int size);
		void create();
		void createStack(char character);
		void createQueue(char character);
		void add_at_begin(char word); //for checkpalindrome function.
		void add_at_end(char word);
		std::string remove_at_begin();
		void print();
		void freeList();
		void lowercase(std::string *sentence,int size);
		bool checkpalindrome(std::string me);
		void add_at_begin(std::string word); //for add_in_order function
		void add_in_order(std::string &word);
		bool checkSentencePalindrome();
		void userTextName();
};

int main()
{	
	link a;
	int pick;
	char choices;
	
	std::string textname;
	std::string name;
	std::ifstream in_file;
	
	std::cout << "would you like to start the program? Press 'Y' or 'N'"<<std::endl;
	std::cin>> choices;
	
	a.askName();
	do {
		
		pick = a.userChoice();
		
		if (pick ==1){ //if user chooses to look at the text file
		textname=a.menuBook(); //return the name of the text file that the user choose 
		int x = a.openfileSize(in_file, textname); // get the size of the text file (in terms of sentences)
		std::string *sentence = new std::string[x]; // make two dynamic arrays. one will be clean and the other will remain original
		std::string *copy = new std::string[x];
			
		a.openFile(in_file, textname,sentence,copy); //opens file and pass strings in the arrays
		a.cleanArray(sentence,x); //clean the array
		
		for (int i=0;i<x;i++){	 //will go through every sentence of the array
			if(a.checkpalindrome(sentence[i]) == true){ 	//pop n deque. passing each sentence. This checks the indexs of all palindrome in the sentence array.
				a.add_in_order(copy[i]);	//then the indexs of palindromes gets passed to copy array and every sentence is being put in order through a linked list
			}//end if			 
		}//end for
		
		a.print();
		a.userTextName(); //choose the name of the text file
		
	delete[] sentence; //free memory
	delete[] copy;
		}//end if pick 1
		
		else if(pick == 2){ //user provides a string to check for palindrome
					 if(a.checkSentencePalindrome() == true){ 
								cout<<endl;
								cout<<"The choice of word is a palindrome"<<endl;
							}//end if
						
					else{
								cout<<endl;
								cout<<"Sorry!! The word is not a palindrome"<<endl;
					}//end else
				}//end if	

		cout<<"would you like to restart the entire program? Press 'Y' or 'N'"<<endl;
		cin>> choices;

	}// end of do
	while(choices=='Y'|| choices=='y');
	return 0;
}// end main

bool link::checkSentencePalindrome(){
	
	std::string *newDynamicArray = new std::string [1]; //hardcoded 1 because one string is being checked at a time
		
	cout<<"Please enter a word or sentence to check for palindrome"<<endl;
	cin.ignore();
	std::getline(cin,*newDynamicArray); // take spaces	
		
	cleanArray(newDynamicArray, 1);
			
	if(checkpalindrome(*newDynamicArray)==true){
		return true;
	}
	else {return false;}
}

bool link::checkpalindrome(std::string me){

	link  tempStack; //2 class objects are made. 1)stack 2)queue
	link tempQueue;
	
	for(int i=0;i<me.length();i++){ 
		tempStack.add_at_begin(me[i]);//char are being passed into both the class objects as linked list
		tempQueue.add_at_end(me[i]);	
	}

	std::string xa,za;
	int counter =0; //counter is made to count how many chars are the same from both a stack list and queue list.
	for(int z=0; z<me.length();z++){ //char
					
		xa=tempStack.remove_at_begin();
		za=tempQueue.remove_at_begin();
		if(xa==za){		//compare each letter at a time from stack and queue
			counter++;
		}				
	}//end for z
	
	if (counter==me.length()){ // if the amount of chars are the same for both queue and stack and they equal to the amount 
		//amount of chars of a word then that will be one palindrome.  			
		return true;
	}
	
	else{
		return false;
	}	
}

void link::add_in_order(std::string &word){
	
    node *a=head;
	node *newnode = new node;
	newnode->data = word;
   
	if(head==NULL){//checking if list is empty or not
        add_at_begin(word); 
    }
	
	else  if (head->data >= newnode->data){// to check if the newnode needs to be ahead of the head
				newnode->next = head; 
				head = newnode;
			}
			else {
			while(a->next != NULL && a->next->data < newnode->data){ //checks everything after the head and puts them in order.
			a = a->next;
			}//end while
			newnode->next = a->next;//. if the node is greater than the newnode then conncect the newnode to the a->next so that it can be behind the node that has a greater value than the newnode
			a->next = newnode;
	
	}//end else
}//end add_in_order

link::link()//constructor is called when object is made. so this functions makes the head and tail pointers r
{
     create(); 		
} 

void link::askName(){

	std::string name;
	cout<<"Hello!! What's your name?"<<endl;
	cin.ignore();
	std::getline(cin,name);
	//cin>>name;
	cout<<"\n";
	cout<<"Nice to meet you today "<<name<<"."<<endl;
	cout<<"This is a program that finds a palindrome from a text file or a word that you provide to me"<<endl;
	cout<<"\n";
}

void link::create() {//initialize the head and tail from the constructor calling the function
		 
	head = NULL;// set to null becaue there is no nodes 
	tail = NULL;

}

void link::userTextName(){

	std::string fileName;
	char giveMe;

	std::ofstream newFile; 
	cout<<endl;

	cout<<"what would you like to name the file? Type 'Y' or 'N'"<<endl;
	cin.ignore();
	getline(cin,fileName);
	if (fileName == "y"){
		
		newFile.open(fileName.c_str());
				
		node *temp=new node;
		temp=head;//temp will be at the beginning of the list

		while(temp){ //as long temp has a value in it and not equal to null or 0
			newFile<< temp->data<<endl;
			temp=temp->next;
		}// end while 
		
		newFile.close();
	}//end if
}

std::string link::menuBook(){
	int choice;
	std::string textname;
	cout<<"Choose one of the two following books"<<endl;
	cout<<"#1 Kubla Kahn"<<endl;
	cout<<"#2 Palindrome Test 2"<<endl;
	cin>>choice;
	if(choice==1){
		textname = "KublaKhan.txt";
		cout<<"Great Choice!!!"<<endl;
	}
	else if (choice==2){
		textname = "PalindromeTest2.txt";
		cout<<"Great Choice!!!"<<endl;
	}
	
	return textname; 
}

int link::openfileSize(std::ifstream &in_file, std::string textname){
    std::string words;
    int size =0;
    in_file.open(textname);
	
    if (in_file.fail()){
        cout << "Could not open file."<<endl;
        return -1; 
    }//end if 
	
    while(std::getline(in_file, words)){
		
		size++;
    }//end while
	in_file.close(); //
	return size;
}

void link::openFile(std::ifstream &in_file,std::string textname, std::string *sentence, std::string *copy){
	
	int counter = 0;
	std::string words,emptySpaces;
	
	
	in_file.open(textname);
		if (in_file.fail()){
			cout << "Could not open file."<<std::endl;
			
		}//end if 
		
		
    while(std::getline(in_file, words)){
		emptySpaces=words;
		
		if(emptySpaces[0]<= 32){
			continue;
		}
		
        sentence[counter]= words;
		copy[counter]=words;
			
		counter++;
    }//end while
	in_file.close();
}

int link::userChoice(){ //maybe sentence
	int n;
	
	cout<<"\tPlease choose to following choice by inputing a number"<<endl;
	cout<<"#1 Find a palindrome in a text file"<<endl;
	cout<<"#2 Provide a word so I can see if it's a palindrome or not"<<endl;
	cin>>n;
	
	return n;
}

void link::cleanArray(std::string *sentence, int size ){

	  for (int i =0; i< size; i++){ 
		for(int j=0; j<sentence[i].length(); j++){ //this loop and if statement will look
	
		if (isalpha(sentence[i][j]))  
		{
			continue;	
			} 
		else if(isdigit(sentence[i][j])) { //leave all digits from the text
				continue;
			}
		sentence[i].erase(sentence[i].begin()+j);
		j--; // after erasing decrement j because the array is shrinking after erasing an element
		
		} //end of j
	}// end of i
	
	lowercase(sentence,size);
}

void link::createStack(char character){
	add_at_begin(character);
	
}

void link::createQueue(char character){	
	add_at_end(character);		
	
}

void link::add_at_begin(char word){ //this function will be used for checking palindromes in the checkpalindrome function
	node *newnode= new node;
	newnode->data=word; //create newnode and attach the word from user to the data of newnode
	newnode->next=head;
	head=newnode; 
}

void link::add_at_begin(std::string word){ //this will be use in add_in_order function
	node *newnode= new node;
	newnode->data=word; //create newnode and attach the word from user to the data of newnode
	newnode->next=head;
	head=newnode; 
}
		
void link::add_at_end(char word){ 

	node *newnode = new node; 
	newnode->data=word;
	newnode->next=NULL;
			
	if(tail==NULL){ // if theres no nodes in list
		head=newnode;
		tail=newnode;
	}
		else{
			tail->next=newnode;
			tail=newnode; //the tail will connect to the newnode and the newnode will become the tail
		}
}

std::string link::remove_at_begin(){
std::string temp;
	if(head==NULL){
		cout<<"Node is empty. Can't remove a node."<<endl;
		
	}
		else{
			node *p=head;
			head=head->next;
			temp = p->data;
			delete p;
		}	
		return temp;
} 

void link::lowercase(std::string *sentence,int size){
	for (int i =0; i<size; i++){
		transform(sentence[i].begin(), sentence[i].end(), sentence[i].begin(), ::tolower);
			//cout<<sentence[i]<<endl;
	}
}

void link::print() {

	node *temp=new node;
	temp=head;//temp will be at the beginning of the list

	while(temp){ //as long temp has a value in it and not equal to null or 0
		cout<<temp->data<<endl;
		temp=temp->next;
	}// end while 
}//end print

void link::freeList(){ // make a pointer and point from the head and delete all nodes
	while (head){
		node *p = new node;
		p = head;
		head = p->next; //make sure to move head before deleting so that the next time the pointer can point at the node again
		delete p;
	}
}
link::~link(){
	freeList();
	
}