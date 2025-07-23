#include <bits/stdc++.h>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;

	node(int d){
		this->data=d;
		this->left=NULL;
		this->right=NULL;
	}
};

void preorder(node* root){
	if(root==NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node* root){
	if(root==NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(node* root){
	if(root==NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelorder(node* root){
	queue<node*>q;
	q.push(root);
	q.push(NULL); // using NULL to print the node in the new Line.
	while(!q.empty()){
		auto c=q.front();
		q.pop();
		if(c==NULL){
			cout << "\n" ;
			if(!q.empty())q.push(NULL);	
		} 
		else{
			cout << c->data << " ";
			if(c->left) q.push(c->left);
			if(c->right) q.push(c->right);
		}
	}
}

node* build(node *root){
	int d; cin >> d;
	if(d==-1) return NULL;
	root= new node(d);
	cout << "Enter the data for left child of Node " << d << " : ";
	root->left=build(root->left);
	cout << "Enter the data for right child " << d << " : ";
	root->right=build(root->right);
	return root;
}

int main(){
	node* tree=NULL;
	cout<< "Enter the Root Node data: ";
	tree=build(tree);
	cout << "\n" << endl;
	cout << "levelorder :";
	levelorder(tree);
	cout << "preorder :";
	preorder(tree);
	cout << "postorder :";
	postorder(tree);
	cout << "Inorder : ";
	inorder(tree);
}
