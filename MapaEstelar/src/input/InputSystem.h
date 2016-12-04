#pragma once

#include <list>

#include "..\core\System.h"

class InputComponent;

typedef std::list<InputComponent*> InputList;

class InputSystem : public System {
public:
	InputSystem();

	//Prioridad para la recepción de mensajes de entrada
	//
	//TOP:    Se crea un nuevo nivel de prioridad, bloquea los anteriores
	//FREE:   Siempre recibe mensajes
	//EQUAL:  Se incorpora al nivel actual
	//ALL:    No utilizar
	enum class Priority {
		TOP,
		FREE,
		EQUAL,
		ALL
	};

	virtual int update();
	virtual int sendMessage(Message);

	//Funciones para escuchar eventos de entrada del sistema
	int subscribe(InputComponent*, Priority);
	int unsubscribe(InputComponent*);
private:
	std::list<InputList> priority_stack;
	InputList priority_free;

protected:
	int relayMessage(Message);
};