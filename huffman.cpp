#include "huffman.h"

huffman::huffman() = default;

huffman::huffman(string w) :
    word(std::move(w))
    {
        size_t tmp;
        for (auto &i : word) {
            tmp = vector_contains(i);
            if (tmp != (size_t)-1) {
                vec[tmp].first++;
            } else {
                vec.emplace_back(1, i);
            }
        }

        for (auto i : vec) {
            pqueue.push(new node{i.second, i.first});
        }
    }

size_t huffman::vector_contains(const char &symbol) const
{
    for (auto i=0; i<(int)vec.size(); i++) {
        if (vec[i].second == symbol) return i;
    }
    return -1;
}

void huffman::create_tree()
{
    while (pqueue.size() != 1)
    {
        node* left = pqueue.top(); pqueue.pop();
        node* right = pqueue.top();	pqueue.pop();
        pqueue.push(new node{'\0', left->count + right->count, left, right});
    }
}

void huffman::code(node *root, const string &str, vector<pair<char, string>> &res)
{
    if (root == nullptr) return;

    if (root->left_node == nullptr && root->right_node == nullptr) {
        res.emplace_back(root->symbol, (!str.empty()) ? str : "1");
    }

    code(root->left_node, str + "0", res);
    code(root->right_node, str + "1", res);
}

void huffman::print_codes()
{
    vector<pair<char, string>> codes;
    code(pqueue.top(), coded_word, codes);

    cout << endl << "Your string was: " << endl << '\t' << word << endl << endl;
    cout << "In binary format without Huffman coding: " << endl << '\t';
    for (size_t i=0; i<word.size(); i++)
    {
        cout << bitset<8>(word.c_str()[i]);
    }
    cout << endl;

    cout << endl << "Huffman codes for individual characters in this string:" << endl;
    for (const auto& i : codes) {
        cout << '\t' << i.first << " | " << i.second << endl;
    }
    for (char j : word)
    {
        for (const auto& k : codes) {
            if (j == k.first) {
                coded_word += k.second;
                break;
            }
        }
    }
    cout << endl << "Result:" << endl << '\t' << coded_word << endl;
}

void huffman::short_print_codes(bool r)
{
    vector<pair<char, string>> codes;
    code(pqueue.top(), coded_word, codes);
    for (char j : word)
    {
        for (const auto& k : codes) {
            if (j == k.first) {
                coded_word += k.second;
                break;
            }
        }
    }
    if (r) cout << '\t' << coded_word << endl;
}

string huffman::get_coded_word()
{
    return coded_word;
}

void huffman::decode(node *root, string &str, int &ind)
{
    if (root == nullptr) return;

    if (root->left_node == nullptr && root->right_node == nullptr) {
        cout << root->symbol;
        return;
    }
    ind++;

    if (str[ind] == '0') decode(root->left_node, str, ind);
    else decode(root->right_node, str, ind);
}

void huffman::print_decodes()
{
    cout << endl << "Decoding result: " << endl << '\t';
    int ind = -1;
    while (ind < (int)coded_word.size()-1) {
        decode(pqueue.top(), coded_word, ind);
    }
    cout << endl;
}

huffman::~huffman()
{
    tree_destroyer(pqueue.top());
}

void huffman::tree_destroyer(node *n)
{
    if (n != nullptr) {
        tree_destroyer(n->left_node);
        tree_destroyer(n->right_node);
        delete n;
    }
}

ostream &operator<<(ostream &out, huffman &h)
{
    cout << "queue contains " << h.pqueue.size() << " elements" << endl;
    return out;
}