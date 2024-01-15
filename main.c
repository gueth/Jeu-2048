#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <time.h>
#define n_ligne 5//nombre de ligne du tableau
#define n_colone 5//nombre de colone du tableau
#define taille_fenetre 625//la taille de la fenetre de jeux_on a un carre
#define x_rect 50//la position en x de base des carres
#define y_rect 10// la position en y de base des carres
#define cote_rect 99//le cote des carres
#define espace 10//l'espace entre les carres
#define pour_cent 100//la taille des case en pourcentage
#define taille_x_score 150//la taille suivant x de la fenetre de score du jeux
#define taille_y_score 40//la taille suivant y de la fenetre de score du jeux
#define r_score 255//couleur du carre des score(blanc)
#define v_score 255
#define b_score 255
#define espace_nbr 7//l'espace entre les nombres du score


//police d'ecriture Bernard MT


//********************************************************************************************************************************************************
//verifi si le tableau possede 2048
//********************************************************************************************************************************************************
int verif_2048(int tab[n_ligne][n_colone])
{
    int ind_l=0,ind_c=0;// indice ligne et indice colone
   int compteur=0;
   for(ind_l=0;ind_l<n_ligne;ind_l++)for(ind_c=0;ind_c<n_colone;ind_c++)if(tab[ind_l][ind_c]>=2048)compteur=1;
    if(compteur==1)return(1);
    return(0);
}//fin verif_2048


//********************************************************************************************************************************************************
//verifi si le tableau est plein
//********************************************************************************************************************************************************
int verif_plein(int tab[n_ligne][n_colone])
{
    int ind_l=0,ind_c=0;// indice ligne et indice colone
    int compteur=0;
    for(ind_l=0;ind_l<n_ligne;ind_l++)for(ind_c=0;ind_c<n_colone;ind_c++)if(tab[ind_l][ind_c]!=0)compteur++;
    if(compteur==25)return(1);
    return(0);
}//fin verif


//********************************************************************************************************************************************************
//permutation de deux chiffres
//********************************************************************************************************************************************************
void permutation(int *nb1,int *nb2)
{
   int inter;//variable intermediaire
   inter=*nb1;
   *nb1=*nb2;
   *nb2=inter;
}//fin permutation

//********************************************************************************************************************************************************
//somme deux meme chiffre de la meme ligne vers la droite
//********************************************************************************************************************************************************
int somme_droit(int ajout_score,int tab[n_ligne][n_colone],int i,int cont)
{
    tab[i-1][cont+1]=tab[i-1][cont+1]+tab[i-1][cont];
    ajout_score=tab[i-1][cont];
    tab[i-1][cont]=0;
    return(ajout_score);
}//fin somme droite


//********************************************************************************************************************************************************
//somme deux meme chiffre de la meme ligne vers la gauche
//********************************************************************************************************************************************************
int somme_gauche(int ajout_score,int tab[n_ligne][n_colone],int i,int cont)
{
    tab[i][cont-1]=tab[i][cont-1]+tab[i][cont];
    ajout_score=ajout_score+tab[i][cont];
    tab[i][cont]=0;
    return(ajout_score);
}//fin somme gauche

//********************************************************************************************************************************************************
//somme deux meme chiffre de la meme ligne vers le haut
//********************************************************************************************************************************************************
int somme_haut(int ajout_score,int tab[n_ligne][n_colone],int j,int cont)
{
    tab[cont-1][j]=tab[cont-1][j]+tab[cont][j];
    ajout_score=ajout_score+tab[cont][j];
    tab[cont][j]=0;
    return(ajout_score);
}//fin somme haut

//********************************************************************************************************************************************************
//somme deux meme chiffre de la meme ligne vers le bas
//********************************************************************************************************************************************************
int somme_bas(int ajout_score,int tab[n_ligne][n_colone],int j,int cont){
    tab[cont+1][j-1]=tab[cont+1][j-1]+tab[cont][j-1];
    ajout_score=ajout_score+tab[cont][j-1];
    tab[cont][j-1]=0;
    return(ajout_score);
}//fin somme bas

//********************************************************************************************************************************************************
//affiche le tableau de chiffre
//********************************************************************************************************************************************************
void affiche_tableau(int tab[n_ligne][n_colone])
{
    int ind_l=0,ind_c=0;// indice ligne et indice colone
    printf(" tableau \n");
    for(ind_l=0;ind_l<n_ligne;ind_l++)
    {
        for(ind_c=0;ind_c<5;ind_c++)printf("%3d ",tab[ind_l][ind_c]);
        printf("\n");
    }
}//fin de l'affichage du tablaeu

