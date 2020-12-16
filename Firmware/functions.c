int8 ASCItoInt(int8 Data){
  if(Data<58)return(Data-48);
  if(Data>=65)return(Data-55);
}

int8 Byte_yap(int8 ByteL,int8 ByteH){
  ByteL=ASCItoInt(ByteL);
  ByteH=ASCItoInt(ByteH);
  ByteH<<=4;
  return ByteH|ByteL;
}

void f_Anlg_giris(){
  int8 s_Kanal=0;
  for(s_Kanal=0;s_Kanal<=1;s_Kanal++){
    set_adc_channel(s_Kanal);
    delay_us(20);
    //d_Anlg[s_Kanal][s_Anlg_ort]=read_adc();
    d_Anlg[s_Kanal]=read_adc();
  }
  //s_Anlg_ort++;
  //if(s_Anlg_ort>=4)s_Anlg_ort=0;
  //lcd_gotoxy(1,1);
  //Printf(Lcd_Putc,"V= %4Lu         ",d_Anlg[0]);
  //lcd_gotoxy(1,2);
  //Printf(Lcd_Putc,"A= %4Lu D=%3Lu   ",d_Anlg[1],Duty);
}

int16 f_Kontrol(int16 V_set){
  //int16 V_hata=0;
  float32 PWM_temp=0,V_set_temp=0,V_out_temp=0,V_hata=0,Duty_temp=0;
  V_set_temp=V_set;
  //V_out_temp=(d_Anlg[0][0]+d_Anlg[0][1]+d_Anlg[0][2]+d_Anlg[0][3]+d_Anlg[0][4]);
  //V_out_temp=V_out_temp/5;
  V_out_temp=d_Anlg[0];
  V_hata=V_set_temp-V_out_temp;
  //printf("\r\n Hata: %3e",V_hata);
  //printf("\r\n V_out: %Lu",d_Anlg[0]);
  //printf("\r\n V_set: %Lu",V_set);
  //output_low(Pin_D0);
  if(abs(V_hata)>3){
    //printf("\r\n Hata buyuk uc");
    //switch (Kontrol_modu){
      //case 0:{//Matematiksel
        
        if(Duty==0)Duty=2;
      //Duty_temp=log(Duty);
      //PWM_temp=(65.91*Duty_temp)-98.69;
        //printf("\r\n PWM_temp: %3e",PWM_temp);
      //  PWM_temp=PWM_temp+(V_hata*0.7);
      PWM_temp=V_hata*1.5;
        //printf("\r\n Ek: %3e",PWM_temp);
      //  Duty_temp=(PWM_temp+98.69)/65.91;
      //  Duty=exp(Duty_temp);
        //printf("\r\n Duty: %Lu",Duty);
      Duty=Duty+PWM_temp;
        if(Duty>=400)Duty=400;
        if(Duty<0)Duty=0;
        //break;
      //}
      //case 1: {//PI kontrolör
        //Hata_I=Hata_I+V_hata;
        //printf("\r\n Hata_I: %3e",Hata_I);
        //s_Integral++;
        //if(s_Integral>=9){
          //s_Integral=0;
          //Hata_I=0;
          //printf("\r\n ");
        //}  
        //Hata_I2=Hata_I/Ti;
        //printf("\r\n Hata_I: %3e",Hata_I);
        //Knt_sng=Hata_I2+V_hata;
        
        //Knt_sng=Knt_sng*Kp;
        //Duty=Knt_sng;
        //printf("\r\n Konrol sinyali: %3e",Knt_sng);
        //if(Duty>=400)Duty=400;
        //if(Duty<0)Duty=0;  
        //break;
      //}
    //}
  }
  
  return Duty;
}

