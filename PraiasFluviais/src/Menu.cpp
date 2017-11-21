#include "Menu.h"

#ifdef _WIN32
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif

int printMenu() {

	clearScreen();

	state_t state = getCurrentState();

	switch (state) {
		case INITIAL:
			MainMenu();
			break;
		case ADD: {
			AddMenu();
			break;
		}
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
		char input = _getch();
		valid = sendEvent(input);
	}
	while(!valid);
}

void AddMenu() {

	std::cout << " - Add Menu - " << std::endl << std::endl;
	std::cout << " [1] Adicionar praia - Rio " << std::endl;
	std::cout << " [2] Adicionar praia - Albufeira " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			//Input variables
			std::string i_nome, i_concelho, i_servico, i_bandeira, i_lat, i_lon, i_largura, i_caudal, i_profundidade;

			//Object's variables
			std::vector<std::string> servicos;
			bool bandeira;
			double lat, lon, largura, caudal, profundidade;

			//Nome
			std::cout << " Nome da praia: ";

			redo_nome1:
			std::getline(std::cin, i_nome);

			switch (inputHandling(i_nome, 's')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_nome1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			//Concelho
			std::cout << " Nome do concelho: ";

			redo_concelho1:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_concelho1;
				case 1:
					break;
				case 2:
					std::cerr << "Operação cancelada.\n";
					_getch();
					return;
			}

			//Servicos
			std::cout << " Lista de servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico1:
			std::cout << " Serviço número " << cont_s + 1 << ": ";
			std::getline(std::cin, i_servico);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico1;
			}

			switch (inputHandling(i_servico, 's')) {
				case 0:
					std::cerr << " # Input inválido.";
					goto redo_servico1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			cont_s++;
			servicos.push_back(i_servico);
			goto redo_servico1;

			endservico1:

			//Bandeira
			std::cout << " Bandeira (true/false): ";

			redo_bandeira1:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_bandeira1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude1:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'd')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_latitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude1:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'd')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_longitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			//Largura
			std::cout << " Largura: ";

			redo_largura:
			std::getline(std::cin, i_largura);

			switch (inputHandling(i_largura, 'd')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_largura;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_largura(i_largura);
			iss_largura >> largura;

			//Caudal
			std::cout << " Caudal: ";

			redo_caudal:
			std::getline(std::cin, i_caudal);

			switch (inputHandling(i_caudal, 'd')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_caudal;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_caudal(i_caudal);
			iss_caudal >> caudal;

			//Profundidade
			std::cout << " Profundidade: ";

			redo_profundidade:
			std::getline(std::cin, i_profundidade);

			switch (inputHandling(i_profundidade, 'd')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_profundidade;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_profundidade(i_profundidade);
			iss_profundidade >> profundidade;

			Gps g = Gps(lat, lon);
			Praia* p = new PRio(i_nome, i_concelho, servicos, bandeira, g, largura, caudal, profundidade);

			if(db.existPraia(p))
				throw PraiaAlreadyExists(i_nome);
			else
				db.addPraia(p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		case '2': {

			//Input variables
			std::string i_nome, i_concelho, i_servico, i_bandeira, i_lat, i_lon, i_area;

			//Object's variables
			std::vector<std::string> servicos;
			bool bandeira;
			double lat, lon, area;

			//Nome
			std::cout << " Nome da praia: ";

			redo_nome2:
			std::getline(std::cin, i_nome);

			switch (inputHandling(i_nome, 's')) {
			case 0:
				std::cerr << " # Input inválido. Introduza novamente: ";
				goto redo_nome2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operação cancelada. ";
				_getch();
				return;
			}

			//Concelho
			std::cout << " Nome do concelho: ";

			redo_concelho2:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
			case 0:
				std::cerr << " # Input inválido. Introduza novamente: ";
				goto redo_concelho2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operação cancelada. ";
				_getch();
				return;
			}

			//Servicos
			std::cout << " Lista de servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico2:
			std::cout << " Serviço número " << cont_s + 1 << ": ";
			std::getline(std::cin, i_servico);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico2;
			}

			switch (inputHandling(i_servico, 's')) {
				case 0:
					std::cerr << " # Input inválido.";
					goto redo_servico2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			cont_s++;
			servicos.push_back(i_servico);
			goto redo_servico2;

			endservico2:

			//Bandeira
			std::cout << " Bandeira (true/false): ";

			redo_bandeira2:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Input inválido. Introduza novamente: ";
					goto redo_bandeira2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operação cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude2:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'd')) {
			case 0:
				std::cerr << " # Input inválido. Introduza novamente: ";
				goto redo_latitude2;
			case 1:
				break;
			case 2:
				std::cerr << "# Operação cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude2:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'd')) {
			case 0:
				std::cerr << " # Input inválido. Introduza novamente: ";
				goto redo_longitude2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operação cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			//Area
			std::cout << " Area: ";

			redo_area:
			std::getline(std::cin, i_area);

			switch (inputHandling(i_area, 'd')) {
			case 0:
				std::cerr << " # Input inválido. Introduza novamente: ";
				goto redo_area;
			case 1:
				break;
			case 2:
				std::cerr << " # Operação cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_area(i_area);
			iss_area >> area;

			Gps g = Gps(lat, lon);
			Praia* p = new PAlbufeira(i_nome, i_concelho, servicos, bandeira, g, area);

			if(db.existPraia(p))
				throw PraiaAlreadyExists(i_nome);
			else
				db.addPraia(p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		default: {
			std::cout << " Escolha uma das opções! " << std::endl;
			goto again;
		}
	}

}

void RemoveMenu() {

	std::cout << " - Remove Menu - " << std::endl << std::endl;
	std::cout << " [1] Remover Praia " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

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

int inputHandling(std::string input, char property) {
	/*
		PROPRIEDADES:
		's' : nome, concelho, servico (string)
		'd' : latitude, longitude, area, largura, caudal, profundidade (double)
		'b' : bandeira (bool)

		RETURN:
		0 : Input inválido
		1 : Continuar operação
		2 : Cancelar operação
		*/

		if (std::cin.eof() || input.length() == 0)
		{
			std::cin.clear();
			return 0;
		}
		else if (input.length() == 1 && input == "0")
			return 2;

		switch (property)
		{
		case 's':
			for (size_t i = 0; i < input.length(); i++)
			{
				if (!isalpha(input.at(i)))
					return 0;
			}
			break;
		case 'd':
			for (size_t i = 0; i < input.length(); i++)
			{
				if (input.at(i) != '.' && !isdigit(input.at(i)))
					return 0;
			}
			break;
		case 'b':
			if(input != "false" && input != "true")
				return 0;
			break;
		}

		return 1;
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

