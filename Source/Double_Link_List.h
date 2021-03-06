#pragma once

#include <initializer_list>

namespace Data_Structures
{
	template<typename T>
	class Double_Link_List
	{
	private:
		struct Node
		{
			T data {};
			Node* next = nullptr;
			Node* previous = nullptr;

			Node(const T& data = {}) : data{data}
			{}
		};

		Node* head = nullptr;
		Node* tail = nullptr;
		unsigned long long count = 0;

	public:
		Double_Link_List(const std::initializer_list<T>& initializer_list = {})
		{
			for(T value : initializer_list)
			{
				Insert_Tail(value);
			}
		}

		Double_Link_List(const Double_Link_List& list)
		{
			Node* node = list.head;

			while(node != nullptr)
			{
				Insert_Tail(node->data);
				node = node->next;
			}
		}

		~Double_Link_List()
		{
			Clear();
		}

		bool Empty()
		{
			return head == nullptr;
		}

		unsigned long long Count()
		{
			return count;
		}

		void Clear()
		{
			while(!Empty())
			{
				Delete_Head();
			}
		}

		T Head() const
		{
			return head->data;
		}

		T Tail() const
		{
			return tail->data;
		}

		T& operator[](const unsigned long long& index)
		{
			Node* node = head;

			for(unsigned long long i = 0; i < index; ++i)
			{
				node = node->next;
			}

			return node->data;
		}

		constexpr T& operator[](const unsigned long long& index) const
		{
			Node* node = head;

			for(unsigned long long i = 0; i < index; ++i)
			{
				node = node->next;
			}

			return node->data;
		}

		void operator=(const Double_Link_List& list)
		{
			Clear();

			Node* node = list.head;

			while(node != nullptr)
			{
				Insert_Tail(node->data);
				node = node->next;
			}
		}

		void operator=(const std::initializer_list<T>& data)
		{
			Clear();

			for(T value : data)
			{
				Insert_Tail(value);
			}
		}

		unsigned long long Contains(const T& data)
		{
			if(Empty())
			{
				return 0;
			}

			Node* node = head;
			unsigned long long data_count = 0;

			while(node != nullptr)
			{
				if(node->data == data)
				{
					data_count++;
				}

				node = node->next;
			}

			return data_count;
		}

		void Delete_Head()
		{
			if(Empty())
			{
				return;
			}

			Node* node = head;

			head = head->next;
			delete node;
			count--;
		}

		void Delete_Tail()
		{
			if(Empty())
			{
				return;
			}

			if(count == 1)
			{
				Delete_Head();
				return;
			}

			Node* tail_pointer = tail;
			tail = tail->previous;
			tail->next = nullptr;
			delete tail_pointer;
			count--;
		}

		void Delete(const unsigned long long& index)
		{
			if(Empty())
			{
				return;
			}

			if(index < 0 || index >= count)
			{
				return;
			}

			if(index == 0)
			{
				Delete_Head();
				return;
			}

			if(index == count - 1)
			{
				Delete_Tail();
				return;
			}

			Node* previous_node = head;

			for(unsigned long long i = 0; i < index - 1; ++i)
			{
				previous_node = previous_node->next;
			}

			Node* node = previous_node->next;
			Node* next_node = node->next;

			previous_node->next = next_node;
			next_node->previous = previous_node;
			delete node;
			count--;
		}

		void Insert_Head(const T& data)
		{
			Node* node = new Node(data);

			node->next = head;

			if(head != nullptr)
			{
				head->previous = node;
			}

			head = node;
			count++;

			if(count == 1)
			{
				tail = head;
			}
		}

		void Insert_Tail(const T& data)
		{
			if(Empty())
			{
				Insert_Head(data);
				return;
			}

			Node* node = new Node(data);

			tail->next = node;
			node->previous = tail;
			tail = node;
			count++;
		}

		void Insert(const unsigned long long& index, const T& data)
		{
			if(index < 0 || index > count)
			{
				return;
			}

			if(index == 0 || Empty())
			{
				Insert_Head(data);
				return;
			}

			if(index == count)
			{
				Insert_Tail(data);
				return;
			}

			Node* previous_node = head;
			Node* node = new Node(data);

			for(unsigned long long i = 0; i < index - 1; ++i)
			{
				previous_node = previous_node->next;
			}

			node->next = previous_node->next;
			previous_node->next = node;
			count++;
		}

		void Reverse()
		{
			if(Empty())
			{
				return;
			}

			Node* left = head;
			Node* right = tail;

			for(unsigned int i = 0; i < count / 2; i++)
			{
				std::swap(left->data, right->data);
				left = left->next;
				right = right->previous;
			}
		}
	};
}