#include "doublelinkedlist.h"


using namespace std;

DoubleLinkedList::DoubleLinkedList(int maxSize)
{
    first=nullptr;
    last=nullptr;
    size=0;
    binarytree.resize(maxSize);
    this->maxSize=maxSize;
    loadFile();
}

DoubleLinkedList::Node *DoubleLinkedList::begin() const
{
    return first;
}

DoubleLinkedList::Node *DoubleLinkedList::end() const
{
    return last;
}

int DoubleLinkedList::getMaxsize() const
{
    return maxSize;
}

void DoubleLinkedList::deleteNV(QString title)
{
    DoubleLinkedList::iterator current;
    unsigned int old_position =static_cast<unsigned int>(search(title,current));
    qDebug()<<old_position;
    unsigned int current_position=old_position*2;
    if(binarytree[old_position*2].getPNode()==nullptr&&binarytree[old_position*2+1].getPNode()==nullptr)
    {
        binarytree[old_position].clear();
    }
    else if (binarytree[old_position*2+1].getPNode()==nullptr)
    {
        qDebug()<<"B";
        iterator info;
        if(searchPosition(0,old_position,current_position,info)==-1)
        {
            binarytree[old_position]=info;
        }
    }
    else if(binarytree[old_position*2].getPNode()==nullptr||binarytree[old_position*2+1].getPNode()!=nullptr)
    {
        qDebug()<<"A";
        iterator info;
        current_position++;
        if(searchPosition(1,old_position,current_position,info)==-1)
        {
            binarytree[old_position]=info;
        }
    }

}
int DoubleLinkedList::searchPosition(int direction,unsigned int parent,unsigned int child,iterator&info)
{
    qDebug()<<"ITERACION"<<parent<<" "<<child;
    if(binarytree[child].getPNode()==nullptr)
    {
        qDebug()<<"FIN";
        info=binarytree[parent];
        binarytree[parent]=binarytree[child];
        return 0;
    }
    if(direction==1&&binarytree[child*2].getPNode()!=nullptr)
    {
        qDebug()<<"A";
        info=binarytree[child*2];
        binarytree[child*2].clear();
        return -1;
    }
    if(direction==0&&binarytree[child*2+1].getPNode()!=nullptr)
    {
        qDebug()<<"B";
        info=binarytree[child*2+1];
        binarytree[child*2+1].clear();
        return -1;
    }
    if(searchPosition(direction,child,child*2+direction,info)==0)
    {
        qDebug()<<"C";
        iterator temp=info;
        info=binarytree[parent];
        binarytree[parent]=temp;
        return 0;
    }

    return -1;

}

bool DoubleLinkedList::push_back(Imagen_ a){
    unsigned int root=1;
    bool succes=false;
    Node*nuevo=new  Node(a);
    size++;
    if(first==nullptr){
        first=nuevo;
        last=nuevo;
        binarytree[1]=first;
        return true;
    }
    else{
        last->next=nuevo;
        nuevo ->previous=last;
        last=nuevo;
        first->previous=last;
        last->next=first;
        do
            {
                if(int(root)>maxSize)return false;
                if(binarytree[root].getPNode()==nullptr){
                    binarytree[root]=nuevo;
                    succes=true;
                }
                else if(a.title>(*binarytree[root]).getTitle()){
                    root=2*root+1;
                }

                else if(a.title<(*binarytree[root]).getTitle()){
                    root=2*root;
                }

            }while(!succes);
    }


}
int DoubleLinkedList::fsize(){
    return size;
}

void DoubleLinkedList::show(){
    Node *actual;
    if(first==nullptr)
    {
       qDebug()<<"LISTA VACIA"<<endl;
       return;
    }
    actual=first;
    qDebug()<<"Los elementos son"<<endl;
    qDebug() <<actual->dato.getTitle()<<endl;
    actual=actual->next;
    while(actual!=first){
        qDebug() <<actual->dato.getTitle()<<endl;
        actual=actual->next;
    }
    qDebug()<<endl;

}
int DoubleLinkedList::deleteN(DoubleLinkedList::iterator Element){
    Node*element =Element.getPNode();
    if(element==nullptr)return 0;
    size--;
    Node *actual=first,*temp;
    deleteNV((*Element).getTitle());
    if(element==first){
         if(size==0)
         {
            delete element;
             return 0;
         }
         first=first->next;
         first->previous=last;
         last->next=first;
         delete actual;
         return 1;
    }
     if(element==last){
         temp=last;
         actual=last->previous;
         actual->next=first;
         first->previous=actual;
         last=actual;
         delete temp;
         return 2;
    }
    element->previous->next=element->next;
    element->next->previous=element->previous;
    delete element;
    return 3;
}

void DoubleLinkedList::showAll(){
    Node*actual;
    actual=first;
    for(int i=0;i<this->fsize();i++){
       // cout<<"previousrior: "<<actual->previous->dato.titulo<<" Actual: "<<actual->dato.titulo<<" nextuiente: "<<actual->next->dato.titulo<<endl;

        actual= actual->next;


    }

}

int DoubleLinkedList::search(QString a,DoubleLinkedList::iterator&currentImage){
   unsigned int root=1;
   bool succes=false;
   do
   {
       if(int(root)>maxSize)return -2;
       if(binarytree[root].getPNode()==nullptr)
       {
            succes=true;
            return -1;
       }
       else if(a>(*binarytree[root]).getTitle())
       {
           root=2*root+1;
       }
       else if(a<(*binarytree[root]).getTitle())
       {
           root=2*root;
       }
       else if((*binarytree[root]).getTitle()==a)
       {
            succes=true;
            currentImage=binarytree[root];
            return int(root);
       }

   }while(!succes);

    return -1;

}

void DoubleLinkedList::showVector()
{
    qDebug()<<"---------";
    for(unsigned int i=1;i<10;i++){
        qDebug()<<i;
        if(binarytree[i].getPNode()==nullptr)continue;
        qDebug()<<(*binarytree[i]).getTitle();
    }

}

void DoubleLinkedList::loadFile()
{
    int tam;
    ifstream in("datos.txt");
    string line;
    getline(in,line);
    std::istringstream iss(line);
    iss >> tam;

    qDebug()<<"TAMAÑO"<<size;
    string title,ubication,tags;
    for(int i=0;i<tam;i++)
    {
        getline(in,title);
        getline(in,ubication);
        getline(in,tags);
        QPixmap image;
        bool valid =image.load(QString::fromStdString(ubication));
        if(valid)
        {
            Imagen_ image_(image.toImage(),
                           QString::fromStdString(title),
                           QString::fromStdString(tags)
                           ,QString::fromStdString(ubication));
            push_back(image_);
            qDebug()<<"INSERTADO";
        }
        else
        {
            qDebug()<<"FALLO";
        }
    }

}

void DoubleLinkedList::updateFile(Imagen_ image)
{
    fstream fichero;
    fichero.open("datos.txt",ios::in|ios::out);
    fichero.seekp(0);
    fichero<<size<<"\n";
    fichero.close();
    ofstream fichero2("datos.txt",ios::app);
    fichero2 << image.getTitle().toStdString()<<"\n"<<
                image.getPath().toStdString()<<"\n"<<
                image.getTags().toStdString() <<"\n";
    fichero2.close();
}

