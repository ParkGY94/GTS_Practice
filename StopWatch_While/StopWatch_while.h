//---------------------------------------------------------------------------

#ifndef StopWatch_whileH
#define StopWatch_whileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TLabel *Lab_hour;
    TLabel *label4;
    TLabel *Lab_minute;
    TLabel *Label5;
    TLabel *label6;
    TLabel *Lab_milisec;
    TLabel *Lab_sec;
    TLabel *Lab_hour2;
    TLabel *label1;
    TLabel *Lab_minute2;
    TLabel *label2;
    TLabel *Lab_sec2;
    TLabel *label3;
    TLabel *Lab_milisec2;
    TLabel *Lab_Section;
    TLabel *Lab_SectionRecord;
    TLabel *Lab_Time;
    TButton *BTN_Stop;
    TButton *BTN_Start;
    TButton *BTN_Reset;
    TMemo *Text_Section;
    TMemo *Text_Section_Score;
    TMemo *Text_Time;
    void __fastcall BTN_StartClick(TObject *Sender);
    void __fastcall BTN_StopClick(TObject *Sender);
    void __fastcall BTN_ResetClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
