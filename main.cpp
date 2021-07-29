#include <time.h>
#include <glut.h>
#include <vector>
#include<string>
#include<iostream>
#include <random>
#include <math.h>
#include <MMSystem.h>
#define PI 3.14159265

using namespace std;
char skorchar_array[25] = "Puan: 000   Kalan Hak: 3"; //Yukar�daki skor ve kalan hak b�l�m�
char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; //Rakamlar�n char veri tipinde tutuldu�u yer
int ustperv, yanperv = 0, harekethiz = 5, hak = 3, puan = 0; //Pervaneler ve skor ile ilgili de�i�kenler
float xhareket = 0, yhareket = 0, xucakyer = 120, yucakyer = 75;//U�a��n hareketini belirleyecek olan de�i�kenler
bool oyunsonu = false;//Gameover olup olmad���n� kontrol eden de�i�ken
float level = 0.0699f, zorluk = 0.0856f;//Helikopterlerin ilk h�z� ve bir sonraki turda ne kadar h�zlanaca��n� tutan de�i�kenler
std::vector<int> rastgelerenk = { 0,1,2,3 };//Rastgele renk secmek icin vector kullanip  kod icinde shuffle ediyoruz.
float renk[4][3] = { {0.20, 0.85, 0.78}, {0.0, 1.0, 0.0}, {1.0, 0.454, 0.0}, {0.8745, 1.0, 0.0 } }; //Helikopterlerimizin renkleri

class digerhelikopterler
{
public:
	float hiz = 0;
	int yon = 1;//Y�n Durumlar�
	float x, y = 110;
	float renka, renkb, renkc = 0.5; //Rasgele renk 
	void basla()
	{
		/*
			Burada di�er 4 helikoptere random olarak renk atan�yor ve y�n veriliyor.
			E�er helikopter sa�dan gitmeye devam ederse ve kaybolursa soldan ortaya ��k�yor.Burada if blogu �al���yor.
			E�er helikopter soldan gitmeye devam ederse ve kaybolursa sa�dan ortaya ��k�yor.Burada else blogu �al���yor

		*/
		hiz = rand() % (100 - 1 + 1) + 1;
		yon = rand() % 2;
		if (yon == 1)
			x = -150;
		else
		{
			x = 480 + 150;
			yon = -1;
		}
	}

