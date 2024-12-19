
//Código realizado por Julia Carballo del Pino


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NUM_CEPAS 3
#define NUM_ANTIB 3
#define MAX_NOMBRE 70


void rellenarCepas(char cepas[NUM_CEPAS][MAX_NOMBRE]);
void rellenarSensibilidad(char cepas[NUM_CEPAS][MAX_NOMBRE],float sensibilidad[NUM_CEPAS][NUM_ANTIB]);
void mostrarSensibilidad(char cepas[NUM_CEPAS][MAX_NOMBRE],float sensibilidad[NUM_CEPAS][NUM_ANTIB]);
void modificarSensibilidad (float sensibilidad[NUM_CEPAS][NUM_ANTIB],char cepas[NUM_CEPAS][MAX_NOMBRE], char cepaIndividual[MAX_NOMBRE],
                            int antibIndividual, float nuevoValSensibilidad);
float calculosSensibilidad(float sensibilidad[NUM_CEPAS][NUM_ANTIB],char cepas[NUM_CEPAS][MAX_NOMBRE],char cepaIndividual[MAX_NOMBRE],
                            int* indiceCepa,int* indiceAntib,float*media);
void calculoDistancias(float sensibilidad[NUM_CEPAS][NUM_ANTIB],float distancias[NUM_CEPAS][NUM_CEPAS]);
void mostrarDistancias(char cepas[NUM_CEPAS][MAX_NOMBRE],float distancias[NUM_CEPAS][NUM_CEPAS]);
void ordenaDistanciaCepa(char cepaIndividual[MAX_NOMBRE], char cepas[NUM_CEPAS][MAX_NOMBRE], float distancias[NUM_CEPAS][NUM_CEPAS], int indiceCepa);

int main() {

    int numMenu;
    char cepas[NUM_CEPAS][MAX_NOMBRE];
    float sensibilidad[NUM_CEPAS][NUM_ANTIB];
    char cepaIndividual[MAX_NOMBRE];
    int antibIndividual;
    float nuevoValSensibilidad;
    float media;
    int indiceCepa;
    int indiceAntib;
    float distancias[NUM_CEPAS][NUM_CEPAS];
    int datosRellenados=0;

    do {
        printf("\n---------------------------- MENU ----------------------------\n");
        printf("1.- Introducir nombres de las cepas\n");
        printf("2.- Introducir datos de sensibilidad\n");
        printf("3.- Mostrar datos de sensibilidad\n");
        printf("4.- Modificar la sensibilidad\n");
        printf("5.- Calcular media y antibiotico mas efectivo\n");
        printf("6.- Calcular la matriz de distancias\n");
        printf("7.- Mostrar la matriz de distancias\n");
        printf("8.- Ordenar y mostrar distancias de una cepa\n");
        printf("0.- Salir\n");
        printf("\n--------------------------------------------------------------\n");
        printf("Introduzca una opcion: ");
        scanf("%d", &numMenu);
        getchar();

        switch (numMenu) {

            case 1:

                rellenarCepas(cepas);
                datosRellenados=1;

                break;


            case 2:

                if(datosRellenados==1||datosRellenados==2){

                   rellenarSensibilidad(cepas, sensibilidad);
                   datosRellenados=2;
                }else{

                printf("Por favor, inicialice primero la funcion anterior.");
                }

                break;


            case 3:

                if (datosRellenados==2) {
                    mostrarSensibilidad(cepas, sensibilidad);

                } else {
                    printf("Por favor, introduzca el nombre de las cepas primero, asi como su valor.\n");

                    }

                break;

          case 4:

              if(datosRellenados==2){

                printf("Introduce el nombre de la cepa: ");
                fgets(cepaIndividual, MAX_NOMBRE, stdin);
                cepaIndividual[strcspn(cepaIndividual, "\n")] = '\0';


                printf("Introduce el numero de antibiotico (0,1 o 2): ");
                scanf("%d", &antibIndividual);
                getchar();

                if(antibIndividual!=0&&antibIndividual!=1&&antibIndividual!=2){

                    printf("Introduzca una cifra valida para el antibiotico.");
                }else{

                    printf("Introduce el nuevo valor de sensibilidad: ");
                    scanf("%f", &nuevoValSensibilidad);
                    getchar();

                    modificarSensibilidad(sensibilidad,cepas, cepaIndividual,antibIndividual, nuevoValSensibilidad);

                }



            }else{
            printf("Por favor, inicialice primero las funciones anteriores en orden.");
            }
                break;



           case 5:

               if (datosRellenados==2) {

                printf("Introduce el nombre de la cepa: ");
                fgets(cepaIndividual, MAX_NOMBRE, stdin);
                cepaIndividual[strcspn(cepaIndividual, "\n")] = '\0';


                calculosSensibilidad(sensibilidad, cepas, cepaIndividual, &indiceCepa, &indiceAntib, &media);

                if (indiceCepa != -1) {
                printf("La media es %.2f.\nEl antibiotico mas efectivo es Antib%d (sensibilidad %.2f).\n",
                   media, indiceAntib+1, sensibilidad[indiceCepa][indiceAntib]);

        }

                } else {
                printf("Por favor, inicialice primero las funciones anteriores necesarias en orden.\n");
                }

                break;

        case 6:

                if (datosRellenados==2) {
                    calculoDistancias(sensibilidad,distancias);
                    datosRellenados=6;
                } else {
                    printf("Por favor, introduzca el nombre de las cepas primero, asi como su valor.\n");
                    }

                break;

        case 7:

                if (datosRellenados==6){
                    mostrarDistancias(cepas,distancias);
                } else {
                    printf("Por favor, inicialice primero las funciones anteriores en orden.");
                }

                break;


        case 8:

                    if (datosRellenados == 6) {
                            printf("Introduce el nombre de la cepa: ");
                            fgets(cepaIndividual, MAX_NOMBRE, stdin);
                            cepaIndividual[strcspn(cepaIndividual, "\n")] = '\0';

                            int indiceCepa = -1;
                            ordenaDistanciaCepa(cepaIndividual, cepas, distancias,indiceCepa);
                                } else {
                                    printf("Por favor, inicialice primero las funciones anteriores en orden.\n");
    }

                break;



            case 0:

            printf("Saliendo del programa...\n");

            break;



            default:

            printf("Error, vuelva a intentarlo introduciendo una cifra valida.");

            break;


            }

        } while (numMenu!=0);


        return 0;       //he considerado más oportuno el uso de int main() puesto que al ser un código tan largo sirve como control para comprobar un correcto funcionamiento
    }





