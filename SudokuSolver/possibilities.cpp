#include "frame.cpp"
class Possibilities{

    struct node{
        int value;
        struct node* next;
    };
    typedef struct node* Node;

    Node head;
    Node pos;

    public:Possibilities(){
        head=new struct node;
        head->next=NULL;
    }

    public:~Possibilities(){
        destroy();
    }
    public:void append(int number){
        Node temp=new struct node;

        temp->value=number;
        temp->next=NULL;

        pos=head;
        while(pos!=NULL){
            if(pos->next==NULL){
                pos->next=temp;
                break;
            }
            pos=pos->next;
        }
    }
    public:int operator[](int index){
        int count=0;
        pos=head->next;

        while(pos!=NULL){
            if(count==index)
                return pos->value;
            pos=pos->next;
            count++;
        }

        return -1;
    }

    public:int length(){
        pos=head->next;
        int count=0;

        while(pos!=NULL){
            count++;
            pos=pos->next;
        }

        return count;
    }
    public:void copy(Possibilities possibilities){
        int oldLength=possibilities.length();
        int iter=0;

        pos=head;
        for(iter=0; iter<oldLength; iter++){
            Node temp=new struct node;

            temp->next=NULL;
            temp->value=possibilities[iter];

            pos->next=temp;
            pos=pos->next;
        }
    }

    private:void destroy(){
        Node temp;
        pos=head;
        while(pos!=NULL){
            temp=pos;
            pos=pos->next;
            delete temp;
        }
    }

};
