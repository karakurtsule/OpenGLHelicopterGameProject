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
char skorchar_array[25] = "Puan: 000   Kalan Hak: 3"; //Yukarýdaki skor ve kalan hak bölümü
char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; //Rakamlarýn char veri tipinde tutulduðu yer
int ustperv, yanperv = 0, harekethiz = 5, hak = 3, puan = 0; //Pervaneler ve skor ile ilgili deðiþkenler
float xhareket = 0, yhareket = 0, xucakyer = 120, yucakyer = 75;//Uçaðýn hareketini belirleyecek olan deðiþkenler
bool oyunsonu = false;//Gameover olup olmadýðýný kontrol eden deðiþken
float level = 0.0699f, zorluk = 0.0856f;//Helikopterlerin ilk hýzý ve bir sonraki turda ne kadar hýzlanacaðýný tutan deðiþkenler
std::vector<int> rastgelerenk = { 0,1,2,3 };//Rastgele renk secmek icin vector kullanip  kod icinde shuffle ediyoruz.
float renk[4][3] = { {0.20, 0.85, 0.78}, {0.0, 1.0, 0.0}, {1.0, 0.454, 0.0}, {0.8745, 1.0, 0.0 } }; //Helikopterlerimizin renkleri

class digerhelikopterler
{
public:
	float hiz = 0;
	int yon = 1;//Yön Durumlarý
	float x, y = 110;
	float renka, renkb, renkc = 0.5; //Rasgele renk 
	void basla()
	{
		/*
			Burada diðer 4 helikoptere random olarak renk atanýyor ve yön veriliyor.
			Eðer helikopter saðdan gitmeye devam ederse ve kaybolursa soldan ortaya çýkýyor.Burada if blogu çalýþýyor.
			Eðer helikopter soldan gitmeye devam ederse ve kaybolursa saðdan ortaya çýkýyor.Burada else blogu çalýþýyor

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
			Helikopterler rasgele olarak seçilen yöne doðru adým adým random renklerle çizilirler.
			Ýf bloðu çalýþtýðýnda helikopterler düz olarak çizilmiþ olur.
			Else bloðu çalýþýrsa helikopterler ayný þekilde fakat ters yönlü olarak çizilip ekrana gelir.
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
			Baþlangýçta random olarak beelirlenen helikopter hýzlarý , helikopter ekrana belirince sabit olan hýzlarda hareket ediyor.
			Ayrýca helikopterlerin ekranýn dýþýný çýkmasýný engelleyen kod satýrlarýna ihtiyaç duyuyoruz.
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
			Çarpýþmanýn gerçekleþip gerçekleþmediðinin testi burada yapýlýr.
			Uçaðýn bir noktasý helikopterlerden herhangi birinin bir noktasýna deðiyorsa bu çarpýþma olarak kabul edlilir ve true deðer döner.
			Aksi halde çarpýþma gerçekleþmediðinden false deðer döner.

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
		Burada uçaðýmýzý belirtilen alandaki koordinatlara göre gövde,füze ve kanatlarýný çiziyoruz.
	*/


	glColor3f(0.0, 0.212, 0.89);//gövdenin sol yarýsýnýn çizimi
	glBegin(GL_QUADS);
	glVertex2i(xucakyer + xhareket, yucakyer + yhareket);
	glVertex2i(xucakyer - 10 + xhareket, yucakyer - 12 + yhareket);
	glVertex2i(xucakyer - 10 + xhareket, yucakyer - 36 + yhareket);
	glVertex2i(xucakyer + xhareket, yucakyer - 44 + yhareket);
	glEnd();

	glBegin(GL_QUADS);//gövdenin sað yarýsýnýn çizimi
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(130 + xhareket, 39 + yhareket);
	glVertex2i(130 + xhareket, 63 + yhareket);
	glVertex2i(120 + xhareket, 75 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//uçaðýn sol  kanadýnýn çizimi
	glVertex2i(130 + xhareket, 51 + yhareket);
	glVertex2i(130 + xhareket, 60 + yhareket);
	glVertex2i(145 + xhareket, 49.5 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//uçaðýn sað  kanadýnýn çizimi
	glVertex2i(110 + xhareket, 51 + yhareket);
	glVertex2i(110 + xhareket, 60 + yhareket);
	glVertex2i(95 + xhareket, 49.5 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//uçaðýn kuyruðunun çizimi
	glVertex2i(105 + xhareket, 25 + yhareket);
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(113 + xhareket, 37 + yhareket);
	glEnd();

	glBegin(GL_TRIANGLES);//uçaðýn kuyruðunun çizimi
	glVertex2i(135 + xhareket, 25 + yhareket);
	glVertex2i(120 + xhareket, 31 + yhareket);
	glVertex2i(127 + xhareket, 37 + yhareket);
	glEnd();

	glLineWidth(1.5f);
	glBegin(GL_LINES);//uçaðýn füzelerinin çizimi
	glVertex2i(100 + xhareket, 52 + yhareket);
	glVertex2i(100 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//uçaðýn füzelerinin çizimi
	glVertex2i(105 + xhareket, 54 + yhareket);
	glVertex2i(105 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//uçaðýn füzelerinin çizimi
	glVertex2i(135 + xhareket, 54 + yhareket);
	glVertex2i(135 + xhareket, 60 + yhareket);
	glEnd();

	glBegin(GL_LINES);//uçaðýn füzelerinin çizimi
	glVertex2i(140 + xhareket, 52 + yhareket);
	glVertex2i(140 + xhareket, 60 + yhareket);
	glEnd();
}

void ucakorta()
/*
	Çizdiðimiz uçaðýn alt kýsýmdaki bölgede ortalanmasýný saðlar
*/
{
	xhareket = -95 + 240 - 25;
	yhareket = -25 + 120 - 25;
}

void display()
{
	/*
		Kazanýlan puanlarýn yazýlýdýðý,uçaðýmýzýn ve diðer 4 helikopterin çizilidði fonsiyon.
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
		Eðer oyun sona ermediyse çimiþ olduðumuz uçaðý klavye tuþlarý ile saða sola aþaðý ve yukarýya doðru hareket ettirebiliriz.
		Hýzýmýz : 3.25
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
		Burada renkler karýþtýrýlýp diðer 4 helikopter random olarak çiziliyor ve dizilerden aldýklarý deðerlere göre her birine bir renk atanýyor.
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
		Pervanelerle ilgili hesaplamalar yer alýyor.
		Cisimlerin ekrsn dýþýns çýkmasý sonrasý yapýlacak iþlemler yer alýyor.
		Eðer ki uçak helikopterlerin arasýndan geçip karþýya ulaþtýysa yeni bir level atlamýþ demektir ve helikopterlerin hýzý artar.
		Her karþýya geçiþte 10 puan kazanýlýr.
		Yeni seviyeye göre helikopterler tekrardan yönü ve hýzý itibariyle çizilir.
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
				Çarpýþma testi yapýlýyor.
				Eðer çarpýþma olduysa ses dosyasi varsa o ses dosyasi yoksa bip sesi veriyor.
				Can 1 azalýyor.
				Uçak eski yerine ortalanacak þekilde yerleþiyor.
				Kaç hakkýmýzýn kaldýðýný gösteren dizi deðiþiyor.
				Hak 0 a eþitlenince game over.
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
		3 hakkýmýz bittiðinde ve entera basýldýðýnda oyun tekrar baþlar .
		Skor ve can sayýlarýmýzý tutan diziler eski haline dönüyor.
		Oyun sonu false oluyor.
		Helikopterler ve uçak yeniden çiziliyor.

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
	helikopterrandom();//4 helikopter random renk ve yön ile çiziliyor.
	ucakorta();// Uçaðýmýz belirtilen konumda en ortada beliriyor.
	srand(time(0)); //Random rakamlar yaratýlýyor.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(240, 320);
	glutInitWindowSize(480, 640); //Pencere boyutu
	glutCreateWindow("17030130042 - Þule - Karakurt"); //Pencere ismi
	glutDisplayFunc(display); //Görüntü
	glClearColor(1, 1, 1, 0); //Beyaz temizleme
	gluOrtho2D(0, 480, 0, 640);
	glutSpecialFunc(tus_giris); //Klavye giriþi
	glutKeyboardFunc(tus_giris2); //Giriþ 2(Enter için)
	glutIdleFunc(hesaplama); //Sayýsal hesaplamalar
	glutMainLoop();
	return 0;
}


