#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//Constantes
#define TAILLE_TABLEAU 10 //tablo büyüklüğü
#define NORMALE 10  //mayyın sayısı
#define GAGNER 1   //kazanmak
#define PERDU -1  //kaybetmek
#define CONTINUE 0   //oyuna devem etme

//Variables globales
char tab[TAILLE_TABLEAU+2][TAILLE_TABLEAU+2];    //
int soustab[TAILLE_TABLEAU+2][TAILLE_TABLEAU+2];   //
int nb_mine,y=0;
int d_count = 0;

//Foksiyonlarımız
void creer_soustableau();//alt tabloyu oluşturmyı saglar
void initialiser_tableau();//tobloyu ınızıle eder
void afficher_soustableau();//alt tbaloyu bastırmayı saglar
void afficher_tableau();//tabloyu bastırma
void placer_mines();//mayınalrı yerleştirme
int verifiermatchgagner();//kazanıp kazanmadıgını kontrol etme
void explorer(int ligne,int colonne);//mayın tarlasında ne var ne yok keşif ediyor
int creuser(int ligne,int colonne);//mayın tarlasındaki istediğim kordinantı açar




int main(void)
{
  int ligne,colonne;
    int ilerleme;

    int yeniden;
    char action;//Hangi harf
    printf("Mayin Tarlasi oyunumuza hosgeldiniz\n");
    creer_soustableau();
    initialiser_tableau();
    do
    {
        afficher_tableau();
        printf("\n");
        printf("Lutfen su formatta giriniz: c,ligne,colonne veya d,ligne,colonne veya e,ligne,colonne\n");
        scanf("%c,%d,%d",&action,&ligne,&colonne);
        printf("\n");

        if(action == 'c')
        {

            ilerleme=creuser(ligne,colonne);
        }
        else if(action == 'd')
        {
            if(nb_mine >d_count)
            {
                d_count++;
                tab[ligne][colonne]='D';
                ilerleme=verifiermatchgagner();
            }
        }
        else if(action == 'e')
        {
            if(d_count>0)
            {
                d_count--;
            }
            tab[ligne][colonne]='#';
            ilerleme=creuser(ligne,colonne);
        }


        if(ilerleme==PERDU)
        {
            printf("Arkadasim oyunu kaybettin \n");
            afficher_soustableau();
            printf("Oyunu yendiden oynamak istiyorusunuz? [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Tesekkürler Gorusuruz\n");
                return 0;
                break;
            case 1:
                d_count=0;
                ilerleme=CONTINUE;
                creer_soustableau();
                initialiser_tableau();
                break;
            default:
                printf("Yanlis bir deger girdiniz\n");
                break;
            }
        }

        if(ilerleme==GAGNER)
        {
            printf("Bravo Harika bir is cikardin\n");
            afficher_soustableau();
            printf("Oyunu yendiden oynamak istiyorusunuz? [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Tesekkürler Gorusuruz\n");
                return 0;
                break;
            case 1:
                d_count=0;
                ilerleme=CONTINUE;
                creer_soustableau();
                initialiser_tableau();
                break;
            default:
                printf("Yanlis bir deger girdiniz\n");
                break;
            }

        }

    }
    while(1);
    return 0;

}

void creer_soustableau()
{
	int i,j,nb_mine;



	for(i=0;i<=TAILLE_TABLEAU+1;i++)
	{
		for(j=0;j<=TAILLE_TABLEAU+1;j++)
		{
			soustab[i][j]= 0;
		}
	}
	for(i=0;i<=TAILLE_TABLEAU;i++)
	{
		soustab[i][0]= 1;
		soustab[i][TAILLE_TABLEAU+1]= 1;
	}
	for(j=0;j<=TAILLE_TABLEAU;j++)
	{
		soustab[0][j]= 1;
		soustab[TAILLE_TABLEAU+1][j]= 1;
	}
    nb_mine =NORMALE;
	placer_mines();

}

void initialiser_tableau()
{
	int i,j;


	for(i=0;i<=TAILLE_TABLEAU+1;i++)
	{
		for(j=0;j<=TAILLE_TABLEAU+1;j++)

			tab[i][j]= '#';
		}
	for(i=0;i<=TAILLE_TABLEAU;i++)
		{
			tab[i][0]= '*';
			tab[i][TAILLE_TABLEAU+1]= '*';
		}
	for(j=0;j<=TAILLE_TABLEAU;j++)
		{
			tab[0][j]= '*';
			tab[TAILLE_TABLEAU+1][j]= '*';
		}

}

