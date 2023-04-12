/*
 * NPDADriver.cpp
 *      Author: J. Alex Burke
 *      4/13/21
 *      This program uses the NPDA class to build a NPDA from a text file of specific format.
 *      Then, it allows the user to test if a string would be accepted or rejected.
 */
#include "NPDA.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
	bool repeatFlag = true;
	NPDA myNPDA;
	fstream newfile;
	string fileName,input;
	cout<<"enter file path: "<<endl;
	cin>>fileName;

	newfile.open(fileName, ios::in);
	while(newfile.is_open()==false)
	{
		cout<<"File did not open. Please re-enter file path: "<<endl;
		cin>>fileName;
		newfile.open(fileName, ios::in);
	}

	cout<<"File opened successfully. Building NPDA"<<endl;
	string nextline;

	getline(newfile,nextline);
	getline(newfile,nextline);

	while(nextline.compare("<input alphabet>") != 0)
	{
		myNPDA.add_state(nextline);
		getline(newfile, nextline);
	}
	getline(newfile,nextline);
	while(nextline.compare("<stack alphabet>") != 0)
	{
		myNPDA.add_input_alphabet_symbol(nextline);
		getline(newfile, nextline);
	}
	getline(newfile,nextline);
	while(nextline.compare("<transitions>") !=0 )
	{
		myNPDA.add_stack_alphabet_symbol(nextline);
		getline(newfile,nextline);
	}
	getline(newfile,nextline);
	while(nextline.compare("<initial state>") !=0)
	{
		stringstream ss(nextline);
		string t1, t2, t3, t4, t5;
		ss>>t1>>t2>>t3>>t4>>t5;
		myNPDA.add_transition(t1,t2,t3,t4,t5);
		getline(newfile, nextline);
	}
	getline(newfile,nextline);
	while(nextline.compare("<stack start>") !=0)
	{
		myNPDA.set_current_state_to_inital(nextline);
		getline(newfile, nextline);
	}
	getline(newfile,nextline);
	while(nextline.compare("<final states>") !=0)
	{
		myNPDA.set_stack_start(nextline);
		getline(newfile,nextline);
	}
	getline(newfile,nextline);
	do
	{
		myNPDA.add_final_state(nextline);
	}while(getline(newfile,nextline));

	cout<<"NPDA is complete!"<<endl;
	myNPDA.display_NPDA();

	cout<<"Enter a string to process(Ctrl^C or input x to exit): "<<endl;
	cin>>input;
	while(repeatFlag)
	{
		cout<<myNPDA.get_current_state()<<","<<input<<","<<myNPDA.get_stackTop()<<")"<<endl;
		if(myNPDA.process(input)==true)
			cout<<"\n accepted "<<endl;
		else
			cout<<"\n rejected"<<endl;

		myNPDA.set_current_state_to_inital("q0");
		cout<<"Enter a string to process(Ctrl^C or input x to exit): "<<endl;
		cin>>input;

		if(input=="x")
			repeatFlag=false;
	}
}
