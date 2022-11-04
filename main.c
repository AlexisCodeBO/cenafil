#define N 5                  /* n�mero de fil�sofos */
#define IZQUIERDO (i+N-1)%N  /* n�mero del vecino izquierdo de i */
#define DERECHO (i+1)%N      /* n�mero del vecino derecho de i */
#define PENSANDO 0           /* el fil�sofo est� pensando */
#define HAMBRIENTO 1         /* el fil�sofo trata de obtener los tenedores */
#define COMIENDO 2           /* el fil�sofo est� comiendo */
typedef int semaforo;        /* los sem�foros son un tipo especial de int */
int estado[N];               /* arreglo que lleva registro del estado de todos*/
semaforo mutex = 1;          /* exclusi�n mutua para las regiones cr�ticas */
semaforo s[N];               /* un sem�foro por fil�sofo */
void filosofo(int i)         /* i: n�mero de fil�sofo, de 0 a N-1 */
{
while(TRUE){                 /* se repite en forma indefinida */
pensar();                    /* el fil�sofo est� pensando */
tomar_tenedores(i);          /* adquiere dos tenedores o se bloquea */
comer();                     /* come espagueti */
poner_tenedores(i);          /* pone de vuelta ambos tenedores en la mesa */
}
}
void tomar_tenedores(int i)    /* i: n�mero de fil�sofo, de 0 a N-1 */
{
down(&mutex);                  /* entra a la regi�n cr�tica */
estado[i] = HAMBRIENTO;        /* registra el hecho de que el fil�sofo i est� hambriento */
probar(i);                     /* trata de adquirir 2 tenedores */
up(&mutex);                    /* sale de la regi�n cr�tica */
down(&s[i]);                   /* se bloquea si no se adquirieron los tenedores */
}
void poner_tenedores(i)        /* i: n�mero de fil�sofo, de 0 a N�1 */
{
down(&mutex);                  /* entra a la regi�n cr�tica */
estado[i] = PENSANDO;          /* el fil�sofo termin� de comer */
probar(IZQUIERDO);             /* verifica si el vecino izquierdo puede comer ahora */
probar(DERECHO);               /* verifica si el vecino derecho puede comer ahora */
up(&mutex);                    /* sale de la regi�n cr�tica */
}
void probar(i)                 /* i: n�mero de fil�sofo, de 0 a n-1 */
{
if (estado[i] == HAMBRIENTO && estado[IZQUIERDO] != COMIENDO && estado[DERECHO] != COMIENDO) {
estado[i] = COMIENDO;
up(&s[i]);
}
}