//********************************************************************************************************************************************************
//retourne vrai si le joueur a gagne et faux sinon c'est aussi la fontion qui permet d'arreter le jeux
//********************************************************************************************************************************************************
bool victoire(int tab[n_ligne][n_colone])
{
    if(verif_2048(tab)==1)return(true);
    return(false);
}//fin de la fonction victoire

//********************************************************************************************************************************************************
//retourne vrai si le joueur a perdu et faux sinon il s'agit egalement de la fonction qui arrte le juex
//********************************************************************************************************************************************************
bool defaite(int tab[n_ligne][n_colone])
{
	int l=0;
    int i=0,j=0;// indice ligne et indice colone
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if(i+1<5)
			{
				if(tab[i][j]==tab[i+1][j])
				{
					l++;
				}
			}
		}
	}

	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			if(j+1<5)
			{
				if(tab[i][j]==tab[i][j+1])
				{
					l++;
				}
			}
		}
	}
	if(verif_plein(tab)==1&&l==0&&verif_2048(tab)==0)return(true);
	return(false);
}


//********************************************************************************************************************************************************
//retourne vrai si le jeux doit s'arreter et faux sinon il s'agit de la fonction qui arrte le juex
//********************************************************************************************************************************************************
bool fin(int score,int tab[n_ligne][n_colone],bool *possible)
{
   if(victoire(tab)==true&&defaite(tab)==false)return(true);
   if(victoire(tab)==false&&defaite(tab)==true)return(true);
   return(false);
}//fin de la fonction defaite


//********************************************************************************************************************************************************
//donne le nombre de chiffre qui condtitue un nombre ex: 123 a 3 chiffre
//********************************************************************************************************************************************************
int nbr_nbr(int nbr)
{
    int div=1,compt=0;//l'element de comparaison a incrementer et le compteur
    if(nbr==0)return(0);//on retourne 0 si le nombre est 0
    do
    {
        compt++;
        div=div*10;
    }while(nbr>=div);
    return(compt);
}//fin de la fonction nbr_nbr

//********************************************************************************************************************************************************
//calcule les puissance-1 de 1à ex: 10 puis 0 c'est O et ici 10 pui 1 c'est 1 et 10 pui 2 c'est 10 etc
//********************************************************************************************************************************************************
int puiss_10(int n)
{
    int p_10=1,compteur=1;
    if(n==0)return(0);//0 puissance 0 c'est 1 ici
    while(compteur<n)
    {
        compteur++;
        p_10=p_10*10;
    }
    return(p_10);
}//fin de puiss_10

//********************************************************************************************************************************************************
//range les chiffre qui forme le score dans un tableau aligne dans l'odrre d'indice croissant de sorte que le chiffre des unites soit le dernier
//********************************************************************************************************************************************************
void generate_score(int score,int tab[n_ligne])
{
    int faux_score=score,n;//la valeur du score sur la quelle on va effecuer les calcule,le nombre de chiffre du faux_score
    int ind_l;//indice de la ligne du tableau
    printf("nombre de chiffre du score =%d \n",nbr_nbr(score));
    if(nbr_nbr(score)==0)
    {
        tab[0]=0;
        n=nbr_nbr(score)+1;
            if(n<n_ligne)for(ind_l=n;ind_l<n_ligne;ind_l++)tab[ind_l]=-1;//on attribut au reste des cases inutiliser la vealur -1
    }
    else
    {
        for(ind_l=0;ind_l<nbr_nbr(score);ind_l++)
        {//on parcourt le nombre de case du tableau correspondant au nombre le chifrre du score
            if(puiss_10(nbr_nbr(faux_score))==0)
            {//si le chiffre est 0
                        tab[ind_l]=0;
            }
            else
            {
                tab[ind_l]=faux_score/puiss_10(nbr_nbr(faux_score));
                n=nbr_nbr(faux_score);
                faux_score=faux_score%puiss_10(nbr_nbr(faux_score));
                        if(nbr_nbr(faux_score)!=n-1){//si il y a un 0 entre deux nombre
                            ind_l++;
                            tab[ind_l]=0;
                        }
                    }
        }
                if(nbr_nbr(score)<n_ligne)for(ind_l=nbr_nbr(score);ind_l<n_ligne;ind_l++)tab[ind_l]=-1;//on attribut au reste des cases inutiliser la vealur -1

            }
            printf("//-1 pour case du tableau inocupees \n");

}//fin de generate_score

