#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class BST
{
	struct Node
	{
		pair <double, int> data;
		Node* left;
		Node* right;

		Node(pair <double, int> data) : data(data), left(nullptr), right(nullptr) {}
	};

	Node* root;

	void createBST_rec(const vector<pair<double, int>> v, int startIndex, int endIndex, Node*& root);

	void CopyFrom_rec(const Node* otherNode, Node*& root);
	void CopyFrom(const BST& other);

	void Free_rec(Node* root);
	void Free();

	bool contains_rec(pair <double, int> el, Node* currentNode, Node*& prevNode);

	void searchValues_rec(Node* root, double key, vector<int>& searchedValues);

	void inorderTraversal_rec(Node* root, vector<int>& rowsIndices);
	void outorderTraversal_rec(Node* root, vector<int>& rowsIndices);

public:
	BST(const vector<pair<double, int>> v);

	BST();
	BST(const BST& other);
	~BST();

	bool contains(pair <double, int> el);
	bool insert(pair <double, int> el);

	void searchValues(double key, vector<int>& searchedValues);

	void inorderTraversal(vector<int>& rowsIndices);
	void outorderTraversal(vector<int>& rowsIndices);
};