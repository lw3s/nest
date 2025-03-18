#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

template<typename T>
class ListNode {
    /**
     * class ListNode<T>
     * 
     * enable doubly-linked lists, keeping a pointer to the left and the right and a public value `val`
     * automatically points left and right nodes to each other on destruction
     */
    ListNode<T>* _next;
    ListNode<T>* _prev;
public:
    T val;
    
    ListNode(T val) : val(val), _prev(nullptr), _next(nullptr) {}
    ListNode(const ListNode<T>& node) { *this = ListNode(node.val); }
    ~ListNode() {
        if (_prev) _prev->_next = _next;
        if (_next) _next->_prev = _prev;
    }
    inline ListNode<T>* prev() const { return _prev; }
    inline ListNode<T>* next() const { return _next; }
    void insert_left(ListNode<T>* node) {
        /**
         * void insert_left(ListNode<T>*)
         * 
         * insert the input node directly to this node's left
         */
        if (_prev) _prev->_next = node;
        node->_next = this;
        node->_prev = _prev;
        _prev = node;
    }
    void insert_right(ListNode<T>* node) {
        /**
         * void insert_left(ListNode<T>*)
         * 
         * insert the input node directly to this node's right
         */
        if (_next) _next->_prev = node;
        node->_prev = this;
        node->_next = _next;
        _next = node;
    }
};

#endif // LIST_NODE_HPP