//********************************************************************************************************************************************************
//creer l'interface du score qui apparait a l'ecran
//********************************************************************************************************************************************************
void interface_score(SDL_Renderer *rendu,int score){
    int tab_score[n_ligne];//le tableau ou seront ranger les chiffres qui forme le score
    int i=0;// indice ligne


    //genere l'image ou est ecrit le mot score
    SDL_Surface* surfscore;
    surfscore = SDL_LoadBMP("score.bmp");
    SDL_Texture* textscore= SDL_CreateTextureFromSurface(rendu, surfscore);
    SDL_FreeSurface(surfscore);
    SDL_Rect dstscore= { (taille_fenetre/2)-(taille_x_score),y_rect+((espace+cote_rect)*5)+espace,taille_x_score,taille_y_score};
    SDL_RenderCopy(rendu, textscore, NULL, &dstscore);
    //genere le rectangle ou on ecrit le score
    SDL_Rect rect_score ={(taille_fenetre/2),y_rect+((espace+cote_rect)*5)+espace,taille_x_score,taille_y_score}; // x, y, largeur, hauteur
    SDL_SetRenderDrawColor(rendu, r_score, v_score, b_score, 255);// Changer la couleur de dessin (
    SDL_RenderFillRect(rendu, &rect_score); // Dessiner un rectangle plein

    //genere et renge dans tab_score les chiffres qui forme le score
    generate_score(score,tab_score);


//initialisation des textures et surfaces des 10 ciffres
            SDL_Surface* surfn0;
            SDL_Texture* textn0;
            SDL_Surface* surfn1;
            SDL_Texture* textn1;
            SDL_Surface* surfn2;
            SDL_Texture* textn2;
            SDL_Texture* textn3;
            SDL_Surface* surfn3;
            SDL_Texture* textn4;
            SDL_Surface* surfn4;
            SDL_Texture* textn5;
            SDL_Surface* surfn5;
            SDL_Texture* textn6;
            SDL_Surface* surfn6;
            SDL_Texture* textn7;
            SDL_Surface* surfn7;
            SDL_Texture* textn8;
            SDL_Surface* surfn8;
            SDL_Texture* textn9;
            SDL_Surface* surfn9;


            for(i=0;i<n_ligne;i++)switch(tab_score[i]){//affiche la score
                                case 0:
                                    surfn0 = SDL_LoadBMP("score0.bmp");
                     textn0= SDL_CreateTextureFromSurface(rendu, surfn0);
                    SDL_FreeSurface(surfn0);
                    SDL_Rect dstn0 = { (taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                    SDL_RenderCopy(rendu, textn0, NULL, &dstn0);

                                    break;
                                    case 1:
                     surfn1 = SDL_LoadBMP("score1.bmp");
                     textn1= SDL_CreateTextureFromSurface(rendu, surfn1);
                    SDL_FreeSurface(surfn1);
                    SDL_Rect dstn1 = {(taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                    SDL_RenderCopy(rendu, textn1, NULL, &dstn1);
                                    break;
                                    case 2:
                    surfn2 = SDL_LoadBMP("score2.bmp");
                     textn2= SDL_CreateTextureFromSurface(rendu, surfn2);
                    SDL_FreeSurface(surfn2);
                    SDL_Rect dstn2 = { (taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn2, NULL, &dstn2);
                                    break;
                                    case 3:
                                        surfn3 = SDL_LoadBMP("score3.bmp");
                     textn3= SDL_CreateTextureFromSurface(rendu, surfn3);
                    SDL_FreeSurface(surfn3);
                    SDL_Rect dstn3 = {(taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn3, NULL, &dstn3);
                                    break;
                                    case 4:
                                         surfn4 = SDL_LoadBMP("score4.bmp");
                     textn4= SDL_CreateTextureFromSurface(rendu, surfn4);
                    SDL_FreeSurface(surfn4);
                    SDL_Rect dstn4 = {(taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                    SDL_RenderCopy(rendu, textn4, NULL, &dstn4);
                                    break;
                                    case 5:
                                         surfn5 = SDL_LoadBMP("score5.bmp");
                     textn5= SDL_CreateTextureFromSurface(rendu, surfn5);
                    SDL_FreeSurface(surfn5);
                    SDL_Rect dstn5 = { (taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn5, NULL, &dstn5);
                                    break;
                                    case 6:
                                         surfn6 = SDL_LoadBMP("score6.bmp");
                     textn6= SDL_CreateTextureFromSurface(rendu, surfn6);
                    SDL_FreeSurface(surfn6);
                    SDL_Rect dstn6 = {(taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                    SDL_RenderCopy(rendu, textn6, NULL, &dstn6);
                                    break;
                                    case 7:
                                         surfn7 = SDL_LoadBMP("score7.bmp");
                     textn7= SDL_CreateTextureFromSurface(rendu, surfn7);
                    SDL_FreeSurface(surfn7);
                    SDL_Rect dstn7 = {(taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn7, NULL, &dstn7);
                                    break;
                                    case 8:
                                         surfn8 = SDL_LoadBMP("score8.bmp");
                     textn8= SDL_CreateTextureFromSurface(rendu, surfn8);
                    SDL_FreeSurface(surfn8);
                    SDL_Rect dstn8 = { (taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn8, NULL, &dstn8);
                                    break;

                                    case 9:
                                         surfn9 = SDL_LoadBMP("score9.bmp");
                     textn9= SDL_CreateTextureFromSurface(rendu, surfn9);
                    SDL_FreeSurface(surfn9);
                    SDL_Rect dstn9 = { (taille_fenetre/2)+i*((taille_x_score/5)+espace_nbr),y_rect+((espace+cote_rect)*5)+espace,(taille_x_score)/5,taille_y_score};
                   SDL_RenderCopy(rendu, textn9, NULL, &dstn9);
                                    break;

                                }//fin des cas de chiffre pouvant etre utiliser ainsi que leur affichage
                                // Mettre à jour le rendu
                                SDL_RenderPresent(rendu);
}//fin de la fontion qui affiche le score


//********************************************************************************************************************************************************
//positionne deux aleatoirement dans le tableau sur une case ayant 0
//********************************************************************************************************************************************************
void deux_aleatoire(int tab[n_ligne][n_colone]){
    int ind_l,ind_c;// indice des ligne et colone de lq position du deux
    srand(time(NULL));
    do{
        ind_l=rand()%(n_ligne);
        ind_c=rand()%(n_colone);

    }while(tab[ind_l][ind_c]!=0&&verif_plein(tab)==0);
    if(tab[ind_l][ind_c]==0)tab[ind_l][ind_c]=2;
     printf("position 2 aleatoire = tab[%d][%d]\n",ind_l,ind_c);
}//fin de la fonction deux_aleatoire


//********************************************************************************************************************************************************
//affiche les images des nombres qui apparaissent a l'ecran lors du jeux en fonction des valeurs du tableau
//********************************************************************************************************************************************************
void place_nbr(SDL_Renderer *rendu,int tab[n_ligne][n_colone],int n_tour){


      int i=0,j=0;//indice ligne et colone de la matrice
            //initialisation des surfaces et textures des images de nombres du jeux
            SDL_Surface* surf0;
            SDL_Texture* text0;
            SDL_Surface* surf2;
            SDL_Texture* text2;
            SDL_Surface* surf4;
            SDL_Texture* text4;
            SDL_Surface* surf8;
            SDL_Texture* text8;
            SDL_Surface* surf16;
            SDL_Texture* text16;
            SDL_Surface* surf32;
            SDL_Texture* text32;
            SDL_Surface* surf64;
            SDL_Texture* text64;
            SDL_Surface* surf128;
            SDL_Texture* text128;
            SDL_Surface* surf256;
            SDL_Texture* text256;
            SDL_Surface* surf512;
            SDL_Texture* text512;
            SDL_Surface* surf1024;
            SDL_Texture* text1024;
            SDL_Surface* surf2048;
            SDL_Texture* text2048;


      for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++){//parcour chaque valeur de la matrice et affiche l'image qui correspond a sa valeur dans le tableau
                                switch(tab[i][j]){
                                case 0:
                                    surf0 = SDL_LoadBMP("0.bmp");
                     text0= SDL_CreateTextureFromSurface(rendu, surf0);
                    SDL_FreeSurface(surf0);
                    SDL_Rect dst0 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text0, NULL, &dst0);

                                    break;
                                    case 2:
                     surf2 = SDL_LoadBMP("2.bmp");
                     text2= SDL_CreateTextureFromSurface(rendu, surf2);
                    SDL_FreeSurface(surf2);
                    SDL_Rect dst2 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text2, NULL, &dst2);
                                    break;
                                    case 4:
                                        surf4 = SDL_LoadBMP("4.bmp");
                     text4= SDL_CreateTextureFromSurface(rendu, surf4);
                    SDL_FreeSurface(surf4);
                    SDL_Rect dst4 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text4, NULL, &dst4);
                                    break;
                                    case 8:
                                        surf8 = SDL_LoadBMP("8.bmp");
                     text8= SDL_CreateTextureFromSurface(rendu, surf8);
                    SDL_FreeSurface(surf8);
                    SDL_Rect dst8 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text8, NULL, &dst8);
                                    break;
                                    case 16:
                                         surf16 = SDL_LoadBMP("16.bmp");
                     text16= SDL_CreateTextureFromSurface(rendu, surf16);
                    SDL_FreeSurface(surf16);
                    SDL_Rect dst16 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text16, NULL, &dst16);
                                    break;
                                    case 32:
                                         surf32 = SDL_LoadBMP("32.bmp");
                     text32= SDL_CreateTextureFromSurface(rendu, surf32);
                    SDL_FreeSurface(surf32);
                    SDL_Rect dst32 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text32, NULL, &dst32);
                                    break;
                                    case 64:
                                         surf64 = SDL_LoadBMP("64.bmp");
                     text64= SDL_CreateTextureFromSurface(rendu, surf64);
                    SDL_FreeSurface(surf64);
                    SDL_Rect dst64 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text64, NULL, &dst64);
                                    break;
                                    case 128:
                                         surf128 = SDL_LoadBMP("128.bmp");
                     text128= SDL_CreateTextureFromSurface(rendu, surf128);
                    SDL_FreeSurface(surf128);
                    SDL_Rect dst128 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text128, NULL, &dst128);
                                    break;
                                    case 256:
                                         surf256 = SDL_LoadBMP("256.bmp");
                     text256= SDL_CreateTextureFromSurface(rendu, surf256);
                    SDL_FreeSurface(surf256);
                    SDL_Rect dst256 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text256, NULL, &dst256);
                                    break;
                                    case 512:
                                         surf512 = SDL_LoadBMP("512.bmp");
                     text512= SDL_CreateTextureFromSurface(rendu, surf512);
                    SDL_FreeSurface(surf512);
                    SDL_Rect dst512 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text512, NULL, &dst512);
                                    break;


                                    case 1024:
                                         surf1024 = SDL_LoadBMP("1024.bmp");
                     text1024= SDL_CreateTextureFromSurface(rendu, surf1024);
                    SDL_FreeSurface(surf1024);
                    SDL_Rect dst1024 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text1024, NULL, &dst1024);
                                    break;
                                    case 2048:
                                         surf2048 = SDL_LoadBMP("2048.bmp");
                     text2048= SDL_CreateTextureFromSurface(rendu, surf2048);
                    SDL_FreeSurface(surf2048);
                    SDL_Rect dst2048 = { j*espace+x_rect+j*cote_rect,i*espace+y_rect+i*cote_rect, (pour_cent*cote_rect)/100,(pour_cent*cote_rect)/100};
                    SDL_RenderCopy(rendu, text2048, NULL, &dst2048);
                                    break;
                                }
                                }//fin du parcourt de la matrice
}//fin de place_nbr

//********************************************************************************************************************************************************
// deplace chaque nombre vers la droite case par case par ligne en commencant par la case d'indice 4,4
//********************************************************************************************************************************************************
int deplacement_droite(int tab[n_ligne][n_colone],bool *possible,int tab_poss[n_ligne][n_colone]){
    int i,j;//valeaur des compteurs ligne, colone
    int cont;//compteur interne a une ligne
    int ajout_score=0;

    for(i=n_ligne;i>=1;i--)for(j=n_colone;j>=1;j--){
            if(tab[i-1][j-1]!=0){// si la case n'est pas egale a 0
                        cont=j-1;// initialisation du compteur a l'indice colone de la case
                          do{
                                if(cont+1<n_colone){//si la case de droite existe
                                    if(tab[i-1][cont+1]==0){//si la case de droite est egale a 0
                                        permutation(&tab[i-1][cont+1],&tab[i-1][cont]);
                                        cont++;
                                        *possible=true;
                                    }else{
                                        if(tab[i-1][cont+1]==tab[i-1][cont]&&tab_poss[i-1][cont+1]==0){//si la case de droite est egale au nombre de la case et qu'on a pas encore additionner ces cases
                                            ajout_score=ajout_score+somme_droit(ajout_score,tab,i,cont);
                                            *possible=true;
                                            tab_poss[i-1][cont+1]=1;
                                            }
                                            cont=n_colone-1;//stop la boucle de deplacement
                                    }
                                }
                            }while(cont+1<n_colone);//fin boucle de deplacment

            }
                }
        for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++)tab_poss[i][j]=0;
        return(2*ajout_score);
    }//fin de deplacement a droite

