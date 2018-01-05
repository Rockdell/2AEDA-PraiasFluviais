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
		case ADD:
			AddMenu();
			break;
		case REMOVE:
			RemoveMenu();
			break;
		case EDIT:
			EditMenu();
			break;
		case SEARCH:
			SearchMenu();
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

	std::cout << " - Main Menu -" << std::endl << std::endl;
	std::cout << " [1] Create menu" << std::endl;
	std::cout << " [2] Remove menu" << std::endl;
	std::cout << " [3] Edit menu" << std::endl;
	std::cout << " [4] Search menu" << std::endl;
	std::cout << " [5] Service menu" << std::endl;
	std::cout << " [0] Exit" << std::endl << std::endl;

	int valid;

	do {
		char input = _getch();

		valid = sendEvent(input);
	}
	while(!valid);
}

void AddMenu() {

	std::cout << " - Create Menu - " << std::endl << std::endl;
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

			//Services
			std::cout << " List of services (CTRL-Z to end): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico1:
			Service new_service;
			service_t type;

			std::cout << " Service number " << cont_s + 1 << ": \n";

			std::cout << " Type (restauracao, alojamento, aluguer): ";
			std::getline(std::cin, i_typeS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico1;
			}

			switch (inputHandling(i_typeS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_servico1;
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
				goto redo_servico1;
			}

			std::cout << " Name of service: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_servico1;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
					_getch();
					return;
			}

			new_service.setType(type);
			new_service.setName(i_nameS);

			//Check for duplicates in services
			tmp_pq = services;

			while(!tmp_pq.empty()) {

				Service tmp_s = tmp_pq.top();

				if(new_service == tmp_s) {
					std::cerr << " # Service already exists.";
					goto redo_servico1;
				}

				tmp_pq.pop();
			}

			cont_s++;
			services.push(new_service);
			goto redo_servico1;

			endservico1:

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

			Praia* p = new PRio(i_name, i_concelho, services, capacity, bandeira, gps, width, flow, depth);

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

			//Services
			std::cout << " List of services (CTRL-Z to end): " << std::endl;
			unsigned int cont_s = 0;

			redo_servico2:
			Service new_serv;
			service_t type;

			std::cout << " Service number " << cont_s + 1 << ": \n";

			std::cout << " Type (restauracao, alojamento, aluguer): ";
			std::getline(std::cin, i_typeS);

			if (std::cin.eof())
			{
				std::cin.clear();
				goto endservico2;
			}

			switch (inputHandling(i_typeS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_servico2;
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
				goto redo_servico2;
			}

			std::cout << " Name of service: ";
			std::getline(std::cin, i_nameS);

			switch (inputHandling(i_nameS, 's')) {
				case 0:
					std::cerr << " # Invalid input.";
					goto redo_servico2;
				case 1:
					break;
				case 2:
					std::cerr << " # Operation cancelled. ";
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
					std::cerr << " # Service already exists.";
					goto redo_servico2;
				}
				tmp_pq.pop();
			}

			cont_s++;
			services.push(new_serv);
			goto redo_servico2;

			endservico2:

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

			Praia* p = new PAlbufeira(i_name, i_concelho, services, capacity, bandeira, gps, area);

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			db.removePraia(p);

			std::cout << " Removed praia successfully. ";

			_getch();

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit name
			std::string name;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit concelho
			std::string concelho;

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
		case '3': {

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit capacity
			std::string i_capacity;
			unsigned int capacity;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit bandeira
			std::string i_bandeira;
			bool bandeira;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit coordinates
			std::string i_lat, i_lon;
			double lat, lon;

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

			PRio* p1 = dynamic_cast<PRio*>(p);
			PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(p);

			//Verify class
			if (p1 == nullptr)
				p2->setGps(coord);
			else
				p1->setGps(coord);

			std::cout << " Coordinates edited successfully. ";

			_getch();

			break;
		}
		case '6': {

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit area
			std::string i_area;
			double area;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit width
			std::string i_width;
			double width;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit flow
			std::string i_flow;
			double flow;

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

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			//Edit depth
			std::string i_depth;
			double depth;

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
			std::cout << " Choose one of the options! " << std::endl;
			goto again;
		}
	}
}

