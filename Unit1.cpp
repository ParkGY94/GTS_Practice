//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
class Node{
    //Node(){prev = NULL; next = NULL; data = "0";}
public:
	float data;
    Node *next;
    Node *prev;

    void Push(float input) {
        Node *node = new Node;
        node->data = input;
        Node *front = this->prev;
        front-> next = node;
        node-> prev = this->prev;
        node-> next = this;
        this->prev = node;
    }
    float Pop(Node *head) {
        if(head -> next == this){
          ShowMessage("제거할 값이 없습니다");
          return 0;
          }
        else{
        Node *last = this->prev;
        float last_data = last->data;
        Node *fron = last-> prev;
        fron -> next = this;
        this->prev = last->prev;
        delete last;
        return last_data;
        }
    }
};
Node *head = new Node();
Node *tail = new Node();

TStringList *list = new TStringList;
TStringList *listExp = new TStringList;
TStringList *stack = new TStringList;
String Input_ = "";
int pointNum = 0;
float savedNum = 0;
float recentNum = 0;
int count = 0;
bool Iscalc = false;
bool Ispercent = false;
int sqr_ = 0;
bool isresult = false;

void Plus()
{
    list->Add(Input_);
    list->Add(" + ");
    /*store->Lines->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Lines->Add(list->operator [](i);
    }*/
}
void Minus()
{
    list->Add(Input_);
    list->Add(" - ");
}
void Multi()
{
    list->Add(Input_);
    list->Add(" X ");
}
void Div()
{
    list->Add(Input_);
    list->Add(" ÷ ");
}
int Get_weight(String oper)
{
    if (oper == " X " || oper == " ÷ ")
    {
        return 2;
    }
    else
        return 1;
}
void Convert_to_postfix()
{
    for (int i = 0; i < list->Count; i++)
    {
        if (list->operator [](i) == " + " || list->operator [](i) == " - " || list->operator [](i) == " X " || list->operator [](i) == " ÷ ")
        {
            if (stack->Count == 0)
            {
                stack->Add(list->operator [](i));
            }
            else
            {
                if (Get_weight(list->operator [](i)) > Get_weight(stack->operator [](stack->Count-1)))
                {
                    stack->Add(list->operator [](i));
                }
                else
                {
                    for (int j = 0; j< stack->Count; j++)
                    {
                        if(Get_weight(list->operator [](i))<= Get_weight(stack->operator [](stack->Count-1)))
                        {
                            listExp->Add(stack->operator [](stack->Count-1));
                            stack->Delete(stack->Count-1);
                            j--;
                        }
                        else
                        {
                            stack->Add(list->operator [](i));
                            break;
                        }
                    }
                    if(stack->Count == 0)
                    {
                        stack->Add(list->operator [](i));
                    }
                }
            }
        }
        else
        {
            listExp->Add(list->operator [](i));
        }
    }
    while(stack->Count > 0 )
    {
        listExp->Add(stack->operator [](stack->Count-1));
        stack->Delete(stack->Count-1);
    }
}
float clac(float num1, float num2, String oper)
{
    if(oper == " + ") return num1 + num2;
    else if (oper == " - ") return num1 - num2;
    else if (oper == " X ") return num1 * num2;
    else if (oper == " ÷ ") return num1 / num2;
    else return 0;
}
void calculate()
{
    for (int i = 0; i< listExp->Count; i++)
    {
        if (listExp->operator [](i)== " + " || listExp->operator [](i) == " - "
        || listExp->operator [](i) == " X " || listExp->operator [](i) == " ÷ ")
        {
            float Num2;
            Num2 = tail->Pop(head);
            float Num1;
            Num1 = tail->Pop(head);
            tail->Push(clac(Num1, Num2, listExp->operator [](i)));
        }
        else
        {
            tail->Push(StrToFloat(listExp->operator [](i)));
        }
    }
    savedNum = tail->Pop(head);
}
void Clear()
{
    Input_ = "";
    //store->Lines->Text = "";
    count = 0;
    list->Clear();
    pointNum = 0;
    savedNum = 0;
    recentNum = 0;
    Input_ = "";
    Iscalc = true;
    Ispercent = false;
    isresult = false;
    sqr_ = 0;
    //Output->Lines->Text = "0";
}

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_NumClick(TObject *Sender)
{
    if (isresult == true)
    {
        Clear();
    }
    if (Output->Lines->Text == "0" || Iscalc == true)
    {
        Input_ = "";
        Iscalc = false;
    }
    if (sqr_ > 0)
    {
        recentNum = 0;
        Input_ = "";
        sqr_ = 0;
    }
    /*if (Ispercent == true)
    {
        recentNum = 0;
        Input_ = "";
        Ispercent = false;
        list.RemoveAt(list.Count - 1);
    }*/
    TButton *b = (TButton*) Sender;
    Input_ = Input_.operator +(IntToStr(b->Tag));
    if (Input_ == "") { Input_ = "0"; }
    Output->Lines->Text = Input_;
    recentNum = StrToFloat(Input_);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_clacClick(TObject *Sender)
{
    if (isresult == true)
    {
        recentNum = savedNum;
        Input_ = FloatToStr(recentNum);
        Output->Lines->Text = Input_;
        isresult = false;
    }
    if (Iscalc == true)
    {
        return;
    }
    TButton *b = (TButton*) Sender;
    if(b->Caption == "+") Plus();
    else if (b->Tag == 11) Minus();
    else if (b->Tag == 12) Multi();
    else Div();
    Input_ = "";
    store->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
    Iscalc = true;
    Output->Lines->Text = FloatToStr(savedNum);
    count++;
    sqr_ = 0;
    pointNum = 0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_SignClick(TObject *Sender)
{
    if (Input_ == "0")
    {
        return;
    }
    else
    {
        recentNum = -recentNum;
        Input_ = FloatToStr(recentNum);
    }
    Output->Lines->Text = Input_;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ResultClick(TObject *Sender)
{
    if (list->Count % 2 == 0)
    {
        list->Add(Input_);
    }
    Convert_to_postfix();

    calculate();
    list->Add(" = ");
    Input = "";
    store->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
    /*for(int i = 0; i < listExp->Count; i++)
    {
        store->Text= store->Text + (listExp->operator [](i));
    }*/
    Output->Lines->Text = FloatToStr(savedNum);
    recentNum = savedNum;
    isresult = true;
    list->Clear();
    Iscalc = false;
    pointNum = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_PointClick(TObject *Sender)
{
    if (pointNum == 0)
    {
        if (Input_ == "" || isresult == true)
        {
            Input_ = "0";
            isresult = false;
        }
        Input_ = Input_ + ".";
        Output->Lines->Text = Input_;
        pointNum++;
    }
    else  return;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ClearClick(TObject *Sender)
{
    Clear();
    store->Text = "";
    Output->Lines->Text = "0";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_RemoveClick(TObject *Sender)
{
    if (Ispercent == true)
    {
        return;
    }
    if (sqr_ > 0)
    {
        return;
    }
    if (Input_.Length() == 0)
    {
        return;
    }
    else
    {
        if (Input_.Length() == 1)
        {
            Input_ = "";
        }
        else
        {
            Input_ = Input_.Delete(Input_.Length() - 1,1);
        }
    }
    if (Input_ == "")
    {
        recentNum = 0;
    }
    else
    {
        recentNum = StrToFloat(Input_);
    }
    if (Input_ == "")
    {
        Output->Lines->Text = "0";
    }
    else
    {
        Output->Lines->Text = Input_;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ClearRecentClick(TObject *Sender)
{
    if (isresult == true) { savedNum = 0; }
    Input_ = "";
    Output->Text = "0";
    recentNum = 0;
    pointNum = 0;
    Ispercent = false;
    sqr_ = 0;
    isresult = false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_SquareClick(TObject *Sender)
{
    if (Input_ == "") { Input_ = "0"; }
    recentNum = pow(recentNum,2);
    Input_ = FloatToStr(recentNum);
    Output->Text = Input_;
    sqr_++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_RootClick(TObject *Sender)
{
    if (Input_ == "") { Input_ = "0"; }
    recentNum = sqrt(recentNum);
    Input_ = FloatToStr(recentNum);
    Output->Text = Input_;
    sqr_++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_InverseClick(TObject *Sender)
{
    if (Input_ == "") { Input_ = "0"; }
    recentNum = 1/recentNum;
    Input_ = FloatToStr(recentNum);
    //list->Add(Input_);
    Output->Text = Input_;
    sqr_++;
}
//---------------------------------------------------------------------------

