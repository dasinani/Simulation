#include <iostream>
#include <iomanip>
#include "Queue.h"

void Queue::enqueue(Job& oneJob)
{
	Node* extraNode = new Node;
	extraNode->jobData = oneJob;
	extraNode->next = nullptr;

	if (head == nullptr)
		head = extraNode;

	else
	{
		Node* ptr = head;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}

		ptr->next = extraNode;


	}

}

void Queue::dequeue()
{
	if (head != nullptr)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	
}

bool Queue::isEmpty()
{
	return (head == nullptr);
}

int Queue::countQueue()
{
	int count = 0;
	Node* current = head;

	// Traverse the queue and count the elements
	while (current != nullptr)
	{
		count++;
		current = current->next;
	}

	return count;
}

Job Queue::getFirstJobInQueue()
{
	if (head != nullptr)
	{
		return head->jobData;
	}
}

void Queue::printQueue()
{
	Node* ptr = head;

	while (ptr != nullptr)
	{
		std::cout << "\n\n" << std::setw(4) << std::right
			<< ptr->jobData.jobType << std::setw(16) << std::right
			<< ptr->jobData.arrivalTime << std::setw(18) << std::right
			<< ptr->jobData.processingTime;

		ptr = ptr->next;
	}
}