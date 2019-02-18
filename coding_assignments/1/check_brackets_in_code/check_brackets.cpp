#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
			opening_brackets_stack.push(Bracket(next, position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
			if (opening_brackets_stack.size()) {
				Bracket temp_bracket = opening_brackets_stack.top();
				if (temp_bracket.Matchc(next))
					opening_brackets_stack.pop();
				else {
					cout << position + 1;
					return 0;
				}
			}
			else {
				cout << position + 1;
				return 0;
			}
        }
    }
	
    // Printing answer, write your code here
	Bracket temp1_bracket(' ', 0);
	while (opening_brackets_stack.size()) {
		temp1_bracket.type = opening_brackets_stack.top().type;
		temp1_bracket.position = opening_brackets_stack.top().position;
		opening_brackets_stack.pop();
	}
	if (temp1_bracket.type != ' ')
		cout << temp1_bracket.position;
	else
		cout << "Success";

	return 0;
}

