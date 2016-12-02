/* Para usar, simplemente crear la clase y llamar a la función
que se requiere, Name("SIGLA") para obtener el nombre y 
Description("SIGLA") para la descripción de Wikipedia. Notar
que la SIGLA es de 3 caracteres en mayúscula, en caso de ingresar
una que no exista o que haya algún error en el nombre o descripción
para esa constelación en la parte de la sigla ambas funciones 
retornan "Error check for: SIGLA"*/

#pragma once

#include <string>

class DataManager {
public:
	DataManager();
	~DataManager();
	std::string getName(std::string);
	std::string getDescription(std::string);
};