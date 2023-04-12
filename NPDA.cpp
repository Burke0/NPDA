/*
 * NPDA.cpp
 *      Author: J. Alex Burke
 *      4/13/21
 */



#include "NPDA.h"


void NPDA::add_state(string s)
{
	states.insert(states.end(),s);
}

void NPDA::add_final_state(string s)
{
	finalStates.insert(finalStates.end(),s);
}

void NPDA::add_input_alphabet_symbol(string s)
{
	inputAlphabet.insert(inputAlphabet.end(),s);
}
void NPDA::add_stack_alphabet_symbol(string s)
{
	stackAlphabet.insert(stackAlphabet.end(),s);
}
void NPDA::add_transition(string beforeState, string symbol,string stackTop, string afterState, string stackAfter)
{
	transitions.insert({{beforeState,symbol, stackTop},{afterState, stackAfter}});
}

void NPDA::set_current_state_to_inital(string s)
{
	currentState=initialState=s;
	while(!stack.empty())
	{
		stack.pop();
	}
	stack.push(stackStart);

}

void NPDA::display_NPDA()
{
	map<tuple<string, string, string>,pair<string,string>>::iterator it = transitions.begin();

	cout<<"\n----NPDA--------------------------------------------\n<states>\n";
    copy(states.begin(), states.end(), ostream_iterator<string>(cout," "));
	cout<<"\n<input alphabet>\n";
	copy(inputAlphabet.begin(), inputAlphabet.end(), ostream_iterator<string>(cout," "));
	cout<<"\n<stack alphabet>\n";
		copy(stackAlphabet.begin(), stackAlphabet.end(), ostream_iterator<string>(cout," "));
	cout<<"\n<transitions>\n";
	while (it != transitions.end())
    {
        tuple<string,string,string> t= it->first;
        string s1= get<0>(t);
        string s2= get<1>(t);
        string s3= get<2>(t);
        string s4= it->second.first;
        string s5= it->second.second;
        cout <<"(" << s1 + "," << s2 << "," << s3 << ")" << " -> " << "(" << s4 << "," << s5+ ")" << "\n";
        it++;
    }
	cout<<"<initial state>\n" << initialState << "\n<stack start>\n" << stackStart << "\n<final states>\n";
	copy(finalStates.begin(),finalStates.end(), ostream_iterator<string>(cout," "));
	cout<<"\n---------------------------------------------------------\n";

}
bool NPDA::is_symbol_valid(string s)
{
	if(s=="")
		return false;
	else if(find(inputAlphabet.begin(), inputAlphabet.end(), s) != inputAlphabet.end())
		return true;
	else
	{
		cout<<s<<": invalid symbol"<<endl;
		return false;
	}
}
void NPDA:: set_stack_start(string s)
{
	stackStart=s;
	stack.push(s);
}
string NPDA:: get_stack_start()
{
	return stackStart;
}
stack<string> NPDA:: get_stack()
{
	return stack;
}
string NPDA::get_current_state()
{
	return currentState;
}
string NPDA::get_stackTop()
{
	return stack.top();
}
void NPDA::transition_to_next_state(string input, string stackTop)
{

	if (transitions.count({get_current_state(), input, stackTop}))
	{
		pair<string, string> tempPair = transitions.at({get_current_state(), input, stackTop});
		currentState=tempPair.first;// first element in value pair is the next state. current state is set to the next state.
		string newStackTop=tempPair.second;
		stack.pop();
		if(tempPair.second != "*")//second element in value pair is the new stack top. * is lamda so nothing is pushed on stack.
		{
			int numCharToAddToStack=tempPair.second.length();
			while(numCharToAddToStack>=0)
			{
				stack.push(tempPair.second.substr(numCharToAddToStack,1));
				numCharToAddToStack--;
			}
		}
		else if(stack.empty() && tempPair.second == "*")
			stack.push("*");
		//cout<<"|- ("<<currentState<<","<<"placeholder for remaining string"<<","<<stack.top()<<endl;
	}
	else
	{
		cout<<" transition failed"<<endl;
	}

}
bool NPDA::is_final_state()
{
	if(count(finalStates.begin(), finalStates.end(), currentState))
		return true;
	else
		return false;
}
bool NPDA::process(string s)
{//TODO fix recursive function...

	string nextChar=s.substr(0,1);
	std::stack<string> tempStackCopy;
	if(s=="" && is_final_state())
	{
		return true;
	}
	if(is_symbol_valid(nextChar))
	{
		transition_to_next_state(nextChar, get_stackTop());

		tempStackCopy=stack;
		cout<<"|- ("<<currentState<<","<<s.substr(1)<<",";
		while(!tempStackCopy.empty())
		{
			cout<<tempStackCopy.top();
			tempStackCopy.pop();
		}
		cout<<")"<<endl;

		if(process(s.substr(1))==true)
			return true;
	}
	else if(!is_symbol_valid(nextChar))
	{
		transition_to_next_state("*", get_stackTop());

		tempStackCopy=stack;
		cout<<"|- ("<<currentState<<","<<"*"<<",";
		while(!tempStackCopy.empty())
		{
			cout<<tempStackCopy.top();
			tempStackCopy.pop();
		}
		cout<<")"<<endl;

		if(s.size()>1 && process(s.substr(1))==true)
			return true;
	}
	return false;


}

