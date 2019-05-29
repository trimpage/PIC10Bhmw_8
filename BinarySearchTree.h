//BinarySearchTree.h

#ifndef TREE
#define TREE

#include <stdexcept>
#include <utility> //for std::move

namespace pic10b {
	//tree class
	class Tree {
	public:
		//nested iterator class
		class iterator;

		//default constructor
		Tree() noexcept;

		//destructor
		~Tree();

		//copy constructor
		Tree(const Tree& _tree);

		//move constructor
		Tree(Tree&& _tree) noexcept;

		//assignment operator
		Tree& operator=(Tree _tree) &;

		/*
		function to insert a value to the tree
		@param input: double value to be added
		*/
		void insert(double input);

		/*
		function to erase node managed by given iterator
		@param it: iterator to remove node of
		*/
		void erase(iterator it);

		/*
		function that returns number of elements in tree
		@return: returns size of tree
		*/
		size_t size() const;

		/*
		function that returns iterator to first node
		@return: returns iterator to first node
		*/
		iterator begin() const;

		/*
		function that returns iterator one past the final node
		@return: returns iterator one past final node
		*/
		iterator end() const;

		/*
		function to find a double in the tree
		@param input: double to find
		@return: bool that is true if found or false if not found
		*/
		iterator find(const double& input) const;

		/*
		function to swap two trees
		@param firstTree, secondTree: trees to be swapped
		*/
		friend void swap(Tree& firstTree, Tree& secondTree);

	private:
		//nested node class
		class node;

		//root node of tree
		node* root;

		//size variable
		size_t treeSize;

		/*
		function to recursively delete tree
		@param _node: pointer to node to start deleting from
		*/
		void deleteTree(node* _node);

		/*
		function to help with copying, traverses tree and inserts
		@param _node: pointer to node of copy tree's root
		*/
		void traverseInsert(node* _node);
	};

	//node class
	class Tree::node {
		//declare friends
		friend Tree;
		friend iterator;

	public:
		/*
		function to see if node is left of its parent
		@return: bool of whether function is left of parent or not
		*/
		bool leftOfParent();

		/*
		function to see if node is lright of its parent
		@return: bool of whether function is right of parent or not
		*/
		bool rightOfParent();

		/*
		function to get left most node in tree
		@return: returns pointer to left most node
		*/
		node* leftMost();

		/*
		function to get right most node in tree
		@return: returns pointer to right most node
		*/
		node* rightMost();

		/*
		function to help with tree find, searches nodes to check for given value
		@param input: value to search for
		@return: returns node holding desired value
		*/
		node* search(const double& input);

	private:
		//constructor
		node(double input);

		//parent node
		node* parent;

		//child nodes
		node* left;
		node* right;

		//double data to store
		double value;

		/*
		function to insert node
		@param _node: pointer to node to insert
		*/
		bool insertNode(node* _node);
	};

	//iterator class
	class Tree::iterator {
		//declare friends
		friend Tree;

	public:
		//prefix ++ operator
		iterator &operator++();

		//postfix ++ operator
		iterator operator++(int value);

		//prefix -- operator
		iterator &operator--();

		//postfix -- operator
		iterator operator--(int value);

		//dereference operator
		double& operator*() const;

		//arrow operator
		const double* operator->() const {
			return &(current->value);
		}

		//comparison operator
		friend bool operator==(const iterator& left, const iterator& right);

	private:
		//constructor
		iterator(node* _node, const Tree* _tree);

		//node for current position
		node* current;

		//container iterator is for
		const Tree* container;
	};

	//redeclare swap function
	void swap(Tree& firstTree, Tree& secondTree);

	//equality operator
	bool operator==(const Tree::iterator& left, const Tree::iterator& right);

	//inequality operator
	bool operator!=(const Tree::iterator& left, const Tree::iterator& right);
}

#endif
