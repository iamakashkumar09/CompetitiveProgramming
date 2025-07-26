// The intuition behind this is to traverse the tree using level-order traversal.
// We maintain a boolean variable 'nullseen', initially set to false.
// While visiting nodes, if we encounter a NULL node, we set 'nullseen' to true.
// After this point, if we encounter any non-NULL node, it means the tree is not complete,
// so we return false.
// Otherwise, if we complete the traversal without finding a non-NULL node after a NULL,
// we return true, indicating that the tree is complete.

 
 bool isCompleteTree(TreeNode* root) {
        if(root==NULL) return true;
        queue<TreeNode*> q;
        q.push(root);
        bool nullseen=false;
        while(!q.empty()){
            auto e=q.front();
            q.pop();
            if(e==NULL){
                nullseen=true;
            }else{
                if(nullseen) return false;
                q.push(root->left);
                q.push(root->right);
            }
        }
        return true;
    }
