//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AmoebaC.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Spin"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxEdit"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMaskEdit"
#pragma link "cxSpinEdit"
#pragma link "cxTextEdit"
#pragma resource "*.dfm"
TamoebaF *amoebaF;
//---------------------------------------------------------------------------
__fastcall TamoebaF::TamoebaF(TComponent* Owner)
	: TForm(Owner)
{
	ar_size = area_size->Text.ToInt();
	init();



	amr->Canvas->Brush->Color = clBlack;
	amr->Canvas->FillRect(Rect(0,0,400,400));
	tube->Canvas->Brush->Color = clBlack;
	tube->Canvas->FillRect(Rect(0,0,400,400));


}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::area_sizeChange(TObject *Sender)
{
	prev_size = ar_size;
	ar_size = area_size->Text.ToInt();
}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::reinit()
{

  	for (int i = 0; i < prev_size; i++) {
		delete[] MassA[i];
		delete[] MassB[i];
		delete[] FoodA[i];
		delete[] FoodB[i];
		delete[] FoodD[i];
		delete[] A[i];
		delete[] FoodI[i];
		delete[] TubeM[i];
	}
	delete[] MassA;
	delete[] MassB;
	delete[] FoodA;
	delete[] FoodB;
	delete[] FoodD;
	delete[] A;
	delete[] FoodI;
	delete[] TubeM;

	MassA = new double*[ar_size];
	MassB = new long double*[ar_size];
	FoodA = new long double*[ar_size];
	FoodB = new long double*[ar_size];
	FoodD = new long double*[ar_size];
	A = new long double*[ar_size];
	FoodI = new long double*[ar_size];
	TubeM = new double*[ar_size];

	for (int i = 0; i < ar_size; i++) {
		MassA[i] = new double[ar_size];
		MassB[i] = new long double[ar_size];
		FoodA[i] = new long double[ar_size];
		FoodB[i] = new long double[ar_size];
		FoodD[i] = new long double[ar_size];
		A[i] = new long double[ar_size];
		FoodI[i] = new long double[ar_size];
		TubeM[i] = new double[ar_size];
	}

	for (int i = 0 ; i < ar_size; i++) {
		for (int j = 0 ; j < ar_size; j++) {
			MassA[i][j] = 0;
			MassB[i][j] = 0;
			FoodA[i][j] = 0;
			FoodB[i][j] = 0;
			FoodD[i][j] = 0;
			A[i][j] = 0;
			FoodI[i][j] = 0;
			TubeM[i][j] = 0;
		}
	}

	for (int i = 1 ; i < ar_size-1; i++) {
		for (int j = 1 ; j < ar_size-1; j++) {
			MassA[i][j] = 1;
			MassB[i][j] = 0;
			FoodA[i][j] = 0;
			FoodB[i][j] = 0;
			FoodD[i][j] = 0;
			A[i][j] = 0;
			FoodI[i][j] = 0;
			TubeM[i][j] = 0;

		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::init()
{

	MassA = new double*[ar_size];
	MassB = new long double*[ar_size];
	FoodA = new long double*[ar_size];
	FoodB = new long double*[ar_size];
	FoodD = new long double*[ar_size];
	A = new long double*[ar_size];
	FoodI = new long double*[ar_size];
	TubeM = new double*[ar_size];


	for (int i = 0; i < ar_size; i++) {
		MassA[i] = new double[ar_size];
		MassB[i] = new long double[ar_size];
		FoodA[i] = new long double[ar_size];
		FoodB[i] = new long double[ar_size];
		FoodD[i] = new long double[ar_size];
		A[i] = new long double[ar_size];
		FoodI[i] = new long double[ar_size];
		TubeM[i] = new double[ar_size];
	}

    for (int i = 0 ; i < ar_size; i++) {
		for (int j = 0 ; j < ar_size; j++) {
			MassA[i][j] = 0;
			MassB[i][j] = 0;
			FoodA[i][j] = 0;
			FoodB[i][j] = 0;
			FoodD[i][j] = 0;
			A[i][j] = 0;
			FoodI[i][j] = 0;
			TubeM[i][j] = 0;
		}
	}

	for (int i = 1 ; i < ar_size-1; i++) {
		for (int j = 1 ; j < ar_size-1; j++) {
			MassA[i][j] = 1;
			MassB[i][j] = 0;
			FoodA[i][j] = 0;
			FoodB[i][j] = 0;
			FoodD[i][j] = 0;
			A[i][j] = 0;
			FoodI[i][j] = 0;
			TubeM[i][j] = 0;

		}
	}

}

//---------------------------------------------------------------------------
void __fastcall TamoebaF::drawAmoeba()
{
	amr->Canvas->Brush->Color = clBlack;
	amr->Canvas->FillRect(Rect(0,0,400,400));
	int step = 400/ar_size;

	//Find table max
	double max = -1;
	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {
			if (MassA[i][j]>max) {
				max = MassA[i][j];
			}
		}
	}

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {
		   /*	if (MassA[i][j]/max<0.5) {
				amr->Canvas->Brush->Color = (255*(MassA[i][j]/max)*1.2);
			}
			else*/
			amr->Canvas->Brush->Color = (255*(MassA[i][j]/max));
			amr->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));

		}
	}

	//drawTube();
}
//---------------------------------------------------------------------------
int __fastcall TamoebaF::cPath(int x , int y , int count , int tvalue)
{
// tvalue is the different value we set on TubeM depending on the food source we started
// the path from.

	double max=-1;
	int max_i=-1,max_j=-1;

	TubeM[x][y] = tvalue;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (TubeM[x+i][y+j] > 0 && TubeM[x+i][y+j] != tvalue) {
				return 0;
			}
			if (TubeM[x+i][y+j] != tvalue) {
				if(MassA[x+i][y+j] > max)
				{
					max = MassA[x+i][y+j];
					max_i = x+i;
					max_j = y+j;
				}
			}
		}
	}

	if (!(max_i == -1 || max_j == -1 ) && count < ctsearch->Value) {
		cPath(max_i , max_j , ++count , tvalue);
	}
}
//---------------------------------------------------------------------------

