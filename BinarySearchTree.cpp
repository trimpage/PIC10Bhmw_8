//BinarySearchTree.cpp

#include "BinarySearchTree.h"

namespace pic10b {
	//FREE FUNCTION DEFINITIONS
	//swap function
	void swap(Tree& firstTree, Tree& secondTree) {
		//swap root nodes
		std::swap(firstTree.root, secondTree.root);

		//swap sizes
		std::swap(firstTree.treeSize, secondTree.treeSize);
	}

	//operator == 
	bool operator==(const Tree::iterator& left, const Tree::iterator& right) {
		//return bool of whether iterators are equal or not
		return ((left.current == right.current) && (left.container == right.container));
	}

	//operator !=
	bool operator!=(const Tree::iterator& left, const Tree::iterator& right) {
		//return opposite of ==
		return !(left == right);
	}

	//TREE CLASS DEFINITIONS
	//default constructor
	Tree::Tree() noexcept : root(nullptr), treeSize(0) {}

	//destructor
	Tree::~Tree() {
		deleteTree(root);
	}

	//copy constructor
	Tree::Tree(const Tree& _tree) : root(nullptr), treeSize(_tree.treeSize) {
		//call traverse insert to recursively copy nodes
		traverseInsert(_tree.root);
	}

	//move constructor
	Tree::Tree(Tree&& _tree) noexcept : Tree() {
		swap(*this, _tree);
	}

	//assignment operator
	Tree& Tree::operator=(Tree _tree) & {
		swap(*this, _tree);
		return *this;
	}

	//insert function
	void Tree::insert(double input) {
		//if root is empty
		if (!root) {
			//create new node for root
			root = new node(std::move(input));
			++treeSize;
		}
		//else already has root
		else {
			//create new node
			node* n = new node(std::move(input));

			//recursively pass it until in place
			if (root->insertNode(n)) {
				++treeSize;
			}
			else {
				return;
			}
		}
	}

	//erase function
	void Tree::erase(iterator it) {
		//if iterator is null
		if (it.current == nullptr) {
			//do nothing
			return;
		}
		
		//if node is root
		if (it.current == root) {
			//if root has left child
			if (root->left) {
				//create temp node
				node* temp = root->left;

				//while right of temp is not nullptr
				while (temp->right) {
					temp = temp->right;
				}

				//now set root to temp and reduce size
				root = temp;
				--treeSize;
			}
			//else root has no left child
			else {
				//so set root equal to right of root
				node* temp = root->right;
				delete root;
				root = temp;
				--treeSize;
			}
		}
		//if node is leaf node
		if ((it.current->left == nullptr) && (it.current->right == nullptr)) {
			//if node is left of parent
			if (it.current->parent->left == it.current) {
				//set left of parent to nullptr
				it.current->parent->left = nullptr;
			}
			//else is right of parent
			else {
				//set right of parent to nullptr
				it.current->parent->right = nullptr;
			}

			//then delete current and return
			delete it.current;
			it.current = nullptr;
			return;
		}
		//else if node has 1 child
		else if (((it.current->left == nullptr) && (it.current->right != nullptr)) || ((it.current->left != nullptr) && (it.current->right == nullptr))) {
			//if has right child 
			if ((it.current->left == nullptr) && (it.current->right != nullptr)) {
				//if current is left of parent
				if (it.current->parent->left == it.current) {
					//then parent left tree becomes current right tree
					it.current->parent->left = it.current->right;

					//set parent of current right to parent of current
					it.current->right->parent = it.current->parent;

					//delete current
					delete it.current;

					//set nullptr
					it.current = nullptr;

					//reduce size and return
					--treeSize;
					return;
				}
				//else current is right of parent
				else {
					//parent right tree becomes current right tree
					it.current->parent->right = it.current->right;

					//set parent of current right to parent of current
					it.current->right->parent = it.current->parent;

					//delete current
					delete it.current;

					//set nullptr
					it.current = nullptr;

					//reduce size and return
					--treeSize;
					return;
				}
			}
			//else has left child
			else {
				//if current if left of parent
				if (it.current->parent->left == it.current) {
					//parent left tree becomes current left tree
					it.current->parent->left = it.current->left;

					//set parent of current left to parent of current
					it.current->left->parent = it.current->parent;

					//delete current
					delete it.current;

					//set nullptr
					it.current = nullptr;

					//reduce size and return
					--treeSize;
					return;
				}
				//else current is right of parent
				else {
					//parent right tree becomes current left tree
					it.current->parent->right = it.current->left;

					//set parent of current left to parent of current
					it.current->left->parent = it.current->parent;

					//delete current
					delete it.current;

					//set nullptr
					it.current = nullptr;

					//reduce size and return
					--treeSize;
					return;
				}
			}
			return;
		}
		//else if current has 2 children
		else if ((it.current->left != nullptr) && (it.current->right != nullptr)) {
			//create node to check
			node* check = it.current->right;

			//if check children are nullptr
			if ((check->left == nullptr) && (check->right == nullptr)) {
				//set parent of check to parent of current
				check->parent = it.current->parent;

				//set current to check
				it.current = check;

				//delete check
				delete check;

				//set nullptr
				it.current->right = nullptr;

				//reduce size and return
				--treeSize;
				return;
			}
			//else right child has children
			else {
				//if right child has left child
				if (it.current->right->left != nullptr) {
					//create node pointers
					node* left = it.current->right->left;
					node* leftParent = it.current->right;

					//while left of left is not null
					while (left->left != nullptr) {
						//set parent to left
						leftParent = left;

						//set left to left of left
						left = left->left;
					}

					//then, set current value to left value
					it.current->value = left->value;

					//delete left
					delete left;

					//set nullptr
					leftParent->left = nullptr;

					//reduce size and return
					--treeSize;
					return;
				}
				//else right child has no left child
				else {
					//create temp node pointer
					node* temp = it.current->right;
					
					//set current value to temp value
					it.current->value = temp->value;

					//set right node to temp right node
					it.current->right = temp->right;

					//delete temp
					delete temp;

					//reduce size and return
					--treeSize;
					return;
				}
			}
			return;
		}
	}

