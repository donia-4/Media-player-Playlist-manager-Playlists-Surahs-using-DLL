#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct Node
{
    T data ;
    Node* next ;
    Node* prev ; // Previous node!

    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    ~Node() = default;
    void set(Node* next, Node* prev)
    {
        this->next = next;
        this->prev = prev;
    }
};

template <typename T>
class DLL
{
private:
    Node<T>* head;
    Node<T>* tail;
    int length = 0;

    vector<Node<T>*> debug_data;

    void debug_add_node(Node<T>* node)
    {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node<T>* node)
    {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }
    Node<T>* delete_and_link(Node<T>* cur)   // utility function
    {
        Node<T>* ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        return ret;
    }
public:
    DLL() : head(nullptr), tail(nullptr), length(0) {}
    DLL(const DLL<T>& other) : head(nullptr), tail(nullptr), length(0)
    {
        Node<T>* current = other.head;
        while (current)
        {
            insert_end(current->data);
            current = current->next;
        }
    }
    DLL& operator=(const DLL& another)
    {
        if (this == &another)
            return *this;
        while (head)
            delete_front();
        Node<T>* current = another.head;
        while (current)
        {
            insert_end(current->data);
            current = current->next;
        }
    }

    ~DLL()
    {
        Node<T>* current = head;
        while (current)
        {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node<T>* cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int)debug_data.size());

        len = 0;
        for (Node<T>* cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
    }

    void print()
    {
        for (Node<T>* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void delete_node(Node<T>* node)
    {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node<T>* node)
    {
        debug_add_node(node);
        ++length;
    }
    T& get_node_at(size_t index) const
    {
        assert(index >= 0 && index < length);
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;
        return current->data;
    }


    void link(Node<T>* first, Node<T>* second)   // utility function
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void insert_end(T value)
    {
        Node<T>* item = new Node<T>(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(tail, item);
            tail = item;
        }
        debug_verify_data_integrity();
    }

    void insert_front(T value)
    {
        Node<T>* item = new Node<T>(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        debug_verify_data_integrity();
    }

    void print_reversed()
    {
        for (Node<T>* cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void delete_front()
    {
        if (!head)
            return;
        Node<T>* cur = head->next;
        delete_node(head);
        head = cur;

        if (head)
            head->prev = nullptr;
        else if (!length)
            tail = nullptr;

        debug_verify_data_integrity();
    }

    void delete_end()
    {
        if (!head)
            return;
        Node<T>* cur = tail->prev;
        delete_node(tail);
        tail = cur;

        if (tail)
            tail->next = nullptr;
        else if (!length)
            head = nullptr;

        debug_verify_data_integrity();
    }
    T& operator[](size_t index)
    {
        assert(index < length);
        Node<T>* current = head;

        for (size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }

        return current->data;
    }
    T& operator[](size_t index) const
    {
        assert(index < length);
        Node<T>* current = head;

        for (size_t i = 0; i < index; ++i)
            current = current->next;

        return current->data;
    }
    size_t get_length() const
    {
        return length;
    }
    void delete_node_with_key(T value)
    {
        if (!length)
        {
            cout<<"Playlist is empty ....\n";
        }
        if (head->data.get_name() == value.get_name())
            delete_front();
        else
        {
            for (Node<T>* cur = head; cur; cur = cur->next)
            {
                if (cur->data.get_name() == value.get_name())
                {
                    cur = delete_and_link(cur);
                    if (!cur->next) // if we removed last node..
                        tail = cur;
                    break;
                }
            }
        }
        debug_verify_data_integrity();
    }
    void update_node_pos(size_t pos, const T& value)
    {
        assert(pos >= 1 && pos <= length);

        Node<T>* targetNode = nullptr;
        Node<T>* posNode = nullptr;

        Node<T>* current = head;
        size_t currentIndex = 1;
        while (current)
        {
            if (currentIndex == pos)
                posNode = current; // Node at the given position.

            if (current->data.get_name() == value.get_name())
                targetNode = current; // Node with matching data.

            if (posNode && targetNode) // Stop when both are found.
                break;

            current = current->next;
            ++currentIndex;
        }
        if (!posNode)
        {
            cout << "Error: Invalid position " << pos << ".\n";
            return;
        }
        if (!targetNode)
        {
            cout << "Error: Node with the given data not found.\n";
            return;
        }
        std::swap(posNode->data, targetNode->data);
        debug_verify_data_integrity();
    }
};

#endif // DLL_H
