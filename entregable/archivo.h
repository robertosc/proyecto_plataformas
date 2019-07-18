#define F_BALANCES "balance.csv"
#define F_INFO "info.csv"
#define LEN_NOMBRE 50
#define LEN_TARJETA 30
#define LEN_PIN 8
#define LEN_BUFFER 1024
#define NUM_USUARIOS 1
#define NUM_PERSONA 1
#define LEN_PASSWD 512
#define NUM_BALANCES 20
#define LEN_TIEMPO 20
#define CONTRASENA_ADMINISTRADOR "IngresoAdmin"

typedef struct balance_s{
    char nombre[30];
    char no_tarjeta[30];
    float transaccion;
}balance_t;


typedef struct usuarios_s{
    char nombre[LEN_NOMBRE];
    char tarjeta[LEN_TARJETA];
    char pin[LEN_PIN];
    char actividad[30];
    int encontrado;
}usuarios_t;


typedef struct balance_estado_s{
    char nombre[LEN_NOMBRE];
    char no_tarjeta[LEN_TARJETA];
    char transaccion[100];    
    int encontrado;
}balance_est_t;

