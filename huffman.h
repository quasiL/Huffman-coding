#ifndef HUFFMAN_CODING_HUFFMAN_H
#define HUFFMAN_CODING_HUFFMAN_H

#include <string>
#include <iostream>
#include <queue>
#include <bitset>
#include <stdexcept>
#include <random>
#include <fstream>
#include <ctime>
#include <iomanip>

#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

/**
 * Tree node
 */
struct node {
    char symbol = 0;
    size_t count = 0;
    node *left_node = nullptr;
    node *right_node = nullptr;
};

/**
 * Comparing nodes
 */
struct compare_nodes {
    bool operator()(const node *lhs, const node *rhs) const
    {
        return lhs->count > rhs->count;
    }
};

/**
 * Main tree class
 */
class huffman {
private:
    string word;
    string coded_word;
    vector<pair<size_t, char>> vec;
    priority_queue<node*, vector<node*>, compare_nodes> pqueue;
public:

    /**
     * Default constructor
     */
    huffman();

    /**
     * Basic constructor fills the vector and creates a queue
     * @param w
     */
    explicit huffman(string w);

    /**
     * Destructor of the tree
     */
    ~huffman();

    /**
     * Recursive tree traversal for the destructor
     * @param n
     */
    void tree_destroyer(node* n);

    /**
     * Check if the symbol is already in the vector
     * @param symbol
     * @return -1 if not or index of symbol in the vector
     */
    size_t vector_contains(const char &symbol) const;

    /**
     * Create tree of symbols
     * After that, the queue will have only one element which is the root of this tree
     */
    void create_tree();

    /**
     * Recursive tree traversal for coding string of symbols
     * @param root
     * @param str
     * @param res
     */
    void code(node* root, const string &str, vector<pair<char, string>> &res);

    /**
     * Calls method code and displays information about a whole process
     */
    void print_codes();

    /**
     * Calls method code and displays only codes. Suitable for large files
     */
    void short_print_codes(bool r = true);

    /**
     * Getter
     * @return coded_word
     */
    string get_coded_word();

    /**
     * Recursive tree traversal for decoding string of bits
     * @param root
     * @param str
     * @param ind
     */
    void decode(node* root, string &str, int &ind);

    /**
     * Calls method decode and displays the initial string of symbols
     */
    void print_decodes();

    /**
     * Output operator overloading for huffman class
     * @param out
     * @param h
     * @return output stream
     */
    friend ostream &operator << (ostream &out, huffman &h);
};

/**
 * Timer
 * @tparam TimePoint
 * @param tp
 * @return time
 */
template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

/**
 * Queue for thread's work
 */
class lines_queue {
private:
    std::queue<string> queue;
    std::mutex mutex;
    std::condition_variable take_var, add_var;
    bool closing = false;
public:

    /**
     * Get element from the queue
     * @return queue element
     */
    std::pair<string, bool> get();

    /**
     * Remove element from the queue
     * @param e
     */
    void remove(string const& e);

    /**
     * Notify others about empty queue
     */
    void close();
};

#endif //HUFFMAN_CODING_HUFFMAN_H