	//size function
	size_t Tree::size() const {
		return treeSize;
	}

	//begin function
	Tree::iterator Tree::begin() const {
		//if root is empty
		if (root == nullptr) {
			//return null iterator
			return iterator(nullptr, this);
		}
		//else root is not empty
		else {
			//start at root
			node* n = root;

			//while can still go left to a lower value
			while (n->left != nullptr) {
				//go left
				n = n->left;
			}

			//return iterator of smallest node
			return iterator(n, this);
		}
	}

	//end function
	Tree::iterator Tree::end() const {
		//end iterator must be past the end so is always nullptr
		return iterator(nullptr, this);
	}

	//find function
	Tree::iterator Tree::find(const double& input) const {
// 		create iterator to root
// 				iterator it = iterator(root, this);
// 		
// 				//while iterator does not point to nullptr
// 				while (it.current) {
// 					//if current value is greater than desired value 
// 					if (it.current->value > input) {
// 						//move left
// 		
// 					}
// 				}
		//if root is nullptr, then tree is empty
		if (!root) {
			return iterator(nullptr, this);
		}
		//else tree not empty;
		else {
			return iterator((root->search(input)), this);
		}
	}

	//delete tree function
	void Tree::deleteTree(node* _node) {
		//if node is null, then return
		if (_node == nullptr) {
			return;
		}
		//else not null
		else {
			//delete both subtrees
			deleteTree(_node->right);
			deleteTree(_node->left);

			//then delete node
			delete _node;
		}
	}

	//traverse insert function
	void Tree::traverseInsert(node* _node) {
		//if not nullptr
		if (_node) {
			//insert node value
			insert(_node->value);

			//if left not null
			if (_node->left) {
				//recursively insert
				traverseInsert(_node->left);
			}

			//if right not null
			if (_node->right) {
				//recursively insert
				traverseInsert(_node->right);
			}
		}
		//else do nothing
		else {
			return;
		}
	}

	//NODE CLASS DEFINITIONS
	//constructor
	Tree::node::node(double input) : parent(nullptr), left(nullptr), right(nullptr), value(input) {}

	//left of parent function
	bool Tree::node::leftOfParent() {
		//if not a root
		if (parent) {
			//if left of parent
			if (parent->left == this) {
				return true;
			}
			//else right of parent
			else {
				return false;
			}
		}
		//else root
		else {
			return false;
		}
	}

	//right of parent function
	bool Tree::node::rightOfParent() {
		//if not a root
		if (parent) {
			//if right of parent
			if (parent->right == this) {
				return true;
			}
			//else left of parent
			else {
				return false;
			}
		}
		//else root
		else {
			return false;
		}
	}