void SearchMenu() {

	std::cout << " - Search Menu - " << std::endl << std::endl;
	std::cout << " [1] Search praia by name, for more info (sorted by concelho and bandeira)" << std::endl;
	std::cout << " [2] Search praia by name and concelho" << std::endl;
	std::cout << " [3] Search praia by coordinates" << std::endl;
	std::cout << " [4] Search for praias near an existent praia" << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch (input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			p->fullInfoPraia();

			_getch();

			break;
		}
		case '2': {

			std::string query_nome, query_concelho;

			if (db.getSize() == 0) {
				std::cerr << " There are no praias to search. ";
				_getch();
				return;
			}
			else
				std::cout << " Name of praia you want to search for: ";

			redo_nome:
			std::getline(std::cin, query_nome);

			switch (inputHandling(query_nome, 's')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_nome;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
				_getch();
				return;
			}

			query_nome = decapitalize(query_nome);

			std::cout << " Concelho of praia you want to search for: ";

			redo_concelho:
			std::getline(std::cin, query_concelho);

			switch (inputHandling(query_concelho, 's')) {
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

			query_concelho = decapitalize(query_concelho);

			iter_pair result = db.searchPraia(query_nome, query_concelho);

			if (result.second == -1)
				throw PraiaNotFound(query_nome);
			else {
				PRio* p1 = dynamic_cast<PRio*>(result.first->second[result.second]);
				PAlbufeira* p2 = dynamic_cast<PAlbufeira*>(result.first->second[result.second]);

				if (p1 == nullptr)
					p2->fullInfoPraia();
				else
					p1->fullInfoPraia();

				_getch();
			}

			break;
		}
		case '3': {
			
			std::string i_lat, i_lon, i_radius;
			double lat, lon, radius;

			if (db.getSize() <= 0) {
				std::cerr << " There are no praias to search.";
				_getch();
				return;
			}

			//Latitude
			std::cout << " Latitude: ";

			redo_latitude:
			std::getline(std::cin, i_lat);

			switch (inputHandling(i_lat, 'd')) {
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

			std::istringstream iss_lat(i_lat);
			iss_lat >> lat;

			//Longitude
			std::cout << " Longitude: ";

			redo_longitude:
			std::getline(std::cin, i_lon);

			switch (inputHandling(i_lon, 'd')) {
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

			std::istringstream iss_lon(i_lon);
			iss_lon >> lon;

			//Radius
			std::cout << " Radius of search: ";

			redo_radius1:
			std::getline(std::cin, i_radius);

			switch (inputHandling(i_radius, 'd')) {
			case 0:
				std::cerr << " # Invalid input: ";
				goto redo_radius1;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
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
					std::cout << " There are no praias in a radius of " << std::to_string(radius) << " from the coordinates.\n";
					std::cout << " All praias and their distances from the coordinates: \n";
					continue;
				}

				Praia* p = it->second;

				std::cout << " " << p->getName() << " (" << p->getConcelho() << ") : " << it->first << "\n";
			}

			_getch();
		
			break;
		}
		case '4': {

			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			std::string i_radius;
			double radius;

			//Radius
			std::cout << " Radius of search: ";

			redo_radius2:
			std::getline(std::cin, i_radius);

			switch (inputHandling(i_radius, 'd')) {
			case 0:
				std::cerr << " # Invalid input. Re-enter: ";
				goto redo_radius2;
			case 1:
				break;
			case 2:
				std::cerr << " # Operation cancelled. ";
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
					std::cout << " There are no praias in a radius of " << std::to_string(radius) << " from the original praia.\n";
					std::cout << " All praias and their distances to the original praia: \n";
					continue;
				}

				Praia* p = it->second;

				std::cout << " " << p->getName() << " (" << p->getConcelho() << ") : " << it->first << "\n";
			}

			_getch();

			break;

		}
		default: {
			std::cout << " Choose one of the options! " << std::endl;
			goto again;
		}
	}
}

