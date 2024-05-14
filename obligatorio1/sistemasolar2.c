# include <stdio.h>
# include <math.h>

#define G 6.67e-11
#define Ms 1.99e30
#define c 1.496e11

int main()
{
    int i, j, k;
    double h, energia, l, p, t, tf;
    double m[6], x[6],  y[6], vx[6], vy[6], a1x[6], a1y[6], aux[6], a2x[6], a2y[6];
    

    //defino valores de las masas, posiciones iniciales y velocidades iniciales
    //masas en kg
    m[0]=1.99e30;
    m[1]=3.3e23;
    m[2]=48.7e23;
    m[3]=59.7e23;
    m[4]=6.42e23;
    m[5]=18990e23;
    //m[6]=568.0e24;
    //m[7]=86.8e24;
    //m[8]=102.0e24;
    //m[9]=0.0125e24;
    
    //distancias expresadas en m
    x[0]=0.0;
    x[1]=57.9e9;
    x[2]=108.2e9;
    x[3]=149.6e9;
    x[4]=227.9e9;
    x[5]=778.6e9;
    //x[6]=1433.5e9;
    //x[7]=2872.e9;
    //x[8]=4495.1e9;
    //x[9]=5870.0e9;
    
    for(i=0;i<6;i++) 
    {
        y[i]=0.0;
        vx[i]=0.0;
        aux[i]=0.0; //lleno el vector auxiliar de 0, para que cuando un planeta haya dado una vuelta entera, escribamos el periodo y lo hagamos valer 1
    }    
    //velocidades expresadas en m/s    
    vy[0]=0; 
    vy[1]=47900;
    vy[2]=35000;
    vy[3]=29800;
    vy[4]=24100;
    vy[5]=13100;
    //vy[6]=9700.0;
    //vy[5]=6800.0;
    //vy[5]=5400.0;
    //vy[5]=4700.0;

    //reescalamos las masas, las distancias y las velocidades
    
    for(i=0;i<6;i++)
    {
        m[i]=m[i]/Ms;
        x[i]=x[i]/c;
        vy[i]=vy[i]*sqrt(c/(G*Ms));
    }
    //abro un archivo para escribir los datos x-y de cada planeta
    //abro otro fichero para escribir la energía y el momento angular en
    //función del tiempo, y otro para escribir los periodos
    FILE *f1,*f2,*f3;
    f1=fopen("datosdelsistemasolar.txt","w");
    f2=fopen("energiayl.txt","w");
    f3=fopen("periodos.txt","w");
    t=0.0;
    h=0.1;
    //tf=5*24*3600;
    tf=1000;
    //tf=tf*sqrt((G*Ms)/pow(c,3));
    //calculo las aceleraciones a partir de la suma de fuerzas sobre cada partícula i
    for(i=0;i<6;i++) 
    {
        a1x[i]=0.0;
        a1y[i]=0.0;
    } 
    
    for (i=0;i<6;i++) {
        for (j=0;j<6;j++) {
            if (i != j) {
                a1x[i] = a1x[i] - m[j] * (x[i] - x[j]) * pow(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2), -1.5);
                a1y[i] = a1y[i] - m[j] * (y[i] - y[j]) * pow(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2), -1.5);
            }
        }
    }
    
    
    //para ver en pantalla las aceleraciones
    printf("aceleraciones\n");
    for (i = 0; i < 6; i++) {
    printf("%lf %lf\n", a1x[i], a1y[i]);
    }
    
    
    //empiezo el metodo iterativo basado en el algoritmo de verlet
    for (t=0;t<tf;t=t+h) {

        fprintf(f1, "%lf, %lf\n%lf, %lf\n%lf, %lf\n%lf, %lf\n%lf, %lf\n%lf, %lf\n", x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3], x[4], y[4], x[5], y[5]);
        fprintf(f1, "\n");
        
        
    


        //calcular y escribir en el segundo archivo la energía y el momento
        energia = 0.0;
        l = 0.0;
        for (i = 0; i < 6; i++) {
            l = l + m[i] * (x[i] * vy[i] - y[i] * vx[i]);
            energia = energia + 0.5 * m[i] * (pow(vx[i],2) + pow(vy[i],2));
            for (j = 0; j < 6; j++) {
                if (i != j) {
                    energia = energia - (m[i] * m[j] * pow(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2), -0.5));
                }
            }
        }
        fprintf(f2, "%lf %lf %lf\n", energia, t, l);

        //hago un bucle if para que nos dé los periodos orbitales de los planetas
        //y los escriba en el tercer fichero
        //para ello impongo las condiciones de que "y" esté en un intervalo muy proximo a 0, x sea positivo y
        //t sea mayor que un cierto numero de iteraciones para evitar el instante inicial
        for (i = 1; i <= 6; i++) {
            if (aux[i] == 0) {
                if (((y[i] < 0.01 && y[i] > -0.01) && (x[i] > 0)) && (t > 50)) {
                   fprintf(f3, "%d, %f\n", i, t*sqrt(pow(c,3)/G*Ms));
                   aux[i] = 1;
                }
            }
        }

    
        //calculo las posiciones x(t+h), y(t+h) y las funciones w
        for (i = 0; i < 6; i++) {
            x[i]=x[i]+h*vx[i]+0.5*pow(h,2)*a1x[i];
            y[i]=y[i]+h*vy[i]+0.5*pow(h,2)*a1y[i];
            //wx[i]=vx[i]+0.5*h*a1x[i];
            //wy[i]=vy[i]+0.5*h*a1y[i];
        }
        //calculo las aceleraciones a(t+h) usando las nuevas posiciones
        for(i=0;i<6;i++) {
            a2x[i]=0.0;
            a2y[i]=0.0;
        } 
        for (i=0;i<6;i++) {
            for (j = 0; j < 6; j++) {
                if (i != j) {
                   a2x[i] =  (-m[j]) * ((x[i] - x[j])) * (pow(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2), -1.5));
                   a2y[i] =  (-m[j]) * ((y[i] - y[j])) * (pow(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2), -1.5));
                }
            }
        }
        //calculo las velocidades en t+h
        for (i = 0; i < 6; i++) {
            vx[i]=vx[i]+0.5*h*(a1x[i]+a2x[i]);
            vy[i]=vy[i]+0.5*h*(a1y[i]+a2y[i]);
        }
        
        for(i=0;i<6;i++) 
        {
            a1x[i]=a2x[i];
            a1y[i]=a2y[i];
        } 
        
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    }


