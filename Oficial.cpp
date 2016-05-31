#include <allegro.h>
#include <winalleg.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include <time.h>//necessário p/ função time()
#include "estrutura_arq.h"

volatile int exit_program;
void fecha_programa()
{
    exit_program = TRUE;
}
END_OF_FUNCTION(fecha_programa)

volatile int ticks;
void tick_counter()
{
    ticks++;
}
END_OF_FUNCTION(tick_counter)

volatile int milisegundos;
void msec_counter()
{
    milisegundos++;
}
END_OF_FUNCTION(msec_counter)


void sleep( clock_t wait )  //Wait é o tempo que deverá ficar ocioso.. em milisegundos --  delay
{
    clock_t goal = ( wait + clock() );

    while( goal > clock() );
} // observe que durante o tempo [wait] o programa vai ficar completamente parado! ou seja até sair da função -- delay

void initialize(volatile int *exit,volatile int *ticks,volatile int *milisegundos)
{
    allegro_init();
    install_timer();
    install_keyboard();
    set_color_depth(32);
    install_joystick(JOY_TYPE_AUTODETECT);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_window_title("Jogo da veia");

    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

    LOCK_FUNCTION(tick_counter);
    LOCK_VARIABLE(ticks);
    install_int_ex(tick_counter, BPS_TO_TIMER(60));

    LOCK_FUNCTION(msec_counter);
    LOCK_VARIABLE(milisegundos);
    install_int_ex(msec_counter, MSEC_TO_TIMER(1));            
}

