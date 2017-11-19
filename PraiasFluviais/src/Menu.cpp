#include "Menu.h"

int printMenu() {

	state_t state = getCurrentState();

	switch (state) {
		case INITIAL:
			MainMenu();
			break;
		case ADD:
			AddMenu();
			break;
		case REMOVE:
			RemoveMenu();
			break;
		case EDIT:
			EditMenu();
			break;
		case WATCH:
			WatchMenu();
			break;
		case DONE:
			return 1;
	}

	return 0;
}

void MainMenu() {


	std::cout << " - Main Menu - " << std::endl << std::endl;
	std::cout << " [1] Add Menu " << std::endl;
	std::cout << " [2] Remove Menu" << std::endl;
	std::cout << " [3] Edit Menu" << std::endl;
	std::cout << " [4] Look menu" << std::endl;
	std::cout << " [0] Exit " << std::endl << std::endl;

	int valid;

	do {
		char input = std::cin.get();
		valid = sendEvent(input);
	}
	while (!valid);
}

void AddMenu() {

	std::cout << " - Add Menu - " << std::endl << std::endl;
	std::cout << " [1] Adicionar praia - Rio " << std::endl;
	std::cout << " [2] Adicionar praia - Albufeira " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = std::cin.get();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {
			std::string nome, concelho;
			double lat, lon;
			float largura, caudal, profundidade;

			std::cout << " Nome da praia: ";
			std::cin >> nome;
			std::cout << " Nome do concelho: ";
			std::cin >> concelho;
			std::cout << " Latitude: ";
			std::cin >> lat;
			std::cout << " Longitude: ";
			std::cin >> lon;
			std::cout << " Largura: ";
			std::cin >> largura;
			std::cout << " Caudal: ";
			std::cin >> caudal;
			std::cout << " Profundidade: ";
			std::cin >> profundidade;

			Gps g = Gps(lat, lon);
			PRio p = PRio(nome, concelho, true, g, largura, caudal, profundidade);

			if(db.existPraia(&p))
				throw PraiaAlreadyExists(nome);
			else
				db.addPraia(&p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		case '2': {
			std::string nome, concelho;
			double lat, lon;
			float area;

			std::cout << " Nome da praia: ";
			std::cin >> nome;
			std::cout << " Nome do concelho: ";
			std::cin >> concelho;
			std::cout << " Latitude: ";
			std::cin >> lat;
			std::cout << " Longitude: ";
			std::cin >> lon;
			std::cout << " Area: ";
			std::cin >> area;

			Gps g = Gps(lat, lon);
			PAlbufeira p = PAlbufeira(nome, concelho, true, g, area);

			if(db.existPraia(&p))
				throw PraiaAlreadyExists(nome);
			else
				db.addPraia(&p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		default: {
			std::cout << " Escolha uma das opções! " << std::endl;
			std::cin.ignore();
			goto again;
		}
	}

}

void RemoveMenu() {

	std::cout << " - Remove Menu - " << std::endl << std::endl;
	std::cout << " [1] Remover Praia " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = std::cin.get();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {
			std::string nome;

			std::cout << " Nome da praia que pretende eliminar: ";
			std::cin >> nome;

			int i = db.searchPraia(nome);

			if(i != -1) {
				db.removePraia(i);
				std::cout << " Praia removida com sucesso. ";
			}
			else
				std::cout << " Não existe uma praia com esse nome. " << std::endl;

			break;
		}
		default: {
			std::cout << " Escolha uma das opções! " << std::endl;
			std::cin.ignore();
			goto again;
		}
	}

}

void EditMenu() {


	std::cout << " - Edit Menu - " << std::endl << std::endl;
	std::cout << " [1] Editar Praia " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;


}

void WatchMenu() {


	std::cout << " - Watch Menu - " << std::endl << std::endl;
	std::cout << " [1] Ver praias " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = std::cin.get();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {
			break;
		}
		default: {
			std::cout << " Escolha uma das opções! " << std::endl;
			std::cin.ignore();
			goto again;
		}
	}


}

int sendEvent(char c) {
	switch (c) {
		case '0': {
			event_t event{GO_BACK};
			menuHandler(&event);
			break;
		}
		case '1': {
			event_t event{GO_ADD};
			menuHandler(&event);
			break;
		}
		case '2': {
			event_t event{GO_REMOVE};
			menuHandler(&event);
			break;
		}
		case '3': {
			event_t event{GO_EDIT};
			menuHandler(&event);
			break;
		}
		case '4': {
			event_t event{GO_WATCH};
			menuHandler(&event);
			break;
		}
		default:
			std::cout << " Escolha uma das opções! " << std::endl;
			return 0;
	}

	return 1;
}

