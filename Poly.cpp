#include "Poly.h"
#include <iostream>
#include <cmath>
using namespace std;
Poly::Poly()
{
	//Dummy Node
	int x = -1;
	double y = 1;
	size = 0;
	head = new PolyNode(x, y, NULL);
	// Total time complexity of Theta(7) = class of Theta(1)
	//Space complexity = Theta(7) = class of Theta(1)
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	int x = deg.size();
	//Dummy Node
	int z = -1;
	double y = 1;
	head = new PolyNode(z, y, NULL);
	size = 0;
	//Creating polynomial
	PolyNode* Readerhead = head;
	for (int i = 0; i < x; i++)
	{
		Readerhead->next = new PolyNode(deg[i], coeff[i], NULL);
		Readerhead = Readerhead->next;
		size++;
	}
	//Time Complexity of Theta(9+6n) = class of Theta(n)
	//Space complexity of Theta(2+6(n+1)) = Theta(n)
}

Poly::~Poly()
{
	while (head->next != NULL)
	{
		auto temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	size = 0;
	delete head;
	//time complexity of theta(3n + 2) = class of Theta(n)
	//space complexity of 3 or class of Theta(1)
}

void Poly::addMono(int i, double c)
{
	if (c == 0)
	{
		return;
	}
	else
	{
		PolyNode* readerhead = head;
		PolyNode* prevhead = NULL;
		for (int j = 0; j < size; j++)
		{
			if (readerhead->next->deg == i) // This code handles all conditions when i == a monomial in the list
			{
				if (readerhead->next->coeff + c != 0)
				{
					readerhead->next->coeff += c;
					return;
				}
				else
				{
					PolyNode* temp = readerhead->next;
					readerhead->next = readerhead->next->next;
					delete temp;
					size--;
					return;
				}
			}//Complexity of Theta(1)
			else if (j == 0 && readerhead->next->deg < i)
			{
				readerhead = readerhead->next;
				head->next = new PolyNode(i, c, readerhead);
				size++;
				return;
			}
			else if (j != 0 && (prevhead->next->deg > i && prevhead->next->next->deg < i))
			{
				PolyNode* temp = prevhead->next->next;
				prevhead->next->next = new PolyNode(i, c, temp);
				size++;
				return;
			}
			else if (j == size - 1 && readerhead->next->deg > i)
			{
				readerhead->next->next = new PolyNode(i, c, NULL);
				size++;
				return;
			}
			else
			{
				prevhead = readerhead;
				readerhead = readerhead->next;

			}
		}
	}
} // Best case time complexity Theta(1), Worst Case Theta(cn), Complexity of O(n)
//Space complexity of Theta(3)

void Poly::addPoly(const Poly& p)
{
	if (size > 0)
	{
		PolyNode* readerhead = p.head->next;
		for (int i = 0; i < p.size; i++)
		{
			addMono(readerhead->deg, readerhead->coeff);
			readerhead = readerhead->next;
		}
	}//Time Complexity of Theta(n*m) or class of O(n^2)
	//Space complexity of class Theta(1)
	else
	{
		PolyNode* readerhead = head;
		PolyNode* readerhead2 = p.head;
		for (int i = 0; i < p.size; i++)
		{
			readerhead->next = new PolyNode(readerhead2->next->deg, readerhead2->next->coeff, NULL);
			readerhead = readerhead->next;
			readerhead2 = readerhead2->next;
			size++;
		}
	}//Time complexity of O(n^2)
}//Space complexity of Theta(1)

void Poly::multiplyMono(int i, double c)
{
	if (c == 0)
	{
		while (head->next != NULL)
		{
			auto temp = head->next;
			head->next = temp->next;
			delete temp;
		}
		size = 0;
	}//Time complexity of Theta(n)
	//Space complexity of Theta(1)
	else
	{
		PolyNode* readerhead = head;
		for (int j = 0; j < size; j++)
		{
			readerhead->next->coeff *= c;
			readerhead->next->deg += i;
			readerhead = readerhead->next;
		}
	}
}//Time complexity of Theta(n)
//Space complexity of Theta(1)

void Poly::multiplyPoly(const Poly& p)
{
	Poly temp = Poly();
	temp.addPoly(*this); // Theta(n)
	multiplyMono(1, 0); // Theta(n)
	PolyNode* readerhead = p.head; //Theta(1)
	for (int i = 0; i < p.size; i++)
	{
		Poly temp2 = Poly();
		temp2.addPoly(temp);
		temp2.multiplyMono(readerhead->next->deg, readerhead->next->coeff);// O(n^2)
		readerhead = readerhead->next;
		addPoly(temp2);//O(n^3)
		temp2.~Poly();
	}
	temp.~Poly();//Theta(n)
}//Space complexity = Theta(n^2)
//Time complexity  = O(n^3)

void Poly::duplicate(Poly& outputPoly)
{
	outputPoly.multiplyMono(1, 0);// Theta(n)
	outputPoly.addPoly(*this);//Theta(n)
}//Space complexity = Theta(n)
//Time complexity of Theta(1)

int Poly::getDegree()
{
	// TODO
	if (head->next == NULL)
	{
		return -1;
	}
	else
	{
		return head->next->deg;
	}
}//Space complexity of Theta(1)
//Time complexity of Theta(1)

int Poly::getTermsNo()
{
	// TODO
	return size;//change this after completing this function
}//Time complexity of Theta(1)
//Space complexity of Theta(1)

double Poly::evaluate(double x)
{
	double number = 0;
	PolyNode* readerhead = head;
	for (int i = 0; i < size; i++)
	{
		number += (readerhead->next->coeff) * pow(x, readerhead->next->deg);
		readerhead = readerhead->next;
	}
	return number;//change this after completing this function
}//Space complexity of class Theta(1)
//Time complexity of Theta(2+2n) = class of Theta(n)

std::string Poly::toString()
{
	// TODO
	return "";//change this after completing this function
}