//Funciones individudales:

    void rellenarCepas(char cepas[NUM_CEPAS][MAX_NOMBRE]) {

    int i;
    for (i=0;i<NUM_CEPAS;i++) {
            printf("Introduzca la cepa %d:\n", i+1);
            fgets(cepas[i], MAX_NOMBRE, stdin);
            cepas[i][strcspn(cepas[i], "\n")] = '\0';
        }

    }

    void rellenarSensibilidad(char cepas[NUM_CEPAS][MAX_NOMBRE], float sensibilidad[NUM_CEPAS][NUM_ANTIB]) {
    int i, j;
    for (i = 0; i < NUM_CEPAS; i++) {
        printf("Introduzca los datos de sensibilidad para la cepa %d:\n", i + 1);
        for (j = 0; j < NUM_ANTIB; j++) {
            printf("Sensibilidad frente a Antib%d: ", j);
            scanf("%f", &sensibilidad[i][j]);
            getchar();
        }
    }
}



    void mostrarSensibilidad(char cepas[NUM_CEPAS][MAX_NOMBRE], float sensibilidad[NUM_CEPAS][NUM_ANTIB]){

        int i, j;

        printf("==========================================\n");
        printf("Datos de sensibilidad:\n");
        printf("==========================================\n");

        printf("\t");
        for (j = 0; j < NUM_ANTIB; j++) {
        printf("Antib%d\t",j);
        }
        printf("\n");

        for (i = 0; i < NUM_CEPAS; i++) {
        printf("%s\t", cepas[i]);
            for (j = 0; j < NUM_ANTIB; j++) {
                printf("%.2f\t", sensibilidad[i][j]);
            }
                    printf("\n");
        }
    }




    void modificarSensibilidad(float sensibilidad[NUM_CEPAS][NUM_ANTIB],char cepas[NUM_CEPAS][MAX_NOMBRE], char cepaIndividual[MAX_NOMBRE],
    int antibIndividual, float nuevoValSensibilidad){

        int i=0;
        int enc=0;

        while (i<NUM_CEPAS && enc==0) {
            if (strcmp(cepas[i], cepaIndividual) == 0) {
                sensibilidad[i][antibIndividual] = nuevoValSensibilidad;
                printf("Valor modificado correctamente.\n");
                enc=1;
            }
        i++;
    }


        if (enc!=1) {
            printf("Cepa no encontrada. Intentelo de nuevo\n");
        }

    }

    float calculosSensibilidad(float sensibilidad[NUM_CEPAS][NUM_ANTIB],
                               char cepas[NUM_CEPAS][MAX_NOMBRE],
                               char cepaIndividual[MAX_NOMBRE],
                               int* indiceCepa,
                               int* indiceAntib,float*media){

        int i;
        int j;

        for (int i=0;i<NUM_CEPAS;i++) {
            if (strcmp(cepas[i], cepaIndividual) == 0) {
                *indiceCepa = i;
                *media = 0.0;
                *indiceAntib = 0;

        for (int j=0;j<NUM_ANTIB;j++) {
            *media += sensibilidad[i][j];
            if (sensibilidad[i][j] < sensibilidad[i][*indiceAntib]) {
                    *indiceAntib = j;
                }
            }
            *media /= NUM_ANTIB;

            return sensibilidad[i][*indiceAntib];
        }
    }


    if(strcmp(cepas[i],cepaIndividual)!=0){

        printf("Cepa no encontrada.");
      }

}

    void calculoDistancias(float sensibilidad[NUM_CEPAS][NUM_ANTIB],float distancias[NUM_CEPAS][NUM_CEPAS]){


        int i,j,z;
        float sum=0.0;
        float dif=0.0;

        for (i=0;i<NUM_CEPAS;i++){
            for(j=0;j<NUM_ANTIB;j++){


                if(j==i){
                    distancias[i][j]=0.0;

                }else if(j!=i && j>i){


                    for (z=0;z<NUM_ANTIB;z++) {

                    float dif=sensibilidad[i][z]-sensibilidad[j][z];
                    sum+=dif*dif;
            }
                    distancias[i][j]=sqrt(sum);

                }else{
                    distancias[i][j]=distancias[j][i];
                }

            }
        }
            printf("Proceso acabado.");
    }

    void mostrarDistancias(char cepas[NUM_CEPAS][MAX_NOMBRE],float distancias[NUM_CEPAS][NUM_CEPAS]){


        int i,j;

        printf("==========================================\n");
        printf("Matriz de distancias:\n");
        printf("==========================================\n");

        printf("\t");
            for (i=0;i<NUM_ANTIB;i++){
                printf("Antib%d\t",i);
        }


        printf("\n");


            for (i=0;i<NUM_CEPAS;i++) {
                printf("%s\t",cepas[i]);
                    for (j=0;j<NUM_ANTIB;j++) {
                        printf("%.2f\t", distancias[i][j]);
    }
        printf("\n");
    }


    }


    void ordenaDistanciaCepa(char cepaIndividual[MAX_NOMBRE], char cepas[NUM_CEPAS][MAX_NOMBRE], float distancias[NUM_CEPAS][NUM_CEPAS], int indiceCepa) {


        int i=0;
        int j=0;
        int menor=0;
        float aux;

          while (i<NUM_CEPAS) {
    if (strcmp(cepas[i],cepaIndividual)==0) {
        indiceCepa=i;
            }
    i++;
        }


    if (indiceCepa==-1) {
        printf("Cepa no encontrada.\n");
    }

    float distanciasCepa[NUM_CEPAS];
    for (i=0;i<NUM_CEPAS;i++) {
        distanciasCepa[i] = distancias[indiceCepa][i];
    }

    for (i=0;i<NUM_CEPAS-1;i++) {
        int menor=i;
        for (j=i+1;j<NUM_CEPAS;j++) {
            if (distanciasCepa[j]<distanciasCepa[menor]) {
                menor=j;
            }
        }

        float aux=distanciasCepa[i];
        distanciasCepa[i]=distanciasCepa[menor];
        distanciasCepa[menor]=aux;
    }

    printf("Las distancias ordenadas para la cepa con nombre %s son:\n", cepaIndividual);    //aquí según el output propuesto por el enunciado debería poner "...con nombre %s es:" pero al ser un fallo gramatical se ha pretendido corregir
    for (i=0;i<NUM_CEPAS;i++) {
        if (strcmp(cepas[i], cepaIndividual) != 0) {
            printf("Distancia respecto a la cepa con nombre %s: %.2f\n", cepas[i], distancias[indiceCepa][i]);

    }}
}


