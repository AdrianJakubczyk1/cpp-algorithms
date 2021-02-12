




#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
#include <math.h>

using namespace std;
struct person
{
	int age;
	string name;
};



template <class T>
class Node
{
public:
	//T data=NULL;
	Node<T>* prev = NULL;
	Node<T>* next = NULL;
	string key;

	Node() {
		data = NULL;
	}


	void setData(T data)
	{
		this->data = data;
	}

	T getData()
	{
		return this->data;
	}

private:
	T data;

};

template <class T>
class list
{

	Node<T>* head;
	Node<T>* tail;
	//int size = 0;
	int size = 0;

public:
	
	list() {
		head = NULL;
		tail = NULL;
	}

	int getSize() {
		return this->size;
	}

	void addAtTail(T data, string key)
	{
		Node<T>* temp = new Node<T>();
		temp->setData(data);
		temp->key = key;
		
		if (size == 0)
		{
			this->head = temp;
			this->tail = temp;
			

		}
		else if (size > 0)
		{
			this->tail->next = temp;
			temp->prev = tail;
			this->tail = temp;
			
		}
		this->size++;

	}
	void deleteLast()
	{
		if (size == 0)
		{

			return;
		}
		else
		{
			Node<T>* temp = this->tail->prev;

			delete this->tail;

			if (temp != NULL)
			{
				this->tail = temp;
				temp->next = NULL;

			}
			else {
				this->head = NULL;
				this->tail = NULL;
			}
			size--;
		}
	}

	void deleteFirst()
	{
		if (size == 0)
			return;
		else {
			Node<T>* temp = this->head->next;

			delete this->head;

			if (temp != NULL)
			{
				this->head = temp;

				temp->prev = NULL;

			}
			else {
				this->head = NULL;
				this->tail = NULL;
			}

			size--;
		}

	}


	string toString(string(*dataToString)(T obj))
	{
		int counter = 0;
		string result = "";
		Node<T>* temp = this->head;
		while (temp != NULL)
		{

			if (temp == this->head)
			{
				result.append(" data:  ");
				result.append(to_string(temp->getData()));
				result.append(" , key: ");
				result.append(temp->key);
				result.append(" -> ");
			}
			else if (counter < 6) {
				result.append(" data:  ");
				result.append(to_string(temp->getData()));
				result.append("  key: ");
				result.append(temp->key);
				result.append(" -> ");
			}
			else if (size - counter - 6 == 6)
			{
				result.append(".....");
			}
			else if (size - counter < 6) {
				result.append(" data:  ");
				result.append(to_string(temp->getData()));
				result.append("  key: ");
				result.append(temp->key);
				result.append(" -> ");
			}



			temp = temp->next;
			counter++;
		}

		return result;
	}



	Node<T>* getDataFromSpecificNode(int i)

	{
		if (size > i)
		{
			int counter = 0;
			Node<T>* temp = new Node<T>();
			if (size - i > size / 2)
			{
				temp = this->head;
				while (temp->next != NULL && counter != i)
				{
					temp = temp->next;
					counter++;
				}
			}
			else if (size - i < size / 2)
			{
				temp = this->tail;
				while (temp->prev != NULL && counter != i)
				{
					temp = temp->prev;
					counter++;
				}
			}
			return temp;

		}
		return NULL;
	}

	Node<T>* getDataFromSpecificNodeByKey(string key)
	{
			Node<T>* temp = NULL;
				temp = this->head;
				if (this->head != NULL) {
					if (this->head->key == key)
						return this->head;
					while (temp->next != NULL)
					{
						
						if (temp->key == key)
							return temp;
						else temp = temp->next;
					}
				}

			return NULL;

		}

		bool DeleteByKey(string key)
		{
			Node<T>* temp = new Node<T>();
			temp = this->head;
			while (temp->next != NULL && temp->key!=key)
			{
				temp = temp->next;
			}
			if (temp == NULL)
				return false;
			if (temp == head)
			{
				temp->next = head;
			}
			else if (temp == tail)
				temp->prev = tail;
			else {
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
			}
			size--;
			delete temp;
			return true;
		}
			
		
		


