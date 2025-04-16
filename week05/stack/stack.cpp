#include <iostream>
#include <string>

struct Stack {
  private:
    struct node {
        int key;
        node *p_next;
        node() : key(0), p_next(nullptr) {}
        node(int _key) : key(_key), p_next(nullptr) {}
    } *top;

    void add_to_front(int key) {
        node *k = new node(key);
        if (!top)
            top = k;
        else
            k->p_next = top, top = k;
    }

    bool remove_front() {
        if (!top)
            return false;
        else {
            node *k = top;
            top = top->p_next;
            delete k;
            return true;
        }
    }

    int _size;

  public:
    Stack() : top(nullptr), _size(0) {}

    ~Stack() {
        while (remove_front());
    }

    int size() const {
        return _size;
    }

    bool is_empty() const {
        return size() == 0;
    }

    void push(int key) {
        _size++;
        add_to_front(key);
    }

    int pop() {
        if (!is_empty()) {
            _size--;
            int key = top->key;
            remove_front();
            return key;
        } else return 0;
    }

    void print() const {
        if (is_empty())
            std::cout << "EMPTY\n";
        else {
            for (node *k = top; k != nullptr; k = k->p_next)
                std::cout << k->key << ' ';
            std::cout << '\n';
        }
    }
};

// Declarations

Stack *initializeStack();

void push(Stack &s, int key);

int pop(Stack &s);

int size(Stack s);

bool isEmpty(Stack s);


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Stack *s = nullptr;
    std::string instruction;
    
    while (std::cin >> instruction) {
        if (instruction == "init") {
            if (!s)
                s = new Stack();
        } else if (instruction == "push") {
            int key;
            std::cin >> key;
            push(*s, key);
        } else if (instruction == "pop") {
            pop(*s);
        } else
            throw (instruction);
    
        s->print();
    }

    std::fclose(stdin);
    std::fclose(stdout);
}

// Definition

Stack *initializeStack() {
    return new Stack();
}

void push(Stack &s, int key) {
    s.push(key);
}

int pop(Stack &s) {
    return s.pop();
}

int size(Stack s) {
    return s.size();
}

bool isEmpty(Stack s) {
    return s.is_empty();
}