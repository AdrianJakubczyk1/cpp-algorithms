//ALGO2 IS1 221A LAB04
//Adrian Jakubczyk
//ja36272@zut.edu.pl

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>



using namespace std;
struct person
{
	int age;
	string name;
};




template <class T>
class Node {

	

public:
	Node(bool is=true) {
		isBlack = is;
	}

	T data;
	Node<T>* Left = NULL;
	Node<T>* Right = NULL;
	Node<T>* Parent = NULL;
	bool isBlack;

};

template <class T>
class RedBlack {
	int size = 0;
	
public:
	Node<T>* root = NULL;


	void add(T data, int(*cmp)(T, T)) {
		Node<T>* temp = new Node<T>();
		temp->data = data;

		Node<T>* tempRoot = this->root;
		Node<T>* tempNext = NULL;
		if (size == 0) {
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

		if (cmp(temp->data, tempNext->data) < 0)
		{

			tempNext->Left = temp;
			temp->Parent = tempNext;
			temp->isBlack = false;
		}


		else if (cmp(temp->data, tempNext->data) > 0) {

			tempNext->Right = temp;
			temp->isBlack = false;
			temp->Parent = tempNext;
		}
		
		
		size++;
		addRepair(temp);
		return;

	}

	void addRepair(Node<T>* pt)
	{
		Node<T>* temp;

		while ((pt != root) && (!pt->isBlack) && (!pt->Parent->isBlack))
		{
			Node<T> *parent_pt = NULL;
			Node<T> *grand_parent_pt = NULL;
			grand_parent_pt = pt->Parent->Parent;
			parent_pt = pt->Parent;
			


			if (parent_pt == grand_parent_pt->Right)
			{

				Node<T> *uncle_pt = grand_parent_pt->Left;

				if(uncle_pt!=NULL){
				if ((!uncle_pt->isBlack))
				{

					parent_pt->isBlack = true;
					uncle_pt->isBlack = true;
					grand_parent_pt->isBlack = false;
					pt = grand_parent_pt;

				}
				else
				{
					if (pt == parent_pt->Left)
					{
						rotateRight(parent_pt);
						pt = parent_pt;
						parent_pt = pt->Parent;

					}

					rotateLeft(grand_parent_pt);
					parent_pt->isBlack = !(parent_pt->isBlack);
					grand_parent_pt->isBlack = !(grand_parent_pt->isBlack);
					pt = parent_pt;

				}
			}
			}
			else
			{

				Node<T> *uncle_pt = grand_parent_pt->Right;


				if (uncle_pt != NULL && !uncle_pt->isBlack)
				{
					grand_parent_pt->isBlack = false;
					parent_pt->isBlack = true;
					uncle_pt->isBlack = true;
					pt = grand_parent_pt;

				}

				else
				{

					if (pt == parent_pt->Right)
					{
						rotateLeft(parent_pt);
						pt = parent_pt;
						parent_pt = pt->Parent;

					}

					rotateRight(grand_parent_pt);
					parent_pt->isBlack = !(parent_pt->isBlack);
					grand_parent_pt->isBlack = !(grand_parent_pt->isBlack);
					pt = parent_pt;
				}
			}
			
		}
		root->isBlack = true;
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

	void toString(string(*dataToString)(T obj), int hits)
	{


		reverseLevelOrder(root, dataToString);
		int height = getHeightForPrint(root);
		cout << "wysokosc drzewa wynosi: " << height + 1 << endl;
		cout << "drzewo ma: " << size << " elementow" << "\n\n\n\n" << endl;


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
		string color = " ";
		if (root == NULL)
			return;
		if (level == 1) {
			count++;
			if (root != this->root) {
				if (root->isBlack)color = " B "; else color = " R ";
				if (root->Left != NULL && root->Right != NULL) {
					cout << "[index: " << root->data->age << " Parent's index: "<<root->Parent->data->age;
					
					cout << " Left Child's index: " << root->Left->data->age << " Right's Child index: " << root->Right->data->age << " colour: "<< color << "data name: " << root->data->name << " ]" << endl;
				}
				else if (root->Left != NULL && root->Right == NULL) {
					cout << "[index: " << root->data->age << " Parent's index "<< root->Parent->data->age;
					
					cout << " Left Child's index: " << root->Left->data->age << " Right's Child index: None" << " colour: "<<color  << "data name: " << root->data->name << " ]" << endl;
				}

				else if (root->Left == NULL && root->Right != NULL) {
					cout << "[index: " << root->data->age << " Parent's index "<< root->Parent->data->age;
					
					cout << " Left Child's index: None" << " Right's Child index: " << root->Right->data->age << " colour: "<< color << "data name: " << root->data->name << " ]" << endl;
				}
				else if (root->Left == NULL && root->Right == NULL)
				{
					cout << "[index: " << root->data->age << " Parent's index "<< root->Parent->data->age;
					
					cout << " Left Child's index: None" << " Right's Child index:None " << " colour: "<< color <<"data name: " << root->data->name << " ]" << endl;
				}
			}
			else if (level < 6)
			{
				if (root->isBlack)color = " B "; else color = " R ";
				if (root->Left != NULL && root->Right != NULL)
					cout << "[index: " << root->data->age << " Parent's index: none" << " Left Child's index: " << root->Left->data->age << " Right's Child index: " << root->Right->data->age <<" colour: " << color << "data name: " << root->data->name << " ]" << endl;

				else if (root->Left != NULL && root->Right == NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: " << root->Left->data->age << " Right's Child index: None"<<" colour: " << color  << "data name: " << root->data->name << " ]" << endl;

				else if (root->Left == NULL && root->Right != NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: None" << " Right's Child index: " << root->Right->data->age<< " colour: " << color  << "data name: " << root->data->name << " ]" << endl;
				else if (root->Left == NULL && root->Right == NULL)
					cout << "[index: " << root->data->age << " Parent's index None" << " Left Child's index: None" << " Right's Child index:None "<< " colour: " << color  << "data name: " << root->data->name << " ]" << endl;
			}


		}

		else if (level < 6)
		{
			count++;
			printGivenLevel(root->Left, level - 1, dataToString);
			printGivenLevel(root->Right, level - 1, dataToString);
		}


	}



	Node<T>* searchForElement(Node<T>* root, T key, bool(*cmp1)(T, T), int(*cmp)(T, T))
	{
		while (!cmp1(root->data, key)) {

			if (root != NULL) {


				if (cmp(root->data,key)>0) {
					root = root->Left;
				}  
				else {
					root = root->Right;
				}

			
				if (root == NULL) {
					return NULL;
				}
			}
		}
		return root;
	}

	void printpreorder(Node<T>* node)
	{
		if (node == NULL)
			return;

		if (node == this->root)
			cout << "root: ";
		cout << node->data->age << " | ";
		
		printpreorder(node->Left);



		
		printpreorder(node->Right);
	}

	void printInorder(Node<T>* node)
	{
		if (node == NULL)
			return;

		
		printInorder(node->Left);

		
		if (node == this->root)
			cout << "root: ";
		cout << node->key << " | ";

		
		printInorder(node->Right);
	}

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


	~RedBlack()
	{
		clear(root);
	}



	void rotateRight(Node<T>* node) {
		Node<T>* y = node->Left;
		node->Left = y->Right;
		if (y->Right != NULL) {
			y->Right->Parent = node;
		}
		y->Parent = node->Parent;
		if (node==this->root) {
			this->root = y;
		}
		else if (node == node->Parent->Left) {
			node->Parent->Left = y;
		}
		else {
			node->Parent->Right = y;
			
		}
		y->Right = node;
		node->Parent = y;
	}

	void rotateLeft(Node<T>* node) {
		Node<T>* y = node->Right;
		if (node->Right != NULL) {
			node->Right = y->Left;
			if (y->Left != NULL) {
				y->Left->Parent = node;
			}
		}
		y->Parent = node->Parent;
		if (node==this->root) {
			this->root = y;
		}
		else if (node == node->Parent->Right) {
			node->Parent->Right = y;
		}
		else {
			node->Parent->Left = y;
			
		}
		y->Left = node;
		node->Parent = y;
	}




};


bool object1SearchCmp(person*o1, person*o2)
{
	if (o1->age == o2->age) {


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
	RedBlack<person*>* bst = new RedBlack<person*>(); // stworzenie
	person* so = new person;
	so->age = 55;

	so->name = Names[rand() % (20 - 0) + 0];
	person* so1 = new person;
	so1->age = 69;

	so1->name = Names[rand() % (20 - 0) + 0];
	person* so2 = new person;
	so2->age = 62;

	so2->name = Names[rand() % (20 - 0) + 0];
	person* so3 = new person;
	so3->age = 57;

	so3->name = Names[rand() % (20 - 0) + 0];
	person* so4 = new person;
	so4->age = 35;

	so4->name = Names[rand() % (20 - 0) + 0];
	person* so5 = new person;
	so5->age = 83;

	so5->name = Names[rand() % (20 - 0) + 0];
	person* so6 = new person;
	so6->age = 72;

	so6->name = Names[rand() % (20 - 0) + 0];
	person* so7 = new person;
	so7->age = 74;

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


	bst->toString(personToString, 0);
	Node<person*>* temp = NULL;
	temp = bst->searchForElement(bst->root, so4, object1SearchCmp, object1Comparator);

	
	bst->toString(personToString, 0);



	getchar();
	return 0;
}



int main() {

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> distribution(1, 15000000);
	uniform_real_distribution<> distribution2(1, 10000000);
	//generating a random integer:
	double random = distribution(gen);
	unsigned int prev = 0;
	const int MAX_ORDER = 6; // maksymalny rzad wielkosci dodawanych danych
	RedBlack<person*>* bst = new RedBlack<person*>(); // stworzenie
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


			so->name = Names[rand() % (20 - 0) + 0];

			bst->add(so, object1Comparator); // dodanie ( drugi argument to wskaznik na komparator )

		}

		clock_t t2 = clock();
		// wypis na ekran aktualnej postaci drzewa ( skrotowej ) wraz z pomiarami czasowymi i w / w
		bst->toString(personToString, hits);
		double diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar dodawanie : " << diff << "\n\n";


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

				hits++;

			}
			delete so1;

		}

		cout << "liczba znalezionych wezlow:  " << hits << endl;
		t2 = clock();
		bst->toString(personToString, hits);
		cout << "logarytm " << 2*log2(n+1) << endl;
		diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar szukanie : " << diff << "\n\n\n";
		cout << "\t\t-----------------------------------------\n\n" << endl;
		//bst->printpreorder(bst->root);

		bst->~RedBlack();

	}
	delete bst;
	cout << "\n\n koniec" << endl;
	getchar();
	return 0;
}