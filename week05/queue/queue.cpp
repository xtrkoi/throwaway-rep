#include <iostream>

struct Queue {
  private:
    struct node {
        int key;
        node *p_next;
        node() : key(0), p_next(nullptr) {}
        node(int _key) : key(_key), p_next(nullptr) {}
    } *head, *tail;

    void add_to_back(int key) {
        node *k = new node(key);
        if (!tail)
            head = tail = k;
        else
            tail->p_next = k, tail = k;
    }

    bool remove_front() {
        if (!head)
            return false;
        else {
            if (head == tail)
                tail = nullptr;

            node *k = head;
            head = head->p_next;
            delete k;
            return true;
        }
    }

    int _size;

  public:
    Queue() : head(nullptr), tail(nullptr), _size(0) {}

    ~Queue() {
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
        add_to_back(key);
    }

    int pop() {
        if (!is_empty()) {
            _size--;
            int key = head->key;
            remove_front();
            return key;
        } else return 0;
    }

    void print() const {
        if (is_empty())
            std::cout << "EMPTY\n";
        else {
            for (node *k = head; k != nullptr; k = k->p_next)
                std::cout << k->key << ' ';
            std::cout << '\n';
        }
    }
};


// Declarations

Queue *initializeQueue();

void enqueue(Queue &q, int key);

int dequeue(Queue &q);

int size(Queue q);

bool isEmpty(Queue q);


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Queue *q = nullptr;
    std::string instruction;
    
    while (std::cin >> instruction) {
        if (instruction == "init") {
            if (!q)
                q = new Queue();
        } else if (instruction == "enqueue") {
            int key;
            std::cin >> key;
            enqueue(*q, key);
        } else if (instruction == "dequeue") {
            dequeue(*q);
        } else
            throw (instruction);
    
        q->print();
    }

    std::fclose(stdin);
    std::fclose(stdout);
}

// Definitions

Queue *initializeQueue() {
    return new Queue();
}

void enqueue(Queue &q, int key) {
    q.push(key);
}

int dequeue(Queue &q) {
    return q.pop();
}

int size(Queue q) {
    return q.size();
}

bool isEmpty(Queue q) {
    return q.is_empty();
}