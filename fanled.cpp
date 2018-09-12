/*
 * povwithouthc595.cpp
 *
 * Created: 19/07/2018 08:43:05
 * Author : Van.Hao
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#define sbi(port,bits)	(port)|=(1<<(bits))
#define cbi(port,bits)	(port)&=~(1<<(bits))

//====== CHUOI MUON XUAT HIEN! ==========//
char ChuoiHienThi[] = "   CEEC-VDK  ";
//char VienDongHo[]   = "2     3     6     9         1 ";
#define DodaiChuoi	30     // DO DAI CUA CHUOI TREN

char DongHo[]="";
#define time_	300000		// CHON SO DE VONG FOR CHAY DUNG 1S
//*********************************************//

//===== MANG KI TU! ========//
uint8_t a[6]={0b00000010  , 0b00010101  , 0b00010101  , 0b00010101  , 0b00001111 , 0 };
uint8_t b[6]={0b01111111  , 0b00001001  , 0b00010001  , 0b00010001  , 0b00001110 , 0 };
uint8_t c[6]={0b00001110  , 0b00010001  , 0b00010001  , 0b00010001  , 0b00000010 , 0 };
uint8_t d[6]={0b00001110  , 0b00010001  , 0b00010001  , 0b00001001  , 0b01111111 , 0 };
uint8_t e[6]={0b00001110  , 0b00010101  , 0b00010101  , 0b00010101  , 0b00001100 , 0 };
uint8_t f[6]={0b00001000  , 0b00111111  , 0b01001000  , 0b01000000  , 0b00100000 , 0 };
uint8_t g[6]={0b00001000  , 0b00010101  , 0b00010101  , 0b00010101  , 0b00011110 , 0 };
uint8_t h[6]={0b01111111  , 0b00001000  , 0b00010000  , 0b00010000  , 0b00001111 , 0 };
uint8_t i[6]={0  , 0b00001001  , 0b01011111  , 0b00000001  , 0 , 0 };
uint8_t j[6]={0b00000010  , 0b00000001  , 0b00010001  , 0b01011110  , 0 , 0 };
uint8_t k[6]={0  , 0b01111111  , 0b00000100  , 0b00001010  , 0b00010001 , 0 };
uint8_t l[6]={0  , 0b01000001  , 0b01111111  , 0b00000001  , 0 , 0 };
uint8_t m[6]={0b00011111  , 0b00010000  , 0b00001111  , 0b00010000  , 0b00001111 , 0 };
uint8_t n[6]={0b00011111  , 0b00001000  , 0b00010000  , 0b00010000  , 0b00001111 , 0 };
uint8_t o[6]={0b00001110  , 0b00001001  , 0b00001001  , 0b00001001  , 0b00001110 , 0 };
uint8_t p[6]={0b00011111  , 0b00010100  , 0b00010100  , 0b00010100  , 0b00001000 , 0 };
uint8_t q[6]={0b00001000  , 0b00010100  , 0b00010100  , 0b00010100  , 0b00011111 , 0 };
uint8_t r[6]={0  , 0b00011111  , 0b00001000  , 0b00010000  , 0b00010000 , 0 };
uint8_t s[6]={0b00001001  , 0b00010101  , 0b00010101  , 0b00010101  , 0b00010010 , 0 };
uint8_t t[6]={0  , 0b00010000  , 0b00111110  , 0b00010001  , 0b00000010 , 0 };
uint8_t u[6]={0b00011110  , 0b00000001  , 0b00000001  , 0b00000010  , 0b00011111 , 0 };
uint8_t v[6]={0b00011100  , 0b00000010  , 0b00000001  , 0b00000010  , 0b00011100 , 0 };
uint8_t w[6]={0b00011110  , 0b00000001  , 0b00000110  , 0b00000001  , 0b00011110 , 0 };
uint8_t x[6]={0b00010001  , 0b00010010  , 0b00001110  , 0b00001001  , 0b00010001 , 0 };
uint8_t y[6]={0b00010001  , 0b00001001  , 0b00000110  , 0b00000100  , 0b00011000 , 0 };
uint8_t z[6]={0b00010001  , 0b00010011  , 0b00010101  , 0b00011001  , 0b00010001 , 0 };
	
uint8_t Rong[6]={0 , 0 , 0 , 0 , 0, 0};

