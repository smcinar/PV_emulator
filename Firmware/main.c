#include <main.h>
#include <flcd.c>
#include <math.h>
#include <stdlib.h>
#include <init.h>
#include <functions.c>




int1 b_Rx=False;
int8 Data[10],s_Rx_data=0,s_Tx_data=0;

#int_RTCC
void  RTCC_isr(void) {
  set_timer0(99);
  output_toggle(Pin_D0);
  f_Anlg_giris();
  f_Kontrol(150);
  if(test)set_pwm1_duty(Duty);
}

#int_RDA
void  RDA_isr(void) {
  d_Data[s_Rx_data]=getch();
  s_Rx_data++;
  if(s_Rx_data>9){
    b_Rx=True;
    s_Rx_data=0;
  }
}

#int_TIMER1
void  TIMER1_isr(void) {

}



void main() {
  setup_adc(ADC_CLOCK_DIV_32);
  setup_adc_ports(AN0_AN1_AN3);
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);    //16.3 ms overflow
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);    //32.7 ms overflow
  setup_timer_2(T2_DIV_BY_4,99,1);    //PWM frekansi 5kHz Duty 0..400 arasi
  setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_OFF);
  enable_interrupts(INT_RTCC);
  enable_interrupts(INT_RDA);
  //enable_interrupts(INT_TIMER1);
  enable_interrupts(GLOBAL);
  set_timer0(99);
  set_tris_a(0xff);
  set_tris_b(0xff);
  set_tris_c(0x80);
  set_tris_d(0x00);
  set_tris_e(0xff);
  port_b_pullups(true);
  lcd_init();
  delay_ms(100);
  //                lcd_putc("                ");
  lcd_gotoxy(1,1);  lcd_putc("PV Emulator sys.");
  lcd_gotoxy(1,2);  lcd_putc("    v 1.0       ");
  while(TRUE){
  
    if(!input(btn_Enter)){
      delay_ms(10);
      while(!input(btn_Enter));
      //set_pwm1_duty((int16)200);
      test=True;
    }
    if(!input(btn_ESC)){
      delay_ms(10);
      while(!input(btn_ESC));
      set_pwm1_duty((int16)0);
      test=False;
    }
    if(!input(btn_Arti)){
      delay_ms(10);
      while(!input(btn_Arti));
      Duty++;
      if(Duty>=400)Duty=400;
      set_pwm1_duty((int16)100);
    }
    if(!input(btn_Eksi)){
      delay_ms(10);
      while(!input(btn_Eksi));
      Duty--;
      if(Duty<=1)Duty=0;
      set_pwm1_duty((int16)200);
    }


    if(b_Rx){
      disable_interrupts(global);
      //for(s_tx_data=0;s_Tx_data<=9;s_Tx_data++){
        //printf("%2X",d_Data[s_Tx_data]);
      //}
      chk_sum=65;
      printf("%2X%2X%2X%2X%2X",chk_sum,make8(d_Anlg[0],1),make8(d_Anlg[0],0),make8(d_Anlg[1],1),make8(d_Anlg[1],0));
      b_Rx=False;
      b_RDA=True;
      enable_interrupts(global);
    }
    
   if(b_RDA){
      b_RDA=FALSE;
      for(s_tx_data=0;s_Tx_data<=9;s_Tx_data++){
        printf("%2X",d_Data[s_Tx_data]);
      }
      j=0;
      for(i=0;i<=4;i++){r_Data[i]=0;}
      for(i=0;i<=9;i=i+2){
        r_Data[j]=Byte_yap(d_Data[i],d_Data[i+1]);
        j++;
      }
      lcd_gotoxy(1,1);lcd_putc("                ");
      //lcd_gotoxy(1,2);lcd_putc("                ");
      lcd_gotoxy(1,1);printf(lcd_putc,"%u %u %u %u %u",r_Data[0],r_Data[1],r_Data[2],r_Data[3],r_Data[4]);
      //lcd_gotoxy(1,2);printf(lcd_putc,"%u %u %u %u %u",r_Data[5],r_Data[6],r_Data[7],r_Data[15],r_Data[16]);
    }
  }
}
