//ALGO2 IS1 221A LAB03
//Adrian Jakubczyk
//ja36272@zut.edu.pl

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>




using namespace std;
struct person
{
	  int age;
	string name;
};




template <class T>
class Node {

public:
	T data;
	Node<T>* Left = NULL;
	Node<T>* Right = NULL;
};

template <class T>
class BST {
public:
	Node<T>* root;
	int size;
	//int height = 0;
	BST() {
		root = NULL;
		size = 0;
	}

	void add(T data, int(*cmp)(T, T))
	{

		
		Node<T>* temp = new Node<T>();
		temp->data = data;

		Node<T>* tempRoot = this->root;
		Node<T>* tempNext = NULL;
		if (root == NULL)
		{

			root = temp;
			size++;
			return;
		}
		while (tempRoot != NULL) {

			tempNext = tempRoot;
			if (cmp(temp->data, tempRoot->data) < 0)
				tempRoot = tempRoot->Left;
			else
				tempRoot = tempRoot->Right;
		}

		

		if (tempNext == NULL)
		{
			tempNext = temp;

		}

		

		else if (cmp(temp->data, tempNext->data) < 0)
		{

			tempNext->Left = temp;

		}


		else if (cmp(temp->data, tempNext->data) > 0) {

			tempNext->Right = temp;
		}
		
		size++;
		return;
	}


	void toString(string(*dataToString)(T obj), int hits)
	{


		reverseLevelOrder(root, dataToString);
		int height = getHeightForPrint(root);
		cout << "wysokosc drzewa wynosi: " << height + 1 << endl;
		cout << "drzewo ma: " << size - hits << " elementow" << "\n\n\n\n" << endl;


	}


	void reverseLevelOrder(Node<T>* root, string(*dataToString)(T obj))
	{
		int h = 4;
		int i;
		for (i = 1; i <= h; i++)
			printGivenLevel(root, i, dataToString);
	}