//********************************************************************************************************************************************************
// deplace chaque nombre vers la gauche case par case selon la ligne en commencant par la case d'indice 0,0
//********************************************************************************************************************************************************
int deplacement_gauche(int tab[n_ligne][n_colone],bool *possible,int tab_poss[n_ligne][n_colone]){
    int i,j;//valeaur dex compteur ligne colone
    int cont;//compteur interne a une ligne
    int ajout_score=0;

    for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++){
        if(tab[i][j]!=0){// si la case n'est pas egale a 0
                    cont=j;// initialisation du compteur a l'indice colone de la case
                      do{
                            if(cont-1>=0){//si la case de gauche existe
                                if(tab[i][cont-1]==0){//si la case de gauche est egale a 0
                                    permutation(&tab[i][cont-1],&tab[i][cont]);
                                    cont--;
                                    *possible=true;
                                }else{
                                    if(tab[i][cont-1]==tab[i][cont]&&tab_poss[i][cont-1]==0){//si la case de gauche est egale au nombre de la case
                                        ajout_score=ajout_score+somme_gauche(ajout_score,tab,i,cont);
                                        *possible=true;
                                        tab_poss[i][cont-1]=1;
                                        }
                                        cont=0;//stop la boucle de deplacement
                                }
                            }
                        }while(cont-1>=0);//fin boucle de deplacment

        }
        }
        for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++)tab_poss[i][j]=0;
        return(2*ajout_score);
    }//fin de deplacement a gauche


