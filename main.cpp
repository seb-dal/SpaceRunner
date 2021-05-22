//! \file tuto5.cpp utiliser mesh pour charger un objet .obj et le dessiner du point de vue d'une camera + controle de la camera a la souris

#include <runner/src/include/App_Runner.h>


int main(int argc, char** argv) {
	App_Runner runner(1024, 640);
	runner.run();
	runner.quit();
	return 0;
}