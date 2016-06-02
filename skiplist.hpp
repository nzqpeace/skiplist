//
// Created by 牛志强 on 16/6/1.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <cstddef>
#include <assert.h>
#include <stdlib.h>

const double SKIPLIST_P = 0.25;
template <typename T>
class Skiplist
{
public:
    const static int MAX_LEVEL = 32;
    Skiplist();
    virtual ~Skiplist();

    struct Node{
        T value;

        struct Level{
            struct Node* forward;
        } level[];
    };

    bool Insert(T value);
    bool Delete(T value);

    size_t size()  {return length_;}
    int level() {return level_; }
    Node* first() {return header_; }

private:
    int random_level();
    Node* create_node(size_t level){
        Node* node = (Node*)malloc(sizeof(Node) + level * sizeof(struct Node::Level));
        return node;
    }

    Node* create_node(size_t level, const T& value){
        Node* node = (Node*)malloc(sizeof(Node) + level * sizeof(struct Node::Level));
        node->value = value;
        return node;
    }

private:
    size_t length_;
    int level_;
    Node*  header_;
};

template <typename T>
Skiplist<T>::Skiplist()
        : length_(0), level_(1)
{
    header_ = create_node(MAX_LEVEL);
    assert(header_ != NULL);

    for (int i = 0; i < MAX_LEVEL; ++i) {
        header_->level[i].forward = NULL;
    }
}

template <typename T>
Skiplist<T>::~Skiplist() {
    Node* next;
    Node* p = header_->level[0].forward;
    while (p){
        next = p->level[0].forward;
        free(p);
        p = next;
    }
    free(header_);
}

template <typename T>
bool Skiplist<T>::Insert(T value){
    Node* update[MAX_LEVEL];
    Node* p = header_;
    for (int i = level_ - 1; i >= 0; --i) {
        Node* next = p->level[i].forward;
        while (next && next->value < value){
            p = next;
            next = p->level[i].forward;
        }

        update[i] = p;
    }

    p = p->level[0].forward;
    if (p && p->value == value){
        p->value = value;
        return true;
    }

    // create new node
    int level = random_level();
    if (level > level_){
        for (int i = level - 1; i >= level_; --i) {
            update[i] = header_;
        }
        level_ = level;
    }
    Node* new_node = create_node(level, value);
    for (int i = 0; i < level; ++i) {
        new_node->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = new_node;
    }

    length_++;
    return true;
}

template <typename T>
bool Skiplist<T>::Delete(T value){
    Node* update[MAX_LEVEL];
    Node* p = header_;
    for (int i = level_; i >= 0; --i) {
        Node* next = p->level[i].forward;
        while (next && next->value < value){
            p = next;
            next = p->level[i].forward;
        }

        update[i] = p;
    }

    p = p->level[0].forward;

    // not exist
    if (p && p->value != value){
        return false;
    }

    // adjust point
    for (int i = 0; i < level_; ++i) {
        if (update[i]->level[i].forward != p){
            break;
        }
        update[i]->level[i].forward = p->level[i].forward;
    }

    free(p);

    // update level
    while (header_->level[level_].forward == NULL){
        level_--;
    }

    // update length
    length_--;
    return true;
}

template <typename T>
int Skiplist<T>::random_level() {
    int level = 1;
    while ((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF)){
        level++;
    }
    return (level < MAX_LEVEL) ? level : MAX_LEVEL;
}
#endif //SKIPLIST_SKIPLIST_H
