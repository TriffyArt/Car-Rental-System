/*
 * CAR RENTAL SYSTEM using DevC++11
 *
 *   Copyright (c) 2024 Psalm Salcedo
 *   All rights reserved.
 */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <vector>

using namespace std;

class rental {
private:
    int ccode;
    int cyear;
    int price;
    string cname;

public:
    void menu();
    void administrator();
    void renter();
    void addcar();
    void editcar();
    void rem();
    void listofcars(bool clearScreenAndPause = true);
    void receipt();
    void showRentedCars();
    void returnCar(int ccode);
    void saveRentedCarsToFile();
    void loadRentedCarsFromFile();
    void availableCarsList(bool clearScreenAndPause = true);
};

class RentalRecord {
public:
    int carCode;
    int rentalDays;
    string renterName;
    string renterContact;
    string renterAddress;
    RentalRecord(int code, int days, string name, string contact, string address)
    	: carCode(code), rentalDays(days), renterName(name), renterContact(contact), renterAddress(address){}
};

vector<RentalRecord> rentedCars;

void rental :: menu (){
	m:
	int choice;
	string username;
	string password;
	loadRentedCarsFromFile();
		
		cout<<"*********************\n";
		cout<<"                     \n";
		cout<<"      MAIN MENU      \n";
		cout<<"                     \n";
		cout<<"1. Administrator     \n";
		cout<<"2. Renter            \n";
		cout<<"3. Exit              \n";
		cout<<"                     \n";
		cout<<"*********************\n";
		cout<<"Select options (1-3) : ";
		cin>> choice;
		
	system("CLS");
		
	switch (choice) {
	case 1: { 
		
		char ch;
	
		cout<<"Login Here. \n";
		cout<<"Enter Username : ";
		cin>>username;
		
		cout<<"Enter Password : ";

		ch=_getch();
		while(ch != 13){
			password.push_back(ch);
			cout<<'*';
			ch=_getch();
		}
		
		if (username =="123" && password =="123") {
			cout<<"\n\nACCESS GRANTED!!\n\n";
			system("PAUSE");
			system("CLS");
			administrator();
		}else{
			cout<<"\n\nInvalid Username | Password: \n";
			system("PAUSE");
			system("CLS");
		}
		break;
	}
	case 2: {
		renter();
		break;
	}
	case 3: {
		saveRentedCarsToFile();
		exit(0);
	}
	default: {
		cout<<"Select from the given option. ";
	}
}
	goto m;
	
	
}


void rental :: administrator (){
	m:
	int choice;
		cout<<"*********************\n";
		cout<<"                     \n";
		cout<<"     ADMNISTRATOR    \n";
		cout<<"                     \n";
		cout<<"1. Add a Car         \n";
		cout<<"2. Edit Car Details  \n";
		cout<<"3. Delete a Car      \n";
		cout<<"4. Show Car List     \n";
		cout<<"5. Show Rented Cars  \n";
		cout<<"6. Show Available Cars\n";
		cout<<"7. Back to main menu \n";
		cout<<"                     \n";
		cout<<"*********************\n";
		cout<<"Select options (1-5) : ";
		cin>> choice;
		
		system("CLS");
		
		switch (choice) {
			case 1:
				addcar();
				break;
			case 2:
				editcar();
				break;
			case 3:
				rem();
				break;
			case 4:
				listofcars();
				break;
			case 5:
				showRentedCars();
				break;
			case 6:
				availableCarsList();
				break;
			case 7:
				menu();
				break;
			default:
				cout<<"Invalid..";
		}
	goto m;	
}

void rental::renter() {
	m:
	int choice;
		cout<<"*********************\n";
		cout<<"                     \n";
		cout<<"      Renter Menu    \n";
		cout<<"                     \n";
		cout<<"1. Rent a Car        \n";
		cout<<"2. Show Car List     \n";
		cout<<"3. Show Available Cars\n";
		cout<<"4. Return a Car      \n";
		cout<<"5. Back to main menu \n";
		cout<<"                     \n";
		cout<<"*********************\n";
		cout<<"Select options (1-3) : ";
		cin>> choice;
			
	system("CLS");
	
	switch (choice){
    case 1:
        receipt();
        break;
    case 2:
        listofcars();
        break;
    case 3:
    	availableCarsList();
		break;
    case 4: {
        int carCode;
        cout << "Enter the car code to return: ";
        cin >> carCode;
        returnCar(carCode);
        break;
    }
    case 5:
    	menu();
        break; 
    default:
        cout << "Invalid..";
	}

	goto m;
}

int loadLatestID() {
    ifstream dataFile("database.txt");
    if (!dataFile.is_open()) {
        return 1; // If the file cannot be opened, start with ID 1
    }

    dataFile.seekg(0, ios::end); // Move to the end of the file
    if (dataFile.tellg() == 0) { // Check if the file is empty
        dataFile.close();
        return 1; // Reset ID to 1 if file is empty
    }

    // File is not empty, proceed to load the latest ID from latest_id.txt
    ifstream idFile("latest_id.txt");
    int latestID = 0;
    if (idFile.is_open()) {
        idFile >> latestID;
        idFile.close();
    }
    return latestID > 0 ? latestID : 1; 
}

