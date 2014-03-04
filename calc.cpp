//Make single digit.
/******************************************************
 * @author Nootan Ghimire <nootan.ghimire@gmail.com>
 * @file   shunting-yard.cpp
 * @desc   Conversion of Infix Expression to Postfix
 *****************************************************/ 

// C++ Includes
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <typeinfo>

/*#define xeval(o1, o, o2) o1##o##o2*/ //Tried to mimic eval

// Namespace Specifications
using namespace std;

//Global var for (Un)Displaying Debug 
bool debug = false;
float ans = 0.0;


/************************************************
 * @class logger
 * @desc  logs to o/p according to debug status
 ***********************************************/
class logger{
public:
    template <typename T>
    friend logger& operator <<(logger& log, T& value);
};
template <typename T>
logger& operator <<(logger& log, T  & value) {
    // Here I'd output the values to a file and stdout, etc.
    if(::debug){
    	cout << value;
	}
    return log;
}
// End Class

//Declare logger
logger L;

/**************************************
 * @class Stack
 * @desc  Implements Stacks
 *************************************/
template <class T>
class Stack
{
private:
	T* st;
	int currTop, maxTop;

public:
	Stack(int = 0);
	~Stack();

	int push(T);
	T pop();
	int currentStackPos(){
		return currTop;
	}

};

template <class T>
Stack<T>::Stack(int size){
	maxTop = size;
	currTop = -1;
	st = new T[size];
}

template <class T>
Stack<T>::~Stack(){
	delete []st;
}

template <class T>
int Stack<T>::push(T a){
	if(currTop >= maxTop){
		L<<"[!] Could not push. StackOverflow"<<"\n" ;
		return -2;
	}
	currTop++;
	st[currTop] = a;
	L<<"[-] Pushed "<<a<<" to Stack"<<"\n";
	return 1;
}

template <class T>
T Stack<T>::pop(){
	if(currTop<=-1){
		L<<"[!] Could not pop. Reached the bottom"<<"\n" ;
		return -1;
	}
	currTop--;
	L<<"[-] Popped "<<st[currTop+1]<<" from Stack"<<"\n";
	return st[currTop+1];
}
//End Class

/**************************************
 * @class Queue
 * @desc  Implements Queue
 *************************************/
template <class T>
class Queue{
private:
	int front, rear, max;
	T *q;
	/*Queue(const Queue&);
	Queue& operator=(const Queue&);*/
public:
	Queue(int size=0){
		front = rear = 0;
		max = size;
		q = new T[size];
	}
	/*Queue(const Queue& rop){
		front = rear = 0;
		max = rop.max;
		q = new T[max];
		q = rop.q;
	}

	Queue& operator=(const Queue& rop){
 		// update this with rop, means the same as above
 		front = rear = 0;
		max = rop.max;
		q = new T[max];
		q = rop.q;
 		return *this;
	}*/

	~Queue(){
		delete []q;
	}
	int enqueue(T);
	T dequeue();

	T& getValueFromIndex(int index){
		return q[index];
	}

	const T& getValueFromIndex(int index) const {
		return q[index];
	}

	void printQueueContents(Queue& typeInfo){
		for(int i=rear; i<front;i++){
			if(typeInfo.getValueFromIndex(i)) {
			cout<<q[i]<<" ";
			} else {
				cout<<static_cast<char>(q[i])<<" ";
			}
		}
		cout<<"\n";
	}
	int getRear(){
		return rear;
	}
	int getFront(){
		return front;
	}
	/*int currentQueueSize(){
		return front - rear;
	}
	T& convQueueToArray(){
		T* arr = new T[currentQueueSize()];
		for(int i = rear; i<front; i++){
			arr[i]=q[i];
		}
		return arr;
	}*/
};


template <class T>
int Queue<T>::enqueue(T elem){
	if(front>=max){
		L<<"[!] Could not enqueue. QueueOverflow"<<"\n" ;
		return -2;
	}
	q[front] = elem; front++;
	L<<"[-] Enqueued "<<elem<<" to Queue"<<"\n";
}

template <class T>
T Queue<T>::dequeue(){
	if(front<=0){
		L<<"[!] Could not dequeue. QueueUnderflow"<<"\n" ;
		return -1;
	}
	T result = q[rear];
	L<<"[-] Dequed "<<result<<" from Queue\n";
	++rear;
	return result;
	
}
//End Class



/*Function Declaration*/
float xeval(float op1, char op, float op2);
int countNonNumerals(char s[]);
int addSpace(char s[], char* a[]);

/*int split(char str[], char *ret[]){
	//addSpace(str);
	int c=0;
	char * pch;
	pch = strtok (str," ");
  	while (pch != NULL)
  	{
    	//printf ("%s\n",pch);
    	ret[c] = new char[strlen(pch)];
    	strcpy(ret[c], pch); c++;
    	pch = strtok (NULL, "");
  	}
  	return c;
} */


int countNonNumerals(char s[]){
	int c;
	for(int i=0; i<strlen(s); i++){
		if(s[i]>=30 && s[i]<=39) continue;
		c++;
	}
	return c;
}

void emptyArray(char arr[]){
	for(int i =0; i<40;i++){
		arr[i]='\0';
	}
}

