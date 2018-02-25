//
// Created by root on 18-2-25.
//

#ifndef CSYSPROJ_BINARYTREE_H
#define CSYSPROJ_BINARYTREE_H

#include <vector>
#include <stack>
#include <functional>
using namespace std;

// 树的节点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

/**
 * 树的遍历有两类：深度优先遍历和宽度优先遍历。
 * 深度优先遍历又可分为两种：  先根（次序）遍历     和         后根（次序）遍历。
 */



// LeetCode, Binary Tree Preorder inorder postorder Traversal
// 使用栈，时间复杂度 O(n)，空间复杂度 O(n)
class Solution1
{
    public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        const TreeNode *p;
        stack<const TreeNode *> s;
        p = root;

        if (p != nullptr)
            s.push(p);

        while (!s.empty())
        {
            p = s.top();
            s.pop();
            result.push_back(p->val);
            if (p->right != nullptr)
                s.push(p->right);
            if (p->left != nullptr)
                s.push(p->left);
        }
        return result;
    }


    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        const TreeNode *p = root;
        stack<const TreeNode *> s;
        while (!s.empty() || p != nullptr)
        {
            if (p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top();
                s.pop();
                result.push_back(p->val);
                p = p->right;
            }
        }
        return result;
    }



    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        const TreeNode *p, *q;/* p，正在访问的结点， q，刚刚访问过的结点 */
        stack<const TreeNode *> s;
        p = root;
        do {
            while (p != nullptr)
            { /* 往左下走 */
                s.push(p);
                p = p->left;
            }
            q = nullptr;
            while (!s.empty())
            {
                p = s.top();
                s.pop();
                if (p->right == q)/* 右孩子不存在或已被访问，访问之 */
                {
                    result.push_back(p->val);
                    q = p; /* 保存刚访问过的结点 */
                }
                else
                {
                    s.push(p);/* 当前结点不能访问，需第二次进栈 */
                    p = p->right;/* 先处理右子树 */
                    break;
                }
            }
        } while (!s.empty());
        return result;
    }


};



///////////////////////////////////////////////////////////////////////////////////////////////////////////


// LeetCode, Binary Tree Preorder inorder postorder Traversal
// Morris 遍历，时间复杂度 O(n)，空间复杂度 O(1)
class Solution2 {
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode *cur, *prev;
        cur = root;
        while (cur != nullptr)
        {
            if (cur->left == nullptr)
            {
                result.push_back(cur->val);
                prev = cur; /* cur 刚刚被访问过 */
                cur = cur->right;
            }
            else
            {
                /* 查找前驱 */
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;
                if (node->right == nullptr)
                { /* 还没线索化，则建立线索 */
                    result.push_back(cur->val); /* 仅这一行的位置与中序不同 */
                    node->right = cur;
                    prev = cur; /* cur 刚刚被访问过 */
                    cur = cur->left;
                }
                else
                {
                    node->right = nullptr;/* 已经线索化，则删除线索 */
                    cur = cur->right;/* prev = cur; 不能有这句， cur 已经被访问 */
                }
            }
        }
        return result;
    }


    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode *cur, *prev;
        cur = root;
        while (cur != nullptr)
        {
            if (cur->left == nullptr)
            {
                result.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            }
            else
            {
                TreeNode *node = cur->left;/* 查找前驱 */
                while (node->right != nullptr && node->right != cur)
                    node = node->right;
                if (node->right == nullptr)
                { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    cur = cur->left;/* prev = cur; 不能有这句， cur 还没有被访问 */
                }
                else
                { /* 已经线索化，则访问节点，并删除线索 */
                    result.push_back(cur->val);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        return result;
    }


    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        TreeNode dummy(-1);
        TreeNode *cur, *prev = nullptr;
        std::function < void(const TreeNode*)> visit =
                [&result](const TreeNode *node){
                    result.push_back(node->val);
                };
        dummy.left = root;
        cur = &dummy;
        while (cur != nullptr)
        {
            if (cur->left == nullptr)
            {
                prev = cur; /* 必须要有 */
                cur = cur->right;
            }
            else
            {
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;
                if (node->right == nullptr)
                { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    prev = cur; /* 必须要有 */
                    cur = cur->left;
                }
                else
                { /* 已经线索化，则访问节点，并删除线索 */
                    visit_reverse(cur->left, prev, visit);
                    prev->right = nullptr;
                    prev = cur; /* 必须要有 */
                    cur = cur->right;
                }
            }
        }
        return result;
    }
private:
// 逆转路径
    static void reverse(TreeNode *from, TreeNode *to)
    {
        TreeNode *x = from, *y = from->right, *z;
        if (from == to) return;
        while (x != to) {
            z = y->right;
            y->right = x;
            x = y;
            y = z;
        }
    }
// 访问逆转后的路径上的所有结点
    static void visit_reverse(TreeNode* from, TreeNode *to, std::function< void(const TreeNode*) >& visit)
    {
        TreeNode *p = to;
        reverse(from, to);
        while (true) {
            visit(p);
            if (p == from)
                break;
            p = p->right;
        }
        reverse(to, from);
    }




};



#endif //CSYSPROJ_BINARYTREE_H
