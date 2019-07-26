#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <stdexcept>




template<class T>
class Container
{
private:
    class nodo{
    public:
        nodo() : element(new T), next(nullptr), prev(nullptr){}//done
        nodo(const T& tmp, nodo* nxt=nullptr, nodo* prv=nullptr) : element(tmp), next(nxt), prev(prv) {}//done
        nodo(const nodo& tmp) : element(tmp.element), next(tmp.next), prev(tmp.prev){}//done
        ~nodo(){//deve eliminare in profonditá, done
            if(next!=nullptr)
                delete next;
        }
        T element;
        nodo* next;
        nodo* prev;
    };
    nodo* first;
    nodo* last;
    int size;

public:
    Container() : first(nullptr), last(nullptr), size(0){}//done
    Container(const Container<T>&);//done
    ~Container()=default;
    void PushFront(const T&);//done
    void PushBack(const T&);//done
    void Insert(int i,const T&);//done
    void Remove(nodo*);//done
    void Remove(const int&);//done
    bool IsIn(const T&) const;//done
    int GetSize() const{return size;}//done
    nodo* GetNodoIndex(const int&) const;//done
    nodo* GetNodo(const T) const;//done
    int GetPos(nodo*) const;//done
    int GetPos(const T&) const;//done
    Container<T> operator=(const Container<T>&);//done
    Container<T> operator+(const Container<T>&);//done
    T& operator[](const int&) const;//done
};

template<class T>
Container<T>::Container(const Container<T>& cont){
    size=0;
    first=nullptr;
    last=nullptr;
    nodo* tmp=cont.first;
    while(size<=cont.size){
        this->PushBack(tmp->element);
        tmp=tmp->next;
    }
}

template<class T>
void Container<T>::PushFront(const T& tmp){
    if(size==0){
        first=new nodo(tmp);
        first->next=first;
        first->prev=first;
        last=first;
    }else{
        nodo* t=first;
        first=new nodo(tmp,t,last);
        t->prev=first;
        last->next=first;
    }
    ++size;
}

template<class T>
void Container<T>::PushBack(const T& tmp){
    if(size==0){
        this->PushFront(tmp);
    }else {
        ++size;
        last->next=new nodo(tmp,first,last);
        first->prev=last->next;
        last=last->next;
    }
}

template<class T>
void Container<T>::Remove(nodo* toremove){
    nodo* tmp=first;
    int i=0;
    for(i=0; i<size && tmp!=toremove; ++i){
        tmp=tmp->next;
    }
    Remove(i);
}

template<class T>
void Container<T>::Remove(const int& i){
    nodo* tmp=nullptr;
    if(i==0){
        tmp=first;
        if(size==1){
            first=nullptr;
            last=nullptr;
        }else{
            first=tmp->next;
            last->next=tmp->next;
        }
    }else if (i==size-1) {
        tmp=last;
        last=tmp->prev;
        last->next=first;
        first->prev=last;

    }else{
        tmp=GetNodoIndex(i);
        if(tmp->prev && tmp->next){
            tmp->prev->next=tmp->next;
            tmp->next->prev=tmp->prev;
        }
    }
    tmp->prev=nullptr;
    tmp->next=nullptr;
    delete tmp;
    --size;
}

template<class T>
void Container<T>::Insert(int i,const T& item)
{
    if(i>0 && i<size){
        nodo* old=GetNodoIndex(i);
        nodo* newnode=new nodo(item,old,old->prev);
        old->prev->next=newnode;
        old->prev=newnode;
        ++size;
    }else if(i==0){
        PushFront(item);
    }else if (i==size) {
        PushBack(item);
    }
}

template<class T>
bool Container<T>::IsIn(const T& tmpelement) const{
    nodo* tmp=first;
    for(int i=0; i<size; ++i){
        if(tmp->element==tmpelement)
            return true;
        tmp=tmp->next;
    }
    return false;
}

template<class T>
typename Container<T>::nodo* Container<T>::GetNodoIndex(const int& i) const{
    nodo* tmp=first;
    for(int k=0; k<size && k<i; ++k)
        tmp=tmp->next;
    return tmp;
}

template<class T>
typename Container<T>::nodo* Container<T>::GetNodo(const T i) const{
    nodo* tmp=first;
    int k=0;
    for(k=0; k<size && !(tmp->element==i); ++k)
        tmp=tmp->next;
    if(k==size)
        return nullptr;
    return tmp;
}

template<class T>
int Container<T>::GetPos(nodo* i) const{
    nodo* tmp=first;
    int k;
    for(k=0; k<size && tmp!=i; ++k)
        tmp=tmp->next;
    return k;
}

template<class T>
int Container<T>::GetPos(const T& i) const{
    nodo* tmp=first;
    int k=0;
    for(k=0; k<size && tmp->element!=i; ++k){
        tmp=tmp->next;
    }
    return k;
}

template<class T>
Container<T> Container<T>::operator=(const Container<T>& cont){
    if(first)
        delete first;
    first=nullptr;
    size=0;
    nodo* tmp=cont.first;
    while(size<cont.size){
        this->PushBack(tmp->element);
        tmp=tmp->next;
    }
    if(size>0)
        first->prev=GetNodoIndex(size-1);
    return *this;
}

template<class T>//concatena alla prima la seconda
Container<T> Container<T>::operator+(const Container<T>& cont){
    nodo* last=GetNodoIndex(size-1);
    size+=cont.size;
    last->next=cont.first;
    GetNodoIndex(size-1)->next=first;
    return *this;
}

template<class T>
T& Container<T>::operator[](const int& i) const{
    nodo* tmp=first;
    int k;
    for(k=0; k<size && k<i; ++k)
        tmp=tmp->next;
    if(k==size)
        return last->element;
    return tmp->element;
}


#endif // CONTAINER_H