	void ciz()
	{
		/*
			Helikopterler rasgele olarak se�ilen y�ne do�ru ad�m ad�m random renklerle �izilirler.
			�f blo�u �al��t���nda helikopterler d�z olarak �izilmi� olur.
			Else blo�u �al���rsa helikopterler ayn� �ekilde fakat ters y�nl� olarak �izilip ekrana gelir.
		*/

		if (yon == -1)
		{
			glColor3f(renka, renkb, renkc);
			glBegin(GL_POLYGON);//govde   
			glVertex2i(x, y - 15);
			glVertex2i(x + 5, y - 10);
			glVertex2i(x + 20, y - 10);
			glVertex2i(x + 25, y - 15);
			glVertex2i(x + 25, y - 35);
			glVertex2i(x + 20, y - 38);
			glVertex2i(x + 5, y - 38);
			glVertex2i(x, y - 35);
			glEnd();

			glBegin(GL_QUADS);//kuyruk
			glVertex2i(x + 50, y - 20);
			glVertex2i(x + 50, y - 25);
			glVertex2i(x + 25, y - 25);
			glVertex2i(x + 25, y - 20);
			glEnd();

			//ust pervane
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i(x + 13, y - 5);
			glVertex2i(x + 13, y - 10);
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(x + 13 - ustperv, y - 5);
			glVertex2i(x + 13 + ustperv, y - 5);
			glEnd();

			//yan pervane
			glBegin(GL_LINES);
			glVertex2i(x + 50 - 10 * sin(yanperv*PI / 180), y - 23 - 10 * cos(yanperv*PI / 180));
			glVertex2i(x + 50 + 10 * sin(yanperv*PI / 180), y - 23 + 10 * cos(yanperv*PI / 180));
			glEnd();
			glBegin(GL_LINES);
			glVertex2i(x + 50 - 10 * sin((yanperv + 90)*PI / 180), y - 23 - 10 * cos((yanperv + 90)*PI / 180));
			glVertex2i(x + 50 + 10 * sin((yanperv + 90)*PI / 180), y - 23 + 10 * cos((yanperv + 90)*PI / 180));
			glEnd();

			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);//Cam
			glVertex2i(x + 5, y - 15);
			glVertex2i(x + 5, y - 20);
			glVertex2i(x + 10, y - 20);
			glVertex2i(x + 10, y - 15);
			glEnd();

			glColor3f(0.1, 0.1, 0.1);
			glLineWidth(3.0);
			glBegin(GL_LINES);//Alt taraf
			glVertex2i(x, y - 45);
			glVertex2i(x + 25, y - 45);
			glEnd();

			glBegin(GL_LINES);//Alt taraf
			glVertex2i(x + 5, y - 45);
			glVertex2i(x + 5, y - 35);
			glEnd();

			glBegin(GL_LINES);//Alt taraf
			glVertex2i(x + 20, y - 45);
			glVertex2i(x + 20, y - 35);
			glEnd();

		}
		else
		{

			glColor3f(renka, renkb, renkc);
			glBegin(GL_POLYGON);
			glVertex2i(x + 50, y - 15);
			glVertex2i(x + 45, y - 10);
			glVertex2i(x + 30, y - 10);
			glVertex2i(x + 25, y - 15);
			glVertex2i(x + 25, y - 35);
			glVertex2i(x + 30, y - 38);
			glVertex2i(x + 45, y - 38);
			glVertex2i(x + 50, y - 35);
			glEnd();

			glBegin(GL_QUADS);
			glVertex2i(x + 0, y - 20);
			glVertex2i(x + 0, y - 25);
			glVertex2i(x + 25, y - 25);
			glVertex2i(x + 25, y - 20);
			glEnd();

			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
			glVertex2i(x + 50 - 13, y - 5);
			glVertex2i(x + 50 - 13, y - 10);
			glEnd();

			glBegin(GL_LINES);
			glVertex2i(x + 50 - 13 - (ustperv + 15) % 30, y - 5);
			glVertex2i(x + 50 - 13 + (ustperv + 15) % 30, y - 5);
			glEnd();

			glBegin(GL_LINES);
			glVertex2i(x - 10 * sin(yanperv*PI / 180), y - 23 - 10 * cos(yanperv*PI / 180));
			glVertex2i(x + 10 * sin(yanperv*PI / 180), y - 23 + 10 * cos(yanperv*PI / 180));
			glEnd();

			glBegin(GL_LINES);
			glVertex2i(x - 10 * sin((yanperv + 90)*PI / 180), y - 23 - 10 * cos((yanperv + 90)*PI / 180));
			glVertex2i(x + 10 * sin((yanperv + 90)*PI / 180), y - 23 + 10 * cos((yanperv + 90)*PI / 180));
			glEnd();

			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glVertex2i(x + 45, y - 15);
			glVertex2i(x + 45, y - 20);
			glVertex2i(x + 40, y - 20);
			glVertex2i(x + 40, y - 15);
			glEnd();

			glColor3f(0.1, 0.1, 0.1);
			glLineWidth(3.0);
			glBegin(GL_LINES);
			glVertex2i(x + 25, y - 45);
			glVertex2i(x + 50, y - 45);
			glEnd();

			glBegin(GL_LINES);
			glVertex2i(x + 45, y - 45);
			glVertex2i(x + 45, y - 35);
			glEnd();

			glBegin(GL_LINES);
			glVertex2i(x + 30, y - 45);
			glVertex2i(x + 30, y - 35);
			glEnd();
		}
	}

	void hareket()
	{
		/*
			Ba�lang��ta random olarak beelirlenen helikopter h�zlar� , helikopter ekrana belirince sabit olan h�zlarda hareket ediyor.
			Ayr�ca helikopterlerin ekran�n d���n� ��kmas�n� engelleyen kod sat�rlar�na ihtiya� duyuyoruz.
		*/

		if (x >= -50 && yon == 1 || yon == -1 && x <= 480 + 50)
		{
			hiz = level * 1.0f;
		}
		x = x + hiz * yon;

		if (x < -80 && yon == -1)
			yon = 1;
		if (yon == 1 && x > 480 + 50)
			yon = -1;
	}

	bool carp()
	{
		/*
			�arp��man�n ger�ekle�ip ger�ekle�medi�inin testi burada yap�l�r.
			U�a��n bir noktas� helikopterlerden herhangi birinin bir noktas�na de�iyorsa bu �arp��ma olarak kabul edlilir ve true de�er d�ner.
			Aksi halde �arp��ma ger�ekle�medi�inden false de�er d�ner.

		*/
		if (x < xhareket + 95 + 50 && x + 50 > xhareket + 95 && y < yhareket + 75 + 50 && y + 50 > yhareket + 75)
		{
			return true;
		}
		return false;
	}
};

