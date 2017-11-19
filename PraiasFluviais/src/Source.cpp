#include "Menu.h"
#include "Gps.h"
#include "Globals.h"

int main() {
	/*
	* No sentido de fomentar o turismo do tipo â€œvÃ¡ para fora cÃ¡ dentroâ€�, a AssociaÃ§Ã£o Nacional de MunicÃ­pios
	Portugueses resolveu criar um guia de lazer com as praias fluviais existentes nos diferentes concelhos
	portugueses.
	* Cada praia fluvial, situada num concelho especÃ­fico, tem coordenadas GPS, pode ter bandeira azul e alguns serviÃ§os no local
	(nadador-salvador, cafÃ©, restaurante, aluguer de embarcaÃ§Ãµes de recreaÃ§Ã£o, etc) e uma capacidade mÃ¡xima indicativa.
	* As praias fluviais baseadas em rios tÃªm uma largura, caudal e profundidade mÃ¡xima. As praias fluviais incorporadas em albufeiras
 	tÃªm uma Ã¡rea aquÃ¡tica utilizÃ¡vel.
	* Para cada praia fluvial interessa saber quais os pontos turÃ­sticos de interesse nas proximidades, bem como restaurantes e
	alojamento recomendados.
	* As praias fluviais devem estar agrupadas por concelho. Por outro lado, interessa tambÃ©m saber qual Ã© a praia fluvial mais
	prÃ³xima de um determinado local (p.ex., de outra praia fluvial, que poderÃ¡ estar num concelho diferente).
	 */

	/* Classes a implementar:
	 * Praia
	 * Concelho
	 * Bandeira Azul
	 * GPS
	 * ServiÃ§os
	 * ExcepcÃµes
	 */

	/* Guardar data:
	 * Usar JSON strings para guardar em ficheiros .json
	 */

	/* Flow dos menus:
	 * State machine
	 */

	/* General functions:
	 * static class
	 * static functions
	 * new namespace
	 * global namespace
	 * c
	 */

	Database db;

	//db.load("listaPraias.txt");

	unsigned int stop = 0;

	while(!stop) {
		stop = printMenu();
		std::cin.ignore();
	}

	//db.save("listPraias.txt");

	return 0;
}
;
