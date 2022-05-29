#include "pasha_lib.hpp"
#include "linked_list.hpp"
#include "dual_linked_list.hpp"
#include "stack.h"
#include "queue.h"

#include <stack>

#include <iostream>

using namespace pasha_lib;
using namespace std;

template <typename T>
void printAndClearStack(Stack<T>* s) {
    while (!s->empty()) {
        cout << s->popTop() << endl;
    }
}

int main() {
    stack<int> x;
    Stack<int>* s1 = new LinkedListBasedStack<int>();
    s1->pushTop(1);
    s1->pushTop(3);
    s1->pushTop(2);

    printAndClearStack(s1);
    return 0;
}
