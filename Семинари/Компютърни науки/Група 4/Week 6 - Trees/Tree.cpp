#include <iostream>
#include <vector>
#include <queue>

class TreeNode
{
    private:

        int element;
        std::vector<TreeNode*> children;
        TreeNode* parent;
    
    public:
        TreeNode(int element, std::vector<TreeNode*> children, TreeNode* parent)
        {
            this->element = element;
            this->children = children;
            this->parent = parent;
        }
        void setParent(TreeNode* parent)
        {
            this->parent = parent;
        }
        std::vector<TreeNode*> getChildren()
        {
            return children;
        }
        int getElement()
        {
            return element;
        }

};
void dfs(TreeNode* node)
{
    std::cout << node->getElement() << " ";
    for(TreeNode* child : node->getChildren())
    {
        dfs(child);
    }
}
void bfs(TreeNode* node)
{
    std::queue<TreeNode*> qu;
    qu.push(node);
    while(!qu.empty())
    {
        TreeNode* node = qu.front();
        std::cout << node->getElement() << " ";
        qu.pop();
        for(TreeNode* child : node->getChildren())
        {
            qu.push(child);
        }
    }
    std::cout << std::endl;
}
int main()
{
       TreeNode* nodes[10];
       nodes[6] = new TreeNode(7, {}, nullptr);
       nodes[5] = new TreeNode(6, {nodes[6]}, nullptr);
       nodes[4] = new TreeNode(5, {}, nullptr);
       nodes[1] = new TreeNode(2, {nodes[4], nodes[5]}, nullptr);
       nodes[2] = new TreeNode(3, {}, nullptr);
       nodes[7] = new TreeNode(8, {}, nullptr);
       nodes[8] = new TreeNode(9, {}, nullptr);
       nodes[9] = new TreeNode(10, {}, nullptr);
       nodes[3] = new TreeNode(4, {nodes[7], nodes[8], nodes[9]}, nullptr);
       nodes[0] = new TreeNode(1, {nodes[1], nodes[2], nodes[3]}, nullptr);
       nodes[1]->setParent(nodes[0]);
       nodes[2]->setParent(nodes[0]);
       nodes[3]->setParent(nodes[0]);
       nodes[4]->setParent(nodes[1]);
       nodes[5]->setParent(nodes[1]);
       nodes[6]->setParent(nodes[5]);
       nodes[7]->setParent(nodes[3]);
       nodes[8]->setParent(nodes[3]);
       nodes[9]->setParent(nodes[3]);
       bfs(nodes[0]);
}