void __fastcall TamoebaF::drawTube()
{

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {
			TubeM[i][j] = 0;
		}

	}

	int n=1;                        //------thetei to kathe tvalue iso me n++
	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {
			if(FoodI[i][j] == 100)
				cPath(i,j,0,n++);
		}
	}





	tube->Canvas->Brush->Color = clBlack;
	tube->Canvas->FillRect(Rect(0,0,400,400));
	int step = 400/ar_size;


	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (TubeM[i][j]>0) {


				tube->Canvas->Brush->Color = 0x000000FF;
				tube->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));
			}
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::Button2Click(TObject *Sender)
{

	reinit();
	drawAmoeba();
	drawFood();

}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::amrMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{

	if (Button == mbLeft) {
		int step = 400/ar_size;
		if (!( X/step<1 || Y/step<1 || X/step>=ar_size-1 || Y/step>=ar_size-1))
		{
			FoodA[X/step][Y/step] = 100;
			FoodI[X/step][Y/step] = 100;
			drawFood();
		}
	}

	if (Button == mbRight) {
		int step = 400/ar_size;
		if (!( X/step<1 || Y/step<1 || X/step>=ar_size-1 || Y/step>=ar_size-1))
		{
			FoodD[X/step][Y/step] = foodDEdit->Value;
			FoodI[X/step][Y/step] = foodDEdit->Value;
			drawFood();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::drawFood()
{

	int step = 400/ar_size;


	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (FoodA[i][j] == 100) {
				amr->Canvas->Brush->Color = clGreen;
				amr->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));
				tube->Canvas->Brush->Color = clGreen;
				tube->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));

			}

			if (FoodD[i][j] == foodDEdit->Value) {
				amr->Canvas->Brush->Color = clYellow;
				amr->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));
				tube->Canvas->Brush->Color = clYellow;
				tube->Canvas->FillRect(Rect(i*step,j*step,(i*step)+step,(j*step)+step));
			}
		}
	}

	tube->Repaint();
	amr->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::distMass1()
{

	double N = 0;
	double S = 0;
	double W = 0;
	double E = 0;
	double NW = 0;
	double NE = 0;
	double SW = 0;
	double SE = 0;

	fp1=double(fp1v->Value);
	fp2=double(fp2v->Value);
	fp3=double(fp3v->Value);
	op1=double(op1v->Value);
	op2=double(op2v->Value);
	op3=double(op3v->Value);
	CON=double(conv->Value);
	PA=double(pav->Value);


	for (int i = 1; i < ar_size-1; i++) {
		for (int j = 1; j < ar_size-1; j++) {

			N = 0;
			S = 0;
			W = 0;
			E = 0;
			NW = 0;
			NE = 0;
			SW = 0;
			SE = 0;

					if (FoodA[i-1][j]>0.5 && FoodA[i-1][j]>FoodA[i-1][j-1] && FoodA[i-1][j]>FoodA[i-1][j+1] && FoodA[i-1][j]>FoodA[i][j-1] && FoodA[i-1][j]>FoodA[i][j+1] && FoodA[i-1][j]>FoodA[i+1][j-1] && FoodA[i-1][j]>FoodA[i+1][j] && FoodA[i-1][j]>FoodA[i+1][j+1])
					{
						N = -PA;
						S = PA;
					}


					if (FoodA[i+1][j]>0.5 && FoodA[i+1][j]>FoodA[i-1][j-1] && FoodA[i+1][j]>FoodA[i-1][j] && FoodA[i+1][j]>FoodA[i-1][j+1] && FoodA[i+1][j]>FoodA[i][j-1] && FoodA[i+1][j]>FoodA[i][j+1] && FoodA[i+1][j]>FoodA[i+1][j-1] && FoodA[i+1][j]>FoodA[i+1][j+1])
					{
						N = PA;
						S = -PA;
					}


					if (FoodA[i-1][j-1]>0.5 && FoodA[i-1][j-1]>FoodA[i-1][j] && FoodA[i-1][j-1]>FoodA[i-1][j+1] && FoodA[i-1][j-1]>FoodA[i][j-1] && FoodA[i-1][j-1]>FoodA[i][j+1] && FoodA[i-1][j-1]>FoodA[i+1][j-1] && FoodA[i-1][j-1]>FoodA[i+1][j] && FoodA[i-1][j-1]>FoodA[i+1][j+1])
					{
						NW = -PA;
						SE = PA;
					}


					if (FoodA[i+1][j+1]>0.5 && FoodA[i+1][j+1]>FoodA[i-1][j-1] && FoodA[i+1][j+1]>FoodA[i-1][j] && FoodA[i+1][j+1]>FoodA[i-1][j+1] && FoodA[i+1][j+1]>FoodA[i][j-1] && FoodA[i+1][j+1]>FoodA[i][j+1] && FoodA[i+1][j+1]>FoodA[i+1][j-1] && FoodA[i+1][j+1]>FoodA[i+1][j])
					{
						NW = PA;
						SE = -PA;
					}


					if (FoodA[i-1][j+1]>0.5 && FoodA[i-1][j+1]>FoodA[i-1][j-1] && FoodA[i-1][j+1]>FoodA[i-1][j] && FoodA[i][j-1] && FoodA[i-1][j+1]>FoodA[i][j+1] && FoodA[i-1][j+1]>FoodA[i+1][j-1] && FoodA[i-1][j+1]>FoodA[i+1][j] && FoodA[i-1][j+1]>FoodA[i+1][j+1])
					{
						NE = -PA;
						SW = PA;
					}


					if (FoodA[i+1][j-1]>0.5 && FoodA[i+1][j-1]>FoodA[i-1][j-1] && FoodA[i+1][j-1]>FoodA[i-1][j] && FoodA[i+1][j-1]>FoodA[i-1][j+1] && FoodA[i+1][j-1]>FoodA[i][j-1] && FoodA[i+1][j-1]>FoodA[i][j+1] && FoodA[i+1][j-1]>FoodA[i+1][j] && FoodA[i+1][j-1]>FoodA[i+1][j+1])
					{
						NE = PA;
						SW = -PA;
					}


					if (FoodA[i][j-1]>0.5 && FoodA[i][j-1]>FoodA[i-1][j-1] && FoodA[i][j-1]>FoodA[i-1][j] && FoodA[i][j-1]>FoodA[i-1][j+1] && FoodA[i][j-1]>FoodA[i][j+1] && FoodA[i][j-1]>FoodA[i+1][j-1] && FoodA[i][j-1]>FoodA[i+1][j] && FoodA[i][j-1]>FoodA[i+1][j+1])
					{
						W = -PA;
						E = PA;
					}


					if (FoodA[i][j+1]>0.5 && FoodA[i][j+1]>FoodA[i-1][j-1] && FoodA[i][j+1]>FoodA[i-1][j] && FoodA[i][j+1]>FoodA[i-1][j+1] && FoodA[i][j+1]>FoodA[i][j-1] && FoodA[i][j+1]>FoodA[i+1][j-1] && FoodA[i][j+1]>FoodA[i+1][j] && FoodA[i][j+1]>FoodA[i+1][j+1])
					{
						W = PA;
						E = -PA;
					}



					MassB[i][j]=MassA[i][j] \
						+op1*(((1+N)*MassA[i-1][j]-op3*MassA[i][j]) \
						+((1+S)*MassA[i+1][j]-op3*MassA[i][j]) \
						+((1+W)*MassA[i][j-1]-op3*MassA[i][j]) \
						+((1+E)*MassA[i][j+1]-op3*MassA[i][j])) \
						+op2*(((1+NW)*MassA[i-1][j-1]-op3*MassA[i][j]) \
						+((1+SW)*MassA[i+1][j-1]-op3*MassA[i][j]) \
						+((1+NE)*MassA[i-1][j+1]-op3*MassA[i][j]) \
						+((1+SE)*MassA[i+1][j+1]-op3*MassA[i][j]));



				FoodB[i][j]=CON*(FoodA[i][j] \
					+fp1*((FoodA[i-1][j]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j]-fp3*FoodA[i][j]) \
					+(FoodA[i][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i][j+1]-fp3*FoodA[i][j])) \
					+fp2*((FoodA[i-1][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i-1][j+1]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j+1]-fp3*FoodA[i][j])));

		}
	}




	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			FoodA[i][j]=FoodB[i][j];
			MassA[i][j]=MassB[i][j];
		}
	}

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (FoodI[i][j] == 100) {
				   FoodA[i][j] = 100;
				}

		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::distMass()
{
	double calc_mass;
	double N = 0;
	double S = 0;
	double W = 0;
	double E = 0;
	double NW = 0;
	double NE = 0;
	double SW = 0;
	double SE = 0;

	fp1=double(fp1v->Value);
	fp2=double(fp2v->Value);
	fp3=double(fp3v->Value);
	op1=double(op1v->Value);
	op2=double(op2v->Value);
	op3=double(op3v->Value);
	CON=double(conv->Value);
	PA=double(pav->Value);


	for (int i = 1; i < ar_size-1; i++) {
		for (int j = 1; j < ar_size-1; j++) {

			N = 0;
			S = 0;
			W = 0;
			E = 0;
			NW = 0;
			NE = 0;
			SW = 0;
			SE = 0;

					if (FoodA[i-1][j]>0.5 && FoodA[i-1][j]>FoodA[i+1][j])
					{
						N = -PA;
						S = PA;
					}


					if (FoodA[i+1][j]>0.5 && FoodA[i+1][j]>FoodA[i-1][j])
					{
						N = PA;
						S = -PA;
					}


					if (FoodA[i-1][j-1]>0.5 && FoodA[i-1][j-1]>FoodA[i+1][j+1])
					{
						NW = -PA;
						SE = PA;
					}


					if (FoodA[i+1][j+1]>0.5 && FoodA[i+1][j+1]>FoodA[i-1][j-1])
					{
						NW = PA;
						SE = -PA;
					}


					if (FoodA[i-1][j+1]>0.5 && FoodA[i-1][j+1]>FoodA[i+1][j-1])
					{
						NE = -PA;
						SW = PA;
					}


					if (FoodA[i+1][j-1]>0.5 && FoodA[i+1][j-1]>FoodA[i-1][j+1])
					{
						NE = PA;
						SW = -PA;
					}


					if (FoodA[i][j-1]>0.5 && FoodA[i][j-1]>FoodA[i][j+1])
					{
						W = -PA;
						E = PA;
					}


					if (FoodA[i][j+1]>0.5 && FoodA[i][j+1]>FoodA[i][j-1])
					{
						W = PA;
						E = -PA;
					}



					MassB[i][j]=MassA[i][j] \
						+op1*(((1+N)*MassA[i-1][j]-op3*MassA[i][j]) \
						+((1+S)*MassA[i+1][j]-op3*MassA[i][j]) \
						+((1+W)*MassA[i][j-1]-op3*MassA[i][j]) \
						+((1+E)*MassA[i][j+1]-op3*MassA[i][j])) \
						+op2*(((1+NW)*MassA[i-1][j-1]-op3*MassA[i][j]) \
						+((1+SW)*MassA[i+1][j-1]-op3*MassA[i][j]) \
						+((1+NE)*MassA[i-1][j+1]-op3*MassA[i][j]) \
						+((1+SE)*MassA[i+1][j+1]-op3*MassA[i][j]));



				FoodB[i][j]=CON*(FoodA[i][j] \
					+fp1*((FoodA[i-1][j]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j]-fp3*FoodA[i][j]) \
					+(FoodA[i][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i][j+1]-fp3*FoodA[i][j])) \
					+fp2*((FoodA[i-1][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j-1]-fp3*FoodA[i][j]) \
					+(FoodA[i-1][j+1]-fp3*FoodA[i][j]) \
					+(FoodA[i+1][j+1]-fp3*FoodA[i][j])));

		}
	}




	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			FoodA[i][j]=FoodB[i][j];
			MassA[i][j]=MassB[i][j];
		}
	}

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (FoodI[i][j] == 100) {
				   FoodA[i][j] = 100;
				}

		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::normalizeMass()
{
	double N = 0;
	double S = 0;
	double W = 0;
	double E = 0;
	double NW = 0;
	double NE = 0;
	double SW = 0;
	double SE = 0;

	fp1=double(fp1v->Value);
	fp2=double(fp2v->Value);
	fp3=double(fp3v->Value);
	op1=double(op1v->Value);
	op2=double(op2v->Value);
	op3=double(op3v->Value);
	CON=double(conv->Value);
	PA=double(pav->Value);


	for (int i = 1; i < ar_size-1; i++) {
		for (int j = 1; j < ar_size-1; j++) {

			N = 0;
			S = 0;
			W = 0;
			E = 0;
			NW = 0;
			NE = 0;
			SW = 0;
			SE = 0;

					if (FoodD[i-1][j]>0.5 && FoodD[i-1][j]>FoodD[i+1][j])
					{
						N = -PA;
						S = PA;
					}


					if (FoodD[i+1][j]>0.5 && FoodD[i+1][j]>FoodD[i-1][j])
					{
						N = PA;
						S = -PA;
					}


					if (FoodD[i-1][j-1]>0.5 && FoodD[i-1][j-1]>FoodD[i+1][j+1])
					{
						NW = -PA;
						SE = PA;
					}


					if (FoodD[i+1][j+1]>0.5 && FoodD[i+1][j+1]>FoodD[i-1][j-1])
					{
						NW = PA;
						SE = -PA;
					}


					if (FoodD[i-1][j+1]>0.5 && FoodD[i-1][j+1]>FoodD[i+1][j-1])
					{
						NE = -PA;
						SW = PA;
					}


					if (FoodD[i+1][j-1]>0.5 && FoodD[i+1][j-1]>FoodD[i-1][j+1])
					{
						NE = PA;
						SW = -PA;
					}


					if (FoodD[i][j-1]>0.5 && FoodD[i][j-1]>FoodD[i][j+1])
					{
						W = -PA;
						E = PA;
					}


					if (FoodD[i][j+1]>0.5 && FoodD[i][j+1]>FoodD[i][j-1])
					{
						W = PA;
						E = -PA;
					}



					MassB[i][j]=MassA[i][j] \
						+op1*(((1+N)*MassA[i-1][j]-op3*MassA[i][j]) \
						+((1+S)*MassA[i+1][j]-op3*MassA[i][j]) \
						+((1+W)*MassA[i][j-1]-op3*MassA[i][j]) \
						+((1+E)*MassA[i][j+1]-op3*MassA[i][j])) \
						+op2*(((1+NW)*MassA[i-1][j-1]-op3*MassA[i][j]) \
						+((1+SW)*MassA[i+1][j-1]-op3*MassA[i][j]) \
						+((1+NE)*MassA[i-1][j+1]-op3*MassA[i][j]) \
						+((1+SE)*MassA[i+1][j+1]-op3*MassA[i][j]));



				FoodB[i][j]=CON*(FoodD[i][j] \
					+fp1*((FoodD[i-1][j]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j]-fp3*FoodD[i][j]) \
					+(FoodD[i][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i][j+1]-fp3*FoodD[i][j])) \
					+fp2*((FoodD[i-1][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i-1][j+1]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j+1]-fp3*FoodD[i][j])));

		}
	}




	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			FoodD[i][j]=FoodB[i][j];
			MassA[i][j]=MassB[i][j];
		}
	}

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (FoodI[i][j] == foodDEdit->Value) {
				   FoodD[i][j] = foodDEdit->Value;
				}

		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TamoebaF::normalizeMass1()
{
	double N = 0;
	double S = 0;
	double W = 0;
	double E = 0;
	double NW = 0;
	double NE = 0;
	double SW = 0;
	double SE = 0;

	fp1=double(fp1v->Value);
	fp2=double(fp2v->Value);
	fp3=double(fp3v->Value);
	op1=double(op1v->Value);
	op2=double(op2v->Value);
	op3=double(op3v->Value);
	CON=double(conv->Value);
	PA=double(pav->Value);


	for (int i = 1; i < ar_size-1; i++) {
		for (int j = 1; j < ar_size-1; j++) {

			N = 0;
			S = 0;
			W = 0;
			E = 0;
			NW = 0;
			NE = 0;
			SW = 0;
			SE = 0;

					if (FoodD[i-1][j]>0.5 && FoodD[i-1][j]>FoodD[i-1][j-1] && FoodD[i-1][j]>FoodD[i-1][j+1] && FoodD[i-1][j]>FoodD[i][j-1] && FoodD[i-1][j]>FoodD[i][j+1] && FoodD[i-1][j]>FoodD[i+1][j-1] && FoodD[i-1][j]>FoodD[i+1][j] && FoodD[i-1][j]>FoodD[i+1][j+1])
					{
						N = -PA;
						S = PA;
					}


					if (FoodD[i+1][j]>0.5 && FoodD[i+1][j]>FoodD[i-1][j-1] && FoodD[i+1][j]>FoodD[i-1][j] && FoodD[i+1][j]>FoodD[i-1][j+1] && FoodD[i+1][j]>FoodD[i][j-1] && FoodD[i+1][j]>FoodD[i][j+1] && FoodD[i+1][j]>FoodD[i+1][j-1] && FoodD[i+1][j]>FoodD[i+1][j+1])
					{
						N = PA;
						S = -PA;
					}


					if (FoodD[i-1][j-1]>0.5 && FoodD[i-1][j-1]>FoodD[i-1][j] && FoodD[i-1][j-1]>FoodD[i-1][j+1] && FoodD[i-1][j-1]>FoodD[i][j-1] && FoodD[i-1][j-1]>FoodD[i][j+1] && FoodD[i-1][j-1]>FoodD[i+1][j-1] && FoodD[i-1][j-1]>FoodD[i+1][j] && FoodD[i-1][j-1]>FoodD[i+1][j+1])
					{
						NW = -PA;
						SE = PA;
					}


					if (FoodD[i+1][j+1]>0.5 && FoodD[i+1][j+1]>FoodD[i-1][j-1] && FoodD[i+1][j+1]>FoodD[i-1][j] && FoodD[i+1][j+1]>FoodD[i-1][j+1] && FoodD[i+1][j+1]>FoodD[i][j-1] && FoodD[i+1][j+1]>FoodD[i][j+1] && FoodD[i+1][j+1]>FoodD[i+1][j-1] && FoodD[i+1][j+1]>FoodD[i+1][j])
					{
						NW = PA;
						SE = -PA;
					}


					if (FoodD[i-1][j+1]>0.5 && FoodD[i-1][j+1]>FoodD[i-1][j-1] && FoodD[i-1][j+1]>FoodD[i-1][j] && FoodD[i-1][j+1]>FoodD[i][j-1] && FoodD[i-1][j+1]>FoodD[i][j+1] && FoodD[i-1][j+1]>FoodD[i+1][j-1] && FoodD[i-1][j+1]>FoodD[i+1][j] && FoodD[i-1][j+1]>FoodD[i+1][j+1])
					{
						NE = -PA;
						SW = PA;
					}


					if (FoodD[i+1][j-1]>0.5 && FoodD[i+1][j-1]>FoodD[i-1][j-1] && FoodD[i+1][j-1]>FoodD[i-1][j] && FoodD[i+1][j-1]>FoodD[i-1][j+1] && FoodD[i+1][j-1]>FoodD[i][j-1] && FoodD[i+1][j-1]>FoodD[i][j+1] && FoodD[i+1][j-1]>FoodD[i+1][j] && FoodD[i+1][j-1]>FoodD[i+1][j+1])
					{
						NE = PA;
						SW = -PA;
					}


					if (FoodD[i][j-1]>0.5 && FoodD[i][j-1]>FoodD[i-1][j-1] && FoodD[i][j-1]>FoodD[i-1][j] && FoodD[i][j-1]>FoodD[i-1][j+1] && FoodD[i][j-1]>FoodD[i][j+1] && FoodD[i][j-1]>FoodD[i+1][j-1] && FoodD[i][j-1]>FoodD[i+1][j] && FoodD[i][j-1]>FoodD[i+1][j+1])
					{
						W = -PA;
						E = PA;
					}


					if (FoodD[i][j+1]>0.5 && FoodD[i][j+1]>FoodD[i-1][j-1] && FoodD[i][j+1]>FoodD[i-1][j] && FoodD[i][j+1]>FoodD[i-1][j+1] && FoodD[i][j+1]>FoodD[i][j-1] && FoodD[i][j+1]>FoodD[i+1][j-1] && FoodD[i][j+1]>FoodD[i+1][j] && FoodD[i][j+1]>FoodD[i+1][j+1])
					{
						W = PA;
						E = -PA;
					}



					MassB[i][j]=MassA[i][j] \
						+op1*(((1+N)*MassA[i-1][j]-op3*MassA[i][j]) \
						+((1+S)*MassA[i+1][j]-op3*MassA[i][j]) \
						+((1+W)*MassA[i][j-1]-op3*MassA[i][j]) \
						+((1+E)*MassA[i][j+1]-op3*MassA[i][j])) \
						+op2*(((1+NW)*MassA[i-1][j-1]-op3*MassA[i][j]) \
						+((1+SW)*MassA[i+1][j-1]-op3*MassA[i][j]) \
						+((1+NE)*MassA[i-1][j+1]-op3*MassA[i][j]) \
						+((1+SE)*MassA[i+1][j+1]-op3*MassA[i][j]));



				FoodB[i][j]=CON*(FoodD[i][j] \
					+fp1*((FoodD[i-1][j]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j]-fp3*FoodD[i][j]) \
					+(FoodD[i][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i][j+1]-fp3*FoodD[i][j])) \
					+fp2*((FoodD[i-1][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j-1]-fp3*FoodD[i][j]) \
					+(FoodD[i-1][j+1]-fp3*FoodD[i][j]) \
					+(FoodD[i+1][j+1]-fp3*FoodD[i][j])));

		}
	}




	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			FoodD[i][j]=FoodB[i][j];
			MassA[i][j]=MassB[i][j];
		}
	}

	for (int i = 0; i < ar_size; i++) {
		for (int j = 0; j < ar_size; j++) {

			if (FoodI[i][j] == foodDEdit->Value) {
				   FoodD[i][j] = foodDEdit->Value;
				}

		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TamoebaF::Button6Click(TObject *Sender)
{
	for (int i = 0; i < stepsedit->Value; i++) {
			int found = 0;
			currentstepedit->Text = UnicodeString(i);
			currentstepedit->Repaint();
			distMass1();
			drawAmoeba();
			for (int i = 0; i < ar_size; i++) {
				for (int j = 0; j < ar_size; j++) {
					if(FoodD[i][j] > 0)
						found =1;
				}
			}
			if (found)
			{
				normalizeMass1();
				drawAmoeba();
			}
			drawTube();
			drawFood();


	}
}
//---------------------------------------------------------------------------




