#include<iostream>
#include<conio.h>
#include<windows.h>       // fix hien khung xem lop khi nhap
#include<string.h>
#include<iomanip>
#include<fstream>
#include"lib.h"

#include <sstream>

#define DOWN -80
#define UP -72
#define LEFT -75
#define RIGHT -77
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SPACE 32
#define F1 -59
#define F2 -60
#define F3 -61
#define F5 -63

#define F8 -66
using namespace std;
#define MAXLTC 100
#define MAXLOP 100
#define MAXSV  100
char a[34] = "Ban chua nhap ma sv";

//-----------------------------------------------------
//------Monhoc------ 
//cay nhi phan
struct NodeMH {
	char mmh[11];	//ma mon hoc
	char tmh[51];	// ten mon hoc
	int stclt;		// so tinh chi li thuyet
	int stcth;		// so tinh chi thuc hanh
};
struct dsmh {
	NodeMH data;
	dsmh *left;
	dsmh *right;
};
typedef dsmh *PTRMH;
//-------------------------------------------------------------------------------------------
//------danh sach sinh vien------
//danh sach lien ket don
struct NodeSV {
	char mssv[16]; 	//ma sinh vien
	char ho[21]; 	//ho sinh vien
	char ten[11];	//ten sinh vien
	char phai[4]; 	// gioi tinh
	char sdt[12]; 	// so dien thoai
	char malop[16];
};
struct dssv {
	NodeSV data;
	dssv *next;
};
typedef dssv *PTRSV;
//------quan li lop------
//struct Nodelop {
//	char malop[16];
//	char tenlop[31];
//	char nienkhoa[5];
//	PTRSV DSSV; // con tro toi danh sach sinh vien
//};
//struct ListLop {
//	int n;
//	Nodelop dsl[MAXLOP];
//};
//------danh sach dang ki------
//danh sach lien ket don
struct NodeDK {
	char mssv[16]; //ma sinh vien
	char  diem[4]; 	//diem
};
struct dsdk {
	NodeDK data;
	dsdk *next;
};
typedef dsdk *PTRDK;
//---------------------DSLTC--------------------------------

struct Ltc {
	int  malopTc; 		//ma lop
	char mmh[11];		//ma mon hoc
	char nienkhoa[5];		// nien khoa
	int  hocki; 		// hoc ki
	int  nhom; 			//nhom
	int  nsvmax;
	int nsvmin;
	bool huy = 0;
	PTRDK DSDK = NULL;
};
struct	Dslop {
	int n;
	Ltc *nodeltc[MAXLTC];
};

//Bat ph˙ä
int GetKey()
{
	char key;
	key = _getch();
	if (key == -32 || key == 0)
		return -_getch();
	else return key;
}
//Ghi chÅE
void GhiChu(char c[], int x, int y, int color, int sleep)
{

	gotoXY(x, y);
	TextColor(color);
	cout << c;
	Sleep(sleep);
	gotoXY(x, y);
	TextColor(14);
	for (int j = 0; j <= strlen(c); j++)
	{
		cout << ' ';
	}

}

int	 ThongBao_ESCaoky() {
	int key, count = 0;
	TextColor(206);
	gotoXY(25, 12);
	cout << "     Ban Chac Chan Muon Xoa!     ";
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

char MENU[5][40] = {
	"  1.Quan Ly Lop Tin Chi ",
	"  2.Quan Ly Sinh Vien   ",
	"  3.Quan Ly Mon Hoc     ",
	"  4.Quan Ly Dang Ki     ",
	"  5.Thoat               " };

char MENUloptc[4][40] = {
	"  1. Nhap Danh Sach Lop Tin Chi ",
	"  2. Xem Danh Sach Lop Tin Chi  ",
	"  3. Xem Diem Lop Tin Chi       ",
	"  4. Xoa lop Tin Chi            "
};

//char MENUlop[1][40] = {
////	"  1. Nhap Danh Sach Lop         ",
//	"  1. Xem Danh Sach Lop          "
////	"  3. Xem diem Trung Binh        ", 
//	//"  4. Xem diem Ca lop            "
//};

char MENUsv[3][40] = {
	"  1. Nhap Danh Sach SV          ",
	"  2. Xem Danh Sach SV           "
 //   "  3. Xem Diem Sinh Vien         "
	};

char MENUmonhoc[1][40] = {
	"         Xem Mon Hoc            " };

char MENUdangki[3][40] = {
	"  1. Dang Ki Lop Tin Chi        ",
	"  2. Xem Danh Sach Dang Ki      ",
	"  3. Nhap Diem                  " };

void ToMauMenuChinh(int color, int vitri)
{
	TextColor(color);
	gotoXY(0, 5 + vitri * 4); cout << "                        ";
	gotoXY(0, 6 + vitri * 4); cout << MENU[vitri];
	gotoXY(0, 7 + vitri * 4); cout << "                        ";
}

void ToMauMenuCon(int color, char MENUCON[][40], int vitri)
{
	TextColor(color);
	gotoXY(28, 5 + (vitri + 1) * 4);	cout << "                                ";
	gotoXY(28, 6 + (vitri + 1) * 4);	cout << MENUCON[vitri];
	gotoXY(28, 7 + (vitri + 1) * 4);	cout << "                                ";
}



int MenuCon(int item, char MENUCON[][40])
{
	
	char key;
	int vitri = 0;	int color = 188; int color1 = 236;
	while (1)
	{
		ThongTinChung();
		key = GetKey();
		if (key == ENTER)
			return vitri + 1;
		if (key == ESC || key == LEFT)
			return 0;
		switch (key)
		{
		case DOWN:
		{
			if (vitri == (item - 1))
			{
				ToMauMenuCon(252, MENUCON, vitri);
				vitri = 0;
				ToMauMenuCon(236, MENUCON, vitri);
			}
			else
			{
				ToMauMenuCon(252, MENUCON, vitri);
				vitri++;
				ToMauMenuCon(236, MENUCON, vitri);
			}
		}break;
		case UP:
		{
			if (vitri == 0)
			{
				ToMauMenuCon(252, MENUCON, vitri);
				vitri = item - 1;
				ToMauMenuCon(236, MENUCON, vitri);
			}
			else
			{
				ToMauMenuCon(252, MENUCON, vitri);
				vitri--;
				ToMauMenuCon(236, MENUCON, vitri);
			}
		}break;
		}
	}
}

int MenuCha()
{
	
	int vitri = 0;
	while (1)
	{
		ThongTinChung();
		char key = GetKey();
		if (key == ENTER || (key == RIGHT && vitri != 5)) // vitri!= 6 la ngay tai o Tho·t
		{
			return vitri + 1;
		}
		switch (key)
		{
		case DOWN:
		{
			if (vitri == 4)
			{
				ToMauMenuChinh(240, vitri);
				vitri = 0;
				ToMauMenuChinh(236, vitri);
			}
			else
			{
				ToMauMenuChinh(240, vitri);
				vitri++;
				ToMauMenuChinh(236, vitri);
			}
		}break;
		case UP:
		{
			if (vitri == 0)
			{
				ToMauMenuChinh(240, vitri);
				vitri = (4);
				ToMauMenuChinh(236, vitri);
			}
			else
			{
				ToMauMenuChinh(240, vitri);
				vitri--;
				ToMauMenuChinh(236, vitri);
			}
		}break;
		}
	}
}
//----them vao cac kieu
bool EmptyDSMH(PTRMH DSMH) {// kiem tra dsmh
	if (NULL == DSMH) return true;
	return false;
}
void InsertNode_MH(PTRMH &DSMH, NodeMH mh) {
	if (EmptyDSMH(DSMH)) {// neu trong thi them  dau 
		PTRMH p = new dsmh;
		p->data = mh;
		p->left = p->right = NULL;
		DSMH = p;
		return;
	}
	else {
		if (0< strcmp(DSMH->data.mmh, mh.mmh)) {
			InsertNode_MH(DSMH->left, mh);
		}
		else {
			InsertNode_MH(DSMH->right, mh);
		}
	}
}
void Insert_TailSV(PTRSV &DSSV, NodeSV sv) {
	PTRSV p = new dssv;
	p->data = sv;
	p->next = NULL;
	if (DSSV == NULL) {
		DSSV = p;
	}
	else {
		for (PTRSV k = DSSV; k != NULL; k = k->next)
		{
			if (k->next == NULL)	//Tim ra Node Tail
			{
				k->next = p;
				k = p;
			}
		}
		return;
	}
}

//void Insert_TailSV(PTRSV &DSSV, NodeSV sv)
//{
//	PTRSV p, t, s;  // t la nut truoc, s la nut sau
//	p = new dssv;
//	p->data = sv;
//	t = NULL;
//	for (s = DSSV; s != NULL && strcmp(s->data.mssv,sv.mssv) < 0 ; t = s, s = s->next);
//	if (s == DSSV)  // them nut vao dau danh sach lien ket
//	{
//		p->next = DSSV;
//		DSSV = p;
//	}
//	else           // them nut p vao truoc nut s
//	{
//		p->next = s;
//		t->next = p;
//	}
//}


void Insert_NodeDk(PTRDK &DSDK, NodeDK svdk) {
	PTRDK p = new dsdk;
	p->data = svdk;
	p->next = NULL;
	if (DSDK == NULL) {
		DSDK = p;
		return;
	}
	else {
		for (PTRDK k = DSDK; k != NULL; k = k->next)
		{
			if (k->next == NULL)	//Tim ra Node Tail
			{
				k->next = p;
				k = p;
			}
		}
		return;
	}
}
int	 KTMaLop(PTRSV ds, char c[], int n)
{
	for (PTRSV p = ds; p->next != NULL; p = p->next)
	{
		if (strcmp(p->data.malop, c) == 0)
		{
			return 1;	// neu co ma lop
		}
	}
	return -1;			// khong tim thay ptu tra 0
}
int  Search_malopTc(Dslop DSLTC, int malopTc, int dem)
{
	for (int i = 0; i < dem; i++)
	{
		//so sanh bang ma lop tin chi
		if (DSLTC.nodeltc[i]->malopTc == malopTc)
		{
			return i; //neu phan trung thi tra ve vi tri i
		}
	}
	return -1; //khong tim thay trung
}
Ltc* TaoLTC()
{
	Ltc *ltc = new Ltc;
	ltc->malopTc = 0;
	ltc->mmh[0] = NULL;
	ltc->hocki = 0;
	ltc->nienkhoa[0] = NULL;
	ltc->nhom = 0;
	ltc->nsvmax = 0;
	ltc->nsvmin = 0;
	ltc->DSDK = NULL;
	ltc->huy = 0;
	return ltc;
}
int  FullLTC(Dslop DSLTC)
{
	return(DSLTC.n == MAXLTC ? TRUE : FALSE);
}
int Maloptc(Dslop &DSLTC){
	if(DSLTC.n == 0)return 1;
	int max = DSLTC.nodeltc[DSLTC.n-1]->malopTc;
//	for(int i = 1; i < DSLTC.n; i++){
//		if(max < DSLTC.nodeltc[i]->malopTc){
//			max = DSLTC.nodeltc[i]->malopTc;
//		}
	
	return max + 1;//ham xu li maloptc
}

int	 InsertLTC(Dslop &DSLTC, Ltc lopTc, int i)
{
	//kiem tra xem danh sach full hay chua
	if (FullLTC(DSLTC))
		return 0;
	else
	{
		//them vao cuoi
		DSLTC.nodeltc[i] = new Ltc;
		DSLTC.nodeltc[i]->malopTc = lopTc.malopTc;
		strcpy(DSLTC.nodeltc[i]->mmh, lopTc.mmh);
		DSLTC.nodeltc[i]->hocki= lopTc.hocki;
		DSLTC.nodeltc[i]->nhom = lopTc.nhom;
		strcpy(DSLTC.nodeltc[i]->nienkhoa, lopTc.nienkhoa);
		DSLTC.nodeltc[i]->nsvmax= lopTc.nsvmax;
		DSLTC.nodeltc[i]->nsvmin= lopTc.nsvmin;
	}
	//them thanh cong, tang so luong phan tu len 1
	DSLTC.n++;
}

void InitLTC(Dslop &DSLTC)//khoi tao
{
	DSLTC.n = 0;
}
//Empty
int EmptyLTC(Dslop DSLTC)
{
	return(DSLTC.n == 0 ? TRUE : FALSE);
}
//Full
Ltc lopTc;
//xoaLTC
void DeleteLTC(Dslop &DSLTC, int i)
{
	//cac truong hop chi so dua vao khong hop le
	if (i<0 || i>DSLTC.n || EmptyLTC(DSLTC))
	{
		return;
	}
	if (i == DSLTC.n)
	{
		delete DSLTC.nodeltc[DSLTC.n];
		DSLTC.n--;
		DSLTC.nodeltc[DSLTC.n] = NULL;//tranh tinh trang con tro bi treo
		return;
	}
	else
	{
		delete DSLTC.nodeltc[i];
		for (int temp = i + 1; temp < DSLTC.n; temp++)
		{
			DSLTC.nodeltc[temp - 1] = DSLTC.nodeltc[temp];
		}
		DSLTC.n--;
		DSLTC.nodeltc[DSLTC.n] = NULL; //tranh tinh trang con tro bi treo
	}
	return;
}
//----thao tac file-------
void DocFileMH(PTRMH &DSMH) {
	ifstream infile;
	string data;
	infile.open("DSMH.txt", ios::in);
	if (!infile) { GhiChu("Khong tim thay file", 35, 27, 79, 2000); return; } //Khong tim thay file
	while (infile.good())
	{
		NodeMH mh;
		getline(infile, data);
		if (data.size() == 0) { break; } //Da co file nhung chua co du lieu
		strcpy(mh.mmh, data.c_str());
		getline(infile, data);		strcpy(mh.tmh, data.c_str());
		infile >> mh.stclt;
		infile.ignore();
		infile >> mh.stcth;
		infile.ignore();
		InsertNode_MH(DSMH, mh);
	}
	infile.close();
}
void GhiFile_LNR(ofstream &file, PTRMH DSMH) // ghi file theo tr·i node phai
{
	if (DSMH != NULL)
	{
		GhiFile_LNR(file, DSMH->left);
		file << DSMH->data.mmh << endl
			<< DSMH->data.tmh << endl
			<< DSMH->data.stclt << endl
			<< DSMH->data.stcth << endl;
		GhiFile_LNR(file, DSMH->right);
	}
}
void GhiFileMH(PTRMH DSMH) {
	ofstream outfile;
	outfile.open("DSMH.txt", ios::out);
	GhiFile_LNR(outfile, DSMH);
	outfile.close();
}
void DocFileDSLTC(Dslop &DSLTC)
{
	ifstream infile;
	infile.open("DSLTC.txt", ios::in);
	if (!infile)
	{
		cout << "\nFile Khong Ton Tai!";
		return;
	}
	int i = 0;
	Ltc lopTc;
	while (infile.good())
	{
		infile >> lopTc.malopTc;
		infile.ignore();
		infile.getline(lopTc.mmh, 11);
		infile.getline(lopTc.nienkhoa, 5);
		infile >> lopTc.hocki;
		infile.ignore();
		infile >> lopTc.nhom;
		infile.ignore();
		infile >> lopTc.nsvmin;
		infile.ignore();
		infile >> lopTc.nsvmax;
		infile.ignore();
		if (infile.eof()) break;
		if (i<MAXLTC)
		{
			InsertLTC(DSLTC, lopTc, DSLTC.n);
			i++;
		}
	}
	infile.close();
}
void GhiFileDSLTC(Dslop DSLTC)
{
	ofstream outfile;
	outfile.open("DSLTC.txt");
	for (int i = 0; i<DSLTC.n; i++)
	{
		outfile << DSLTC.nodeltc[i]->malopTc << endl;
		outfile << DSLTC.nodeltc[i]->mmh << endl;
		outfile << DSLTC.nodeltc[i]->nienkhoa << endl;
		outfile << DSLTC.nodeltc[i]->hocki << endl;
		outfile << DSLTC.nodeltc[i]->nhom << endl;
		outfile << DSLTC.nodeltc[i]->nsvmin << endl;
		outfile << DSLTC.nodeltc[i]->nsvmax << endl;
	}
	outfile.close();
}
void DocFileSV(PTRSV &ds)
{
	string data;
	ifstream infile;
	NodeSV sv;
	infile.open("DSSV.txt", ios::in);
	if (!infile) { return; }
	while (infile.good())
	{
		
		infile.getline(sv.malop, 16);
		
			infile.getline(sv.mssv, 16);	
			infile.getline(sv.ho, 21);		
			infile.getline(sv.ten, 11);		
			infile.getline(sv.phai, 4);		
			infile.getline(sv.sdt, 12);		
			Insert_TailSV(ds, sv);
		
	}
	infile.close();
}
void GhiFileSV(PTRSV ds)
{
	ofstream outfile;
	outfile.open("DSSV.txt", ios::out);
	
			
			for (PTRSV p = ds; p != NULL; p = p->next)
			{
				outfile << p->data.malop << endl;
				outfile << p->data.mssv << endl
					<< p->data.ho << endl
					<< p->data.ten << endl
					<< p->data.phai << endl
					<< p->data.sdt << endl;
			}
	
	outfile.close();
}
//void DocFileLop(ListLop &ds)
//{
//	for (int i = 0; i < MAXLOP; i++)	//Khoi tao Mang rong~
//	{
//		ds.dsl[i].malop[0] = NULL;
//		ds.dsl[i].tenlop[0] = NULL;
//		ds.dsl[i].nienkhoa[0] = NULL;
//		ds.dsl[i].DSSV = NULL;
//	}
//	fstream infile; string data;
//	infile.open("DSLOP.txt", ios::in);
//	if (!infile) { GhiChu("Khong tim thay file", 35, 12, 79, 2000); return; } //Khong tim thay file 
//	while (infile.good())
//	{
//		getline(infile, data);
//		if (data.size() == 0) { break; } // Khi da co file va du lieu rong~
//		strcpy(ds.dsl[ds.n].malop, data.c_str());
//		getline(infile, data);
//		strcpy(ds.dsl[ds.n].tenlop, data.c_str());
//		getline(infile, data);
//		strcpy(ds.dsl[ds.n].nienkhoa, data.c_str());
//		ds.dsl[ds.n].DSSV = NULL;	//Khoi tao con tro dau` DSSV NULL
//		ds.n++;
//	}
//	infile.close();
//}
//void GhiFileLop(ListLop ds)
//{
//	int n = 0;
//	ofstream outfile;
//	outfile.open("DSLOP.txt", ios::out);
//	while (n < ds.n)
//	{
//		outfile << ds.dsl[n].malop << endl
//			<< ds.dsl[n].tenlop << endl
//			<< ds.dsl[n].nienkhoa << endl;
//		n++;
//	}
//	outfile.close();
//}
void DocFileDSDK(Dslop &DSLTC)
{
	int temp, vitri;
	string data;
	char a[11];
	int malopTc;
	ifstream infile;
	infile.open("DSDK.txt", ios::in);
	if (!infile) { return; }
	while (infile.good())
	{
		NodeDK svdk;
		getline(infile, data);
		if (data.size() == 0) { break; }
		strcpy(a, data.c_str());
		malopTc = atoi(a);// atoi chuyen so nguyen thanh chuoi
		temp = Search_malopTc(DSLTC, malopTc, DSLTC.n);
		if (temp != -1)
		{
			vitri = temp;
		}
		else {
			strcpy(svdk.mssv, data.c_str());
			getline(infile, data);		strcpy(svdk.diem, data.c_str());
			Insert_NodeDk(DSLTC.nodeltc[vitri]->DSDK, svdk);

		}
	}
	infile.close();
}
void GhiFileDK(Dslop DSLTC)
{
	ofstream outfile;
	outfile.open("DSDK.txt", ios::out);
	for (int i = 0; i < DSLTC.n; i++)
	{
		if (DSLTC.nodeltc[i]->DSDK != NULL) //Kiem tra Lop cÛ Sinh Vien moi' nap. vao`
		{
			outfile << DSLTC.nodeltc[i]->malopTc << endl;
			for (PTRDK p = DSLTC.nodeltc[i]->DSDK; p != NULL; p = p->next)
			{
				outfile << p->data.mssv << endl
					<< p->data.diem << endl;
			}
		}
	}
	outfile.close();
}

//-----------------------DANH SACH MON HOC--------------------------------------------------------------------------------------------------------------------

int Search_MH_LTC(Dslop DSLTC, char mh[]) { // tim kiem mamonhoc trong ltc
	for (int i = 0; i < DSLTC.n; i++) {
		if (0 == strcmp(DSLTC.nodeltc[i]->mmh, mh)) {
			return i;// tra ve gia tri i;
		}
	}
	return -1;
}

int KTMH(PTRMH DSMH, char mh[]) {//ktra trong cay
	if (DSMH == NULL)
	{
		return 0;
	}
	else {
		if (strcmp(DSMH->data.mmh, mh) == 0)
		{
			return 1;// neu tim thay mamh 
		}
		else if (strcmp(DSMH->data.mmh, mh) >0)
		{
			KTMH(DSMH->left, mh);
		}
		else {
			KTMH(DSMH->right, mh);
		}
	}
}

PTRMH Search_MH(PTRMH &DSMH, char mh[]) {
	if (EmptyDSMH(DSMH)) { return NULL; }
	else {
		if (0 == strcmp(DSMH->data.mmh, mh)) {
			return DSMH;
		}
		else if (0< strcmp(DSMH->data.mmh, mh)) {
			Search_MH(DSMH->left, mh);
		}
		else {
			Search_MH(DSMH->right, mh);
		}
	}
}
//--them mon hoc

int demchu(int n){
	int ans = 0;
	while ( n> 0){
		ans += 1;
		n/=10;
	}
	return ans;
}

void ThemMonHoc(PTRMH &DSMH, bool &check_change)
{
	int key, vitri = 0, x = 12, y = 14, check_trung;
	NodeMH mh;	mh.mmh[0] = NULL;	mh.tmh[0] = NULL;	mh.stclt = 0;	mh.stcth = 0;
	Khung_Them_MonHoc(); gotoXY(x, y);
MAMH:
	while (1)
	{
		TextColor(250);	gotoXY(10, 15);
		cout << "Ki tu: (A-Z) & (0-9). Toi da: 10";
		TextColor(12); gotoXY(12 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			mh.mmh[vitri] = char(key);
			mh.mmh[vitri] = toupper(mh.mmh[vitri]);
			cout << mh.mmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			mh.mmh[vitri] = '\0';
			check_trung = KTMH(DSMH, mh.mmh);
			if (check_trung == 1) {
				TextColor(78);	gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			vitri = strlen(mh.tmh);
			gotoXY(30 + vitri, y);
			goto TENMH;
		}
		if (key == RIGHT)
		{
			mh.mmh[vitri] = '\0';
			check_trung = KTMH(DSMH, mh.mmh);
			if (check_trung == 1) {
				TextColor(78);	gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500); continue;
			}
			vitri = strlen(mh.tmh);
			gotoXY(30 + vitri, y);
			goto TENMH;
		}
		if (key == ESC || key == F1) { return; }
	}
TENMH:
	while (1)
	{
		TextColor(250);	gotoXY(10, 15);
		cout << "Ki tu: (A-Z) & (0-9). Toi da: 50";
		TextColor(12); gotoXY(30 + vitri, y); //Ghi ch˙
		key = GetKey();
		if (mh.mmh[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ma Mon Hoc!", 35, 27, 79, 700);
			gotoXY(12, y);
			goto MAMH;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 35))
		{
			mh.tmh[vitri] = char(key);
			mh.tmh[vitri] = toupper(mh.tmh[vitri]);
			cout << mh.tmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(30 + vitri, y);
			cout << " ";
			gotoXY(30 + vitri, y);
		}
		if (key == SPACE && mh.tmh[vitri - 1] != ' ' && vitri > 0 && vitri < 35) // ko cho 2 khoang trang && vitri = 0
		{
			gotoXY(30 + vitri, y);
			cout << " ";
			mh.tmh[vitri] = ' ';
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			if (mh.tmh[vitri - 1] == ' ') { vitri--; } //Kiem tra ki tu cuoi cung la khoang trang thi xoa khoang trang
			mh.tmh[vitri] = '\0';
			vitri = demchu(mh.stclt);
			gotoXY(72 + vitri, y);
			goto STCLT;
		}
		if (key == LEFT)
		{
			mh.tmh[vitri] = '\0';
			vitri = strlen(mh.mmh);
			gotoXY(12 + vitri, y);
			goto MAMH;
		}
		if (key == RIGHT)
		{
			if (mh.tmh[vitri - 1] == ' ') { vitri--; } //Kiem tra ki tu cuoi cung la khoang trang thi xoa khoang trang
			mh.tmh[vitri] = '\0';
			vitri = demchu(mh.stclt);
			gotoXY(72 + vitri, y);
			goto STCLT;
		}
		if (key == ESC || key == F1) { return; }
	}
STCLT:
	while (1)
	{
		TextColor(250);	gotoXY(10, 15);
		cout << "Ki tu: (0-9). Toi da: 1         ";
		TextColor(12); gotoXY(72 + vitri, y); // Ghi ch˙
		key = GetKey();
		if (mh.tmh[0] == '\0')
		{
			GhiChu("Ban Chua Nhap TEN Mon Hoc!", 35, 27, 79, 700);
			gotoXY(30, y);
			goto TENMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 1))
		{
			mh.stclt = key - 48;
			cout << mh.stclt;
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			mh.stclt = mh.stclt/10;
			gotoXY(72 + vitri, y);
			cout << " ";
			gotoXY(72 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{

			vitri = demchu(mh.stcth);
			gotoXY(79 + vitri, y);
			goto STCTH;
		}
		if (key == LEFT)
		{

			vitri = strlen(mh.tmh);
			gotoXY(30 + vitri, y);
			goto TENMH;
		}
		if (key == RIGHT)
		{

			vitri = demchu(mh.stcth);
			gotoXY(79 + vitri, y);
			goto STCTH;
		}
		if (key == ESC || key == F1) { return; }
	}
STCTH:
	while (1)
	{
		TextColor(250);	gotoXY(10, 15);
		cout << "Ki tu: (0-9). Toi da: 1         ";
		TextColor(12); gotoXY(79 + vitri, y); // Ghi ch˙
		key = GetKey();
		if (mh.stclt == 0)
		{
			GhiChu("Ban Chua Nhap STCLT Mon Hoc!", 35, 27, 79, 700);
			gotoXY(72, y);
			goto STCLT;
		}
		if ((key <= '9' && key >= '0') && (vitri < 1))
		{
			mh.stcth = key -48;

			cout << mh.stcth;
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			mh.stcth = mh.stcth/10;
			gotoXY(79 + vitri, y);
			cout << " ";
			gotoXY(79 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			InsertNode_MH(DSMH, mh);
			GhiChu("Them Thanh Cong", 35, 27, 79, 1000);
			return;
		}
		if (key == LEFT)
		{

			vitri = demchu(mh.stclt);
			gotoXY(67 + vitri, y);
			goto STCLT;
		}
		if (key == ESC || key == F1) { return; }
	}
}


//--xoa mon hoc
void PhanTuTheMang(PTRMH &p, PTRMH &q) {
	if (q->left != NULL)
	{
		PhanTuTheMang(p, q->left);
	}
	else {
		p->data = q->data;			//cap nhat du lieu vÙ c˘ng tr·i sang con tro can xÛa
		p = q;						//cap nhat dia chi vÙ c˘ng tr·i sang con tro can xÛa
		q = q->right;				//ben phai cua vÙ c˘ng trai' dÙn` lÍn
	}
}
void DeleteNode_MH(PTRMH &DSMH, char c[]) {
	if (DSMH == NULL) { return; }
	//Truong hop root > hoac < char c
	if (strcmp(DSMH->data.mmh, c) >0)
	{
		DeleteNode_MH(DSMH->left, c);// tim node
	}
	else if (strcmp(DSMH->data.mmh, c) <0)
	{
		DeleteNode_MH(DSMH->right, c);// tim node
	}
	//Truong Hop root == char c
	else {
		PTRMH p = DSMH;		//Cho con tro tai vi tri muon xoa vao 1 con tro? tam. de lat' xoa
		if (DSMH->left == NULL && DSMH->right == NULL)	//Truong hop 2 nhanh con NULL
		{
			delete DSMH; DSMH = NULL; return; //xoa node cuoi
		}
		if (DSMH->left == NULL && DSMH->right != NULL)	//Truong hop co nhanh con ben phai
		{
			DSMH = DSMH->right;//tro den node phai
		}
		else if (DSMH->right == NULL && DSMH->left != NULL) //Truong hop co nhanh con ben trai
		{
			DSMH = DSMH->left;//tro den node trai
		}
		//Truong hop ca 2 nhanh con deu != NULL
		else {
			PhanTuTheMang(p, DSMH->right);
			delete p;
		}
	}
}
void XoaMonHoc(Dslop &DSLTC, PTRMH &DSMH, bool &check_change)
{
	int key, x = 33, y = 14, vitri = 0;
	NodeMH mh;	mh.mmh[0] = NULL;
	Khung_Xoa_MonHoc();	gotoXY(x, y);
Reset:
	while (1)
	{
		TextColor(14);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 15))
		{
			mh.mmh[vitri] = char(key);
			mh.mmh[vitri] = toupper(mh.mmh[vitri]);
			cout << mh.mmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			mh.mmh[vitri] = '\0';	//Ngat chuoi~
			int temp1 = KTMH(DSMH, mh.mmh);// kiem tra mon hoc co ton tai khong
			if (temp1 != 0) //ton tai
			{
				int temp2 = Search_MH_LTC(DSLTC, mh.mmh);// kiem tra da mo lop tin chi chua
				if (temp2 == -1) { // chua mo -> xoa
					check_change = true;
					DeleteNode_MH(DSMH, mh.mmh);
					GhiChu("XOA THANH CONG MON HOC!", 20, 27, 79, 500);
					return;
				}
				else { //da mo
					int dem = 0;
					for (int i = 0; i < DSLTC.n; i++) {
						dem++;
						if (strcmp(DSLTC.nodeltc[i]->mmh, mh.mmh) == 0) {
							if (DSLTC.nodeltc[i]->DSDK != NULL) {// kiem tra mon hoc co ds
								GhiChu("Mon Hoc da co danh sach dang ki khong the Xoa!", 20, 27, 79, 500); TextColor(12);
								gotoXY(33 + vitri, y); goto Reset; break;
							}
						}
					}
					if (dem == DSLTC.n) {
						check_change = true;
						while (temp2 != -1) {
							DeleteLTC(DSLTC, temp2);//xoa mh co ds loptc xoa mh va xoa ca ltc
							temp2 = Search_MH_LTC(DSLTC, mh.mmh);
						}
						DeleteNode_MH(DSMH, mh.mmh);
						GhiChu("XOA THANH CONG MON HOC!", 20, 27, 79, 500);
						return;
					}
				}
			}
			else {
				GhiChu("Ma Mon Hoc Khong Ton Tai!", 35, 27, 79, 500);
				TextColor(14);
				gotoXY(33 + vitri, y);
			}
		}
		if (key == ESC || key == F3) { return; }
	}
}

//--sua mon hoc----
void SuaMonHoc(Dslop &DSLTC, PTRMH &DSMH, bool &check_change)
{
	int key, vitri = 0, x = 33, y = 14, check_trung;
	PTRMH p;
	char tam[11]; //de luu ma mon nhap vao
	NodeMH mh;	mh.mmh[0] = NULL;	mh.tmh[0] = NULL;	mh.stclt = 0;	mh.stcth = 0;
	Khung_Sua_MonHoc(); gotoXY(x, y);
	//dau tien phai tim cai vi tri cua ma mon da
	while (1)
	{
		TextColor(14);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 15))
		{
			mh.mmh[vitri] = char(key);
			mh.mmh[vitri] = toupper(mh.mmh[vitri]);
			cout << mh.mmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			mh.mmh[vitri] = '\0';	//Ngat chuoi~
			strcpy(tam, mh.mmh);
			check_trung = KTMH(DSMH, mh.mmh); //KT trung`. 1: trung, co ton tai 0: ko trung
			if (check_trung == 1)
			{
				vitri = 0;
				p = Search_MH(DSMH, mh.mmh);
				Khung_Them_MonHoc();
				x = 12, y = 14;
				gotoXY(x, y);
				TextColor(4);
				strcpy(mh.mmh, p->data.mmh);
				strcpy(mh.tmh, p->data.tmh);
				mh.stclt= p->data.stclt;
				mh.stcth= p->data.stcth;
				gotoXY(12, y); cout << mh.mmh;
				gotoXY(30, y); cout << mh.tmh;
				gotoXY(67, y); cout << mh.stclt;
				gotoXY(75, y); cout << mh.stcth;// in ra cac du lieu da co
				vitri = strlen(mh.mmh);
				goto MAMH;
				break;
			}
			else {
				GhiChu("Ma Mon Hoc Khong Ton Tai!", 35, 27, 79, 500);	TextColor(12);	gotoXY(33 + vitri, y);
			}
		}
		if (key == ESC || key == F2) { return; }
	}