//********************************************************************************************************************************************************
// deplace chaque nombre vers le haut case par case selon la colone en commencant par la case d'indice 0,0
//********************************************************************************************************************************************************
int deplacement_haut(int tab[n_ligne][n_colone],bool *possible,int tab_poss[n_ligne][n_colone]){
    int i,j;//valeaur dex compteur ligne colone
    int cont;//compteur interne a une ligne
    int ajout_score=0;

    for(j=0;j<n_colone;j++){
               for(i=0;i<n_ligne;i++){
        if(tab[i][j]!=0){// si la case n'est pas egale a 0
                    cont=i;// initialisation du compteur a l'indice ligne de la case
                      do{
                            if(cont-1>=0){//si la case du haut existe
                                if(tab[cont-1][j]==0){//si la case de gauche est egale a 0
                                    permutation(&tab[cont-1][j],&tab[cont][j]);
                                    cont--;
                                    *possible=true;
                                }else{
                                    if(tab[cont-1][j]==tab[cont][j]&&tab_poss[cont-1][j]==0){//si la case du haut est egale au nombre de la case
                                        ajout_score=ajout_score+somme_haut(ajout_score,tab,j,cont);
                                        *possible=true;
                                        tab_poss[cont-1][j]==1;
                                        }
                                        cont=0;//stop la boucle de deplacement
                                }
                            }
                        }while(cont-1>=0);//fin boucle de deplacment haut

        }
        }

}
        for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++)tab_poss[i][j]=0;
        return(2*ajout_score);
    }//fin de deplacement a haut