uint8_t Mot[6]={0b00010001  , 0b00100001  , 0b01111111  , 0b00000001  , 0b00000001 , 0 };
uint8_t Hai[6]={0b00100001  , 0b01000011  , 0b01000101  , 0b01001001  , 0b00110001 , 0 };
uint8_t Ba[6]={0b00100010  , 0b01000001  , 0b01001001  , 0b01001001  , 0b00110110 , 0 };
uint8_t Bon[6]={0b00001100  , 0b00010100  , 0b00100100  , 0b01111111  , 0b00000100 , 0 };
uint8_t Nam[6]={0b01110010  , 0b01010001  , 0b01010001  , 0b01010001  , 0b01001110 , 0 };
uint8_t Sau[6]={0b00111110  , 0b01001001  , 0b01001001  , 0b01001001  , 0b00100110 , 0 };
uint8_t Bay[6]={0b01000000  , 0b01000111  , 0b01001000  , 0b01010000  , 0b01100000 , 0 };
uint8_t Tam[6]={0b00110110  , 0b01001001  , 0b01001001  , 0b01001001  , 0b00110110 , 0 };
uint8_t Chin[6]={0b00110010  , 0b01001001  , 0b01001001  , 0b01001001  , 0b00111110 , 0 };
uint8_t Khong[6]={0b00111110  , 0b01000101  , 0b01001001  , 0b01010001  , 0b00111110 , 0 };
	

uint8_t HaiCham[6]={0  , 0  , 0b00010100  , 0  , 0 , 0 };
uint8_t Xuyet[6] ={2,4,8,16,32,0};
uint8_t GachNgang[6] ={8,8,8,8,8,0};

uint8_t A[6]={0b00011111  , 0b00100100  , 0b01000100  , 0b01000100  , 0b01111111 , 0 };
uint8_t B[6]={0b01111111  , 0b01001001  , 0b01001001  , 0b01001001  , 0b00110110 , 0 };
uint8_t C[6]={0b00111110  , 0b01000001  , 0b01000001  , 0b01000001  , 0b00100010 , 0 };
uint8_t D[6]={0b01111111  , 0b01000001  , 0b01000001  , 0b01000001  , 0b00111110 , 0 };
uint8_t E[6]={0b01111111  , 0b01001001  , 0b01001001  , 0b01001001  , 0b01000001 , 0 };
uint8_t F[6]={0b01111111  , 0b01001000  , 0b01001000  , 0b01001000  , 0b01000000 , 0 };
uint8_t G[6]={0b00111110  , 0b01000001  , 0b01000001  , 0b01000101  , 0b00100110 , 0 };
uint8_t H[6]={0b01111111  , 0b00001000  , 0b00001000  , 0b00001000  , 0b01111111 , 0 };
uint8_t I[6]={0b00000000  , 0b01000001  , 0b01111111  , 0b01000001  , 0b00000000 , 0 };
uint8_t J[6]={0b00000000  , 0b00000010  , 0b01000001  , 0b01000001  , 0b01111110 , 0 };
uint8_t K[6]={0b01111111  , 0b00001000  , 0b00010100  , 0b00100010  , 0b01000001 , 0 };
uint8_t L[6]={0b01111111  , 0b00000001  , 0b00000001  , 0b00000001  , 0b00000001 , 0 };
uint8_t M[6]={0b01111111  , 0b00100000  , 0b00011000  , 0b00100000  , 0b01111111 , 0 };
uint8_t N[6]={0b01111111  , 0b00010000  , 0b00001000  , 0b00000100  , 0b01111111 , 0 };
uint8_t O[6]={0b00111110  , 0b01000001  , 0b01000001  , 0b01000001  , 0b00111110 , 0 };
uint8_t P[6]={0b01111111  , 0b01001000  , 0b01001000  , 0b01001000  , 0b00110000 , 0 };
uint8_t Q[6]={0b00111100  , 0b01000010  , 0b01000010  , 0b01000010  , 0b00111101 , 0 };
uint8_t R[6]={0b01111111  , 0b01001000  , 0b01001100  , 0b01001010  , 0b00110001 , 0 };
uint8_t S[6]={0b00110010  , 0b01001001  , 0b01001001  , 0b01001001  , 0b00100110 , 0 };
uint8_t T[6]={0b01000000  , 0b01000000  , 0b01111111  , 0b01000000  , 0b01000000 , 0 };
uint8_t U[6]={0b01111110  , 0b00000001  , 0b00000001  , 0b00000001  , 0b01111110 , 0 };
uint8_t V[6]={0b01111100  , 0b00000010  , 0b00000001  , 0b00000010  , 0b01111100 , 0 };
uint8_t W[6]={0b01111110  , 0b00000001  , 0b00000110  , 0b00000001  , 0b01111110 , 0 };
uint8_t X[6]={0b01100011  , 0b00010100  , 0b00001000  , 0b00010100  , 0b01100011 , 0 };
uint8_t Y[6]={0b01110000  , 0b00001000  , 0b00001111  , 0b00001000  , 0b01110000 , 0 };
uint8_t Z[6]={0b01000011  , 0b01000101  , 0b01001001  , 0b01010001  , 0b01000011 , 0 };



