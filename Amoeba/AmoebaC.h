//---------------------------------------------------------------------------

#ifndef AmoebaCH
#define AmoebaCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Spin.hpp"
#include <ExtCtrls.hpp>
#include "cxContainer.hpp"
#include "cxControls.hpp"
#include "cxEdit.hpp"
#include "cxGraphics.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "cxMaskEdit.hpp"
#include "cxSpinEdit.hpp"
#include "cxTextEdit.hpp"
//---------------------------------------------------------------------------
class TamoebaF : public TForm
{
__published:	// IDE-managed Components
	TImage *amr;
	TComboBox *area_size;
	TLabel *Label1;
	TButton *Button2;
	TMemo *Memo1;
	TButton *Button6;
	TImage *tube;
	TLabel *Steps;
	TSpinEdit *stepsedit;
	TLabel *fsdfsd;
	TEdit *currentstepedit;
	TSpinEdit *ctsearch;
	TLabel *Label2;
	TSpinEdit *foodDEdit;
	TLabel *Label3;
	TLabel *Label4;
	TcxSpinEdit *fp1v;
	TcxSpinEdit *fp2v;
	TLabel *Label5;
	TcxSpinEdit *fp3v;
	TLabel *Label6;
	TLabel *Label7;
	TcxSpinEdit *op1v;
	TcxSpinEdit *op2v;
	TLabel *Label8;
	TLabel *Label9;
	TcxSpinEdit *op3v;
	TLabel *Label10;
	TcxSpinEdit *conv;
	TLabel *Label11;
	TcxSpinEdit *pav;
	void __fastcall area_sizeChange(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall amrMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
	int ar_size;
	int prev_size;
	double ** MassA;
	double ** TubeM;
	long double ** MassB;
	long double ** FoodA;
	long double ** FoodB;
	long double ** FoodI;
	long double ** FoodD;
	long double ** A;
	double fp1;
	double fp2;
	double fp3;
	double op1;
	double op2;
	double op3;
	double CON;
	double PA;
	int stp;

public:		// User declarations
	__fastcall TamoebaF(TComponent* Owner);
	void __fastcall reinit();
	void __fastcall init();
	void __fastcall drawAmoeba();
	void __fastcall distMass();
	void __fastcall distMass1();
	void __fastcall normalizeMass();
	void __fastcall normalizeMass1();
	void __fastcall drawFood();
	void __fastcall drawTube();
	int __fastcall cPath(int x, int y , int count, int tvalue );

};
//---------------------------------------------------------------------------
extern PACKAGE TamoebaF *amoebaF;
//---------------------------------------------------------------------------
#endif
