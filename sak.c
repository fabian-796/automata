#include<stdio.h>
#include<string.h>
#define N 1000
#define ESTADOS_TOTALES 5
#define ESTADOS_FINALES 1
#define ALFABETO_CARACT 7
#define SIMBOLOS_ERRONEOS 0
#define ESTADO_FINAL_NOT 1
#define ESTADO_FINAL_ACEPT 4
enum ESTADOS_DFA{q1,q2,q3,q4,q5};
enum entrada{s,a,k,S,A,K};
int estados_Aceptados[ESTADOS_FINALES]={q4};
char alfabeto[ALFABETO_CARACT]={'s','a','k','S','A','K',' '};
int tabla_Transiciones[ESTADOS_TOTALES][ALFABETO_CARACT];
int estado_Current = q1;
int estado_Current2 = q1; 
void DefineDFA(){
  tabla_Transiciones[q1][a] = q5;
  tabla_Transiciones[q1][A] = q5;
  tabla_Transiciones[q1][k] = q5;
  tabla_Transiciones[q1][K] = q5;
  tabla_Transiciones[q1][s] = q2;
  tabla_Transiciones[q1][S] = q2;

  
  tabla_Transiciones[q2][a] = q3;
  tabla_Transiciones[q2][A] = q3;
  tabla_Transiciones[q2][s] = q2;
  tabla_Transiciones[q2][S] = q2;
  tabla_Transiciones[q2][k] = q5;
  tabla_Transiciones[q2][K] = q5;

  tabla_Transiciones[q3][k] = q4;
  tabla_Transiciones[q3][K] = q4;
  tabla_Transiciones[q3][a] = q3;
  tabla_Transiciones[q3][A] = q3;
  tabla_Transiciones[q3][s] = q5;
  tabla_Transiciones[q3][S] = q5;

  tabla_Transiciones[q4][k] = q4;
  tabla_Transiciones[q4][K] = q4;
  tabla_Transiciones[q4][a] = q5;
  tabla_Transiciones[q4][A] = q5;
  tabla_Transiciones[q4][s] = q5;
  tabla_Transiciones[q4][S] = q5;
  
  tabla_Transiciones[q5][s] = q5;
  tabla_Transiciones[q5][S] = q5;
  tabla_Transiciones[q5][a] = q5;
  tabla_Transiciones[q5][A] = q5;
  tabla_Transiciones[q5][k] = q5;
  tabla_Transiciones[q5][K] = q5;
}//fin del automata

void resetAUTO(){
  estado_Current = q1;
}

int DFA(char current_symbol){
  int i,pos;
  for(pos = 0; pos < ALFABETO_CARACT; pos++)
      if( current_symbol == alfabeto[pos])
          break; //paramos si algun caracter es diferente a s or a or k
          
  if(pos == ALFABETO_CARACT)
      return SIMBOLOS_ERRONEOS; 
  for( i = 0; i < ESTADOS_FINALES; i++)
  { 
        if( (estado_Current = tabla_Transiciones[estado_Current][pos]) == estados_Aceptados[i]){
              return ESTADO_FINAL_ACEPT;
    }//fin del if
  }//fin del for
  return ESTADO_FINAL_NOT;
}//fin del DFA

int main(){
    int result;
    char cadena[N];
    int cuenta = 0;
    DefineDFA(); //llenamos la tabla de transiciones
    //printf("dame la cadena con 's', 'a', 'k':\n presiona enter para parar\n");
    while( scanf("%s",&cadena)/*scanf("%[^\n]", &cadena)*/ != EOF){
    /*int cuenta = 0;*/
    char delimitador[] = " ";
    char *token = strtok(cadena, delimitador);
            if(token != NULL){
                    while(token != NULL){
                           // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
                     // printf("Token: %s\n", token);
                        if( strlen(token) < N){
                                for(int i = 0; i < strlen(token); i++){
                                   if( (result = DFA(token[i])) == SIMBOLOS_ERRONEOS)
                                        break;     
                              }//fin de la longitud del token 

                              switch(result){
                                    case SIMBOLOS_ERRONEOS: /*printf("No aceptado");*/ break;
                                    case ESTADO_FINAL_NOT: /*printf(" no aceptado ");*/ break;
                                    case ESTADO_FINAL_ACEPT: cuenta++;/*printf(" aceptado ");*/ break;
                              }
                              resetAUTO(); }
                             //printf("\n"); }//fin del if para la condicion de longitud
                             //del ejercio a lo mas de longitud 10
                             
                      token = strtok(NULL, delimitador); //en esta linea le pasamos el token siguiente hasta que encuentre en NULL
                    }//fin del while para token  printf("%s\n", token); 
                   
            }
	}//fin del while para eof
            printf("%d",cuenta);     
	   printf("\n");
return 0;//termino correctamente
}//fin del main