	/* Print nodes at a given level */
	void printGivenLevel(Node<T>* root, int level, string(*dataToString)(T obj))
	{
		int count = 0;

		if (root == NULL)
			return;
		if (level == 1) {
			count++;
			if (root != this->root) {
				if (root->Left != NULL && root->Right != NULL) {
					cout << "[index: " << root->data->age << " Parent's index: ";
					findParent(this->root, root->data->age, -1);
					cout << " Left Child's index: " << root->Left->data->age << " Right's Child index: " << root->Right->data->age << "data name: " << root->data->name << " ]" << endl;
				}
				else if (root->Left != NULL && root->Right == NULL) {
					cout << "[index: " << root->data->age << " Parent's index ";
					findParent(this->root, root->data->age, -1);
					cout << " Left Child's index: " << root->Left->data->age << " Right's Child index: None" << "data name: " << root->data->name << " ]" << endl;
				}

				else if (root->Left == NULL && root->Right != NULL) {
					cout << "[index: " << root->data->age << " Parent's index ";
					findParent(this->root, root->data->age, -1);
					cout << " Left Child's index: None" << " Right's Child index: " << root->Right->data->age << "data name: " << root->data->name << " ]" << endl;
				}
				else if (root->Left == NULL && root->Right == NULL)
				{
					cout << "[index: " << root->data->age << " Parent's index";
					findParent(this->root, root->data->age, -1);
					cout << " Left Child's index: None" << " Right's Child index:None " << "data name: " << root->data->name << " ]" << endl;
				}
			}
			else if (level < 5)
			{
				if (root->Left != NULL && root->Right != NULL)
					cout << "[index: " << root->data->age << " Parent's index: none" << " Left Child's index: " << root->Left->data->age << " Right's Child index: " << root->Right->data->age << "data name: " << root->data->name << " ]" << endl;

				else if (root->Left != NULL && root->Right == NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: " << root->Left->data->age << " Right's Child index: None" << "data name: " << root->data->name << " ]" << endl;

				else if (root->Left == NULL && root->Right != NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: None" << " Right's Child index: " << root->Right->data->age << "data name: " << root->data->name << " ]" << endl;
				else if (root->Left == NULL && root->Right == NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: None" << " Right's Child index:None " << "data name: " << root->data->name << " ]" << endl;
			}


		}

		else if (level < 5)
		{
			count++;
			printGivenLevel(root->Left, level - 1, dataToString);
			printGivenLevel(root->Right, level - 1, dataToString);
		}


	}
	void findParent(Node<T>* node, int val, int parent)
	{
		if (node == NULL)
			return;

		if (node->data->age == val) {
			cout << parent;
		}
		else{

			findParent(node->Left, val, node->data->age);
			findParent(node->Right, val, node->data->age);
		}
	}

	Node<T>* findParentForDelete(Node<T>* node, Node<T>*& nodeToFind, int (*cmp)(T, T))
	{
		
		if (node == NULL)
			return NULL;

		if (node->Left == NULL && node->Right == NULL)
			return NULL;

		if ((node->Left != NULL && node->Left == nodeToFind)
			|| (node->Right != NULL && node->Right == nodeToFind))
			return node;
		
		if (cmp(node->data,nodeToFind->data) >= 0)
			return findParentForDelete(node->Left, nodeToFind,cmp);
		//else
		if (cmp(node->data, nodeToFind->data) <= 0)
			return findParentForDelete(node->Right, nodeToFind,cmp);

	
		
	}


	/* Compute the "height" of a tree -- the number of
		nodes along the longest path from the root node
		down to the farthest leaf node.*/




	int getHeight(Node<T>* node)
	{
		if (node == NULL)
			return 0;
		else
		{

			int lheight = getHeight(node->Left);
			int rheight = getHeight(node->Right);


			if (lheight > rheight)
				return(lheight + 1);
			else return(rheight + 1);
		}
	}

	int getHeightForPrint(Node<T>* node)
	{
		if (node == NULL)
			return 0;
		else
		{

			int lheight = getHeight(node->Left);
			int rheight = getHeight(node->Right);


			if (lheight > rheight)
				return(lheight - 1);
			else return(rheight - 1);
		}
	}

	Node<T>* searchForElement(Node<T>* root, T key, bool(*cmp1)(T, T), int(*cmp)(T, T))
	{
		while (!cmp1(root->data, key)) {

			if (root != NULL) {


				//go to left tree
				if (root->data->age > key->age) {
					root = root->Left;
				}  //else go to right tree
				else {
					root = root->Right;
				}

				//not found
				if (root == NULL) {
					return NULL;
				}
			}
		}
		return root;
	}


	Node<T>* findMin(Node<T>* node)
	{
		while (node->Left != NULL)
			node = node->Left;
		return node;
	}

	void Delete(Node<T>*& node,int(*cmp)(T,T)) {

		if (node == NULL)
			return;

		Node<T>* parent = findParentForDelete(this->root, node,cmp);
		
		Node<T>* temp = NULL;


		//leafs
		if (node->Left == NULL && node->Right == NULL) {
			if (node == root) {
				delete root;
				root = NULL;
				return;
			}
			else {
				if(parent!=NULL)
				if (parent->Left == node)
					parent->Left = NULL;
				else
					parent->Right = NULL;
				delete node;
				node = NULL;
				return;
			}
		}
		//1 child left not null
		else if (node->Left != NULL && node->Right == NULL)
		{
			if (node == root) {
				temp = root->Left;

				delete root;
				root = NULL;

				root = temp;
				return;

			}
			else {
				if (parent != NULL)
				if (parent->Left == node)
					parent->Left = node->Left;
				else
					parent->Right = node->Left;

				delete node;
				node = NULL;
				return;

			}
		}
		//1 child Right not null
		else if (node->Left == NULL && node->Right != NULL)
		{
			if (node == root) {
				temp = root->Right;

				delete root;
				root = NULL;

				root = temp;
				return;
			}
			else {
				if (parent != NULL)
				if (parent->Left == node)
					parent->Left = node->Right;
				else
					parent->Right = node->Right;

				delete node;
				node = NULL;
				return;
			}
		}
		//2 childs
		else if (node->Left != NULL && node->Right != NULL)
		{
			temp = findMin(node->Right);
			T data = temp->data;
			Delete(temp,cmp);
			node->data = data;
			
		}
	}
	



		
		
	
	void printpreorder(Node<T>* node)
	{
		if (node == NULL)
			return;

		if (node == this->root)
			cout << "root: ";
		cout << node->data->age<<" | ";
		/* first recur on left child */
		printpreorder(node->Left);

		/* then print the data of node */
		

		/* now recur on right child */
		printpreorder(node->Right);
	}

	void printInorder(Node<T>* node)
	{
		if (node == NULL)
			return;

		/* first recur on left child */
		printInorder(node->Left);

		/* then print the data of node */
		if (node == this->root)
			cout << "root: ";
		cout << node->key << " | ";

		/* now recur on right child */
		printInorder(node->Right);
	}

	void clear(Node<T>* root)
	{
		if (root != NULL) {
			clear(root->Left);
			clear(root->Right); 
			delete root->data;
			root->data = NULL;
			delete root;
			root = NULL; // <<<<<<<<<<<<<<<<
		}
		this->root = NULL;
			size = 0;
	}
	~BST()
	{
		clear(root);
	}

};

bool object1SearchCmp(person*o1, person*o2)
{
	if (o1->age==o2->age) {
		
		
		return true;
	}
	return false;
}

int object1Comparator(person *o1, person *o2)
{

	
	int wynik = o1->age - o2->age;
	//if (!wynik == 0)
		return wynik;
	/*else {
		if (o1->name > o2->name)
			return -1;
		else if (o1->name < o2->name)
			return 1;
	}*/
}


string personToString(person *obj)
{
	string result = "data:\n index: ";
	result.append(to_string(obj->age));
	result.append(" , name: ");
	result.append(obj->name);
	return result;
}


string Names[22] = {
			" Adrian ", " Bolek ", " lolek ", " Borat ", " James ", " Jas ", "Jaroslaw ",
			" Waldemar ", " Wladyslaw ", " Zbigniew ", "Zdzislaw "
		," Jakub ", " Mateusz ", " Michal ", " Justynian ", " Zeus ", " Magda ", " Justyna ",
		" Krzysztof ", " Milosz ", " Marcin ", " Matt "
};

int main2()
{
	BST<person*>* bst = new BST<person*>(); // stworzenie
	person* so = new person;
	so->age = 10;

	so->name = Names[rand() % (20 - 0) + 0];
	person* so1 = new person;
	so1->age = 15;

	so1->name = Names[rand() % (20 - 0) + 0];
	person* so2 = new person;
	so2->age = 12;

	so2->name = Names[rand() % (20 - 0) + 0];
	person* so3 = new person;
	so3->age = 5;

	so3->name = Names[rand() % (20 - 0) + 0];
	person* so4 = new person;
	so4->age = 30;

	so4->name = Names[rand() % (20 - 0) + 0];
	person* so5 = new person;
	so5->age = 25;

	so5->name = Names[rand() % (20 - 0) + 0];
	person* so6 = new person;
	so6->age = 35;

	so6->name = Names[rand() % (20 - 0) + 0];
	person* so7 = new person;
	so7->age = 7;

	person* so8 = new person;
	so8->age = -2;

	so8->name = Names[rand() % (20 - 0) + 0];

	so7->name = Names[rand() % (20 - 0) + 0];

	person* so9 = new person;
	so9->age = 33;

	so9->name = Names[rand() % (20 - 0) + 0];

	bst->add(so, object1Comparator);
	bst->add(so1, object1Comparator);
	bst->add(so2, object1Comparator);
	bst->add(so3, object1Comparator);
	bst->add(so4, object1Comparator);
	bst->add(so5, object1Comparator);
	bst->add(so6, object1Comparator);
	bst->add(so7, object1Comparator);
	bst->add(so8, object1Comparator);
	bst->add(so9, object1Comparator);

	bst->toString(personToString, 0);
	Node<person*>* temp = NULL;
	temp=bst->searchForElement(bst->root, so4, object1SearchCmp, object1Comparator);
	
	bst->Delete(temp, object1Comparator);
	bst->toString(personToString, 0);

	temp = bst->searchForElement(bst->root, so7, object1SearchCmp, object1Comparator);
	bst->Delete(temp, object1Comparator);
	bst->toString(personToString, 0);
	temp = bst->searchForElement(bst->root, so3, object1SearchCmp, object1Comparator);
	bst->Delete(temp, object1Comparator);
	bst->toString(personToString, 0);
	
	getchar();
	return 0;
}

int main()
{
	
	//srand(time(NULL));

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> distribution(1, 15000000);
	uniform_real_distribution<> distribution2(1, 10000000);
	//generating a random integer:
	double random = distribution(gen);
	unsigned int prev = 0;
	const int MAX_ORDER = 6; // maksymalny rzad wielkosci dodawanych danych
	BST<person*>* bst = new BST<person*>(); // stworzenie
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do drzewa
		unsigned int hits = 0;
		clock_t t1 = clock();
		for (int i = 0; i < n; i++)

		{
			
				
				person* so = new person;
				
				so->age = distribution(gen);
				
				if (i == 0)
					so->age = 150000000 / 2;
				
				so->name = Names[rand() % (20 - 0) + 0];

				bst->add(so, object1Comparator); // dodanie ( drugi argument to wskaznik na komparator )
			
		}
		
		clock_t t2 = clock();
		// wypis na ekran aktualnej postaci drzewa ( skrotowej ) wraz z pomiarami czasowymi i w / w
		bst->toString(personToString, hits);
		double diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar diff1 : " << diff << "\n\n";


		// wyszukiwanie
		const int m = pow(10, 4); // liczba prob wyszukiwania
		 // liczba trafien
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			Node<person*>* result = NULL;
			person* so1 = new person;
			so1->age = distribution2(gen);
			so1->name = Names[rand() % (20 - 0) + 0];


			result = bst->searchForElement(bst->root, so1, object1SearchCmp, object1Comparator);
			
			if (result != NULL)
			{

				bst->Delete(result, object1Comparator);
				hits++;

			}

		}

		cout << "liczba znalezionych i usunietych elementow: " << hits << endl;
		t2 = clock();
		bst->toString(personToString, hits);
		diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar dif2 : " << diff << "\n\n\n";
		cout << "\t\t-----------------------------------------\n\n" << endl;
		//bst->printpreorder(bst->root);

		bst->~BST();

	}
	delete bst;
	cout << "\n\n koniec" << endl;
	getchar();
	return 0;

}
