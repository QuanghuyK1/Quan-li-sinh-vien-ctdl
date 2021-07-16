
#include<iostream>
#include<conio.h>
#include<windows.h>
#define LEFT -75	
#define RIGHT -77	
#define ENTER 13 
#define ESC 27

using namespace std;

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int  GetKey1() {
	char key; key = _getch();
	if (key == -32 || key == 0)
		return -(_getch());
	else return key;
}
void HienThiTrang(int trang, int tongtrang, int x, int y) {
	TextColor(174);	gotoXY(x, y); cout << " Trang:        ";
	gotoXY(x + 8, y); cout << trang << "/" << tongtrang;
	TextColor(14);
}
//--------------LTC----------------
void Khung_Nhap_LTC() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n";
	cout << "   +-----------------------------------------------------------------------------------+";
	cout << "\n   |    |             |  	      | 	    |        |        |        |        |";
	cout << "\n   |----+-------------+---------------+-------------+--------+--------+--------+-------+";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      |             |        |        |        |        |";
	cout << "\n   |    | 	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |    |	      |		      | 	    |        |        |        |        |";
	cout << "\n   |------------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                    |";
	cout << "\n   +------------------------------------------------------------------------------------+";
	gotoXY(26, 2);
	TextColor(236);
	cout << "     DANH SACH LOP TIN CHI      ";
	TextColor(14);
	gotoXY(5, 6);    	cout << "STT";
	gotoXY(11, 6);    	cout << "MA LOP TC";
	gotoXY(25, 6);		cout << "MA MON HOC";
	gotoXY(41, 6);		cout << "NIEN KHOA";
	gotoXY(54, 6);		cout << "HOC KI";
	gotoXY(64, 6);		cout << "NHOM";
	gotoXY(73, 6);		cout << "MIN";
	gotoXY(82, 6);		cout << "MAX";
	gotoXY(4, 24);		TextColor(252);		cout << "ESC";
	TextColor(14);		cout << ": Exit";
	gotoXY(20, 24);		TextColor(252);		cout << "ENTER";
	TextColor(14);		cout << ": OK";
	gotoXY(36, 24);		TextColor(252);		cout << "CONTROL";
	TextColor(14);		cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Xuat_LTC() {
	gotoXY(0, 1);
	cout << "\n\n\n\n";
	cout << "   +------------------------------------------------------------------------------------+";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |----+-------------+---------------+-------------+--------+--------+--------+--------+";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |    |             |               |             |        |        |        |        |";
	cout << "\n   |------------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                    |";
	cout << "\n   +------------------------------------------------------------------------------------+";
	gotoXY(26, 2);
	TextColor(236);
	cout << "     DANH SACH LOP TIN CHI      ";
	TextColor(14);
	gotoXY(5, 6);    	cout << "STT";
	gotoXY(11, 6);    	cout << "MA LOP TC";
	gotoXY(25, 6);		cout << "MA MON HOC";
	gotoXY(41, 6);		cout << "NIEN KHOA";
	gotoXY(54, 6);		cout << "HOC KI";
	gotoXY(64, 6);		cout << "NHOM";
	gotoXY(71, 6);		cout << "SO MIN";
	gotoXY(81, 6);		cout << "SO MAX";
	gotoXY(4, 24);		TextColor(252);		cout << "ESC";
	TextColor(14);		cout << ": Exit";
	gotoXY(20, 24);		TextColor(252);		cout << "F1";
	TextColor(14);		cout << ": Insert";
	gotoXY(36, 24);		TextColor(252);		cout << "F2";
	TextColor(14);		cout << ": Edit";
	gotoXY(50, 24);		TextColor(252);		cout << "F3";
	TextColor(14);		cout << ": Delete";
	gotoXY(95, 13); cout << "^";
	gotoXY(91, 15); cout << "<";
	gotoXY(99, 15); cout << ">";
	gotoXY(95, 17); cout << "v";
	gotoXY(90, 19); cout << "UP";
	gotoXY(90, 21); cout << "DOWN";
	gotoXY(90, 23); cout << "LEFT";
	gotoXY(90, 25); cout << "RIGHT";
	gotoXY(95, 19); cout << ": LEN";
	gotoXY(95, 21); cout << ": XUONG";
	gotoXY(95, 23); cout << ": TRAI";
	gotoXY(95, 25); cout << ": PHAI";
	gotoXY(0, 27);
}

void Khung_Cao_Ky() {
	gotoXY(0, 1);
	cout << "\n\n\n\n";
	cout << "   +-----------------------------------------------------------------------------------------+";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |----+-------+------------+------------------------------------+--------+--------+--------+";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |    |       |            |                                    |        |        |        |";
	cout << "\n   |-----------------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                         |";
	cout << "\n   +-----------------------------------------------------------------------------------------+";
//	gotoXY(26, 2);
//	TextColor(236);
//	cout << "     DANH SACH LOP TIN CHI      ";
	TextColor(14);
	gotoXY(5, 6);    	cout << "STT";
	gotoXY(10, 6);    	cout << "MA TC";
	gotoXY(18, 6);		cout << "MA MON HOC";
	gotoXY(39, 6);		cout << "TEN MON HOC";
	gotoXY(69, 6);		cout << "NHOM";
	gotoXY(76, 6);		cout << "SO SV DK";
	gotoXY(86, 6);		cout << "CON LAI";

	gotoXY(100, 13); cout << "^";
	gotoXY(96, 15); cout << "<";
	gotoXY(104, 15); cout << ">";
	gotoXY(100, 17); cout << "v";
	gotoXY(95, 19); cout << "UP";
	gotoXY(95, 21); cout << "DOWN";
	gotoXY(95, 23); cout << "LEFT";
	gotoXY(95, 25); cout << "RIGHT";
	gotoXY(100, 19); cout << ": LEN";
	gotoXY(100, 21); cout << ": XUONG";
	gotoXY(100, 23); cout << ": TRAI";
	gotoXY(100, 25); cout << ": PHAI";
	gotoXY(0, 27);
}