//*****************************************************************************//

#define TimeDelay	610			   // THOI GIAN DELAY SAU MOI LAN XUAT

int Gio=10;										// TAHY DOI THOI GIAN TAI DAY
int Phut=23;
int Giay=40;
int Ngay=27;
int Thang=7;
int nam=2018;

//====== HAM XUAT LED =======//                                      
void XuatLed_B(uint8_t Mang[6]);                  // HAM XUAT LED THANH CHU
void XuatLed_C(uint8_t Mang[6]);
void XuatChu_B(char Chu);                            // HAM HIEN THI MOT CHU
void XuatChu_C(char Chu);
void XuatChuoiHienThi_B(char Chuoi[]);		   // HAM HIEN THI CHUOI MUON XUAT
void XuatChuoiHienThi_C(char Chuoi[]);
void DongHoSo(void);
char ChuyenDoi(int x);
int main(void)
{
    /* Replace with your application code */
	//===== INIT LED ======//
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
	DDRD=0;
	PORTA=0;
	PORTB=0;
	PORTC=0;
	//*********************//
	//* TIMER 0 */
	 TCCR0=5;                  // CS02=1, CS01=0, CS00=1: chon Prescaler = 1024
	 TCNT0=0;              //gan gia tri khoi tao cho T/C0
	 TIMSK=(1<<TOIE0);//cho phep ngat khi co tran o T/C0
	/*TIMER*/
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK = 0;
	TCCR1B |= (1 << CS12); // Normal Mode ,prescaler = 256
	TIMSK |= (1 << TOIE1); //Set interrupt on overflow
	
	TCNT1 = 3035;
	
	//===== KHAI BAO NGAT NGOAI ======//
	MCUCR|=(1<<ISC11)|(1<<ISC10);   
	GICR=(1<<INT1);
	sei();
	//********************************//
	
    while (1) 
    {
		PORTC=0;
		PORTB=0;
		PORTA=0x00;
		//DongHoSo();
    }
}


