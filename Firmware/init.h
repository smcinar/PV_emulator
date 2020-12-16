//Buton tanimlamalari
#define btn_Enter Pin_B0
#define btn_ESC   Pin_B1
#define btn_Arti  Pin_B2
#define btn_Eksi  Pin_B2
//#define Kontrol_modu=0;//Matematik model

//#define Ti=1;//PI kontrolör
int1 test=false,b_RDA=FALSE,b_TX=False,b_Tx_master=False;
int8 s_Anlg_ort=0,Kontrol_modu=0,s_Haberlesme=0,s_Data=10,i=0,j=0;
int16 chk_sum=0,Duty=0,d_Anlg[2]={0,0};
char  d_Data[10];
int8 r_Data[5];
int8 t_Data[5];
//float32 Hata_I=0,Hata_I2=0,Knt_sng=0,Ti=0.001;