void Khung_Them_LTC() {
	TextColor(225);
	gotoXY(7, 8);		cout << "                          NHAP THONG TIN LOP TIN CHI CAN THEM                       ";
	TextColor(228);
	gotoXY(7, 9);		cout << "                                                                                    ";
	gotoXY(7, 10);    	cout << "                                                                                    ";
	gotoXY(12, 10);    	cout << "MA LOP TC";
	gotoXY(25, 10);		cout << "MA MON HOC";
	gotoXY(41, 10);		cout << "NIEN KHOA";
	gotoXY(54, 10);		cout << "HOC KI";
	gotoXY(64, 10);		cout << "NHOM";
	gotoXY(71, 10);		cout << "SO MIN";
	gotoXY(81, 10);		cout << "SO MAX";
	gotoXY(7, 11);    	cout << "                                                                                    ";
	gotoXY(7, 12);    	cout << "                                                                                    ";
	gotoXY(7, 13);    	cout << "                                                                                    ";
	TextColor(245);
	gotoXY(9, 13);    	cout << "                                                                           ";
	TextColor(12);
	gotoXY(9, 11);    	cout << "            ";
	gotoXY(24, 11);    	cout << "            ";
	gotoXY(41, 11);    	cout << "         ";
	gotoXY(54, 11);    	cout << "      ";
	gotoXY(64, 11);		cout << "    ";
	gotoXY(71, 11);		cout << "        ";
	gotoXY(81, 11);		cout << "        ";
}
void Khung_Xoa_LTC() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Lop Can Xoa";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(12);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Sua_LTC() {
	TextColor(228);
	gotoXY(30, 10); cout << "                                 ";
	gotoXY(30, 11); cout << "                                 ";
	gotoXY(30, 12); cout << "                                 ";
	gotoXY(33, 10); cout << "Nhap Ma Lop Tin Chi Can Sua";
	TextColor(228); gotoXY(33, 12); cout << "Enter:";
	gotoXY(51, 12); cout << "ESC:";
	TextColor(225); gotoXY(40, 12); cout << "OK";
	gotoXY(56, 12); cout << "Exit";
	TextColor(12);	gotoXY(33, 11); cout << "                           ";
}
void Khung_Diem_LTC() {
	TextColor(228);
	gotoXY(30, 10); cout << "                                 ";
	gotoXY(30, 11); cout << "                                 ";
	gotoXY(30, 12); cout << "                                 ";
	gotoXY(33, 10); cout << "   Nhap Ma Lop Tin Chi    ";
	TextColor(228); gotoXY(33, 12); cout << "Enter:";
	gotoXY(51, 12); cout << "ESC:";
	TextColor(225); gotoXY(40, 12); cout << "OK";
	gotoXY(56, 12); cout << "Exit";
	TextColor(12);	gotoXY(33, 11); cout << "                           ";
}
void KhungLTC() {
	TextColor(245);
	gotoXY(30, 0);		cout << "     NHAP THONG TIN DE TIEN HANH MO LOP      ";
	TextColor(228);
	gotoXY(30, 1);    	cout << "                                             ";
	gotoXY(40, 1);		cout << "NIEN KHOA";
	gotoXY(60, 1);		cout << "HOC KI";
	gotoXY(30, 2);    	cout << "                                             ";
	gotoXY(30, 3);    	cout << "                                             ";
	TextColor(12);
	gotoXY(38, 2);    	cout << "             ";
	gotoXY(60, 2);    	cout << "      ";

}
//------------DSDK-----------------
void Khung_Nhap_MSV_HK_NK() {
	TextColor(245);
	gotoXY(30, 0);		cout << "     NHAP THONG TIN DE TIEN HANH DANG KI     ";
	TextColor(228);
	gotoXY(30, 1);    	cout << "                                             ";
	gotoXY(34, 1);		cout << "MA SINH VIEN";
	gotoXY(50, 1);		cout << "HOC KI ";
	gotoXY(63, 1);		cout << "NIEN KHOA";
	gotoXY(30, 2);    	cout << "                                             ";
	gotoXY(30, 3);    	cout << "                                             ";
	TextColor(12);
	gotoXY(34, 2);    	cout << "            ";
	gotoXY(49, 2);    	cout << "            ";
	gotoXY(64, 2);    	cout << "      ";
}
void Khung_DKLTC() {
	TextColor(244);
	gotoXY(80, 1); cout << "   NHAP LOP TIN CHI MUON DANG KI   ";
	TextColor(228);
	gotoXY(80, 2); cout << "                                   ";
	gotoXY(80, 3); cout << "   MA LTC                          ";
	gotoXY(80, 4); cout << "                                   ";
	TextColor(14);
	gotoXY(93, 3); cout << "             ";

}
void Khung_Nhap_bo4Diem() {
	TextColor(244);
	gotoXY(11, 9);		cout << "                    NHAP THONG TIN                     ";
	TextColor(228);
	gotoXY(11, 10);    	cout << "                                                       ";
	gotoXY(16, 10);    	cout << "MA MON HOC";
	gotoXY(31, 10);		cout << "NIEN KHOA";
	gotoXY(44, 10);		cout << "HOC KI";
	gotoXY(58, 10);		cout << "NHOM";
	gotoXY(11, 11);    	cout << "                                                       ";
	gotoXY(11, 12);    	cout << "                                                       ";
	TextColor(12);
	gotoXY(13, 11);    	cout << "            ";
	gotoXY(28, 11);    	cout << "            ";
	gotoXY(45, 11);    	cout << "         ";
	gotoXY(58, 11);    	cout << "      ";
}
int	 ThongBao_DK() {
	int key, count = 0;
	TextColor(206);
	gotoXY(85, 22); cout << "    Ban chac chan muon dang ki   ";
	gotoXY(85, 23); cout << "                                 ";
	gotoXY(85, 24); cout << "                                 ";
	gotoXY(85, 25); cout << "                                 ";
	gotoXY(85, 26); cout << "                                 ";
	TextColor(238);
	gotoXY(88, 23); cout << "                           ";
	gotoXY(88, 24); cout << "                           ";
	gotoXY(88, 25); cout << "                           ";
	TextColor(252);	gotoXY(93, 24);	cout << " YES ";
	TextColor(233);	gotoXY(105, 24);	cout << " NO ";
	gotoXY(94, 24);
	while (1) {
		key = GetKey1();
		if (key == LEFT || key == RIGHT) {
			count++;
			if (count % 2 == 1) {
				TextColor(233);		gotoXY(93, 24); cout << " YES ";
				TextColor(252);		gotoXY(105, 24); cout << " NO ";
				gotoXY(106, 24);
			}
			else {
				TextColor(252);		gotoXY(93, 24); cout << " YES ";
				TextColor(233);		gotoXY(105, 24); cout << " NO ";
				gotoXY(94, 24);
			}
		}
		if (key == ENTER) {
			if (count == 0) {
				return 1;
			}
			else {
				if (count % 2 == 1) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		if (key == ESC) {
			return -1;
		}
	}
}
void Khung_Xuat_Diem() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------+";
	cout << "\n   |     |		 |		             |     	    |      |";
	cout << "\n   |-----+---------------+---------------------------+--------------+------|";
	cout << "\n   |	 |               |       	             |              |      |";
	cout << "\n   |	 |         	 |		             |	    	    |      |";
	cout << "\n   | 	 |	         |		             |	            |      |";
	cout << "\n   |	 |	         |		             |              |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |-----------------------------------------------------------------------|";
	cout << "\n   |              		                         	  	   |";
	cout << "\n   +-----------------------------------------------------------------------+";
	TextColor(236);	gotoXY(25, 1);	cout << "                              ";
	gotoXY(25, 2);	cout << "      XUAT DANH SACH DIEM     ";
	gotoXY(25, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(40, 6);	cout << "HO";
	gotoXY(60, 6);	cout << "TEN";
	gotoXY(70, 6);	cout << "DIEM";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(14);	cout << ": Exit";
	gotoXY(20, 24);	TextColor(252);	cout << "ENTER";
	TextColor(14);	cout << ": OK";
	gotoXY(36, 24);	TextColor(252);	cout << "CONTROL";
	TextColor(14);		cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Nhap_Diem() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------+";
	cout << "\n   |     |		 |		             |     	    |      |";
	cout << "\n   |-----+---------------+---------------------------+--------------+------|";
	cout << "\n   |	 |               |       	             |              |      |";
	cout << "\n   |	 |         	 |		             |	    	    |      |";
	cout << "\n   | 	 |	         |		             |	            |      |";
	cout << "\n   |	 |	         |		             |              |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |	 |	         |		             |		    |      |";
	cout << "\n   |-----------------------------------------------------------------------|";
	cout << "\n   |              		                         	  	   |";
	cout << "\n   +-----------------------------------------------------------------------+";
	TextColor(236);	gotoXY(25, 1);	cout << "                              ";
	gotoXY(25, 2);	cout << "      NHAP DANH SACH DIEM     ";
	gotoXY(25, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(40, 6);	cout << "HO";
	gotoXY(60, 6);	cout << "TEN";
	gotoXY(70, 6);	cout << "DIEM";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(14);	cout << ": Exit";
	gotoXY(20, 24);	TextColor(252);	cout << "ENTER";
	TextColor(14);	cout << ": OK";
	gotoXY(36, 24);	TextColor(252);	cout << "CONTROL";
	TextColor(14);		cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}

//----------DSLOP------------------
void Khung_Nhap_Lop() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n";
	cout << "   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |		      |					       |	       |";
	cout << "\n   |-----+--------------------+----------------------------------------+---------------|";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |    	       |";
	cout << "\n   | 	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |	 |		      |					       |	       |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                            				       |";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);
	cout << "      NHAP DANH SACH LOP      ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(14);		gotoXY(5, 6);    	cout << "STT";
	gotoXY(17, 6);		cout << "MA LOP";
	gotoXY(48, 6);		cout << "TEN LOP";
	gotoXY(75, 6);		cout << "NIEN KHOA";
	gotoXY(4, 24);		TextColor(252);		cout << "ESC";
	TextColor(14);		cout << ": Exit";
	gotoXY(20, 24);		TextColor(252);		cout << "ENTER";
	TextColor(14);		cout << ": OK";
	gotoXY(36, 24);		TextColor(252);		cout << "CONTROL";
	TextColor(14);		cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Them_Lop() {
	TextColor(228); gotoXY(10, 13); cout << "       MA LOP                    TEN LOP             NK   ";
	gotoXY(10, 14); cout << "  ";
	gotoXY(28, 14); cout << "  ";
	gotoXY(60, 14); cout << "  ";
	gotoXY(66, 14); cout << "  ";
	gotoXY(10, 15); cout << "                                                          ";
	TextColor(228);	gotoXY(45, 15); cout << "Enter:";
	gotoXY(58, 15); cout << "ESC:";	TextColor(225);
	gotoXY(52, 15); cout << "OK";
	gotoXY(63, 15); cout << "Exit";
	TextColor(14);
	gotoXY(12, 14); cout << "                ";
	gotoXY(30, 14); cout << "                              ";
	gotoXY(62, 14); cout << "     ";
}
void Khung_Xoa_Lop() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Lop Can Xoa";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(14);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Sua_Lop() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Lop Can Sua";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(14);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Xuat_Lop() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n";

	cout << "\n   +------------------+";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   |		      |";
	cout << "\n   +------------------+";
	
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);
	cout << "         DANH SACH LOP        ";
	gotoXY(33, 3);	cout << "                              ";
}
void Khung_Nhap_MaLop() {
	TextColor(228); gotoXY(33, 2); cout << "                              ";
	gotoXY(33, 3); cout << "                              ";
	gotoXY(33, 4); cout << "                              ";
	gotoXY(33, 1); cout << "                              ";
	TextColor(192);	TextColor(116); gotoXY(33, 1); cout << "          NHAP MA LOP         ";
	TextColor(233); gotoXY(36, 3); cout << "Enter:";
	gotoXY(50, 3); cout << "ESC:";
	gotoXY(38, 4); cout << "F5:";
	TextColor(228); gotoXY(43, 3); cout << "OK";
	gotoXY(55, 3); cout << "Exit";
	gotoXY(42, 4); cout << "XEM DANH SACH LOP";
	TextColor(14);	gotoXY(40, 2); cout << "               ";
}
//-------------DSMH--------------
void Khung_Them_MonHoc() {
	TextColor(228);
	gotoXY(10, 13); cout << "     MA MON HOC                    TEN MON HOC                STCLT   STCTH ";
	gotoXY(10, 14); cout << "                                                                            ";
	gotoXY(10, 15); cout << "                                                                            ";
	TextColor(228);	gotoXY(58, 15); cout << "Enter:";
	gotoXY(70, 15); cout << "ESC:";
	TextColor(225);	gotoXY(65, 15); cout << "OK";
	gotoXY(75, 15); cout << "Exit";
	TextColor(12);
	gotoXY(12, 14); cout << "                ";
	gotoXY(30, 14); cout << "                                   ";
	gotoXY(72, 14); cout << "   ";
	gotoXY(79, 14); cout << "   ";
}
void Khung_Sua_MonHoc() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Mon Hoc Can Sua";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(14);
	gotoXY(33, 14); cout << "                           ";
}
void Khung_Xoa_MonHoc() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Mon Hoc Can Xoa";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(14);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Xuat_MH() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |		      |					       |       |       |";
	cout << "\n   |-----+--------------------+----------------------------------------+---------------|";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                            	                       	       |";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);	cout << "    XUAT DANH SACH MON HOC    ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(15, 6);	cout << "MA MON HOC";
	gotoXY(46, 6);	cout << "TEN MON HOC";
	gotoXY(73, 6);	cout << "STCLT";
	gotoXY(81, 6);	cout << "STCTH";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(14);	cout << ": Exit";
	gotoXY(18, 24);	TextColor(252);	cout << "F1";
	TextColor(14);	cout << ": Insert";
	gotoXY(35, 24);	TextColor(252);	cout << "F2";
	TextColor(14);	cout << ": Edit";
	gotoXY(50, 24);	TextColor(252);	cout << "F3";
	TextColor(14);	cout << ": Delete";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	TextColor(14); gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Xuat_SV() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |		 |		      |          |	    |	               |";
	cout << "\n   |-----+---------------+--------------------+----------+----------+------------------|";
	cout << "\n   |	 |               |       	      |          |          |                  |";
	cout << "\n   |	 |         	 |		      |	         |	    |                  |";
	cout << "\n   | 	 |	         |		      |		 |	    |                  |";
	cout << "\n   |	 |	         |		      | 	 |          |                  |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                   |";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);	cout << "   XUAT DANH SACH SINH VIEN   ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(35, 6);	cout << "HO";
	gotoXY(51, 6);	cout << "TEN";
	gotoXY(61, 6);	cout << "PHAI";
	gotoXY(72, 6);	cout << "SO DIEN THOAI";
	gotoXY(4, 24);		TextColor(252);		cout << "ESC";
	TextColor(14);		cout << ": Exit";
	gotoXY(20, 24);		TextColor(252);		cout << "F1";
	TextColor(14);		cout << ": Insert";
	gotoXY(36, 24);		TextColor(252);		cout << "F2";
	TextColor(14);		cout << ": Edit";
	gotoXY(50, 24);		TextColor(252);		cout << "F3";
	TextColor(14);		cout << ": Delete";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Nhap_MH() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |		      |					       |       |       |";
	cout << "\n   |-----+--------------------+----------------------------------------+---------------|";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   |	 |		      |					       |       |       |";
	cout << "\n   | 	 |		      |					       |       |       |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                            	                       	       |";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);	cout << "    NHAP DANH SACH MON HOC    ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(15, 6);	cout << "MA MON HOC";
	gotoXY(46, 6);	cout << "TEN MON HOC";
	gotoXY(73, 6);	cout << "STCLT";
	gotoXY(81, 6);	cout << "STCTH";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(14);	cout << ": Exit";
	gotoXY(20, 24);	TextColor(252);	cout << "ENTER";
	TextColor(14);	cout << ": OK";
	gotoXY(36, 24);	TextColor(252);	cout << "CONTROL";
	TextColor(14);	cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
