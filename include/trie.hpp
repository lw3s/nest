#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <utility>


class Trie {
    Trie* _subtries[26];
    bool _is_end;
    const int _depth;

public:
    Trie(size_t depth = 0) : _is_end(false), _depth(depth) {
        for (int i = 0; i < 26; ++i) {
            _subtries[i] = nullptr;
        }
    }
    ~Trie() {
        for (int i = 0; i < 26; ++i) {
            delete _subtries[i];
        }
    }
    void add(std::string str) {
        if (_depth == str.size()) {
            _is_end = true;
            return;
        }
        if (_depth == 0) {
            for (size_t i = 0; i < str.size(); ++i) {
                str[i] = std::tolower(str[i]);
            }
        }
        int subtrie = str[_depth] - *"a";
        if (!_subtries[subtrie]) _subtries[subtrie] = new Trie(_depth + 1);
        _subtries[subtrie]->add(str);
    }
    bool contains(std::string str) {
        if (_depth == str.size()) {
            return _is_end;
        }
        if (_depth == 0) {
            for (size_t i = 0; i < str.size(); ++i) {
                str[i] = std::tolower(str[i]);
            }
        }
        Trie* subtrie = _subtries[str[_depth] - *"a"];
        if (subtrie == nullptr) return false;
        return subtrie->contains(str);
    }
    std::vector<std::string> all_strings() { // not recommended to use, just there for convenience and client-side debugging
        std::vector<std::string> words;
        for (int i = 0; i < 26; ++i) {
            if (_subtries[i] != nullptr) {
                for (auto str : _subtries[i]->all_strings()) {
                    words.push_back(str);
                    words[words.size() - 1][_depth] = *"a" + i;
                }
            }
        }
        if (_is_end) {
            words.push_back(std::string(_depth, *" "));
        }
        return words;
    }
};

#endif // TRIE_HPP