void saveLatestID(int latestID) {
    ofstream idFile("latest_id.txt");
    if (idFile.is_open()) {
        idFile << latestID;
        idFile.close();
    }
}

void rental::addcar() {
    fstream data;
    int c;
    string n;
    int y;
    float p;

    cout << "Add a new car for rental \n";

    // Load the latest ID from file
    int latestID = loadLatestID();

    // Incrementing ID
    ccode = latestID;

    cout << "Car model : ";
    cin.ignore(); // ignore any leftover newline character
    getline(cin, cname); // Use getline to read the whole line

    cout << "\nCar Year : ";
    cin >> cyear;

    cout << "\nRental Price : ";
    cin >> price;

    data.open("database.txt", ios::in);
    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << ccode << " " << cname << " " << cyear << " " << price << "\n";
        data.close();
    } else {
        // Reset file position to the beginning
        data.clear();
        data.seekg(0, ios::beg);

        data.close();
        data.open("database.txt", ios::app | ios::out);
        data << ccode << " " << cname << " " << cyear << " " << price << "\n";
        data.close();
    }

    // Save the updated latest ID to file
    saveLatestID(ccode + 1); // Increment the ID for the next car

    cout << "\n\n A new Car has been added... \n";
    system("PAUSE");
    system("CLS");
}

void rental::editcar() {
    fstream data, data1;
    int ckey;
    int token = 0;
    int c;
    int y;
    float p;
    string n;

    cout << "     Modify The Car Record    \n";
    
    // Display car list without clearing the screen and pausing
    listofcars(false);

    cout << "\n Car code : ";
    cin >> ckey;

    // Auto-incrementing ID
    static int latestID = 0;

    data.open("database.txt");
    if (!data) {
        cout << "File does not exist...";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> ccode >> cname >> cyear >> price;
        while (!data.eof()) {
            if (ckey == ccode) {
                // Auto-incrementing ID for edited record
                c = ++latestID;

                cout << "Car Model : ";
                cin >> n;

                cout << "Car Year : ";
                cin >> y;

                cout << "Rental Price : ";
                cin >> p;
                data1 << " " << c << " " << n << " " << y << " " << p << "\n";

                cout << "Record has been edited... \n";
                token++;
                
            } else {
                data1 << " " << ccode << " " << cname << " " << cyear << " " << price << "\n";
            }
            data >> ccode >> cname >> cyear >> price;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "Record not Found... \n";
        }
    }

    system("PAUSE");
    system("CLS");
}

void rental::rem() {
    fstream data, data1;
    int ckeys;
    int token = 0;

    cout << "        Delete a Car    \n";
    
    // Display car list without clearing the screen and pausing
    listofcars(false);

    cout << "Car ID : ";
    cin >> ckeys;

    data.open("database.txt");
    if (!data) {
        cout << "\n File Does not exist \n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> ccode >> cname >> cyear >> price;
        while (!data.eof()) {
            if (ckeys == ccode) {
                cout << "A Car is Deleted successfully! \n";
                token++;
                system("PAUSE");
                system("CLS");
            } else {
                data1 << " " << ccode << " " << cname << " " << cyear << " " << price << "\n";
            }
            data >> ccode >> cname >> cyear >> price;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n Record not found...! \n";
            system("PAUSE");
            system("CLS");
        }
        listofcars(false);
    }
}

void rental::listofcars(bool clearScreenAndPause) {
    if (clearScreenAndPause) {
        system("CLS");
    }
    fstream data;
    int id;
    data.open("database.txt");
    cout << "********************************************************************************************\n";
    cout << "Car ID\t          Model \t\t     Year \t\t        rental price \n";
    cout << "********************************************************************************************\n";
    
    data >> ccode >> cname >> cyear >> price;
    
    while (!data.eof()) {
        cout << left;
        cout << setw(15) << ccode << setw(30) << cname << setw(30) << cyear << setw(30) << price << "\n";
        data >> ccode >> cname >> cyear >> price;
    }
    data.close();
    
    if (clearScreenAndPause) {
        system("PAUSE");
        system("CLS");
    }
}