//********************************************************************************************************************************************************
// deplace chaque nombre vers le bas case par case selon la colone en commencant par la case d'indice 4,4
//********************************************************************************************************************************************************
int deplacement_bas(int tab[n_ligne][n_colone],bool *possible,int tab_poss[n_ligne][n_colone]){
    int i,j;//valeaur dex compteur ligne colone
    int cont;//compteur interne a une ligne
    int ajout_score=0;


    for(j=n_colone;j>=1;j--)for(i=n_ligne;i>=1;i--){
        if(tab[i-1][j-1]!=0){// si la case n'est pas egale a 0
                    cont=i-1;// initialisation du compteur a l'indice ligne de la case
                      do{
                            if(cont+1<n_colone){//si la case du bas existe
                                if(tab[cont+1][j-1]==0){//si la case du bas est egale a 0
                                    permutation(&tab[cont+1][j-1],&tab[cont][j-1]);
                                    cont++;
                                    *possible=true;
                                }else{
                                    if(tab[cont+1][j-1]==tab[cont][j-1]&&tab_poss[cont+1][j-1]==0){//si la case de droite est egale au nombre de la case
                                        ajout_score=ajout_score+somme_bas(ajout_score,tab,j,cont);
                                        *possible=true;
                                        tab_poss[cont+1][j-1]=1;

                                        }
                                        cont=n_colone-1;//stop la boucle de deplacement
                                }
                            }
                        }while(cont+1<n_colone);//fin boucle de deplacment

        }
        }

        for(i=0;i<n_ligne;i++)for(j=0;j<n_colone;j++)tab_poss[i][j]=0;
        return(2*ajout_score);
    }//fin de deplacement bas