void afficher_tableau(){
	int i,j;

	printf("\n");

	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("%3d",i);
	}
	printf("\n");


	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("---");
	}
	printf("\n");


	for(i=1;i<=TAILLE_TABLEAU;i++){
		for(j=1;j<=TAILLE_TABLEAU;j++){
			printf("%3c",tab[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}


	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("___");
	}
}

void afficher_soustableau(){
	int i,j;

	printf("\n");

	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("%3d",i);
	}
	printf("\n");


	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("---");
	}
	printf("\n");


	for(i=1;i<=TAILLE_TABLEAU;i++){
		for(j=1;j<=TAILLE_TABLEAU;j++){
			printf("%3d",soustab[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}


	for(i=1;i<=TAILLE_TABLEAU;i++){
		printf("___");
	}
	printf("\n");
}


void placer_mines()
{
	srand(time(NULL)); //Random ile mayınlarbaşka yerlere katılıyor
	int i,j,k,p,ligne,colonne;
	nb_mine = NORMALE;


		for(i=1;i<=nb_mine;i++)
		{
			ligne=1+rand()%TAILLE_TABLEAU;//Rastgele bir tamsayýnýn tablo boyuna göre kalanýný bulluyor
			colonne=1+rand()%TAILLE_TABLEAU;
			if(soustab[ligne][colonne]== -1) i--; //Burada mayýn varsa önceki adýma dön
			soustab[ligne][colonne]= -1;
                            for(k=-1;k<=1;k++){//Sol Orta Sað
                                for(p=-1;p<=1;p++){//Üst Orta Alt
                                    if(soustab[ligne][colonne]==-1){//Bombaysa
                                    if(soustab[ligne+k][colonne+p]!=-1)//Komþusu bomba deðilse
                                    {
                                    soustab[ligne+k][colonne+p]++;//Çevresindeki bomba sayýsýný 1 arttýr
                                    }
                            }
                        }
                    }

                }



        }









int verifiermatchgagner()
{
	int i,j,y=0,statut;
	for(i=1;i<=TAILLE_TABLEAU;i++)
	{
        for(j=1;j<=TAILLE_TABLEAU;j++)
        {
            if(tab[i][j]=='D')//Bayraksa say
			{
                if(soustab[i][j]==-1)
                {
                    y++;
                }
			}

        }
	}
	if(y==NORMALE) //Bayraklarýn sayýsýyla açýlmamýþlarýn
                                                                                    //sayýsýnýn toplamý bomba sayýsýna eþitse
	{
		statut=GAGNER;
	}
	else
		statut=CONTINUE;

	return statut;
}

void explorer(int ligne, int colonne) {
	int i, j;


	tab[ligne][colonne] = '0' + soustab[ligne][colonne]; //Alt tablodaki deðeri üst tabloya karakter olarak atýyoruz(açma operasyonu)
  //Tüm komþular için
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			//Sayý varsa (komþusu mayýnlýysa)ve açýk deðilse
			if (soustab[ligne + i][colonne + j] > 0 && tab[ligne + i][colonne + j] == '#')
			{
				tab[ligne + i][colonne + j] = '0'+ soustab[ligne + i][colonne + j];//Komþuyu aç
			}
			//Sayý 0 sa (komþusu mayýnsýzsa)
			else if (soustab[ligne + i][colonne + j] == 0 && tab[ligne + i][colonne + j] == '#')
			{
				explorer(ligne + i, colonne + j);//Komþuya geç ayný iþlemi tekrar  rekürsif olarak yap
			}
		}
	}
}


int creuser(int ligne, int colonne)
{
	int x=0;
    if (soustab[ligne][colonne] == -1)
    {
    	x=PERDU;//Öldün
    }

    else if (soustab[ligne][colonne] > 0)//Sayý  mý (komþusu mayýnlýysa)
    {
        tab[ligne][colonne] = ('0' + soustab[ligne][colonne]);//Aç
    //Bittimi
        x=CONTINUE;
	}
    else//Boþsa(Komþusu bossa)
    {
    	explorer(ligne, colonne); //Komþularýný açarak ilerle
    	 // Bittimi diye bak
    }

    return x;
}
