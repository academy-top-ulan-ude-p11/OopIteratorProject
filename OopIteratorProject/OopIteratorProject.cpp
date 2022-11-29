#include <iostream>
#include "Vector.h"
#include "ForwardList.h"

template <int N, int M>
class Matrix
{
    int matrix[N][M];
public:
};




template <typename T>
void PrintContainer(IIterator<T>* iter)
{
    for (iter->SetBegin(); !iter->IsEnd(); iter->Next())
        std::cout << iter->Current() << " ";
    std::cout << "\n";
}


template <typename T>
void SortConainer(IIterator<T>* iter)
{
    IIterator<T>* i = iter;
    for (i->SetBegin(); !i->IsEnd(); i->Next())
    {
        IIterator<T>* itMin = i;
        IIterator<T>* j = i;
        j->Next();
        for(j; !j->IsEnd(); j->Next())
        {
            if (j->Current() < itMin->Current())
            {
                itMin = j;
            }
        }
        T temp = i->Current();
        i->Current() = itMin->Current();
        itMin->Current() = temp;

        
    }
}


int main()
{
    srand(time(nullptr));

    Vector<int> vectInt;
    for (int i = 0; i < 10; i++)
        vectInt.PushBack(rand() % 100);

    for (int i = 0; i < 10; i++)
        std::cout << vectInt[i] << " ";
    std::cout << "\n";
    
    PrintContainer(vectInt.GetIterator());
    SortConainer(vectInt.GetIterator());
    PrintContainer(vectInt.GetIterator());

    ForwardList<int> listInt;

    for (int i = 0; i < 7; i++)
        listInt.Add(rand() % 100);

    for (int i = 6; i >= 0; i--)
        std::cout << listInt[i] << " ";
    std::cout << "\n";

    PrintContainer(listInt.GetIterator());
    

}
