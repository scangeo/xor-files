#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct global_v {
	int tamano;
	int * arreglo2;
} global_v;

static void uso()
{
    fprintf(stderr, 
          "XOR for files\n"
          "Usage: \n"
          "xor [-r \"route\"] route_1 route_2 (...) route_n \n"
          "Where:\n"
          "    -r             Resultant file route\n"
          "    -h             Usage\n"
         );
}

int xor_op(FILE * archivo2, int *arreglo) {
	int d,i;
	i = 0;
	d = fgetc(archivo2);
    while(i != global_v.tamano) {
		global_v.arreglo2[i] = arreglo[i]^d;
        i++;
       	if(d == EOF) {
       		rewind(archivo2);
       	}	
        d = fgetc(archivo2);
    }
	fclose(archivo2);	
	}


int main(int argc, char *argv[])
{	
	int args, i;
	char *ruta = NULL;
	global_v.tamano =0;
	args = 0; 
	int index;
	int ruta_ind = 0;
	FILE *archivo;
	FILE *archivo2;
	
	
	while (1) {
		args = getopt(argc, argv, "r:h?");
	    if (args == -1) {
        	break;
        }
        
        switch (args) {
        	case 'r':
        		ruta = (char*)optarg;
        		ruta_ind = 1;
        		break;
        	case 'h':
        	case '?':
            	uso();
            	return 0;       		
        	default:
        		fprintf(stderr, "ERROR: Invalid argument\n");
//        		printf("error en argumento");
        		uso();
        		return 1;
        }
    }
        if (argc == 1) {
        	uso();
        	return 1;
        }
        if ((ruta==NULL) && (ruta_ind == 1 )){
        	fprintf(stderr, "ERROR: Invalid route. Please specify\n");
        	uso();
        	return 1; 
        }    
        if (ruta!=NULL) { if (strcmp(ruta,"-h")==0){
        	fprintf(stderr, "ERROR: Invalid route. Please specify\n");
        	uso();
        	return 1; 
        }}
        
        
        
        index = 3;   
        if (ruta_ind == 0) {
        	index = 3;
        }    	    
        
        
        for (optind; optind < argc; optind++) {
        	if ((argv[optind] != NULL) && (index == 3)) {
       			archivo = fopen(argv[optind],"r");
		    	if (archivo == NULL){
    		    	fprintf(stderr, "ERROR: Invalid route for first file\n");
        		//	printf("Ruta de primer archivo incorrecta\n");
        			uso();
        			return 1;
        		}
        		fseek(archivo,0, SEEK_END);
    			global_v.tamano = ftell(archivo);
		    	rewind(archivo);
		    	i = 0;
		    	global_v.arreglo2 = (int *)malloc (global_v.tamano*sizeof(int));
		    	while (i != global_v.tamano) {
		       		global_v.arreglo2[i] = fgetc(archivo);
       				i++;
       			}
		    	fclose(archivo);
		    	optind++;	
		    	index++;
			}
			        	
        	if ((argv[optind] == NULL) && ((index == 4)||(index == 3))) {
             	fprintf(stderr, "ERROR: Two files at least required\n");
 //        		printf("Debe indicar al menos dos archivos\n");
        		return 1;
        	}
        	      	
		    if ((argv[optind] != NULL) && (index > 3)) {
		    	archivo2 = fopen(argv[optind],"r");
		   		if (archivo2 == NULL){
		   		    fprintf(stderr, "ERROR: Invalid route for file %i \n",optind-2);
 //       			printf("Ruta del archivo %i incorrecta\n",optind-2);
        			uso();
        			return 1;
        		}
        	}
		    index++;
           	xor_op(archivo2,global_v.arreglo2);	  
        }	 
        
       	i = 0;
       	if (ruta_ind == 1) {
       		archivo = fopen(ruta,"w+");
       		while (i < global_v.tamano) {
       			fputc(global_v.arreglo2[i],archivo);
       			i++;
       		}
       		fclose(archivo);
       	}
       	else{
       		while (i < global_v.tamano) {
       		    fprintf(stdout, "%c",(char)global_v.arreglo2[i]);
       			i++;
       		}
       	}
       	 	
       	free(global_v.arreglo2);
      	
}