	Node<T>* getData()
	{
		Node<T>* temp;
		temp = this->head;
		if(head->next!=NULL)
		head = head->next;
		temp->prev = NULL;
		temp->next = NULL;
		return temp;
	}

	void changeData(int index, T data)
	{
		if (size - 1 > index)
		{
			int counter = 0;
			Node<T>* temp = new Node<T>();
			temp = this->head;
			while (temp->next != NULL && counter != index)
			{
				temp = temp->next;
				counter++;
			}

			//free(temp->data);
			temp->setData(data);
			
		}
		else
		{
			//cout << "the index given is incorrect";
		}
	}

	
	void clear()
	{
		Node<T>* temp = new Node<T>();
		while (head != NULL) {
			temp = head;
			head = head->next;
			if (temp != NULL)
				free(temp);
			size--;
		}

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

}


string personToString(int i)
{

	string s = "";
	return s;
}

// --TAB

template<class T>
class hashTable {
private:
	unsigned int currentSize;
	unsigned int maxSize;



public:

	list<T>* arr;
	hashTable() {
		maxSize = 256;
		currentSize = 0;
		arr = new list<T>[maxSize];
	}

	int hashFunction(string key)
	{
		unsigned int sum = 0;

		for (int i = 1; i <= key.length(); i++)
		{
			char x = key[i - 1];
			int numX = (int)x;

			sum += numX * pow(31, key.length() - i);

		}
		return sum % maxSize;
	}


	void addNewElement(T data, string key)
	{
		Node<T>* temp = NULL;
		int index = hashFunction(key);
		if (currentSize >= maxSize * 0.75)
			reReHash();
			//reHash();

		if (arr[index].getSize() > 0)
		{
			for (int i = 0; i < arr[index].getSize(); i++)
			{
				temp = arr[index].getDataFromSpecificNode(i);
				
				if (temp != NULL && temp->key == key) {
					arr[index].changeData(i,data);
					return;
				}
			}
		}
		arr[index].addAtTail(data, key);
		currentSize++;
	}

	void reReHash()
	{
		if (currentSize >= maxSize * 0.75) {
			int oldSize = maxSize;
			
			maxSize = maxSize * 2;
			//cout << "rehash" << endl;
			list<T>* tempArr = new list<T>[maxSize];
			Node<T>* temp = NULL;
			int index = 0;
			for (int i = 0; i < oldSize- 1; i++)
			{

				if (arr[i].getSize() > 0) {
					for (int j = 0; j < arr[i].getSize(); j++) {
						temp = arr[i].getDataFromSpecificNode(j);
						if (temp != NULL) {
							index = hashFunction(temp->key);
							tempArr[index].addAtTail(temp->getData(), temp->key);
							break;
						}
					}
				}
			}

			delete[] arr;
			
			arr = tempArr;
			

		}

	}


	Node<T>* searchForData(string key)
	{
		Node<T>* temp;
		int index = hashFunction(key);
		/*if (arr[index].getSize() > 0)
		{
			for (int j = 0; j < arr[index].getSize(); j++) {
				if (arr[index].getDataFromSpecificNode(j)->key == key) {
					temp = arr[index].getDataFromSpecificNode(j);
					return temp;
				}
			}
		}*/
		return  arr[index].getDataFromSpecificNodeByKey(key);
		
	}

	void changeData(int index, T data)
	{
		if (index <= currentSize && currentSize > 0)
		{

			arr[index] = NULL;
			delete arr[index];
			arr[index] = data;


		}
		else
			return;
	}

	bool deleteData(string key)
	{
		int index = hashFunction(key);
		if (arr[index].getSize() > 0)
		{
			return arr[index].DeleteByKey(key);
		}

		else return false;
	}
	