digerhelikopterler hedef[4];
void ucakciz()
{
	/*
		Burada u�a��m�z� belirtilen alandaki koordinatlara g�re g�vde,f�ze ve kanatlar�n� �iziyoruz.
	*/


	glColor3f(0.0, 0.212, 0.89);//g�vdenin sol yar�s�n�n �izimi
	glBegin(GL_QUADS);
	glVertex2i(xucakyer + xhareket, yucakyer + yhareket);
	glVertex2i(xucakyer - 10 + xhareket, yucakyer - 12 + yhareket);
	glVertex2i(xucakyer - 10 + xhareket, yucakyer - 36 + yhareket);
	glVertex2i(xucakyer + xhareket, yucakyer - 44 + yhareket);
	glEnd();

	glBegin(GL_QUADS);//g�vdenin sa� yar�s�n�n �izimi
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(130 + xhareket, 39 + yhareket);
	glVertex2i(130 + xhareket, 63 + yhareket);
	glVertex2i(120 + xhareket, 75 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//u�a��n sol  kanad�n�n �izimi
	glVertex2i(130 + xhareket, 51 + yhareket);
	glVertex2i(130 + xhareket, 60 + yhareket);
	glVertex2i(145 + xhareket, 49.5 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//u�a��n sa�  kanad�n�n �izimi
	glVertex2i(110 + xhareket, 51 + yhareket);
	glVertex2i(110 + xhareket, 60 + yhareket);
	glVertex2i(95 + xhareket, 49.5 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//u�a��n kuyru�unun �izimi
	glVertex2i(105 + xhareket, 25 + yhareket);
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(113 + xhareket, 37 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//u�a��n kuyru�unun �izimi
	glVertex2i(135 + xhareket, 25 + yhareket);
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(127 + xhareket, 37 + yhareket);
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINES);//u�a��n f�zelerinin �izimi
	glVertex2i(100 + xhareket, 52 + yhareket);
	glVertex2i(100 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//u�a��n f�zelerinin �izimi
	glVertex2i(105 + xhareket, 54 + yhareket);
	glVertex2i(105 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//u�a��n f�zelerinin �izimi
	glVertex2i(135 + xhareket, 54 + yhareket);
	glVertex2i(135 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//u�a��n f�zelerinin �izimi
	glVertex2i(140 + xhareket, 52 + yhareket);
	glVertex2i(140 + xhareket, 60 + yhareket);
	glEnd();
}

void ucakorta()
/*
	�izdi�imiz u�a��n alt k�s�mdaki b�lgede ortalanmas�n� sa�lar
*/
{
	xhareket = -95 + 240 - 25;
	yhareket = -25 + 120 - 25;
}

void display()
{
	/*
		Kazan�lan puanlar�n yaz�l�d���,u�a��m�z�n ve di�er 4 helikopterin �izilid�i fonsiyon.
	*/


	glColor3f(1, 0.40, 0.47);
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(260, 640 - 15);
	int i = 0;
	while (i < 24)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, skorchar_array[i]);
		i++;
	}
	ucakciz();
	for (int i = 0; i < 4; i++)
	{
		hedef[i].ciz();//dusmanlar ciziliyor
	}
	glFlush();
	glutSwapBuffers();
}


void tus_giris(int key, int x, int y)
{
	/*
		E�er oyun sona ermediyse �imi� oldu�umuz u�a�� klavye tu�lar� ile sa�a sola a�a�� ve yukar�ya do�ru hareket ettirebiliriz.
		H�z�m�z : 3.25
	*/
	if (!oyunsonu)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			yhareket = yhareket + 3.25 * harekethiz;	break;
		case GLUT_KEY_DOWN:
			yhareket = yhareket - 3.25 * harekethiz;	break;
		case GLUT_KEY_LEFT:
			xhareket = xhareket - 3.25 * harekethiz;	break;
		case GLUT_KEY_RIGHT:
			xhareket = xhareket + 3.25 * harekethiz;	break;
		case GLUT_KEY_HOME:
			exit(0);	break;
		}
	}
}

void helikopterrandom()
{
	/*
		Burada renkler kar��t�r�l�p di�er 4 helikopter random olarak �iziliyor ve dizilerden ald�klar� de�erlere g�re her birine bir renk atan�yor.
	*/


	std::random_shuffle(rastgelerenk.begin(), rastgelerenk.end());//renklerin sirasi burada karistiriliyor
	int i = 0;
	while (i < 4)
	{
		hedef[i] = digerhelikopterler();
		hedef[i].basla();
		hedef[i].y = 600 - i * 75 - rand() % 20;
		int myr = rastgelerenk.at(i);
		hedef[i].renka = renk[myr][0];
		hedef[i].renkb = renk[myr][1];
		hedef[i].renkc = renk[myr][2];
		i++;
	}
}

void hesaplama()
{
	/*
		Pervanelerle ilgili hesaplamalar yer al�yor.
		Cisimlerin ekrsn d���ns ��kmas� sonras� yap�lacak i�lemler yer al�yor.
		E�er ki u�ak helikopterlerin aras�ndan ge�ip kar��ya ula�t�ysa yeni bir level atlam�� demektir ve helikopterlerin h�z� artar.
		Her kar��ya ge�i�te 10 puan kazan�l�r.
		Yeni seviyeye g�re helikopterler tekrardan y�n� ve h�z� itibariyle �izilir.
	*/

	if (!oyunsonu)
	{
		ustperv = (ustperv + 1) % 30;
		yanperv = (yanperv + 11) % 360;
		if (xhareket <= -95)
			xhareket = -95;
		if (xhareket >= -95 + 430)
			xhareket = -95 + 430;
		if (yhareket <= -25)
			yhareket = -25;
		for (int i = 0; i < 4; i++)
			hedef[i].hareket();
		if (yhareket > 620)
		{
			ucakorta();
			puan = puan + 10;
			skorchar_array[6] = digits[(puan % 1000) / 100];
			skorchar_array[7] = digits[(puan % 100) / 10];
			skorchar_array[8] = digits[(puan % 10) / 1];
			level = level + zorluk;
			helikopterrandom();
		}

		int i = 0;
		while (i < 4)
		{
			/*
				�arp��ma testi yap�l�yor.
				E�er �arp��ma olduysa ses dosyasi varsa o ses dosyasi yoksa bip sesi veriyor.
				Can 1 azal�yor.
				U�ak eski yerine ortalanacak �ekilde yerle�iyor.
				Ka� hakk�m�z�n kald���n� g�steren dizi de�i�iyor.
				Hak 0 a e�itlenince game over.
			*/

			if (hedef[i].carp())
			{
				PlaySound("C:/ucak/hit.wav", NULL, SND_ASYNC);
				ucakorta();
				hak = hak - 1;
				skorchar_array[23] = digits[hak];
				if (hak == 0)
					oyunsonu = true;
			}
			i++;
		}
	}
	glutPostRedisplay();
}
void tus_giris2(unsigned char key, int x, int y)
{
	/*
		3 hakk�m�z bitti�inde ve entera bas�ld���nda oyun tekrar ba�lar .
		Skor ve can say�lar�m�z� tutan diziler eski haline d�n�yor.
		Oyun sonu false oluyor.
		Helikopterler ve u�ak yeniden �iziliyor.

	*/


	if (key == 13 && oyunsonu)
	{
		puan = 0, level = 0.1f, hak = 3;
		skorchar_array[6] = digits[(puan % 1000) / 100];
		skorchar_array[7] = digits[(puan % 100) / 10];
		skorchar_array[8] = digits[(puan % 10) / 1];
		skorchar_array[23] = digits[(hak)];
		oyunsonu = false;
		helikopterrandom();
		ucakorta();
	}
}

int main(int argc, char **argv)
{
	helikopterrandom();//4 helikopter random renk ve y�n ile �iziliyor.
	ucakorta();// U�a��m�z belirtilen konumda en ortada beliriyor.
	srand(time(0)); //Random rakamlar yarat�l�yor.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(240, 320);
	glutInitWindowSize(480, 640); //Pencere boyutu
	glutCreateWindow("17030130042 - �ule - Karakurt"); //Pencere ismi
	glutDisplayFunc(display); //G�r�nt�
	glClearColor(1, 1, 1, 0); //Beyaz temizleme
	gluOrtho2D(0, 480, 0, 640);
	glutSpecialFunc(tus_giris); //Klavye giri�i
	glutKeyboardFunc(tus_giris2); //Giri� 2(Enter i�in)
	glutIdleFunc(hesaplama); //Say�sal hesaplamalar
	glutMainLoop();
	return 0;
}


