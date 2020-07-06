//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "list_stack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct Node{
	String data;
    Node *next;
    Node *prev;
}Node;

Node *head = new Node;
Node *tail = new Node;

void add(String input) {
    Node *node = new Node;
	node->data = input;
    Node *front = tail-> prev;
    front-> next = node;
    node-> prev = tail->prev;
    node-> next = tail;
    tail-> prev = node;
}
void remove() {
    if(head -> next == tail){
      ShowMessage("제거할 값이 없습니다");
      }
    else{
	Node *last = tail->prev;
    Node *fron = last-> prev;
    fron -> next = tail;
	tail->prev = last->prev;
    delete last;
    }
}
String Display(){
      String output;
      Node *cur = head->next;
      while(cur != tail) {
        output = output + cur->data + ", ";
        cur = cur->next;
      }
     return output;
}
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
    add(Input->Lines->Text);
    Output->Lines-> Add(Display());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_RemoveClick(TObject *Sender)
{
    remove();
    Output-> Lines-> Add(Display());
}

//---------------------------------------------------------------------------