int addSpace(char s[], char *a[]){
	int c = 0;
	int inFlag=0;
	char someArr[40];
	strcat(s,"#");
	//char* a[200];
	//int num = strlen(s+countNonNumerals(s)+5); //extra 5 for tettikai :D
	//cout<<num;
	//a = new char[num];
	int newCharPos = 0;
	//cout<<strlen(s);
	for(int i=0; i<=strlen(s);i++){
		//cout<<(s[i]>='0' && s[i]<='9');
		if(s[i]==' ') continue;
		if(((s[i]>='0') && (s[i]<='9')) || (s[i]=='.')){
			//number:
			//Copy it verbatim
			//cout<<typeid(a[newCharPos][c]).name();
			someArr[c] = s[i];
			inFlag = 1;
			//a[newCharPos][c] = s[i];
			c++;			
		} else {
			if(inFlag == 1) {
			someArr[c] = '\0';
			a[newCharPos] = new char[c+1];
			strcpy(a[newCharPos], someArr);
			//cout<<a[newCharPos];
			//cout<<s[i];
			newCharPos++;
			emptyArray(someArr);
			} 
			c=0;
			//a[newCharPos++][c] = ' ';

			if(s[i]=='#') break;
			a[newCharPos] = new char;
			a[newCharPos][c] = s[i];
			//cout<<a[newCharPos];
			newCharPos++;
			inFlag = 0;
			//a[newCharPos++][c] = ' ';
		}
	}
	return newCharPos;


}

/*
int isnumber(char* s){
	while(*s!='\0'){
		if(!isdigit(*s)) return false;
		s++;
	}
		if(*s=='+') return false;
	return true;
}*/

//Main Starts
int main(int argc, char const *argv[])
{
	/* code */
	/*if(argc>1){
		if(*argv[1]=='v'){
			::debug = true;
		} else if(*argv[1]=='s') {
			::debug = false;
		} else {
			cout<<"Usage: "<<argv[0]<<" [v]/[s]\n\nSwitches\t\tFunctions\nv\t\t\tVerbose\ns\t\t\tSilent\n";
			return 1;
		}
	} else {
		//cout<<"Usage: "<<argv[0]<<" [v]/[s]\n\nSwitches\t\tFunctions\nv\t\t\tVerbose\ns\t\t\tSilent\n";
		::debug = false; //Default
	}*/
		::debug = false;

	///Code Starts

	char* s;
	//char* dum = new char[200];
	//char* ssa;
	s =  new char[200];
	cout<<"Welcome to Calculator! Input 'Q' (without quotes) to Quit!\n";
	while(1) {
	cout<<"> ";
	cin.getline(s,200);
	if(s[0]=='Q' || s[0] =='q') break;
	//strcpy(dum, addSpace(s));
	//strcpy(s, dum);
	char* st[200];
	//int size=3;
	int size = addSpace(s, st);
	//int stC =0;

	Stack<float> s1(200);
	Stack<float> s2(200); // Holds data type information for s1
	Queue<float> q1(200);
	Queue<float> q2(200); // Holds data type information for q1
	float o1, o2;
	int i=0;
	for(i=0; i<size;i++) {
		if(isdigit(st[i][0])) {
			//s1.push(atof(st[i]));
			q1.enqueue(atof(st[i]));
			q2.enqueue(1); //1 = number
		} else {
			//Found a operator (possibly)
			//check stack size.
			/*if(s1.currentStackPos()<1){
				cout<<"[!] Abort! Invalid Postfix Expression. Check the Position of Operator?\n";
				exit(-1);
			}*/
			//Safe
			//o2 = s1.pop();
			//o1 = s1.pop();
			//s1.push(xeval(o1,st[i][0],o2));
			if(st[i][0]==')'){
				//pop from stack to queue until you find (
				int j = 0; 
				for(j=s1.currentStackPos() ; j>=0; j--){
					int item = s1.pop();
					if(item =='(') { 
						break; 
					} else { 
						q1.enqueue(item);
						q2.enqueue(0); //0 = not number
					}
				}
				if(j<0){
					cout<<"[!] Abort! Errorenous Input"<<"\n";
				}
			} else {
			//if nothing else than push to stack;
			s1.push(st[i][0]);
			}
		}
		

	} //End For

	for(int k=s1.currentStackPos(); k>=0; k--){
		q1.enqueue(s1.pop());
		q2.enqueue(0);
	}
	//This is the end of stack
	//The result is most probably.
	//int result = s1.pop();
	//cout<<"[-] The result is: "<<result<<"\n";	
	//return 0;
	//print queue contents at last
	//cout<<"[=] The Resulting Postfix Expression is: ";
	//q1.printQueueContents(q2); //< I think this contains error
	//cout<<"\n";
	float op1, op2;
	Stack<float> pfeval(200);
	for(int l=q1.getRear(); l<q1.getFront(); l++){
		if(q2.getValueFromIndex(l)==1){
			//digit
			pfeval.push(q1.getValueFromIndex(l));
		}  else {
			//Found a operator (possibly)
			//check stack size.
			if(pfeval.currentStackPos()<1){
				cout<<"[!] Abort! Invalid Postfix Expression. Check the Position of Operator?\n";
				exit(-1);
			}
			//Safe
			o2 = pfeval.pop();
			o1 = pfeval.pop();
			pfeval.push(xeval(o1,q1.getValueFromIndex(l),o2));
		}
	}

	float finalResult = pfeval.pop();
	cout<<"ans: "<< finalResult <<"\n";
	::ans = finalResult;
}
	return 0;
}







float xeval(float op1, char op, float op2){
	// op1 = atof(op1);
	// op2 = atof(op2);
	switch(op){

		case '+':
		return op1 + op2;
		break;

		case '-':
		return op1 - op2 ;
		break;

		case '*':
		return op1 * op2;
		break;

		case '/':
		return op1 / op2 ;
		break;

		default:
		L<<"[!] Invalid Operator: "<<op<<"\n";
		return 0;
	}
}