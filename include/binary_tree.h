#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template<typename T>
struct node {
    T data;
    int key;
    node *L_Tree;
    node *R_Tree;

    node(const T& data_arg, const int key_arg, node* L_Tree_arg = nullptr, node* R_Tree_arg = nullptr)
        : data(data_arg), key(key_arg), L_Tree(L_Tree_arg), R_Tree(R_Tree_arg) {
    }

    ~node() {
        delete L_Tree;
        delete R_Tree;
    }
};

template<typename T>
class binary_tree {
    node<T>* root;

    void replace_node(node<T>*& substitute, node<T>* replaceable) {
        node<T>** current = &substitute;
        while ((*current)->R_Tree != nullptr) {
            current = &((*current)->R_Tree);
        }
        
        replaceable->key = (*current)->key;
        replaceable->data = (*current)->data;
        
        node<T>* temp = *current;
        *current = (*current)->L_Tree;
        delete temp;
    }

public:
    binary_tree() : root(nullptr) {}
    explicit binary_tree(node<T>* root_arg) : root(root_arg) {}
    explicit binary_tree(const T& data_arg, int key_arg) 
        : root(new node<T>(data_arg, key_arg)) {}

    ~binary_tree() {
        clear(root);
    }

    void clear(node<T>*& root_arg) {
        if (root_arg) {
            clear(root_arg->L_Tree);
            clear(root_arg->R_Tree);
            delete root_arg;
            root_arg = nullptr;
        }
    }

    node<T>* find(int key) const {
        node<T>* current = root;
        while (current) {
            if (key == current->key) return current;
            current = (key < current->key) ? current->L_Tree : current->R_Tree;
        }
        return nullptr;
    }

    bool insert(int key, const T& value) {
        node<T>** current = &root;
        while (*current) {
            if (key < (*current)->key) {
                current = &((*current)->L_Tree);
            }
            else if (key > (*current)->key) {
                current = &((*current)->R_Tree);
            }
            else {
                (*current)->data = value;
                return false; // Ключ уже существует
            }
        }
        *current = new node<T>(value, key);
        return true;
    }

    bool erase(int key) {
        node<T>** current = &root;
        while (*current) {
            if (key < (*current)->key) {
                current = &((*current)->L_Tree);
            }
            else if (key > (*current)->key) {
                current = &((*current)->R_Tree);
            }
            else {
                node<T>* to_delete = *current;
                if (!to_delete->L_Tree) {
                    *current = to_delete->R_Tree;
                }
                else if (!to_delete->R_Tree) {
                    *current = to_delete->L_Tree;
                }
                else {
                    replace_node(to_delete->L_Tree, to_delete);
                    return true;
                }
                delete to_delete;
                return true;
            }
        }
        return false;
    }
};
#endif // BINARY_TREE_H