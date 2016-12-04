#pragma once

class GraphicComponent;
class InputComponent;

class Object {
public:
	Object(GraphicComponent* graphic = nullptr, InputComponent* input = nullptr) :
		graphic_component(graphic),
		input_component(input)
	{ }

	GraphicComponent* graphic_component;
	InputComponent*   input_component;
};