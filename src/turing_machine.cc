// colors for printing config.
#define BOLDYELLOW "\033[1m\033[33m"
#define RESET "\033[0m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDRED "\033[1m\033[31m"

#include <iostream>
#include <vector>
#include <map>

using namespace std;

namespace TuringMachine
{
  enum class Direction
  {
    LEFT,
    RIGHT,
  };

  enum class Result
  {
    ACCEPTED,
    REJECTED,
    ON_GOING,
  };

  struct Rule
  {
    char read_symbol, write_symbol;
    Direction direction;

    // constructor
    Rule(char r, char w, Direction d) : read_symbol(r), write_symbol(w), direction(d) {}

    // compare operator
    bool operator==(const Rule &other) const
    {
      return read_symbol == other.read_symbol && write_symbol == other.write_symbol && direction == other.direction;
    }
  };

  bool operator<(const Rule &a, const Rule &b) { return a.read_symbol < b.read_symbol; }

  struct State
  {
    string name;
    map<Rule, State &> transitions;

    State(string n) : name(n) {}

    // compare operator
    bool operator==(const State &other) const
    {
      return name == other.name;
    }
  };

  struct TuringMachine
  {
    vector<State> states;
    vector<char> input_alphabet;
    vector<char> tape_alphabet;
    State q_0, q_a, q_r;
    TuringMachine(vector<State> i_states,
                  vector<char> i_input_alphabet,
                  vector<char> i_tape_alphabet, State i_q_0,
                  State i_q_a, State i_q_r)
        : states(i_states), input_alphabet(i_input_alphabet),
          tape_alphabet(i_tape_alphabet), q_0(i_q_0), q_a(i_q_a), q_r(i_q_r) {}

    Result check_input_string(string input_string)
    {
      size_t current_index = 0;
      State current_state = q_0;
      Result result = Result::ON_GOING;
      print_current_config(input_string, current_index, current_state);

      while (result == Result::ON_GOING)
      {
        handle_current_char(input_string, current_index, current_state);
        print_current_config(input_string, current_index, current_state);
        if (current_state == q_a)
        {
          result = Result::ACCEPTED;
        }
        else if (current_state == q_r)
        {
          result = Result::REJECTED;
        }
      }

      return result;
    }

  private:
    void handle_current_char(string &input_string, size_t &current_index, State &current_state)
    {
      char &head_symbol = input_string[current_index];

      for (auto &pair : current_state.transitions)
      {
        if (pair.first.read_symbol == head_symbol)
        {
          head_symbol = pair.first.write_symbol;                    // a -> b
          current_index = (pair.first.direction == Direction::LEFT) // R, L
                              ? current_index - 1
                              : current_index + 1;
          current_state = pair.second;
          return;
        }
      }
      current_state = q_r;
    }

    // prints uqv
    void print_current_config(string &input_string,
                              size_t &current_index, State &current_state)
    {
      // print u
      for (size_t i = 0; i < current_index; i++)
        cout << input_string[i];
      // print q
      cout << BOLDYELLOW << current_state.name << RESET;
      // print v
      for (size_t i = current_index; i < input_string.size(); i++)
        cout << input_string[i];
      cout << endl;
    }
  };
} // namespace TuringMachine