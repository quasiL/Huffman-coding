#include "huffman.h"

int main() {
    huffman h("beep boop beer!");
    h.create_tree();
    h.print_codes();
    h.print_decodes();
    return 0;
}
