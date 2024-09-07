#include "client.h"
#include <readline/readline.h>
#include <string.h>

int main(void){

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = iniciar_config();

	valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");

	log_info(logger, "%s | %s | %s",valor, ip, puerto); 
	

	conexion = crear_conexion(ip, puerto);
	enviar_mensaje(valor, conexion);


	//leer_consola(logger);
	paquete(conexion);
	terminar_programa(conexion, logger, config);

}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger= log_create("tp0.log", "", true, LOG_LEVEL_INFO );

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config= config_create("cliente.config");

	if (nuevo_config == NULL) {
    	printf("No se pudo crear el config!");
		config_destroy(nuevo_config);
	}

	return nuevo_config;
}

// void leer_consola(t_log* logger)
// {	
// 	char* leido = readline("> ");

// 	while (strcmp("", leido)!=0){
// 		log_info(logger, leido);
// 		leido = readline("> ");
// 	}
// 	free(leido);
// 	return;
// }

void paquete(int conexion)
{
	void* leido = readline("> ");
	t_paquete* paquete = crear_paquete();

	while (strcmp("", leido)!=0){
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		leido = readline("> ");
	}

	enviar_paquete(paquete, conexion);
	free(leido);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{	
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(int conexion);


}