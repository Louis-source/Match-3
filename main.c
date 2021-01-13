#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, char **argv)
{

    SDL_Window *window = NULL; // création d'un pointeur fenetre du menu
    SDL_Renderer *rendu_menu = NULL; //pour mettre un affichage un rendu
    SDL_Surface *menu = NULL;
    SDL_Texture *texture_menu = NULL;
    SDL_Surface *jeu = NULL;
    SDL_Texture *texture_jeu = NULL;


    if(SDL_Init(SDL_INIT_VIDEO) != 0)  // Si l'exécution de la fenêtre de fonctionne pas
    {
        SDL_Log("Erreur : Initialisation SDL > %s\n", SDL_GetError());  // affiche un message d'erreur grace à SDL_Log et renvoie une erreur
        exit(EXIT_FAILURE);
    }

// Ici nous pouvons exécuter le programme

//Création de la fenêtre
    window = SDL_CreateWindow("Space Nova", //titre de la fenetre
                                SDL_WINDOWPOS_CENTERED,  // position X (ici centré grace aux paramètre) sinon X débute en haut à gauche
                                SDL_WINDOWPOS_CENTERED,  // position y
                                WINDOW_WIDTH,  //Largeur
                                WINDOW_HEIGHT, //hauteur
                                0); // liste de drapeau pour l'affichage de la fenêtre (ici 0 = la fenêtre s'affichera normalement) SDL_WINDOW_SHOWN

    if(window == NULL)
    {
        SDL_Log("Erreur : Creation de la fenetre echoue > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

// Création du rendu
    rendu_menu = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // 3 paremetre : nom de la fenetre, ..., drapeau

    if(rendu_menu == NULL)
    {
        SDL_Log("Erreur : creation rendu du menu echoue > %s\n", SDL_GetError());
    }

//Affichage du rendu

    menu = SDL_LoadBMP("menu.bmp"); // prend en paramètre le chemin d'accès de l'image

    if(menu == NULL)
    {
        SDL_Log("Erreur : Impossible de charger le menu > %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu_menu);
        SDL_DestroyWindow(window);
    }

    texture_menu = SDL_CreateTextureFromSurface(rendu_menu, menu); // prend en paramètre le rendu et la surface ( ici image) + création texture
    SDL_FreeSurface(menu); // libère la surface pour économiser de la mémoire

    if(texture_menu == NULL)
    {
        SDL_Log("Erreur : Impossible de creer la texture du menu > %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu_menu);
        SDL_DestroyWindow(window);
    }

    SDL_Rect rectangle; // structure rectangle


    if(SDL_QueryTexture(texture_menu, NULL, NULL, &rectangle.w, &rectangle.h) !=0) //  charge la texture en mémoire, prend en paremètre la texture + 2 autres paramètres osef
    {
        SDL_Log("Erreur : Impossible de charge la texture du menu en mémoire > %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu_menu);
        SDL_DestroyWindow(window);
    }

    rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2; // permet de centrer l'image
    rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

    if(SDL_RenderCopy(rendu_menu, texture_menu, NULL, &rectangle) !=0) //permet d'afficher la texture sur l'écran paramètre rendu, texture, osef, cadre
    {
        SDL_Log("Erreur : Impossible d'afficher la texture du menu > %s\n", SDL_GetError());
        SDL_DestroyRenderer(rendu_menu);
        SDL_DestroyWindow(window);
    }

    SDL_RenderPresent(rendu_menu); //chargement du rendu


//gestion des evenements
    SDL_bool program_launched = SDL_TRUE; //type de variable booléen true ou false

    while(program_launched)
    {

        SDL_Event event; // création d'une variable de type event pour les evenements (bouge la souris , ferme le programme etc)

        while(SDL_PollEvent(&event)) // capturer les evenemnts sans bloquer ou couper le programme
        {
            switch(event.type) //quitte proprement le programme sans delay
            {
                case SDL_MOUSEBUTTONUP:
                    if(event.button.x > 448 && event.button.x < 523 && event.button.y > 350 && event.button.y < 381) // bouton jouer
                    {
                        //Affichage du rendu

                        jeu = SDL_LoadBMP("jeu.bmp"); // prend en paramètre le chemin d'accès de l'image

                        if(jeu == NULL)
                        {
                            SDL_Log("Erreur : Impossible de charger le jeu > %s\n", SDL_GetError());
                            SDL_DestroyRenderer(rendu_menu);
                            SDL_DestroyWindow(window);
                        }

                        texture_jeu = SDL_CreateTextureFromSurface(rendu_menu, jeu); // prend en paramètre le rendu et la surface ( ici image) + création texture
                        SDL_FreeSurface(jeu); // libère la surface pour économiser de la mémoire

                        if(texture_jeu == NULL)
                        {
                            SDL_Log("Erreur : Impossible de creer la texture du jeu > %s\n", SDL_GetError());
                            SDL_DestroyRenderer(rendu_menu);
                            SDL_DestroyWindow(window);
                        }

                        SDL_Rect rectangle; // structure rectangle


                        if(SDL_QueryTexture(texture_jeu, NULL, NULL, &rectangle.w, &rectangle.h) !=0) //  charge la texture en mémoire, prend en paremètre la texture + 2 autres paramètres osef
                        {
                            SDL_Log("Erreur : Impossible de charge la texture du jeu en mémoire > %s\n", SDL_GetError());
                            SDL_DestroyRenderer(rendu_menu);
                            SDL_DestroyWindow(window);
                        }

                        rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2; // permet de centrer l'image
                        rectangle.y = (WINDOW_HEIGHT - rectangle.h) / 2;

                        if(SDL_RenderCopy(rendu_menu, texture_jeu, NULL, &rectangle) !=0) //permet d'afficher la texture sur l'écran paramètre rendu, texture, osef, cadre
                        {
                            SDL_Log("Erreur : Impossible d'afficher la texture du jeu > %s\n", SDL_GetError());
                            SDL_DestroyRenderer(rendu_menu);
                            SDL_DestroyWindow(window);
                        }

                        SDL_RenderPresent(rendu_menu); //chargement du rendu
                    }
                    else if(event.button.x > 594 && event.button.x < 696 && event.button.y > 531 && event.button.y < 569) //bouton quitter
                    {
                        SDL_QUIT;
                        program_launched = SDL_FALSE;
                    }
                    else;
                    break;

                case SDL_QUIT:
                    SDL_DestroyTexture(texture_jeu); // detruit la texture
                    program_launched = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }
    }

    SDL_DestroyTexture(texture_menu); // detruit la texture
    SDL_DestroyRenderer(rendu_menu); // ferme le rendu
    SDL_DestroyWindow(window); // ferme la fenetre
    SDL_Quit(); // ferme le programme

    return EXIT_SUCCESS;

}