int main()
{
    exit_program = FALSE;
    ticks = 0;
    milisegundos = 0;
    initialize(&exit_program, &ticks, &milisegundos);

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* esco = load_bitmap("escolha.bmp", NULL);
    BITMAP* jogo = load_bitmap("jogo.bmp", NULL);
    BITMAP* esc_menu = load_bitmap("escolha2.bmp", NULL);
    BITMAP* bengala = load_bitmap("bengala.bmp", NULL);
    BITMAP* bolinha = load_bitmap("bolinha.bmp", NULL);
    BITMAP* youwin = load_bitmap("youwin.bmp", NULL);
    BITMAP* start = load_bitmap("start.bmp", NULL);
    
    BITMAP* fundo[2];
    fundo[0] = load_bitmap("menu.bmp", NULL);
    fundo[1] = load_bitmap("menu2.bmp", NULL);
    //musica
    SAMPLE* musica = load_sample("musica.wav");
    //velhas
    BITMAP* rosa[3];
    rosa[0] = load_bitmap("velharosa.bmp", NULL);
    rosa[1] = load_bitmap("velharosa1.bmp", NULL);
    rosa[2] = load_bitmap("velharosa2.bmp", NULL);
    
    BITMAP* azul[3];
    azul[0] = load_bitmap("velhazul.bmp", NULL);
    azul[1] = load_bitmap("velhazul1.bmp", NULL);
    azul[2] = load_bitmap("velhazul2.bmp", NULL);
    
    BITMAP* win[2];
    win[0] = load_bitmap("velharosawin.bmp", NULL);
    win[1] = load_bitmap("velhazulwin.bmp", NULL);
    
    int x = 268, y = 180;//posição de escolha
    int pont_p1 = 0,pont_p2 = 0;
    int player = 1;
    int x2[20],y2[20];
    int i = 0,op = 1;
    int linha=0,coluna=0;
    int pos_v = 0, pos_x = 1, pos_b = 2;
    int bb = 380, a = 0;// posição para escolha do menu
    int jogar = 1;
    int menu = 1,sair = 0;
    int desenho[3][3];
    int mop = 0;
    int winer;
    int jogadas = 0;
    
    char jogador1[100] = "Player1";
    char jogador2[100] = "Player2";
    FILE *arquivo;
    
      x2[0]=268;
      y2[0]=180;
      x2[1]=364;
      y2[1]=180;
      x2[2]=460;
      y2[2]=180;
      
      x2[3]=268;
      y2[3]=264;
      x2[4]=364;
      y2[4]=264;
      x2[5]=460;
      y2[5]=264;
      
      x2[6]=268;
      y2[6]=348;
      x2[7]=364;
      y2[7]=348;
      x2[8]=460;
      y2[8]=348;
      
      int velha = 0;
      
    for(linha=0; linha<4; linha++)
    {
        for(coluna=0; coluna<4; coluna++)
        {
            desenho[linha][coluna] = pos_v;
        }
    }
    
    play_sample(musica, 255, 128, 1000, TRUE);
    
    set_color_blender(0,0,0, makecol(60, 200, 10));
    //INPUT

    while(!exit_program)
    {
        while(ticks > 0 && !exit_program)
        {

            while(!key[KEY_ESC] && sair == 0)
            {
              
              poll_joystick();
              fecha_programa();
                //menu
              int z = 0;
              a = 0;
              bb = 380;
              
              
              while(menu == 1 && sair == 0 && !key[KEY_ESC]){
                    poll_joystick();
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 345, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    if(key[KEY_DOWN] ||  joy[0].stick[2].axis[1].pos > 0 ){
                    
                    bb += 22;
                    a += 1;
                    
                    if(bb > 424){
                         bb-=22;
                         a--;
                    }
                    
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 345, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    sleep(250); //ocioso durante 1 segundo
                    
                    }
                    if(key[KEY_UP] || joy[0].stick[2].axis[1].pos < 0 ){
                    
                    bb -= 22;
                    a -= 1;
                    if(bb < 380){
                         bb+=22;
                         a++;
                    }
                    
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 345, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    sleep(250); //ocioso durante 1 segundo
                    
                    }
                    
                    if((a == 0 && key[KEY_ENTER]) || ( a == 0 && joy[0].button[2].b  ) ){
                    
                    menu = 2;
                    mop = 1;
                    
                    sleep(250); //ocioso durante 1 segundo -- delay
                    }
                    
                    if((a == 1 && key[KEY_ENTER]) || ( a == 1 && joy[0].button[2].b   )){
                    /*
                    arquivo = fopen("teste.txt","rt"); //wt = Gravação
                                       //rt = Leitura
                                       //a  = append

                    if(arquivo==NULL){      //Se houver algum erro, o ponteiro apontará para NULL
                    printf("Nao foi possivel abrir o arquivo");
                    exit(0);
                    }
                    
                    fscanf(arquivo,"%s %d %d %s", &jogador1, &pont_p1, &pont_p2, &jogador2);
                    printf("\n%s : %d X %d : %s\n", jogador1, pont_p1, pont_p2, jogador2);
                    
                    fclose(arquivo);
                    */
                    consulta();
                    
                    sleep(250); //ocioso durante 1 segundo -- delay
                    
                    }
                    
                    if((a == 2 && key[KEY_ENTER]) || ( a == 2 && joy[0].button[2].b   )){
                    menu = 0;
                    sair = 1;
                    player = 0;
                    jogar = 0;
                    }
                    
                }//while menu
                
                bb = 380;
                
                          
                while(menu == 2 && sair == 0 && !key[KEY_ESC]){
                    
                    poll_joystick();
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 320, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    if(key[KEY_DOWN] ||  joy[0].stick[2].axis[1].pos > 0 ){
                    
                    bb += 22;
                    z += 1;
                    
                    if(bb > 424){
                         bb-=22;
                         z--;
                    }
                    
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 320, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    sleep(250); //ocioso durante 1 segundo
                    
                    }
                    if(key[KEY_UP] || joy[0].stick[2].axis[1].pos < 0 ){
                    
                    bb -= 22;
                    z -= 1;
                    if(bb < 380){
                         bb+=22;
                         z++;
                    }
                    
                    masked_blit(fundo[mop], buffer, 0, 0, 0, 0, 800, 600);
                    masked_blit(esc_menu, buffer, 0, 0, 320, bb, 20, 20);

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    sleep(250); //ocioso durante 1 segundo
                    
                    }
                    
                    if((z == 0 && key[KEY_ENTER]) || ( z == 0 && joy[0].button[2].b  )){
                    jogar = 1;
                    menu = 0;
                    /*system("cls");
                    printf("Insira o nome dos jogadores\n");
                    printf("Player 1 - nome : ");
                    scanf("%s",jogador1);
                    printf("Player 2 - nome : ");
                    scanf("%s",jogador2);*/
                    op = 1;
                    sleep(500); //ocioso durante 1 segundo -- delay
                    }
                    
                    if((z == 1 && key[KEY_ENTER]) || ( z == 1 && joy[0].button[2].b  )){
                    jogar = 1;
                    menu = 0;
                    /*system("cls");
                    printf("Insira o nome dos jogadores\n");
                    printf("Player 1 - nome : ");
                    scanf("%s",jogador1);
                    printf("Player 2 - nome : ");
                    scanf("%s",jogador2);*/
                    op = 3;
                    sleep(500); //ocioso durante 1 segundo -- delay
                    }
                    
                    if((z == 2 && key[KEY_ENTER]) || ( z == 2 && joy[0].button[2].b  )){
                    jogar = 1;
                    menu = 0;
                    /*system("cls");
                    printf("Insira o nome dos jogadores\n");
                    printf("Player 1 - nome : ");
                    scanf("%s",jogador1);
                    printf("Player 2 - nome : ");
                    scanf("%s",jogador2);*/
                    op = 5;
                    sleep(500); //ocioso durante 1 segundo -- delay
                    }
                }//while menu 2
                
                linha = 0;
                coluna = 0;
                pont_p2 = 0;
                pont_p1 = 0; 
                
                
                         while(jogar == 1){
                                 
                                 masked_blit(start, buffer, 0, 0, 0, 0, 800, 600);
                                 textprintf(buffer, font, 20, 140, -1,"%s", jogador1);
                                 textprintf(buffer, font, 725, 140, -1,"%s", jogador2);
                                 draw_sprite(screen, buffer, 0, 0);
                                 clear_to_color(buffer, makecol(255,255,255));
                               /*( joy[0].button[0].b ) // Botão A (XBOX),   Botão X (PS).
                                 ( joy[0].button[1].b ) // Botão B (XBOX),   Botão O (PS).
                                 ( joy[0].button[2].b ) // Botão X (XBOX),   Botão quadrado (PS).
                                 ( joy[0].button[3].b ) // Botão Y (XBOX),   Botão triangulo (PS).
                                 ( joy[0].button[4].b ) // Botão LB (XBOX),   Botão L1 (PS).
                                 ( joy[0].button[5].b ) // Botão RB (XBOX),   Botão R1 (PS).
                                 ( joy[0].button[6].b ) // Botão BACK (XBOX),   Botão SELECT (PS).
                                 ( joy[0].button[7].b ) // Botão START (XBOX),   Botão START (PS).
                                 ( joy[0].button[8].b ) // Botão LS (XBOX),   Botão L2 (PS).
                                 ( joy[0].button[9].b ) // Botão RS (XBOX),   Botão R2 (PS)
                                 os principais tem que testar*/
                                 
                                 if(key[KEY_ENTER]){
                                 
                                 jogar = 2;
                                 sleep(250); //ocioso durante 1 segundo -- delay
                                 
                                 }
                         }
                
                
                while((player == 1 && jogar == 2 && !key[KEY_ESC] )|| (player == 2 && jogar == 2 && !key[KEY_ESC])){
                 //player 1 e player 2
                          
                          poll_joystick();
                          
                          if(pont_p1 == op){
                          winer = 0;
                          jogar = 0;
                          }
                          
                          if(pont_p2 == op){
                          winer = 1;
                          jogar = 0;
                          }
                          
                 //comparação de locais
                          if((desenho[0][0] == pos_x && desenho[0][1] == pos_x && desenho[0][2] == pos_x) ||//linha 1
                          (desenho[1][0] == pos_x && desenho[1][1] == pos_x && desenho[1][2] == pos_x) ||//linha 2
                          (desenho[2][0] == pos_x && desenho[2][1] == pos_x && desenho[2][2] == pos_x) ||//linha 3
                          (desenho[0][0] == pos_x && desenho[1][1] == pos_x && desenho[2][2] == pos_x) ||//diagonal 1
                          (desenho[0][2] == pos_x && desenho[1][1] == pos_x && desenho[2][0] == pos_x) ||//diagonal 2
                          (desenho[0][0] == pos_x && desenho[1][0] == pos_x && desenho[2][0] == pos_x) ||//coluna 1
                          (desenho[0][1] == pos_x && desenho[1][1] == pos_x && desenho[2][1] == pos_x) ||//coluna 2
                          (desenho[0][2] == pos_x && desenho[1][2] == pos_x && desenho[2][2] == pos_x)){//coluna 3
                          
                          pont_p1+=1;
                          for(linha=0; linha<4; linha++)
                          {
                                       for(coluna=0; coluna<4; coluna++)
                                       {
                                                     desenho[linha][coluna] = pos_v;
                                       }
                          }
                          x = 268;
                          y = 180;
                          linha = 0;
                          coluna = 0;
                          
                          } else if((desenho[0][0] == pos_b && desenho[0][1] == pos_b && desenho[0][2] == pos_b) ||//linha 1
                          (desenho[1][0] == pos_b && desenho[1][1] == pos_b && desenho[1][2] == pos_b) ||//linha 2
                          (desenho[2][0] == pos_b && desenho[2][1] == pos_b && desenho[2][2] == pos_b) ||//linha 3
                          (desenho[0][0] == pos_b && desenho[1][1] == pos_b && desenho[2][2] == pos_b) ||//diagonal 1
                          (desenho[0][2] == pos_b && desenho[1][1] == pos_b && desenho[2][0] == pos_b) ||//diagonal 2
                          (desenho[0][0] == pos_b && desenho[1][0] == pos_b && desenho[2][0] == pos_b) ||//coluna 1
                          (desenho[0][1] == pos_b && desenho[1][1] == pos_b && desenho[2][1] == pos_b) ||//coluna 2
                          (desenho[0][2] == pos_b && desenho[1][2] == pos_b && desenho[2][2] == pos_b)){//coluna 3
                          
                          pont_p2+=1;
                          for(linha=0; linha<4; linha++)
                          {
                                       for(coluna=0; coluna<4; coluna++)
                                       {
                                                     desenho[linha][coluna] = pos_v;
                                       }
                          }
                          x = 268;
                          y = 180;
                          linha = 0;
                          coluna = 0;
                          
                          }
                          if(desenho[0][0] != pos_v && desenho[0][1] != pos_v && desenho[0][2] != pos_v &&//linha 1
                             desenho[1][0] != pos_v && desenho[1][1] != pos_v && desenho[1][2] != pos_v &&//linha 2
                             desenho[2][0] != pos_v && desenho[2][1] != pos_v && desenho[2][2] != pos_v){ //linha 3
                           
                           velha++;

                           for(linha=0; linha<4; linha++){
                                         for(coluna=0; coluna<4; coluna++)
                                         {
                                                       desenho[linha][coluna] = pos_v;
                                         }
                           }
                           
                           x = 268;
                           y = 180;
                           linha = 0;
                           coluna = 0;
                           
                           }
                           
                           
                    textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                    masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                    masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                    masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                    masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                    textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                    textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                    textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                    textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);
                    
                    if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                    draw_sprite(screen, buffer, 0, 0);
                    clear_to_color(buffer, makecol(255,255,255));
                    
                    if((key[KEY_ENTER] && player == 1) || (joy[0].button[2].b  && player == 1)){
                        
                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);
                        
                        
                        if(desenho[linha][coluna] == pos_v){
                            desenho[linha][coluna] = pos_x;
                            player = 2;
                            jogadas++;
                        
                        }
                        else{
                        textprintf(buffer, font, 350, 100, -1,"Ocupado %d",desenho[linha][coluna]);
                        }
                        
                        
                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                        draw_sprite(screen, buffer, 0, 0);
                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo -- delay
                        
                    }//player 1
                    
                    
                    
                    if((key[KEY_ENTER] && player == 2) || (joy[0].button[2].b  && player == 2)){
                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);
                        
                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);


                        if(desenho[linha][coluna] == pos_v)
                        {
                            desenho[linha][coluna] = pos_b;
                            player = 1;
                            jogadas++;
                            
                        }
                        else{
                        textprintf(buffer, font, 350, 100, -1,"Ocupado %d",desenho[linha][coluna]);
                        }
                        
                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                        draw_sprite(screen, buffer, 0, 0);
                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo -- delay
                    }//player 2
                    
                    
                    if(key[KEY_RIGHT] || joy[0].stick[2].axis[0].pos > 0 ){

                        coluna += 1;

                        if(coluna >2)
                        {
                            coluna -= 1;
                        }

                        x += 94;

                        if(x > 458)
                        {
                            x-=94;
                        }

                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);

                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                        draw_sprite(screen, buffer, 0, 0);

                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo -- delay
                    }

                    if(key[KEY_LEFT] || joy[0].stick[2].axis[0].pos < 0){

                        coluna -= 1;
                        if(coluna <0)
                        {
                            coluna += 1;
                        }

                        x -= 94;
                        if(x < 268)
                        {
                            x+=94;
                        }

                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);

                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                        draw_sprite(screen, buffer, 0, 0);

                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo
                    }

                    if(key[KEY_DOWN] ||  joy[0].stick[2].axis[1].pos > 0){

                        linha += 1;
                        if(linha >2)
                        {
                            linha -= 1;
                        }

                        y += 84;
                        //348

                        if(y > 348)
                        {
                            y-=84;
                        }

                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);

                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 3
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }

                        draw_sprite(screen, buffer, 0, 0);

                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo

                    }


                    if(key[KEY_UP] || joy[0].stick[2].axis[1].pos < 0 ){

                        linha -= 1;

                        if(linha <0)
                        {
                            linha += 1;
                        }

                        y -= 84;

                        if(y < 180)
                        {
                            y+=84;
                        }

                        textprintf(buffer, font, 350, 100, -1,"Player: %d", player);

                        masked_blit(jogo, buffer, 0, 0, 265, 177, 300, 245);
                        masked_blit(esco, buffer, 0, 0, x, y, 80, 70);
                        masked_blit(rosa[i], buffer, 0, 0, 0, 350, 170, 170);
                        masked_blit(azul[i], buffer, 0, 0, 630, 350, 170, 170);
                        textprintf(buffer, font, 0, 540, -1,"Player 1 : %s", jogador1);
                        textprintf(buffer, font, 650, 540, -1,"Player 2 : %s", jogador2);
                        textprintf(buffer, font, 0, 570, -1,"Player 1 : %d", pont_p1);
                        textprintf(buffer, font, 650, 570, -1,"Player 2 : %d",pont_p2);
                        
                        if(desenho[0][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[0], y2[0], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[0], y2[0], 80, 80);

                            }
                        }
                        if(desenho[0][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[1], y2[1], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[1], y2[1], 80, 80);

                            }
                        }
                        if(desenho[0][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[2], y2[2], 80, 80);

                        }
                        else
                        {
                            if(desenho[0][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[2], y2[2], 80, 80);

                            }
                        }
                        //linha 1
                        if(desenho[1][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[3], y2[3], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[3], y2[3], 80, 80);

                            }
                        }
                        if(desenho[1][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[4], y2[4], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[4], y2[4], 80, 80);

                            }
                        }
                        if(desenho[1][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[5], y2[5], 80, 80);

                        }
                        else
                        {
                            if(desenho[1][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[5], y2[5], 80, 80);

                            }
                        }
                        //linha 2
                        if(desenho[2][0] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[6], y2[6], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][0] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[6], y2[6], 80, 80);

                            }
                        }
                        if(desenho[2][1] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[7], y2[7], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][1] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[7], y2[7], 80, 80);

                            }
                        }
                        if(desenho[2][2] == pos_b)
                        {

                            masked_blit(bolinha, buffer, 0, 0, x2[8], y2[8], 80, 80);

                        }
                        else
                        {
                            if(desenho[2][2] == pos_x)
                            {

                                masked_blit(bengala, buffer, 0, 0, x2[8], y2[8], 80, 80);

                            }
                        }
                        

                        draw_sprite(screen, buffer, 0, 0);

                        clear_to_color(buffer, makecol(255,255,255));

                        sleep(250); //ocioso durante 1 segundo

                    }

                }//fecha if player 1 e player 2

                while(pont_p1 == op && !key[KEY_ESC]){
                poll_joystick();
                masked_blit(win[winer], buffer, 0, 0, 315, 215, 170, 170);
                masked_blit(youwin, buffer, 0, 0, 40, 0, 720, 150);
                textprintf(buffer, font, 300, 400, -1,"Player %s : %d", jogador1, pont_p1);
                textprintf(buffer, font, 300, 450, -1,"velha(s) : %d", velha);
                draw_sprite(screen, buffer, 0, 0);
                clear_to_color(buffer, makecol(255,255,255));
                
                
                
                if(key[KEY_ENTER] || joy[0].button[2].b ){
                menu = 1;
                op = 10;
                jogar = 0;
                mop = 0;
                player = 1;
                sleep(250); //ocioso durante 1 segundo
                
                /*arquivo = fopen("score.txt","a"); //wt = Gravação
                                       //rt = Leitura
                                       //a  = append
                
                if(arquivo==NULL){      //Se houver algum erro, o ponteiro apontará para NULL
                printf("Nao foi possivel abrir o arquivo");
                }
                
                fprintf(arquivo,"\n%s : %d X %d : %s",jogador1 , pont_p1,pont_p2,jogador2);
                
                fclose(arquivo);*/
                
                inclusao(pont_p1,pont_p2);
                
                }
                
                }
                
                while(pont_p2 == op  && !key[KEY_ESC]){
                masked_blit(win[winer], buffer, 0, 0, 315, 215, 170, 170);
                masked_blit(youwin, buffer, 0, 0, 40, 0, 720, 150);
                textprintf(buffer, font, 300, 400, -1,"Player %s : %d", jogador2, pont_p2);
                textprintf(buffer, font, 300, 450, -1,"velha(s) : %d", velha);
                draw_sprite(screen, buffer, 0, 0);
                clear_to_color(buffer, makecol(255,255,255));
                
                
                if(key[KEY_ENTER] || joy[0].button[2].b ){
                menu = 1;
                op = 10;
                jogar = 0;
                mop = 0;
                player = 1;
                sleep(250); //ocioso durante 1 segundo
                
                /*arquivo = fopen("score.txt","a"); //wt = Gravação
                                       //rt = Leitura
                                       //a  = append
                
                if(arquivo==NULL){      //Se houver algum erro, o ponteiro apontará para NULL
                printf("Nao foi possivel abrir o arquivo");
                }
                
                fprintf(arquivo,"%s : %d X %d : %s\n",jogador1 , pont_p1, pont_p2, jogador2);
                
                fclose(arquivo);*/
                
                inclusao(pont_p1,pont_p2);
                ordena();
                
                }
                
                }
                
                }
            ticks --;
            
        }
    }
    ///FINALIZA??O
    stop_midi();
    destroy_sample(musica);
    destroy_bitmap(buffer);
    destroy_bitmap(bolinha);
    destroy_bitmap(fundo[0]);
    destroy_bitmap(fundo[1]);
    destroy_bitmap(jogo);
    destroy_bitmap(esc_menu);
    destroy_bitmap(esco);
    destroy_bitmap(bengala);
    destroy_bitmap(youwin);
    destroy_bitmap(rosa[0]);
    destroy_bitmap(rosa[1]);
    destroy_bitmap(rosa[2]);
    destroy_bitmap(azul[0]);
    destroy_bitmap(azul[1]);
    destroy_bitmap(azul[2]);
    destroy_bitmap(win[0]);
    destroy_bitmap(win[1]);

}
END_OF_MAIN();
