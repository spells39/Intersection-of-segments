#include "TTree.h"

Node* Node::getMax()
{
	if (r == nullptr)
		return this;
	return r->getMax();
}

Node* Node::getMin()
{
	if (l == nullptr)
		return this;
	return l->getMin();
}

bool Node::leaf() const
{
	return l == nullptr && r == nullptr;
}

Node* Node::getPrev() 
{
	if (leaf()) 
	{
		Node* node = this;
		if (node->par == nullptr) 
			return nullptr;
		if (node->par->r == node) 
			return node->par;
		if (node->par->l == node) 
		{
			while (node->par != nullptr && node->par->l == node)
				node = node->par;
			return node->par;
		}
	}
	else 
	{
		Node* node = this->l;
		if (node == nullptr) 
		{
			if (par == nullptr) 
				return nullptr;
			if (par->r == this) 
				return par;
			return nullptr;
		}
		return node->getMax();
	}
	throw - 1;
}

Node* Node::getNext() 
{
	if (leaf()) 
	{
		Node* node = this;
		if (node->par == nullptr) 
			return nullptr;
		if (node->par->l == node) 
			return node->par;
		if (node->par->r == node) 
		{
			while (node->par != nullptr && node->par->r == node)
				node = node->par;
			return node->par;
		}
	}
	else 
	{
		Node* node = this->r;
		if (node == nullptr) {
			if (par == nullptr) 
				return nullptr;
			if (par->l == this) 
				return par;
			return nullptr;
		}
		return node->getMin();
	}
	throw - 1;
}

Node* Tree::search(Node* node, Segment seg_, double time) 
{
	/*if (node == nullptr)
		return nullptr;
	double segKey = seg_.calcY(time);
	double nodeKey = node->seg.calcY(time);
	if (segKey == nodeKey) 
		return node;
	else if (segKey < nodeKey) 
		return search(node->l, seg_, time);
	else if (segKey > nodeKey) 
		return search(node->r, seg_, time);
	throw - 1;*/
	if (node == nullptr)
		return nullptr;
	if (time < node->seg.getBegin().x || time > node->seg.getEnd().x)
		throw std::runtime_error("Error");
	if (!(seg_ != node->seg))
		return node;
	double segKey = seg_.calcY(time);
	double nodeKey = node->seg.calcY(time);
	if (static_cast<int>(segKey * ERROR_RATE) == static_cast<int>(nodeKey * ERROR_RATE))
		segKey = nodeKey;
	if (segKey < nodeKey)
		return search(node->l, seg_, time);
	if (segKey >= nodeKey)
		return search(node->r, seg_, time);
	throw - 1;
}

void Tree::updateHeight(Node* node) 
{
	if (node->leaf()) 
		node->height = 0;
	else if (node->r != nullptr && node->l == nullptr)
		node->height = node->r->height + 1;
	else if (node->l != nullptr && node->r == nullptr)
		node->height = node->l->height + 1;
	else
		node->height = std::max(node->l->height, node->r->height) + 1;
}

void Tree::insert(Node* node, Segment seg_) 
{
	if (root == nullptr) 
	{
		root = new Node(seg_);
		//root->seg = seg_;
		updateHeight(root);
		return;
	}
	double time = seg_.getBegin().x;
	double segKey = seg_.calcY(time);
	double nodeKey = node->seg.calcY(time);
	if (time < node->seg.getBegin().x || time > node->seg.getEnd().x)
		throw -1;
	if (segKey < nodeKey)
	{
		if (node->l == nullptr)
		{
			node->l = new Node(seg_);
			node->l->par = node;
		}
		else
			insert(node->l, seg_);
	}
	else if (segKey >= nodeKey)
	{
		if (node->r == nullptr)
		{
			node->r = new Node(seg_);
			node->r->par = node;
		}
		else
			insert(node->r, seg_);
	}
	updateHeight(node);
	balance(node);
	/*Node* nodeRes = nullptr;
	if (segKey <= nodeKey) 
	{
		if (node->l == nullptr) 
		{
			node->l = new Node(seg_);
			node->l->par = node;
			nodeRes = node->l;
		}
		else
			nodeRes = insert(node->l, seg_);
	}
	else if (segKey > nodeKey)
	{
		if (node->r == nullptr)
		{
			node->r = new Node(seg_);
			node->r->par = node;
			nodeRes = node->r;
		}
		else
			nodeRes = insert(node->r, seg_);
	}
	updateHeight(node);
	balance(node);
	return nodeRes;*/
}

