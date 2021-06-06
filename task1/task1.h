using namespace std;

class Node {
private:
	int data;
	Node* next;
	Node* prev;
public:
	Node(int newData) {
		prev = nullptr;
		next = nullptr;
		data = newData;
	}
	int getData() {
		return data;
	}
	void setData(int newData) {
		data = newData;
	}
	Node* getNext() {
		return next;
	}
	void setNext(Node* n) {
		next = n;
	}
	Node* getPrev() {
		return prev;
	}
	void setPrev(Node* n) {
		prev = n;
	}
};

class LinkedList {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
public:
	
	bool add(Node* data, int pos) {
		if (data == nullptr || pos < 0 || pos > size) {
			return false;
		}
		if (head == nullptr) { //first add
			tail = head = data;
		}
		else if (pos == 0) { //start
			data->setNext(head);
			head->setPrev(data);
			head = data;
		}
		else if (pos == size) { //end
			data->setPrev(tail);
			tail->setNext(data);
			tail = data;
		}
		else { //middle
			Node* n = head;
			for(int i=0; i<pos; i++) { //find node after pos
				n = n->getNext();
			}
			data->setPrev(n->getPrev());
			data->getPrev()->setNext(data);

			data->setNext(n);
			n->setPrev(data);			
		}

		size++;
		return true;
	}
	bool remove(int pos) {
		if (head == nullptr || pos < 0 || pos >= size) {
			return false;
		}
		Node* toRemove;
		if (pos == 0) { //start
			toRemove = head;
			head = head->getNext();
			toRemove->setNext(nullptr);
			if (!head) {
				tail = nullptr;
			}
			else {
				head->setPrev(nullptr);
			}
		}
		else if (pos == size-1) { //end
			toRemove = tail;
			tail = tail->getPrev();
			if (!tail) {
				head = nullptr;
			}
			else {
				tail->setNext(nullptr);
			}
		}
		else { //middle
			Node* n = head;
			for (int i = 0; i < pos; i++) { 
				n = n->getNext();
			}
			toRemove = n;
			
			Node* prev = toRemove->getPrev();
			Node* next = toRemove->getNext();

			prev->setNext(next);
			next->setPrev(prev);

			toRemove->setNext(nullptr);
			toRemove->setPrev(nullptr);
		}
		delete toRemove;
		size--;
		return true;
	}
	bool replace(Node* old, Node* newNode) {
		if (old == nullptr || newNode == nullptr || search(old) == -1) {
			return false;
		}
		Node* prev = old->getPrev();
		Node* next = old->getNext();

		if (prev) {
			old->setPrev(nullptr);
			prev->setNext(newNode);
		}
		else {
			head = newNode;
		}
		if (next) {
			old->setNext(nullptr);
			next->setPrev(newNode);
		}
		else {
			tail = newNode;
		}
		newNode->setPrev(prev);
		newNode->setNext(next);

		delete old;
		return true;
	}
	int search(Node* data) {
		Node* n = head;
		int pos = 0;
		while (n) {
			if (n == data) {
				return pos;
			}
			n = n->getNext();
			pos++;
		}
		return -1;
	}
	Node* nodeAt(int pos) {
		if (head == nullptr || pos < 0 || pos > size) {
			return nullptr;
		}
		Node* n = head;
		for (int i = 0; i < pos; i++) { 
			n = n->getNext();
		}
		return n;
	}
	void displayForward() {
		Node* n = head;
		if (n) {
			cout << n->getData() << endl;
			n = n->getNext();
			while (n) {
				cout << n->getData() << endl;
				n = n->getNext();
			}
		}
		else {
			cout << "\nEmpty list\n";
		}
	}
	void displayBackward() {
		Node* n = tail;
		if (n) {
			cout << n->getData() << endl;
			n = n->getPrev();
			while (n) {
				cout << n->getData() << endl;
				n = n->getPrev();
			}
		}
		else {
			cout << "\nEmpty list\n";
		}
	}
	int getSize() {
		return size;
	}
};