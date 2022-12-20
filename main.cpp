#include "huffman.h"

int main(int argc, char *argv[])
{
    switch (argc) {
        case 1: {
            string in;
            cout << "Enter your string: ";
            getline(cin, in);
            if (!in.empty()) {
                huffman h(in);
                h.create_tree();
                h.print_codes();
                h.print_decodes();
            } else {
                cout << "There is nothing to code :(" << endl;
            }
            break;
        }
        case 2: {
            if ((string)argv[1] == "--help" || (string)argv[1] == "-help") {
                cout << endl << "Usage:" << endl;
                cout << '\t' << "huffman_coding [options]" << endl << endl;
                cout << "Options:" << endl;
                cout << '\t' << "-r" << '\t' << '\t' << "code random sentence" << endl;
                cout << '\t' << "-f [filename]" << '\t' << "input from file" << endl;
                cout << '\t' << "-s" << '\t' << '\t' << "save result in file" << endl;
                cout << '\t' << "--help" << '\t' << '\t' << "display this help and exit" << endl;
                cout << endl << "For more details see gitlab.fel.cvut.cz/khairart/huffman_coding" << endl;
                break;
            } else if ((string)argv[1] == "-r") {
                vector<string> vec{
                    "Everybody seems to think I'm lazy",
                    "Give me your autograph",
                    "Who wants to live forever?",
                    "The things you've said have got me real mad",
                    "Listen to the silence, let it ring on",
                    "I walk a road, horizons change",
                    "Here come the morning that I say goodbye to ya",
                    "Blow the wind blow blow",
                    "We can be heroes, just for one day",
                    "The time to hesitate is through"
                };
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distr(0, (int)vec.size());
                huffman h(vec[distr(gen)]);
                h.create_tree();
                h.print_codes();
                h.print_decodes();
                break;
            } else {
                cout << "Argument " << argv[1] << " is wrong!" << endl;
                cout << "Try huffman_coding --help" << endl;
                break;
            }
        }
        case 3: {
            if ((string)argv[1] == "-f") {
                string line;
                ifstream inpfile ("../" + (string)argv[2]);
                if (inpfile.is_open())
                {
                    cout << endl << "Result:" << endl;
                    while (getline(inpfile,line))
                    {
                        if (line.empty()) continue;
                        huffman h(line);
                        h.create_tree();
                        h.short_print_codes();
                    }
                    inpfile.close();
                } else {
                    cout << "Unable to open file. Check if this file really exists" << endl;
                }
                break;
            } else {
                cout << "Argument " << argv[1] << " is wrong!" << endl;
                cout << "Try huffman_coding --help" << endl;
                break;
            }
        }
        case 4: {
            if (((string)argv[1] == "-f" && (string)argv[2] == "-s") ||
            ((string)argv[1] == "-s" && (string)argv[2] == "-f")) {
                string line;
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distr(1111, 9999);
                string filename = to_string(distr(gen)) + "_coded_" + (string)argv[3];
                ofstream o("../" + filename);
                ifstream inpfile ("../" + (string)argv[3]);
                if (inpfile.is_open())
                {
                    while (getline(inpfile,line))
                    {
                        if (line.empty()) continue;
                        huffman h(line);
                        h.create_tree();
                        h.short_print_codes(false);
                        o << h.get_coded_word() << endl;
                    }
                    inpfile.close();
                    cout << "The result has been placed in the file " << filename << endl;
                } else {
                    cout << "Unable to open file. Check if this file really exists" << endl;
                }
                break;
            } else {
                cout << "Argument " << argv[1] << " or " << argv[2] << " is wrong!" << endl;
                cout << "Try huffman_coding --help" << endl;
                break;
            }
        }
        default: {
            throw invalid_argument("Received invalid argument");
        }
    }
    return 0;
}