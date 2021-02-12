// ConsoleApplication7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

struct object1
{
	int data1;
	char data2;
};

struct object2
{
	double data3;
	bool data4;
};

template <class T>
class Node
{
public:{
	T data = NULL;
	Node prev = NULL;
	Node next = NULL;
}
};

template <class T>
class list
{

	Node* head;
	Node* tail;
	int size = 0;


public:
{
	list() {
		head = NULL;
		tail = NULL;

		void addAtTail(T data)
		{
			Node<T> temp = new Node<T>();
			temp->data = data;
			if (this->size == 0)
			{
				this->head = temp;
				this->tail = temp;
				

			}
			else if (size > 0)
			{
				this->tail->next = temp;
				temp->prev = this->tail;
				this->tail = temp;
			
			}
			size++;

		}
		void addAtHead(T data)
		{
			Node<T>* temp = new Node<T>();
			temp->data = data;
			if (this->size == 0)
			{
				this->head = temp;
				this->tail = temp;
			}
			else if (size > 0)
			{
				this->head->prev = temp;
				temp->next = this->head;
				this->head = temp;
			}
			size++;
		}

		void deleteLast()
		{
			if (size == 0)
			{
				//std::cout << "list is empty you cannot delete anything";
				return;
			}
			else
			{
				Node<T>* temp = this->tail->prev;
				delete this->tail;
				if (temp != NULL)
				{
					this->tail = temp;
					temp->next = null;
					
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
				Node<T>*temp = this->head->next;
				delete this->head;
				if (temp!=NULL)
				{
					this->head = temp;
					this->prev = NULL;
					
				}
				this->head = NULL;
				this->tail = NULL;
				size--;
			}

		}
		void toString() {
			if (this->size == 0)
				std::cout << "lista ma 0 elementow";
			else if (this->size < 6)
				std::cout << "lista posiada" << this->size << "elementow";
			else if (this->size >= 6)
				std::cout << "1." << this->head << "2." << this->head->prev << ".\n.\n.\n" << this->tail->next << "\n" << this->tail;
		}
}

}

};




int main()
{
	int a = 0;
	int b = 1;
	int c = 2;
	int s = 3;
	std::cout << "1." << a << "\n 2." << b << ".\n.\n.\n" << c << "\n" << d;
    //std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