void ServicesMenu()
{
	std::cout << " - Services Menu - " << std::endl << std::endl;
	std::cout << " [1] See services" << std::endl;
	std::cout << " [2] Add service" << std::endl;
	std::cout << " [3] Remove service" << std::endl;
	std::cout << " [4] Perform an inspection" << std::endl;
	std::cout << " [5] Re-open service" << std::endl;
	std::cout << " [6] Close service" << std::endl;
	std::cout << " [0] Back " << std::endl << std::endl;

	again:
	char input = _getch();

	switch(input) {
		case '0': {
			sendEvent('0');
			break;
		}
		case '1': {

			//Show services
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			p->showServices();
			
			_getch();

			break;
		}
		case '2': {

			//Add service
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			std::string i_typeS, i_nameS;
			service_t type;
			Service new_service;

			redo_addserv_t:
			std::cout << " Type (Restauracao, alojamento, aluguer): ";
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

			if (type == Null) {
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

			p->addServiceOpen(new_service);

			std::cout << " Service added successfully. ";

			_getch();

			break;
		}
		case '3': {

			//Remove service
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			if(p->showServices())
				return;

			Service s = selectService(p);

			if(s.getType() == Null)
				return;

			p->removeService(s);

			std::cout << " Service removed successfully. ";

			_getch();

			break;
		}
		case '4': {

			//Perform inspection
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			if(p->showServices())
				return;

			Service s = selectService(p);

			if(s.getType() == Null)
				return;

			if(!p->inspectionService(s))
				std::cout << " Service successfully inspected. ";

			_getch();

			break;
		}
		case '5': {

			//Re-open service
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			if(p->showServices())
				return;

			Service s = selectService(p);

			if(s.getType() == Null)
				return;

			if(!p->openService(s))
				std::cout << " Service re-opened successfully. ";

			_getch();

			break;
		}
		case '6': {

			//Close service
			Praia* p = selectPraia();

			if(p == nullptr)
				return;

			if(p->showServices())
				return;

			Service s = selectService(p);

			if(s.getType() == Null)
				return;

			std::cout << " [1] Temporarily" << std::endl;
			std::cout << " [2] Permanently" << std::endl;
			std::cout << " [0] Cancel" << std::endl;

			closed_type:
			std::cout << " Close: " << std::endl;
			char cts = _getch();

			unsigned int cti;

			switch(cts) {
				case '0': {
					return;
				}
				case '1': {
					cti = 1;
					break;
				}
				case '2': {
					cti = 2;
					break;
				}
				default: {
					std::cerr << " Choose one of the options! " << std::endl;
					goto closed_type;
				}
			}

			if(!p->closeService(s, cti))
				std::cout << " Service closed successfully. ";

			_getch();

			break;
		}
		default: {
			std::cout << " Choose one of the options! " << std::endl;
			goto again;
		}
	}
}

int inputHandling(std::string input, char property) {

	/*
	 PROPRIEDADES:
	 's' : nome, concelho, servico (string)
	 'c':  latitude, longitude (double)
	 'd' : area, largura, caudal, profundidade, raio (double)
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
			if (input.at(i) != '-' && !isalpha(input.at(i)))
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
			event_t event{GO_SEARCH};
			menuHandler(&event);
			break;
		}
		case '5': {
			event_t event{GO_SERVICES};
			menuHandler(&event);
			break;
		}
		default:
			std::cout << " Choose one of the options! " << std::endl;
			return 0;
	}

	return 1;
}

Praia* selectPraia() {

	std::string i_index;
	int p_index;

	//Display praias
	db.showPraias();

	if (db.getSize() == 0) {
		std::cerr << " There are no praias to select. ";
		_getch();
		return nullptr;
	}
	else
		std::cout << " Number of praia you want to select: ";

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
			return nullptr;
	}

	std::istringstream iss_p_index(i_index);
	iss_p_index >> p_index;

	unsigned int i = p_index - 1;

	if (i >= 0 && i < db.getSize()) {
		//All good
	}
	else {
		std::cerr << " # Choose a valid praia. Re-enter: ";
		goto redo_index;
	}

	Praia* p = db.searchPraia(i);

	return p;
}

Service selectService(Praia* p) {

	std::string i_index;
	unsigned int s_index;

	std::cout << " Number of service you want to select: ";

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
		return Service();
	}

	std::istringstream iss_indexService(i_index);
	iss_indexService >> s_index;

	unsigned int iService = s_index - 1;

	if (s_index >= 0 && s_index <= p->getServicesOpen().size() + p->getServicesClosed().size()) {
		//All good
	}
	else {
		std::cerr << " # Choose a valid service. Re-enter: ";
		goto redo_index;
	}

	Service s = p->accessService(iService);

	return s;
}
