#include <iostream>

#include "turing_machine.cc"

using namespace std;

int main()
{
	// parsing an example
	TuringMachine::Rule r1('0', '_', TuringMachine::Direction::RIGHT);
	TuringMachine::Rule r2('0', '0', TuringMachine::Direction::RIGHT);
	TuringMachine::Rule r3('1', '1', TuringMachine::Direction::RIGHT);
	TuringMachine::Rule r4('_', '_', TuringMachine::Direction::LEFT);
	TuringMachine::Rule r5('1', '_', TuringMachine::Direction::LEFT);
	TuringMachine::Rule r6('1', '1', TuringMachine::Direction::LEFT);
	TuringMachine::Rule r7('0', '0', TuringMachine::Direction::LEFT);
	TuringMachine::Rule r8('_', '_', TuringMachine::Direction::RIGHT);

	TuringMachine::State q_0("q_0");
	TuringMachine::State q_1("q_1");
	TuringMachine::State q_2("q_2");
	TuringMachine::State q_3("q_3");
	TuringMachine::State q_4("q_4");
	TuringMachine::State q_a("q_a");
	TuringMachine::State q_r("q_r");

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
	TuringMachine::Result result = tm.check_input_string("00001111___");

	// check the result and print it
	switch (result)
	{
	case TuringMachine::Result::ACCEPTED:
		cout << BOLDGREEN << "ACCEPTED" << RESET << endl;
		break;
	case TuringMachine::Result::REJECTED:
		cout << BOLDRED << "REJECTED" << RESET << endl;
		break;
	}
	return 0;
}
