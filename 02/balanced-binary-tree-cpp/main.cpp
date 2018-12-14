#include<stdio.h>

struct BinaryTreeNode {
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
};

BinaryTreeNode *CreateBinaryTreeNode(int value) {
    auto *pNode = new BinaryTreeNode();
    pNode->m_nValue = value;
    pNode->m_pLeft = nullptr;
    pNode->m_pRight = nullptr;
    return pNode;
}

void ConnectTreeNodes(BinaryTreeNode *pParent, BinaryTreeNode *pLeft, BinaryTreeNode *pRight) {
    if (pParent != nullptr) {
        pParent->m_pLeft = pLeft;
        pParent->m_pRight = pRight;
    }
}

void PrintTreeNode(BinaryTreeNode *pNode) {
    if (pNode != nullptr) {
        printf("value of this node is: %d\n", pNode->m_nValue);

        if (pNode->m_pLeft != nullptr)
            printf("value of its left child is: %d.\n", pNode->m_pLeft->m_nValue);
        else
            printf("left child is null.\n");

        if (pNode->m_pRight != nullptr)
            printf("value of its right child is: %d.\n", pNode->m_pRight->m_nValue);
        else
            printf("right child is null.\n");
    } else {
        printf("this node is null.\n");
    }
    printf("\n");
}

void PrintTree(BinaryTreeNode *pRoot) {
    PrintTreeNode(pRoot);

    if (pRoot != nullptr) {
        if (pRoot->m_pLeft != nullptr)
            PrintTree(pRoot->m_pLeft);

        if (pRoot->m_pRight != nullptr)
            PrintTree(pRoot->m_pRight);
    }
}

void DestroyTree(BinaryTreeNode *pRoot) {
    if (pRoot != nullptr) {
        BinaryTreeNode *pLeft = pRoot->m_pLeft;
        BinaryTreeNode *pRight = pRoot->m_pRight;

        delete pRoot;
        pRoot = nullptr;

        DestroyTree(pLeft);
        DestroyTree(pRight);
    }
}


//========================方法1==============================
int TreeDepth(BinaryTreeNode *pRoot) {
    if (pRoot == nullptr)
        return 0;

    int nLeft = TreeDepth(pRoot->m_pLeft);
    int nRight = TreeDepth(pRoot->m_pRight);

    return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

bool IsBalanced_Solution1(BinaryTreeNode *pRoot) {
    if (pRoot == nullptr)
        return true;

    // 先计算左右子树深度
    int left = TreeDepth(pRoot->m_pLeft);
    int right = TreeDepth(pRoot->m_pRight);
    int diff = left - right;
    // 如果超过1，即不是AVL
    if (diff > 1 || diff < -1)
        return false;

    // 递归调用
    return IsBalanced_Solution1(pRoot->m_pLeft)
           && IsBalanced_Solution1(pRoot->m_pRight);
}

//=====================方法2===========================
bool IsBalanced(BinaryTreeNode *pRoot, int *pDepth);

bool IsBalanced_Solution2(BinaryTreeNode *pRoot) {
    int depth = 0;
    return IsBalanced(pRoot, &depth);
}

bool IsBalanced(BinaryTreeNode *pRoot, int *pDepth) {
    if (pRoot == nullptr) {
        *pDepth = 0;
        return true;
    }

    int left, right;
    if (IsBalanced(pRoot->m_pLeft, &left)
        && IsBalanced(pRoot->m_pRight, &right)) {
        int diff = left - right;
        if (diff <= 1 && diff >= -1) {
            *pDepth = 1 + (left > right ? left : right);
            return true;
        }
    }

    return false;
}

// 不是完全二叉树，但是平衡二叉树
//             1
//         /      \
//        2        3
//       /\         \
//      4  5         6
//        /
//       7

int main() {
    BinaryTreeNode *pNode1 = CreateBinaryTreeNode(1);
    BinaryTreeNode *pNode2 = CreateBinaryTreeNode(2);
    BinaryTreeNode *pNode3 = CreateBinaryTreeNode(3);
    BinaryTreeNode *pNode4 = CreateBinaryTreeNode(4);
    BinaryTreeNode *pNode5 = CreateBinaryTreeNode(5);
    BinaryTreeNode *pNode6 = CreateBinaryTreeNode(6);
    BinaryTreeNode *pNode7 = CreateBinaryTreeNode(7);

    ConnectTreeNodes(pNode1, pNode2, pNode3);
    ConnectTreeNodes(pNode2, pNode4, pNode5);
    ConnectTreeNodes(pNode3, pNode6, pNode7);

    printf("Solution1 begins: ");
    if (IsBalanced_Solution1(pNode1))
        printf("is balanced.\n");
    else
        printf("not balanced.\n");

    printf("Solution2 begins: ");
    if (IsBalanced_Solution2(pNode1))
        printf("is balanced.\n");
    else
        printf("not balanced.\n");
    printf("\n");

    DestroyTree(pNode1);

    return 0;
}