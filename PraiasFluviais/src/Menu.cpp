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
		case SERVICES:
			ServicesMenu();
			break;
		case DONE:
			return 1;
	}

	return 0;
}

void MainMenu() {

	std::cout << " - Main Menu - " << std::endl << std::endl;
	std::cout << " [1] Create praia " << std::endl;
	std::cout << " [2] Remove praia" << std::endl;
	std::cout << " [3] Edit praia" << std::endl;
	std::cout << " [4] Watch menu - change name plox" << std::endl;
	std::cout << " [5] Services menu" << std::endl;
	std::cout << " [0] Exit " << std::endl << std::endl;

	int valid;

	do {
		char input = _getch();

		valid = sendEvent(input);
	}
	while(!valid);
}

void AddMenu() {

	std::cout << " - Creator Menu - " << std::endl << std::endl;
	std::cout << " [1] Create praia - rio " << std::endl;
	std::cout << " [2] Create praia - albufeira " << std::endl;
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
			std::string i_name, i_concelho, i_typeS, i_nameS, i_dateS, i_capacity, i_bandeira, i_lat, i_lon, i_width, i_flow, i_depth;

			//Object's variables
			std::priority_queue<Service> services;
			std::priority_queue<Service> tmp_pq;
			HashTabService hs;
			unsigned int capacity;
			bool bandeira;
			double lat, lon, width, flow, depth;

			//Nome
			std::cout << " Name of praia: ";

			redo_name1:
			std::getline(std::cin, i_name);

			switch (inputHandling(i_name, 's')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_name1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			i_name = decapitalize(i_name);

			//Concelho
			std::cout << " Name of concelho: ";

			redo_concelho1:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_concelho1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			if(db.existPraia(i_name, i_concelho))
				throw PraiaAlreadyExists(i_name);

			i_concelho = decapitalize(i_concelho);

			//TODO
			//Servicos
			std::cout << " List of servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico1:
			Service new_service;
			service_t type;

			std::cout << " Servico numero " << cont_s + 1 << ": \n";

			std::cout << " Tipo (Restauracao, alojamento): ";
			std::getline(std::cin, i_typeS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico1;
			}

			switch (inputHandling(i_typeS, 's')) {
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

			type = to_enum(i_typeS);

			if(type == Null) {
				std::cerr << " # Input invalido.";
				goto redo_servico1;
			}

			std::cout << " Nome do servico: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
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

			new_service.setType(type);
			new_service.setName(i_nameS);

			//Check for duplicates in services
			tmp_pq = services;

			while(!tmp_pq.empty())
			{
				Service tmp_s = tmp_pq.top();
				if(new_service == tmp_s)
				{
					std::cerr << " # Servico já existe.";
					goto redo_servico1;
				}
				tmp_pq.pop();
			}

			cont_s++;
			services.push(new_service);
			goto redo_servico1;

			endservico1:
			//FIM -------------------------------------------------------

			//Capacity:
			std::cout << " Capacity of praia: ";

			redo_capacity1:
			std::getline(std::cin, i_capacity);

			switch (inputHandling(i_capacity, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_capacity1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_cap(i_capacity);
			iss_cap >> capacity;

			//Bandeira
			std::cout << " Bandeira (yes/no): ";

			redo_bandeira1:
			std::getline(std::cin, i_bandeira);

			//String "i_bandeira" to lower case
			std::transform(i_bandeira.begin(), i_bandeira.end(), i_bandeira.begin(), tolower);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_bandeira1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			if (i_bandeira == "yes")
				bandeira = true;
			else
				bandeira = false;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude1:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_latitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_latitude1;
			}

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude1:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_longitude1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			if (lon < -180 || lon > 180) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_longitude1;
			}

			//Width
			std::cout << " Width: ";

			redo_width:
			std::getline(std::cin, i_width);

			switch (inputHandling(i_width, 'd')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_width;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_width(i_width);
			iss_width >> width;

			//Flow
			std::cout << " Flow: ";

			redo_flow:
			std::getline(std::cin, i_flow);

			switch (inputHandling(i_flow, 'd')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_flow;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_flow(i_flow);
			iss_flow >> flow;

			//Depth
			std::cout << " Depth: ";

			redo_depth:
			std::getline(std::cin, i_depth);

			switch (inputHandling(i_depth, 'd')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_depth;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_depth(i_depth);
			iss_depth >> depth;

			Gps gps = Gps(lat, lon);

			Praia* p = new PRio(i_name, i_concelho, services, hs, capacity, bandeira, gps, width, flow, depth);


			//TODO
			//Set Praia nos servicos
//			for (size_t i = 0; i < services.size(); i++) {
//				servicos[i].setPraia(p);
//			}

			//Add praia
			db.addPraia(p);

			std::cout << " Added praia successfully. " << std::endl;

			break;
		}
		case '2': {

			//Input variables
			std::string i_name, i_concelho, i_typeS, i_nameS, i_dateS, i_capacity, i_bandeira, i_lat, i_lon, i_area;

			//Object's variables
			std::priority_queue<Service> services;
			std::priority_queue<Service> tmp_pq;
			HashTabService hs;
			unsigned int capacity;
			bool bandeira;
			double lat, lon, area;

			//Name
			std::cout << " Name of praia: ";

			redo_name2:
			std::getline(std::cin, i_name);

			switch (inputHandling(i_name, 's')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_name2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			i_name = decapitalize(i_name);

			//Concelho
			std::cout << " Name of concelho: ";

			redo_concelho2:
			std::getline(std::cin, i_concelho);

			switch (inputHandling(i_concelho, 's')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_concelho2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			if(db.existPraia(i_name, i_concelho))
				throw PraiaAlreadyExists(i_name);

			i_concelho = decapitalize(i_concelho);

			//Servicos
			std::cout << " Lista de servicos (CTRL-Z para terminar): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico2:
			Service new_serv;
			service_t type;

			std::cout << " Servico numero " << cont_s + 1 << ": \n";

			std::cout << " Tipo (Restauracao, alojamento): ";
			std::getline(std::cin, i_typeS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico2;
			}

			switch (inputHandling(i_typeS, 's')) {
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

			type = to_enum(i_typeS);

			if(type == Null) {
				std::cerr << " # Input invalido.";
				goto redo_servico2;
			}

			std::cout << " Nome do servico: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
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

			new_serv.setType(type);
			new_serv.setName(i_nameS);

			//Check for duplicates in services
			tmp_pq = services;

			while(!tmp_pq.empty())
			{
				Service tmp_s = tmp_pq.top();
				if(new_serv == tmp_s)
				{
					std::cerr << " # Servico já existe.";
					goto redo_servico2;
				}
				tmp_pq.pop();
			}

			cont_s++;
			services.push(new_serv);
			goto redo_servico2;

			endservico2:
			//FIM --------------------------------------------------------

			//Capacity:
			std::cout << " Capacity of praia: ";

			redo_capacity2:
			std::getline(std::cin, i_capacity);

			switch (inputHandling(i_capacity, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_capacity2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_cap(i_capacity);
			iss_cap >> capacity;

			//Bandeira
			std::cout << " Bandeira (yes/no): ";

			redo_bandeira2:
			std::getline(std::cin, i_bandeira);

			//String "i_bandeira" to lower case
			std::transform(i_bandeira.begin(), i_bandeira.end(), i_bandeira.begin(), tolower);

			switch (inputHandling(i_bandeira, 'b')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_bandeira2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			if (i_bandeira == "yes")
				bandeira = true;
			else
				bandeira = false;

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude2:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_latitude2;
			case 1:
				break;
			case 2:
				std::cerr << "# Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_latitude2;
			}

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude2:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_longitude2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			if (lon < -180 || lon > 180) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_longitude2;
			}

			//Area
			std::cout << " Area: ";

			redo_area:
			std::getline(std::cin, i_area);

			switch (inputHandling(i_area, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_area;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_area(i_area);
			iss_area >> area;

			Gps gps = Gps(lat, lon);

			Praia* p = new PAlbufeira(i_name, i_concelho, services, hs, capacity, bandeira, gps, area);

//			//Set Praia nos servicos
//			for (size_t i = 0; i < servicos.size(); i++) {
//				servicos[i].setPraia(p);
//			}

			//Add praia
			db.addPraia(p);

			std::cout << " Added praia successfully. " << std::endl;

			break;
		}
		default: {
			std::cout << " Choose one of the options! " << std::endl;
			goto again;
		}

	}
}

void RemoveMenu() {

	std::cout << " - Remove Menu - " << std::endl << std::endl;
	std::cout << " [1] Remove praia" << std::endl;
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
				std::cerr << " There are no praias to remove. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to remove: ";

			redo_index:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i < db.getSize()) {
				Praia* p = db.searchPraia(i);
				db.removePraia(p);
				std::cout << " Removed praia successfully. ";
				_getch();
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index;
			}

			break;
		}
		default: {
			std::cout << " Choose one of the options! " << std::endl;
			goto again;
		}
	}
}

void EditMenu() {

	std::cout << " - Edit Menu - " << std::endl << std::endl;
	std::cout << " [1] Edit name " << std::endl;
	std::cout << " [2] Edit concelho " << std::endl;
	std::cout << " [3] Edit capacity " << std::endl;
	std::cout << " [4] Edit bandeira azul " << std::endl;
	std::cout << " [5] Edit coordinates " << std::endl;
	std::cout << " [6] Edit area " << std::endl;
	std::cout << " [7] Edit width " << std::endl;
	std::cout << " [8] Edit flow " << std::endl;
	std::cout << " [9] Edit depth " << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			//Edit name
			std::string i_index, name;
			int index;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index1:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index1;
			}

			std::cout << " New name: ";

			redo_nome:
			std::getline(std::cin, name);

			switch (inputHandling(name, 's')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_nome;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled ";
				_getch();
				return;
			}

			name = decapitalize(name);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setName(name);
			else
				p1->setName(name);

			std::cout << " Name edited successfully. ";

			_getch();

			break;
		}
		case '2': {

			//Edit concelho
			std::string i_index, concelho;
			int index;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			} else
				std::cout << " Number of praia you want to edit: ";

			redo_index2:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index2;
			}

			std::cout << " New concelho: ";

			redo_concelho:
			std::getline(std::cin, concelho);

			switch (inputHandling(concelho, 's')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_concelho;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			concelho = decapitalize(concelho);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setConcelho(concelho);
			else
				p1->setConcelho(concelho);

			std::cout << " Concelho edited successfully. ";

			_getch();

			break;
		}
				  /*
		case '3': {

			//TODO create a menu for services maybe

			//Add service
			std::string i_index, i_typeS, i_nameS, i_dateS;
			int index;
			service_t type;
			Service new_service;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			} else
				std::cout << " Number of praia you want to edit: ";

			redo_index3:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index3;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index3;
			}

			redo_addserv_t:
			std::cout << " Type (Restauracao, alojamento): ";
			std::getline(std::cin, i_typeS);

			switch (inputHandling(i_typeS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_addserv_t;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			type = to_enum(i_typeS);

			if(type == Null) {
				std::cerr << " # Invalid input.";
				goto redo_addserv_t;
			}

			redo_addserv_n:
			std::cout << " Name of the service: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_addserv_n;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			new_service.setType(type);
			new_service.setName(i_nameS);

			Praia* p = db.searchPraia(i);

			//Check if there's a service like that in the object
			if (p->existService(new_service)) {
				std::cerr << " # Service already exists.";
				goto redo_addserv_t;
			}

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->addService(new_service);
			else
				p1->addService(new_service);

			std::cout << " Servicos editados com sucesso. \n";

			_getch();

			break;
		}
		*/
		case '3': {

			//Edit capacity
			std::string i_index, i_capacity;
			int index;
			unsigned int capacity;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index5:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_index5;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index5;
			}

			std::cout << " New capacity: ";

			redo_capacity:
			std::getline(std::cin, i_capacity);

			switch (inputHandling(i_capacity, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_capacity;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_cap(i_capacity);
			iss_cap >> capacity;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setCapacity(capacity);
			else
				p1->setCapacity(capacity);

			std::cout << " Capacity edited successfully. ";

			_getch();

			break;
		}
		case '4': {

			//Edit bandeira
			std::string i_index, i_bandeira;
			int index;
			bool bandeira;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index6:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index6;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index6;
			}

			std::cout << " New bandeira (yes/no): ";

			redo_bandeira:
			std::getline(std::cin, i_bandeira);

			switch (inputHandling(i_bandeira, 'b')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_bandeira;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_bandeira(i_bandeira);
			iss_bandeira >> bandeira;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setBandeira(bandeira);
			else
				p1->setBandeira(bandeira);

			std::cout << " Bandeira edited successfully. ";

			_getch();

			break;
		}
		case '5': {

			//Edit coordinates
			std::string i_index, i_lat, i_lon;
			int index;
			double lat, lon;

			//Display praias
			db.showPraias();

			if(db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index7:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
				case 0:
					std::cerr << " # Invalid input. Re-enter: ";
					goto redo_index7;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if(i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index7;
			}

			std::cout << " New latitude: ";

			redo_latitude:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'c')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_latitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_latitude(i_lat);
			iss_latitude >> lat;

			if (lat < -90 || lat > 90) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_latitude;
			}

			std::cout << " New longitude: ";

			redo_longitude:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'c')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_longitude;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_longitude(i_lon);
			iss_longitude >> lon;

			if (lon < -180 || lon > 180) {
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_longitude;
			}

			Gps coord = Gps(lat, lon);

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setGps(coord);
			else
				p1->setGps(coord);

			std::cout << " Coordi edited successfully. ";

			_getch();

			break;
		}
		case '6': {

			//Edit area
			std::string i_index, i_area;
			int index;
			double area;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index8:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_index8;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index8;
			}

			std::cout << " New area: ";

			redo_area:
			std::getline(std::cin, i_area);

			switch (inputHandling(i_area, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_area;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_area(i_area);
			iss_area >> area;

			Praia* p = db.searchPraia(i);

			PAlbufeira* p1 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				std::cout << " This praia is not an albufeira. ";
			else {
				p1->setArea(area);
				std::cout << " Area edit successfully. ";
			}

			_getch();

			break;

		}
		case '7': {

			//Edit width
			std::string i_index, i_width;
			int index;
			double width;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_index9:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_index9;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_index9;
			}

			std::cout << " New width: ";

			redo_width:
			std::getline(std::cin, i_width);

			switch (inputHandling(i_width, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_width;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_width(i_width);
			iss_width >> width;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verify class
			if (p1 == nullptr)
				std::cout << " This praia is not a rio. ";
			else {
				p1->setWidth(width);
				std::cout << " Width edited successfully. ";
			}

			_getch();

			break;

		}
		case '8': {

			//Edit flow
			std::string i_index, i_flow;
			int index;
			double flow;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_indexA:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_indexA;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_indexA;
			}

			std::cout << " New flow: ";

			redo_flow:
			std::getline(std::cin, i_flow);

			switch (inputHandling(i_flow, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_flow;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_flow(i_flow);
			iss_flow >> flow;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verify class
			if (p1 == nullptr)
				std::cout << " This praia is not a rio. ";
			else {
				p1->setFlow(flow);
				std::cout << " Flow edited successfully. ";
			}

			_getch();

			break;

		}
		case '9': {

			//Edit depth
			std::string i_index, i_depth;
			int index;
			double depth;

			//Display praias
			db.showPraias();

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to edit. ";
				_getch();
				return;
			}
			else
				std::cout << " Number of praia you want to edit: ";

			redo_indexB:
			std::getline(std::cin, i_index);

			switch (inputHandling(i_index, 'i')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_indexB;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_index(i_index);
			iss_index >> index;

			unsigned int i = index - 1;

			if (i >= 0 && i < db.getSize()) {
				//All good
			}
			else {
				std::cerr << " # There are no praias with that name. Re-enter: ";
				goto redo_indexB;
			}

			std::cout << " New depth: ";

			redo_depth:
			std::getline(std::cin, i_depth);

			switch (inputHandling(i_depth, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_depth;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			std::istringstream iss_depth(i_depth);
			iss_depth >> depth;

			Praia* p = db.searchPraia(i);

			PRio* p1 = dynamic_cast<PRio*>(p);

			//Verify class
			if (p1 == nullptr)
				std::cout << " This praia is not a rio. ";
			else {
				p1->setDepth(depth);
				std::cout << " Depth edited successfully. ";
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

				std::cout << " " << p->getName() << " (" << p->getConcelho() << ") : " << it->first << "\n";
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

			if (i >= 0 && i < db.getSize()) {
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

				std::cout << " " << p->getName() << " (" << p->getConcelho() << ") : " << it->first << "\n";
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

void ServicesMenu()
{
	std::cout << " - Services Menu - " << std::endl << std::endl;
	std::cout << " [1] Realizar inspecao" << std::endl;
	std::cout << " [2] Encerrar Servico" << std::endl;
	std::cout << " [3] Reabrir Servico" << std::endl;
	std::cout << " [4] Eliminar Servico" << std::endl;
	std::cout << " [5] Adicionar Servico" << std::endl;
	std::cout << " [6] Ver Servicos" << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again: char input = _getch();

	//So verifico se é para voltar para tras ou se é para continuar
	if (input == '0')
	{
		sendEvent('0');
		return;
	}

	if (input != '1' && input != '2' && input != '3' && input != '4' && input != '5' && input != '6')
	{
		std::cerr << " Escolha uma das opcoes! " << std::endl;
		goto again;
	}

	//Gota do this for all cases so might as well put in before the switch :)
	std::string ps_index, ss_index;
	int p_index, s_index;

	//Display praias
	db.showPraias();

	if (db.getSize() == 0) {
		std::cerr << " There are no praias to edit. ";
		_getch();
		return;
	}
	else
		std::cout << " Number of praia you want to edit: ";

make_inspection1:
	std::getline(std::cin, ps_index);

	switch (inputHandling(ps_index, 'i')) {
	case 0:
		std::cerr << " # Invalid input. Re-enter: ";
		goto make_inspection1;
	case 1:
		break;
	case 2:
		std::cerr << " # Operation cancelled. ";
		_getch();
		return;
	}

	std::istringstream iss_index(ps_index);
	iss_index >> p_index;

	unsigned int i = p_index - 1;

	if (i >= 0 && i < db.getSize()) {
		//All good
	}
	else {
		std::cerr << " # There are no praias with that index. Re-enter: ";
		goto make_inspection1;
	}
	Praia* tmp = db.searchPraia(i);

	Service s_tmp;

	if (input != '5')
	{
		//Show services
		tmp->showServices();

		if (input == '6')
			goto pass;

		if (tmp->getServices().size() == 0 && tmp->getServicesClosed().size() == 0) {
			std::cerr << " Nao existem servicos para inspecionar. ";
			_getch();
			return;
		}

	make_inspection2:
		std::getline(std::cin, ss_index);

		switch (inputHandling(ss_index, 'i')) {
		case 0:
			std::cerr << " # Input invalido. Introduza novamente: ";
			goto make_inspection2;
		case 1:
			break;
		case 2:
			std::cerr << " # Operacao cancelada. ";
			_getch();
			return;
		}

		std::istringstream iss_indexService(ss_index);
		iss_indexService >> s_index;

		unsigned int iService = s_index - 1;

		if (s_index >= 0 && s_index <= tmp->getServices().size() + tmp->getServicesClosed().size()) {
			//All good
		}
		else {
			std::cerr << " # Nao existe um servico com esse index. Introduza novamente: ";
			goto make_inspection2;
		}

		s_tmp = tmp->accessService(iService);
	}

pass:
	switch (input) {
		case '1': {
			//MAKE INSPECTION
			//Se nao estiver aberto nao pode inspecionar!
			if (s_tmp.getStatus().getClosed() != 0)
			{
				std::cerr << " # Nao pode inspecionar um servico fechado! Introduza novamente: ";
				goto make_inspection2;
			}

			PRio* p1 = dynamic_cast<PRio*>(tmp);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(tmp);

			//Verify class
			if (p1 == nullptr)
				std::cout << "Data de inspecao : " << p2->inspectionService(s_tmp) << "\n";
			else
				std::cout << "Data de inspecao : " << p1->inspectionService(s_tmp) << "\n";

			std::cout << " Servico inspecionado com sucesso. \n";

			_getch();

			break;
		}
		case '2': {
			//CLOSE SERVICE
			//Se nao estiver aberto nao pode fechar daaaa...
			if (s_tmp.getStatus().getClosed() != 0)
			{
				std::cerr << " # Servico atualmente fechado! Introduza novamente: ";
				goto make_inspection2;
			}

			PRio* p1 = dynamic_cast<PRio*>(tmp);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(tmp);

			std::cout << " Fechar :" << std::endl;
			std::cout << " [1] Temporariamente" << std::endl;
			std::cout << " [2] Permanentemente" << std::endl;

		closed_type:
			char cts = _getch();
	
			if (cts != '1' && cts != '2')
			{
				std::cerr << " Escolha uma das opcoes! " << std::endl;
				goto closed_type;
			}

			int cti;
			if (cts == '1')
				cti = 1;
			else
				cti = 2;

			//Verify class
			if (p1 == nullptr)
				std::cout << " Data de inspecao atualizada para : " << p2->closeService(s_tmp,cti) << "\n";
			else
				std::cout << " Data de inspecao atualizada para : " << p1->closeService(s_tmp,cti) << "\n";

			std::cout << " Servico fechado com sucesso. \n";

			_getch();

			break;
		}
		case '3' : {
			//OPEN SERVICE
			//Se nao estiver fechado nao pode abrir daaaa...
			if(s_tmp.getStatus().getClosed() == 0)
			{
				std::cerr << " # Servico atualmente aberto! Introduza novamente: ";
				goto make_inspection2;
			}

			if (s_tmp.getStatus().getClosed() == 2)
			{
				std::cerr << " # Servico PERMANENTEMENTE fechado! Introduza novamente: ";
				goto make_inspection2;
			}

			PRio* p1 = dynamic_cast<PRio*>(tmp);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(tmp);

			//Verify class
			if (p1 == nullptr)
				std::cout << " Data de inspecao atualizada para : " << p2->openService(s_tmp) << "\n";
			else
				std::cout << " Data de inspecao atualizada para : " << p1->openService(s_tmp) << "\n";

			std::cout << " Servico aberto com sucesso. \n";

			_getch();

			break;
		}
		case '4': {
			Service new_service();

			PRio* p1 = dynamic_cast<PRio*>(tmp);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(tmp);

			//Verify class
			if (p1 == nullptr)
				p2->removeService(s_tmp);
			else
				p1->removeService(s_tmp);

			std::cout << " Servicos editados com sucesso. \n";

			_getch();

			break;
		}
		case '5': {
			//Add service
			std::string i_typeS, i_nameS;
			int index;
			service_t type;
			Service new_service;

		addService:
			std::cout << " Type (Restauracao, alojamento, aluguer): ";
			std::getline(std::cin, i_typeS);

			switch (inputHandling(i_typeS, 's')) {
			case 0:
				std::cerr << " # Invalid input.";
				goto addService;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			type = to_enum(i_typeS);

			if (type == Null) {
				std::cerr << " # Invalid input.";
				goto addService;
			}

		redo_addserv_n:
			std::cout << " Name of the service: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
			case 0:
				std::cerr << " # Invalid input.";
				goto addService;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			new_service.setType(type);
			new_service.setName(i_nameS);

			//Check if there's a service like that in the object
			if (tmp->existService(new_service)) {
				std::cerr << " # Service already exists.";
				goto addService;
			}

			PRio* p1 = dynamic_cast<PRio*>(tmp);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(tmp);

			//Verify class
			if (p1 == nullptr)
				p2->addService(new_service);
			else
				p1->addService(new_service);

			std::cout << " Servicos editados com sucesso. \n";

			_getch();

			break;
		}
		case '6': {

			_getch();

			break;
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

	//Verficar caracteres estranhos na string (arrows, por exemplo)
	for (size_t i = 0; i < input.length(); i++) {
		if(input.at(i) != '.' && input.at(i) != '-' && !isalpha(input.at(i)) && !isdigit(input.at(i)))
			return 0;
	}

	bool dot = false;

	if (std::cin.eof() || input.length() == 0) {
		std::cin.clear();
		return 0;
	}
	else if (input.length() == 1 && input == "0" && property != 'c')
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
		if (input != "yes" && input != "no")
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
		case '5': {
			event_t event{GO_SERVICES};
			menuHandler(&event);
			break;
		}
		default:
			std::cout << " Escolha uma das opcoes! " << std::endl;
			return 0;
	}

	return 1;
}
