//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#include<stdlib.h>

#pragma hdrstop

#include "list.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

class Node{
    //Node(){prev = NULL; next = NULL; data = "0";}
public:
	String data;
    Node *next;
    Node *prev;

    void add(String input) {
    Node *node = new Node;
	node->data = input;
    Node *front = this->prev;
    front-> next = node;
    node-> prev = this->prev;
    node-> next = this;
    this->prev = node;
    }
    void remove(Node *head) {
    if(head -> next == this){
      ShowMessage("제거할 값이 없습니다");
      }
    else{
	Node *last = this->prev;
    Node *fron = last-> prev;
    fron -> next = this;
	this->prev = last->prev;
    delete last;
        }
    }
String Display(Node *head){
      String output;
      Node *cur = head->next;
      while(cur != this) {
        output = output + cur->data + ", ";
        cur = cur->next;
      }
     return output;
    }
};

Node *head = new Node();
Node *tail = new Node();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    head-> prev = head;
    head-> next = tail;
    tail-> next = tail;
    tail-> prev = head;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_AddClick(TObject *Sender)
{
    tail->add(Input->Lines->Text);
    Output->Lines -> Add(tail->Display(head));
}

//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_RemoveClick(TObject *Sender)
{
    tail->remove(head);
    Output->Lines -> Add(tail->Display(head));
}
//---------------------------------------------------------------------------



