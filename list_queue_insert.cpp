//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "list_queue_insert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
class Node{
public:
	String data;
    Node *next;
    Node *prev;

    void insert(String indexnum, String input);
    void remove(String indexnum);
    String Display(Node *head);
};

Node *head = new Node();
Node *tail = new Node();
int NoI=0;

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    head-> prev = head;
    head-> next = tail;
    tail-> next = tail;
    tail-> prev = head;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_InsertClick(TObject *Sender)
{
    tail->insert(IndexNum->Lines->Text, Input->Lines->Text);
    Output->Lines -> Add(tail->Display(head));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_RemoveClick(TObject *Sender)
{
    head->remove(IndexNum->Lines->Text);
    Output->Lines -> Add(tail->Display(head));
}

void Node::insert(String indexnum, String input){
    int index = atoi(indexnum.c_str());
    if(index-1 <= NoI && index-1 >= 0){
        Node *node = new Node();
        node->data = input;
        Node *cur = head;
        for (int i = 0; i < index-1; i++){
            cur = cur->next;
        }
        node-> next = cur->next;
        cur-> next = node;
        node-> prev = cur;
        cur->next->prev = node;
        NoI++;
    }
    else{
        ShowMessage("인덱스를 다시 입력해 주세요.");
    }
}

void Node::remove(String indexnum) {
    //int index = StrToInt(indexnum);
    int index = atoi(indexnum.c_str());
    if(index-1 < NoI && index-1 >= 0){
         Node *cur = head;
        for (int i = 0; i < index-1; i++){
            cur = cur->next;
        }
        if(cur == head){
            if(index-1 == 0 && cur->next == tail){
                ShowMessage("제거할 값이 없습니다.");
              }
            else{
                Node *NtoC = cur-> next;
                cur-> next = NtoC-> next;
                NtoC->next->prev = cur;
                delete NtoC;
                NoI--;
                }
            }
        else{
        Node *NtoC = cur-> next;
        cur-> next = NtoC-> next;
        NtoC->next->prev = cur;
        delete NtoC;
        NoI--;
        }
    }
    else{
       ShowMessage("인덱스를 다시 입력해 주세요.");
    }
}

String Node::Display(Node *head){
      String output;
      Node *cur = head->next;
      while(cur != this) {
        output = output + cur->data + ", ";
        cur = cur->next;
      }
     return output;
    }
//---------------------------------------------------------------------------