//********************************************************************************************************************************************************
// le programme main
//********************************************************************************************************************************************************
int main(int Argc, char *argv[])
{

//********************************************************************************************************************************************************
// l'initialisation de la SDL, de la fenetren du rendu
//********************************************************************************************************************************************************

    //intialiser SDL2
    //Si la SDL ne s'initialise pas  bien
    if(0!=SDL_Init(SDL_INIT_TIMER|SDL_INIT_EVENTS|SDL_INIT_AUDIO|SDL_INIT_VIDEO))
    {
            //affiche l'erreur d'initalisation, GetError recupere l'erreur en chaine de caractere
        fprintf(stdout,"erreur SDL initalisation: %s",SDL_GetError());
        SDL_Quit();
    }

     //Si la SDL s'initialise bien

     //creation de la ferentre de jeux
     SDL_Window *fenetre=NULL;//on cree un pointeur de type fenetre qu'on initialise a null en cas d'erreur
     fenetre=SDL_CreateWindow("Jeux 2048 INGE II",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,taille_fenetre,taille_fenetre,SDL_WINDOW_SHOWN);//on cree une fenetre au milieux et plein ecran a partir du pointeur

     //gestion des erreurs de fenetre
     if(NULL==fenetre){
        fprintf(stdout,"erreur initalisation fenetre: %s",SDL_GetError());
        SDL_Quit();
     }

     //fenetre initielisee

     //creer un rendu associe a la fenetre cree
     SDL_Renderer *rendu=NULL;
     rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);// rendu associe a la fenetre et effectuee par le CUP; -1 permet de directement affecter la vealur qui corresprnd au rendu

     //gestion des erreurs de fenetre
     if(NULL==rendu){
        fprintf(stdout,"erreur creation rendu: %s",SDL_GetError());
        SDL_Quit();
     }
     //rendu bien cree

//********************************************************************************************************************************************************
// debut des programmes du jeux
//********************************************************************************************************************************************************

//le plateau s'affiche grace a place_nbr car les case vide ont 0

 // couleur du rendu
SDL_SetRenderDrawColor(rendu, 195, 195, 195, 195);//gris un pe pale
SDL_RenderClear(rendu);

int ind_l=0,ind_c=0;// indice ligne et indice colone
// rempli initialement de tableau de 0
 //int tab[n_ligne][n_colone]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

// initialisation victoire
 int tab[n_ligne][n_colone]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};

// initialisation defaite
//int tab[n_ligne][n_colone]={{2,2,512,32,128},{2,8,32,16,2},{8,4,512,8,4},{256,64,16,1024,2},{8,128,32,256,8}};

// initialisation deplacement gauche et droite
//int tab[n_ligne][n_colone]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,4,2,2,2},{0,2,2,2,2}};

// initialisation deplacement haut et bas
// int tab[n_ligne][n_colone]={{0,0,0,0,0},{0,0,0,0,2},{0,0,0,0,2},{0,0,0,0,2},{0,0,0,0,2}};

int tab_poss[n_ligne][n_colone];
for(ind_l=0;ind_l<n_ligne;ind_l++)for(ind_c=0;ind_c<n_colone;ind_c++)tab_poss[ind_l][ind_c]=0;

printf("**************************************************************************************** \n PHASES D'EXECUTION DU PROGRAMME \n*********************************************************** \n");


//affiche le tableeau au debut du jeux
affiche_tableau(tab);

bool sortie=false;//vraie si le jeux est fini faux sinon
SDL_Event quitter;//l'envenement qui va gere les touches dirrectionnelles et la croix de sortie de la fenetre
int n_tour=0;//nombre de tours du joueur, le jeux commence a 1
int score=0;//le score du joueur
bool possible=false;


place_nbr(rendu,tab,n_tour);


