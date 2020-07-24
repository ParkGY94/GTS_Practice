//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Calculator_Last.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
class Node{
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
int Paren_O = 0;
int Paren_C = 0;
bool isdecimal = true;
bool isbinary = false;
bool ishexadecimal = false;
bool isParen_C = false;

String IntToBinStr(int a){
    String Output = "";
    while(a > 0){
    Output = IntToStr(a%2).operator +(Output);
    a = a/2;
    }
    return Output;
}
String IntToHexStr(int a){
    String Output = "";
    while (a>0){
        String rest ="";
        if(a%16 == 10)
        {
            rest= "A";
        }
        else if(a%16==11)
        {
            rest="B";
        }
        else if(a%16==12)
        {
            rest="C";
        }
        else if(a%16==13)
        {
            rest="D";
        }
        else if(a%16==14)
        {
            rest="E";
        }
        else if(a%16==15)
        {
            rest="F";
        }
        else
        {
            rest = IntToStr(a%16);
        }
        Output = rest.operator +(Output);
        a = a/16;
    }
    return Output;
}
float BinStrToFloat(String c){
    float d = 0;
    for (int i = c.Length(); i > 0; i--){
        d += StrToInt(c.operator [](c.Length()-i+1))*pow(2,i-1);
    }
    return d;
}
float HexStrToFloat(String c){
    float d = 0;
    char ch;
    for (int i = c.Length(); i > 0; i--){
        ch = c.operator [](c.Length()-i+1);
        if(ch == 'A')
        {
            d += 10*pow(16,i-1);
        }
        else if(ch == 'B')
        {
            d += 11*pow(16,i-1);
        }
        else if(ch == 'C')
        {
            d += 12*pow(16,i-1);
        }
        else if(ch == 'D')
        {
            d += 13*pow(16,i-1);
        }
        else if(ch == 'E')
        {
            d += 14*pow(16,i-1);
        }
        else if(ch == 'F')
        {
            d += 15*pow(16,i-1);
        }
        else{
            d += StrToInt(c.operator [](c.Length()-i+1))*pow(16,i-1);
        }
    }
    return d;
}
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
        return 3;
    else if (oper == " + " || oper == " - ")
        return 2;
    else if (oper == "(")
        return 1;
    else
        return -1;
}
void Convert_to_postfix()
{
    for (int i = 0; i < list->Count; i++)
    {
        if (list->operator [](i) == " + " || list->operator [](i) == " - " || list->operator [](i) == " X "
        || list->operator [](i) == " ÷ " || list->operator [](i) == "(" || list->operator [](i) == ")")
        {
            if (stack->Count == 0 || list->operator [](i) == "(")
            {
                stack->Add(list->operator [](i));
            }
            else if (list->operator [](i) == ")")
            {
                String op = stack->operator [](stack->Count-1);
                stack->Delete(stack->Count-1);
                while (op != "(")
                {
                    listExp->Add(op);
                    op = stack->operator [](stack->Count-1);
                    stack->Delete(stack->Count-1);
                }
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
        else if (listExp->operator [](i) == "") { }
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
    Paren_O = 0;
    Paren_C = 0;
    isParen_C = false;
    //Output->Lines->Text = "0";
}

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
    Output->Lines->Text = "0";
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
void __fastcall TForm1::BTN_NumClick(TObject *Sender)
{
    if(isParen_C == true)
    {
        return;
    }
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
    Input_ = Input_.operator +(b->Caption);
    if (Input_ == "") { Input_ = "0"; }
    Output->Lines->Text = Input_;
    if (isdecimal == true)
    {
        recentNum = StrToFloat(Input_);
    }
    if (isbinary == true)
    {
        recentNum = BinStrToFloat(Input_);
    }
    if (ishexadecimal == true)
    {
        recentNum = HexStrToFloat(Input_);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ClacClick(TObject *Sender)
{
    if (isresult == true)
    {
        recentNum = savedNum;
        if(isbinary == true)
        {
            Input_ = IntToBinStr((int)recentNum);
        }
        if (isdecimal == true)
        {
            Input_ = FloatToStr(recentNum);
        }
        if (ishexadecimal == true)
        {
            Input_ = IntToHexStr((int)recentNum);
        }
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
    //Output->Lines->Text = FloatToStr(savedNum);
    count++;
    sqr_ = 0;
    pointNum = 0;
    isParen_C = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ResultClick(TObject *Sender)
{
    if (Paren_C != Paren_O)
    {
        ShowMessage("수식이 정확한지 확인해주세요");
        return;
    }
    if (list->operator [](list->Count-1) == " + " || list->operator [](list->Count-1) == " - "
    || list->operator [](list->Count-1) == " X " || list->operator [](list->Count-1) == " ÷ ")
    {
        if (Input_ == "")
        {
            return;
        }
        list->Add(Input_);
    }
    store->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
    store->Text = store->Text + " = ";
    if (isbinary == true)
    {
        TStringList *iBase10 = new TStringList;
        for(int i = 0; i < list->Count; i++)
        {
            if (list->operator [](i) != " + " && list->operator [](i) != " - " && list->operator [](i) != " X "
            && list->operator [](i) != " ÷ " && list->operator [](i) != "(" && list->operator [](i) != ")")
            {
                iBase10->Add(FloatToStr(BinStrToFloat(list->operator [](i))));
            }
        }
        for (int i = 0; i < list->Count; i++)
        {
            if(list->operator [](i) != " + " && list->operator [](i) != " - " && list->operator [](i) != " X "
            && list->operator [](i) != " ÷ " && list->operator [](i) != "(" && list->operator [](i) != ")")
            {
                list->Delete(i);
                list->Insert(i, iBase10->operator [](0));
                iBase10->Delete(0);
            }
        }
    }
    if (ishexadecimal == true)
    {
        TStringList *iBase10 = new TStringList;
        for (int i = 0; i < list->Count; i++)
        {
            if (list->operator [](i) != " + " && list->operator [](i) != " - " && list->operator [](i) != " X "
            && list->operator [](i) != " ÷ " && list->operator [](i) != "(" && list->operator [](i) != ")")
            {
                iBase10->Add(FloatToStr(HexStrToFloat(list->operator [](i))));
            }
        }
        for (int i = 0; i < list->Count; i++)
        {
            if (list->operator [](i) != " + " && list->operator [](i) != " - " && list->operator [](i) != " X "
            && list->operator [](i) != " ÷ " && list->operator [](i) != "(" && list->operator [](i) != ")")
            {
                list->Delete(i);
                list->Insert(i, iBase10->operator [](0));
                iBase10->Delete(0);
            }
        }
    }
    Convert_to_postfix();
    calculate();
    Input_ = "";
    if (isbinary == true)
    {
        Output->Lines->Text = IntToBinStr((int)savedNum);
    }
    if (ishexadecimal == true)
    {
        Output->Lines->Text = IntToHexStr((int)savedNum);
    }
    if (isdecimal == true)
    {
        Output->Lines->Text = FloatToStr(savedNum);
    }
    /*for(int i = 0; i < listExp->Count; i++)
    {
        store->Text= store->Text + (listExp->operator [](i));
    }*/
    recentNum = savedNum;
    isresult = true;
    list->Clear();
    Iscalc = false;
    pointNum = 0;
    Paren_O = 0;
    Paren_C = 0;
}
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
void __fastcall TForm1::BTN_RootClick(TObject *Sender)
{
    if (Input_ == "") { Input_ = "0"; }
    recentNum = sqrt(recentNum);
    Input_ = FloatToStr(recentNum);
    Output->Text = Input_;
    sqr_++;
}
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
void __fastcall TForm1::BTN_ClearClick(TObject *Sender)
{
    Clear();
    store->Text = "";
    Output->Lines->Text = "0";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_PercentClick(TObject *Sender)
{
    if (Iscalc == true)
    {
        return;
    }
    if (Input_ == "") { Input_ = "0"; }
    recentNum = recentNum/100;
    Input_ = FloatToStr(recentNum);
    //list->Add(Input_);
    Output->Text = Input_;
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_DecimalClick(TObject *Sender)
{
    if(isbinary == true)
    {
        if (Output->Text != "0")
        {
            Input_ = FloatToStr(BinStrToFloat(Output->Text));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    if (ishexadecimal == true)
    {
        if (Output->Text != "0")
        {
            Input_ = FloatToStr(HexStrToFloat(Output->Text));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    isdecimal = true;
    isbinary = false;
    ishexadecimal = false;
    BTN_2->Enabled = true;
    BTN_3->Enabled = true;
    BTN_4->Enabled = true;
    BTN_5->Enabled = true;
    BTN_6->Enabled = true;
    BTN_7->Enabled = true;
    BTN_8->Enabled = true;
    BTN_9->Enabled = true;
    BTN_A->Enabled = false;
    BTN_B->Enabled = false;
    BTN_C->Enabled = false;
    BTN_D->Enabled = false;
    BTN_E->Enabled = false;
    BTN_F->Enabled = false;
    BTN_Point->Enabled = true;
    BTN_Percent->Enabled = true;
    BTN_Inverse->Enabled = true;
    BTN_Root->Enabled = true;
    BTN_Square->Enabled = true;
    BTN_Decimal->Enabled = false;
    BTN_Binary->Enabled = true;
    BTN_Hexadecimal->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_BinaryClick(TObject *Sender)
{
    if (savedNum != (int)savedNum || recentNum !=(int)recentNum)
    {
        ShowMessage("소수값은 변환할 수 없습니다.");
        return;
    }
    if (isdecimal == true)
    {
        if (Output->Text != "0")
        {
            Input_ = IntToBinStr(StrToInt(Output->Text));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    if (ishexadecimal == true)
    {
        if (Output->Text != "0")
        {
            Input_ = IntToBinStr((int)(HexStrToFloat(Output->Text)));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    isdecimal = false;
    isbinary = true;
    ishexadecimal = false;
    BTN_2->Enabled = false;
    BTN_3->Enabled = false;
    BTN_4->Enabled = false;
    BTN_5->Enabled = false;
    BTN_6->Enabled = false;
    BTN_7->Enabled = false;
    BTN_8->Enabled = false;
    BTN_9->Enabled = false;
    BTN_A->Enabled = false;
    BTN_B->Enabled = false;
    BTN_C->Enabled = false;
    BTN_D->Enabled = false;
    BTN_E->Enabled = false;
    BTN_F->Enabled = false;
    BTN_Point->Enabled = false;
    BTN_Percent->Enabled = false;
    BTN_Inverse->Enabled = false;
    BTN_Root->Enabled = false;
    BTN_Square->Enabled = false;
    BTN_Decimal->Enabled = true;
    BTN_Binary->Enabled = false;
    BTN_Hexadecimal->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_HexadecimalClick(TObject *Sender)
{
    if (savedNum != (int)savedNum || recentNum !=(int)recentNum)
    {
        ShowMessage("소수값은 변환할 수 없습니다.");
        return;
    }
    if (isdecimal == true)
    {
        if (Output->Text != "0")
        {
            Input_ = IntToHexStr(StrToInt(Output->Text));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    if (isbinary == true)
    {
        if (Output->Text != "0")
        {
            Input_ = IntToHexStr((int)(BinStrToFloat(Output->Text)));
            Output->Text = Input_;
            store->Text = "";
        }
    }
    isdecimal = false;
    isbinary = false;
    ishexadecimal = true;
    BTN_2->Enabled = true;
    BTN_3->Enabled = true;
    BTN_4->Enabled = true;
    BTN_5->Enabled = true;
    BTN_6->Enabled = true;
    BTN_7->Enabled = true;
    BTN_8->Enabled = true;
    BTN_9->Enabled = true;
    BTN_A->Enabled = true;
    BTN_B->Enabled = true;
    BTN_C->Enabled = true;
    BTN_D->Enabled = true;
    BTN_E->Enabled = true;
    BTN_F->Enabled = true;
    BTN_Point->Enabled = false;
    BTN_Percent->Enabled = false;
    BTN_Inverse->Enabled = false;
    BTN_Root->Enabled = false;
    BTN_Square->Enabled = false;
    BTN_Decimal->Enabled = true;
    BTN_Binary->Enabled = true;
    BTN_Hexadecimal->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_Parenthesis_OpenClick(TObject *Sender)
{
    if (Iscalc == false && list->Count != 0)
    {
        return;
    }
    if (isresult == true)
    {
        Clear();
    }
    list->Add("(");
    Paren_O++;
    Input_ = "";
    store->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
    Output->Text = FloatToStr(savedNum);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BTN_Parenthesis_CloseClick(TObject *Sender)
{
    if (Iscalc == true || Paren_C >= Paren_O)
    {
        return;
    }
    if (isresult == true)
    {
        Clear();
    }
    list->Add(Input_);
    list->Add(")");
    Paren_C++;
    isParen_C = true;
    Input_ = "";
    store->Text = "";
    for(int i = 0; i < list->Count; i++)
    {
        store->Text= store->Text + (list->operator [](i));
    }
    Output->Text = FloatToStr(savedNum);
}
//---------------------------------------------------------------------------