MAMH:
	while (1)
	{
		TextColor(244);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 10";
		TextColor(14); gotoXY(12 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			mh.mmh[vitri] = char(key);
			mh.mmh[vitri] = toupper(mh.mmh[vitri]);
			cout << mh.mmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			mh.mmh[vitri] = '\0';
			check_trung = KTMH(DSMH, mh.mmh);
			if (check_trung == 1 && strcmp(mh.mmh, tam) != 0) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			else {
				vitri = strlen(mh.tmh);
				gotoXY(30 + vitri, y);
				goto TENMH;
			}
		}
		if (key == RIGHT)
		{
			mh.mmh[vitri] = '\0';
			check_trung = KTMH(DSMH, mh.mmh);
			if (check_trung == 1 && strcmp(mh.mmh, tam) != 0) { // strcmp: khong sua gi van ok
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			else {
				vitri = strlen(mh.tmh);
				gotoXY(30 + vitri, y);
				goto TENMH;
			}
		}
		if (key == ESC || key == F1) { return; }
	}
TENMH:
	while (1)
	{
		TextColor(244);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 35";
		TextColor(14); gotoXY(30 + vitri, y); //Ghi ch˙
		key = GetKey();
		if (mh.mmh[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ma Mon Hoc!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(12 + vitri, y);
			goto MAMH;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 35))
		{
			mh.tmh[vitri] = char(key);
			mh.tmh[vitri] = toupper(mh.tmh[vitri]);
			cout << mh.tmh[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(30 + vitri, y);
			cout << " ";
			gotoXY(30 + vitri, y);
		}
		if (key == SPACE && mh.tmh[vitri - 1] != ' ' && vitri > 0 && vitri < 35) // ko cho 2 khoang trang && vitri = 0
		{
			gotoXY(30 + vitri, y);
			cout << " ";
			mh.tmh[vitri] = ' ';
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			if (mh.tmh[vitri - 1] == ' ') { vitri--; } //Kiem tra ki tu cuoi cung la khoang trang thi xoa khoang trang
			mh.tmh[vitri] = '\0';
			vitri = demchu(mh.stclt);
			gotoXY(67 + vitri, y);
			goto STCLT;
		}
		if (key == LEFT)
		{
			mh.tmh[vitri] = '\0';
			vitri = strlen(mh.mmh);
			gotoXY(12 + vitri, y);
			goto MAMH;
		}
		if (key == RIGHT)
		{
			if (mh.tmh[vitri - 1] == ' ') { vitri--; } //Kiem tra ki tu cuoi cung la khoang trang thi xoa khoang trang
			mh.tmh[vitri] = '\0';
			vitri = demchu(mh.stclt);
			gotoXY(67 + vitri, y);
			goto STCLT;
		}
		if (key == ESC || key == F1) { return; }
	}
STCLT:
	while (1)
	{
		TextColor(244);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 3         ";
		TextColor(14); gotoXY(67 + vitri, y); // Ghi ch˙
		key = GetKey();
		if (mh.tmh[0] == '\0')
		{
			GhiChu("Ban Chua Nhap TEN Mon Hoc!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(30 + vitri, y);
			goto TENMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 1))
		{
			mh.stclt = key - 48;
			cout << mh.stclt;
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			mh.stclt = mh.stclt/10;
			gotoXY(67 + vitri, y);
			cout << " ";
			gotoXY(67 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{

			vitri = demchu(mh.stcth);
			gotoXY(75 + vitri, y);
			goto STCTH;
		}
		if (key == LEFT)
		{

			vitri = strlen(mh.tmh);
			gotoXY(30 + vitri, y);
			goto TENMH;
		}
		if (key == RIGHT)
		{

			vitri = demchu(mh.stcth);
			gotoXY(75 + vitri, y);
			goto STCTH;
		}
		if (key == ESC || key == F1) { return; }
	}
STCTH:
	while (1)
	{
		TextColor(244);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 3         ";
		TextColor(14); gotoXY(75 + vitri, y); // Ghi ch˙
		key = GetKey();
		if (mh.stclt == 0)
		{
			GhiChu("Ban Chua Nhap STCLT Mon Hoc!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(67 + vitri, y);
			goto STCLT;
		}
		if ((key <= '9' && key >= '0') && (vitri < 1))
		{
			mh.stcth = key-48;

			cout << mh.stcth;
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			mh.stcth = mh.stcth/10;
			gotoXY(75 + vitri, y);
			cout << " ";
			gotoXY(75 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			//sua trong danh sach mon hoc, phai sua luon trong DSLTC
			for (int i = 0; i < DSLTC.n; i++) {
				if (strcmp(DSLTC.nodeltc[i]->mmh, p->data.mmh) == 0) {
					strcpy(DSLTC.nodeltc[i]->mmh, mh.mmh);
				}
			}
			p->data = mh;
			GhiChu("Lop hoc da duoc cap nhat!", 35, 27, 79, 700);
			return;
		}
		if (key == LEFT)
		{

			vitri = demchu(mh.stclt);
			gotoXY(67 + vitri, y);
			goto STCLT;
		}
		if (key == ESC || key == F1) { return; }
	}
}
//phai lam them chuc nang sua doi trong danh sach lop tin chi // daxong

//--Xem danh sach-----------
int DemMonHoc(PTRMH DSMH) {
	if (DSMH != NULL)
	{
		return (DemMonHoc(DSMH->left) + DemMonHoc(DSMH->right) + 1);
	}
	else return 0;
}
//load tam tat ca mon hoc vao de xu li //
void MangTam_MonHoc(PTRMH DSMH, NodeMH mh[], int &dem) {
	//phep duyet LNR
	if (DSMH != NULL)
	{
		MangTam_MonHoc(DSMH->left, mh, dem);
		mh[dem++] = DSMH->data;
		MangTam_MonHoc(DSMH->right, mh, dem);
	}
}
void Sort_MangMH(NodeMH a[], int n) { //MH khong qua nhieu. Dung Selection Sort la Ok r
	NodeMH min;
	int vitrimin;
	int i, j;
	for (i = 0; i < n - 1; i++) {
		min = a[i];
		vitrimin = i;
		for (j = i + 1; j < n; j++) {
			if (strcmp(min.tmh, a[j].tmh) >0)
			{
				min = a[j];// chuoi ten mon hoc co gia tri nho nhat
				vitrimin = j;
			}
		}
		min = a[vitrimin];
		a[vitrimin] = a[i];
		a[i] = min;
	}
}


//--xem danh sach mon
void XemMonHoc(Dslop &DSLTC, PTRMH &DSMH, int chedoxem) { // 1 xem,  != 1 xuli
	int key;
	int STT = 1, trang = 0, tongtrang = 0;
	int soluongmh, dem = 0, demdong = 0;
	bool check_change = false;
	while (1)
	{
		soluongmh = DemMonHoc(DSMH);
		if (soluongmh == 0)
		{
			GhiChu("Chua co du lieu Mon Hoc", 35, 27, 79, 500);
		}
		else {
			if (soluongmh < 15)
			{
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((soluongmh - 1) / 15 + 1);
			}
		}
		NodeMH *MH = new NodeMH[soluongmh + 1];
		MangTam_MonHoc(DSMH, MH, dem); //Do Cay Nhi Phan ra Mang?
		Sort_MangMH(MH, dem);
		dem = 0; demdong = 0;
		TextColor(14);	system("cls");
		Khung_Xuat_MH();
		for (int i = trang * 15; i < 15 + trang * 15 && i < soluongmh; i++)
		{
			TextColor(12); gotoXY(6, 8 + demdong); cout << (i + 1);
			TextColor(14);
			gotoXY(10, 8 + demdong); cout << MH[i].mmh;
			gotoXY(31, 8 + demdong); cout << MH[i].tmh;
			gotoXY(72, 8 + demdong); cout << MH[i].stclt;
			gotoXY(80, 8 + demdong); cout << MH[i].stcth;
			demdong++;
		}
		HienThiTrang(trang + 1, tongtrang, 73, 26);
		if (chedoxem == 1)//Dang o che do xem
		{
			TextColor(236); gotoXY(18, 24); cout << "                        DANG O CHE DO XEM!                      ";
			TextColor(236); gotoXY(33, 2); cout << " NHAN ESC DE THOAT CHE DO XEM";
		}	gotoXY(81, 26);
		key = GetKey();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == F1 && chedoxem != 1)
		{
			gotoXY(18, 24);  TextColor(251);	cout << "F1";	//TÙ m‡u F1
			ThemMonHoc(DSMH, check_change);
		}
		if (key == F2 && chedoxem != 1)
		{
			gotoXY(35, 24);  TextColor(251);	cout << "F2";	//TÙ m‡u F2
			SuaMonHoc(DSLTC, DSMH, check_change);
		}
		if (key == F3 && chedoxem != 1)
		{
			gotoXY(50, 24);  TextColor(251);	cout << "F3";	//TÙ m‡u F3
			XoaMonHoc(DSLTC, DSMH, check_change);
		}
		if (key == ESC)
		{
			if (chedoxem == 1) { delete(MH); return; };
			if (check_change == true)
			{
				putchar(7);	gotoXY(4, 24);  TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC();
				if (temp == -1) { continue; }
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileMH(DSMH);  GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");	delete(MH); return;
		}
		if (key == F5 && chedoxem == 1) { delete(MH); return; }
	}
}


//---------------------ham de xu li lop va dssv----------------
int DemSinhVien(PTRSV DSSV)
{
	int dem = 0;
	for (PTRSV p = DSSV; p != NULL; p = p->next) { dem++; }
	return dem;
}

int kt_Lop_MSV_MH(PTRSV ds, PTRMH DSMH, char c[], int n)
{
	for (PTRSV p = ds; p->next != NULL; p=p->next)						// tra ve -1 : trung Ma lop
	{													// tra ve -2 : trung Ma SV
                                     					// tra ve -3 : trung Ma MH
		if (strcmp(p->data.malop, c) == 0) return -1;	// tra ve 0 : khong trung
		if (strcmp(p->data.mssv, c) == 0)return -2;
		
	}
	if (KTMH(DSMH, c) == 1) return -3;
	return 0;
}
int KTSV(PTRSV DSSV, char c[])
{
	for (PTRSV p = DSSV; p != NULL; p = p->next)
	{
		if ((strcmp(p->data.mssv, c)) == 0 && p == DSSV)
		{
			return 1;
		}
		if ((strcmp(p->data.mssv, c) == 0) && (p->next == NULL)) //Luu y: phai so sanh Tail truoc' giua neu khong roi vao truong hop giua~ truoc
		{
			return -1;
		}
		if (strcmp(p->data.mssv, c) == 0)
		{
			return 0;
		}
	}	return 2;
}
void SapXepSV(PTRSV &DSSV)
{
	PTRSV tam, p, q;
	NodeSV sv;	//Sap xep theo Selection Sort, tai vi 1 lop khoang 100sv
	if (DSSV == NULL) { return; }
	for (p = DSSV; p->next != NULL; p = p->next) //p nhu mang di tu i = 0 den n-1
	{
		tam = p; sv = p->data; //dia chi nho nhat gan vao tam, gia tri nho nhat gan vao sv
		for (q = p->next; q != NULL; q = q->next) //q nhu mang di tu i+1 den n
		{
			if (strcmp(tam->data.ten, q->data.ten)>0) //So sanh Ten truoc'
			{
				tam = q;
			}
			else {
				if (strcmp(tam->data.ten, q->data.ten) == 0) //Neu Ten bang nhau so sanh tiep Ho
				{
					if (strcmp(tam->data.ho, q->data.ho)>0)
					{
						tam = q;
					}
				}
			}
		}
		//sv = p->data;
		p->data = tam->data;
		tam->data = sv;
	}
}


//--------------------------DANH SACH LOP-------------------------------------------------------------------------------------------------------

//int Full_Lop(ListLop &ds) {
//	if (ds.n == MAXLOP - 1) {
//		GhiChu("Danh sach Lop Da Day. Khong the them!", 35, 27, 79, 700);
//		return 1;
//	}
//	return 0;
//}
//void InitLop(ListLop &ds) {
//	ds.n = 0;
//}
//--nhap hang loat
/*void NhapLop(ListLop &ds, PTRMH DSMH)
{
	int key;
	int vitri = 0, x = 10, y = 8;
	int dem = ds.n;
	int STT = 1;
	int check_trung;
	bool check_change = false;
	ds.dsl[ds.n].malop[0] = NULL; 	ds.dsl[ds.n].tenlop[0] = NULL;		ds.dsl[ds.n].nienkhoa[0] = NULL;	//Khoi tao rong~
	Khung_Nhap_Lop();
	TextColor(12);		gotoXY(6, 8); 	 cout << STT;
	TextColor(14); //In STT dau tien
	gotoXY(10, 8);
MALOP:
	while (1)
	{
		TextColor(252);				//Chu thich
		gotoXY(20, 29); cout << "                                                        ";
		gotoXY(20, 30); cout << " MA LOP: GOM CAC KI TU (A-Z) & (0-9), TOI DA: 15 KI TU  ";
		gotoXY(20, 31); cout << "                                                        ";
		TextColor(14);
		gotoXY(10 + vitri, y);
		key = GetKey();				//Bat phim
		if (ds.dsl[ds.n - 1].nienkhoa[0] == '\0' && y > 8) //Kiem tra Ù truoc co du lieu chua
		{
			GhiChu("Ban Chua Nhap Nien Khoa!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(72, --y);
			ds.n--;
			goto NIENKHOA;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			//if (Full_Lop(ds)) { continue; }	//KT day o nho mang xem danh sach do day chua
			ds.dsl[ds.n].malop[vitri] = char(key);
			ds.dsl[ds.n].malop[vitri] = toupper(ds.dsl[ds.n].malop[vitri]);	//Chuyen thanh kieu chu Hoa
			cout << ds.dsl[ds.n].malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			//if (Full_Lop(ds)) { continue; }
			ds.dsl[ds.n].malop[vitri] = '\0';		  //Ngat chuÙi~
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(31 + vitri, y);
			goto TENLOP;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(10 + vitri, y);
			cout << " ";
			gotoXY(10 + vitri, y);
		}
		if (key == RIGHT)
		{
			//if (Full_Lop(ds)) { continue; }
			ds.dsl[ds.n].malop[vitri] = '\0';		  //Ngat chuÙi~
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(31 + vitri, y);
			goto TENLOP;
		}
		if (key == DOWN && y < 22 && ds.dsl[ds.n + 1].malop[0] != '\0')
		{
			//if (Full_Lop(ds)) { continue; }
			ds.dsl[ds.n].malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			ds.n++;
			vitri = strlen(ds.dsl[ds.n].malop);
			gotoXY(10 + vitri, ++y);
		}
		if (key == UP &&	y > 8)
		{
			//if (Full_Lop(ds)) { continue; }
			ds.dsl[ds.n].malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			ds.n--;
			vitri = strlen(ds.dsl[ds.n].malop);
			gotoXY(10 + vitri, --y);
		}
		if (key == ESC)
		{
			if (check_change == true) //Bo nho da thay doi
			{
				ds.dsl[ds.n].malop[vitri] = '\0';
				putchar(7);
				gotoXY(4, 24);	TextColor(251);	cout << "ESC"; //To mau` button ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua// ESC hai lan
				{
					gotoXY(4, 24); TextColor(252);	cout << "ESC";
					TextColor(14);
					continue;
				}
				ds.n = dem;		//Khi thoat cap nhat bien dem cao nhat cho ds.n// La tong so lop da nhap vao
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileLop(ds); GhiFileSV(ds);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");	return;
		}
	}
TENLOP:
	while (1)
	{
		TextColor(252);				//Chu thich
		gotoXY(20, 29); cout << "                                                        ";
		gotoXY(20, 30); cout << " TEN LOP: GOM CAC KI TU (A-Z) & (0-9), TOI DA: 30 KI TU ";
		gotoXY(20, 31); cout << "                                                        ";
		TextColor(14);
		gotoXY(31 + vitri, y);
		key = GetKey();
		if (ds.dsl[ds.n].malop[0] == '\0')		//Kiem tra Ù phÌa truoc cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ma Lop!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(10, y);
			goto MALOP;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 30))
		{
			ds.dsl[ds.n].tenlop[vitri] = char(key);
			ds.dsl[ds.n].tenlop[vitri] = toupper(ds.dsl[ds.n].tenlop[vitri]);
			cout << ds.dsl[ds.n].tenlop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			if (ds.dsl[ds.n].tenlop[vitri - 1] == ' ') { vitri--; }	//Chuan hoa chuoi
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].tenlop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(72 + vitri, y);
			goto NIENKHOA;
		}
		if (key == SPACE && ds.dsl[ds.n].tenlop[vitri - 1] != ' ' && vitri > 0 && vitri < 30)
		{
			gotoXY(31 + vitri, y);
			cout << " ";
			ds.dsl[ds.n].tenlop[vitri] = ' ';
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(31 + vitri, y);
			cout << " ";
			gotoXY(31 + vitri, y);
		}
		if (key == RIGHT)
		{
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].tenlop, dem);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(31 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(72 + vitri, y);
			goto NIENKHOA;
		}
		if (key == LEFT)
		{
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			vitri = strlen(ds.dsl[ds.n].malop);
			gotoXY(10 + vitri, y);
			goto MALOP;
		}
		if (key == UP && y > 8)
		{
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			ds.n--;
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(31 + vitri, --y);
		}
		if (key == DOWN && y < 22 && ds.dsl[1 + ds.n].tenlop[0] != '\0')
		{
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			ds.n++;
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(31 + vitri, ++y);
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				ds.dsl[ds.n].tenlop[vitri] = '\0';
				putchar(7); gotoXY(4, 24);	TextColor(251);	cout << "ESC"; //To mau button ESC va tiep tuc
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);	TextColor(252);	cout << "ESC"; TextColor(14); //To mau button ESC
					gotoXY(31 + vitri, y);
					continue;
				}
				ds.n = dem;		//Khi thoat cap nhat bien dem cao nhat cho ds.n
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileLop(ds); GhiFileSV(ds);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");	return;
		}
	}
NIENKHOA:
	while (1)
	{
		TextColor(252);				//Chu thich
		gotoXY(20, 29); cout << "                                                        ";
		gotoXY(20, 30); cout << "    NIEN KHOA: GOM CAC KI TU (0-9), TOI DA: 4 KI TU     ";
		gotoXY(20, 31); cout << "                                                        ";
		TextColor(14);
		gotoXY(72 + vitri, y);
		key = GetKey();
		if (ds.dsl[ds.n].tenlop[0] == '\0')	//Kiem tra Ù truoc' co du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ten Lop!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(31, y);
			goto TENLOP;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			ds.dsl[ds.n].nienkhoa[vitri] = char(key);
			ds.dsl[ds.n].nienkhoa[vitri] = toupper(ds.dsl[ds.n].nienkhoa[vitri]);
			cout << ds.dsl[ds.n].nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			GhiChu("Save Thanh Cong!", 40, 27, 79, 500);	TextColor(92);
			gotoXY(6, y + 1);
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			if (ds.dsl[ds.n + 1].malop[0] == '\0' && dem == ds.n)	//Khong cho bien dem tang len khi sua loi~ cac NK phia' trÍn
			{
				TextColor(12);
				cout << ++STT;	//Cho xuat hien STT
				dem++; 			//dem la so lop hien hanh` dang nhap vao ds.n = dem tai ESC
			}
			if ((STT - 1) % 15 == 0) //Khi svien day` khung. Reset lai khung
			{
				y = 7;
				system("cls");
				Khung_Nhap_Lop();
				TextColor(12); 	gotoXY(6, 8); cout << STT;
			}
			TextColor(14);
			ds.n++;
			vitri = strlen(ds.dsl[ds.n].malop);
			gotoXY(10 + vitri, ++y);
			goto MALOP;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(72 + vitri, y);
			cout << " ";
			gotoXY(72 + vitri, y);
		}
		if (key == LEFT)
		{
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(31 + vitri, y);
			goto TENLOP;
		}
		if (key == UP && y > 8)
		{
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			ds.n--;
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(72 + vitri, --y);
		}
		if (key == DOWN && y < 22 && ds.dsl[ds.n + 1].nienkhoa[0] != '\0')
		{
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			ds.n++;
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(72 + vitri, ++y);
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				ds.dsl[ds.n].nienkhoa[vitri] = '\0';
				putchar(7);
				gotoXY(4, 24);	TextColor(251);	cout << "ESC"; //To mau button ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);	TextColor(252);	cout << "ESC"; TextColor(14); continue;//To mau button ESC va tiep tuc
				}
				ds.n = dem;		//Khi thoat cap nhat bien dem cao nhat cho ds.n
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileLop(ds); GhiFileSV(ds);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");	return;
		}
	}
}*/
/*void ThemLop(ListLop &ds, PTRMH DSMH, bool &check_change)
{
	ds.dsl[ds.n].malop[0] = NULL; 	ds.dsl[ds.n].tenlop[0] = NULL;		ds.dsl[ds.n].nienkhoa[0] = NULL;	//Khoi tao rong~
	int key;
	int check_trung;
	int vitri = 0, x = 12, y = 14;
	Khung_Them_Lop();	gotoXY(x, y);
MALOP:
	while (1)
	{
		TextColor(228);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 10";	//Ghi chu
		TextColor(14);	gotoXY(12 + vitri, y);
		key = GetKey();	//Bat phim'
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) || (key == '-') && (vitri < 11))
		{
			ds.dsl[ds.n].malop[vitri] = char(key);
			ds.dsl[ds.n].malop[vitri] = toupper(ds.dsl[ds.n].malop[vitri]);
			cout << ds.dsl[ds.n].malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			ds.dsl[ds.n].malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, ds.n);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == RIGHT)
		{
			ds.dsl[ds.n].malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].malop, ds.n);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == ESC || key == F1) { return; }
	}
TENLOP:
	while (1)
	{
		TextColor(228);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 30";	//Ghi chu
		TextColor(14);	gotoXY(30 + vitri, y);
		key = GetKey(); //Bat phim
		if (ds.dsl[ds.n].malop[0] == '\0')		//Kiem tra Ù phÌa truoc cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ma Lop!", 35, 27, 79, 700);
			gotoXY(12, y);
			goto MALOP;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 30))
		{
			ds.dsl[ds.n].tenlop[vitri] = char(key);
			ds.dsl[ds.n].tenlop[vitri] = toupper(ds.dsl[ds.n].tenlop[vitri]);
			cout << ds.dsl[ds.n].tenlop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			if (ds.dsl[ds.n].tenlop[vitri - 1] == ' ') { vitri--; }  //KT khi enter truoc do co phai khoang trang-> chuan hoa
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].tenlop, ds.n);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(62 + vitri, y);
			goto NIENKHOA;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(30 + vitri, y);
			cout << " ";
			gotoXY(30 + vitri, y);
		}
		if (key == SPACE && ds.dsl[ds.n].tenlop[vitri - 1] != ' ' && ds.dsl[ds.n].tenlop[0] != '\0' && vitri > 0 && vitri < 30) // khong cho 2 dau cach
		{
			gotoXY(30 + vitri, y);
			cout << " ";
			ds.dsl[ds.n].tenlop[vitri] = ' ';
			vitri++;
		}
		if (key == LEFT)
		{
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			vitri = strlen(ds.dsl[ds.n].malop);
			gotoXY(12 + vitri, y);
			goto MALOP;
		}
		if (key == RIGHT)
		{
			if (ds.dsl[ds.n].tenlop[vitri - 1] == ' ') { vitri--; }  //KT khi enter truoc do co phai khoang trang-> chuan hoa
			ds.dsl[ds.n].tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, ds.dsl[ds.n].tenlop, ds.n);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			vitri = strlen(ds.dsl[ds.n].nienkhoa);
			gotoXY(62 + vitri, y);
			goto NIENKHOA;
		}
		if (key == ESC || key == F1) { return; }
	}
NIENKHOA:
	while (1)
	{
		TextColor(228);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 4         "; //Ghi ch˙
		TextColor(14); gotoXY(62 + vitri, y);
		key = GetKey(); //Bat phim
		if (ds.dsl[ds.n].tenlop[0] == '\0')		//Kiem tra Ù phÌa truoc cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ten Lop!", 35, 27, 79, 700);
			gotoXY(30, y);
			goto TENLOP;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			ds.dsl[ds.n].nienkhoa[vitri] = char(key);
			ds.dsl[ds.n].nienkhoa[vitri] = toupper(ds.dsl[ds.n].nienkhoa[vitri]);
			cout << ds.dsl[ds.n].nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			GhiChu("Da luu vao bo nho", 35, 27, 79, 1000);
			ds.n++;
			return;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(62 + vitri, y);
			cout << " ";
			gotoXY(62 + vitri, y);
		}
		if (key == LEFT)
		{
			ds.dsl[ds.n].nienkhoa[vitri] = '\0';
			vitri = strlen(ds.dsl[ds.n].tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == ESC || key == F1) { return; }
	}
}
void SuaLop(ListLop &ds, PTRMH DSMH, bool &check_change)
{
	int key;
	int check_trung;
	int x = 33, y = 14, vitri = 0, vitriMang, temp;
	Nodelop lop;
	Khung_Sua_Lop();	gotoXY(x, y);
	while (1)
	{
		TextColor(14);
		key = GetKey(); //Bat phim
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			lop.malop[vitri] = char(key);
			lop.malop[vitri] = toupper(lop.malop[vitri]);
			cout << lop.malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lop.malop[vitri] = '\0';
			temp = KTMaLop(ds, lop.malop, ds.n);
			if (temp != -1)
			{
				vitriMang = temp; //luu vi tri cua lop tim ra
				Khung_Them_Lop();
				strcpy(lop.malop, ds.dsl[vitriMang].malop);
				strcpy(lop.tenlop, ds.dsl[vitriMang].tenlop);
				strcpy(lop.nienkhoa, ds.dsl[vitriMang].nienkhoa);
				TextColor(12);
				gotoXY(12, y); cout << lop.malop;
				gotoXY(30, y); cout << lop.tenlop;
				gotoXY(62, y); cout << lop.nienkhoa;
				vitri = strlen(lop.malop);
				gotoXY(12 + vitri, y);
				TextColor(14);
				goto MALOP;
			}
			else {
				GhiChu("Khong co Ma Lop trong Danh Sach!", 25, 27, 79, 500);
				gotoXY(33 + vitri, y);	TextColor(12);	continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ESC || key == F2) { return; }
	}
MALOP:
	while (1)
	{
		TextColor(224);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 15";
		TextColor(14); gotoXY(12 + vitri, y); //Ghi ch˙
		key = GetKey(); //Bat phim
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			lop.malop[vitri] = char(key);
			lop.malop[vitri] = toupper(lop.malop[vitri]);
			cout << lop.malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lop.malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, lop.malop, ds.n);
			if (check_trung == -1 && strcmp(ds.dsl[vitriMang].malop, lop.malop) != 0) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			vitri = strlen(lop.tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == RIGHT)
		{
			lop.malop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, lop.malop, ds.n - 1);
			if (check_trung == -1 && strcmp(ds.dsl[vitriMang].malop, lop.malop) != 0) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(12 + vitri, y);
				continue;
			}
			vitri = strlen(lop.tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == ESC || key == F2) { return; }
	}
TENLOP:
	while (1)
	{
		TextColor(224);	gotoXY(10, 15);
		cout << "Ki tu: (A-Z) & (0-9). Toi da: 30";	 //Ghi ch˙
		TextColor(14);
		gotoXY(30 + vitri, y);
		key = GetKey();
		if (lop.malop[0] == '\0')		//Kiem tra Ù phÌa truoc cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ma Lop!", 35, 27, 79, 700);
			gotoXY(12, y);
			goto MALOP;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 30))
		{
			lop.tenlop[vitri] = char(key);
			lop.tenlop[vitri] = toupper(lop.tenlop[vitri]);
			cout << lop.tenlop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			while (lop.tenlop[vitri - 1] == ' ') { vitri--; } //KT khi enter truoc do co phai khoang trang
			lop.tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, lop.tenlop, ds.n);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			vitri = strlen(lop.nienkhoa);
			gotoXY(62 + vitri, y);
			goto NIENKHOA;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(30 + vitri, y);
			cout << " ";
			gotoXY(30 + vitri, y);
		}
		if (key == SPACE && lop.tenlop[vitri - 1] != ' ' && lop.tenlop[0] != '\0' && vitri > 0 && vitri < 30)
		{
			gotoXY(30 + vitri, y);
			cout << " ";
			lop.tenlop[vitri] = ' ';
			vitri++;
		}
		if (key == LEFT)
		{
			lop.tenlop[vitri] = '\0';
			vitri = strlen(lop.malop);
			gotoXY(12 + vitri, y);
			goto MALOP;
		}
		if (key == RIGHT)
		{
			while (lop.tenlop[vitri - 1] == ' ') { vitri--; }
			lop.tenlop[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, lop.tenlop, ds.n - 1);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(30 + vitri, y);
				continue;
			}
			vitri = strlen(lop.nienkhoa);
			gotoXY(62 + vitri, y);
			goto NIENKHOA;
		}
		if (key == ESC || key == F2) { return; }
	}
NIENKHOA:
	while (1)
	{
		TextColor(228);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 4         ";
		TextColor(14); gotoXY(62 + vitri, y);//Ghi ch˙
		key = GetKey();
		if (lop.tenlop[0] == '\0')		//Kiem tra Ù phÌa truoc cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap Ten Lop!", 35, 27, 79, 700);
			gotoXY(30, y);
			goto TENLOP;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			lop.nienkhoa[vitri] = char(key);
			lop.nienkhoa[vitri] = toupper(lop.nienkhoa[vitri]);
			cout << lop.nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			lop.nienkhoa[vitri] = '\0';
			strcpy(ds.dsl[vitriMang].malop, lop.malop);
			strcpy(ds.dsl[vitriMang].tenlop, lop.tenlop);
			strcpy(ds.dsl[vitriMang].nienkhoa, lop.nienkhoa);
			return;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(62 + vitri, y);
			cout << " ";
			gotoXY(62 + vitri, y);
		}
		if (key == LEFT)
		{
			lop.nienkhoa[vitri] = '\0';
			vitri = strlen(lop.tenlop);
			gotoXY(30 + vitri, y);
			goto TENLOP;
		}
		if (key == ESC || key == F2) { return; }
	}
}
void XoaLop(ListLop &ds, bool &check_change)
{
	int key, x = 33, y = 14, vitri = 0;
	int vitriMang, temp;
	ds.dsl[ds.n].malop[0] = NULL;//Khoi tao MaLop rong~
	Khung_Xoa_Lop();	gotoXY(x, y);
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			ds.dsl[ds.n].malop[vitri] = char(key);
			ds.dsl[ds.n].malop[vitri] = toupper(ds.dsl[ds.n].malop[vitri]);
			cout << ds.dsl[ds.n].malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			ds.dsl[ds.n].malop[vitri] = '\0';
			temp = KTMaLop(ds, ds.dsl[ds.n].malop, ds.n);
			if (temp != -1)
			{
				vitriMang = temp;
				if (ds.dsl[vitriMang].DSSV != NULL)
				{
					GhiChu("Lop nay da co Sinh Vien khong the Xoa!", 25, 27, 79, 500);
					gotoXY(33 + vitri, y);
					TextColor(12);
					continue;
				}
				check_change = true;
				for (int i = vitriMang; i < ds.n; i++) {
					ds.dsl[i] = ds.dsl[i + 1];
				}//don khuc sau len
				GhiChu("Da Xoa Thanh Cong", 25, 27, 79, 500);
				ds.n--;
				return;
			}
			else {
				GhiChu("Khong co Ma Lop trong Danh Sach!", 25, 27, 79, 500);
				gotoXY(35 + vitri, y);	TextColor(12);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ESC || key == F3) { return; }
	}
}*/


//Insertion Sort // cai nay tinh sau
void ISortMaLop(NodeSV* ds, int n) {
	int i, hole;
	NodeSV value;
	for (i = 1; i<n; i++) {
		value = ds[i];
		hole = i;
		while (hole > 0 && strcmp(ds[hole - 1].malop, value.malop) > 0) {
			ds[hole] = ds[hole - 1];
			hole--;
		}
		ds[hole] = value;
	}
}
void XemLop(Dslop &DSLTC, PTRSV &ds, PTRMH DSMH, int chedoxem)	// chedoxem == 1 thi chi de xem
{
	int key;
	int dem = 0;
	int trang = 0, tongtrang = 0;
	bool check_change = false;
		int n = DemSinhVien(ds);
	NodeSV k[n+1];
	NodeSV l[n+1];
	int px = 0, j = 1;

	for(PTRSV p = ds; p != NULL; p = p->next){
		k[px] = p->data;
		px++;//cho data vao mang
	}
	ISortMaLop(k, n);
	l[0] = k[0];
	for(int x = 1; x < n; x++){
		if(strcmp(k[x-1].malop, k[x].malop) != 0){
			l[j] = k[x];
			j++;
		}
	}
	while (1)
	{
		if (j == 0)
		{
			GhiChu("Chua co Danh Sach Lop", 35, 27, 79, 1000);
		}
		else {
			if (j < 5)
			{
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((j - 1) / 5 + 1);
			}
		}
		TextColor(14);
		system("cls");
		Khung_Xuat_Lop();
		dem = 0;
		for (int i = trang * 5; i < 5 + trang * 5 && i < j; i++)
		{
			
			TextColor(14);
			gotoXY(10, 8 + dem + 2); cout << l[i].malop;
			//gotoXY(31, 8 + dem); cout << l[i].tenlop;
			//gotoXY(72, 8 + dem); cout << l[i].nienkhoa;
			dem++;
		}
		HienThiTrang(trang + 1, tongtrang, 73, 26);
		if (chedoxem == 1)//Dang o che do xem
		{
			TextColor(228); gotoXY(18, 24); cout << "               DANG O CHE DO XEM!            ";
			TextColor(228); gotoXY(33, 2); cout << " NHAN ESC DE THOAT CHE DO XEM";
		}
		gotoXY(81, 26);
		key = GetKey(); //Bat Phim
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
/*		if (key == F1 && chedoxem != 1)
		{
			//if (Full_Lop(ds)) { continue; }
			gotoXY(18, 24);  TextColor(251);	cout << "F1"; //To mau` F1
			ThemLop(ds, DSMH, check_change);
		}
		if (key == F2 && chedoxem != 1)
		{
			gotoXY(36, 24);	TextColor(251);	cout << "F2"; //To mau` F2
			SuaLop(ds, DSMH, check_change);
		}
		if (key == F3 && chedoxem != 1)
		{
			gotoXY(50, 24);	TextColor(251);	cout << "F3"; //To mau` F3 
			XoaLop(ds, check_change);
		}*/
		if (key == ESC)
		{
			if (chedoxem == 1) { return; };
			if (check_change == true)
			{
				putchar(7);	gotoXY(4, 24); TextColor(251); cout << "ESC"; //To mau` ESC
				int temp = ThongBao_ESC();
				if (temp == -1) { continue; }	//Tra ve -1 => Bat' duoc phim' ESC 1 l‚n` nua~
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					/*GhiFileLop(ds);  GhiFileSV(ds);*/ GhiFileDK(DSLTC);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");
			return;
		}
		if (key == F5 && chedoxem == 1) { return; }
	}
}

//-----------------------DANH SACH SINH VIEN-------------------------------------------------------------------------------------------------------------------------

PTRSV Search_MSV(PTRSV DSSV, char msv[]) {
	if (NULL == DSSV) {
		return NULL;
	}
	for (PTRSV p = DSSV; p != NULL; p = p->next) {
		if (strcmp(p->data.mssv, msv) == 0) {
			return p;
		}
	}return NULL;
}
PTRDK SearchSV_LTC(Dslop &DSLTC, char c[])
{
	for (int i = 0; i < DSLTC.n; i++) //Duyet Lop
	{
		if (DSLTC.nodeltc[i]->DSDK == NULL) { continue; } //Lop khong co sinh vien => continue
		for (PTRDK p = DSLTC.nodeltc[i]->DSDK; p != NULL; p = p->next)
		{
			if (strcmp(p->data.mssv, c) == 0) { return p; } //Tim thay sinh vien => tra ve n˙t svien 
		}
	}return NULL;
}
PTRSV Search_MSV_DSLOP(PTRSV ds, char msv[]) {
	
		for (PTRSV p =ds; p != NULL; p = p->next) {
			if (strcmp(p->data.mssv, msv) == 0) {
				return p;
			}
		}
	return NULL;
}
int Full_SV(PTRSV &DSSV, int dem)	//tra ve 1: day sinh vien cua lop
{
	int soluongsv = DemSinhVien(DSSV);
	if (dem == MAXSV - soluongsv - 1) {
		GhiChu("Danh sach Sinh Vien Full. Khong the them!", 35, 27, 79, 700);
		return 1;
	} return 0;
}
//Nhap hang loat sinh vien-------------------------
void NhapSinhVien(Dslop DSLTC, PTRSV &ds, PTRMH DSMH)
{
	int key;
	int check_trung;
	int x = 40, y = 2, vitri = 0, vitriMang, temp;
	int STT = 1;
	bool check_change = false;
NHAPLOP:
	Khung_Nhap_MaLop();
	char malop[12];
	gotoXY(x, y); //Khoi tao rong~
				  //cai nay de tim ma lop
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			temp = KTMaLop(ds, malop, 1); //Kiem tra tr˘ng ma lop
			if (temp != -1)
			{
				TextColor(14);	system("cls");	break;
			}
			else {
				GhiChu("     Ma Lop Khong Ton Tai! F1 De Them Lop    ", 33, 5, 79, 2000);
				if(key = F1){
					GhiChu("     Them Lop Thanh Cong    ", 33, 5, 79, 500);
					system("cls");	break;
				}
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(40 + vitri, y);
			cout << " ";
			gotoXY(40 + vitri, y);
		}
		if (key == F5)
		{
			malop[vitri] = '\0';
			XemLop(DSLTC, ds, DSMH, 1);
			Khung_Nhap_MaLop();
			TextColor(228);
			gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
			TextColor(14);	gotoXY(40, y); cout << malop;	//In lai nhung gi da nhap
		}
		if (key == ESC) { TextColor(14);	return; }
	}
	//neu o tren ok thi bd nhap
	x = 10, y = 8, vitri = 0;
	//int soluongsv = DemSinhVien(ds.dsl[vitriMang].DSSV);
	int dem = 0; //dem vi tri dong cua con tro hien tai
	int demkhongdoi = 0; // dem tong so sinh vien dang nhap vao
	NodeSV demsv[MAXSV];
	for (int i = 0; i < MAXSV; i++) // Khoi tao mang tam rong~
	{
		demsv[i].mssv[0] = NULL;
		demsv[i].ho[0] = NULL;
		demsv[i].ten[0] = NULL;
		demsv[i].phai[0] = NULL;
		demsv[i].sdt[0] = NULL;
		strcpy(demsv[i].malop, malop);
	}
	Khung_Nhap_SV();
	TextColor(12);		gotoXY(6, 8); 	 cout << STT;
	TextColor(14); //In STT dau tien
MASV:
	while (1)
	{
		TextColor(252);				//Chu thich
		gotoXY(20, 26); cout << "                                                              ";
		gotoXY(20, 27); cout << " MA SINH VIEN: GOM CAC KI TU (A-Z) & (0-9), TOI DA: 10 KI TU  ";
		gotoXY(20, 28); cout << "                                                              ";
		TextColor(14);
		gotoXY(10 + vitri, y);
		key = GetKey();
		if (demsv[dem - 1].sdt[0] == '\0' && y > 8)		//Kiem tra Ù phÌa truoc' cÛ du~ lieu chua
		{
			GhiChu("Ban Chua Nhap SDT!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(69, --y);
			dem--;
			goto SODT;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			
			demsv[dem].mssv[vitri] = char(key);
			demsv[dem].mssv[vitri] = toupper(demsv[dem].mssv[vitri]);
			cout << demsv[dem].mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(10 + vitri, y);
			cout << " ";
			gotoXY(10 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
		
			demsv[dem].mssv[vitri] = '\0';
			for (int i = 0; i <= demkhongdoi; i++)
			{
				if (i == dem) { continue; }	// khi user sua loi~ cac MASV o tren bo? qua duyet bÙ. dÍm. chÌnh nÛ
				if (strcmp(demsv[i].mssv, demsv[dem].mssv) == 0) //KT trung sinh vien o mang? tam.
				{
					GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
					goto MASV;
				}
			}
			check_trung = kt_Lop_MSV_MH(ds, DSMH, demsv[dem].mssv, 1);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			vitri = strlen(demsv[dem].ho);
			gotoXY(26 + vitri, y);
			goto HO;
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				demsv[dem].mssv[vitri] = '\0';
				putchar(7);
				gotoXY(4, 24);
				TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);
					TextColor(252);
					cout << "ESC"; //TÙ m‡u ESC
					TextColor(14);
					continue;
				}
				if (temp == 1) // 1 la YES 
				{
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}	//Do? mang? tam. vao DSLK (bo nho trong)
					GhiFileSV(ds);
				}
				if (temp == 0) // 0 la NO
				{
					GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}	//Do? mang? tam. vao DSLK (bo nho trong)
				}
			}
			system("cls");	return;
		}
		if (key == RIGHT)
		{
		
			demsv[dem].mssv[vitri] = '\0';
			for (int i = 0; i <= demkhongdoi; i++)
			{
				if (i == dem) { continue; }	// khi user sua loi~ cac MASV o tren bo? qua duyet bÙ. dÍm. chÌnh nÛ
				if (strcmp(demsv[i].mssv, demsv[dem].mssv) == 0) //KT trung sinh vien o mang? tam.
				{
					GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
					goto MASV;
				}
			}
			check_trung = kt_Lop_MSV_MH(ds, DSMH, demsv[dem].mssv, 1);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			vitri = strlen(demsv[dem].ho);
			gotoXY(26 + vitri, y);
			goto HO;
		}
		if (key == DOWN && y < 22 && demsv[dem + 1].mssv[0] != '\0')
		{
			demsv[dem].mssv[vitri] = '\0';
			for (int i = 0; i <= demkhongdoi; i++) {
				if (i == dem) { continue; }// khi user sua loi cac MASV o tren bo qua duyet bÙ. dÍm. chÌnh nÛ
				if (strcmp(demsv[i].mssv, demsv[dem].mssv) == 0) //KT trung sinh vien o mang? tam.
				{
					GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
					goto MASV;
				}
			}
			check_trung = kt_Lop_MSV_MH(ds, DSMH, demsv[dem].mssv, 1);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			dem++;
			vitri = strlen(demsv[dem].mssv);
			gotoXY(10 + vitri, ++y);
		}
		if (key == UP &&	y > 8)
		{
		
			demsv[dem].mssv[vitri] = '\0';
			for (int i = 0; i <= demkhongdoi; i++) {
				if (i == dem) { continue; }	// khi user sua loi cac MASV o tren bo qua duyet bÙ. dÍm. chÌnh nÛ
				if (strcmp(demsv[i].mssv, demsv[dem].mssv) == 0) //KT trung sinh vien o mang? tam.
				{
					GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
					goto MASV;
				}
			}
			//check
			check_trung = kt_Lop_MSV_MH(ds, DSMH, demsv[dem].mssv, 1);
			if (check_trung == -1) {
				GhiChu("Trung Ma Lop Tin Chi. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -2) {
				GhiChu("Trung Ma Sinh Vien. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			if (check_trung == -3) {
				GhiChu("Trung Mon Hoc. Vui Long Nhap Lai!", 35, 27, 79, 500);
				gotoXY(10 + vitri, y);
				continue;
			}
			dem--;
			vitri = strlen(demsv[dem].mssv);
			gotoXY(10 + vitri, --y);
		}
	}
HO:
	while (1)
	{
		TextColor(252);			//Chu thich
		gotoXY(20, 26); cout << "                                                              ";
		gotoXY(20, 27); cout << "      HO: GOM CAC KI TU (A-Z) & (0-9), TOI DA: 20 KI TU       ";
		gotoXY(20, 28); cout << "                                                              ";
		TextColor(14);
		gotoXY(26 + vitri, y);
		key = GetKey();
		if (demsv[dem].mssv[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ma Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(10, y);
			goto MASV;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 20))
		{
			demsv[dem].ho[vitri] = char(key);
			demsv[dem].ho[vitri] = toupper(demsv[dem].ho[vitri]);
			cout << demsv[dem].ho[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(26 + vitri, y);
			cout << " ";
			gotoXY(26 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			if (demsv[dem].ho[vitri - 1] == ' ') { vitri--; }//KT khi enter truoc do co phai khoang trang
			demsv[dem].ho[vitri] = '\0';
			vitri = strlen(demsv[dem].ten);
			gotoXY(47 + vitri, y);
			goto TEN;
		}
		if (key == SPACE && demsv[dem].ho[vitri - 1] != ' ' && vitri > 0 && vitri < 20)
		{
			gotoXY(26 + vitri, y);
			cout << " ";
			demsv[dem].ho[vitri] = ' ';
			vitri++;
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				demsv[dem].ho[vitri] = '\0';
				putchar(7);
				gotoXY(4, 24);
				TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);  TextColor(252);	cout << "ESC"; //TÙ m‡u ESC
					TextColor(14); continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang? tam. vao DSLK (bo nho trong)
					GhiFileSV(ds);//?
				}
				if (temp == 0)
				{
					GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do mang? tam. vao DSLK (bo nho trong)
				}
			}
			system("cls");	return;
		}
		if (key == LEFT)
		{
			demsv[dem].ho[vitri] = '\0';
			vitri = strlen(demsv[dem].mssv);
			gotoXY(10 + vitri, y);
			goto MASV;
		}
		if (key == RIGHT)
		{
			demsv[dem].ho[vitri] = '\0';
			vitri = strlen(demsv[dem].ten);
			gotoXY(47 + vitri, y);
			goto TEN;
		}
		if (key == UP && y > 8)
		{
			demsv[dem].ho[vitri] = '\0';
			dem--;
			vitri = strlen(demsv[dem].ho);
			gotoXY(26 + vitri, --y);
		}
		if (key == DOWN && y < 22 && demsv[1 + dem].ho[0] != '\0')
		{
			demsv[dem].ho[vitri] = '\0';
			dem++;
			vitri = strlen(demsv[dem].ho);
			gotoXY(26 + vitri, ++y);
		}
	}
TEN:
	while (1)
	{
		TextColor(252);			//Chu thich
		gotoXY(20, 26); cout << "                                                               ";
		gotoXY(20, 27); cout << "          TEN: GOM CAC KI TU (A-Z), TOI DA: 10 KI TU           ";
		gotoXY(20, 28); cout << "                                                               ";
		TextColor(14); gotoXY(47 + vitri, y);
		key = GetKey();
		if (demsv[dem].ho[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ho!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(26, y);
			goto HO;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			demsv[dem].ten[vitri] = char(key);
			demsv[dem].ten[vitri] = toupper(demsv[dem].ten[vitri]);
			cout << demsv[dem].ten[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(47 + vitri, y);
			cout << " ";
			gotoXY(47 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			demsv[dem].ten[vitri] = '\0';
			vitri = strlen(demsv[dem].phai);
			gotoXY(58 + vitri, y);
			goto PHAI;
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				demsv[dem].ten[vitri] = '\0';
				putchar(7);	gotoXY(4, 24);  TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);  TextColor(252);	cout << "ESC";
					TextColor(14); continue;//TÙ m‡u ESC
				}
				if (temp == 1)
				{
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do mang tam. vao DSLK (bo nho trong)
					GhiFileSV(ds); // luu file luon
				}
				if (temp == 0)
				{
					GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang tam. vao DSLK (bo nho trong)
				}
			}
			system("cls");	return;
		}
		if (key == LEFT)
		{
			demsv[dem].ten[vitri] = '\0';
			vitri = strlen(demsv[dem].ho);
			gotoXY(26 + vitri, y);
			goto HO;
		}
		if (key == RIGHT)
		{
			demsv[dem].ten[vitri] = '\0';
			vitri = strlen(demsv[dem].phai);
			gotoXY(58 + vitri, y);
			goto PHAI;
		}
		if (key == UP && y > 8)
		{
			demsv[dem].ten[vitri] = '\0';
			dem--;
			vitri = strlen(demsv[dem].ten);
			gotoXY(47 + vitri, --y);
		}
		if (key == DOWN && y < 22 && demsv[1 + dem].ten[0] != '\0')
		{
			demsv[dem].ten[vitri] = '\0';
			dem++;
			vitri = strlen(demsv[dem].ten);
			gotoXY(47 + vitri, ++y);
		}
	}
PHAI: // se sua lai; lam cai bang chon nam hay nu
	while (1)
	{
		TextColor(252);			//Chu thich
		gotoXY(20, 26); cout << "                                                                ";
		gotoXY(20, 27); cout << "      PHAI: GOM CAC KI TU (A-Z) - NAM/NU, TOI DA: 3 KI TU       ";
		gotoXY(20, 28); cout << "                                                                ";
		TextColor(14); gotoXY(58 + vitri, y);
		key = GetKey();
		if (demsv[dem].ten[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ten!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(47, y);
			goto TEN;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 3))
		{
			demsv[dem].phai[vitri] = char(key);
			demsv[dem].phai[vitri] = toupper(demsv[dem].phai[vitri]);
			cout << demsv[dem].phai[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(58 + vitri, y);
			cout << " ";
			gotoXY(58 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			demsv[dem].phai[vitri] = '\0';
			if ((strcmp(demsv[dem].phai, "NAM") == 0) || (strcmp(demsv[dem].phai, "NU") == 0)) // So sanh
			{
				vitri = strlen(demsv[dem].sdt);
				gotoXY(69 + vitri, y);
				goto SODT;
			}
			GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500); continue;
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				demsv[dem].phai[vitri] = '\0';
				putchar(7);	gotoXY(4, 24);
				TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);  TextColor(252);	cout << "ESC"; //TÙ m‡u ESC
					TextColor(14); continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang? tam. vao DSLK (bo nho trong)
					GhiFileSV(ds);
				}
				if (temp == 0)
				{
					GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000);
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang? tam. vao DSLK (bo nho trong)
				}
			}
			system("cls"); 	return;
		}
		if (key == LEFT)
		{
			demsv[dem].phai[vitri] = '\0';
			if ((strcmp(demsv[dem].phai, "NAM") != 0) && (strcmp(demsv[dem].phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500);
				continue;
			}
			vitri = strlen(demsv[dem].ten);
			gotoXY(47 + vitri, y);
			goto TEN;
		}
		if (key == RIGHT)
		{
			demsv[dem].phai[vitri] = '\0';
			if ((strcmp(demsv[dem].phai, "NAM") != 0) && (strcmp(demsv[dem].phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500);
				continue;
			}
			vitri = strlen(demsv[dem].sdt);
			gotoXY(69 + vitri, y);
			goto SODT;
		}
		if (key == UP && y > 8)
		{
			demsv[dem].phai[vitri] = '\0';
			if ((strcmp(demsv[dem].phai, "NAM") != 0) && (strcmp(demsv[dem].phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500);
				continue;
			}
			dem--;
			vitri = strlen(demsv[dem].phai);
			gotoXY(58 + vitri, --y);
		}
		if (key == DOWN && y < 22 && demsv[1 + dem].phai[0] != '\0')
		{
			demsv[dem].phai[vitri] = '\0';
			if ((strcmp(demsv[dem].phai, "NAM") != 0) && (strcmp(demsv[dem].phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500);
				continue;
			}
			dem++;
			vitri = strlen(demsv[dem].phai);
			gotoXY(58 + vitri, ++y);
		}
	}
SODT:
	while (1)
	{
		TextColor(252);
		gotoXY(20, 26); cout << "                                                                 ";
		gotoXY(20, 27); cout << "      SO DIEN THOAI: GOM CAC KI TU (0-9), TOI DA: 11 KI TU       ";
		gotoXY(20, 28); cout << "                                                                 ";
		TextColor(14); gotoXY(69 + vitri, y);
		key = GetKey();
		if (demsv[dem].phai[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Phai!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(58, y);
			goto PHAI;
		}
		if ((key <= '9' && key >= '0') && (vitri < 11))
		{
			demsv[dem].sdt[vitri] = char(key);
			demsv[dem].sdt[vitri] = toupper(demsv[dem].sdt[vitri]);
			cout << demsv[dem].sdt[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(69 + vitri, y);
			cout << " ";
			gotoXY(69 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			TextColor(14);
			demsv[dem].sdt[vitri] = '\0';
			GhiChu("Save Thanh Cong!", 40, 27, 79, 500);
			gotoXY(6, y + 1);
			if (demsv[dem + 1].mssv[0] == '\0' && dem == demkhongdoi) // khong cho bien demkhongdoi tang khi sua loi~ cac SDT o tren
			{
				TextColor(12);
				cout << ++STT; //Cho xuat hien STT
				demkhongdoi++;	// De cuoi cung ESC gan' cho dem
			}
			if ((STT - 1) % 15 == 0)
			{
				y = 7;
				system("cls");
				Khung_Nhap_SV();
				TextColor(12);	gotoXY(6, 8); cout << STT;
			}
			TextColor(14);
			dem++;	//dem nay co the thay doi khi di chuyen => can bien demkhongdoi
			vitri = strlen(demsv[dem].mssv);
			gotoXY(10 + vitri, ++y);
			goto MASV;
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				demsv[dem].sdt[vitri] = '\0';
				putchar(7);
				gotoXY(4, 24);  TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					gotoXY(4, 24);  TextColor(252);	cout << "ESC"; //TÙ m‡u ESC
					TextColor(14);	continue;
				}
				if (temp == 1)
				{
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang? tam. vao DSLK (bo nho trong)
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileSV(ds);
				}
				if (temp == 0)
				{
					for (int i = 0; i < demkhongdoi; i++) {
						Insert_TailSV(ds, demsv[i]);
					}//Do? mang? tam. vao DSLK (bo nho trong)
					GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000);
				}
			}
			system("cls");	return;
		}
		if (key == LEFT)
		{
			demsv[dem].sdt[vitri] = '\0';
			vitri = strlen(demsv[dem].phai);
			gotoXY(58 + vitri, y);
			goto PHAI;
		}
		if (key == UP && y > 8)
		{
			demsv[dem].sdt[vitri] = '\0';
			dem--;
			vitri = strlen(demsv[dem].sdt);
			gotoXY(69 + vitri, --y);
		}
		if (key == DOWN && y < 22 && demsv[dem + 1].sdt[0] != '\0')
		{
			demsv[dem].sdt[vitri] = '\0';
			dem++;
			vitri = strlen(demsv[dem].sdt);
			gotoXY(69 + vitri, ++y);
		}
	}
}

//Them sinh vien
void ThemSinhVien(PTRSV &ds, PTRMH DSMH, bool &check_change, char c[])
{
	int key;
	int check_trung;
	int vitri = 0, x = 12, y = 14, temp = 0;
	NodeSV sv;
	sv.mssv[0] = NULL; sv.ho[0] = NULL; sv.ten[0] = NULL; sv.phai[0] = NULL; sv.sdt[0] = NULL; 
	strcpy(sv.malop, c);
	Khung_Them_SV(); gotoXY(x, y);
MASV:
	while (1)
	{
		TextColor(236); gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 10";
		TextColor(14); gotoXY(12 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 15))
		{
			sv.mssv[vitri] = char(key);
			sv.mssv[vitri] = toupper(sv.mssv[vitri]);
			cout << sv.mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.mssv[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.mssv, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == RIGHT)
		{
			sv.mssv[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.mssv, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == ESC || key == F1) { return; }
	}
HO:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 20";
		TextColor(14); gotoXY(29 + vitri, y);
		key = GetKey();
		if (sv.mssv[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ma Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(12, y);
			goto MASV;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 20))
		{
			sv.ho[vitri] = char(key);
			sv.ho[vitri] = toupper(sv.ho[vitri]);
			cout << sv.ho[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(29 + vitri, y);
			cout << " ";
			gotoXY(29 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			if (sv.ho[vitri - 1] == ' ') { vitri--; }	//KT khi enter truoc do co phai khoang trang
			sv.ho[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ho, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == SPACE && sv.ho[vitri - 1] != ' ' && vitri > 0 && vitri < 20)
		{
			gotoXY(29 + vitri, y);
			cout << " ";
			sv.ho[vitri] = ' ';
			vitri++;
		}
		if (key == LEFT)
		{
			sv.ho[vitri] = '\0';
			vitri = strlen(sv.mssv);
			gotoXY(12 + vitri, y);
			goto MASV;
		}
		if (key == RIGHT)
		{
			if (sv.ho[vitri - 1] == ' ') { vitri--; }	//KT khi enter truoc do co phai khoang trang
			sv.ho[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ho, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == ESC || key == F1) { return; }
	}
TEN:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (A-Z). Toi da: 10        ";
		TextColor(124); gotoXY(51 + vitri, y);
		key = GetKey();
		if (sv.ho[0] == '\0')
		{
			GhiChu("Ban Chua Nhap HO Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(29, y);
			goto HO;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			sv.ten[vitri] = char(key);
			sv.ten[vitri] = toupper(sv.ten[vitri]);
			cout << sv.ten[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(51 + vitri, y);
			cout << " ";
			gotoXY(51 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.ten[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ten, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == LEFT)
		{
			sv.ten[vitri] = '\0';
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == RIGHT)
		{
			sv.ten[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ten, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == ESC || key == F1) { return; }
	}
PHAI:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Gioi tinh Nam / Nu. Toi da: 3         ";
		TextColor(14); gotoXY(63 + vitri, y);
		key = GetKey();
		if (sv.ten[0] == '\0')
		{
			GhiChu("Ban Chua Nhap TEN Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(51, y);
			goto TEN;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 3))
		{
			sv.phai[vitri] = char(key);
			sv.phai[vitri] = toupper(sv.phai[vitri]);
			cout << sv.phai[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(63 + vitri, y);
			cout << " ";
			gotoXY(63 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") == 0) || (strcmp(sv.phai, "NU") == 0)) // So sanh
			{
				vitri = strlen(sv.sdt);
				goto SODT;
			}
			GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500); continue;
		}
		if (key == LEFT)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") != 0) && (strcmp(sv.phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 74, 500); continue;
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == RIGHT)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") != 0) && (strcmp(sv.phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam / Nu!", 35, 27, 79, 500);
				continue;
			}
			vitri = strlen(sv.sdt);
			gotoXY(68 + vitri, y);
			goto SODT;
		}
		if (key == ESC || key == F1) { return; }
	}
SODT:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 11        ";
		TextColor(14);	gotoXY(68 + vitri, y);
		key = GetKey();
		if (sv.phai[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Gioi Tinh!", 35, 27, 79, 700);
			gotoXY(63, y);
			goto PHAI;
		}
		if ((key <= '9' && key >= '0') && (vitri < 11))
		{
			sv.sdt[vitri] = char(key);
			sv.sdt[vitri] = toupper(sv.sdt[vitri]);
			cout << sv.sdt[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(68 + vitri, y);
			cout << " ";
			gotoXY(68 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			sv.sdt[vitri] = '\0';
			Insert_TailSV(ds, sv);
			GhiChu("Them thanh cong", 35, 27, 79, 1000);
			return;
		}
		if (key == LEFT)
		{
			sv.sdt[vitri] = '\0';
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == ESC || key == F1) { return; }
	}
}
//Sua Sinh Vien
void SuaSinhVien(PTRSV &ds, PTRMH DSMH, Dslop &DSLTC, bool &check_change) {
	int key;
	int check_trung;
	PTRSV p; //vi tri cua sinh vien trong dssv, tra ve con tro
	int vitri = 0, x = 33, y = 14, temp = 0;
	NodeSV sv;
	sv.mssv[0] = NULL; sv.ho[0] = NULL; sv.ten[0] = NULL; sv.phai[0] = NULL; sv.sdt[0] = NULL;
	Khung_Sua_SV(); gotoXY(x, y);
	while (1)
	{
		TextColor(14);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 15))
		{
			sv.mssv[vitri] = char(key);
			sv.mssv[vitri] = toupper(sv.mssv[vitri]);
			cout << sv.mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.mssv[vitri] = '\0';	//Ngat chuoi~
			check_trung = KTSV(ds, sv.mssv);//KT trung sinh vien trong List
			if (check_trung != 2) // !=2 o day la 1. tra ve 1 tat nhien la co trong danh sach
			{
				vitri = 0;
				p = Search_MSV(ds, sv.mssv);
				x = 12; y = 14;
				Khung_Them_SV();
				strcpy(sv.mssv, p->data.mssv);
				strcpy(sv.ho, p->data.ho);
				strcpy(sv.ten, p->data.ten);
				strcpy(sv.phai, p->data.phai);
				strcpy(sv.sdt, p->data.sdt);
				TextColor(12);
				gotoXY(12, y); cout << sv.mssv;
				gotoXY(29, y); cout << sv.ho;
				gotoXY(51, y); cout << sv.ten;
				gotoXY(63, y); cout << sv.phai;
				gotoXY(68, y); cout << sv.sdt;
				vitri = strlen(sv.mssv);
				TextColor(14);
				goto MASV;
				break; //Tra ve con tro? sinh vien da tim` thay'
			}
			else {
				GhiChu("Ma Sinh Vien Khong Ton Tai!", 35, 27, 79, 500);
				TextColor(14);	gotoXY(33 + vitri, y);
			}
		}
		if (key == ESC || key == F2) { return; }
	}
MASV:
	while (1)
	{
		TextColor(236); gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 10";
		TextColor(14); gotoXY(12 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 15))
		{
			sv.mssv[vitri] = char(key);
			sv.mssv[vitri] = toupper(sv.mssv[vitri]);
			cout << sv.mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(12 + vitri, y);
			cout << " ";
			gotoXY(12 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.mssv[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.mssv, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == RIGHT)
		{
			sv.mssv[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.mssv, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
				Sleep(500);
				continue;
			}
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == ESC || key == F2) { return; }
	}
HO:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (A-Z) & (0-9). Toi da: 20";
		TextColor(14); gotoXY(29 + vitri, y);
		key = GetKey();
		if (sv.mssv[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Ma Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(12, y);
			goto MASV;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 20))
		{
			sv.ho[vitri] = char(key);
			sv.ho[vitri] = toupper(sv.ho[vitri]);
			cout << sv.ho[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(29 + vitri, y);
			cout << " ";
			gotoXY(29 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			if (sv.ho[vitri - 1] == ' ') { vitri--; }	//KT khi enter truoc do co phai khoang trang
			sv.ho[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ho, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == SPACE && sv.ho[vitri - 1] != ' ' && vitri > 0 && vitri < 20)
		{
			gotoXY(29 + vitri, y);
			cout << " ";
			sv.ho[vitri] = ' ';
			vitri++;
		}
		if (key == LEFT)
		{
			sv.ho[vitri] = '\0';
			vitri = strlen(sv.mssv);
			gotoXY(12 + vitri, y);
			goto MASV;
		}
		if (key == RIGHT)
		{
			if (sv.ho[vitri - 1] == ' ') { vitri--; }	//KT khi enter truoc do co phai khoang trang
			sv.ho[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ho, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == ESC || key == F2) { return; }
	}
TEN:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (A-Z). Toi da: 10        ";
		TextColor(14);  gotoXY(51 + vitri, y);
		key = GetKey();
		if (sv.ho[0] == '\0')
		{
			GhiChu("Ban Chua Nhap HO Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(29, y);
			goto HO;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			sv.ten[vitri] = char(key);
			sv.ten[vitri] = toupper(sv.ten[vitri]);
			cout << sv.ten[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(51 + vitri, y);
			cout << " ";
			gotoXY(51 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.ten[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ten, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == LEFT)
		{
			sv.ten[vitri] = '\0';
			vitri = strlen(sv.ho);
			gotoXY(29 + vitri, y);
			goto HO;
		}
		if (key == RIGHT)
		{
			sv.ten[vitri] = '\0';
			check_trung = kt_Lop_MSV_MH(ds, DSMH, sv.ten, 1);
			if (check_trung == -1) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Lop Tin Chi. Vui Long Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -2) {
				TextColor(78);
				gotoXY(10, 15); cout << "Trung Ma Sinh Vien. Nhap Lai!";
				Sleep(500);
				continue;
			}
			if (check_trung == -3) {
				TextColor(78);
				gotoXY(10, 15);
				cout << "Trung Ma Mon Hoc. Nhap Lai!";
			}
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == ESC || key == F2) { return; }
	}
PHAI:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Gioi tinh Nam / Nu. Toi da: 3         ";
		TextColor(14); gotoXY(63 + vitri, y);
		key = GetKey();
		if (sv.ten[0] == '\0')
		{
			GhiChu("Ban Chua Nhap TEN Sinh Vien!", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(51, y);
			goto TEN;
		}
		if (((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) && (vitri < 3))
		{
			sv.phai[vitri] = char(key);
			sv.phai[vitri] = toupper(sv.phai[vitri]);
			cout << sv.phai[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(63 + vitri, y);
			cout << " ";
			gotoXY(63 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") == 0) || (strcmp(sv.phai, "NU") == 0)) // So sanh
			{
				vitri = strlen(sv.sdt);
				goto SODT;
			}
			GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 79, 500); continue;
		}
		if (key == LEFT)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") != 0) && (strcmp(sv.phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam/Nu!", 35, 27, 74, 500); continue;
			}
			vitri = strlen(sv.ten);
			gotoXY(51 + vitri, y);
			goto TEN;
		}
		if (key == RIGHT)
		{
			sv.phai[vitri] = '\0';
			if ((strcmp(sv.phai, "NAM") != 0) && (strcmp(sv.phai, "NU") != 0))
			{
				GhiChu("Gioi Tinh phai la Nam / Nu!", 35, 27, 79, 500);
				continue;
			}
			vitri = strlen(sv.sdt);
			gotoXY(68 + vitri, y);
			goto SODT;
		}
		if (key == ESC || key == F2) { return; }
	}
SODT:
	while (1)
	{
		TextColor(236);	gotoXY(10, 15); cout << "Ki tu: (0-9). Toi da: 11        ";
		TextColor(14);	gotoXY(68 + vitri, y);
		key = GetKey();
		if (sv.phai[0] == '\0')
		{
			GhiChu("Ban Chua Nhap Gioi Tinh!", 35, 27, 79, 700);
			gotoXY(63, y);
			goto PHAI;
		}
		if ((key <= '9' && key >= '0') && (vitri < 11))
		{
			sv.sdt[vitri] = char(key);
			sv.sdt[vitri] = toupper(sv.sdt[vitri]);
			cout << sv.sdt[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(68 + vitri, y);
			cout << " ";
			gotoXY(68 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			check_change = true;
			sv.sdt[vitri] = '\0';
			for (int i = 0; i < DSLTC.n; i++) {
				for (PTRDK q = DSLTC.nodeltc[i]->DSDK; q != NULL; q = q->next) {
					if (strcmp(q->data.mssv, p->data.mssv) == 0) {
						strcpy(q->data.mssv, sv.mssv);
					}
				}
			}
			p->data = sv;
			GhiChu("Sua thanh cong", 35, 27, 79, 1000);
			return;
		}
		if (key == LEFT)
		{
			sv.sdt[vitri] = '\0';
			vitri = strlen(sv.phai);
			gotoXY(63 + vitri, y);
			goto PHAI;
		}
		if (key == ESC || key == F2) { return; }
	}
}
void XoaDauSV(PTRSV &DSSV) {
	PTRSV p = DSSV;	DSSV = DSSV->next;	delete p;
}
void XoaGiuaSV(PTRSV &DSSV, char c[]) {
	PTRSV temp = NULL;
	for (PTRSV p = DSSV; p != NULL; p = p->next)
	{
		if (strcmp(p->data.mssv, c) == 0)
		{
			temp->next = p->next;	delete p;	return;
		}
		temp = p; // temp luon la con tro truoc ben trai' cua con tro dang duyet
	}
}
void XoaCuoiSV(PTRSV &DSSV)
{
	PTRSV temp = NULL;
	for (PTRSV p = DSSV; p != NULL; p = p->next)
	{
		if (p->next == NULL)
		{
			temp->next = NULL;	delete p;	return;
		}
		temp = p; // temp luon la con tro truoc ben trai' cua con tro dang duyet
	}
}
void XoaSinhVien(Dslop &DSLTC, PTRSV &DSSV, bool &check_change)
{
	int key, x = 33, y = 14, vitri = 0, temp;
	NodeSV sv; 	sv.mssv[0] = NULL;
	PTRDK p;
	Khung_Xoa_SV();	gotoXY(x, y);
Reset:
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			sv.mssv[vitri] = char(key);
			sv.mssv[vitri] = toupper(sv.mssv[vitri]);
			cout << sv.mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.mssv[vitri] = '\0';	//Ngat chuoi~
			temp = KTSV(DSSV, sv.mssv);//KT trung sinh vien trong Listlop
			p = SearchSV_LTC(DSLTC, sv.mssv);
			if (temp != 1)
			{
				if (p != NULL) {
					GhiChu("Sinh Vien Da Dang Ki Mon. Khong Duoc Xoa!", 35, 27, 79, 700);
					TextColor(14);
					gotoXY(33 + vitri, y);
					goto Reset;
				}
				else {
					check_change = true;
					if (temp == 1) XoaDauSV(DSSV);
					if (temp == 0) XoaGiuaSV(DSSV, sv.mssv);
					if (temp == -1) XoaCuoiSV(DSSV);
					return;
				}
			}
			else {
				GhiChu("Ma Sinh Vien Khong Ton Tai!", 35, 27, 79, 500);
				TextColor(14);	gotoXY(33 + vitri, y);
			}
		}
		if (key == ESC || key == F3) { return; }
	}
}
void XemSinhVien(PTRSV &ds, PTRMH DSMH, Dslop &DSLTC)
{
	int key;
	int x = 40, y = 2;
	int vitri = 0, vitriMang, temp;
	int STT = 1;
	bool check_change = false;
	char malop[12];
	Khung_Nhap_MaLop();
	gotoXY(x, y);
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			temp = KTMaLop(ds, malop, 1); //KT trung ma lop
			if (temp != -1)
			{
				break;
			}
			else {
				GhiChu("     Ma Lop Khong Ton Tai!    ", 33, 5, 159, 500);
				gotoXY(40 + vitri, y);
				TextColor(14);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(40 + vitri, y);
			cout << " ";
			gotoXY(40 + vitri, y);
		}
		if (key == F5)
		{
			malop[vitri] = '\0';
			XemLop(DSLTC, ds, DSMH, 1);
			Khung_Nhap_MaLop();
			TextColor(223); gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
			TextColor(14);	gotoXY(40, y); cout << malop;
		}
		if (key == ESC) { TextColor(14); return; }
	}
	
	int trang = 0, tongtrang = 0, soluongsv = 0;
	int dem1 = 0, dem = 0;	//dem la dem dong`.  dem1 la vitri phan tu sv
	while (1)
	{
		dem1 = 0;
		NodeSV *SV = new NodeSV[MAXSV];
		for (PTRSV p = ds; p != NULL; p = p->next)
		{
			if(strcmp(p->data.malop, malop) == 0){
				SV[dem1] = p->data;
				dem1++;
			}
			
		}
		soluongsv = dem1;
		if (soluongsv == 0)
		{
			GhiChu("Chua co du lieu sinh vien", 35, 27, 79, 500);
		}
		else {
			if (soluongsv < 15)
			{
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((soluongsv - 1) / 15 + 1);
			}
		}
		//SapXepSV(ds.dsl[vitriMang].DSSV); 	//Sap Xep danh sach theo Ten Ho
		 //DÙ? DSSV v‡o mang?
		TextColor(14);	system("cls");
		Khung_Xuat_SV();
		dem = 0;
		for (int i = trang * 15; i < 15 + trang * 15 && i < dem1; i++)
		{
			TextColor(12); gotoXY(6, 8 + dem); cout << i + 1;
			TextColor(14);
			gotoXY(10, 8 + dem); cout << SV[i].mssv;
			gotoXY(26, 8 + dem); cout << SV[i].ho;
			gotoXY(47, 8 + dem); cout << SV[i].ten;
			gotoXY(58, 8 + dem); cout << SV[i].phai;
			gotoXY(69, 8 + dem); cout << SV[i].sdt;
			dem++;
		}
		TextColor(206);
		gotoXY(1, 0); cout << "MA lOP:";
		gotoXY(1, 2); cout << "TEN LOP:";
		gotoXY(1, 4); cout << "NIEN KHOA:";
		TextColor(7);
		gotoXY(9, 0); cout << SV[0].malop;
		HienThiTrang(trang + 1, tongtrang, 73, 26);
		gotoXY(81, 26);
		key = GetKey();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == F1)
		{
			gotoXY(18, 24);  TextColor(251);	cout << "F1"; //TÙ m‡u F1
			if (dem1 <= MAXSV - 1) {
				ThemSinhVien(ds, DSMH, check_change, malop);
			}
			else {
				GhiChu("LOP DA DAY SINH VIEN", 37, 27, 79, 1000);
				continue;
			}
		}
		if (key == F2)
		{
			gotoXY(35, 24);	TextColor(251);	cout << "F2"; //TÙ m‡u F2	
			SuaSinhVien(ds, DSMH, DSLTC, check_change);
		}
		if (key == F3)
		{
			gotoXY(50, 24);	TextColor(251);	cout << "F3"; //TÙ m‡u F3
			XoaSinhVien(DSLTC, ds, check_change);
		}
		if (key == ESC)
		{
			if (check_change == true)
			{
				putchar(7);	gotoXY(4, 24);  TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int temp = ThongBao_ESC();
				if (temp == -1) { continue; } //Tra ve -1 => Bat' duoc phim' ESC 1 l‚n` nua~
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					//GhiFileSV(ds); GhiFileDK(DSLTC);
				} //Them 1 SV moi cap nhat lai 
				  // can cap nhat file diem
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");	delete(SV); return;
		}
	}
}

//-----------------------DANH SACH LOP TIN CHI-----------------------------------------------------------------------------------------------------------------

void inDSLTC(Dslop DSLTC)
{
	if (EmptyLTC(DSLTC))
		cout << "Chua co danh sach lop!";
	else
		for (int i = 0; i<DSLTC.n; i++)
		{
			cout << "\nMon hoc thu :" << i + 1 << endl;
			cout << "\nMa Lop tin chi:" << "\t\t" << DSLTC.nodeltc[i]->malopTc;
			cout << "\nMa Mon hoc:" << "\t\t" << DSLTC.nodeltc[i]->mmh;
			cout << "\nNien Khoa:" << "\t\t" << DSLTC.nodeltc[i]->nienkhoa;
			cout << "\nHoc ki:" << "\t\t\t" << DSLTC.nodeltc[i]->hocki;
			cout << "\nNhom:" << "\t\t\t" << DSLTC.nodeltc[i]->nhom;
			cout << "\nSo sinh vien toi da:" << "\t" << DSLTC.nodeltc[i]->nsvmax;
			cout << "\n--------------------------------------------------";
		}
}

int checkLopTc(Dslop DSLTC, char kiemtra[], int n)
{
	int malop = atoi(kiemtra);
	if (DSLTC.n == 0)
		return 0;
	for (int i = 0; i <= n; i++)						// tra ve -1 : trung Ma lop
	{
		if (DSLTC.n == i) { continue; }
		if (DSLTC.nodeltc[i]->malopTc == malop)
			return -1;
	}
	return 0;
}


int Search_malopTc_hk(Dslop DSLTC, int malopTc, int hocki, int dem)
{

	for (int i = 0; i < dem; i++)
	{
		//so sanh bang ma lop tin chi
		if (DSLTC.nodeltc[i]->malopTc == malopTc)
		{
			if (DSLTC.nodeltc[i]->hocki == hocki) {
				return i; //neu phan trung thi tra ve vi tri i
			}
		}
	}
	return -1; //khong tim thay trung
}
int Search_mmh(Dslop DSLTC, char mmh[], int dem) {
	for (int i = 0; i < dem; i++)
	{
		//so sanh bang ma mon hoc
		if ((strcmp(DSLTC.nodeltc[i]->mmh, mmh)) == 0)
		{
			return i; //neu phan trung thi tra ve vi tri i
		}
	}
	return -1; //khong tim thay trung
}

int Search_trungmaLopTc(Dslop DSLTC, int malopTc, int vitrisua) {
	for (int i = 0; i<vitrisua; i++) {
		if (DSLTC.nodeltc[i]->malopTc == malopTc)
		{
			return 1; //neu phan trung thi tra ve true
		}
	}
	for (int j = vitrisua + 1; j<DSLTC.n; j++)
	{
		if (DSLTC.nodeltc[j]->malopTc == malopTc)
		{
			return 1; //neu phan trung thi tra ve true
		}
	}
	return 0;
}

int KiemtraBo4(Dslop DSLTC, Ltc *lopTc) {
	int vitriLTC = Search_mmh(DSLTC, lopTc->mmh, DSLTC.n - 1);
	for (int i = 0; i < DSLTC.n; i++) {
		if (strcmp(DSLTC.nodeltc[i]->mmh, lopTc->mmh) == 0) {
			if (strcmp(DSLTC.nodeltc[i]->nienkhoa, lopTc->nienkhoa) == 0) {
				if (DSLTC.nodeltc[i]->hocki- lopTc->hocki== 0) {
					if (DSLTC.nodeltc[i]->nhom- lopTc->nhom == 0) {
						return -2;
					}
					else continue;
				}
				else continue;
			}
			else continue;
		}
		else continue;
	}
	return -1;
}

int KiemtraBo4_v2(Dslop DSLTC, Ltc lopTc) {
	int vitriLTC = Search_mmh(DSLTC, lopTc.mmh, DSLTC.n);
	for (int i = 0; i < DSLTC.n; i++) {
		if (strcmp(DSLTC.nodeltc[i]->mmh, lopTc.mmh) == 0) {
			if (strcmp(DSLTC.nodeltc[i]->nienkhoa, lopTc.nienkhoa) == 0) {
				if (DSLTC.nodeltc[i]->hocki- lopTc.hocki == 0) {
					if (DSLTC.nodeltc[i]->nhom- lopTc.nhom== 0) {
						return -2;
					}
					//else continue;
				}
				//else continue;
			}
			//else continue;
		}
		//else continue;
	}
	return -1;
}
int DemsoLTC(Dslop &DSLTC) {
	int dem = 0;
	for (int i = 0; i<DSLTC.n; i++) {
		dem++;
	}
	return dem;
}
int fullLTC(Dslop &DSLTC, int dem) {
	int soluongltc = DemsoLTC(DSLTC);
	if (dem == (MAXLTC - soluongltc)) {
		GhiChu("Danh sach Lop Tin Chi DAY. Khong the them!", 35, 27, 79, 1000);
		return 1;
	} return 0;
}
//them hang loat Lop tin chi. not fix
//cau a 

int nhap_NK_HK(Ltc &ltc) {
	KhungLTC();
	int x = 38, y = 2;
	int key;
	int vitri = 0;
	ltc.nienkhoa[0] = NULL; ltc.hocki = 0;
NIENKHOA:
	while (1) {
		TextColor(14);
		gotoXY(38 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 4))
		{
			ltc.nienkhoa[vitri] = char(key);
			ltc.nienkhoa[vitri] = toupper(ltc.nienkhoa[vitri]);
			cout << ltc.nienkhoa[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(38 + vitri, y);
			cout << " ";
			gotoXY(38 + vitri, y);
		}
		if (key == ENTER && vitri == 4) {
			ltc.nienkhoa[vitri] = '\0';
			if (strcmp(ltc.nienkhoa, "2016") < 0)
			{
				GhiChu("              NAM KHONG HOP LE               ", 30, 4, 79, 700);
				gotoXY(64 + vitri, y);
				continue;
			}
			vitri = demchu(ltc.hocki);
			gotoXY(60 + vitri, y);
			goto HOCKI;
		}
		else {
			if (key == ENTER && vitri != 4) {
				GhiChu("         NIEN KHOA PHAI DAY DU 4 KI TU!      ", 30, 4, 79, 700);
				gotoXY(38 + vitri, y);
				continue;
			}
		}
		if (key == ESC) {
			return 0;
		}
	}
HOCKI:
	while (1) {
		gotoXY(60 + vitri, y);
		key = GetKey();
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			ltc.hocki = key - 48;
			cout << ltc.hocki;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			GhiChu("             DANG NHAP THANH CONG            ", 30, 4, 79, 700);
			system("cls");
			return 1;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			ltc.hocki = ltc.hocki/10;
			gotoXY(60 + vitri, y);
			cout << " ";
			gotoXY(60 + vitri, y);
		}
		if (key == LEFT)
		{
			vitri = strlen(ltc.nienkhoa);
			gotoXY(38 + vitri, y);
			goto NIENKHOA;
		}
	}
	if (key == ESC) {
		return 0;
	}
}

int DemSVDK(PTRDK DSDK)
{
	int dem = 0;
	for (PTRDK p = DSDK; p != NULL; p = p->next) { dem++; }
	return dem;
}

void xoa_ltc(Dslop &DSLTC, PTRMH &DSMH){
	int key;
	int x = 34, y = 2;
	int dem, trang = 0, tongtrang = 0;
	int kiemtraESC;
	int solop; //dem so lop thoa man
	int vitrilop;
	NodeDK sv; NodeMH mh; Ltc lopTc; 
	sv.mssv[0] = NULL; mh.mmh[0] = NULL; lopTc.nienkhoa[0] = NULL;
	kiemtraESC = nhap_NK_HK(lopTc);
	if (0 == kiemtraESC) {
		return; // qua trinh dang nhap dung lai se tra ve 0l
	}

	
	TextColor(14);	system("cls");	 //Khung_DKLTC();

	gotoXY(93, 3);
	//Khung_DKLTC();
	char malop[11];
	int vitri = 0;
	int quyetdinh;
	Ltc *aduma = new Ltc[MAXLTC];
	while (1)
	{
			int demtongtrang = 0;

		for (int i = 0; i < DSLTC.n; i++) 
			if (DSLTC.nodeltc[i]->hocki - lopTc.hocki == 0) 
				if (strcmp(DSLTC.nodeltc[i]->nienkhoa, lopTc.nienkhoa) == 0)aduma[demtongtrang++] = *DSLTC.nodeltc[i]; 
		if (demtongtrang < 15) {
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((demtongtrang - 1) / 15 + 1);
			}
		TextColor(14); 	Khung_Cao_Ky();  //Khung_DKLTC();
		gotoXY(24,1); TextColor(233); cout  << "                         ";
		gotoXY(24,2); TextColor(14); cout  << " Nam hoc: " << lopTc.nienkhoa << " Hoc ki: " << lopTc.hocki;
		gotoXY(24,3); TextColor(233); cout  << "                         ";
		gotoXY(24,2); TextColor(233); cout << " ";
		gotoXY(48,2); TextColor(233); cout << " ";
		gotoXY(12,24); TextColor(14); cout << "An Delete de xoa nhung lop khong dat yeu cau";
		dem = 0;
		for (int i = trang * 15; (i < 15 + trang * 15) && i < demtongtrang; i++) {
		
			TextColor(12); gotoXY(6, 8 + dem); cout << (i + 1);
			TextColor(14);
			gotoXY(10, 8 + dem); cout << aduma[i].malopTc;
			gotoXY(18, 8 + dem); cout << aduma[i].mmh;
			PTRMH a = Search_MH(DSMH, aduma[i].mmh);
			gotoXY(30, 8 + dem); cout << a->data.tmh;
			gotoXY(69, 8 + dem); cout << aduma[i].nhom;
			
			gotoXY(79, 8 + dem); cout << DemSVDK(aduma[i].DSDK);
			gotoXY(88, 8 + dem); cout << aduma[i].nsvmax - DemSVDK(aduma[i].DSDK);
		
			dem++;
		
		}
		HienThiTrang(trang + 1, tongtrang, 65, 26);
		
		
		TextColor(14);
		gotoXY(93 + vitri, 3);
		key = GetKey();
		if (( key == DOWN) && trang < tongtrang - 1) { trang++;}
		else if (( key == UP) && trang > 0) { trang--; }
		else if (key == ESC)
		{
			delete[] aduma;
			system("cls");
			return;
		}
		else if(key == -83)
		{
			int a = ThongBao_ESCaoky();
			if(a == -1)continue;
			else if(a == 1){
				GhiChu("Da Xoa Het Sach", 35, 27, 233, 700);
				for(int i = 0; i < demtongtrang; i++){
					int j = Search_malopTc(DSLTC, aduma[i].malopTc, DSLTC.n);
					if(aduma[i].nsvmin > DemSVDK(aduma[i].DSDK))DeleteLTC(DSLTC, j);
				}
			}else continue;
		}
		
		
	}
}



// da nhap nien khoa hok ki roi
void nhapDSLTC(Dslop &DSLTC, PTRMH DSMH) {
	int check;
	//Ltc ltc;
	//check = nhap_NK_HK(ltc);
	//if (0 == check) { return; }
	int dem, demkhongdoi = 0;
	if (fullLTC(DSLTC, demkhongdoi)) { return; }
	int key;
	int STT = 1;
	int vitri = 0, x = 10, y = 8;
	int soluonglop = DemsoLTC(DSLTC);
	Ltc *lopTc = new Ltc[MAXLTC - soluonglop];
	for (dem = 0; dem < MAXLTC - soluonglop; dem++) {
		lopTc[dem].malopTc = 0;
		lopTc[dem].mmh[0] = NULL;
		lopTc[dem].nienkhoa[0] = NULL;
		lopTc[dem].hocki=0;
		lopTc[dem].nhom=0;
		lopTc[dem].nsvmin=0;
		lopTc[dem].nsvmax=0;
	}
	dem = 0;
	int check_trung;
	bool check_change = false;
	Khung_Nhap_LTC();
	TextColor(12);
	gotoXY(6, 8); cout << STT;
	char tam[11];
	memset(tam, 0, sizeof(tam));
	TextColor(14);
	gotoXY(27, 4); cout << "SO LOP TIN CHI HIEN TAI LA:" << demkhongdoi + soluonglop;
	char tam1[1];
	//label MALOPTC
MALOPTC:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                        ";
		gotoXY(16, 30); cout << "     MA LOP TU DONG TANG                                ";
		gotoXY(16, 31); cout << "                                                        ";
		TextColor(14);
		if (lopTc[dem - 1].nsvmax == 0 && y > 8) // kiem tra hang truoc do nhap da du du lieu chua
		{
			GhiChu("Ban chua nhap so luong sinh vien", 35, 27, 70, 700);
			vitri = 0;
			gotoXY(63, --y);
			dem--;
			goto SOLUONGMAX; // nhay lenh den label sosvmax
		}
		if (fullLTC(DSLTC, demkhongdoi)) { Sleep(2000);  continue; }
			lopTc[dem].malopTc = Maloptc(DSLTC) + demkhongdoi;
			gotoXY(10, y);
			cout << lopTc[dem].malopTc;
			vitri = strlen(lopTc[dem].mmh);
			gotoXY(24 + vitri, y);
			goto MAMH;
	}
MAMH:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << " MA MON HOC: GOM CAC KI TU (A-Z) & (0-9), TOI DA: 10 KI TU  ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(24 + vitri, y);
		key = GetKey();
		if (lopTc[dem].malopTc == 0)		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap ma lop", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(10, y);
			goto MALOPTC;
		}
		// Tuong tu kiem tra hocki, nienkhoa,.... cua thang nhap o truoc

		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			lopTc[dem].mmh[vitri] = char(key);
			lopTc[dem].mmh[vitri] = toupper(lopTc[dem].mmh[vitri]);
			cout << lopTc[dem].mmh[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc[dem].mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc[dem].mmh);// kiem tra mon hoc co ton tai hay k
			if (temp == 1) {
				vitri = strlen(lopTc[dem].nienkhoa);
				gotoXY(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(24 + vitri, y);// co 2 dau cach thi chi nha 1 dau
			cout << " ";
			gotoXY(24 + vitri, y);
		}
		if (key == LEFT)continue;
		
		if (key == RIGHT)
		{
			lopTc[dem].mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc[dem].mmh);
			if (temp == 1) {
				vitri = strlen(lopTc[dem].nienkhoa);
				gotoXY(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}
		}
		if (key == UP && y > 8)
		{
			lopTc[dem].mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc[dem].mmh);
			if (temp == 1) {
				int pochinki;
				pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);//pochinki = -1 => ktra ktrung voi cac dulieu trong file
				if (pochinki == -1) {
					for (int i = 0; i <= demkhongdoi; i++) {
						if (i == dem) { continue; }
						if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
							if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
									if (lopTc[i].hocki- lopTc[dem].hocki == 0)
									if (lopTc[i].nhom- lopTc[dem].nhom == 0)
										pochinki = -2;
					}
				}
				if (pochinki == -2) {
					GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
					continue;
				}
				dem--;
				vitri = strlen(lopTc[dem].mmh);// nhay ve vi tri ban dau
				gotoXY(24 + vitri, --y);
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}

		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}
			lopTc[dem].mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc[dem].mmh);
			if (temp == 1) {
				int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (-lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
				dem++;
				vitri = strlen(lopTc[dem].mmh);
				gotoXY(24 + vitri, ++y);
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}

		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{
				lopTc[dem].mmh[vitri] = '\0';
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls"); delete(lopTc);	return;
		}
	}
NIENKHOA:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << "    NIEN KHOA: GOM CAC KI TU  (0-9), TOI DA: 4 KI TU        ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(41 + vitri, y);
		key = GetKey();
		if (lopTc[dem].mmh[0] == '\0')		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap ma mon hoc", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(24, y);
			goto MAMH;
		}
		if ((key <= '9' && key >= '0') && (vitri<4))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc[dem].nienkhoa[vitri] = char(key);
			lopTc[dem].nienkhoa[vitri] = toupper(lopTc[dem].nienkhoa[vitri]);
			cout << lopTc[dem].nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri > 0)
		{
			lopTc[dem].nienkhoa[vitri] = '\0';
			if (strcmp(lopTc[dem].nienkhoa, "2017") > 0) {
				vitri = demchu(lopTc[dem].hocki);
				gotoXY(56 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("BAY GIO LA NAM 2021", 35, 27, 79, 700);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(41 + vitri, y);
			cout << " ";
			gotoXY(41 + vitri, y);
		}
		if (key == LEFT&& vitri < 9)
		{
			lopTc[dem].nienkhoa[vitri] = '\0';
			
				vitri = strlen(lopTc[dem].mmh);
				gotoXY(24 + vitri, y);
				goto MAMH;
			
	
		}
		if (key == RIGHT)
		{
			lopTc[dem].nienkhoa[vitri] = '\0';
			if (strcmp(lopTc[dem].nienkhoa, "2016-2019") > 0) {
				vitri = demchu(lopTc[dem].hocki);
				gotoXY(56 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("BAY GIO LA NAM 2021", 35, 27, 79, 700);
				continue;
			}
		
		}
		if (key == UP && y > 8)
		{
			lopTc[dem].nienkhoa[vitri] = '\0';
			if (strcmp(lopTc[dem].nienkhoa, "2016") > 0) {
				int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
				dem--;
				vitri = strlen(lopTc[dem].nienkhoa);
				gotoXY(41 + vitri, --y);
			}
			else {
				GhiChu("BAY GIO LA NAM 2021", 35, 27, 79, 700);
				continue;
			}

		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}
			lopTc[dem].nienkhoa[vitri] = '\0';
			if (strcmp(lopTc[dem].nienkhoa, "2016") > 0) {
				int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
				dem++;
				vitri = strlen(lopTc[dem].nienkhoa);
				gotoXY(41 + vitri, ++y);
			}
			else {
				GhiChu("BAY GIO LA NAM 2021", 35, 27, 79, 700);
				continue;
			}
		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{
				lopTc[dem].nienkhoa[vitri] = '\0';
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls");	delete(lopTc); return;
		}
	}
HOCKI:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << "      HOC KI: GOM CAC KI TU  (1-9), TOI DA: 1 KI TU         ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(56 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc[dem].nienkhoa[0] == '\0')		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap Nien Khoa", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(41, y);
			goto NIENKHOA;
		}
		if ((key <= '3' && key >= '1') && (vitri < 1))
		{
			lopTc[dem].hocki = key - 48;
			cout << lopTc[dem].hocki;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			
				vitri = demchu(lopTc[dem].nhom);
				gotoXY(66 + vitri, y);
				goto NHOM;
		
			
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc[dem].hocki = lopTc[dem].hocki/10;
			gotoXY(56 + vitri, y);
			cout << " ";
			gotoXY(56 + vitri, y);
		}
		if (key == LEFT)
		{
			
			vitri = strlen(lopTc[dem].nienkhoa);
			gotoXY(41 + vitri, y);
			goto NIENKHOA;
		}
		if (key == RIGHT)
		{
			
				vitri = demchu(lopTc[dem].nhom);
				gotoXY(66 + vitri, y);
				goto NHOM;
		
		}
		if (key == UP && y > 8)
		{
			
			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
				dem--;
				vitri = demchu(lopTc[dem].hocki);
				gotoXY(56 + vitri, --y);
			
		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}
			
			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
				dem++;
				vitri = demchu(lopTc[dem].hocki);
				gotoXY(56 + vitri, ++y);
			
		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{
				
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls");	delete(lopTc);  return;
		}
	}
NHOM:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << "       NHOM : GOM CAC KI TU  (1-9), TOI DA: 1 KI TU         ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(65 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc[dem].hocki == 0)		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap Hoc Ki", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(56, y);
			goto HOCKI;
		}
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			lopTc[dem].nhom = key - 48;
			cout << lopTc[dem].nhom;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
			vitri = demchu(lopTc[dem].nsvmin);
			gotoXY(73 + vitri, y);
			goto SOLUONGMIN;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc[dem].nhom = lopTc[dem].nhom/10;
			gotoXY(65 + vitri, y);
			cout << " ";
			gotoXY(65 + vitri, y);
		}
		if (key == LEFT)
		{
			
			vitri = demchu(lopTc[dem].hocki);
			gotoXY(56 + vitri, y);
			goto HOCKI;
		}
		if (key == RIGHT)
		{

			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
			vitri = demchu(lopTc[dem].nsvmin);
			gotoXY(73 + vitri, y);
			goto SOLUONGMIN;
		}
		if (key == UP && y > 8)
		{
			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
			dem--;
			vitri = demchu(lopTc[dem].nhom);
			gotoXY(65 + vitri, --y);
		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}
			int pochinki;
			pochinki = KiemtraBo4_v2(DSLTC, lopTc[dem]);
			if (pochinki == -1) {
				for (int i = 0; i <= demkhongdoi; i++) {
					if (i == dem) { continue; }
					if (strcmp(lopTc[i].mmh, lopTc[dem].mmh) == 0)
						if (strcmp(lopTc[i].nienkhoa, lopTc[dem].nienkhoa) == 0)
							if (lopTc[i].hocki- lopTc[dem].hocki == 0)
								if (lopTc[i].nhom- lopTc[dem].nhom == 0)
									pochinki = -2;
				}
			}
			if (pochinki == -2) {
				GhiChu("4 field MAMH , NIEN KHOA, HOC KI, NHOM khong duoc hoan toan giong nhau!", 8, 27, 79, 2000);
				continue;
			}
			dem++;
			vitri = demchu(lopTc[dem].nhom);
			gotoXY(65 + vitri, ++y);
		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{
				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls");	delete(lopTc); return;
		}
	}
SOLUONGMIN:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << "       NHOM : GOM CAC KI TU  (1-9), TOI DA: 1 KI TU         ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(73 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc[dem].nhom == 0)		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap nhom", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(65, y);
			goto NHOM;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc[dem].nsvmin = lopTc[dem].nsvmin*10 + key-48;
			gotoXY(73, y);
			cout << lopTc[dem].nsvmin;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{

			vitri = demchu(lopTc[dem].nsvmax);
			gotoXY(82 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc[dem].nsvmin = lopTc[dem].nsvmin/10;
			gotoXY(73 + vitri, y);
			cout << " ";
			gotoXY(73 + vitri, y);
		}
		if (key == LEFT)
		{
			vitri = demchu(lopTc[dem].nhom);
			gotoXY(65 + vitri, y);
			goto NHOM;
		}
		if (key == RIGHT)
		{

			vitri = demchu(lopTc[dem].nsvmax);
			gotoXY(82 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == UP && y > 8)
		{
			dem--;
			vitri = demchu(lopTc[dem].nsvmin);
			gotoXY(73 + vitri, --y);
		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}

			dem++;
			vitri = demchu(lopTc[dem].nsvmin);
			gotoXY(73 + vitri, ++y);
		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{

				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls");	delete(lopTc); return;
		}
	}
SOLUONGMAX:
	while (1)
	{
		TextColor(244);				//Chu thich
		gotoXY(16, 29); cout << "                                                            ";
		gotoXY(16, 30); cout << "    SO LUONG : GOM CAC KI TU  (0-9), TOI DA: 3 KI TU        ";
		gotoXY(16, 31); cout << "                                                            ";
		TextColor(14);
		gotoXY(82 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc[dem].nsvmin == 0)		//Kiem tra  Eph˙} truoc c Edu~ lieu chua
		{
			GhiChu("Ban chua nhap min", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(74, y);
			goto SOLUONGMIN;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc[dem].nsvmax = lopTc[dem].nsvmax*10 + key -48;
			gotoXY(82,y);
			cout << lopTc[dem].nsvmax;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
 // cai nay de ngat chuoi, chuyen sang ben phai hoac trai nhap tiep
			if(lopTc[dem].nsvmax < lopTc[dem].nsvmin){
				GhiChu("So sinh vien max phai lon hon min", 40, 27, 228, 500);
				continue;
			}
			check_change = true;
			GhiChu("Da luu vao bo nho", 40, 27, 228, 500);	TextColor(12);
			
			
			gotoXY(6, y + 1);
			if (lopTc[dem + 1].malopTc == 0 && dem == demkhongdoi)	//Khong cho bien dem tang len khi sua loi~ cac NK phia' trÍn
			{
				TextColor(12);
				cout << ++STT;
				demkhongdoi++;//dem o day la bien co dinh cao nhat de ds.n = dem tai ESC
				TextColor(14);
				gotoXY(27, 4); cout << "SO LOP TIN CHI HIEN TAI LA:" << demkhongdoi + soluonglop;
			}
			if ((STT - 1) % 15 == 0) //Khi svien day` khung. Reset lai khung
			{
				y = 7;
				system("cls");
				TextColor(14);
				Khung_Nhap_LTC();
				TextColor(12);
				gotoXY(6, 8);
				cout << STT;
			}
			dem++;
			gotoXY(10 + vitri, ++y);
			goto MALOPTC;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc[dem].nsvmax = lopTc[dem].nsvmax/10;
			gotoXY(82 + vitri, y);
			cout << " ";
			gotoXY(82 + vitri, y);
		}
		if (key == LEFT)
		{
			if(lopTc[dem].nsvmax < lopTc[dem].nsvmin){
				GhiChu("So sinh vien max phai lon hon min", 40, 27, 228, 500);
				continue;
			}
			vitri = demchu(lopTc[dem].nsvmin);
			gotoXY(73 + vitri, y);
			goto SOLUONGMIN;
		}
		if (key == UP && y > 8)
		{

			dem--;
			vitri = demchu(lopTc[dem].nsvmax);
			gotoXY(82 + vitri, --y);
		}
		if (key == DOWN && y < 22)
		{
			if (dem == demkhongdoi) {
				continue;
			}

			dem++;
			vitri = demchu(lopTc[dem].nsvmax);
			gotoXY(82 + vitri, ++y);
		}
		if (key == ESC)
		{
			if (check_change == true) //Co su thay doi
			{

				int temp = ThongBao_ESC_Nhap();
				if (temp == -1)	//-1 la Bat duoc 1 phim ESC nua~
				{
					continue;
				}
				if (temp == 1)
				{
					GhiChu("Luu file thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) {
					GhiChu("Luu file khong thanh cong", 35, 27, 79, 2000);
					for (int i = 0; i<demkhongdoi; i++) {
						InsertLTC(DSLTC, lopTc[i], DSLTC.n);
					}
				}
			}
			system("cls"); delete(lopTc);	return;
		}
	}
}

//Them Lop Tin chi.

void ThemLTC(Dslop &DSLTC, PTRMH DSMH, bool &check_change) {

	int key;
	int STT = 1;
	int vitri = 0, x = 9, y = 11;
	int check_trung;
	int pochinki;
	Ltc lopTc;
	lopTc.malopTc = 0; lopTc.mmh[0] = NULL; lopTc.nienkhoa[0] = NULL; lopTc.hocki= 0; lopTc.nhom=0; lopTc.nsvmax=0;lopTc.nsvmin=0;
	Khung_Them_LTC();
	TextColor(12);
	char tam[11];
	memset(tam, 0, sizeof(tam));
	gotoXY(x, y);

MALOPTC:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Helo";
		TextColor(14);
		gotoXY(9 + vitri, y);
		lopTc.malopTc = Maloptc(DSLTC);
		cout << lopTc.malopTc;
		gotoXY(24 + vitri, y);
		goto MAMH;
	}
MAMH:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so & chu: (A-Z) && (0-9). Toi da 10 ki tu!";
		TextColor(14);
		gotoXY(24 + vitri, y);
		key = GetKey();
		if (lopTc.malopTc == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap ma lop", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(9, y);
			goto MALOPTC;
		}
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			lopTc.mmh[vitri] = char(key);
			lopTc.mmh[vitri] = toupper(lopTc.mmh[vitri]);
			cout << lopTc.mmh[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc.mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc.mmh);
			if (temp == 1) {
				vitri = strlen(lopTc.nienkhoa);
				gotoXY(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(24 + vitri, y);
			cout << " ";
			gotoXY(24 + vitri, y);
		}
		
		if (key == RIGHT)
		{
			lopTc.mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc.mmh);
			if (temp == 1) {
				vitri = strlen(lopTc.nienkhoa);
				gotoXY(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
NIENKHOA:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so: (0-9). Toi da 4 ki tu!";
		TextColor(14);
		gotoXY(41 + vitri, y);
		key = GetKey();
		if (lopTc.mmh[0] == '\0')		//kiemtra du lieu field truoc
		{
			GhiChu("Ban chua nhap ma mon hoc", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(24, y);
			goto MAMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nienkhoa[vitri] = char(key);
			lopTc.nienkhoa[vitri] = toupper(lopTc.nienkhoa[vitri]);
			cout << lopTc.nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc.nienkhoa[vitri] = '\0';
			if (strcmp(lopTc.nienkhoa, "2016") >0 )
			{
				vitri = demchu(lopTc.hocki);
				gotoXY(54 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("              BAY GIO LA NAM 2021               ", 35, 27, 79, 700);
				gotoXY(41 + vitri, y);
				continue;
			}

		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(41 + vitri, y);
			cout << " ";
			gotoXY(41 + vitri, y);
		}
		if (key == LEFT)
		{
			lopTc.nienkhoa[vitri] = '\0';
			vitri = strlen(lopTc.mmh);
			gotoXY(24 + vitri, y);
			goto MAMH;
		}
		if (key == RIGHT)
		{
			lopTc.nienkhoa[vitri] = '\0';
			if (strcmp(lopTc.nienkhoa, "2016")>0)
			{
				vitri = demchu(lopTc.hocki);
				gotoXY(54 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("              NAM KHONG HOP LE               ", 35, 27, 79, 700);
				gotoXY(41 + vitri, y);
				continue;
			}


		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
HOCKI:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so: (0-9). Toi da 1 ki tu!";
		TextColor(14);
		gotoXY(54 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nienkhoa[0] == '\0')
		{
			GhiChu("Ban chua nhap nien khoa", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(41, y);
			goto NIENKHOA;
		}
		if ((key <= '3' && key >= '1') && (vitri < 1))
		{
			lopTc.hocki =key - 48;

			cout << lopTc.hocki;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.hocki = lopTc.hocki/10;
			gotoXY(54 + vitri, y);
			cout << " ";
			gotoXY(54 + vitri, y);
		}
		if (key == LEFT)
		{

			vitri = strlen(lopTc.nienkhoa);
			gotoXY(41 + vitri, y);
			goto NIENKHOA;
		}
		if (key == RIGHT)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
NHOM:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 1 ki tu!";
		TextColor(14);
		gotoXY(64 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.hocki == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap hoc ki", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(54, y);
			goto HOCKI;
		}
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			lopTc.nhom = key -48;

			cout << lopTc.nhom;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			pochinki = KiemtraBo4_v2(DSLTC, lopTc);
			if (-1 == pochinki) {
				vitri = demchu(lopTc.nsvmax);
				gotoXY(71 + vitri, y);
				goto SOLUONGMIN;
			}
			if (-2 == pochinki) {
				GhiChu("Thong tin 4 field Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nhom = lopTc.nhom/10;
			gotoXY(64 + vitri, y);
			cout << " ";
			gotoXY(64 + vitri, y);
		}
		if (key == LEFT)
		{

			vitri = demchu(lopTc.hocki);
			gotoXY(54 + vitri, y);
			goto HOCKI;
		}
		if (key == RIGHT)
		{
			pochinki = KiemtraBo4_v2(DSLTC, lopTc);
			if (-1 == pochinki) {
				vitri = demchu(lopTc.nsvmax);
				gotoXY(71 + vitri, y);
				goto SOLUONGMIN;
			}
			if (-2 == pochinki) {
				GhiChu("Thong tin 4 field Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
SOLUONGMIN:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		TextColor(14);
		gotoXY(71 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nhom == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap nhom", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(64, y);
			goto NHOM;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nsvmin = lopTc.nsvmin*10 + key -48;
			gotoXY(71, y);
			cout << lopTc.nsvmin;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
 // cai nay de ngat chuoi, chuyen sang ben phai hoac trai nhap tiep
			vitri = demchu(lopTc.nsvmax);
			gotoXY(81 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nsvmin = lopTc.nsvmin/10;
			gotoXY(71 + vitri, y);
			cout << " ";
			gotoXY(71 + vitri, y);
		}
		if (key == RIGHT)
		{

			vitri = demchu(lopTc.nsvmax);
			gotoXY(81 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == LEFT)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
SOLUONGMAX:
	while (1)
	{
		TextColor(245);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		TextColor(14);
		gotoXY(81 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nsvmin == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap min", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(71, y);
			goto SOLUONGMIN;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nsvmax = lopTc.nsvmax*10 + key-48;
			gotoXY(81,y);
			cout << lopTc.nsvmax;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			if(lopTc.nsvmax < lopTc.nsvmin){
				GhiChu("So sinh vien max phai lon hon min", 40, 27, 228, 500);
				continue;
			}
			check_change = true;
// cai nay de ngat chuoi, chuyen sang ben phai hoac trai nhap tiep
			InsertLTC(DSLTC, lopTc, DSLTC.n);
			GhiChu("Da luu vao bo nho", 40, 27, 228, 500);
			return;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nsvmax = lopTc.nsvmax/10;
			gotoXY(81 + vitri, y);
			cout << " ";
			gotoXY(81 + vitri, y);
		}
		if (key == LEFT)
		{
			if(lopTc.nsvmax < lopTc.nsvmin){
				GhiChu("So sinh vien max phai lon hon min", 40, 27, 228, 500);
				continue;
			}
			vitri = demchu(lopTc.nsvmin);
			gotoXY(71 + vitri, y);
			goto SOLUONGMIN;
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
}
//Xoa Lop Tin chi
void XoaLTC(Dslop &DSLTC, bool &check_change) {
	int key;
	int x = 33, y = 14;
	int vitri = 0, vitri_LTC;
	int malopXoa;
	char tam[11];
	Khung_Xoa_LTC();
	gotoXY(x, y);
	while (1)
	{
		TextColor(14);
		key = GetKey();
		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
			tam[vitri] = toupper(tam[vitri]);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			malopXoa = atoi(tam);
			vitri_LTC = Search_malopTc(DSLTC, malopXoa, DSLTC.n);
			if (-1 == vitri_LTC) {
				GhiChu("LOP TIN CHI KHONG TON TAI!", 35, 27, 79, 700);
				gotoXY(33 + vitri, y);
				continue;
			}
			else {
				if (DSLTC.nodeltc[vitri_LTC]->DSDK != NULL) {
					GhiChu("LOP TIN CHI DA CO SINH VIEN. KHONG THE XOA!", 35, 27, 79, 700);
					continue;
				}
				check_change = true;
				DeleteLTC(DSLTC, vitri_LTC);
				GhiChu("XOA THANH CONG LOP TIN CHI", 35, 27, 79, 1000);
				return;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ESC || key == F3) {
			return;
		}
	}
}
//Sua Lop Tin Chi
void SuaLTC(Dslop &DSLTC, PTRMH DSMH, bool &check_change) {
	int key;
	int x = 33, y = 11;
	int vitri = 0, vitri_LTC;
	int malopSua;
	char tam[10];
	int check_trung;
	int maLtc_trung;
	int ktmaLtc_trung;
	//DSLTC.n++;
	Ltc lopTc;
	Khung_Sua_LTC();
	gotoXY(x, y);
	while (1) {
		TextColor(14);
		key = GetKey();
		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			tam[vitri] = char(key);
			tam[vitri] = toupper(tam[vitri]);
			cout << tam[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			tam[vitri] = '\0';
			malopSua = atoi(tam);
			vitri_LTC = Search_malopTc(DSLTC, malopSua, DSLTC.n);
			if (-1 == vitri_LTC) {
				GhiChu("LOP TIN CHI KHONG TON TAI!", 35, 27, 79, 700);
				gotoXY(33 + vitri, y);
				TextColor(14);
				continue;
			}
			else {
				//memset(tam, 0, sizeof(tam));
				vitri = 0;
				gotoXY(9, y);
				Khung_Them_LTC();
				TextColor(4);
				//itoa(DSLTC.nodeltc[vitri_LTC]->malopTc, tam, 10);
				lopTc.malopTc = DSLTC.nodeltc[vitri_LTC]->malopTc;
				itoa(lopTc.malopTc, tam, 10);//tam ve he so 10
				vitri = strlen(DSLTC.nodeltc[vitri_LTC]->mmh);
				strcpy(lopTc.mmh, DSLTC.nodeltc[vitri_LTC]->mmh);
				strcpy(lopTc.nienkhoa, DSLTC.nodeltc[vitri_LTC]->nienkhoa);
				lopTc.hocki= DSLTC.nodeltc[vitri_LTC]->hocki;
				lopTc.nhom= DSLTC.nodeltc[vitri_LTC]->nhom;
				lopTc.nsvmax= DSLTC.nodeltc[vitri_LTC]->nsvmax;
				lopTc.nsvmin= DSLTC.nodeltc[vitri_LTC]->nsvmin;
				gotoXY(9, y); cout << tam;
				gotoXY(24, y); cout << lopTc.mmh;
				gotoXY(41, y); cout << lopTc.nienkhoa;
				gotoXY(54, y); cout << lopTc.hocki;
				gotoXY(64, y); cout << lopTc.nhom;
				gotoXY(71, y); cout << lopTc.nsvmin;
				gotoXY(81, y); cout << lopTc.nsvmax;
				goto MAMH;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(33 + vitri, y);
			cout << " ";
			gotoXY(33 + vitri, y);
		}
		if (key == ESC || key == F2)
		{
			return;
		}
	}

//MALOPTC:
//	while (1)
//	{
//		TextColor(245);
//		gotoXY(19, 13); cout << "Ki tu so: (0-9). Toi da 10 ki tu!";
//		TextColor(14);
//		gotoXY(9 + vitri, y);
//		key = GetKey();
//
//		if ((key >= '0' && key <= '9') && (vitri < 10))
//		{
//			tam[vitri] = char(key);
//			tam[vitri] = toupper(tam[vitri]);
//			cout << tam[vitri];
//			vitri++;
//		}
//		if (key == ENTER && vitri != 0)
//		{
//			tam[vitri] = '\0';
//			//ktmaLtc_trung = Search_trungmaLopTc(DSLTC, maLtc_trung, vitri_LTC);
//			check_trung = Search_malopTc(DSLTC, atoi(tam), DSLTC.n);
//			if (check_trung != -1 && check_trung != vitri_LTC) {
//				GhiChu("Ma lop tin chi la duy nhat! Da ton tai", 35, 27, 79, 1000);
//				gotoXY(9 + vitri, y);
//				continue;
//			}
//			lopTc.malopTc = atoi(tam);
//			vitri = strlen(lopTc.mmh);
//			gotoXY(24 + vitri, y);
//			goto MAMH;
//		}
//		if (key == BACKSPACE && vitri > 0)
//		{
//			vitri--;
//			gotoXY(9 + vitri, y);
//			cout << " ";
//			gotoXY(9 + vitri, y);
//		}
//		if (key == RIGHT)
//		{
//			tam[vitri] = '\0';
//			//ktmaLtc_trung = Search_trungmaLopTc(DSLTC, maLtc_trung, vitri_LTC);
//			check_trung = Search_malopTc(DSLTC, atoi(tam), DSLTC.n);
//			if (check_trung != -1 && check_trung != vitri_LTC) {
//				GhiChu("Ma lop tin chi la duy nhat! Da ton tai", 35, 27, 79, 1000);
//				gotoXY(9 + vitri, y);
//				continue;
//			}
//			lopTc.malopTc = atoi(tam);
//			vitri = strlen(lopTc.mmh);
//			gotoXY(24 + vitri, y);
//			goto MAMH;
//		}
//		if (key == ESC || key == F2)
//		{
//			//DSLTC.n--;
//			return;
//		}
//	}
MAMH:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so & chu: (A-Z) && (0-9). Toi da 10 ki tu!";
		TextColor(14);
		gotoXY(24 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			lopTc.mmh[vitri] = char(key);
			lopTc.mmh[vitri] = toupper(lopTc.mmh[vitri]);
			cout << lopTc.mmh[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc.mmh[vitri] = '\0';
			int temp;
			temp = KTMH(DSMH, lopTc.mmh);
			if (temp == 1) {
				vitri = strlen(lopTc.nienkhoa);
				gotoXY(41 + vitri, y);
				goto NIENKHOA;
			}
			else {
				GhiChu("MON HOC KHONG TON TAI", 35, 27, 79, 700);
				gotoXY(24 + vitri, y);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(24 + vitri, y);
			cout << " ";
			gotoXY(24 + vitri, y);
		}
		
		if (key == RIGHT)          // sua lai them phan check mamh
		{
			lopTc.mmh[vitri] = '\0';
			vitri = strlen(lopTc.nienkhoa);
			gotoXY(41 + vitri, y);
			goto NIENKHOA;
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return;
		}
	}
NIENKHOA:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so: (0-9). Toi da 4 ki tu!";
		TextColor(14);
		gotoXY(41 + vitri, y);
		key = GetKey();
		if (lopTc.mmh == '\0')		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap ma mon hoc", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(24, y);
			goto MAMH;
		}
		if ((key <= '9' && key >= '0') && (vitri < 4))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nienkhoa[vitri] = char(key);
			lopTc.nienkhoa[vitri] = toupper(lopTc.nienkhoa[vitri]);
			cout << lopTc.nienkhoa[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			lopTc.nienkhoa[vitri] = '\0';
			if (strcmp(lopTc.nienkhoa, "2016") >0)
			{
				vitri = demchu(lopTc.hocki);
				gotoXY(54 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("              BAY GIO LA NAM 2021               ", 35, 27, 79, 700);
				gotoXY(41 + vitri, y);
				continue;
			}

		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(41 + vitri, y);
			cout << " ";
			gotoXY(41 + vitri, y);
		}
		if (key == LEFT)
		{
			lopTc.nienkhoa[vitri] = '\0';
			vitri = strlen(lopTc.mmh);
			gotoXY(24 + vitri, y);
			goto MAMH;
		}
		if (key == RIGHT)
		{
			lopTc.nienkhoa[vitri] = '\0';
			if (strcmp(lopTc.nienkhoa, "2016")>0)
			{
				vitri = demchu(lopTc.hocki);
				gotoXY(54 + vitri, y);
				goto HOCKI;
			}
			else {
				GhiChu("              BAY GIO LA NAM 2021              ", 35, 27, 79, 700);
				gotoXY(41 + vitri, y);
				continue;
			}
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return;
		}
	}
HOCKI:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so: (0-9). Toi da 1 ki tu!";
		TextColor(14);
		gotoXY(54 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nienkhoa == '\0')		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap nien khoa", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(41, y);
			goto NIENKHOA;
		}
		if ((key <= '3' && key >= '1') && (vitri < 1))
		{
			lopTc.hocki = key - 48;
			cout << lopTc.hocki;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.hocki = lopTc.hocki/10;
			gotoXY(54 + vitri, y);
			cout << " ";
			gotoXY(54 + vitri, y);
		}
		if (key == LEFT)
		{

			vitri = strlen(lopTc.nienkhoa);
			gotoXY(41 + vitri, y);
			goto NIENKHOA;
		}
		if (key == RIGHT)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F2)
		{
			return;
		}
	}
NHOM:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 1 ki tu!";
		TextColor(14);
		gotoXY(64 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.hocki == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap hoc ki", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(54, y);
			goto HOCKI;
		}
		if ((key <= '9' && key >= '1') && (vitri < 1))
		{
			lopTc.nhom = key - 48;

			cout << lopTc.nhom;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{

			
				vitri = demchu(lopTc.nsvmin);
				gotoXY(71 + vitri, y);
				goto SOLUONGMIN;
			
			
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nhom = lopTc.nhom/10;
			gotoXY(64 + vitri, y);
			cout << " ";
			gotoXY(64 + vitri, y);
		}
		if (key == LEFT)
		{

			vitri = demchu(lopTc.hocki);
			gotoXY(54 + vitri, y);
			goto HOCKI;
		}
		if (key == RIGHT)
		{

			
				vitri = demchu(lopTc.nsvmin);
				gotoXY(71 + vitri, y);
				goto SOLUONGMIN;
			
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return;
		}
	}
SOLUONGMIN:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		TextColor(14);
		gotoXY(71 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nhom == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap nhom", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(64, y);
			goto NHOM;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nsvmin = lopTc.nsvmin*10 + key - 48;

			cout << lopTc.nsvmin;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			 // cai nay de ngat chuoi, chuyen sang ben phai hoac trai nhap tiep
			vitri = demchu(lopTc.nsvmax);
			gotoXY(81 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nsvmin = lopTc.nsvmin/10;
			gotoXY(71 + vitri, y);
			cout << " ";
			gotoXY(71 + vitri, y);
		}
		if (key == RIGHT)
		{

			vitri = demchu(lopTc.nsvmax);
			gotoXY(81 + vitri, y);
			goto SOLUONGMAX;
		}
		if (key == LEFT)
		{

			vitri = demchu(lopTc.nhom);
			gotoXY(64 + vitri, y);
			goto NHOM;
		}
		if (key == ESC || key == F1)
		{
			return;
		}
	}
SOLUONGMAX:
	while (1)
	{
		TextColor(14);
		gotoXY(19, 13); cout << "Ki tu so : (0-9). Toi da 999 sinh vien!";
		TextColor(14);
		gotoXY(81 + vitri, y); // vi tri nhap tiep theo
		key = GetKey();
		if (lopTc.nsvmin == 0)		//Kiem tra ÅEph˙} truoc cÅEdu~ lieu chua
		{
			GhiChu("Ban chua nhap min", 35, 27, 79, 700);
			vitri = 0;
			gotoXY(71, y);
			goto SOLUONGMIN;
		}
		if ((key <= '9' && key >= '0') && (vitri < 3))
		{
			if(key == '0' && vitri == 0)continue;
			lopTc.nsvmax = lopTc.nsvmax*10 + key-48;

			cout << lopTc.nsvmax;
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			int pochinki = KiemtraBo4(DSLTC, &lopTc);
			if (-1 == pochinki) {
				check_change = true;
 // cai nay de ngat chuoi, chuyen sang ben phai hoac trai nhap tiep
				DSLTC.nodeltc[vitri_LTC]->malopTc = lopTc.malopTc;
				strcpy(DSLTC.nodeltc[vitri_LTC]->mmh, lopTc.mmh);
				strcpy(DSLTC.nodeltc[vitri_LTC]->nienkhoa, lopTc.nienkhoa);
				DSLTC.nodeltc[vitri_LTC]->hocki= lopTc.hocki;
				DSLTC.nodeltc[vitri_LTC]->nhom= lopTc.nhom;
				DSLTC.nodeltc[vitri_LTC]->nsvmin= lopTc.nsvmin;
				DSLTC.nodeltc[vitri_LTC]->nsvmax= lopTc.nsvmax;
				// delete(DSLTC.nodeltc[DSLTC.n]); // cai nay sai 
				//DSLTC.n--;
				GhiChu("Da luu vao bo nho", 40, 27, 228, 500);	TextColor(12);
				return;
			}
			if (-2 == pochinki) {
				GhiChu("Thong tin 4 field Ma mon hoc, Nien Khoa, Hoc ki, Nhom khong duoc trung", 20, 27, 79, 2000);
				continue;
			}
			
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.nsvmax = lopTc.nsvmax/10;
			gotoXY(81 + vitri, y);
			cout << " ";
			gotoXY(81 + vitri, y);
		}
		if (key == LEFT)
		{

			vitri = demchu(lopTc.nsvmin);
			gotoXY(71 + vitri, y);
			goto SOLUONGMIN;
		}
		if (key == ESC || key == F2)
		{
			//DSLTC.n--;
			return;
		}
	}
}
//Xem danh sach Lop tin chi
//sap xep tuyen tinh
void SortDSLTC(Dslop &DSLTC) {
	int i, j, temp;
	for (i = 1; i < DSLTC.n; i++) {
		for (j = DSLTC.n - 1; j >= i; j--) {
			if (DSLTC.nodeltc[j - 1]->malopTc > DSLTC.nodeltc[j]->malopTc) {
				temp = DSLTC.nodeltc[j - 1]->malopTc;
				DSLTC.nodeltc[j - 1]->malopTc = DSLTC.nodeltc[j]->malopTc;
				DSLTC.nodeltc[j]->malopTc = temp;
			}
		}
	}
}
void XemDSLTC(Dslop &DSLTC, PTRMH DSMH, int chedoxem) { // che do 1: chi xem !=1 cho phep xuli
	int key;
	int dem = 0, trang = 0, tongtrang = 0;
	bool check_change = false;	
	while (1) {
		if (0 == DSLTC.n) {
			GhiChu("Chua co danh sach lop", 35, 27, 79, 1000);
		}
		else {
			if (DSLTC.n < 15) {
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((DSLTC.n - 1) / 15 + 1);
			}
		}
		SortDSLTC(DSLTC);
		TextColor(14);	system("cls");	Khung_Xuat_LTC();  //Khung_DKLTC();
		dem = 0;
		for (int i = trang * 15; i < 15 + trang * 15 && i < DSLTC.n; i++) {

			TextColor(12); gotoXY(6, 8 + dem); cout << (i + 1);
			TextColor(14);
			gotoXY(10, 8 + dem); cout << DSLTC.nodeltc[i]->malopTc;
			gotoXY(24, 8 + dem); cout << DSLTC.nodeltc[i]->mmh;
			gotoXY(41, 8 + dem); cout << DSLTC.nodeltc[i]->nienkhoa;
			gotoXY(56, 8 + dem); cout << DSLTC.nodeltc[i]->hocki;
			gotoXY(65, 8 + dem); cout << DSLTC.nodeltc[i]->nhom;
			gotoXY(73, 8 + dem); cout << DSLTC.nodeltc[i]->nsvmin;
			gotoXY(82, 8 + dem); cout << DSLTC.nodeltc[i]->nsvmax;
			dem++;
		}
		HienThiTrang(trang + 1, tongtrang, 65, 26);
		if (chedoxem == 1) { //Dang o che do xem
			TextColor(14); gotoXY(18, 24); cout << "               DANG O CHE DO XEM!            ";
			TextColor(236); gotoXY(15, 2); cout << "              NHAN ESC DE THOAT CHE DO XEM          ";
		}
		gotoXY(73, 26);
		key = GetKey();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == F1 && chedoxem != 1)
		{
			if (FullLTC(DSLTC)) { continue; }
			gotoXY(20, 24);  TextColor(246);	cout << "F1"; //To mau` F1
			ThemLTC(DSLTC, DSMH, check_change);
		}
		if (key == F2 && chedoxem != 1)
		{
			gotoXY(36, 24);	TextColor(246);	cout << "F2"; //To mau` F2
			SuaLTC(DSLTC, DSMH, check_change);
		}
		if (key == F3 && chedoxem != 1)
		{
			gotoXY(50, 24);	TextColor(246);	cout << "F3"; //To mau` F3 
			XoaLTC(DSLTC, check_change);
		}
		if (key == ESC)
		{
			if (chedoxem == 1) { gotoXY(15, 2); TextColor(14); cout << "                                                         "; 
			return; };
			if (check_change == true)
			{
				putchar(7);	gotoXY(4, 24); TextColor(246); cout << "ESC"; //To mau` ESC
				int temp = ThongBao_ESC();
				if (temp == -1) { continue; }	//Tra ve -1 => Bat' duoc phim' ESC 1 l‚n` nua~
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileDSLTC(DSLTC);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			system("cls");
			return;
		}
		if (key == F5 && chedoxem == 1) {
			gotoXY(15, 2); TextColor(14); cout << "                                                         ";
			return;
		}
	}
}

//-----------------------DANH SACH DANG KI--------------------------------------------------------------------------------------------------------------------------

bool EmptyDK(PTRDK DSDK) {
	if (NULL == DSDK) return true;
	return false;
}

//insert first

PTRDK Search_msvdk(PTRDK DSDK, char masv[]) {
	for (PTRDK p = DSDK; p != NULL; p = p->next)
	{
		if (strcmp(p->data.mssv, masv) == 0) {
			return p;
		}
	}
	return NULL;
}


//detele svdk
void XoaDauDK(PTRDK &DSDK) {
	PTRDK p = DSDK;
	DSDK = DSDK->next;
	delete p;
}
void XoaGiuaDK(PTRDK &DSDK, char mssv[]) {
	PTRDK temp = NULL; //thang nay kieu gi cung dung truoc p
	for (PTRDK p = DSDK; p != NULL; p = p->next) {
		if (strcmp(p->data.mssv, mssv) == 0) {
			temp->next = p->next; delete p; return;
		}
		temp = p;
	}
}
void XoaCuoiDK(PTRDK &DSDK) {
	PTRDK temp = NULL; //thang nay kieu gi cung dung truoc p
	for (PTRDK p = DSDK; p != NULL; p = p->next) {
		if (p->next == NULL) {
			temp->next = p->next; delete p; return;
		}
		temp = p;
	}
}
//kiem tra xem mon do sinh vien A da dang ki chua
int Search_LTC_SV(Dslop DSLTC, char mmh[], char msv[]) {
	for (int i = 0; i < DSLTC.n; i++) {
		if (strcmp(DSLTC.nodeltc[i]->mmh, mmh) == 0) {
			for (PTRDK p = DSLTC.nodeltc[i]->DSDK; p != NULL; p = p->next) {
				if (strcmp(p->data.mssv, msv) == 0) return 1; //Ton tai sinh vien da dang ki mon hoc trong dsdk
			}
		}
		else {
			continue;
		}
	}
	return 0;
}
int Search_LTC_NK(Dslop DSLTC, int hocki, char nk[]) {
	for (int i = 0; i < DSLTC.n; i++) {
		if (DSLTC.nodeltc[i]->hocki- hocki == 0) {
			if (strcmp(DSLTC.nodeltc[i]->nienkhoa, nk) == 0)
				return 1;
		}
	}
	return 0;
}
int nhap_MSV_HK_NK(Dslop DSLTC, PTRSV ds, PTRMH DSMH, NodeDK &sv, Ltc &lopTc) {
	Khung_Nhap_MSV_HK_NK();
	int x = 34, y = 2;
	int key;
	int vitri = 0;
	int temp1; //kiem tra sinh vien
	int temp2; //kiem tra nien khoa
	PTRSV vitrisv;
	int temp_hk, temp_ltc; //kiem tra ma mon
	sv.mssv[0] = NULL;
	lopTc.nienkhoa[0] = lopTc.hocki = 0;
MSV:
	while (1) {
		TextColor(228); gotoXY(30, 3); cout << "                                      ";
		TextColor(14);
		gotoXY(34 + vitri, y);
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			sv.mssv[vitri] = char(key);
			sv.mssv[vitri] = toupper(sv.mssv[vitri]);
			cout << sv.mssv[vitri];
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(34 + vitri, y);
			cout << " ";
			gotoXY(34 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			sv.mssv[vitri] = '\0';	//Ngat chuoi~
			
				temp1 = KTSV(ds, sv.mssv); // ok co ton tai hay k
				//vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
				if (temp1 != 2) {
					vitri = demchu(lopTc.hocki);
					gotoXY(49 + vitri, y);
					goto HOCKI;
				}
			
			if (temp1 == 2) {
				GhiChu("           MA SINH VIEN KHONG TON TAI        ", 30, 4, 79, 500);
				/*gotoXY(34 + vitri, y);
				continue;*/
			}
		}
		if (key == RIGHT && vitri != 0)
		{
			sv.mssv[vitri] = '\0';	//Ngat chuoi~
			
				temp1 = KTSV(ds, sv.mssv); // ok co ton tai hay k
													   //vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
				if (temp1 != 2) {
					vitri = demchu(lopTc.hocki);
					gotoXY(49 + vitri, y);
					goto HOCKI;
				}
			
			if (temp1 == 2) {
				GhiChu("           MA SINH VIEN KHONG TON TAI        ", 30, 4, 79, 500);
				/*gotoXY(34 + vitri, y);
				continue;*/
			}
		}
		if (key == ESC) { TextColor(14);	return 0; }
	}
HOCKI:
	while (1) {
		TextColor(14);
		gotoXY(49 + vitri, y);
		key = GetKey();
		if ((key <= '9' && key >= '0') && (vitri < 1))
		{
			lopTc.hocki =key - 48;

			cout << lopTc.hocki;
			vitri++;
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			lopTc.hocki = lopTc.hocki/10;
			gotoXY(49 + vitri, y);
			cout << " ";
			gotoXY(49 + vitri, y);
		}
		if (key == ENTER && vitri != 0)
		{
			//lopTc.hocki[vitri] = '\0';	//Ngat chuoi~
			vitri = strlen(lopTc.nienkhoa);
			gotoXY(64 + vitri, y);
			goto NIENKHOA;
		}
			if (key == RIGHT && vitri != 0)
			{
				//lopTc.hocki[vitri] = '\0';	//Ngat chuoi~
				vitri = strlen(lopTc.nienkhoa);
				gotoXY(64 + vitri, y);
				goto NIENKHOA;
			}
			if (key == LEFT) {
				//lopTc.hocki[vitri] = '\0';
				vitri = strlen(sv.mssv);
				gotoXY(34 + vitri, y);
				goto MSV;
			}
			if (key == ESC) { TextColor(14);	return 0; }
		}
	NIENKHOA:
		while (1) {
			TextColor(228); gotoXY(30, 3); cout << "    =*+*+*=  ";
			TextColor(14);
			gotoXY(64 + vitri, y);
			key = GetKey();
			if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 4))
			{
				lopTc.nienkhoa[vitri] = char(key);
				lopTc.nienkhoa[vitri] = toupper(lopTc.nienkhoa[vitri]);
				cout << lopTc.nienkhoa[vitri];
				vitri++;
			}
			if (key == BACKSPACE && vitri > 0)
			{
				vitri--;
				gotoXY(64 + vitri, y);
				cout << " ";
				gotoXY(64 + vitri, y);
			}
			if (key == ENTER && vitri == 4) {
				lopTc.nienkhoa[vitri] = '\0';
				if (strcmp(lopTc.nienkhoa, "2016") > 0)
				{
					temp2 = Search_LTC_NK(DSLTC, lopTc.hocki, lopTc.nienkhoa);
					if (temp2 == 1) {
						GhiChu("             DANG NHAP THANH CONG            ", 30, 4, 79, 700);
						system("cls");
						return 1;
					}
					else {
						GhiChu("             KHONG TON TAI LOP HOC           ", 30, 4, 79, 700);
						gotoXY(64 + vitri, y);
					}
				}
				else {
					GhiChu("              NAM KHONG HOP LE               ", 30, 4, 79, 700);
					gotoXY(64 + vitri, y);
					continue;
				}
			}
			else {
				if (key == ENTER && vitri != 4) {
					GhiChu("         NIEN KHOA PHAI DAY DU 4 KI TU!      ", 30, 4, 79, 700);
					gotoXY(64 + vitri, y);
					continue;
				}
			}
			if (key == LEFT) {
				lopTc.nienkhoa[vitri] = '\0';
				vitri = demchu(lopTc.hocki);
				gotoXY(49 + vitri, y);
				goto HOCKI;
			}
			if (key == ESC) { TextColor(14);	return 0; }
		}
	}


int DemSoLopDK(Dslop DSLTC, char mmh[]) {
	int dem = 0;
	for (int i = 0; i < DSLTC.n; i++) {
		if (strcmp(DSLTC.nodeltc[i]->mmh, mmh) == 0) {
			dem++;
		}
	}
	return dem;
}
// lam them trang cho dk ltc; sua them cai them loptc;
void DANGKI_LTC(Dslop &DSLTC, PTRSV ds, PTRMH DSMH, bool check_change) {
	int key;
	int x = 34, y = 2;
	int dem, trang = 0, tongtrang = 0;
	int kiemtraESC;
	int solop; //dem so lop thoa man
	int vitrilop;
	NodeDK sv; NodeMH mh; Ltc lopTc; PTRSV duma = NULL;
	sv.mssv[0] = NULL; mh.mmh[0] = NULL; lopTc.nienkhoa[0] = NULL;
	kiemtraESC = nhap_MSV_HK_NK(DSLTC, ds, DSMH, sv, lopTc);
	if (0 == kiemtraESC) {
		return; // qua trinh dang nhap dung lai se tra ve 0l
	}
	for(int i = 0; i < DemSinhVien(ds); i++){
		duma = Search_MSV(ds, sv.mssv);
		if(duma != NULL)break;
	}
	
	TextColor(14);	system("cls");	 //Khung_DKLTC();

	gotoXY(93, 3);
	Khung_DKLTC();
	char malop[11];
	int vitri = 0;
	int quyetdinh;
	Ltc *aduma = new Ltc[MAXLTC];
MALOPTC:
	while (1)
	{
			int demtongtrang = 0;

		for (int i = 0; i < DSLTC.n; i++) 
			if (DSLTC.nodeltc[i]->hocki - lopTc.hocki == 0) 
				if (strcmp(DSLTC.nodeltc[i]->nienkhoa, lopTc.nienkhoa) == 0)aduma[demtongtrang++] = *DSLTC.nodeltc[i]; 
		if (demtongtrang < 15) {
				tongtrang = 1;
				trang = 0;
			}
			else {
				tongtrang = ((demtongtrang - 1) / 15 + 1);
			}
		TextColor(14); 	Khung_Cao_Ky();  //Khung_DKLTC();
		gotoXY(1, 0);cout<< "MSSV  : " << duma->data.mssv;
		gotoXY(1, 1);cout<< "HO TEN: " << duma->data.ho << " " <<duma->data.ten;
		gotoXY(1, 2);cout<< "PHAI  : " << duma->data.phai;
		gotoXY(1, 3);cout<< "SDT   : " << duma->data.sdt;
		dem = 0;
		for (int i = trang * 15; (i < 15 + trang * 15) && i < demtongtrang; i++) {
		
			TextColor(12); gotoXY(6, 8 + dem); cout << (i + 1);
			TextColor(14);
			gotoXY(10, 8 + dem); cout << aduma[i].malopTc;
			gotoXY(18, 8 + dem); cout << aduma[i].mmh;
			PTRMH a = Search_MH(DSMH, aduma[i].mmh);
			gotoXY(30, 8 + dem); cout << a->data.tmh;
			gotoXY(69, 8 + dem); cout << aduma[i].nhom;
			
			gotoXY(79, 8 + dem); cout << DemSVDK(aduma[i].DSDK);
			gotoXY(88, 8 + dem); cout << aduma[i].nsvmax - DemSVDK(aduma[i].DSDK);
		
			dem++;
		
		}
		HienThiTrang(trang + 1, tongtrang, 65, 26);
		
		
		
//		TextColor(14);
//		Khung_Xuat_LTC();
//		dem = 0;
//		for (int i = 0; i < DSLTC.n; i++) {
//			if (strcmp(DSLTC.nodeltc[i]->hocki, lopTc.hocki) == 0) {
//				if (strcmp(DSLTC.nodeltc[i]->nienkhoa, lopTc.nienkhoa) == 0) {
//					TextColor(12); gotoXY(6, 8 + dem); cout << (dem + 1);
//					TextColor(14);
//					gotoXY(10, 8 + dem); cout << DSLTC.nodeltc[i]->malopTc;
//					gotoXY(24, 8 + dem); cout << DSLTC.nodeltc[i]->mmh;
//					gotoXY(41, 8 + dem); cout << DSLTC.nodeltc[i]->nienkhoa;
//					gotoXY(56, 8 + dem); cout << DSLTC.nodeltc[i]->hocki;
//					gotoXY(65, 8 + dem); cout << DSLTC.nodeltc[i]->nhom;
//					gotoXY(73, 8 + dem); cout << DSLTC.nodeltc[i]->nsvmin;
//					gotoXY(83, 8 + dem); cout << DSLTC.nodeltc[i]->nsvmax;
//					dem++;
//				}
//			}
//		}
		TextColor(14);
		gotoXY(93 + vitri, 3);
		key = GetKey();
		if (( key == DOWN) && trang < tongtrang - 1) { trang++;}
		if (( key == UP) && trang > 0) { trang--; }
		if ((key >= '0' && key <= '9') && (vitri < 10))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			lopTc.malopTc = atoi(malop);
			vitrilop = Search_malopTc_hk(DSLTC, lopTc.malopTc, lopTc.hocki, DSLTC.n);
			
			if (vitrilop == -1) {
				GhiChu("MA LOP KHONG DUNG!", 93, 15, 79, 500);
				continue;
			}
			else {
				strcpy(mh.mmh, DSLTC.nodeltc[vitrilop]->mmh);
				quyetdinh = ThongBao_DK();
				if (-1 == quyetdinh) {
					TextColor(14);
					gotoXY(85, 22); cout << "                                 ";
					gotoXY(85, 23); cout << "                                 ";
					gotoXY(85, 24); cout << "                                 ";
					gotoXY(85, 25); cout << "                                 ";
					gotoXY(85, 26); cout << "                                 ";
					continue;
				}
				if (1 == quyetdinh) {
					TextColor(14);
					gotoXY(85, 22); cout << "                                 ";
					gotoXY(85, 23); cout << "                                 ";
					gotoXY(85, 24); cout << "                                 ";
					gotoXY(85, 25); cout << "                                 ";
					gotoXY(85, 26); cout << "                                 ";
					for (int j = 0; j < DSLTC.n; j++) {
						if (strcmp(DSLTC.nodeltc[j]->mmh, mh.mmh) == 0) {
							if (Search_msvdk(DSLTC.nodeltc[j]->DSDK, sv.mssv) != NULL) {
								GhiChu("SINH VIEN DA DANG KI LOP! KHONG DUOC DANG KI TIEP", 35, 15, 79, 2000);

								gotoXY(93 + vitri, 4); goto MALOPTC;  break;
							}
						}
					}
					GhiChu("DANG KI THANH CONG", 93, 15, 79, 1000);
					Insert_NodeDk(DSLTC.nodeltc[vitrilop]->DSDK, sv);
					check_change = true;
				}
				if (0 == quyetdinh) {
					TextColor(14);
					gotoXY(85, 22); cout << "                                 ";
					gotoXY(85, 23); cout << "                                 ";
					gotoXY(85, 24); cout << "                                 ";
					gotoXY(85, 25); cout << "                                 ";
					gotoXY(85, 26); cout << "                                 ";
					continue;
				}
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(93 + vitri, 3);
			cout << " ";
			gotoXY(93 + vitri, 3);
		}
		if (key == RIGHT || key == LEFT ) { continue; }
		if (key == ESC)
		{
			if (check_change == true) {
				putchar(7);	gotoXY(4, 24); TextColor(246); cout << "ESC"; //To mau` ESC
				int temp = ThongBao_ESC();
				if (temp == -1) { continue; }	//Tra ve -1 => Bat' duoc phim' ESC 1 l‚n` nua~
				if (temp == 1) {
					GhiChu("Luu Vao File Thanh Cong!", 35, 27, 79, 2000);
					GhiFileDSLTC(DSLTC); GhiFileDK(DSLTC);
				}
				if (temp == 0) { GhiChu("Luu Vao File Khong Thanh Cong!", 35, 27, 79, 2000); }
			}
			delete[] aduma;
			system("cls");
			return;
		}
	}
}
void Sort_MangSV(NodeSV a[], int n) { //Lop khong qua nhieu. Dung Selection Sort la Ok r
	NodeSV min;
	int vitrimin;
	int i, j;
	for (i = 0; i < n - 1; i++) {
		min = a[i];
		vitrimin = i;
		for (j = i + 1; j < n; j++) {
			if (strcmp(min.ten, a[j].ten) >0)
			{
				min = a[j];
				vitrimin = j;
			}
			else {
				if (strcmp(min.ten, a[j].ten) == 0)
				{
					if (strcmp(min.ho, a[j].ho) >0)
					{
						min = a[j];
						vitrimin = j;
					}
				}
			}
		}
		min = a[vitrimin];
		a[vitrimin] = a[i];
		a[i] = min;
	}
}
void XemDSDK(Dslop DSLTC, PTRSV ds, PTRMH DSMH) {
	int key;
	int x = 40, y = 2;
	int vitri = 0, vitriMang, temp;
	int STT = 1;
	bool check_change = false;
	char malop[11];
	Khung_Nhap_MaLop();
	gotoXY(x, y);
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			temp = Search_malopTc(DSLTC, atoi(malop), DSLTC.n);//atoi chuyen chuoi thanh so nguyen
			if (temp != -1)
			{
				vitriMang = temp;
				break;
			}
			else {
				GhiChu("     Ma Lop Khong Ton Tai!    ", 33, 5, 159, 500);
				gotoXY(40 + vitri, y);
				TextColor(14);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(40 + vitri, y);
			cout << " ";
			gotoXY(40 + vitri, y);
		}
		if (key == F5)
		{
			malop[vitri] = '\0';
			XemDSLTC(DSLTC, DSMH, 1);
			Khung_Nhap_MaLop();
			TextColor(223); gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
			TextColor(14);	gotoXY(40, y); cout << malop;
		}
		if (key == ESC) { TextColor(14); return; }
	}
	int trang = 0, tongtrang = 0, soluongsv = 0;
	int dem1 = 0, dem = 0;	//dem la dem dong`.  dem1 la vitri phan tu sv
	dem1 = 0;
	soluongsv = DemSVDK(DSLTC.nodeltc[vitriMang]->DSDK);
	if (soluongsv == 0)
	{
		GhiChu("Chua co du lieu sinh vien", 35, 27, 79, 500);
	}
	else {
		if (soluongsv < 15)
		{
			tongtrang = 1;
			trang = 0;
		}
		else {
			tongtrang = ((soluongsv - 1) / 15 + 1);
		}
	}
	int ktrasv;
	PTRSV svdk;
	NodeSV* SV = new NodeSV[soluongsv + 1];
	for (PTRDK p = DSLTC.nodeltc[vitriMang]->DSDK; p != NULL; p = p->next) {
		svdk = Search_MSV_DSLOP(ds, p->data.mssv);
		SV[dem1] = svdk->data;
		dem1++;
	}
	Sort_MangSV(SV, dem1);
	while (1)
	{
		TextColor(14);	system("cls");
		Khung_Xuat_SV();
		dem = 0;
		for (int i = trang * 15; i < 15 + trang * 15 && i < soluongsv; i++)
		{
			TextColor(12); gotoXY(6, 8 + dem); cout << i + 1;
			TextColor(14);
			gotoXY(10, 8 + dem); cout << SV[i].mssv;
			gotoXY(26, 8 + dem); cout << SV[i].ho;
			gotoXY(47, 8 + dem); cout << SV[i].ten;
			gotoXY(58, 8 + dem); cout << SV[i].phai;
			gotoXY(69, 8 + dem); cout << SV[i].sdt;
			dem++;
		}
		TextColor(7);
		gotoXY(1, 0); cout << "MA lOP:";
		gotoXY(1, 1); cout << "MON HOC:";
		gotoXY(1, 2); cout << "NIEN KHOA:";
		gotoXY(1, 3); cout << "HOC KI:";
		gotoXY(1, 4); cout << "NHOM:";
		TextColor(7);
		gotoXY(12, 0); cout << DSLTC.nodeltc[vitriMang]->malopTc;
		gotoXY(12, 1); cout << DSLTC.nodeltc[vitriMang]->mmh;
		gotoXY(12, 2); cout << DSLTC.nodeltc[vitriMang]->nienkhoa;
		gotoXY(12, 3); cout << DSLTC.nodeltc[vitriMang]->hocki;
		gotoXY(12, 4); cout << DSLTC.nodeltc[vitriMang]->nhom;
		HienThiTrang(trang + 1, tongtrang, 73, 26);
		gotoXY(81, 26);
		key = GetKey();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == ESC)
		{
			system("cls");	delete(SV); return;
		}
	}
}


// nhap va xem diem lop tin chi
void nhap_xem_DIEM(Dslop &DSLTC, PTRSV ds, PTRMH DSMH, int chedoxem)
{
	int key;
	int x = 40, y = 2;
	int vitri = 0, vitriMang, temp;
	int STT = 1;
	bool check_change = false;
	char malop[11];
	Khung_Nhap_MaLop();
	gotoXY(x, y);
MALOP:
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			temp = Search_malopTc(DSLTC, atoi(malop), DSLTC.n);
			if (temp != -1)
			{
				vitriMang = temp;
				break;
			}
			else {
				GhiChu("     Ma Lop Khong Ton Tai!    ", 33, 5, 159, 500);
				gotoXY(40 + vitri, y);
				TextColor(14);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(40 + vitri, y);
			cout << " ";
			gotoXY(40 + vitri, y);
		}
		if (key == F5)
		{
			malop[vitri] = '\0';
			XemDSLTC(DSLTC, DSMH, 1);
			Khung_Nhap_MaLop();
			TextColor(228); gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
			TextColor(14);	gotoXY(40, y); cout << malop;
		}
		if (key == ESC) { TextColor(14); return; }
	}
	int trang = 0, tongtrang = 0, soluongsv = 0;
	int dem1 = 0, dem2 = 0, dem = 0;	//dem la dem dong`.  dem1 la vitri phan tu sv. dem2 dem diem
										//NHAP DIEM

	dem1 = 0;
	soluongsv = DemSVDK(DSLTC.nodeltc[vitriMang]->DSDK);
	if (soluongsv == 0)
	{
		GhiChu("Chua co du lieu sinh vien", 35, 27, 79, 500);
		gotoXY(40 + vitri, y);
		goto MALOP;
	}
	else {
		if (soluongsv < 15)
		{
			tongtrang = 1;
			trang = 0;
		}
		else {
			tongtrang = ((soluongsv - 1) / 15 + 1);
		}
	}
	int ktrasv;
	NodeSV* SV = new NodeSV[soluongsv + 1]; // chua thong tin sinh vien
	NodeDK* Diem = new NodeDK[soluongsv + 1]; // chua diem cua sinh vien
	for (PTRDK p = DSLTC.nodeltc[vitriMang]->DSDK; p != NULL; p = p->next) {
		PTRSV svdk = Search_MSV_DSLOP(ds, p->data.mssv);// truy xuat den danh sach lop tim thong tin sinh vien
		SV[dem1] = svdk->data; //tim duoc thong tin chua vao mang thong tin sinh vien
		dem1++;
	}
	Sort_MangSV(SV, dem1);
	//dua du lieu diem vao danh sach sinh vien
	for (int i = 0; i < dem1; i++) {
		for (PTRDK p = DSLTC.nodeltc[vitriMang]->DSDK; p != NULL; p = p->next) {
			if (strcmp(p->data.mssv, SV[i].mssv) == 0) {
				strcpy(Diem[i].diem, p->data.diem);
			}
		}
	}
	vitri = strlen(Diem[0].diem);
	y = 8;
Reset:
	TextColor(14);	system("cls");
	if (chedoxem != 1) {
		Khung_Nhap_Diem();
		dem = 0;
		for (int i = trang * 15; i < 15 + trang * 15 && i < soluongsv; i++)
		{
			TextColor(12); gotoXY(6, 8 + dem); cout << i + 1;
			TextColor(14);
			gotoXY(10, 8 + dem); cout << SV[i].mssv;
			gotoXY(26, 8 + dem); cout << SV[i].ho;
			gotoXY(57, 8 + dem); cout << SV[i].ten;
			gotoXY(71, 8 + dem); cout << Diem[i].diem;
			dem++;
		}
		TextColor(7);
		gotoXY(1, 0); cout << "MA lOP:";
		gotoXY(1, 1); cout << "MON HOC:";
		gotoXY(1, 2); cout << "NIEN KHOA:";
		gotoXY(1, 3); cout << "HOC KI:";
		gotoXY(1, 4); cout << "NHOM:";
		TextColor(7);
		gotoXY(12, 0); cout << DSLTC.nodeltc[vitriMang]->malopTc;
		gotoXY(12, 1); cout << DSLTC.nodeltc[vitriMang]->mmh;
		gotoXY(12, 2); cout << DSLTC.nodeltc[vitriMang]->nienkhoa;
		gotoXY(12, 3); cout << DSLTC.nodeltc[vitriMang]->hocki;
		gotoXY(12, 4); cout << DSLTC.nodeltc[vitriMang]->nhom;
		HienThiTrang(trang + 1, tongtrang, 60, 26);
		while (1)
		{
			TextColor(252);				//Chu thich
			gotoXY(15, 29); cout << "                                                 ";
			gotoXY(15, 30); cout << "     DIEM SINH VIEN: Nhap tu 0.00 den 10.00.     ";
			gotoXY(15, 31); cout << "                                                 ";
			TextColor(14);
			gotoXY(71 + vitri, y);
			key = GetKey();
			if (((key <= '9' && key >= '0') || key == '.') && (vitri < 3))
			{
				Diem[dem2].diem[vitri] = char(key);
				Diem[dem2].diem[vitri] = toupper(Diem[dem2].diem[vitri]);
				cout << Diem[dem2].diem[vitri];
				vitri++;
			}
			if (key == ENTER && dem2 < dem1)// sua lai luon la thg dau tien va thg thu 3 khong cho nhap . bang cach cho thg . ra rieng mot module la dc
			{
				Diem[dem2].diem[vitri] = '\0';
				if (atoi(Diem[dem2].diem) > 10 || Diem[dem2].diem[0] == '.' || Diem[dem2].diem[2] == '.')
				{
					GhiChu("DIEM >= 0   &&   DIEM <= 10 && Khong "".5."" or ""5..""", 20, 27, 74, 500);	continue;
				}
				if (vitri > 0) { GhiChu("Save Thanh Cong!", 35, 27, 79, 300); TextColor(14); }
				dem2++;
				vitri = strlen(Diem[dem2].diem);
				if (dem2 % 15 == 0)
				{
					trang++;
					y = 8;
					goto Reset;
				}
				if (dem2 == dem1) {
					continue;
				}
				gotoXY(71 + vitri, ++y);
			}
			if (key == BACKSPACE && vitri > 0)
			{
				vitri--;
				gotoXY(71 + vitri, y);
				cout << " ";
				gotoXY(71 + vitri, y);
			}
			if ((key == RIGHT) && trang < tongtrang - 1)
			{
				Diem[dem2].diem[vitri] = '\0';
				if (atoi(Diem[dem2].diem) > 10 || Diem[dem2].diem[0] == '.' || Diem[dem2].diem[2] == '.')
				{
					GhiChu("DIEM >= 0   &&   DIEM <= 10 && Khong "".5."" or ""5..""", 20, 27, 79, 500);	continue;
				}
				trang++;
				dem2 += 15;
				if (dem2 > soluongsv) //Neu lat qua trang va vuot qua so luong sinh vien
				{
					dem2 = soluongsv - 1;
					y = dem2 % 15 + 8;
				}
				vitri = strlen(Diem[dem2].diem);
				goto Reset;
			}
			if ((key == LEFT) && trang > 0)
			{
				Diem[dem2].diem[vitri] = '\0';
				if (atoi(Diem[dem2].diem) > 10 || Diem[dem2].diem[0] == '.' || Diem[dem2].diem[2] == '.')
				{
					GhiChu("DIEM >= 0   &&   DIEM <= 10 && Khong "".5."" or ""5..""", 20, 27, 74, 500);	continue;
				}
				trang--;
				dem2 -= 15;
				vitri = strlen(Diem[dem2].diem);
				goto Reset;
			}
			if (key == UP && y > 8)
			{
				Diem[dem2].diem[vitri] = '\0';
				if (atoi(Diem[dem2].diem) > 10 || Diem[dem2].diem[0] == '.' || Diem[dem2].diem[2] == '.')
				{
					GhiChu("DIEM >= 0   &&   DIEM <= 10 && Khong "".5."" or ""5..""", 20, 27, 79, 500);	continue;
				}
				dem2--;
				vitri = strlen(Diem[dem2].diem);
				gotoXY(71 + vitri, --y);
			}
			if (key == DOWN && y < 22 && dem2 < dem1 - 1)
			{
				Diem[dem2].diem[vitri] = '\0';
				if (atoi(Diem[dem2].diem) > 10 || Diem[dem2].diem[0] == '.' || Diem[dem2].diem[2] == '.')
				{
					GhiChu("DIEM >= 0   &&   DIEM <= 10 && Khong "".5."" or ""5..""", 20, 27, 79, 500);	continue;
				}
				dem2++;
				vitri = strlen(Diem[dem2].diem);
				gotoXY(71 + vitri, ++y);
			}
			if (key == ESC)
			{
				Diem[dem2].diem[vitri] = '\0';
				putchar(7);	gotoXY(4, 24);  TextColor(251);	cout << "ESC"; //TÙ m‡u ESC
				int i = 0;
				int checkqd = ThongBao_ESC();
				if (checkqd == -1)	//TH bat duoc them 1 phim' ESC
				{
					gotoXY(4, 24);  TextColor(252);	cout << "ESC";
					TextColor(14); //TÙ m‡u ESC
					goto Reset;
				}
				if (checkqd == 1)
				{
					for (PTRDK p = DSLTC.nodeltc[vitriMang]->DSDK; p != NULL; p = p->next) {
						for (int i = 0; i < dem1; i++) {
							if (strcmp(p->data.mssv, SV[i].mssv) == 0) {
								strcpy(p->data.diem, Diem[i].diem);
							}
						}
					}
					GhiChu("Luu Vao File Thanh Cong!", 30, 27, 79, 2000);
					GhiFileDK(DSLTC); GhiFileDSLTC(DSLTC);
					delete(SV); delete(Diem); system("cls");	return;
				}
				if (checkqd == 0)
				{
					for (PTRDK p = DSLTC.nodeltc[vitriMang]->DSDK; p != NULL; p = p->next) {
						for (int i = 0; i < dem1; i++) {
							if (strcmp(p->data.mssv, SV[i].mssv) == 0) {
								strcpy(p->data.diem, Diem[i].diem);
							}
						}
					}
					GhiChu("Luu Vao File Khong Thanh Cong!", 30, 27, 79, 2000);
					delete(SV); delete(Diem); system("cls");	return;
				}
			}
		}
	}
	else {
		while (1) {
			TextColor(14);	system("cls");
			Khung_Xuat_Diem();
			dem = 0;
			for (int i = trang * 15; i < 15 + trang * 15 && i < soluongsv; i++)
			{
				TextColor(12); gotoXY(6, 8 + dem); cout << i + 1;
				TextColor(14);
				gotoXY(10, 8 + dem); cout << SV[i].mssv;
				gotoXY(26, 8 + dem); cout << SV[i].ho;
				gotoXY(57, 8 + dem); cout << SV[i].ten;
				gotoXY(71, 8 + dem); cout << Diem[i].diem;
				dem++;
			}
			TextColor(7);
			gotoXY(1, 0); cout << "MA lOP:";
			gotoXY(1, 1); cout << "MON HOC:";
			gotoXY(1, 2); cout << "NIEN KHOA:";
			gotoXY(1, 3); cout << "HOC KI:";
			gotoXY(1, 4); cout << "NHOM:";
			TextColor(7);
			gotoXY(12, 0); cout << DSLTC.nodeltc[vitriMang]->malopTc;
			gotoXY(12, 1); cout << DSLTC.nodeltc[vitriMang]->mmh;
			gotoXY(12, 2); cout << DSLTC.nodeltc[vitriMang]->nienkhoa;
			gotoXY(12, 3); cout << DSLTC.nodeltc[vitriMang]->hocki;
			gotoXY(12, 4); cout << DSLTC.nodeltc[vitriMang]->nhom;
			HienThiTrang(trang + 1, tongtrang, 60, 26);
			key = GetKey();
			if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
			if ((key == LEFT || key == UP) && trang > 0) { trang--; }
			if (key == ESC)
			{
				system("cls");	delete(SV); delete(Diem);; return;
			}
		}
	}
}




//theo so tin chi // nham lop tin chi va lop thuong
/*
void xem_DIEM_Lop(Dslop &DSLTC, ListLop ds, PTRMH DSMH)
{
	int key;
	int x = 40, y = 2;
	int vitri = 0, vitriMang, temp;
	int STT = 1;
	bool check_change = false;
	char malop[12];
	Khung_Nhap_MaLop();
	gotoXY(x, y);
Reset:
	while (1)
	{
		key = GetKey();
		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) || (key == '-') && (vitri < 11))
		{
			malop[vitri] = char(key);
			malop[vitri] = toupper(malop[vitri]);
			cout << malop[vitri];
			vitri++;
		}
		if (key == ENTER && vitri != 0)
		{
			malop[vitri] = '\0';
			temp = KTMaLop(ds, malop, ds.n);
			if (temp != -1)
			{
				vitriMang = temp;
				break;
			}
			else {
				GhiChu("     Ma Lop Khong Ton Tai!    ", 33, 5, 159, 500);
				gotoXY(40 + vitri, y);
				TextColor(14);
				continue;
			}
		}
		if (key == BACKSPACE && vitri > 0)
		{
			vitri--;
			gotoXY(40 + vitri, y);
			cout << " ";
			gotoXY(40 + vitri, y);
		}
		if (key == F5)
		{
			malop[vitri] = '\0';
			XemLop(DSLTC, ds, DSMH, 1);
			Khung_Nhap_MaLop();
			TextColor(223); gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
			TextColor(14);	gotoXY(40, y); cout << malop;
		}
		if (key == ESC) { TextColor(14); return; }
	}

	//vitriMang da luu ma lop tim thay
	//in sinh vien ra

	int trang = 0, tongtrang = 0, soluongsv = 0;
	int dem1 = 0, dem2 = 0, dem = 0;	//dem la dem dong`.  dem1 tong so phan tu. dem2 dem diem
										//NHAP DIEM

	dem1 = 0;
	soluongsv = DemSinhVien(ds.dsl[vitriMang].DSSV);
	if (soluongsv == 0)
	{
		GhiChu("Chua co du lieu sinh vien", 35, 27, 79, 500);
		gotoXY(40 + vitri, 2);
		goto Reset;
	}
	else {
		if (soluongsv < 15)
		{
			tongtrang = 1;
			trang = 0;
		}
		else {
			tongtrang = ((soluongsv - 1) / 15 + 1);
		}
	}
	int ktrasv;
	PTRSV svdk;
	NodeSV* SV = new NodeSV[soluongsv + 1]; // chua thong tin sinh vien
	for (PTRSV p = ds.dsl[vitriMang].DSSV; p != NULL; p = p->next) {
		svdk = Search_MSV_DSLOP(ds, p->data.mssv);// truy xuat den danh sach lop tim thong tin sinh vien
		SV[dem1] = svdk->data; //tim duoc thong tin chua vao mang thong tin sinh vien
		dem1++;
	}
	Sort_MangSV(SV, dem1);
	float diem[100];
	for (int i = 0; i < dem1; i++) {
		float tongdiem = 0; int tongtinchi = 0;
		for (int j = 0; j < DSLTC.n; j++) {
			for (PTRDK p = DSLTC.nodeltc[j]->DSDK; p != NULL; p = p->next) {
				if (strcmp(SV[i].mssv, p->data.mssv) == 0) {
					PTRMH temp; //cai nay de tim mon hoc roi suy ra so tin chi
					temp = Search_MH(DSMH, DSLTC.nodeltc[j]->mmh);
					tongtinchi = tongtinchi + atoi(temp->data.stclt) + atoi(temp->data.stcth);
					if (p->data.diem != NULL) {
						tongdiem = tongdiem + atof(p->data.diem)*(atoi(temp->data.stclt) + atoi(temp->data.stcth));
					}
					else {
						tongdiem = tongdiem + 0;
					}
				}
			}
		}
		diem[i] = tongdiem / tongtinchi;
	}
	//dua du lieu diem vao danh sach sinh vien
	y = 8;
	while (1) {
		TextColor(14);	system("cls");
		Khung_Xuat_Diem();
		dem = 0;
		for (int i = trang * 15; i < 15 + trang * 15 && i < soluongsv; i++)
		{
			TextColor(12); gotoXY(6, 8 + dem); cout << i + 1;
			TextColor(14);
			gotoXY(10, 8 + dem); cout << SV[i].mssv;
			gotoXY(26, 8 + dem); cout << SV[i].ho;
			gotoXY(57, 8 + dem); cout << SV[i].ten;
			if (diem[i] > 0) {
				gotoXY(71, 8 + dem); printf("%.1f", diem[i]);
			}
			else {
				gotoXY(71, 8 + dem); cout << "0";
			}
			dem++;
		}
		TextColor(7);
		gotoXY(1, 0); cout << "MA lOP:";
		TextColor(7);
		gotoXY(12, 0); cout << malop;
		HienThiTrang(trang + 1, tongtrang, 60, 26);
		gotoXY(81, 26);
		key = GetKey();
		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { trang++; }
		if ((key == LEFT || key == UP) && trang > 0) { trang--; }
		if (key == ESC)
		{
			system("cls");	delete(SV); return;
		}
	}

}
*/

//void XemDiemSinhVien(NodeSV &sv, Dslop DSLTC, PTRMH DSMH, ListLop ds, int chedo) {
//	int key;
//	int x = 40, y = 14;
//	int vitri = 0;
//	//NodeSV sv;
//	PTRSV vitrisv;
//	if (chedo == 1) {
//		sv.mssv[0] = NULL;
//		int temp1; // tim sinh vien trong dslop
//		Khung_Nhap_MaSV();
//		while (1) {
//			TextColor(14);
//			gotoXY(x + vitri, y);
//			key = GetKey();
//			if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z')) && (vitri < 10))
//			{
//				sv.mssv[vitri] = char(key);
//				sv.mssv[vitri] = toupper(sv.mssv[vitri]);
//				cout << sv.mssv[vitri];
//				vitri++;
//			}
//			if (key == BACKSPACE && vitri > 0 && vitri < 11)
//			{
//				vitri--;
//				gotoXY(x + vitri, y);
//				cout << " ";
//				gotoXY(x + vitri, y);
//			}
//			if (key == ENTER && vitri != 0)
//			{
//				sv.mssv[vitri] = '\0';	//Ngat chuoi~
//				for (int i = 0; i < ds.n; i++) {
//					temp1 = KTSV(ds.dsl[i].DSSV, sv.mssv); // ok co ton tai hay k
//					if (temp1 != 2) {
//						system("cls");
//						Khung_Xuat_DiemSV();
//						y = 8;
//						vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
//						gotoXY(1, 2); cout << "MA SV  :  " << vitrisv->data.mssv;
//						gotoXY(1, 3); cout << "TEN SV :  " << vitrisv->data.ho << " " << vitrisv->data.ten;
//						gotoXY(1, 4); cout << "PHAI   :  " << vitrisv->data.phai;
//						int STT = 0;
//						for (int i = 0; i < DSLTC.n; i++) {
//							char mmh[11];
//							for (PTRDK p = DSLTC.nodeltc[i]->DSDK; p != NULL; p = p->next) {
//								if (strcmp(sv.mssv, p->data.mssv) == 0) {
//									strcpy(mmh, DSLTC.nodeltc[i]->mmh);
//									PTRMH mh = Search_MH(DSMH, mmh);
//									TextColor(12);
//									gotoXY(6, y); cout << ++STT;
//									TextColor(14);
//									gotoXY(10, y); cout << mmh;
//									gotoXY(31, y); cout << mh->data.tmh;
//									gotoXY(80, y); cout << p->data.diem;
//									y++;
//								}
//							}
//						}
//						x = 2; y = 4; vitri = 12;  break;
//					}
//				}
//				if (temp1 == 2) {
//					GhiChu("           MA SINH VIEN KHONG TON TAI        ", 30, 4, 79, 500);
//					continue;
//					/*gotoXY(34 + vitri, y);
//					continue;*/
//				}
//			}
//			if (key == ESC) { TextColor(14); return; }
//		}
//	}
//	else {
//				system("cls");
//				Khung_Xuat_DiemSV();
//				y = 8;
//				//vitrisv = Search_MSV(ds.dsl[i].DSSV, sv.mssv); // lay vi tri
//				gotoXY(1, 2); cout << "MA SV  :  " << sv.mssv;
//				gotoXY(1, 3); cout << "TEN SV :  " << sv.ho << " " << sv.ten;
//				gotoXY(1, 4); cout << "PHAI   :  " << sv.phai;
//				int STT = 0;
//				for (int i = 0; i < DSLTC.n; i++) {
//					char mmh[11];
//					for (PTRDK p = DSLTC.nodeltc[i]->DSDK; p != NULL; p = p->next) {
//						if (strcmp(sv.mssv, p->data.mssv) == 0) {
//							strcpy(mmh, DSLTC.nodeltc[i]->mmh);
//							PTRMH mh = Search_MH(DSMH, mmh);
//							TextColor(12);
//							gotoXY(6, y); cout << ++STT;
//							TextColor(14);
//							gotoXY(10, y); cout << mmh;
//							gotoXY(31, y); cout << mh->data.tmh;
//							gotoXY(80, y); cout << p->data.diem;
//							y++;
//						}
//					}
//				}
//			}
//}

//void XemDiemCuaLop(ListLop &ds, PTRMH DSMH, Dslop &DSLTC)
//{
//	int key;
//	int x = 40, y = 2;
//	int vitri = 0, vitriMang, temp;
//	int STT = 1;
//	bool check_change = false;
//	char malop[12];
//	Khung_Nhap_MaLop();
//	gotoXY(x, y);
//Reset:
//	while (1)
//	{
//		key = GetKey();
//		if (((key >= 'A' && key <= 'Z') || (key <= '9' && key >= '0') || (key >= 'a' && key <= 'z') || (key == '-')) && (vitri < 11))
//		{
//			malop[vitri] = char(key);
//			malop[vitri] = toupper(malop[vitri]);
//			cout << malop[vitri];
//			vitri++;
//		}
//		if (key == ENTER && vitri != 0)
//		{
//			malop[vitri] = '\0';
//			temp = KTMaLop(ds, malop, ds.n); //KT trung ma lop
//			if (temp != -1)
//			{
//				vitriMang = temp;
//				break;
//			}
//			else {
//				GhiChu("     Ma Lop Khong Ton Tai!    ", 33, 5, 159, 500);
//				gotoXY(40 + vitri, y);
//				TextColor(14);
//				continue;
//			}
//		}
//		if (key == BACKSPACE && vitri > 0)
//		{
//			vitri--;
//			gotoXY(40 + vitri, y);
//			cout << " ";
//			gotoXY(40 + vitri, y);
//		}
//		if (key == F5)
//		{
//			malop[vitri] = '\0';
//			XemLop(DSLTC, ds, DSMH, 1);
//			Khung_Nhap_MaLop();
//			TextColor(223); gotoXY(18, 24); cout << "           NHAN F5 DE BAT CHUC NANG DI CHUYEN        ";
//			TextColor(14);	gotoXY(40, y); cout << malop;
//		}
//		if (key == ESC) { TextColor(14); return; }
//	}
//	int trang = 0, tongtrang = 0, soluongsv = 0;
//	int dem1 = 0, dem = 0;	//dem la dem dong`.  dem1 la vitri phan tu sv
//		dem1 = 0;
//		soluongsv = DemSinhVien(ds.dsl[vitriMang].DSSV);
//		if (soluongsv == 0)
//		{
//			GhiChu("Chua co du lieu sinh vien", 35, 27, 79, 500);
//		}
//		else {
//			trang = 0;
//			tongtrang = soluongsv;
//		}
//		SapXepSV(ds.dsl[vitriMang].DSSV); 	//Sap Xep danh sach theo Ten Ho
//		NodeSV *SV = new NodeSV[soluongsv + 1];
//		for (PTRSV p = ds.dsl[vitriMang].DSSV; p != NULL; p = p->next)
//		{
//			SV[dem1] = p->data;
//			dem1++;
//		} //DÙ? DSSV v‡o mang?
//		gotoXY(81, 26);
//		XemDiemSinhVien(SV[trang], DSLTC, DSMH, ds, 0);
//		HienThiTrang(trang + 1, tongtrang, 73, 26);
//	while (1)
//	{
//		key = GetKey();
//		if ((key == RIGHT || key == DOWN) && trang < tongtrang - 1) { 
//			trang++; 
//			XemDiemSinhVien(SV[trang], DSLTC, DSMH, ds, 0);
//			//HienThiTrang(trang + 1, tongtrang, 73, 26);
//		}
//		if ((key == LEFT || key == UP) && trang > 0) { 
//			trang--; 
//			XemDiemSinhVien(SV[trang], DSLTC, DSMH, ds, 0);
//		}
//		HienThiTrang(trang + 1, tongtrang, 73, 26);
//		if (key == ESC)
//		{
//			delete SV;
//			return;
//		}
//	}
//
//}
//===========================GIAI PHONG BO NHO===========================
void GiaiPhong_MH(PTRMH &DSMH)
{
	if (DSMH != NULL)
	{
		GiaiPhong_MH(DSMH->left);
		GiaiPhong_MH(DSMH->right);
		delete DSMH;
		DSMH = NULL;
	}
}
//void GiaiPhong(ListLop &ds, PTRMH &DSMH, Dslop &DSLTC)
//{
//	for (int i = 0; i < ds.n; i++)//Giai phong bo nho lop
//	{
//		for (PTRSV p = ds.dsl[i].DSSV; p != NULL; p = p->next)
//		{
//			delete p;
//		}
//	}
//	for (int j = DSLTC.n- 1; j >= 0; j--)//Giai phong bo nho lop tin chi
//	{
//		for (PTRDK q = DSLTC.nodeltc[j]->DSDK; q != NULL; q++) {
//			delete q;
//		}
//		delete DSLTC.nodeltc[j];
//	}
//	GiaiPhong_MH(DSMH); //Giai phong bo nho Cay Nhi Phan
//}
//----------------------------MENU----------------------------
void MenuKT(Dslop &DSLTC, PTRSV &ds, PTRMH &DSMH)
{
	int chonMenuCon;
	while (1)
	{
		system("cls");
		for (int i = 0; i < 5; i++)
		{
			if (i == 0) { TextColor(228); }
			else { TextColor(240); }
			gotoXY(0, 5 + i * 4); cout << "                        ";
			gotoXY(0, 6 + i * 4); cout << MENU[i];
			gotoXY(0, 7 + i * 4); cout << "                        ";
		}
		gotoXY(24, 7);
		int chon = MenuCha();
		switch (chon)
		{
		case 1:
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == 0) { TextColor(236); }
				else { TextColor(252); }
				gotoXY(28, 5 + (i + 1) * 4);	cout << "                                ";
				gotoXY(28, 6 + (i + 1) * 4);	cout << MENUloptc[i];
				gotoXY(28, 7 + (i + 1) * 4);	cout << "                                ";
			}
			chonMenuCon = MenuCon(4, MENUloptc);
			TextColor(14);
			system("cls");
			switch (chonMenuCon)
			{
			case 1: {	nhapDSLTC(DSLTC, DSMH);		  break;		}
			case 2: {	XemDSLTC(DSLTC, DSMH, 0); break;		}
			case 3: {   nhap_xem_DIEM(DSLTC, ds, DSMH, 1); break;  }
			case 4: {   xoa_ltc(DSLTC, DSMH); break;  }
			}break;
		}
//		case 2:
//		{
//			for (int i = 0; i < 1; i++)
//			{
//				if (i == 0) { TextColor(236); }
//				else { TextColor(252); }
//				gotoXY(28, 5 + (i + 1) * 4);	cout << "                                ";
//				gotoXY(28, 6 + (i + 1) * 4);	cout << MENUlop[i];
//				gotoXY(28, 7 + (i + 1) * 4);	cout << "                                ";
//			}
//			chonMenuCon = MenuCon(1, MENUlop);
//			TextColor(14);
//			system("cls");
//			switch (chonMenuCon)
//			{
//			//case 1: {	NhapLop(ds, DSMH); break;			}
//			//case 1: {	XemLop(DSLTC, ds, DSMH, 0); break;	}
//			//case 3: {  xem_DIEM_Lop(DSLTC, ds, DSMH); break; }
//			//case 4: {  XemDiemCuaLop(ds, DSMH, DSLTC); break; }
//			}break;
//		}
		case 2:
		{
			for (int i = 0; i < 2; i++)
			{
				if (i == 0) { TextColor(236); }
				else { TextColor(252); }
				gotoXY(28, 5 + (i + 1) * 4);	cout << "                                ";
				gotoXY(28, 6 + (i + 1) * 4);	cout << MENUsv[i];
				gotoXY(28, 7 + (i + 1) * 4);	cout << "                                ";
			}
			chonMenuCon = MenuCon(2, MENUsv);
			TextColor(14);
			system("cls");
			switch (chonMenuCon)
			{
			case 1: {	NhapSinhVien(DSLTC, ds, DSMH); break;			}
			case 2: {	XemSinhVien(ds, DSMH, DSLTC); break;			}
//			case 3: { 	
//				NodeSV sv;
//				XemDiemSinhVien(sv, DSLTC, DSMH, ds,1); break; }
			}break;
		}
		case 3:
		{
			for (int i = 0; i < 1; i++)
			{
				if (i == 0) { TextColor(236); }
				else { TextColor(252); }
				gotoXY(28, 5 + (i + 1) * 4);	cout << "                                ";
				gotoXY(28, 6 + (i + 1) * 4);	cout << MENUmonhoc[i];
				gotoXY(28, 7 + (i + 1) * 4);	cout << "                                ";
			}
			chonMenuCon = MenuCon(1, MENUmonhoc);
			TextColor(14);
			system("cls");
			switch (chonMenuCon)
			{
			case 1: { XemMonHoc(DSLTC, DSMH, 0); break; }
			}break;
		}
		case 4:
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == 0) { TextColor(236); }
				else { TextColor(252); }
				gotoXY(28, 5 + (i + 1) * 4);	cout << "                                ";
				gotoXY(28, 6 + (i + 1) * 4);	cout << MENUdangki[i];
				gotoXY(28, 7 + (i + 1) * 4);	cout << "                                ";
			}
			chonMenuCon = MenuCon(3, MENUdangki);
			TextColor(14);
			system("cls");
			switch (chonMenuCon)
			{
			case 1: { bool check_change = false; DANGKI_LTC(DSLTC, ds, DSMH, check_change); break; }
			case 2: {XemDSDK(DSLTC, ds, DSMH); break; }
			case 3: {nhap_xem_DIEM(DSLTC, ds, DSMH, 0); break; }
			}break;
		}
		case 5:
		{
			putchar(7);
			int temp = ThongBao_Thoat();
			if (temp == 1) {
				//GiaiPhong(ds, DSMH, DSLTC);
				TextColor(14);
				system("cls");
				exit(0);
			}
			TextColor(14);	break;   
		}
		}
	}
}
int main()
{
	system("color 0F");
	PTRMH DSMH = NULL;
	Dslop DSLTC;
	//ListLop ds;
	PTRSV ds = NULL;
	//InitLop(ds);
	InitLTC(DSLTC);
	DocFileDSLTC(DSLTC);
	DocFileMH(DSMH);
	//DocFileLop(ds);
	DocFileSV(ds);
	DocFileDSDK(DSLTC);
	//GiaiPhong(ds, DSMH, DSLTC);
	
//	for (int i = 0; i < DSLTC.n; i++){
//		cout << DemSVDK(DSLTC.nodeltc[i]->DSDK) << " ";
//	}
//	
	//int ans = 0;
	//cout << DSLTC.nodeltc[0]->DSDK->data.mssv;
	//	cout << ds->data.malop << endl;
	//	cout << ds->data.mssv << endl;
	//	cout << ds->data.phai;
	MenuKT(DSLTC, ds, DSMH);
	//GiaiPhong(ds, DSMH, DSLTC);
	//XemDiemSinhVien(DSLTC, DSMH, ds);
	system("pause");
	return 0;
}
