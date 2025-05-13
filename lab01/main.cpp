#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/// @brief Find the first pointer with the same element to `val` in a contiguous addresses from `first` (inclusive) to `last` (exclusive). Linear time in complexity.
/// @tparam InputIterator Inferred from the input parameters
/// @tparam T Inferred from desired element
/// @param first A pointer
/// @param last Another pointer with the same type
/// @param val A value whose type has defined `==` operator
/// @return The first pointer in [`first`, `last`) that points to the same element as `val`, `last` if no such element is found.
template<class Iter, class T> Iter l_find(Iter first, Iter last, const T& val) {
    while (first != last) {
        if (*first == val) 
            return first;
        ++first;
    }
    return last;
}

// Stack
template<class T> class l_stack {
  private:
    template<class U> class node {
      private:
        U _data;
        node *p_next;
      public:
        node() : _data(U()), p_next(nullptr) {}
        node(U __data) : _data(__data), p_next(nullptr) {}

        void redirect_to(node *p = nullptr) { p_next = p; }

        node *next() const { return p_next; }
        node *&next() { return p_next; }

        U get() const { return _data; }
        U &get() { return _data; }

        U operator()() const { return _data; }
        U &operator()() { return &_data; }

        ~node() { p_next = nullptr; }
    };

    node<T> *p_top;
    int _size = 0;
  public:
    l_stack() : p_top(nullptr), _size(0) {}

    int size() const { return _size; }

    bool is_empty() const { return size() == 0; }

    void push(T _data) {
        _size++;
        node<T> *k = new node(_data);
        if (is_empty())
            p_top = k;
        else
            k->next() = p_top, p_top = k;
    }

    T top() const {
        if (is_empty())
            throw std::runtime_error("Accessing the top of an empty stack"); 
        
        return p_top->get();
    }

    T &top() {
        if (is_empty())
            throw std::runtime_error("Accessing the top of an empty stack"); 
        
        return p_top->get();
    }
 
    bool pop() {
        if (is_empty())
            return false;
        
        _size--;
        node<T> *k = p_top;
        p_top = p_top->next();
        delete k;
        return true;
    }

    ~l_stack() {
        while(pop());
        p_top = nullptr;
    }
};


class integer {
  private:
    // digits stored in reverse order: least significant digit first
    std::vector<int> digits;
    int sign; // +1 or -1

