class MinStack {
private:
    stack<int> normalStack;
    stack<int> miniStack;
public:
    void push(int x) {
	    normalStack.push(x);
	    if (miniStack.empty() || x <= getMin())  miniStack.push(x);	    
    }
    void pop() {
	    if (normalStack.top() == getMin())  miniStack.pop();
	    normalStack.pop();
    }
    int top() {
	    return normalStack.top();
    }
    int getMin() {
	    return miniStack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
