#include <iostream>
#include <string>

using namespace std;

enum Color { RED, BLACK };

class RBNode 
{
  public:
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int value) 
    {
      data = value;
      color = RED;
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
};

class RedBlackTree 
{
private:
  RBNode* root;
  RBNode* NIL;

  void printTree(RBNode* current, const string& prefix = "", bool isLeft = true) 
  {
    if (current == NIL) return;

    if (current->right != NIL)
      printTree(current->right, prefix + (isLeft ? "│   " : "    "), false);

    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << current->data << (current->color == RED ? " (R)" : " (B)") << endl;

    if (current->left != NIL)
      printTree(current->left, prefix + (isLeft ? "    " : "│   "), true);
  }

  void rotateRight(RBNode* x) 
  {
    RBNode* y = x->left;
    x->left = y->right;

    if (y->right != NIL)
      y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;

    y->right = x;
    x->parent = y;
  }

  void rotateLeft(RBNode* x) 
  {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != NIL)
      y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void fixColor(RBNode* k) 
  {
    RBNode* u;

    while (k->parent != nullptr && k->parent->color == RED) 
    {
      if (k->parent == k->parent->parent->left) 
      {
        u = k->parent->parent->right;

        if (u != NIL && u->color == RED) 
        {
          k->parent->color = BLACK;
          u->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) 
          {
            k = k->parent;
            rotateLeft(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          rotateRight(k->parent->parent);
        }
      } 
      else 
      {
        u = k->parent->parent->left;

        if (u != NIL && u->color == RED) 
        {
          k->parent->color = BLACK;
          u->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } 
        else 
        {
          if (k == k->parent->left) 
          {
            k = k->parent;
            rotateRight(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          rotateLeft(k->parent->parent);
        }
      }

      if (k == root)
        break;
    }

    root->color = BLACK;
  }

  void insertRecusive(RBNode* current, RBNode* newNode) 
  {
    if (newNode->data < current->data) 
    {
      if (current->left == NIL) 
      {
        current->left = newNode;
        newNode->parent = current;
      }
      else 
      {
        insertRecusive(current->left, newNode);
      }
    } 
    else 
    {
      if (current->right == NIL) 
      {
        current->right = newNode;
        newNode->parent = current;
      } 
      else 
      {
        insertRecusive(current->right, newNode);
      }
    }
  }

  RBNode* search(RBNode* node, int key) 
  {
    if (node == NIL || key == node->data)
      return node;

    if (key < node->data)
      return search(node->left, key);
    else
      return search(node->right, key);
  }

  void transplant(RBNode* u, RBNode* v) 
  {
    if (u->parent == nullptr)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;

    v->parent = u->parent;
  }

  RBNode* minimum(RBNode* node) 
  {
    while (node->left != NIL)
      node = node->left;
    return node;
  }

  void fixDelete(RBNode* x) 
  {
    while (x != root && x->color == BLACK) 
    {
      if (x == x->parent->left) 
      {
        RBNode* w = x->parent->right;
        if (w->color == RED) 
        {
          w->color = BLACK;
          x->parent->color = RED;
          rotateLeft(x->parent);
          w = x->parent->right;
        }

        if (w->left->color == BLACK && w->right->color == BLACK) 
        {
          w->color = RED;
          x = x->parent;
        } else 
        {
          if (w->right->color == BLACK) 
          {
            w->left->color = BLACK;
            w->color = RED;
            rotateRight(w);
            w = x->parent->right;
          }

          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          rotateLeft(x->parent);
          x = root;
        }
      } 
      else 
      {
        RBNode* w = x->parent->left;
        if (w->color == RED) 
        {
          w->color = BLACK;
          x->parent->color = RED;
          rotateRight(x->parent);
          w = x->parent->left;
        }

        if (w->left->color == BLACK && w->right->color == BLACK) 
        {
          w->color = RED;
          x = x->parent;
        } 
        else 
        {
          if (w->left->color == BLACK) 
          {
            w->right->color = BLACK;
            w->color = RED;
            rotateLeft(w);
            w = x->parent->left;
          }

          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rotateRight(x->parent);
          x = root;
        }
      }
    }

    x->color = BLACK;
  }

  void deleteNode(RBNode* node, int key) 
  {
    RBNode* z = NIL;
    RBNode* x, *y;

    while (node != NIL) 
    {
      if (node->data == key)
        z = node;

      if (key < node->data)
        node = node->left;
      else
        node = node->right;
    }

    if (z == NIL) 
    {
      cout << "Valor não encontrado na árvore." << endl;
      return;
    }

    y = z;
    Color y_original_color = y->color;

    if (z->left == NIL) 
    {
      x = z->right;
      transplant(z, z->right);
    } else if (z->right == NIL) 
    {
      x = z->left;
      transplant(z, z->left);
    } else 
    {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;

      if (y->parent == z)
        x->parent = y;
      else 
      {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }

    delete z;

    if (y_original_color == BLACK)
      fixDelete(x);
  }

public:
  RedBlackTree() 
  {
    NIL = new RBNode(0);
    NIL->color = BLACK;
    root = NIL;
  }

  ~RedBlackTree() 
  {
    delete NIL;
  }

  void insert(int value) 
  {
    RBNode* Node = new RBNode(value);
    Node->left = NIL;
    Node->right = NIL;
    Node->color = RED;

    if (root == NIL) 
    {
      root = Node;
      root->color = BLACK;
      root->parent = nullptr;
      return;
    }

    insertRecusive(root, Node);
    fixColor(Node);
  }

  void remove(int value) 
  {
    deleteNode(root, value);
  }

  void print() 
  {
    if (root == NIL) 
    {
      cout << "Árvore Vazia!!" << endl;
      return;
    }
    printTree(root);
  }

  RBNode* search(int key) 
  {
    return search(root, key);
  }

  void inOrder() { inOrderHelper(root); }
  void preOrder() { preOrderHelper(root); }
  void posOrder() { posOrderHelper(root); }

  void inOrderHelper(RBNode* node) 
  {
    if (node == NIL) return;
    inOrderHelper(node->left);
    cout << node->data << " ";
    inOrderHelper(node->right);
  }

  void preOrderHelper(RBNode* node) 
  {
    if (node == NIL) return;
    cout << node->data << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }

  void posOrderHelper(RBNode* node) 
  {
    if (node == NIL) return;
    posOrderHelper(node->left);
    posOrderHelper(node->right);
    cout << node->data << " ";
  }

  int getMin() 
  {
    if (root == NIL)
      return -1;
    RBNode* current = root;
    while (current->left != NIL)
      current = current->left;
    return current->data;
  }

  int getMax() 
  {
    if (root == NIL)
      return -1;
    RBNode* current = root;
    while (current->right != NIL)
      current = current->right;
    return current->data;
  }

  void clear() 
  {
    clearHelper(root);
    root = NIL;
  }

  void clearHelper(RBNode* node) 
  {
    if (node == NIL) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
  }

  int countLeavesHelper(RBNode* node) 
  {
    if (node == NIL) return 0;

    if (node->left == NIL && node->right == NIL)
      return 1;

    return countLeavesHelper(node->left) + countLeavesHelper(node->right);
  }

  int countLeaves() 
  {
    return countLeavesHelper(root);
  }
};

int main() 
{
  RedBlackTree tree;

  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(18);
  tree.insert(1);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);
  tree.insert(11);
  tree.insert(13);
  tree.insert(17);
  tree.insert(20);

  cout << "Árvore Rubro Negra:" << endl;
  tree.print();

  cout << "\nÁrvore em ordem: ";
  tree.inOrder();
  cout << "\n\n";

  cout << "Árvore Pré-ordem: ";
  tree.preOrder();
  cout << "\n\n";

  cout << "Árvore Pós-ordem: ";
  tree.posOrder();
  cout << "\n\n";

  cout << "\nNúmero de folhas: " << tree.countLeaves() << endl;
  cout << "Valor mínimo: " << tree.getMin() << endl;
  cout << "Valor máximo: " << tree.getMax() << endl;

  int valor;
  cout << "\nDigite o valor que deseja remover: ";
  cin >> valor;
  tree.remove(valor);

  cout << "\nÁrvore após remoção de " << valor << ":" << endl;
  tree.print();

  return 0;
}