ISR(INT1_vect)
{	
// 	XuatChuoiHienThi_C(ChuoiHienThi);

	XuatChuoiHienThi_B(ChuoiHienThi);

	
}
ISR (TIMER0_OVF_vect ) // XUAT PORTB
{
// 	PORTC=0xff;
// 	TCNT0=0;       //gan gia tri khoi tao cho T/C0
// 	//XuatChuoiHienThi_C(ChuoiHienThi);
// 	
}
ISR(TIMER1_OVF_vect) // DOAN TIMER DUNG DE TINH THOI GIAN
{
// 	TCNT1=3035;
// 	Giay++;
// 	
// 	//=== DOAN CODE TINH THOI GIAN ====//
// 	if(Giay==60)
// 	{
// 		Giay=0;
// 		Phut++;
// 		if(Phut==60)
// 		{
// 			Phut=0;
// 			Gio++;
// 			if(Gio==24)
// 			{
// 				Gio=0;
// 				Ngay++;
// 				// NAM THUONG
// 				if(nam%4!=0)
// 				{
// 					if (Ngay==29)
// 					{
// 						if(Thang==2) 
// 						{
// 							Ngay=1;
// 							Thang++;
// 						}
// 					}
// 					if (Ngay == 31)  // QUA 30 SE BI RESET VAO THNG 30 NGAY
// 					{
// 						if (Thang==4 || Thang == 6 || Thang== 9 || Thang==11)
// 					 	{
// 							 Ngay=1;
// 							 Thang++;
// 						}
// 					
// 					}
// 					if (Ngay ==32)   // QUA 30 SE BI RESET VAO THNG 31 NGAY
// 					{
// 						Ngay=1;
// 						Thang++;
// 						if (Thang==12)
// 						{
// 							Thang=1;
// 							nam++;
// 						}
// 					}
// 				}
// 				
// 				// NAM NHUAN
// 				else 
// 				{
// 					if (Ngay==30)
// 					{
// 						if(Thang==2) 
// 						{
// 							Ngay=1;
// 							Thang++;
// 						}
// 					}
// 					if (Ngay == 31)  // QUA 30 SE BI RESET VAO THNG 30 NGAY
// 					{
// 						if (Thang==4 || Thang == 6 || Thang== 9 || Thang==11)
// 						{
// 							Ngay=1;
// 							Thang++;
// 						}
// 						
// 					}
// 					if (Ngay ==32)   // QUA 30 SE BI RESET VAO THNG 31 NGAY
// 					{
// 						Ngay=1;
// 						Thang++;
// 						if (Thang==12)
// 						{
// 							Thang=1;
// 							nam++;
// 						}
// 					}
// 				}
// 				
// 			}
// 		}	
// 	}
// //******************************************************//
// 	//ngay
// 	DongHo[0]=' ';
// 	if(Ngay<10)
// 	{
// 		DongHo[1] = ChuyenDoi(0);
// 		DongHo[2] = ChuyenDoi(Ngay);
// 	}
// 	else
// 	{
// 		DongHo[1] =ChuyenDoi (Ngay / 10);
// 		DongHo[2] = ChuyenDoi(Ngay % 10);
// 	}
// 	DongHo[3] = '/';
// 	if(Thang<10)
// 	{
// 		DongHo[4] =ChuyenDoi(0) ;
// 		DongHo[5] = ChuyenDoi(Thang);
// 	}
// 	else
// 	{
// 		DongHo[4] = ChuyenDoi(Thang / 10);
// 		DongHo[5] = ChuyenDoi(Thang % 10) ;
// 	}
// 	DongHo[6] = '/';
// 	if(nam<10)
// 	{
// 		DongHo[7] = ChuyenDoi(0);
// 		DongHo[8] = ChuyenDoi( nam);
// 		
// 	}
// 	else
// 	{
// 		DongHo[7] = ChuyenDoi((nam / 10)%10) ;
// 		DongHo[8] = ChuyenDoi(nam % 10) ;
// 	}
// 	DongHo[9]=' ';
// 	DongHo[10]=' ';
// 	//gio
// 	if(Gio<10)
// 	{
// 		DongHo[11] = ChuyenDoi(0);
// 		DongHo[12] = ChuyenDoi(Gio);
// 	}
// 	else
// 	{
// 		DongHo[11] =ChuyenDoi (Gio / 10);
// 		DongHo[12] = ChuyenDoi(Gio % 10);
// 	}
// 	DongHo[13] = ':';
// 	if(Phut<10)
// 	{
// 		DongHo[14] =ChuyenDoi(0) ;
// 		DongHo[15] = ChuyenDoi(Phut);
// 	}
// 	else
// 	{
// 		DongHo[14] = ChuyenDoi(Phut / 10);
// 		DongHo[15] = ChuyenDoi(Phut % 10) ;
// 	}
// 	DongHo[16] = ':';
// 	if(Giay<10)
// 	{
// 		DongHo[17] = ChuyenDoi(0);
// 		DongHo[18] = ChuyenDoi( Giay);
// 		
// 	}
// 	else
// 	{
// 		DongHo[17] = ChuyenDoi(Giay / 10) ;
// 		DongHo[18] = ChuyenDoi(Giay % 10) ;
// 	}

}