    // Remove leading zeros
    void normalize() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            sign = 1;
    }

    // Compare absolute values: return -1 if |a|<|b|, 0 if equal, +1 if greater
    static int absCompare(const integer &a, const integer &b) {
        if (a.digits.size() != b.digits.size())
            return a.digits.size() < b.digits.size() ? -1 : 1;
        for (int i = (int)a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] != b.digits[i])
                return a.digits[i] < b.digits[i] ? -1 : 1;
        }
        return 0;
    }

    // Addition of absolute values
    static integer addAbs(const integer &a, const integer &b) {
        integer res;
        res.digits.clear();
        int carry = 0;
        size_t n = std::max(a.digits.size(), b.digits.size());
        for (size_t i = 0; i < n; ++i) {
            int sum = carry;
            if (i < a.digits.size()) sum += a.digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            res.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry) res.digits.push_back(carry);
        return res;
    }

    // Subtraction of absolute values: assumes |a|>=|b|
    static integer subAbs(const integer &a, const integer &b) {
        integer res;
        res.digits.clear();
        int borrow = 0;
        for (size_t i = 0; i < a.digits.size(); ++i) {
            int diff = a.digits[i] - borrow - (i < b.digits.size() ? b.digits[i] : 0);
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            res.digits.push_back(diff);
        }
        res.normalize();
        return res;
    }

    // Karatsuba multiplication on digit vectors
    static std::vector<int> karatsubaMul(const std::vector<int> &x, const std::vector<int> &y) {
        size_t n = x.size();
        size_t m = y.size();
        if (n < 32 || m < 32) {
            // grade-school multiplication
            std::vector<int> res(n + m);
            for (size_t i = 0; i < n; ++i) {
                int carry = 0;
                for (size_t j = 0; j < m || carry; ++j) {
                    long long cur = res[i + j] + (long long)x[i] * (j < m ? y[j] : 0) + carry;
                    res[i + j] = int(cur % 10);
                    carry = int(cur / 10);
                }
            }
            while (res.size() > 1 && res.back() == 0) res.pop_back();
            return res;
        }
        
        size_t k = std::min(n, m) / 2;
        // x = x1 * 10^k + x0, y = y1 * 10^k + y0
        std::vector<int> x0(x.begin(), x.begin() + k);
        std::vector<int> x1(x.begin() + k, x.end());
        std::vector<int> y0(y.begin(), y.begin() + k);
        std::vector<int> y1(y.begin() + k, y.end());
        auto z0 = karatsubaMul(x0, y0);
        auto z2 = karatsubaMul(x1, y1);

        std::vector<int> sumx = addAbs(integer(x0), integer(x1)).digits;
        std::vector<int> sumy = addAbs(integer(y0), integer(y1)).digits;

        auto z1 = subAbs(integer(karatsubaMul(sumx, sumy)), addAbs(integer(z0), integer(z2))).digits;

        std::vector<int> res;
        res.resize(z0.size() + 2 * k + z2.size());

        for (size_t i = 0; i < z0.size(); ++i) res[i] += z0[i];
        for (size_t i = 0; i < z1.size(); ++i) res[i + k] += z1[i];
        for (size_t i = 0; i < z2.size(); ++i) res[i + 2 * k] += z2[i];

        // normalize carries
        int carry = 0;
        for (size_t i = 0; i < res.size(); ++i) {
            long long curr = res[i] + carry;
            res[i] = int(curr % 10);
            carry = int(curr / 10);
        }
        while (carry) {
            res.push_back(carry % 10);
            carry /= 10;
        }
        while (res.size() > 1 && res.back() == 0) res.pop_back();
        return res;
    }

    /// @returns `{quotient, remainder}` pair
    static std::pair<integer, integer> divmod(const integer &a, const integer &b) {
        if (b == integer())
            throw std::domain_error("Division by 0");
        integer divisor = b; divisor.sign = 1;
        integer dividend = a; dividend.sign = 1;
        integer quotient("0"), current;
        quotient.digits.assign(dividend.digits.size(), 0);

        for (int i = int(dividend.digits.size()) - 1; i >= 0; --i) {
            current.digits.insert(current.digits.begin(), dividend.digits[i]);
            current.normalize();
            int x = 0, l = 0, r = 9;
            while (l <= r) {
                int m = (l + r) / 2;
                integer t = divisor * integer(std::to_string(m));
                if (t <= current) {
                    x = m; l = m + 1;
                } else r = m - 1;
            }
            quotient.digits[i] = x;
            current = current - divisor * integer(std::to_string(x));
        }
        quotient.sign = a.sign * b.sign;
        quotient.normalize();

        if (quotient.sign < 0 && !(current == integer("0")))
            quotient = quotient - integer("1");
        return {quotient, current};
    }

  public:
    integer(): digits(1, 0), sign(1) {}
    integer(const std::vector<int> &d): digits(d), sign(1) {}
    integer(const std::string &s) {        
        sign = 1; digits.clear();
        size_t pos = 0;
        if (s[0] == '-') { sign = -1; pos = 1; }
        else if (s[0] == '+') { pos = 1; }
        for (size_t i = s.size(); i > pos; --i) {
            char c = s[i-1];
            if (c < '0' || c > '9') throw std::invalid_argument("Invalid digit in string");
            digits.push_back(c - '0');
        }
        normalize();
    }
    // Comparison operators
    bool operator==(const integer &other) const {
        return sign == other.sign && digits == other.digits;
    }
    bool operator!=(const integer &other) const { return !(*this == other); }
    bool operator<(const integer &other) const {
        if (sign != other.sign) return sign < other.sign;
        int cmp = absCompare(*this, other);
        return sign == 1 ? (cmp < 0) : (cmp > 0);
    }
    bool operator<=(const integer &other) const { return *this < other || *this == other; }

    // Arithmetic operators
    integer operator-() const {
        integer res = *this;
        if (!(digits.size() == 1 && digits[0] == 0))
            res.sign = -sign;
        return res;
    }

    integer operator+(const integer &other) const {
        if (sign == other.sign) {
            integer res = addAbs(*this, other);
            res.sign = sign;
            return res;
        }
        if (absCompare(*this, other) >= 0) {
            integer res = subAbs(*this, other);
            res.sign = sign;
            return res;
        } else {
            integer res = subAbs(other, *this);
            res.sign = other.sign;
            return res;
        }
    }

    integer operator-(const integer &other) const {
        return *this + (-other);
    }

    integer operator*(const integer &other) const {
        integer res;
        res.sign = sign * other.sign;
        res.digits = karatsubaMul(digits, other.digits);
        res.normalize();
        return res;
    }

    integer operator/(const integer &other) const {
        return divmod(*this, other).first;
    }

    // Stream output
    friend std::ostream &operator<<(std::ostream &os, const integer &bi) {
        if (bi.sign < 0) os << '-';
        for (int i = (int)bi.digits.size() - 1; i >= 0; --i)
            os << abs(bi.digits[i]);
        return os;
    }
};

integer to_integer(const std::string &s) {
    return integer(s);
}

long long to_ll(const std::string &s) {
    return std::stoll(s);
}

using symbol = std::string;

const std::vector<symbol> operators = {"+", "-", "*", "/"};
const std::vector<int> precedence_level = {0, 0, 1, 1};