Node* Tree::del(Node* node, Segment seg_) 
{
	/*if (node == nullptr)
		return node;
	double t = seg_.getEnd().x;
	double segKey = seg_.calcY(t);
	double nodeKey = node->seg.calcY(t);
	if (segKey < nodeKey)
		node->l = del(node->l, seg_);
	else if (segKey > nodeKey)
		node->r = del(node->r, seg_);
	else 
	{
		if (node->l == nullptr || node->r == nullptr)
		{
			Node* temp = node->l ? node->l : node->r;
			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
			{
				node->l = temp->l;
				node->r = temp->r;
				node->seg = temp->seg;
			}
			delete temp;
		}
		else
		{
			Node* minInRight = node->r->getMin();
			node->seg = minInRight->seg;
			node->r = del(node->r, minInRight->seg);
		}
	}
	if (node != nullptr)
	{
		updateHeight(node);
		balance(node);
	}
	return node;*/
	if (node == nullptr)
		return node;
	double t = seg_.getEnd().x;
	double segKey = seg_.calcY(t);
	double nodeKey = node->seg.calcY(t);
	if (t < node->seg.getBegin().x || t > node->seg.getEnd().x)
		throw -1;
	if (static_cast<int>(segKey * ERROR_RATE) == static_cast<int>(nodeKey * ERROR_RATE))
		segKey = nodeKey;
	if (segKey < nodeKey)
		node->l = del(node->l, seg_);
	else if (segKey > nodeKey)
		node->r = del(node->r, seg_);
	else
	{
		if (node->l == nullptr || node->r == nullptr)
		{
			Node* tmp = node->l ? node->l : node->r;
			if (tmp == nullptr)
			{
				delete node;
				node = nullptr;
			}
			else
			{
				std::swap(node->seg, tmp->seg);
				node->l = tmp->l;
				node->r = tmp->r;
			}
			delete tmp;
		}
		else
		{
			Node* minInRight = node->r->getMin();
			std::swap(node->seg, minInRight->seg);
			node->r = del(node->r, minInRight->seg);
		}
	}
	if (node != nullptr)
	{
		updateHeight(node);
		balance(node);
	}
	return node;
}

Node* Tree::remove(Segment seg_)
{
	root = del(root, seg_);
	return root;
}

void Tree::swap(Node* a, Node* b)
{
	Segment aS = a->seg;
	a->seg = b->seg;
	b->seg = aS;
}

int Tree::getHeight(Node* node)
{
	return node == nullptr ? -1 : node->height;
}

int Tree::getBalance(Node* node)
{
	if (node == nullptr)
		return -1;
	int lHeight = -1, rHeight = -1;
	if (node->l != nullptr)
		lHeight = getHeight(node->l);
	if (node->r != nullptr)
		rHeight = getHeight(node->r);
	return rHeight - lHeight;
}

void Tree::balance(Node* node)
{
	int b = getBalance(node);
	if (b == -2)
	{
		if (getBalance(node->l) == 1)
			leftRot(node->l);
		rightRot(node);
	}
	else if (b == 2)
	{
		if (getBalance(node->r) == -1)
			rightRot(node->r);
		leftRot(node);
	}
}

Segment Tree::getPrev(Node* node)
{
	if (node == nullptr)
		return nonIntSeg1;
	Node* n = node->getPrev();
	if (n == nullptr)
		return nonIntSeg1;
	else
		return n->seg;
}

Segment Tree::getNext(Node* node)
{
	if (node == nullptr)
		return nonIntSeg2;
	Node* n = node->getNext();
	if (n == nullptr)
		return nonIntSeg2;
	else
		return n->seg;
}

void Tree::printTree(Node* node)
{
	if (node == nullptr)
		return;
	printTree(node->l);
	std::cout << node << std::endl;
	printTree(node->r);
	std::cout << "________________________" << std::endl;
}

void Tree::rightRot(Node* node)
{
	/*swap(node, node->l);
	Node* buff = node->r;
	node->r = node->l;
	node->l = node->r->l;
	if (node->l != nullptr)
		node->l->par = node;
	node->r->l = node->r->r;
	node->r->r = buff;
	if (node->r->r != nullptr)
		node->r->r->par = node->r;
	updateHeight(node->r);
	updateHeight(node);*/
	std::swap(node->seg, node->l->seg);
	Node* buff = node->r;
	node->r = node->l;
	node->l = node->r->l;
	if (node->l != nullptr)
		node->l->par = node;
	node->r->l = node->r->r;
	node->r->r = buff;
	if (node->r->r != nullptr)
		node->r->r->par = node->r;
	updateHeight(node->r);
	updateHeight(node);
}

void Tree::leftRot(Node* node)
{
	/*swap(node, node->r);
	Node* buff = node->l;
	node->l = node->r;
	node->r = node->l->r;
	if (node->r)
		node->r->par = node;
	node->l->r = node->l->l;
	node->l->l = buff;
	if (node->l->l)
		node->l->l->par = node->l;
	updateHeight(node->l);
	updateHeight(node);*/
	std::swap(node->seg, node->r->seg);
	Node* buff = node->l;
	node->l = node->r;
	node->r = node->l->r;
	if (node->r != nullptr)
		node->r->par = node;
	node->l->r = node->l->l;
	node->l->l = buff;
	if (node->l->l != nullptr)
		node->l->l->par = node->l;
	updateHeight(node->l);
	updateHeight(node);
}