void rental::receipt() {
    fstream data;
    int arrc[100];
    int arrt[100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;

    cout << "       Car Rental       \n";

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database! \n";
    } else {
        data.close();

        do {
            // Display available cars without clearing the screen and pausing
            availableCarsList(false);

            cout << "*************************************\n";
            cout << "                                     \n";
            cout << "Please enter the car you want to rent\n";
            cout << "*************************************\n";

            cout << "\nEnter Car Code : ";
            cin >> arrc[c];
            cout << "\nEnter the number of rental days : ";
            cin >> arrt[c];

            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "\nDUPLICATED CAR ID. Please try again.\n";
                    goto m;
                }
            }
            c++;
            cout << "\nDo you want to rent an additional car? (y/n): ";
            cin >> choice;
        } while (choice == 'y');

        string renterName, renterContact, renterAddress; // Declare variables here

        cout << "Enter your name: ";
        cin.ignore(); // ignore any leftover newline character
        getline(cin, renterName); // Use getline to read the whole line

        cout << "Enter your contact number : ";
        getline(cin, renterContact); // Use getline to read the whole line

        cout << "Enter your address : ";
        getline(cin, renterAddress); // Use getline to read the whole line
        
        system("CLS");

        cout << "=====================================Car Rent Receipt=====================================\n";
        cout << " Car ID\t Car Model\t Car year\t Price\t rental days\n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> ccode >> cname >> cyear >> price;
            while (!data.eof()) {
                if (ccode == arrc[i]) {
                    amount = price * arrt[i];
                    total += amount;
                    cout << "\n" << ccode << "\t\t" << cname << "\t\t" << cyear << "\t\t" << price << "\t\t" << arrt[i];
                    // Add rented car to vector with renter details
                    RentalRecord record(ccode, arrt[i], renterName, renterContact, renterAddress);
                    rentedCars.push_back(record);
                }
                data >> ccode >> cname >> cyear >> price;
            }
            data.close();
        }
        cout << "\n\n-------------------------------\n";
        cout << " Total Amount : " << total << endl;
        // Save rented cars to file after completing the receipt
        saveRentedCarsToFile();
        system("PAUSE");
        system("CLS");
    }
    return;
m:
    goto m;
}

void rental::availableCarsList(bool clearScreenAndPause) {
    if (clearScreenAndPause) {
        system("CLS");
    }
    fstream data;
    data.open("database.txt");
    cout << "********************************************************************************************\n";
    cout << "Available Cars:\n";
    cout << "Car ID\t          Model \t\t     Year \t\t        rental price \n";
    cout << "********************************************************************************************\n";

    data >> ccode >> cname >> cyear >> price;

    while (!data.eof()) {
        bool rented = false;
        // Check if the current car code is in the rented cars list
        for (const auto& record : rentedCars) {
            if (ccode == record.carCode) {
                rented = true;
                break;
            }
        }
        // If the car is not rented, display it
        if (!rented) {
            cout << left;
            cout << setw(15) << ccode << setw(30) << cname << setw(30) << cyear << setw(30) << price << "\n";
        }
        data >> ccode >> cname >> cyear >> price;
    }
    data.close();

    if (clearScreenAndPause) {
        system("PAUSE");
        system("CLS");
    }
}



void rental::showRentedCars() {
    cout << "Rented Cars:\n";
    cout << "Car ID\tRental Days\tRenter Name\tRenter Contact\tRenter Address\n";
    for (const auto& record : rentedCars) {
        cout << record.carCode << "\t" << record.rentalDays << "\t\t" << record.renterName << "\t\t" << record.renterContact << "\t" << record.renterAddress << endl;
    }
}


void rental::returnCar(int ccode) {
    for (auto it = rentedCars.begin(); it != rentedCars.end(); ++it) {
        if (it->carCode == ccode) {
            rentedCars.erase(it);
            cout << "Car with ID " << ccode << " has been returned." << endl;
            saveRentedCarsToFile();
            return;
        }
    }
    cout << "Car with ID " << ccode << " is not currently rented." << endl;
}

void rental::saveRentedCarsToFile() {
    ofstream file("rented_cars.txt");
    if (file.is_open()) {
        for (const auto& record : rentedCars) {
            file << record.carCode << " " << record.rentalDays << " " << record.renterName << " " << record.renterContact << " " << record.renterAddress << endl;
        }
        file.close();
    } else {
        cout << "Unable to save rented car records to file." << endl;
    }
}


void rental::loadRentedCarsFromFile() {
    ifstream file("rented_cars.txt");
    rentedCars.clear(); // Clear existing rented car records
    if (file.is_open()) {
        int code, days;
        string name, contact, address;
        while (file >> code >> days >> ws && getline(file, name, ' ') && getline(file, contact, ' ') && getline(file, address)) {
            RentalRecord record(code, days, name, contact, address);
            rentedCars.push_back(record);
        }
        file.close();
    } else {
        cout << "No rented car records found." << endl;
    }
}


int main() {
    ifstream welcomeFile("welcome.txt");
    
    if (welcomeFile.is_open()) {
        string line;
        while (getline(welcomeFile, line)) {
            cout << line << endl;
        }
        welcomeFile.close();
        system ("PAUSE");
        system ("CLS");
    } else {
        cout << "Unable to open file. Please make sure the file exists." << endl;
    }
    
    rental s;
    s.loadRentedCarsFromFile(); // Ensure rented cars are loaded at the start
    s.menu();
}

/*
 *   Copyright (c) 2024 Psalm Salcedo
 *   All rights reserved.
 */

