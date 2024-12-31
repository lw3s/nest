#ifndef LIST_HPP
#define LIST_HPP

#include "list_node.hpp"

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <functional>
#include <string>
#include <initializer_list>

class ListOutOfBounds : public std::range_error {
public:
    explicit ListOutOfBounds() : std::range_error("List index out of bounds") {}
};

template <typename T>
class List {
    size_t _length;
    ListNode<T>* _begin;
    ListNode<T>* _back;

public:

    class iterator {
        friend class List;
        ListNode<T>* _node;
    public:
        iterator(ListNode<T>* node) : _node(node) {}
        iterator& operator++() { _node = _node->next(); return *this; }
        iterator& operator--() { _node = _node->prev(); return *this; }
        T operator*() const { return _node->val; }
        ListNode<T>* node() const { return _node; }
        bool operator==(const typename List<T>::iterator& rhs) {
            return _node == rhs._node;
        }
        bool operator!=(const typename List<T>::iterator& rhs) {
            return _node != rhs._node;
        }
    };
    
    class const_iterator {
        friend class List;
        const ListNode<T>* _node;
    public:
        const_iterator(ListNode<T>* node) : _node(node) {}
        const_iterator& operator++() { _node = _node->next(); return *this; }
        const_iterator& operator--() { _node = _node->prev(); return *this; }
        T operator*() const { return _node->val; }
        const ListNode<T>* node() const { return _node; }
        bool operator==(const typename List<T>::const_iterator& rhs) {
            return _node == rhs._node;
        }
        bool operator!=(const typename List<T>::const_iterator& rhs) {
            return _node != rhs._node;
        }
    };

    List() : _length(0), _begin(nullptr), _back(nullptr) {};
    List(const std::initializer_list<T> il) {
        for (T i : il) {
            pushr(i);
        }
    }
    List(const List<T>& list) : _length(0), _begin(nullptr), _back(nullptr) {
        for (auto it : list) {
            pushr(it);
        }
    }
    List(const std::vector<T>& list) : _length(0), _begin(nullptr), _back(nullptr) {
        for (auto it : list) {
            pushr(it);
        }
    }
    List(const T* list, size_t length) : _length(0), _begin(nullptr), _back(nullptr) {
        for (size_t i = 0; i < length; ++i) {
            pushr(list[i]);
        }
    }
    List(std::function<T(size_t)> func, size_t length): _length(0), _begin(nullptr), _back(nullptr) {
        for (size_t i = 0; i < length; ++i) {
            pushr(func(i));
        }
    }
    ~List() { clear(); }

    std::string string() {
        return (std::ostringstream() << *this).str();
    }
    
    size_t length() const { return _length; }
    size_t size() const { return _length; }
    bool empty() const { return _length == 0; }
    void clear() {
        for (auto* p = _begin; p != nullptr;) {
            auto* p_next = p->next();
            delete p;
            p = p_next;
        }
        _length = 0;
        _begin = nullptr;
        _back = nullptr;
    }

    iterator begin() { return iterator(_begin); }
    const_iterator begin() const { return const_iterator(_begin); }
    iterator end() { return nullptr; }
    const_iterator end() const { return nullptr; }
    iterator back() { return iterator(_back); }
    const_iterator back() const { return const_iterator(_back); }

    T& operator[](int pos) {
        if (pos < 0) pos += _length;
        if (!(0 <= pos && pos < _length)) throw ListOutOfBounds();
        if (pos >= _length / 2) {
            auto it = back();
            for (size_t _ = 0; _ < _length - pos - 1; ++_) --it;
            return it.node()->val;
        } else {
            auto it = begin();
            for (size_t _ = 0; _ < pos; ++_) ++it;
            return it.node()->val;
        }
    }
    void insert(int pos, T val) {
        if (pos < 0) pos += _length + 1;
        if (!(0 <= pos && pos <= _length)) throw ListOutOfBounds();
        
        ListNode<T>* inserted = new ListNode<T>(val);
        if (_length == 0) {
            _begin = _back = inserted;
            goto end;
        }
        if (pos == 0) {
            _begin->insert_left(inserted);
            _begin = inserted;
            goto end;
        }
        if (pos == _length) {
            _back->insert_right(inserted);
            _back = inserted;
            goto end;
        }
        
        if (pos < _length / 2) {
            auto it = begin();
            for (auto _ = 0; _ < pos - 1; ++_) ++it;
            it.node()->insert_right(inserted);
        } else {
            auto it = back();
            for (auto _ = 0; _ < _length - pos; ++_) --it;
            it.node()->insert_right(inserted);
        }
        end:
        ++_length;
    }
    void del(int pos) { 
        if (pos < 0) pos += _length;
        if (!(0 <= pos && pos < _length)) throw ListOutOfBounds();
    
        if (pos == 0) {
            _begin = _begin->next();
            delete _begin->prev();
            goto end;
        } if (pos == _length - 1) {
            _back = _back->prev();
            delete _back->next();
            goto end;
        }
    
        if (pos >= _length / 2) {
            auto it = back();
            for (size_t _ = 0; _ < _length - pos - 1; ++_) {
                --it;
            }
            delete it.node();
        } else {
            auto it = begin();
            for (size_t _ = 0; _ < pos; ++_) {
                ++it;
            }
            delete it.node();
        }
        end:
        --_length;
    }
    std::vector<size_t> find_vals(T val) {
        std::vector<size_t> its;
        size_t index = 0;
        for (auto it : *this) {
            if (it == val) {
                its.push_back(index);
            }
            ++index;
        }
        return its;
    }
    void del_vals(T val) {
        if (empty()) return;
        while (_begin->val == val && _begin != _back) {
            _begin = _begin->next();
            delete _begin->prev();
            --_length;
        }
        while (_back->val == val && _begin != _back) {
            _back = _back->prev();
            delete _back->next();
            --_length;
        }
        if (_begin == _back) {
            if (_begin->val == val) {
                delete _begin;
                _begin = _back = nullptr;
                _length = 0;
            }
            return;
        }
        for (auto i = begin(); i != back(); ++i) {
            for (;*i == val; ++i) {
                delete i.node();
                --_length;
            }
        }
    }
    
    void pushl(T val) { insert(0, val); }
    void pushr(T val) { insert(-1, val); }
    void popl() { del(0); }
    void popr() { del(-1); }
    
    bool operator==(const List<T> rhs) {
        if (_length != rhs._length) return false;
        auto l = begin(), r = rhs.begin();
        while (l != nullptr && r != nullptr) {
            if (*l != *r) return false;
            ++l; ++r;
        }
        return true;
    }
    bool operator!=(const List<T> rhs) {
        if (_length != rhs._length) return true;
        auto l = begin(), r = rhs.begin();
        while (l != nullptr && r != nullptr) {
            if (*l != *r) return true;
            ++l; ++r;
        }
        return false;
    }
    T reduce(std::function<T(T, T)> fn, T start = T()) {
        for (auto i : *this) {
            start = fn(start, i);
        }
        return start;
    }
    void apply(std::function<T(T)> fn) {
        for (auto i = begin(); i != nullptr; ++i) {
            i.node()->val = fn(i.node()->val);
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& rhs) {
    os << "{";
    if (!rhs.empty()) {
        for (auto i = rhs.begin(); i != rhs.back(); ++i) {
            os << *i << ", ";
        }
        os << *rhs.back();
    }
    os << "}";
    return os;
}

#endif // LIST_HPP