class expression_parser {
    // Find operator precendence
    static int precendence(const symbol &s) {
        int i = std::distance(operators.begin(), l_find(operators.begin(), operators.end(), s));
        if (i == (int)operators.size())
            return -1;
        return precedence_level[i];
    }

  public:
    // Parse the expression into symbols
    static std::vector<symbol> parse_expression(const std::string &expression) {
        symbol s;
        std::vector<symbol> parsed;
        for (char c : expression) {
            if (isspace(c))
                continue;
                
            if (!s.empty() && (c == '(' || c == ')' || s.back() == '(' || s.back() == ')' || isdigit(s.back()) != isdigit(c) || is_operator(std::string(1, c))))
                parsed.push_back(s), s.clear();
            if (precendence(std::string(1, c)) == 0 && (parsed.empty() ||  parsed.back() == "("))
                parsed.push_back("0");
            s += c;
        }
        parsed.push_back(s);
        return parsed;
    }
    
    
    // Convert Infix to Postifx
    static std::vector<symbol> convert_to_postfix(const std::vector<symbol> &parsed_infix_expression) {
        l_stack<symbol> S;
        std::vector<symbol> converted;

        for (const symbol &s : parsed_infix_expression) {
            int p = precendence(s);
            if (p < 0) {
                if (s == ")") {
                    while (!S.is_empty() && S.top() != "(")
                        converted.push_back(S.top()), S.pop();
                    if (S.is_empty())
                        throw std::invalid_argument("Invalid expression - Missing \"(\"");
                    S.pop();
                } else if (s == "(")
                    S.push(s);
                else
                    converted.push_back(s);
            } else {
                while (!S.is_empty() && p <= precendence(S.top()))
                    converted.push_back(S.top()), S.pop();               
                S.push(s);
            }
        }

        while (!S.is_empty()) {
            if (S.top() == "(")
                throw std::invalid_argument("Invalid expression - Missing \")\"");
            converted.push_back(S.top()), S.pop();
        }
        
        return converted;
    }

    static bool is_operand(const symbol &s) {
        return expression_parser::precendence(s) < 0 && s != "(" && s != ")";
    }

    static bool is_operator(const symbol &s) {
        return precendence(s) >= 0 && s != "(" && s != ")";
    }
};

template<class T> T evaluate(const T &left_op, const T &right_op, symbol o) {
    if (o == "+")
        return left_op + right_op;
    if (o == "-")
        return left_op - right_op;
    if (o == "*")
        return left_op * right_op;
    if (o == "/") {
        if (right_op == T())
            throw std::domain_error("Division by 0");
        return left_op / right_op;
    }
    return left_op;
}

// Evalutate expression
template<class T> T evaluate(const std::string &expression, T (*convert_symbol_to_operand)(const std::string &)) {
    std::vector<std::string> parsing = expression_parser::parse_expression(expression);

    std::vector<std::string> postfix = expression_parser::convert_to_postfix(parsing);

    l_stack<T> st;
    for (const symbol &s : postfix) {
        if (expression_parser::is_operand(s))
            st.push(convert_symbol_to_operand(s));            
        else {
            if (st.size() < 2)
                throw std::invalid_argument("Invalid expression");
            T right_op = st.top();
            st.pop();
            T left_op = st.top();
            st.pop();

            st.push(evaluate(left_op, right_op, s));
        }
    }

    if (st.size() > 1)
        throw std::invalid_argument("Invalid expresssion");
    return st.top();
}

int main(int argc, char const *argv[]) {
    // IO

    bool _input_flag = false;
    bool _output_flag = false;

    if (argc > 1) {
        _input_flag = true;
        if (!freopen(argv[1], "r", stdin)) {
            std::cerr << argv[0] << ": Can't find or open \"" << argv[1] << "\" for read-only access." << std::endl;
            return EXIT_FAILURE;
        }
    }

    if (argc > 2) {
        _output_flag = true;
        freopen(argv[2], "w", stdout);
    }


    // Processing

    std::string e;
    while (std::getline(std::cin, e)) {
        try {
            integer result = evaluate<integer>(e, to_integer);
            std::cout << result << std::endl;
            if (_output_flag)
                std::cerr << result << std::endl;
        } 

        // try {
        //     long long result = evaluate<long long>(e, to_ll);
        //     std::cout << result << std::endl;
        // } 

        catch (std::logic_error &e) {
            // thrown_error = true;
            std::cout << e.what() << std::endl;
            if (_output_flag)
                std::cerr << e.what() << std::endl;
        }

        catch (std::runtime_error &e) {
            // thrown_error = true;
            std::cout << e.what() << std::endl;
            if (_output_flag)
                std::cerr << e.what() << std::endl;
        }
    }


    // Termination

    if (_input_flag)
        std::fclose(stdin);
    if (_output_flag)
        std::fclose(stdout);

    return 0;
}