	//left most function
	Tree::node* Tree::node::leftMost() {
		//if has no left child
		if (!left) {
			return this;
		}
		//else has left child
		else {
			//recursive call
			return left->leftMost();
		}
	}

	//right most function
	Tree::node* Tree::node::rightMost() {
		//if has no right child
		if (!right) {
			return this;
		}
		//else has right child
		else {
			//recursive call
			return right->rightMost();
		}
	}

	//search function
	Tree::node* Tree::node::search(const double& input) {
		//if current value is input
		if (input == this->value) {
			return this;
		}
		//else if input is less than value
		else if (input < value) {
			//if no left, then input can't be in tree
			if (left == nullptr) {
				return nullptr;
			}
			//else search left
			else {
				return left->search(input);
			}
		}
		//else if input greater than value
		else if (input > value) {
			//if no right, value can't be in tree
			if (right == nullptr) {
				return nullptr;
			}
			//else search right
			else {
				return right->search(input);
			}
		}
	}

	bool Tree::node::insertNode(node* _node) {
		//if value less than new node, should go right
		if (value < _node->value) {
			//if node has right child
			if (right) {
				right->insertNode(_node);
			}
			//else right child is null
			else {
				right = _node;
				_node->parent = this;
				return true;
			}
		}
		//else if this value larger than new node value
		else if (value > _node->value) {
			//if node has left child
			if (left) {
				left->insertNode(_node);
			}
			//else left child is null
			else {
				left = _node;
				_node->parent = this;
				return true;
			}
		}
		//else node has equal value and can be deleted
		else {
			//free memory
			delete _node;
			return false;
		}
	}

	//ITERATOR CLASS DEFINITIONS
	//constructor
	Tree::iterator::iterator(node* _node, const Tree* _tree) : current(_node), container(_tree) {}

	//prefix ++ operator 
	Tree::iterator& Tree::iterator::operator++() {
		//if iterator at nullptr, we are incrementing from end
		if (current == nullptr) {
			//throw error since can't increase from past the end
			throw std::logic_error("Error! Can't increase from end!");
		}
		//else if last node
		else if (current == container->root->rightMost()) {
			//set to past the end
			current = nullptr;
			return *this;
		}
		//else in valid range, and not the largest
		else {
			//if has right child
			if (current->right) {
				//go leftmost from right child
				current = current->right->leftMost();
				return *this;
			}
			//else no right child
			else {
				//create new pointer to same node
				node* n = current;

				//while n is right child of parent
				while (n->rightOfParent()) {
					n = n->parent;
				}

				//set current to parent of n since parent value larger than current
				current = n->parent;
				return *this;
			}
		}
	}

	//postfix ++ operator
	Tree::iterator Tree::iterator::operator++(int value) {
		//copy iterator
		iterator copy = *this;

		//increment
		++copy;

		return copy;
	}

	//prefix -- operator
	Tree::iterator& Tree::iterator::operator--() {
		//if iterator is at nullptr, we are decrementing from end, so need greatest value in tree
		if (current == nullptr) {
			//set current to root
			current = container->root;

			//if current still null, must be empty
			if (current == nullptr) {
				//so throw error
				throw std::logic_error("Error! Tree is empty!");
			}

			//while right is not nullptr
			while (current->right != nullptr) {
				//set current to right
				current = current->right;
			}
		}
		//else if current is smallest node
		else if (current == container->begin().current) {
			//throw error since can't decrement from beginning
			throw std::logic_error("Error! Can't decrement from beginning!");
		}
		//else if left is not nullptr
		else if (current->left != nullptr) {
			//decrement -- would be farthest right of left node
			current = current->left;

			//while right is not nullptr
			while (current->right != nullptr) {
				//set current to right
				current = current->right;
			}
		}
		//else have gone through right subtree, and is no left subtree
		else {
			//create pointer for parent node
			node* _parent = current->parent;

			//while parent is not nullptr and current is left of parent
			while (_parent != nullptr && current == _parent->left) {
				//set current to parent, move parent up
				current = _parent;
				_parent = _parent->parent;
			}

			//if we were at right most node, current = null, so set equal to parent
			current = _parent;
		}
		return *this;
	}

	//postfix -- operator 
	Tree::iterator Tree::iterator::operator--(int value) {
		//copy iterator
		iterator copy = *this;

		//decrement copy
		--copy;

		return copy;
	}

	//dereference operator
	double& Tree::iterator::operator*() const {
		//return reference to stored double
		return current->value;
	}
}




