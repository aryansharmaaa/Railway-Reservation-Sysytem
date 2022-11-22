#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

int limit = 5;
int size = 2;
class node{
   int seatNo, waitList, age;
   string contactNo;
   string name, bookingStatus;
   char gender;
   node *next;
   public:
     node(string name, char gender, int age, string contactNo){
	this->age = age;
	this->name = name;
	this->contactNo = contactNo;
	this->gender = gender;
	next=NULL;
     }
     friend class Queue;
     friend class Application;
};

class Queue{
  node *newNode, *rear, *temp, *front, *start;
  int seat, wait;
  public:
     Queue(){
       rear = front = start = NULL;
       seat=29;
       wait = 0;
     }
     void enQueue(int);
     node* deQueue();

     node* createPassenger();
     void bookTicket(int);
     void confirmTicket();

     void showWaitList();
     void updateWaitList();
     void cancelTicket(int);
};

node* Queue::createPassenger(){
  int ag;
  char gndr;
  string nm;
  string cno;
  cout<<"\nName:\t";
  cin>>nm;
  cout<<"Age:\t";
  cin>>ag;
  cout<<"Gender:(F/M)\t";
  cin>>gndr;
  cout<<"Contact No:\t";
  cin>>cno;
  newNode = new node(nm, gndr, ag, cno);
  return newNode;
}

void Queue::bookTicket(int n){
  node *newNode, *temp;
  for(int i=0; i<n; i++){
     newNode = createPassenger();
     newNode->bookingStatus = "CNF";
    newNode->seatNo=seat++;
    newNode->next = NULL;
    cout<<"\t\t\tSeat No: "<<newNode->seatNo;
    if(start == NULL)
      start = temp = newNode;
    else{
      temp = start;
    while(temp->next != NULL)
	temp = temp->next;
      temp->next = newNode;
      temp = newNode;
     }
  }
  cout<<"\nTicket booked successfully!!";
}

void Queue::confirmTicket(){
   node *temp;
   int srNo=1;
   temp = start;
   cout<<"\nSrNo\tName\t\tGender\tAge\tContact No\tSeatNo\tStatus\n";
   cout<<"---------------------------------------------------------------------\n";
   while(temp!=NULL){
	cout<<srNo<<"\t"<<temp->name<<"\t\t"<<temp->gender<<"\t"<<temp->age<<"\t"<<temp->contactNo<<"\t"<<temp->seatNo<<"\t"<<temp->bookingStatus;
	temp = temp->next;
	cout<<"\n";
	srNo++;
   }
   cout<<"____________________________________________________________________";
}

void Queue::enQueue(int n){
  for(int i=0; i<n; i++){
   newNode = createPassenger();
   newNode->waitList = ++wait;
   newNode->bookingStatus = "WL";
   newNode->next = NULL;
   if(front == NULL){
     rear = front = newNode;
   }
   else {
     rear->next = newNode;
     rear = newNode;
   }
   cout<<"\t\t\tWait list no: "<<newNode->waitList;
   cout<<"\n__________________________________________________________________________________";
   }
}

node* Queue::deQueue(){
     node *temp;
     if(front!=NULL) {
        temp = front;
        front = front->next;
        return temp;
     }
     else {
        cout<<endl<<"No waiting";
        cout<<"\n__________________________________________________________________________________";
        return NULL;
     }
}

void Queue::cancelTicket(int sno) {
     node *temp, *ptr;
     temp = start;
     while(temp!=NULL){
         if(temp->seatNo == sno) {
              break;
          }
         temp = temp->next;
     }
     cout<<"\nTicket cancelled successfully.....";
     if(front!=NULL) {
           ptr = deQueue();
           temp->name = ptr->name;
           temp->age = ptr->age;
           temp->gender = ptr->gender;
           temp->contactNo = ptr->contactNo;
           temp->bookingStatus = "CNF";
           temp->seatNo = temp->seatNo;
           cout<<endl<<temp->name<<" booking confirmed\nSeat No.:\t" <<temp->seatNo;
           cout<<"\n__________________________________________________________________________________";
     }
         if(front!=NULL){
            temp = front;
            while(temp != NULL){
                temp = temp->next;
                temp->waitList = --wait;
            }
         }
}

void Queue::showWaitList(){
   node *temp;
   int srNo = 1;
   if(front != NULL){
	cout<<"\nWaiting list: ";
	cout<<"\nSrNo\tName\t\tGender\tAge\tContact No\tWaitList No\tStatus\n";
	cout<<"------------------------------------------------------------------------------\n";
	temp = front;
	while(temp != NULL){
	  cout<<srNo<<"\t"<<temp->name<<"\t\t"<<temp->gender<<"\t" <<temp->age <<"\t"<<temp->contactNo<<"\t"<<temp->waitList<<"\t\t"<<temp->bookingStatus;
	  cout<<"\n";
	  temp = temp->next;
	  srNo++;
	}
   }
else{
   if(size>0){
      cout<<endl<<size<<" Seats available";
      cout<<endl<<"__________________________________________________________________________";
   }
  else
     cout<<"\n\t-------CNF Ticket Status: Full\n\t------Waiting List Status: Empty";
     cout<<endl<<"__________________________________________________________________________";
}
}
class Application{
  Queue q;
  public:
    void create(int n){
      q.bookTicket(n);
    }
    void display(){
      q.confirmTicket();
    }
    void enQ(int n){
      q.enQueue(n);
    }
    void dispWaitList(){
      q.showWaitList();
    }
     void cancel(int sno){
      q.cancelTicket(sno);
    }
};

int main(){
  Application a;
  int ch, n, w;
  cout<<"\n**********Railway Reservation System*************";
  do{
  cout<<"\n1. Book Ticket\n2. Cancel Ticket\n3. Confirm Tickets\n4. Wait List\n5. Exit\n";
  cout<<"\nEnter choice: ";
  cin>>ch;
  switch(ch){
     case 1: cout<<"Enter number of tickets: ";
	     cin>>n;
	     if(n<=size){
	       a.create(n);
	       size = size-n;
	     }
	     else if(size==0){
	       cout<<"\nBookings are full....\n"<<(n-size)<<" ticket/s will be in waiting list";
	       cout<<"\n__________________________________________________________________________________";
		if(size!=0)
		   a.create(size);
		a.enQ((n-size));
		size-=size;
		limit-=(n-size);
	     }
	     else{
		cout<<"\n"<<size<<" tickets can be booked. \n"<<(n-size)<<" ticket/s will be in waiting list";
		if(size!=0)
		   a.create(size);
		a.enQ((n-size));
		size-=size;
		limit-=(n-size);
	     }
	     break;
     case 2:  cout<<"\nEnter seat number to be deleted : ";
                   int sno;
                   cin>>sno;
                   a.cancel(sno);
                   limit++;
	     break;
     case 3: a.display();
	     break;
     case 4: a.dispWaitList();
	     break;
     case 5: exit(0);
  }
  }while(ch!=5);

  return 0;
}

