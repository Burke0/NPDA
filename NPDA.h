/*
 * NPDA.h
 * 		Author: J. Alex Burke
 * 		4/13/21
 *      This class is used to build a general purpose NPDA
 */

#ifndef NPDA_H_
#define NPDA_H_

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include<iostream>
#include<iterator>
#include<stack>


using namespace std;
class NPDA
{
	public:

	void add_state(string s);
	void add_final_state(string s);
	void add_stack_start(string s);
	void add_input_alphabet_symbol(string s);
	void add_stack_alphabet_symbol(string s);
	void add_transition(string beforeState, string symbol, string stackTop, string afterState, string stackAfter);
	void set_current_state_to_inital(string s);
	void display_NPDA();
	bool is_symbol_valid(string s);
	void set_stack_start(string s);
	string get_stack_start();
	string get_current_state();
	string get_stackTop();
	stack<string> get_stack();
	void transition_to_next_state(string input, string stackTop);
	bool is_final_state();
	bool process(string s);

	private:
	string currentState, initialState, stackStart;
	vector<string> states;
	vector<string> inputAlphabet;
	vector<string> stackAlphabet;
	vector<string> finalStates;
	stack<string> stack;
	map <tuple<string,string,string>,pair<string,string>>transitions;

};



#endif /* NPDA_H_ */
