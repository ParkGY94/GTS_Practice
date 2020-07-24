//---------------------------------------------------------------------------

#ifndef Thread1H
#define Thread1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Thread : public TThread
{
private:

protected:
    void __fastcall Execute();
public:
    __fastcall Thread(void);
    void __fastcall ShowStatus();
};
//---------------------------------------------------------------------------
#endif
