
struct DH{
       int dia, mes, ano, hora, minuto, segundo;
       };

struct DH Hora(){  //tipo do retorno da função hora eh struct DH
    time_t currentTime; 
    struct tm *timeinfo;
    struct DH dh;
    
     
    /* Pega a hora atual do sistema e a converte em uma estrutura tm. */
    time(&currentTime); 
    timeinfo= localtime(&currentTime); 
     
    /* Imprime o dia da semana. */
    dh.dia = timeinfo->tm_mday;
    dh.mes = timeinfo->tm_mon+1;
    dh.ano = timeinfo->tm_year + 1900;
    dh.hora = timeinfo->tm_hour;
    dh.minuto = timeinfo->tm_min;
    dh.segundo = timeinfo->tm_sec;
    
    printf("%02i/%02i/%d %02i:%02i:%02i\n",dh.dia, dh.mes, dh.ano, dh.hora, dh.minuto, dh.segundo);    
    getch();
    
   return dh;
    
}



struct score{
       char play1[100],play2[100];
       int dia,mes,ano, hora, min,seg;   
       int relogio, pont1, pont2;
       };    
       
void inclusao(int pont_p1,int pont_p2){
       
       FILE *scoreArq;
       struct DH recebedh;
       struct score sc;
       int p,i;
       
      
       scoreArq=fopen("score.txt","ab");
       
       printf("Player1 : ");
       scanf(" %s",sc.play1);
       printf("Player2 : ");
       scanf(" %s",sc.play2);

       
       recebedh=Hora();
   
        
       sc.dia=recebedh.dia;
       sc.mes=recebedh.mes;
       sc.ano=recebedh.ano;
       sc.hora=recebedh.hora;
       sc.min=recebedh.minuto;
       sc.seg=recebedh.segundo;
       sc.pont1=pont_p1;
       sc.pont2=pont_p2;
       
      
       fwrite(&sc,sizeof(sc),1,scoreArq);
         
       fclose(scoreArq);
       
   
}
void consulta(){
     FILE*scoreArq;
     struct score  sc;
     struct DH recebedh;
             
   
    scoreArq=fopen("score.txt","rb");
    printf("\n\n\t\t******** SCORE ********\n");
    printf("\n\n             Tempo Registrado                   Pontuacao\n");
    
     while (fread(&sc,sizeof(sc),1,scoreArq)){
                  
         printf(" %s : %i X %i : %s ",sc.play1,sc.pont1,sc.pont2,sc.play2);
         printf("\t\t%i/%i/%d %i:%02i:%i\n",sc.dia, sc.mes, sc.ano, sc.hora, sc.min, sc.seg);    
                
         }
     
        fclose(scoreArq);
        getch();

               
       
}

void insertionSort(score V[], int tam)
{         
        int i, j;
 
        for(i = 1; i < tam; i++){
 
                j = i;
 
                while(V[j].pont1 > V[j - 1].pont1 || V[j].pont2 > V[j - 1].pont2) {
 
                        score aux = V[j];
                        V[j] = V[j - 1];
                        V[j - 1] = aux;
                        j--;   
 
                        if(j == 0)break;
                }         
        }
 
        return;
}

void ordena(){
     
    FILE*scoreArq;
     struct score  sc;
     struct DH recebedh;
      
     score vet[50];     
     
     int i=0;   
   
    scoreArq=fopen("score.txt","rb");
    
    
     while (fread(&sc,sizeof(sc),1,scoreArq)){
                  
      vet[i]=     sc;  
      i++;        
    }
    int z=0;
    
    for(int j=0;j<i;j++){
          printf("play1 : %d X %d : Play2", vet[j].pont1,vet[j].pont2);
      }
    
     
        fclose(scoreArq);

        
        insertionSort(vet, i);
        
        scoreArq=fopen("score.txt","wb");

      for(int j=0;j<i;j++){
         fwrite(&vet[j],sizeof(vet[j]),1,scoreArq);                      
                       
      }


         fclose(scoreArq);
       
}



