#ifndef IndexedPriority_h__
#define IndexedPriority_h__

#include <vector>
#include <cassert>

template<class comPtr>
class IndexedPriority
{
public:

	//you must pass the constructor a reference to the std::vector the PQ
	//will be indexing into and the maximum size of the queue.
	IndexedPriority(int MaxSize, comPtr const& cp)
		: comp(cp)
		, m_iMaxSize(MaxSize)
		, m_iSize(0)
	{
		m_Heap.assign(MaxSize+1, 0);
		m_invHeap.assign(MaxSize+1, 0);
	}

	bool empty()const{return (m_iSize==0);}
		
	void reset()
	{		
		m_iSize = 0;
		
		std::fill(m_Heap.begin(), m_Heap.end(), 0);
		std::fill(m_invHeap.begin(), m_invHeap.end(), 0);		
		
	}

	//to insert an item into the queue it gets added to the end of the heap
	//and then the heap is reordered from the bottom up.
	void push(const int idx)
	{
		assert (m_iSize+1 <= m_iMaxSize);

		++m_iSize;

		// 双向记录, 
		m_Heap[m_iSize] = idx;

		m_invHeap[idx] = m_iSize;

		ReorderUpwards(m_iSize);
	}
	
	

	//to get the min item the first element is exchanged with the lowest
	//in the heap and then the heap is reordered from the top down. 
	int pop()
	{
		Swap(1, m_iSize);

		ReorderDownwards(1, m_iSize-1);

		return m_Heap[m_iSize--];
	}

	//if the value of one of the client key's changes then call this with 
	//the key's index to adjust the queue accordingly
	void sort(const int idx)
	{
		// 由反向映射找到, 
		ReorderUpwards(m_invHeap[idx]);
	}


private:
	void Swap(int a, int b)
	{
		int temp = m_Heap[a]; m_Heap[a] = m_Heap[b]; m_Heap[b] = temp;

		//change the handles too
		m_invHeap[m_Heap[a]] = a; m_invHeap[m_Heap[b]] = b;
	}

	void ReorderUpwards(int nd)
	{
		// 把小值, 挪到最前边
		//move up the heap swapping the elements until the heap is ordered
		while ( (nd>1) &&  comp(m_Heap[nd/2], m_Heap[nd]))
		{      
			Swap(nd/2, nd);

			nd /= 2;
		}

	}

	void ReorderDownwards(int nd, int HeapSize)
	{
		//move down the heap from node nd swapping the elements until
		//the heap is reordered
		while (2*nd <= HeapSize)
		{
			int child = 2 * nd;

			//set child to smaller of nd's two children
			if ((child < HeapSize) && comp(m_Heap[child], m_Heap[child+1]))
			{
				++child;
			}

			//if this nd is larger than its child, swap
			if (comp(m_Heap[nd], m_Heap[child]))
			{
				Swap(child, nd);

				//move the current node down the tree
				nd = child;
			}

			else
			{
				break;
			}
		}
	}

private:

	int m_iSize, m_iMaxSize;
	std::vector<int> m_Heap;
	std::vector<int> m_invHeap;
	comPtr comp;
};

#endif // IndexedPriority_h__