while(!sortie){//boucle du jeux
        if(n_tour==0){
                deux_aleatoire(tab);
                affiche_tableau(tab);
                deux_aleatoire(tab);
                affiche_tableau(tab);
                interface_score(rendu,score);
                place_nbr(rendu,tab,n_tour);
                printf("\n --> score=%d \n",score);
                SDL_RenderPresent(rendu);
        }
        n_tour++;

// gestion des evenments des direction et de la croix de la fenetre
        sortie=fin(score,tab,&possible);
          SDL_WaitEvent(&quitter);
          switch (quitter.type){
printf("En attente d'action:\n");
            case SDL_KEYDOWN:

                switch (quitter.key.keysym.sym){
                 case SDLK_RIGHT:
                    printf("\n --> deplacement droite \n");
                    score=score+deplacement_droite(tab,&possible,tab_poss);
                    affiche_tableau(tab);
                    if(possible==true){
                        deux_aleatoire(tab);
                        affiche_tableau(tab);
                        possible=false;
                        }else{
                         printf("\n deplacement impossible \n");
                    }
                    place_nbr(rendu,tab,n_tour);
                    printf("\n --> score=%d \n",score);
                    interface_score(rendu,score);
                    SDL_RenderPresent(rendu);// Mettre à jour le rendu
                break;
                 case SDLK_LEFT:
                    printf("\n deplacement gauche \n");
                    score=score+deplacement_gauche(tab,&possible,tab_poss);
                    affiche_tableau(tab);
                    if(possible==true){
                        deux_aleatoire(tab);
                        affiche_tableau(tab);
                        possible=false;
                    }else{
                         printf("\n --> deplacement impossible \n");
                    }
                    place_nbr(rendu,tab,n_tour);
                   printf("\n --> score=%d \n",score);
                    interface_score(rendu,score);
                    SDL_RenderPresent(rendu);// Mettre à jour le rendu
                break;

                case SDLK_DOWN:
                    printf("\n --> deplacement bas \n");
                    score=score+deplacement_bas(tab,&possible,tab_poss);
                    affiche_tableau(tab);
                    if(possible==true){
                        deux_aleatoire(tab);
                        affiche_tableau(tab);
                        possible=false;
                        }else{
                         printf("\n --> deplacement impossible \n");
                    }
                    place_nbr(rendu,tab,n_tour);
                    printf("\n --> score=%d \n",score);
                    interface_score(rendu,score);
                    SDL_RenderPresent(rendu);// Mettre à jour le rendu
                break;

                case SDLK_UP:
                    printf("\n --> deplacement haut \n");
                    score=score+deplacement_haut(tab,&possible,tab_poss);
                    affiche_tableau(tab);
                    if(possible==true){
                        deux_aleatoire(tab);
                        affiche_tableau(tab);
                        possible=false;
                       }else{
                         printf("\n --> deplacement impossible \n");
                    }
                    place_nbr(rendu,tab,n_tour);
                    printf("\n --> score=%d \n",score);
                    interface_score(rendu,score);
                    SDL_RenderPresent(rendu);// Mettre à jour le rendu
                break;
                }

        break;
      case SDL_QUIT:
        sortie=true;
        break;
          }
}//fin boucle de jeux

//affiche image de fin du jeux
    if(victoire(tab)==true){
        printf("\n --> gagne \n");


            SDL_Delay(3000);
            SDL_Surface *surfwin = SDL_LoadBMP("win.bmp");
            SDL_Texture *textwin= SDL_CreateTextureFromSurface(rendu, surfwin);
            SDL_FreeSurface(surfwin);
            SDL_RenderCopy(rendu, textwin, NULL, NULL);
            SDL_RenderPresent(rendu);
            SDL_Delay(3000);



            }
    if(defaite(tab)==true){
                printf("\n --> defaite \n");

            SDL_Delay(3000);
            SDL_Surface *surflose = SDL_LoadBMP("lose.bmp");
            SDL_Texture *textlose= SDL_CreateTextureFromSurface(rendu, surflose);
            SDL_FreeSurface(surflose);
            SDL_RenderCopy(rendu, textlose, NULL, NULL);
            SDL_RenderPresent(rendu);
            SDL_Delay(3000);


            }
    SDL_RenderPresent(rendu);

     if(NULL!=rendu)SDL_DestroyRenderer(rendu);//detruit le rendu associé a la fenetre de jeux
     if(NULL!=fenetre)SDL_DestroyWindow(fenetre);//detruit la fenetre qu'on a cree pour le jeux


    printf("\n --> merci d'avoir jouer!\n");
 return 0;
}//fin main du programme
