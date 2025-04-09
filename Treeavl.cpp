#include <iostream>
#include <algorithm> 

using namespace std;

// Classe que define um nó da Árvore Binária de Busca
class TreeNode 
{
    private:
        int data;             // Valor inteiro do nó
        TreeNode* left;       // Ponteiro para o filho esquerdo
        TreeNode* right;      // Ponteiro para o filho direito

        // Função auxiliar para encontrar o nó com menor valor na subárvore
        TreeNode* minValueNode(TreeNode* node) 
        {
            TreeNode* current = node;
            while (current && current->left != nullptr)
                current = current->left;
            return current;
        }

    public:
        // Construtor que inicializa o nó com um valor e filhos nulos
        TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

        // Destrutor para liberar recursivamente os nós filhos
        ~TreeNode() 
        {
            clear();
        }

        // Limpa os nós recursivamente
        void clear() 
        {
            if (left) 
            {
                left->clear();
                delete left;
                left = nullptr;
            }
            if (right) 
            {
                right->clear();
                delete right;
                right = nullptr;
            }
        }

        // Função para calcular o balanceamento
        int getBalance()
        {
                int leftHeight = left ? left->height() : 0;
                int rightHeight = right ? right->height() : 0;
                return(leftHeight - rightHeight);
            
        }

        // rotação direita
        TreeNode* getrotateRight()
        {
            TreeNode* x = left;
            TreeNode* T2 = x->right;

            x->right= this;
            left = T2;

            // y->height = max((height(y->left), height(y->right)) + 1);
            // x->height = max((height(x->left), height(x->right)) + 1);

            return x;
        }
    
        // //rotação esqquerda
        // TreeNode* getrotateLeft(TreeNode* x) 
        // {
        //     TreeNode* y = x->right;
        //     TreeNode* T2 = y->left;
        
        //     // Realiza a rotação
        //     y->left = x;
        //     x->right = T2;
        
        //     return y; // Retorna a nova raiz após a rotação
        // }

        // Insere 'new_data' na posição correta
        TreeNode* insert(int new_data) 
        {
            TreeNode* node; 

            if (new_data < data) 
            {
                if (node->left == nullptr)
                    left = new TreeNode(new_data);
                else
                    left->insert(new_data);
            } 
            else 
            {
                if (node->right == nullptr)
                    right = new TreeNode(new_data);
                else
                    right->insert(new_data);
                
            }

            int balance = getBalance();

            if(balance > 1 )
            {
                if(new_data < left->data)
                {
                    return getrotateRight();
                }
            }

            return this;
        }

        // Exibe a árvore de forma hierárquica
        void printTree(const string& prefix = "", bool isLeft = true) 
        {
            if (right)
                right->printTree(prefix + (isLeft ? "│   " : "    "), false);

            cout << prefix;
            cout << (isLeft ? "└── " : "┌── ");
            cout << data << endl;

            if (left)
                left->printTree(prefix + (isLeft ? "    " : "│   "), true);
        }

        // Busca um valor 'key' na árvore
        bool search(int key) 
        {
            if (data == key)
                return true;
            if (key < data && left)
                return left->search(key);
            if (key > data && right)
                return right->search(key);
            return false;
        }

        // Calcula a altura da árvore
        int height()
        {
            int leftHeight = left ? left->height() : 0;
            int rightHeight = right ? right->height() : 0;
            return 1 + max(leftHeight, rightHeight);
        }

        // Exclui um nó com o valor 'key' da árvore
        TreeNode* deleteNode(int key) 
        {
            if (key < data && left)
            {
                left = left->deleteNode(key);
            }
            else if (key > data && right)
            {
                right = right->deleteNode(key);
            }
            else if (key == data)
            {
                if (!left)
                {
                    TreeNode* temp = right;
                    right = nullptr;
                    delete this;
                    return temp;
                }
                if (!right)
                {
                    TreeNode* temp = left;
                    left = nullptr;
                    delete this;
                    return temp;
                }

                TreeNode* temp = minValueNode(right);
                data = temp->data;
                right = right->deleteNode(temp->data);
            }
        }

        // Retorna o valor mínimo
        int getMin() 
        {
            if (!left) return data;
            return left->getMin();
        }

        // Retorna o valor máximo
        int getMax() 
        {
            if (!right) return data;
            return right->getMax();
        }

        // Contagem total de nós na subárvore
        int countNodes() 
        {
            int count = 1;
            if (left)
                count += left->countNodes();
            if (right)
                count += right->countNodes();
            return count;
        }

        // Contagem de folhas (nós sem filhos)
        int countLeaves() 
        {
            if (!left && !right)
                return 1;
            int leaves = 0;
            if (left)
                leaves += left->countLeaves();
            if (right)
                leaves += right->countLeaves();
            return leaves;
        }
};

int main() 
{
    TreeNode* root = new TreeNode(50);
    root->insert(60);
    root->insert(70);
    root->insert(80);
    //root->insert(55);
    //root->insert(2);
    //root->insert(1);
    //root->insert(80);
    //root->insert(100);
    //root->insert(200);


    cout << "BST -- Aula 6\n";

    root->printTree();
    

    /*int deleteValue = 0;
    cout << "Digite um valor para deletar: ";
    cin >> deleteValue;

    root = root->deleteNode(deleteValue);
    root->printTree();*/

    cout << "Menor Valor: " << root->getMin() << endl; 
    cout << "Maior Valor: " << root->getMax() << endl;

    cout << "Quantidade total de nós: " << root->countNodes() << endl;
    cout << "Quantidade total de folhas: " << root->countLeaves() << endl;
    // cout << "Nivel de balanceameto: "<< root->getBalance(root) << endl;

    delete root; // Liberação explícita da memória
    
    return 0;
}