void XuatLed_B(uint8_t Mang[6])
{
	for(int i = 0; i < 6; i++)
	{
		PORTB=Mang[i];
		
		_delay_us(TimeDelay);
	}
	
}
void XuatLed_C(uint8_t Mang[6])
{
	for(int i = 0; i < 6; i++)
	{
		PORTB=Mang[i];
		_delay_us(TimeDelay);
	}
}
void XuatChu_B(char Chu)
{
	switch (Chu)
	{
		case '0': XuatLed_B(Khong); break;
		case '1': XuatLed_B(Mot); break;
		case '2': XuatLed_B(Hai); break;
		case '3': XuatLed_B(Ba); break;
		case '4': XuatLed_B(Bon); break;
		case '5': XuatLed_B(Nam); break;
		case '6': XuatLed_B(Sau); break;
		case '7': XuatLed_B(Bay); break;
		case '8': XuatLed_B(Tam); break;
		case '9': XuatLed_B(Chin); break;
		case ' ': XuatLed_B(Rong); break;
		case ':': XuatLed_B(HaiCham); break;
		case '/': XuatLed_B(Xuyet); break;
		default: break;
	}
}
void XuatChu_C(char Chu)
{
	switch (Chu)
	{
		case 'a': XuatLed_C(a); break;
		case 'b': XuatLed_C(b); break;
		case 'c': XuatLed_C(c); break;
		case 'd': XuatLed_C(d); break;
		case 'e': XuatLed_C(e); break;
		case 'f': XuatLed_C(f); break;
		case 'g': XuatLed_C(g); break;
		case 'h': XuatLed_C(h); break;
		case 'i': XuatLed_C(i); break;
		case 'j': XuatLed_C(j); break;
		case 'k': XuatLed_C(k); break;
		case 'l': XuatLed_C(l); break;
		case 'm': XuatLed_C(m); break;
		case 'n': XuatLed_C(n); break;
		case 'o': XuatLed_C(o); break;
		case 'p': XuatLed_C(p); break;
		case 'q': XuatLed_C(q); break;
		case 'r': XuatLed_C(r); break;
		case 's': XuatLed_C(s); break;
		case 't': XuatLed_C(t); break;
		case 'u': XuatLed_C(u); break;
		case 'v': XuatLed_C(v); break;
		case 'w': XuatLed_C(w); break;
		case 'x': XuatLed_C(x); break;
		case 'y': XuatLed_C(y); break;
		case 'z': XuatLed_C(z); break;
		
		case '0': XuatLed_C(Khong); break;
		case '1': XuatLed_C(Mot); break;
		case '2': XuatLed_C(Hai); break;
		case '3': XuatLed_C(Ba); break;
		case '4': XuatLed_C(Bon); break;
		case '5': XuatLed_C(Nam); break;
		case '6': XuatLed_C(Sau); break;
		case '7': XuatLed_C(Bay); break;
		case '8': XuatLed_C(Tam); break;
		case '9': XuatLed_C(Chin); break;
		case ' ': XuatLed_C(Rong); break;
		case ':': XuatLed_C(HaiCham); break;
		
		case 'A': XuatLed_C(A); break;
		case 'B': XuatLed_C(B); break;
		case 'C': XuatLed_C(C); break;
		case 'D': XuatLed_C(D); break;
		case 'E': XuatLed_C(E); break;
		case 'F': XuatLed_C(F); break;
		case 'G': XuatLed_C(G); break;
		case 'H': XuatLed_C(H); break;
		case 'I': XuatLed_C(I); break;
		case 'J': XuatLed_C(J); break;
		case 'K': XuatLed_C(K); break;
		case 'L': XuatLed_C(L); break;
		case 'M': XuatLed_C(M); break;
		case 'N': XuatLed_C(N); break;
		case 'O': XuatLed_C(O); break;
		case 'P': XuatLed_C(P); break;
		case 'Q': XuatLed_C(Q); break;
		case 'R': XuatLed_C(R); break;
		case 'S': XuatLed_C(S); break;
		case 'T': XuatLed_C(T); break;
		case 'U': XuatLed_C(U); break;
		case 'V': XuatLed_C(V); break;
		case 'W': XuatLed_C(W); break;
		case 'X': XuatLed_C(X); break;
		case 'Y': XuatLed_C(Y); break;
		case 'Z': XuatLed_C(Z); break;
		
		case '-': XuatLed_C(GachNgang); break;
		

		default: break;
	}
}
void XuatChuoiHienThi_C(char Chuoi[])
{
	for(int i = 0 ; i < DodaiChuoi ; i++ )
	{
		XuatChu_B(Chuoi[i]);
		_delay_us(300);
	}
}
void XuatChuoiHienThi_B(char Chuoi[])
{
	for(int i = 0 ; i < DodaiChuoi ; i++ )
	{
		XuatChu_C(Chuoi[i]);
		//_delay_us(300);
	}
}
char ChuyenDoi(int x)
{
	char val;
	switch(x)
	{
		case 0: val='0'; break;
		case 1: val='1'; break;
		case 2: val='2'; break;
		case 3: val='3'; break;
		case 4: val='4'; break;
		case 5: val='5'; break;
		case 6: val='6'; break;
		case 7: val='7'; break;
		case 8: val='8'; break;
		case 9: val='9'; break;
		default: break;
	}
	return val;
}
