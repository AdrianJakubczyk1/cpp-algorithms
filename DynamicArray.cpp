//ALGO2 IS1 221A LAB02
//Adrian Jakubczyk
//ja36272@zut.edu.pl

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
struct person
{
	int age;
	string name;
};




template<class T>
class TabDyn
{
	int capacity;//wzrost


	T* arr;
	int size;
	int count;
public:
	
		TabDyn() {
		size = 1;
		capacity = 0;
		arr = new T[1];
	}
		

	void addNewElement(T data)
	{
		
		if (capacity == size)
			incrementSize();
		arr[capacity] = data;
		capacity++;
	}

void incrementSize()
	{
		if (capacity == size){
			T* temp = new T[size*2];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
				//arr[i] = NULL;
			}
			delete[] arr;
			/*
			arr = new T[size * 2];
			for (int i = 0; i < size; i++)
			{
				
				arr[i] = temp[i];
			}
			*/
			arr = temp;
			size = size * 2;
		}
	
	}

	T searchForData(int index)
	{
		T temp;
		if (index <= capacity && capacity > 0)
		{
			temp = arr[index];
			return temp;
		}
		else
			return temp = NULL;
	}

	void changeData(int index, T data)
	{
		if (index <= capacity && capacity > 0)
		{
			
			arr[index] = NULL;
			delete arr[index];
			arr[index] = data;
			

		}
		else
			return;
	}


	string toString(string(*dataToString)(T obj))
	{
		string result = "";
		for(int i=0; i<=capacity-1;i++)
		{
			if (i==0)
			{
				result.append(dataToString(arr[i]));
			}
			else if (i < 4) {
				result.append(" , ");
				result.append(dataToString(arr[i]));
			}
			else if (capacity - i - 4 == 6)
			{
				result.append(".....");
			}
			else if (capacity - i-1 < 6) {
				result.append(" , ");
				result.append(dataToString(arr[i]));
			}
		}
		result.append("\n lista posiada : ");
		result.append(to_string(this->capacity));
		result.append(" elementow \n");
		return result;
	}

	void clear()
	{
		free(arr);
		size = 1;
		capacity = 0;
	}

	void bubbleSort(int(*cmp)(T, T)) {
		
			for (int i = 0; i < capacity-1; i++)
				for (int j = 0; j < capacity - i-1; j++)
				{
					if (cmp(arr[j], arr[j + 1]) >= 1)
						swap(&arr[j], &arr[j + 1]);
				}
		
	}

	void swap(T *obj, T *obj1)
	{
		T temp = *obj;
		*obj = *obj1;
		*obj1 = temp;
	}

	//przepisac tablice na nowa jak rosnie jak dojdzie do max capacity to uzywamy wspolczynnik wzrostu
};

int object1Comparator(person *o1, person *o2)
{
	
	
	int wynik = o1->age - o2->age;
	if (!wynik == 0)
		return wynik;
	else {
		//for (int i = 0; i < o1->name.length(); i++)
		//{
			if (o1->name > o2->name)
				return -1;
			else if (o1->name < o2->name)
				return 1;
		//	else {
		//		continue;
		//	}
		//}
	}
}


string personToString(person *obj)
{
	string result = to_string(obj->age);
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
	TabDyn<person*>* da = new TabDyn<person*>(); // stworzenie tablicy
	const int order = 8; // rzad wielkosci rozmiaru dodawanych danych
	const int n = pow(10, order); // rozmiar danych
	// dodawanie do tablicy
	clock_t t1 = clock();


	float max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
	for (int i = 0; i < n; i++) {
		person* sp =new person;
		sp->age = rand() % (30232 - 1) + 1;
		sp->name = Names[rand() % (21 - 0) + 0];
		// losowe dane
		clock_t t1_element = clock();

		da->addNewElement(sp);
		clock_t t2_element = clock();
		float time_per_element = (t2_element - t1_element) / (float)CLOCKS_PER_SEC; // obliczenie czasu pojedynczej operacji dodawania
			if (time_per_element > max_time_per_element)
			{
				max_time_per_element = time_per_element;
				cout << "\n nowy najgorszy czas: " << time_per_element << "\t dla indeksu : " << i<<endl;
			}
			
		
	}
	
	//da->bubbleSort(object1Comparator);

	clock_t t2 = clock();
	string result = da->toString(personToString); // wypis na ekran aktualnej postaci tablicy ( skrotowej ) i pomiarow czasowych ( czas calkowity i
	cout << result << "\n czas ogolny: " << (t2 - t1) / (float)CLOCKS_PER_SEC << "\n najgorszy czas: " << max_time_per_element<<endl;
	cout <<"zamortyzowany"<< ((t2 - t1) / (float)CLOCKS_PER_SEC) / (double)n;
	da->clear(); // czyszczenie tablicy wraz z uwalnianiem pamieci danych
	delete da;
	getchar();
	return 0;
}