//=============DSSV===========
void Khung_Nhap_SV() {
	gotoXY(0, 0);
	TextColor(14);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------------------+";
	cout << "\n   |     |		 |		      |          |	    |	               |";
	cout << "\n   |-----+---------------+--------------------+----------+----------+------------------|";
	cout << "\n   |	 |               |       	      |          |          |                  |";
	cout << "\n   |	 |         	 |		      |	         |	    |                  |";
	cout << "\n   | 	 |	         |		      |		 |	    |                  |";
	cout << "\n   |	 |	         |		      | 	 |          |                  |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |	 |	         |		      |		 |          |	               |";
	cout << "\n   |-----------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                   |";
	cout << "\n   +-----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);	cout << "   NHAP DANH SACH SINH VIEN   ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(12);	gotoXY(5, 6);    cout << "STT";
	TextColor(14);
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(35, 6);	cout << "HO";
	gotoXY(51, 6);	cout << "TEN";
	gotoXY(61, 6);	cout << "PHAI";
	gotoXY(72, 6);	cout << "SO DIEN THOAI";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(14);	cout << ": Exit";
	gotoXY(20, 24);	TextColor(252);	cout << "ENTER";
	TextColor(14);	cout << ": OK";
	gotoXY(36, 24); TextColor(252);	cout << "CONTROL";
	TextColor(14);	cout << ": LEFT - RIGHT - UP - DOWN";
	gotoXY(95, 9); cout << "^";
	gotoXY(91, 11); cout << "<";
	gotoXY(99, 11); cout << ">";
	gotoXY(95, 13); cout << "v";
	gotoXY(90, 15); cout << "UP";
	gotoXY(90, 17); cout << "DOWN";
	gotoXY(90, 19); cout << "LEFT";
	gotoXY(90, 21); cout << "RIGHT";
	gotoXY(95, 15); cout << ": LEN";
	gotoXY(95, 17); cout << ": XUONG";
	gotoXY(95, 19); cout << ": TRAI";
	gotoXY(95, 21); cout << ": PHAI";
	gotoXY(0, 27);
}
void Khung_Xoa_SV() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Sinh Vien Can Xoa";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(12);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Them_SV() {
	TextColor(228); gotoXY(10, 13); cout << "   MA SINH VIEN              HO              TEN     PHAI     SDT      ";
	gotoXY(10, 14); cout << "  ";
	gotoXY(27, 14); cout << "  ";
	gotoXY(49, 14); cout << "  ";
	gotoXY(61, 14); cout << "  ";
	gotoXY(66, 14); cout << "  ";
	gotoXY(79, 14); cout << "  ";
	gotoXY(10, 15); cout << "                                                                       ";
	TextColor(228);
	gotoXY(55, 15); cout << "Enter:";
	gotoXY(71, 15); cout << "ESC:";
	TextColor(225);	gotoXY(62, 15); cout << "OK";
	gotoXY(76, 15); cout << "Exit";
	TextColor(14);
	gotoXY(12, 14); cout << "               ";
	gotoXY(29, 14); cout << "                    ";
	gotoXY(51, 14); cout << "          ";
	gotoXY(63, 14); cout << "   ";
	gotoXY(68, 14); cout << "           ";
}
void Khung_Sua_SV() {
	TextColor(228);
	gotoXY(30, 13); cout << "                                 ";
	gotoXY(30, 14); cout << "                                 ";
	gotoXY(30, 15); cout << "                                 ";
	gotoXY(33, 13); cout << "Nhap Ma Sinh Vien Can Sua";
	TextColor(228); gotoXY(33, 15); cout << "Enter:";
	gotoXY(51, 15); cout << "ESC:";
	TextColor(225); gotoXY(40, 15); cout << "OK";
	gotoXY(56, 15); cout << "Exit";
	TextColor(12);	gotoXY(33, 14); cout << "                           ";
}
void Khung_Nhap_MaSV() {
	TextColor(228);
	gotoXY(30, 8);	cout << "                                      ";
	gotoXY(30, 9);	cout << "   NHAP VAO MA SINH VIEN DE THAO TAC  ";
	gotoXY(30, 10); cout << "                                      ";
	TextColor(246);
	gotoXY(36, 13); cout << "                         ";
	gotoXY(36, 14); cout << "                         ";
	gotoXY(36, 15); cout << "                         ";
	TextColor(246); gotoXY(37, 13); cout << "    Nhap Ma Sinh Vien  ";
	TextColor(244); gotoXY(38, 15); cout << "Enter:";
	gotoXY(50, 15); cout << "ESC:";
	TextColor(249); gotoXY(44, 15); cout << "OK";
	gotoXY(55, 15); cout << "Exit";
	TextColor(12);	gotoXY(40, 14); cout << "                 ";
}
void Khung_Xuat_DiemSV() {
	gotoXY(0, 0);
	cout << "\n\n\n\n\n   +----------------------------------------------------------------------------------+";
	cout << "\n   |     |		      |					              |       |";
	cout << "\n   |-----+--------------------+-------------------------------------------------------|";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   | 	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   | 	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   | 	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   | 	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   |	 |		      |					              |       |";
	cout << "\n   | 	 |		      |					              |       |";
	cout << "\n   |----------------------------------------------------------------------------------|";
	cout << "\n   |                                            	                      	      |";
	cout << "\n   +----------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(33, 1);	cout << "                              ";
	gotoXY(33, 2);	cout << "      XEM DIEM SINH VIEN      ";
	gotoXY(33, 3);	cout << "                              ";
	TextColor(14);	gotoXY(5, 6);    cout << "STT";
	gotoXY(15, 6);	cout << "MA MON HOC";
	gotoXY(46, 6);	cout << "TEN MON HOC";
	gotoXY(80, 6);	cout << "DIEM";
	gotoXY(0, 27);
}
//===========================
int	 ThongBao_ESC() {
	int key, count = 0;
	TextColor(206);
	gotoXY(25, 12);
	cout << "     Ban Co Muon Luu Vao File!   ";
	gotoXY(25, 13);	cout << "   ";
	gotoXY(55, 13);	cout << "   ";
	gotoXY(25, 14);	cout << "   ";
	gotoXY(55, 14);	cout << "   ";
	gotoXY(25, 15);	cout << "   ";
	gotoXY(55, 15);	cout << "   ";
	gotoXY(25, 16);	cout << "                                 ";
	TextColor(238);
	gotoXY(28, 13); cout << "                           ";
	gotoXY(28, 14); cout << "                           ";
	gotoXY(28, 15); cout << "                           ";
	TextColor(252);	gotoXY(33, 14);	cout << " YES ";
	TextColor(233);	gotoXY(45, 14);	cout << " NO ";
	gotoXY(34, 14);
	while (1) {
		key = GetKey1();
		if (key == LEFT || key == RIGHT) {
			count++;
			if (count % 2 == 1) {
				TextColor(233);		gotoXY(33, 14); cout << " YES ";
				TextColor(252);		gotoXY(45, 14); cout << " NO ";
				gotoXY(46, 14);
			}
			else {
				TextColor(252);		gotoXY(33, 14); cout << " YES ";
				TextColor(233);		gotoXY(45, 14); cout << " NO ";
				gotoXY(34, 14);
			}
		}
		if (key == ENTER) {
			if (count == 0) {
				return 1;
			}
			else {
				if (count % 2 == 1) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		if (key == ESC) {
			return -1;
		}
	}
}
int	 ThongBao_Thoat() {
	int key, count = 0;
	TextColor(206);
	gotoXY(25, 12);
	cout << "        BAN CO MUON THOAT?       ";
	gotoXY(25, 13);	cout << "   ";
	gotoXY(55, 13);	cout << "   ";
	gotoXY(25, 14);	cout << "   ";
	gotoXY(55, 14);	cout << "   ";
	gotoXY(25, 15);	cout << "   ";
	gotoXY(55, 15);	cout << "   ";
	gotoXY(25, 16);	cout << "                                 ";
	TextColor(238);
	gotoXY(28, 13); cout << "                           ";
	gotoXY(28, 14); cout << "                           ";
	gotoXY(28, 15); cout << "                           ";
	TextColor(252);	gotoXY(33, 14);	cout << " YES ";
	TextColor(233);	gotoXY(45, 14);	cout << " NO ";
	gotoXY(34, 14);
	while (1) {
		key = GetKey1();
		if (key == LEFT || key == RIGHT) {
			count++;
			if (count % 2 == 1) {
				TextColor(233);		gotoXY(33, 14); cout << " YES ";
				TextColor(252);		gotoXY(45, 14); cout << " NO ";
				gotoXY(46, 14);
			}
			else {
				TextColor(252);		gotoXY(33, 14); cout << " YES ";
				TextColor(233);		gotoXY(45, 14); cout << " NO ";
				gotoXY(34, 14);
			}
		}
		if (key == ENTER) {
			if (count == 0) {
				return 1;
			}
			else {
				if (count % 2 == 1) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		if (key == ESC) {
			return -1;
		}
	}
}
int  ThongBao_Xoa() {
	int key, count = 0; TextColor(206);
	gotoXY(25, 12);	cout << "   Ban Co Chac Chan Muon Xoa!    ";
	gotoXY(25, 13);	cout << "   ";	gotoXY(55, 13);	cout << "   ";
	gotoXY(25, 14);	cout << "   ";	gotoXY(55, 14);	cout << "   ";
	gotoXY(25, 15);	cout << "   ";	gotoXY(55, 15);	cout << "   ";
	gotoXY(25, 16);	cout << "                                 ";
	TextColor(238);	gotoXY(28, 13); cout << "                           ";
	gotoXY(28, 14); cout << "                           ";
	gotoXY(28, 15); cout << "                           ";
	TextColor(252);	gotoXY(33, 14);	cout << " YES ";
	TextColor(233);	gotoXY(45, 14);	cout << " NO ";
	gotoXY(34, 14);
	while (1) {
		key = GetKey1();
		if (key == LEFT || key == RIGHT) {
			count++;
			if (count % 2 == 1) {
				TextColor(233);				gotoXY(33, 14); cout << " YES ";
				TextColor(252);				gotoXY(45, 14); cout << " NO ";
				gotoXY(46, 14);
			}
			else {
				TextColor(252);				gotoXY(33, 14); cout << " YES ";
				TextColor(233);				gotoXY(45, 14); cout << " NO ";
				gotoXY(34, 14);
			}
		}
		if (key == ENTER) {
			if (count == 0) {
				return 1;
			}
			else {
				if (count % 2 == 1) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		if (key == ESC || key == DELETE) {
			return -1;
		}
	}
}
int  ThongBao_ESC_Nhap() {
	int key, count = 0;	TextColor(206);
	gotoXY(25, 26);	cout << "     Ban Co Muon Luu Vao File!   ";
	gotoXY(25, 27);	cout << "   ";	gotoXY(55, 27);	cout << "   ";
	gotoXY(25, 28);	cout << "   ";	gotoXY(55, 28);	cout << "   ";
	gotoXY(25, 29);	cout << "   ";	gotoXY(55, 29);	cout << "   ";
	gotoXY(25, 30);	cout << "                                 ";
	TextColor(238);	gotoXY(28, 27); cout << "                           ";
	gotoXY(28, 28); cout << "                           ";
	gotoXY(28, 29); cout << "                           ";
	TextColor(252);	gotoXY(33, 28);	cout << " YES ";
	TextColor(233);	gotoXY(45, 28);	cout << " NO ";
	gotoXY(34, 28);
	while (1) {
		key = GetKey1();
		if (key == LEFT || key == RIGHT) {
			count++;
			if (count % 2 == 1) {
				TextColor(233);				gotoXY(33, 28); cout << " YES ";
				TextColor(252);				gotoXY(45, 28); cout << " NO ";
				gotoXY(46, 28);
			}
			else {
				TextColor(252);				gotoXY(33, 28); cout << " YES ";
				TextColor(233);				gotoXY(45, 28); cout << " NO ";
				gotoXY(34, 28);
			}
		}
		if (key == ENTER) {
			if (count == 0) {
				return 1;
			}
			else {
				if (count % 2 == 1) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		if (key == ESC) {
			TextColor(91);			gotoXY(24, 26);	cout << "                                   ";
			gotoXY(24, 27);	cout << "                                   ";
			gotoXY(24, 28);	cout << "                                   ";
			gotoXY(24, 29);	cout << "                                   ";
			gotoXY(24, 30);	cout << "                                   ";
			return -1;
		}
	}
}
void Khung_NK_HK_MMH() {
	TextColor(228);
	gotoXY(10, 6);	cout << "              NHAP VAO CAC THONG TIN DUOI DAY DE THAO TAC             ";
	gotoXY(10, 8);	cout << "                                                                      ";
	gotoXY(10, 9);  cout << "  MA MON HOC                                                          ";
	gotoXY(10, 10);	cout << "                                                                      ";
	gotoXY(10, 11); cout << "  NIEN KHOA                                                           ";
	gotoXY(10, 12);	cout << "                                                                      ";
	gotoXY(10, 13); cout << "  HOC KI                                                              ";
	gotoXY(10, 14);	cout << "                                                                      ";
	gotoXY(10, 15); cout << "  NHOM                                                                ";
	gotoXY(10, 16);	cout << "                                                                      ";
	TextColor(12);
	gotoXY(25, 9);	cout << "                                                     ";
	gotoXY(25, 11);	cout << "                                                     ";
	gotoXY(25, 13);	cout << "                                                     ";
	gotoXY(25, 15);	cout << "                                                     ";
}
void Khung_Xuat_NK() {
	TextColor(14);	gotoXY(23, 8); cout << "                                     ";
	gotoXY(23, 9); cout << "  XUAT DANH SACH LOP THEO NIEN KHOA  ";
	gotoXY(23, 10); cout << "                                     ";
	TextColor(111); gotoXY(30, 13); cout << "                         ";
	gotoXY(30, 14); cout << "                         ";
	gotoXY(30, 15); cout << "                         ";
	TextColor(107); gotoXY(36, 13); cout << "Nhap Nien Khoa";
	TextColor(108); gotoXY(31, 15); cout << "Enter:";
	gotoXY(45, 15); cout << "ESC:";
	TextColor(105); gotoXY(38, 15); cout << "OK";
	gotoXY(50, 15); cout << "Exit";
	TextColor(12);	gotoXY(41, 14); cout << "    ";
}


void ThongTinChung() {
	TextColor(244); gotoXY(35, 1); cout << "                                                  ";
	gotoXY(35, 2); cout << "    CHUONG TRINH QUAN LY DANG KI MON HOC          ";
	gotoXY(35, 3); cout << "                                                  ";
	TextColor(228);
	gotoXY(35, 0); cout << "         DANG QUANG HUY - N19DCCN073              ";
	gotoXY(35, 1); cout << "         VU CAO KY      - N19DCCN084              ";
	gotoXY(35, 4); cout << "                                                  ";
	gotoXY(35, 2); cout << "  "; gotoXY(83, 2); cout << "  ";
	gotoXY(35, 3); cout << "  "; gotoXY(83, 3); cout << "  ";
	TextColor(240);
	char s[] = { "    CHUONG TRINH QUAN LY DANG KI MON HOC     " };
	int m = strlen(s) - 1;	TextColor(240);
	while (!_kbhit()) {
		for (int i = m; i > 0; i--) {
			s[i] = s[i - 1];
			s[0] = s[m - 1];
		}
		gotoXY(38, 2);       cout << s;
		gotoXY(38, 2); cout << " ";	   Sleep(100);
	}
	TextColor(14);
}
void Khung_Xuat_Diem_TB() {
	gotoXY(0, 0); TextColor(90); cout << "\n\n\n\n\n   +-----------------------------------------------------------------------+";
	cout << "\n   |     |		 |		      |          |	    |      |";
	cout << "\n   |-----+---------------+--------------------+----------+----------+------|";
	cout << "\n   |	 |               |       	      |          |          |      |";
	cout << "\n   |	 |         	 |		      |	         |	    |      |";
	cout << "\n   | 	 |	         |		      |		 |	    |      |";
	cout << "\n   |	 |	         |		      | 	 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |	 |	         |		      |		 |          |      |";
	cout << "\n   |-----------------------------------------------------------------------|";
	cout << "\n   |              		                         	  	   |";
	cout << "\n   +-----------------------------------------------------------------------+";
	TextColor(236);	gotoXY(25, 1);	cout << "                               ";
	gotoXY(25, 2);	cout << " BANG THONG KE DIEM TRUNG BINH ";
	gotoXY(25, 3);	cout << "                               ";
	TextColor(94);	gotoXY(5, 6);    cout << "STT";
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(35, 6);	cout << "HO";
	gotoXY(50, 6);	cout << "TEN";
	gotoXY(61, 6);	cout << "PHAI";
	gotoXY(70, 6);	cout << "DTB";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(91);	cout << ": Exit";
	gotoXY(20, 24);	TextColor(252);	cout << "ENTER";
	TextColor(91);	cout << ": OK";
	gotoXY(36, 24);	TextColor(252);	cout << "CONTROL";
	TextColor(91);	cout << ": LEFT - RIGHT - UP - DOWN";
	TextColor(12); gotoXY(8, 26); cout << "None: Sinh Vien chua duoc cap nhat du lieu Diem!";
	gotoXY(0, 27);
}
void Khung_Tong_Ket() {
	gotoXY(0, 0);	TextColor(90);
	cout << "\n\n\n\n\n   +-----------------------------------------------------------------------------------------------+";
	cout << "\n   |     |		 |		      |          |             |             |             |";
	cout << "\n   |-----+---------------+--------------------+----------+-------------+-------------+-------------|";
	cout << "\n   |     |               |       	      |          |             |             |             |";
	cout << "\n   |     |         	 |		      |	         |	       |             |             |";
	cout << "\n   |     |	         |		      |		 |	       |             |             |";
	cout << "\n   |     |	         |		      | 	 |             |             |             |";
	cout << "\n   |     |	         |		      |		 |             |       	     |             |";
	cout << "\n   |     |	         |		      |		 |             |	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |  	   |";
	cout << "\n   |	 |	         |		      |		 |             |  	     | 	           |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |	 |	         |		      |		 |             |  	     |             |";
	cout << "\n   |-----------------------------------------------------------------------------------------------|";
	cout << "\n   |                                                                                               |";
	cout << "\n   +-----------------------------------------------------------------------------------------------+";
	TextColor(236);	gotoXY(38, 1);	cout << "                             ";
	gotoXY(38, 2);	cout << "     BANG DIEM TONG KET      ";
	gotoXY(38, 3);	cout << "                             ";
	TextColor(94);	gotoXY(5, 6);    cout << "STT";
	gotoXY(12, 6);	cout << "MA SINH VIEN";
	gotoXY(35, 6);	cout << "HO";
	gotoXY(51, 6);	cout << "TEN";
	gotoXY(4, 24);	TextColor(252);	cout << "ESC";
	TextColor(91);	cout << ": Exit";
	gotoXY(38, 24);	TextColor(252);	cout << "UP - DOWN";
	TextColor(91);	cout << ": Page Sinh Vien";
	gotoXY(70, 24);	TextColor(252);	cout << "LEFT - RIGHT";
	TextColor(91);	cout << ": Page Mon Hoc";
	TextColor(12); gotoXY(30, 26); cout << "None: Sinh Vien chua duoc cap nhat du lieu Diem!";
	gotoXY(0, 27);
}
