//ALGO2 IS1 221A LAB06
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


template<class T>
class BinaryHeap {
	int capacity;
	T* arr;
	int size;

public:

	BinaryHeap() {
		size = 0;
		capacity = 10;
		arr = new T[capacity];
	}


	void addNewElement(T data, int(*cmp)(T, T))
	{

		if (capacity == size)
			incrementSize();
		arr[size] = data;
		repairUp(size, cmp);
		size++;
	}

	void repairUp(int index, int(*cmp)(T, T)) {
		T temp = arr[index];
		while (index>0 && cmp(temp,arr[(index -1 )/ 2])>0)
		{
			arr[index] = arr[(index - 1) / 2];
			arr[(index - 1) / 2] = temp;
			
			index = (index - 1)/2;
		}
		arr[index] = temp;
	}



	void incrementSize()
	{
		if (capacity == size) {
			
			T* temp = new T[capacity * 10];
			for (int i = 0; i < capacity; i++)
			{
				temp[i] = arr[i];
				
			}
			delete[] arr;
		
			arr = temp;
			capacity = capacity * 10;
		}

	}

	string toString(string(*dataToString)(T obj))
	{
		
		string result = "";
		for (int i = 0; i <= size - 1; i++)
		{
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			if (capacity == 10)
			{
				if (i == 0)
				{

					result.append("root: ");
					result.append(dataToString(arr[i]));
					result.append("\n\nleft: \n");
					result.append(dataToString(arr[left]));
					result.append("\n\nright: \n");
					result.append(dataToString(arr[right]));
					result.append("\n_________________________\n\n\n\n");
				}
				else {

					result.append(dataToString(arr[i]));
					result.append("\n\nleft: \n");
					result.append(dataToString(arr[left]));
					result.append("\n\nright: \n");
					result.append(dataToString(arr[right]));
					result.append("\n _________________________\n\n\n\n");
				}
				if (i == 2)
					break;
			}
			else {
				if (i == 0)
				{

					result.append("root: ");
					result.append(dataToString(arr[i]));
					result.append("\n\nleft: \n");
					result.append(dataToString(arr[left]));
					result.append("\n\nright: \n");
					result.append(dataToString(arr[right]));
					result.append("\n_________________________\n\n\n\n");
				}
				else {

					result.append(dataToString(arr[i]));
					result.append("\n\nleft: \n");
					result.append(dataToString(arr[left]));
					result.append("\n\nright: \n");
					result.append(dataToString(arr[right]));
					result.append("\n _________________________\n\n\n\n");
				}
				if (i == 6)
					break;
			}
		}
		if (size == 0)
			result.append("KOPIEC JEST PUSTY");	

		result.append("\n\n\n heap has right now : ");
		result.append(to_string(this->size));
		result.append(" elements \n");
		//result.append(" capacity is:  ");
		//result.append(to_string(this->capacity));
		result.append("\n");
		return result;
	}

	void clear()
	{
		delete[] arr;
		capacity = 10;
		arr = new T[capacity];
		size = 0;
		
	}

	void swap(T *obj, T *obj1)
	{
		T temp = *obj;
		*obj = *obj1;
		*obj1 = temp;
	}

	T poll(int(*cmp)(T, T))
	{
		if (size==0)return NULL;
		
		size--;
		T temp = arr[0];
		arr[0] = arr[size];
		repairDown(0,cmp);
		return temp;
	}

	void repairDown(int index, int(*cmp)(T, T))
	{
		int heapify;
		T temp;
		
		int r = 2 * index + 2;
		int l = 2 * index + 1;
		if ((l <= size) && (cmp(arr[l], arr[index])>0))
			heapify = l;
		else heapify = index;
		if ((r <= size) && (cmp(arr[r] ,arr[heapify])>0))
			heapify = r;
		if (heapify != index) 
		{
			temp = arr[index];
			arr[index] = arr[heapify];
			arr[heapify] = temp;

			repairDown(heapify, cmp);

		}
		
	}

};

int object1Comparator(person *o1, person *o2)
{
	int wynik = o1->age - o2->age;
	if (!wynik == 0)
		return wynik;
	else {
		if (o1->name > o2->name)
			return -1;
		else if (o1->name < o2->name)
			return 1;
	}
}


string personToString(person *obj)
{
	string result = "key: ";
	result.append(to_string(obj->age));
	result.append(" data: ");
	result.append(obj->name);
	return result;
}


string Names[22] = {
			" Adrian ", " Bolek ", " lolek ", " Borat ", " James ", " Jas ", "Jaroslaw ",
			" Waldemar ", " Wladyslaw ", " Zbigniew ", "Zdzislaw "
		," Jakub ", " Mateusz ", " Michal ", " Justynian ", " Zeus ", " Magda ", " Justyna ",
		" Krzysztof ", " Milosz ", " Marcin ", " Matt "
};


int main()
{

	srand(time(NULL));

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> distribution(1, 2500000);
	//generating a random integer:
	double random = distribution(gen);
		const int MAX_ORDER = 2; // maksymalny rzad wielkosci dodawanych danych
		BinaryHeap <person*>* bh = new BinaryHeap <person*>();
	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o); // rozmiar danych
		// dodawanie do kopca
		
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			person* so = new person();
			so->name = Names[rand() % (20 - 0) + 0];
			so->age = distribution(gen);
				bh->addNewElement(so, object1Comparator);
		}
		clock_t t2 = clock();
		string result = bh->toString(personToString);
		cout << result << endl;
		double diff = (t2 - t1) / (double)CLOCKS_PER_SEC;
		cout << "pomiar dodawanie : " << diff << "(s)\n\n -----------\n";
		// wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
		// pobieranie ( i usuwanie ) elementu maksymalnego z kopca
			t1 = clock();
		for (int i = 0; i < n; i++) {
			
			person* polled = bh->poll(object1Comparator);
			if (polled != NULL) {
				
				delete polled;
			}
		}
		
		t2 = clock();
	 // wypis na ekran aktualnej postaci kopca ( kopiec pusty ) oraz pomiarow czasowych
	
		 result = bh->toString(personToString);
		double diff2 = (t2 - t1) / (double)CLOCKS_PER_SEC;
		
		cout << result << endl;
		cout << "\n\npomiar poll : " << diff2 << "(s)\n\n";
		cout << "_____________________________________________________________ \n\n\n\n" << endl;

		bh->clear(); // czyszczenie kopca ( tak naprawde ,, zresetowanie ’’ tablicy dynamicznej opakowanej przez kopiec )
	}
	cout << "\n\n koniec" << endl;
	delete bh;
	getchar();
	return 0;
}