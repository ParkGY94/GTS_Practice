//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "StopWatch_while.h"
#include "StopWatch_While_Class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
StopWatch *a= new StopWatch();
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_StartClick(TObject *Sender)
{
    BTN_Stop->Enabled = true;
    BTN_Reset->Enabled = true;
    BTN_Reset->Caption = "구간기록";
    a->isStop = false;
    a->isStop2 = false;
    while (a->isStop == false)
    {
        Sleep(10);
        a->DoEvents();
        if (a->GetHours() > 0)
        {
            Lab_hour->Caption = IntToStr(a->GetHours());
            label4->Caption = ":";
        }
        Lab_minute->Caption = IntToStr(a->GetMinutes());
        Lab_sec->Caption = IntToStr(a->GetSeconds());
        Lab_milisec->Caption = IntToStr(a->GetMiliseconds());
        a->IncreaseMilisec();
        if (a->GetRecordCount() > 0)
        {
            if (a->GetHours2() > 0)
            {
                Lab_hour2->Caption = IntToStr(a->GetHours2());
                label1->Caption = ":";
            }
            Lab_minute2->Caption = IntToStr(a->GetMinutes2());
            label2->Caption = ":";
            Lab_sec2->Caption = IntToStr(a->GetSeconds2());
            label3->Caption = ".";
            Lab_milisec2->Caption = IntToStr(a->GetMiliseconds2());
        }
        a->IncreaseMilisec2();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_StopClick(TObject *Sender)
{
    a->isStop = true;
    a->isStop2 = true;
    BTN_Reset->Caption = "초기화";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BTN_ResetClick(TObject *Sender)
{
    if (BTN_Reset->Caption == "초기화")
    {
        a->Reset_Click();
        Lab_hour->Caption = "";
        label4->Caption = "";
        Lab_hour2->Caption = "";
        label1->Caption = "";
        Lab_minute2->Caption = "";
        label2->Caption = "";
        Lab_sec2->Caption = "";
        label3->Caption = "";
        Lab_milisec2->Caption = "";
        Lab_Section->Caption = "";
        Lab_SectionRecord->Caption = "";
        Lab_Time->Caption = "";
        Text_Section->Text = "";
        Text_Section_Score->Text = "";
        Text_Time->Text = "";
        BTN_Reset->Enabled = false;
        BTN_Stop->Enabled = false;
        if (a->GetHours() > 0)
        {
            Lab_hour->Caption = IntToStr(a->GetHours());
            label4->Caption = ":";
        }
        Lab_minute->Caption = IntToStr(a->GetMinutes());
        Lab_sec->Caption = IntToStr(a->GetSeconds());
        Lab_milisec->Caption = IntToStr(a->GetMiliseconds());
    }
    else
    {
        Lab_Section->Caption = "구간";
        Lab_SectionRecord->Caption = "구간기록";
        Lab_Time->Caption = "전체시간";
        a->IncreaseRecordCount();
        Text_Section->Lines->Add(IntToStr(a->GetRecordCount()));
        if(a->GetHours2() > 0)
        {
            Text_Section_Score->Lines->Add(IntToStr(a->GetHours2()) + ":" + IntToStr(a->GetMinutes2())
            + ":" + IntToStr(a->GetSeconds2()) + "." + IntToStr(a->GetMiliseconds2()));
        }
        else
        {
            Text_Section_Score->Lines->Add(IntToStr(a->GetMinutes2()) + ":" + IntToStr(a->GetSeconds2())
            + "." + IntToStr(a->GetMiliseconds2()));
        }
        a->Record_Click();
        if (a->GetHours() > 0)
        {
            Text_Time->Lines->Add(Lab_hour->Caption + ":" + Lab_minute->Caption
             + ":" + Lab_sec->Caption + "." + Lab_milisec->Caption);
        }
        else
        {
            Text_Time->Lines->Add(Lab_minute->Caption + ":" + Lab_sec->Caption +
             "." + Lab_milisec->Caption);
        }
    }
}
//---------------------------------------------------------------------------
