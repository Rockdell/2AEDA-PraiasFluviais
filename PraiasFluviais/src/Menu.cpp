#include "Menu.h"

#ifdef _WIN32
#define clearScreen() system("cls");
#else
#define clearScreen() system("clear");
#endif

extern Database db;

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
	std::cout << " [4] Watch menu" << std::endl;
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
	std::cout << " [1] Adicionar praia - rio " << std::endl;
	std::cout << " [2] Adicionar praia - albufeira " << std::endl;
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
			std::string i_nome, i_concelho, i_tipoS, i_nomeS, i_dataS, i_lotacao, i_bandeira, i_lat, i_lon, i_largura, i_caudal, i_profundidade;

			//Object's variables
			std::vector<Servico> servicos;
			int lotacao;
			bool bandeira;
			double lat, lon, largura, caudal, profundidade;

			//Nome
			std::cout << " Nome da praia: ";

			redo_nome1:
			std::getline(std::cin, i_nome);

			switch (inputHandling(i_nome, 's')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_nome1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			i_nome = decapitalize(i_nome);

			//Concelho
			std::cout << " Nome do concelho: ";

			redo_concelho1:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_concelho1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada.\n";
					_getch();
					return;
			}

			if(db.existPraia(i_nome, i_concelho))
				throw PraiaAlreadyExists(i_nome);

			i_concelho = decapitalize(i_concelho);

			//TODO search servico already exists
			//Servicos
			std::cout << " Lista de servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico1:
			Servico new_serv;
			servico_t tipo;

			std::cout << " Servico numero " << cont_s + 1 << ": \n";

			std::cout << " Tipo (Restauracao, alojamento): ";
			std::getline(std::cin, i_tipoS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico1;
			}

			switch (inputHandling(i_tipoS, 's')) {
				case 0:
					std::cerr << " # Input invalido.";
					goto redo_servico1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			tipo = to_enum(i_tipoS);

			if(tipo == Null) {
				std::cerr << " # Input invalido.";
				goto redo_servico1;
			}

			std::cout << " Nome do servico: ";
			std::getline(std::cin, i_nomeS);

			switch (inputHandling(i_nomeS, 's')) {
				case 0:
					std::cerr << " # Input invalido.";
					goto redo_servico1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			new_serv.setTipo(tipo);
			new_serv.setNome(i_nomeS);

			cont_s++;
			servicos.push_back(new_serv);
			goto redo_servico1;

			endservico1:

			//Lotacao:
			std::cout << " Lotacao da praia: ";

			redo_lotacao1:
			std::getline(std::cin, i_lotacao);

			switch (inputHandling(i_lotacao, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_lotacao1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lot(i_lotacao);
			iss_lot >> lotacao;

			//Bandeira
			std::cout << " Bandeira (true/false): ";

			redo_bandeira1:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_bandeira1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude1:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_latitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude1;
			}

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude1:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_longitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			if (lat < -180 || lat > 180) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude1;
			}

			//Largura
			std::cout << " Largura: ";

			redo_largura:
			std::getline(std::cin, i_largura);

			switch (inputHandling(i_largura, 'd')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_largura;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
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
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_caudal;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
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
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_profundidade;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_profundidade(i_profundidade);
			iss_profundidade >> profundidade;

			Gps g = Gps(lat, lon);
			Praia* p = new PRio(i_nome, i_concelho, servicos, lotacao, bandeira, g, largura, caudal, profundidade);

			//Set Praia nos servicos
			for (size_t i = 0; i < servicos.size(); i++) {
				servicos[i].setPraia(p);
			}

			//Add praia
			db.addPraia(p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		case '2': {

			//Input variables
			std::string i_nome, i_concelho, i_tipoS, i_nomeS, i_dataS, i_lotacao, i_bandeira, i_lat, i_lon, i_area;

			//Object's variables
			std::vector<Servico> servicos;
			int lotacao;
			bool bandeira;
			double lat, lon, area;

			//Nome
			std::cout << " Nome da praia: ";

			redo_nome2:
			std::getline(std::cin, i_nome);

			switch (inputHandling(i_nome, 's')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_nome2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			i_nome = decapitalize(i_nome);

			//Concelho
			std::cout << " Nome do concelho: ";

			redo_concelho2:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_concelho2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			if(db.existPraia(i_nome, i_concelho))
				throw PraiaAlreadyExists(i_nome);

			i_concelho = decapitalize(i_concelho);

			//TODO search servico already exists
			//Servicos
			std::cout << " Lista de servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico2:
			Servico new_serv;
			servico_t tipo;

			std::cout << " Servico numero " << cont_s + 1 << ": \n";

			std::cout << " Tipo (Restauracao, alojamento): ";
			std::getline(std::cin, i_tipoS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico2;
			}

			switch (inputHandling(i_tipoS, 's')) {
				case 0:
					std::cerr << " # Input invalido.";
					goto redo_servico2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			tipo = to_enum(i_tipoS);

			if(tipo == Null) {
				std::cerr << " # Input invalido.";
				goto redo_servico2;
			}

			std::cout << " Nome do servico: ";
			std::getline(std::cin, i_nomeS);

			switch (inputHandling(i_nomeS, 's')) {
				case 0:
					std::cerr << " # Input invalido.";
					goto redo_servico2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			new_serv.setTipo(tipo);
			new_serv.setNome(i_nomeS);

			cont_s++;
			servicos.push_back(new_serv);
			goto redo_servico2;

			endservico2:

			//Lotacao:
			std::cout << " Lotacao da praia: ";

			redo_lotacao2:
			std::getline(std::cin, i_lotacao);

			switch (inputHandling(i_lotacao, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_lotacao2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_lot(i_lotacao);
			iss_lot >> lotacao;

			//Bandeira
			std::cout << " Bandeira (true/false): ";

			redo_bandeira2:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_bandeira2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude2:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude2;
			case 1:
				break;
			case 2:
				std::cerr << "# Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude2;
			}

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude2:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			if (lon < -180 || lon > 180) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude2;
			}

			//Area
			std::cout << " Area: ";

			redo_area:
			std::getline(std::cin, i_area);

			switch (inputHandling(i_area, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_area;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_area(i_area);
			iss_area >> area;

			Gps g = Gps(lat, lon);
			Praia* p = new PAlbufeira(i_nome, i_concelho, servicos, lotacao, bandeira, g, area);

			//Set Praia nos servicos
			for (size_t i = 0; i < servicos.size(); i++) {
				servicos[i].setPraia(p);
			}

			//Add praia
			db.addPraia(p);

			std::cout << " Praia adicionada com sucesso. " << std::endl;

			break;
		}
		default: {
			std::cout << " Escolha uma das opcoes! " << std::endl;
			goto again;
		}
	}

}

void RemoveMenu() {

	std::cout << " - Remove Menu - " << std::endl << std::endl;
	std::cout << " [1] Remover Praia" << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			std::string i_index;
			int index;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " Nao existem praias para remover. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende remover: ";

			redo_index:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i <= db.getSize()) {
				Praia* p = db.searchPraia(i);
				db.removePraia(p);
				std::cout << " Praia removida com sucesso. ";
				_getch();
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index;
			}

			break;
		}
		default: {
			std::cout << " Escolha uma das opcoes! " << std::endl;
			goto again;
		}
	}
}

void EditMenu() {

	std::cout << " - Edit Menu - " << std::endl << std::endl;
	std::cout << " [1] Editar nome " << std::endl;
	std::cout << " [2] Editar concelho " << std::endl;
	std::cout << " [3] Editar servicos " << std::endl;
	std::cout << " [4] Editar lotacao " << std::endl;
	std::cout << " [5] Editar bandeira azul " << std::endl;
	std::cout << " [6] Editar coordenadas " << std::endl;
	std::cout << " [7] Editar area " << std::endl;
	std::cout << " [8] Editar largura " << std::endl;
	std::cout << " [9] Editar caudal " << std::endl;
	std::cout << " [A] Editar profundidade " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	if (isalpha(input))
		input = toupper(input);

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			std::string i_index, nome;
			int index;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index1:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index1;
			}

			std::cout << " Novo nome: ";

			redo_nome:
			std::getline(std::cin, nome);

			switch (inputHandling(nome, 's')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_nome;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			nome = decapitalize(nome);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				p2->setNome(nome);
			else
				p1->setNome(nome);

			std::cout << " Nome editado com sucesso. \n";

			_getch();

			break;
		}
		case '2': {

			std::string i_index, concelho;
			int index;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			} else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index2:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index2;
			}

			std::cout << " Novo concelho: ";

			redo_concelho:
			std::getline(std::cin, concelho);

			switch (inputHandling(concelho, 's')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_concelho;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			concelho = decapitalize(concelho);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				p2->setConcelho(concelho);
			else
				p1->setConcelho(concelho);

			std::cout << " Concelho editado com sucesso. \n";

			_getch();

			break;
		}
		case '3': {

//			std::string i_index, i_servico;
//			int index;
//			std::vector<Servico> servicos;

			//TODO
//			//Display praias
//			db.showPraias();
//
//			if (db.getSize() == 0) {
//				std::cerr << " Nao existem praias para editar. ";
//				_getch();
//				return;
//			} else
//				std::cout << "Numero da praia que pretende editar: ";
//
//			redo_index3:
//			std::getline(std::cin, i_index);
//
//			switch (inputHandling(i_index, 'i')) {
//				case 0:
//					std::cerr << " # Input invalido. Introduza novamente: ";
//					goto redo_index3;
//				case 1:
//					break;
//				case 2:
//					std::cerr << " # Operacao cancelada. ";
//					_getch();
//					return;
//			}
//
//			std::istringstream iss_index(i_index);
//			iss_index >> index;
//
//			unsigned int i = index - 1;
//
//			if (i >= 0 && i <= db.getSize()) {
//				//All good
//			}
//			else {
//				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
//				goto redo_index3;
//			}
//
//			std::cout << " Lista de novos servicos (CTRL-Z para terminar): " << std::endl;
//			unsigned int cont_s = 0;
//
//			redo_servico:
//			std::cout << " Serviço Numero " << cont_s + 1 << ": ";
//			std::getline(std::cin, i_servico);
//
//			if (std::cin.eof())
//			{
//				std::cin.clear();
//				goto endservico;
//			}
//
//			switch (inputHandling(i_servico, 's')) {
//				case 0:
//					std::cerr << " # Input invalido.";
//					goto redo_servico;
//				case 1:
//					break;
//				case 2:
//					std::cerr << " # Operacao cancelada. ";
//					_getch();
//					return;
//			}
//
//			cont_s++;
//			servicos.push_back(i_servico);
//			goto redo_servico;
//
//			endservico:
//
//			Praia* p = db.searchPraia(i);
//
//			PRio* p1 = dynamic_cast<PRio*>(p);
//			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);
//
//			//Verificar class
//			if (p1 == nullptr)
//				p2->setServicos(servicos);
//			else
//				p1->setServicos(servicos);
//
//			std::cout << " Servicos editados com sucesso. \n";
//
//			_getch();

			break;
		}
		case '4': {

			std::string i_index, i_lotacao;
			int index, lotacao;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index4:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_index4;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index4;
			}

			std::cout << " Nova lotacao: ";

			redo_lotacao:
			std::getline(std::cin, i_lotacao);

			switch (inputHandling(i_lotacao, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_lotacao;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lotacao(i_lotacao);
			iss_lotacao >> lotacao;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				p2->setLotacao(lotacao);
			else
				p1->setLotacao(lotacao);

			std::cout << " Lotacao editada com sucesso. \n";

			_getch();

			break;
		}
		case '5': {
			std::string i_index, i_bandeira;
			int index;
			bool bandeira;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index5:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index5;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index5;
			}

			std::cout << " Nova bandeira (true/false): ";

			redo_bandeira:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_bandeira;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				p2->setBandeira(bandeira);
			else
				p1->setBandeira(bandeira);

			std::cout << " Bandeira editada com sucesso. \n";

			_getch();

			break;
		}
		case '6': {

			std::string i_index, i_lat, i_lon;
			int index;
			double lat, lon;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index6:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index6;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index6;
			}

			std::cout << " Nova latitude: ";

			redo_latitude:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_latitude(i_lat);
			iss_latitude >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude;
			}

			std::cout << " Nova longitude: ";

			redo_longitude:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_longitude(i_lon);
			iss_longitude >> lon;

			if (lon < -180 || lon > 180) {
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude;
			}

			Gps coord = Gps(lat, lon);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				p2->setGps(coord);
			else
				p1->setGps(coord);

			std::cout << " Gps editado com sucesso. \n";

			_getch();

			break;
		}
		case '7': {

			std::string i_index, i_area;
			int index;
			double area;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index7:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_index7;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index7;
			}

			std::cout << " Nova area: ";

			redo_area:
			std::getline(std::cin, i_area);

			switch (inputHandling(i_area, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_area;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_area(i_area);
			iss_area >> area;

			Praia* p = db.searchPraia(i);

			PAlbufeira* p1 = dynamic_cast<PAlbufeira*>(p);

			//Verificar class
			if (p1 == nullptr)
				std::cout << " A praia escolhida nao e uma albufeira. \n";
			else {
				p1->setArea(area);
				std::cout << " Area editada com sucesso. \n";
			}

			_getch();

			break;

		}
		case '8': {

			std::string i_index, i_largura;
			int index;
			double largura;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index8:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_index8;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index8;
			}

			std::cout << " Nova largura: ";

			redo_largura:
			std::getline(std::cin, i_largura);

			switch (inputHandling(i_largura, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_largura;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_largura(i_largura);
			iss_largura >> largura;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verificar class
			if (p1 == nullptr)
				std::cout << " A praia escolhida nao e um rio. \n";
			else {
				p1->setLargura(largura);
				std::cout << " Largura editada com sucesso. \n";
			}

			_getch();

			break;

		}
		case '9': {

			std::string i_index, i_caudal;
			int index;
			double caudal;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_index9:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_index9;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index9;
			}

			std::cout << " Nova largura: ";

			redo_caudal:
			std::getline(std::cin, i_caudal);

			switch (inputHandling(i_caudal, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_caudal;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_caudal(i_caudal);
			iss_caudal >> caudal;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verificar class
			if (p1 == nullptr)
				std::cout << " A praia escolhida nao e um rio. \n";
			else {
				p1->setCaudal(caudal);
				std::cout << " Caudal editada com sucesso. \n";
			}

			_getch();

			break;

		}
		case 'A': {

			std::string i_index, i_profundidade;
			int index;
			double profundidade;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para editar. ";
				_getch();
				return;
			}
			else
				std::cout << "Numero da praia que pretende editar: ";

			redo_indexA:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_indexA;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_indexA;
			}

			std::cout << " Nova profundidade: ";

			redo_profundidade:
			std::getline(std::cin, i_profundidade);

			switch (inputHandling(i_profundidade, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_profundidade;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_profundidade(i_profundidade);
			iss_profundidade >> profundidade;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verificar class
			if (p1 == nullptr)
				std::cout << " A praia escolhida nao e um rio. \n";
			else {
				p1->setProfundidade(profundidade);
				std::cout << "Profundidade editada com sucesso. \n";
			}

			_getch();

			break;

		}
		default: {
			std::cout << " Escolha uma das opcoes! " << std::endl;
			goto again;
		}
	}
}

void WatchMenu() {

	std::cout << " - Watch Menu - " << std::endl << std::endl;
	std::cout << " [1] Ver praias por nome (ordenadas por concelho)" << std::endl;
	std::cout << " [2] Pesquisar praia pelo nome e concelho" << std::endl;
	std::cout << " [3] Pesquisar praia por coordenadas GPS" << std::endl;
	std::cout << " [4] Pesquisar praias nas proximidades de uma praia existente" << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			std::string i_index;
			int index;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " Nao existem praias para mostrar. ";
				_getch();
				return;
			}
			else
				std::cout << " Numero da praia que pretende ver mais informacao: ";

			redo_index1:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Input invalido. Introduza novamente: ";
					goto redo_index1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operacao cancelada. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i < db.getSize()) {
				Praia* p = db.searchPraia(i);
				std::cout << p->fullInfoPraia() << std::endl;
				_getch();
				return;
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index1;
			}

			break;
		}
		case '2': {

			std::string query_nome, query_concelho;

			if (db.getSize() == 0) {
				std::cerr << " Nao existem praias para pesquisar. ";
				_getch();
				return;
			}
			else
				std::cout << " Qual o nome da praia que pretende pesquisar: ";

			redo_nome:
			std::getline(std::cin, query_nome);

			switch (inputHandling(query_nome, 's')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_nome;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			query_nome = decapitalize(query_nome);

			std::cout << " Qual o nome do concelho da praia que pretende pesquisar: ";

			redo_concelho:
			std::getline(std::cin, query_concelho);

			switch (inputHandling(query_concelho, 's')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_concelho;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			query_concelho = decapitalize(query_concelho);

			iter_pair result = db.searchPraia(query_nome, query_concelho);

			if (result.second == -1)
				throw PraiaNotFound(query_nome);
			else {
				PRio* p1 = dynamic_cast<PRio*>(result.first->second[result.second]);
				PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(result.first->second[result.second]);

				if (p1 == nullptr)
					std::cout << p2->fullInfoPraia() << std::endl;
				else
					std::cout << p1->fullInfoPraia() << std::endl;

				_getch();
			}

			break;
		}
		case '3': {
			
			std::string i_lat, i_lon, i_radius;
			double lat, lon, radius;

			if (db.getSize() <= 0) {
				std::cerr << " Nao existem praias para pesquisar. ";
				_getch();
				return;
			}

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_latitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_longitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			//Radius
			std::cout << " Radius of search: ";

			redo_radius1:
			std::getline(std::cin, i_radius);

			switch (inputHandling(i_radius, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_radius1;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_radius(i_radius);
			iss_radius >> radius;

			Gps coord = Gps(lat, lon);

			auto result = db.withInRangeGps(coord, radius);

			//Formatting
			std::cout << std::endl;

			for (auto it = result.begin(); it != result.end(); it++) {

				if (it == result.begin() && it->first == -1) {
					std::cout << " Nao existem praias num raio de " << std::to_string(radius) << " das coordenadas.\n";
					std::cout << " Todas as praias e respetivas distancias as coordenadas: \n";
					continue;
				}

				Praia* p = it->second;

				std::cout << " " << p->getNome() << " (" << p->getConcelho() << ") : " << it->first << "\n";
			}

			_getch();
		
			break;
		}
		case '4': {

			std::string i_index, i_radius;
			int index;
			double radius;

			//Display praias
			db.showPraias();

			if (db.getSize() <= 1) {
				std::cerr << " Nao existem praias para pesquisar. ";
				_getch();
				return;
			}
			else
				std::cout << " Numero da praia a partir da qual pretende pesquisar: ";

		redo_index2:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_index2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i <= db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # Nao existe uma praia com esse nome. Introduza novamente: ";
				goto redo_index2;
			}

			//Praia where we will search from
			Praia* p = db.searchPraia(i);

			//Radius
			std::cout << " Radius of search: ";

			redo_radius2:
			std::getline(std::cin, i_radius);

			switch (inputHandling(i_radius, 'd')) {
			case 0:
				std::cerr << " # Input invalido. Introduza novamente: ";
				goto redo_radius2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operacao cancelada. ";
				_getch();
				return;
			}

			std::istringstream iss_radius(i_radius);
			iss_radius >> radius;

			auto result = db.withInRangePraia(p, radius);

			//Formatting
			std::cout << std::endl;

			for (auto it = result.begin(); it != result.end(); it++) {

				if (it == result.begin() && it->first == -1) {
					std::cout << " Nao existem praias num raio de " << std::to_string(radius) << " das coordenadas.\n";
					std::cout << " Todas as praias e respetivas distancias as coordenadas: \n";
					continue;
				}

				Praia* p = it->second;

				std::cout << " " << p->getNome() << " (" << p->getConcelho() << ") : " << it->first << "\n";
			}

			_getch();

			break;

		}
		default: {
			std::cout << " Escolha uma das opcoes! " << std::endl;
			goto again;
		}
	}
}

int inputHandling(std::string input, char property) {
	/*
	 PROPRIEDADES:
	 's' : nome, concelho, servico (string)
	 'c':  latitude, longitude (double)
	 'd' : area, largura, caudal, profundidade (double)
	 'b' : bandeira (bool)
	 'i' : indices (int)
	 RETURN:
	 0 : Input invalido
	 1 : Continuar Operacao
	 2 : Cancelar Operacao
	 */

	bool dot = false;

	if (std::cin.eof() || input.length() == 0) {
		std::cin.clear();
		return 0;
	}
	else if (input.length() == 1 && input == "0")
		return 2;
	else if (input.at(0) == ' ' || input.at(0) == '.')
		return 0;
	else if(input.length() == 1 && input.at(0) == '-')
		return 0;
	else if(input.length() > 1 && input.at(0) == '-' && input.at(1) == '.')
		return 0;

	switch (property) {
	case 's':
		for (size_t i = 0; i < input.length(); i++) {
			if (input.at(i) != ' ' && input.at(i) != '-' && !isalpha(input.at(i)))
				return 0;
		}
		break;
	case 'c':
		for (size_t i = 0; i < input.length(); i++) {
			if (input.at(i) == '-') {
				if(i != 0)
					return 0;
				else
					continue;
			}
			else if (input.at(i) == '.') {
				if (!dot) {
					if (i != 0 && input.at(i-1) == '-')
						return 0;
					else
						dot = true;
				}
				else
					return 0;
			}
			else if (!isdigit(input.at(i)))
				return 0;
		}
		break;
	case 'd':
		for(size_t i = 0; i < input.length(); i++) {
			if (input.at(i) == '.') {
				if (!dot)
					dot = true;
				else
					return 0;
			}
			else if (!isdigit(input.at(i)))
				return 0;
		}
		break;
	case 'b':
		if (input != "false" && input != "true")
			return 0;
		break;
	case 'i':
		for (size_t i = 0; i < input.length(); i++) {
			if (!isdigit(input.at(i)))
				return 0;
		}
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
			std::cout << " Escolha uma das opcoes! " << std::endl;
			return 0;
	}

	return 1;
}
