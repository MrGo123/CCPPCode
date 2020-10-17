#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
/*definition for a binary tree node*/
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//solution class
class Solution
{
    // 用于指定后序遍历元素的位置（即每一个子树的根节点）
    int post_idx;
    // 用于方便指定中序遍历元素
    unordered_map<int,int> idx_map;

public:
    TreeNode* helper(int inleft,int inright){

    }
    TreeNode* buildTree(vector<int>& inorder,vector<int>& postorder){
        //从后序遍历的最后一个元素开始
        post_idx = (int)postorder.size()-1;

        //从中序遍历的元素中构建键值对，每个元素映射到一个数字上
        int idx=0;
        for(auto&val : inorder){
            idx_map[val]=idx++;
        }

        return helper();
    }
};

int main()
{

    system("pause");
    return 0;
}