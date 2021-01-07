#include <iostream>

#include "turing_machine.cc"

using namespace std;
using namespace TuringMachine;

int main()
{
	// parsing an example
	Rule r1('0', '_', Direction::RIGHT);
	Rule r2('0', '0', Direction::RIGHT);
	Rule r3('1', '1', Direction::RIGHT);
	Rule r4('_', '_', Direction::LEFT);
	Rule r5('1', '_', Direction::LEFT);
	Rule r6('1', '1', Direction::LEFT);
	Rule r7('0', '0', Direction::LEFT);
	Rule r8('_', '_', Direction::RIGHT);

	State q_0("q_0");
	State q_1("q_1");
	State q_2("q_2");
	State q_3("q_3");
	State q_4("q_4");
	State q_a("q_a");
	State q_r("q_r");

	q_0.transitions.emplace(r1, q_1);
	q_0.transitions.emplace(r8, q_a);

	q_1.transitions.emplace(r2, q_1);
	q_1.transitions.emplace(r3, q_2);

	q_2.transitions.emplace(r3, q_2);
	q_2.transitions.emplace(r4, q_3);

	q_3.transitions.emplace(r5, q_4);

	q_4.transitions.emplace(r6, q_4);
	q_4.transitions.emplace(r7, q_4);
	q_4.transitions.emplace(r8, q_0);

	// making the TM
	TuringMachine::TuringMachine tm(
			{q_0,
			 q_1,
			 q_2,
			 q_3,
			 q_4,
			 q_a,
			 q_r},
			{'0', '1'},
			{'0', '1', '_'},
			q_0, q_a, q_r);

	// run our TM in an input string
	Result result = tm.check_input_string("00001111___");

	// check the result and print it
	switch (result)
	{
	case Result::ACCEPTED:
		cout << BOLDGREEN << "ACCEPTED" << RESET << endl;
		break;
	case Result::REJECTED:
		cout << BOLDRED << "REJECTED" << RESET << endl;
		break;
	}
	return 0;
}
