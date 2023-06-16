#include<iostream>
#define maxperson 15
#define maxfloor 8
#define maxlift 4
using namespace std;
struct node{
	//beside are the movement of lift
	int currper;	//current person in lift
	int currloc;	//current location of lift
	//int serial;	//the serial of lift, 4 in total
	int mat[maxfloor];	//which floor the lift is going, this serial is a mat
	int backmat[maxfloor];	//save the mat in last round
	int free;		//free=1, busy=0;
	//int ifshown;	//if this floor has been shown
	node*nxt;

	//beside are the need of person
	int where;	//where are this person;
	int up;		//go up or go down, 1=up, 0=down
	int go;		//where does the person want to go;
	int carry;	//carry this person or not, 1=carry, 0=don't carry him
	//int wait; 
	node*lst;

	
};

class elevator{
	public:
		elevator();
		~elevator();
		bool reset(int a);	//the lifta go back to 1 floor
		bool person();	//where does the person want to go and where are this person, return a mat
		//int situation(int a);	//situation of lift a, return the serial of lift
		/*next step, write your algorithm */
		bool FCFS(node*l, node*p);	//first come first serve, the first reference is head->nxt, the first reference should be phead->nxt
		//void select();		//select to use which algorithm
		void ascsort(int *a, int len);	// asc insert sort
		void dessort(int *a, int len);	// des insert sort
		bool control();		//use algorithm
		void show();		//show
		void draw();		//draw
	private:
		int floor[maxfloor];
		node*head;	//lift head
		node*phead;	//person head
};


