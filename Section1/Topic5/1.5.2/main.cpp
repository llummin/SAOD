// ������ 1, ���� 5, ����� 2 - �������� ���������������� �������� ������ (����������� �������)

#include <iostream>
#include <random>

struct TreeNode {
    int data; // �������� �������
    TreeNode *left; // ��������� �� ����� �������
    TreeNode *right; // ��������� �� ������ �������
};

int numberOfNodes; // ���������� ������ � ������

// ���� �������������� �������� � ��������� ���������
int failure(int begin, int end) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\n������� ������ ���������: ";
            continue;
        }
        std::cin.ignore(32767, '\n');
        if (choice < begin || choice > end) {
            std::cout << "\n������� ������ ���������: ";
            continue;
        }
        break;
    }
    return choice;
}

// ������� �������� ����� �������
void newNode(TreeNode *&root, int n) {
    if (n == 0) { // ���� ���������� ������ ����� ����
        root = nullptr; // ��������� ������ ������
    } else {
        int left_n = n / 2; // ���������� ������ � ����� ���������
        int right_n = n - left_n - 1; // ���������� ������ � ������ ���������
        root = new TreeNode; // ��������� ������ ��� ����� �������
        std::random_device rd; // �������� ���������� ��������� �����
        std::mt19937 gen(rd()); // ������������� ����������
        std::uniform_int_distribution<> dis(0, 99); // ������� ��������� ��������� �����
        root->data = dis(gen); // ���������� ����� ������� ��������� ������
        newNode(root->left, left_n); // ����������� ����� ������� ��� �������� ����� �������
        newNode(root->right, right_n); // ����������� ����� ������� ��� �������� ������ �������
    }
}

// ������� ������ ������ � ������ �������
void preOrderTraversal(TreeNode *root, int level) { // root - ��������� �� ������ ������, level - ������� �������
    if (root == nullptr) {
        return;
    }
    // ������� �������� ������� �� �����, �������� ������ � ����������� �� �� ������
    std::cout << std::string(level * 5, ' ') << root->data << std::endl;
    preOrderTraversal(root->left, level + 1); // ���������� �������� ������� ��� ������ ���������
    preOrderTraversal(root->right, level + 1); // ���������� �������� ������� ��� ������� ���������
}

// ������� ������ ������ � ������������ �������
void inOrderTraversal(TreeNode *root, int level) {
    if (root != nullptr) {
        inOrderTraversal(root->left, level + 1); // ����������� ����� ��� ������ ���������

        // ����� �������� ���������������� ������ �������
        for (int i = 0; i < level * 5; i++) { // ���� ��� ������ �������� ����� ��������� �������
            std::cout << " ";
        }

        std::cout << root->data << std::endl; // ����� �������� ������� �������
        inOrderTraversal(root->right, level + 1); // ����������� ����� ��� ������� ���������
    }
}

// ������� ������ ������ � �������-������������ �������
void postOrderTraversal(TreeNode *root, int level) {
    if (root != nullptr) {
        postOrderTraversal(root->right, level + 1); // ���������� �������� ������� ��� ������ �����

        // ����� �������� ���������������� ������ �������
        for (int i = 0; i < level * 5; i++) { // ���� ��� ������ �������� ����� ��������� �������
            std::cout << " ";
        }

        std::cout << root->data << std::endl; // ������� �������� �������� �������
        postOrderTraversal(root->left, level + 1); // ���������� �������� ������� ��� ����� �����
    }
}

// �������� ����
void callMenu(TreeNode *&treeRoot) {
    bool work{true};
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\n�������� ������:\n";
        std::cout << "1. ���������� �������� ����������������� ��������� ������\n";
        std::cout << "2. ����� ������ � ������ �������\n";
        std::cout << "3. ����� ������ � ������������ �������\n";
        std::cout << "4. ����� ������ � �������-������������ �������\n";
        std::cout << "5. ���������� ������\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "������� ����� �������: ";
        int choice = failure(1, 5);
        switch (choice) {
            case 1:
                std::cout << "\n������� ���������� ������ ������ (� ������ ����� �� 1 �� 100): ";
                numberOfNodes = failure(1, 100);
                newNode(treeRoot, numberOfNodes);
                std::cout << std::endl;
                break;
            case 2:
                std::cout << "\n����� ������ � ������ �������:\n";
                preOrderTraversal(treeRoot, 0);
                break;
            case 3:
                std::cout << "\n����� ������ � ������������ �������:\n";
                inOrderTraversal(treeRoot, 0);
                break;
            case 4:
                std::cout << "\n����� ������ � �������-������������ �������:\n";
                postOrderTraversal(treeRoot, 0);
                break;
            case 5:
                work = false;
                std::cout << "\n��������� ���������\n";
                break;
            default:
                break;
        }
    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    auto *treeRoot = new TreeNode;
    callMenu(treeRoot);
}