	string toString(string(*dataToString)(T obj))
	{
		int emptyCounter = 0;
		int notEmptyCounter = 0;
		int counter = 0;
		string result = "";
		double avgSize = 0.0;
		int maxySize = 0;
		for (unsigned int i = 0; i <= maxSize - 1; i++)
		{

			if (arr[i].getSize() > 0) {
				notEmptyCounter++;
				if (maxySize < arr[i].getSize())
					maxySize = arr[i].getSize();
				avgSize += arr[i].getSize();
			
			}
			else if (arr[i].getSize() == 0)
				emptyCounter++;

			if (notEmptyCounter < 10 && arr[i].getSize()>0)
			{
				
				result.append("index: ");
				result.append(to_string(i));
				result.append(arr[i].toString(dataToString));
				result.append(", \n");
				
			}
		}
		result.append("\n tablica posiada : ");
		result.append(to_string(this->currentSize));
		result.append(" elementow \n");
		result.append(to_string(emptyCounter));
		result.append(" pustych elementow \n");
		result.append(to_string(notEmptyCounter));
		result.append(" nie pustych elementow \n");
		result.append(" aktualny rozmiar tablicy to: ");
		result.append(to_string(currentSize));
		result.append("\n");
		result.append(" maksymalny rozmiar tablicy: ");
		result.append(to_string(maxSize));
		result.append("\n maksymalny rozmiar listy: ");
		result.append(to_string(maxySize));
		result.append("\n");
		result.append(" sredni rozmiar listy: ");
		result.append(to_string(avgSize/notEmptyCounter));
		result.append("\n");
		return result;
	}

	void clear()
	{
	
		delete[] this->arr;
		this->maxSize = 256;
		this->arr = new list<T>[maxSize]();
		this->currentSize = 0;
	
	}

};

		//przepisac tablice na nowa jak rosnie jak dojdzie do max capacity to uzywamy wspolczynnik wzrostu
	
string randomKey(int number)
{
	string base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string temp = "";
	for (int i = 0; i < number; i++)
	{
		temp+=base[rand() % (21 - 0) + 0];
	}
	return temp;
}


int main2()
{
	hashTable<int>* table = new hashTable<int>();

	table->addNewElement(0, "aaaaaa");
	table->addNewElement(1, "aabbbb");
	table->addNewElement(2, "cccccc");
	table->addNewElement(3, "cccddd");
	int hits= 0;
	
	bool result = false;

	result = table->deleteData("aaaaaa");
	table->addNewElement(1, "aabbbb");
	table->addNewElement(1, "aaaaaa");
	if (result)
	{

		hits++;
	}
	/*if (result1 != NULL)
	{

		hits++;
	}
	if (result2 != NULL)
	{

		hits++;
	}
	if (result3 != NULL)
	{

		hits++;
	}*/
	cout << hits;
	getchar();
	return 0;
}


int main()
{
	random_device rd;
	mt19937 gen(rd());
	srand(time(NULL));
	uniform_real_distribution<> distribution(1, 15000000);
	uniform_real_distribution<> distribution2(1, 10000000);
	//generating a random integer:
	double random = distribution(gen);
	hashTable<int>* table = new hashTable<int>();

	const int MAX_ORDER = 7; 
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do drzewa
		int hits = 0;
		clock_t t1 = clock();
		for (int i = 0; i < n; i++)

		{
			table->addNewElement(i,randomKey(6));
		}
		
		clock_t t2 = clock();
		string result = table->toString(personToString);
		cout << result;
		double diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "dodawanie : " << diff << "\n\n";


		// wyszukiwanie
		const int m = pow(10, 4); // liczba prob wyszukiwania
		 // liczba trafien
		t1 = clock();
		for (int i = 0; i < m; i++)
		{
			string key = randomKey(6);
			Node<int>* result = NULL;
			result = table->searchForData(key);
			if (result != NULL)
			{
				
				hits++;
			}
		}

		cout << "liczba znalezionych elementow: " << hits << endl;
		t2 = clock();
		diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar szukanie : " << diff << "\n\n\n";
		cout << "\t\t-----------------------------------------\n\n" << endl;
		table->clear();

	}
	delete table;
	cout << "\n\n koniec" << endl;
	getchar();
	return 0;

}
