#include "BST.h"

void BST::createBST_rec(const vector<pair<double, int>> v, int startIndex, int endIndex, Node*& root)
{
	if (startIndex > endIndex)
		return;

	int posOfTempData = (startIndex + endIndex) / 2;
	pair <double, int> tempData = v[posOfTempData];

	root = new Node(tempData);
	createBST_rec(v, startIndex, posOfTempData - 1, root->left);
	createBST_rec(v, posOfTempData + 1, endIndex, root->right);
}
BST::BST(const vector<pair<double, int>> v)
{
	if (!is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";

	createBST_rec(v, 0, v.size() - 1, root);
}

BST::BST() : root(nullptr) {}

void BST::CopyFrom_rec(const Node* otherNode, Node*& root)
{
	if (!otherNode)
		return;

	root = new Node(otherNode->data);

	CopyFrom_rec(otherNode->left, root->left);
	CopyFrom_rec(otherNode->right, root->right);
}
void BST::CopyFrom(const BST& other)
{
	CopyFrom_rec(other.root, root);
}
BST::BST(const BST& other) : root(nullptr)
{
	CopyFrom(other);
}

void BST::Free_rec(Node* root)
{
	if (!root)
		return;

	Free_rec(root->left);
	Free_rec(root->right);

	delete root;
}
void BST::Free()
{
	Free_rec(root);
}
BST::~BST()
{
	Free();
}

bool BST::contains_rec(pair <double, int> el, Node* currentNode, Node*& prevNode)
{
	if (!currentNode)
		return false;
	if (currentNode->data == el)
		return true;

	prevNode = currentNode;

	if (el < currentNode->data)
		return contains_rec(el, currentNode->left, prevNode);
	return contains_rec(el, currentNode->right, prevNode);
}
bool BST::contains(pair <double, int> el)
{
	Node* temp = nullptr;
	return contains_rec(el, root, temp);
}

bool BST::insert(pair <double, int> el)
{
	if (!root)
	{
		root = new Node(el);
		return true;
	}

	Node* prev = nullptr;
	contains_rec(el, root, prev);

	if (el.first < prev->data.first)
		prev->left = new Node(el);
	else
		prev->right = new Node(el);
}

void BST::searchValues_rec(Node* root, double key, vector<int>& searchedValues)
{
	if (!root)
		return;

	if (root->data.first == key)
		searchedValues.push_back(root->data.second);

	if (key < root->data.first)
		searchValues_rec(root->left, key, searchedValues);
	else
		searchValues_rec(root->right, key, searchedValues);
}
void BST::searchValues(double key, vector<int>& searchedValues)
{
	searchValues_rec(root, key, searchedValues);
}

void BST::inorderTraversal_rec(Node* root, vector<int>& rowsIndices)
{
	if (!root)
		return;

	inorderTraversal_rec(root->left, rowsIndices);
	rowsIndices.push_back(root->data.second);
	inorderTraversal_rec(root->right, rowsIndices);
}
void BST::inorderTraversal(vector<int>& rowsIndices)
{
	inorderTraversal_rec(root, rowsIndices);
}

void BST::outorderTraversal_rec(Node* root, vector<int>& rowsIndices)
{
	if (!root)
		return;

	outorderTraversal_rec(root->right, rowsIndices);
	rowsIndices.push_back(root->data.second);
	outorderTraversal_rec(root->left, rowsIndices);
}
void BST::outorderTraversal(vector<int>& rowsIndices)
{
	outorderTraversal_rec(root, rowsIndices);
}