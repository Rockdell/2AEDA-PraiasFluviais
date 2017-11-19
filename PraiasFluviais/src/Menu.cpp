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
	std::cout << " [1] Adicionar praia " << std::endl;
	std::cout << " [2] Adicionar data de outra database " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

}

void RemoveMenu() {

	std::cout << " - Remove Menu - " << std::endl << std::endl;
	std::cout << " [1] Remover Praia " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

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
			std::cout << "Please select one of the options." << std::endl;
			return 0;
	}

	return 1;
}

