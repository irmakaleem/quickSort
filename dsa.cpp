#include <iostream>
#include <string>
using namespace std;
const int MAX_BUSES = 100;
const int MAX_SEATS = 50;
const int RESERVED_SEATS = 5;

struct Bus
{
    string departureLocation;
    string arrivalLocation;
    string status;
    int totalSeats;
    int availableSeats;
    string departureTime;
    string arrivalTime;
    bool seats[MAX_SEATS];
    int standbyPassengers[MAX_SEATS];
    int numStandbyPassengers;
};

// Function to initialize the seats of a bus
void initializeSeats(Bus &bus)
{
    for (int i = 0; i < bus.totalSeats; i++)
    {
        bus.seats[i] = true; // true indicates the seat is available
    }
}

// Function to search for buses based on user input
int searchBuses(string &departure, string &arrival, string &date, Bus buses[], int numBuses)
{
    int searchCount = 0;
    for (int i = 0; i < numBuses; i++)
    {
        if (buses[i].departureLocation == departure && buses[i].arrivalLocation == arrival)
        {
            cout << "Bus " << i + 1 << ":\n";
            cout << "Status: " << buses[i].status << "\n";
            cout << "Total Seats: " << buses[i].totalSeats << "\n";
            cout << "Available Seats: " << buses[i].availableSeats << "\n";
            cout << "Departure Time: " << buses[i].departureTime << "\n";
            cout << "Arrival Time: " << buses[i].arrivalTime << "\n";
            cout << "------------------------\n";
            searchCount++;
        }
    }
    return searchCount;
}

// Function to book a seat on a bus
void bookSeat(Bus &bus)
{
    if (bus.availableSeats <= RESERVED_SEATS)
    {
        cout << "No available seats for booking. Please try again later.\n";
        return;
    }

    int seatNumber;
    cout << "Enter the seat number you want to book: ";
    cin >> seatNumber;

    if (seatNumber < 1 || seatNumber > bus.totalSeats)
    {
        cout << "Invalid seat number.\n";
        return;
    }

    if (!bus.seats[seatNumber - 1])
    {
        cout << "Seat " << seatNumber << " is already booked.\n";
        return;
    }

    bus.seats[seatNumber - 1] = false;
    bus.availableSeats--;

    cout << "Seat " << seatNumber << " booked successfully!\n";
}

// Function to add a passenger to the standby list
void addStandbyPassenger(Bus &bus)
{
    // bus1 //seats=50,49,48,47..
    if (bus.numStandbyPassengers >= RESERVED_SEATS)
    {
        cout << "Standby list is full. Please try again later.\n";
        // if there is return in condition and if the condition gets true then there is no need of else
        return;
    }

    int standbyPassengerNumber = bus.numStandbyPassengers + 1;
    bus.standbyPassengers[bus.numStandbyPassengers] = standbyPassengerNumber;
    bus.numStandbyPassengers++;

    cout << "Added to the standby list. Your standby number is: " << standbyPassengerNumber << "\n";
}

// Function to allocate a seat to the next standby passenger
void allocateStandbySeat(Bus &bus)
{
    if (bus.numStandbyPassengers == 0)
    {
        cout << "No standby passengers in the list.\n";
        return;
    }

    int nextPassenger = bus.standbyPassengers[0];

    int seatNumber;
    for (int i = 0; i < bus.totalSeats; i++)
    {
        if (bus.seats[i])
        {
            seatNumber = i + 1;
            bus.seats[i] = false;
            bus.availableSeats--;
            break;
        }
    }

    // Shift the remaining standby passengers up in the list
    for (int i = 1; i < bus.numStandbyPassengers; i++)
    {
        bus.standbyPassengers[i - 1] = bus.standbyPassengers[i];
    }
    bus.numStandbyPassengers--;

    cout << "Seat " << seatNumber << " allocated to standby passenger " << nextPassenger << ".\n";
}
// FINDING THE ROUTES
const int MAX_LOCATIONS = 100;

struct Location
{
    string name;
    string terminal;
};

struct Route
{
    Location locations[MAX_LOCATIONS];
    int numLocations;
};

// Function to display the route map
void displayRouteMap(const Location locations[], int numLocations)
{
    cout << "Route Map:\n";
    for (int i = 0; i < numLocations; i++)
    {
        cout << "Location: " << locations[i].name << "\n";
        cout << "Terminal: " << locations[i].terminal << "\n";
        cout << "------------------------\n";
    }
}

// Function to find routes from departure to arrival city
void findRoutes(Location locations[], int numLocations, string &departure, string &arrival, Route routes[], int &numRoutes)
{
    // numLocations -> total no of locations
    for (int i = 0; i < numLocations; i++)
    {
        if (locations[i].name == departure)
        {
            for (int j = i + 1; j < numLocations; j++)
            {
                if (locations[j].name == arrival)
                {
                    Route route;
                    route.numLocations = j - i + 1;
                    for (int k = i; k <= j; k++)
                    {
                        route.locations[k - i] = locations[k];
                    }
                    routes[numRoutes] = route;
                    numRoutes++;
                }
            }
        }
    }
}

// Function to display routes
void displayRoutes(Route routes[], int numRoutes)
{
    cout << "Routes:\n";
    for (int i = 0; i < numRoutes; i++)
    {
        cout << "Route " << i + 1 << ":\n";
        for (int j = 0; j < routes[i].numLocations; j++)
        {
            cout << "Location: " << routes[i].locations[j].name << "\n";
            cout << "Terminal: " << routes[i].locations[j].terminal << "\n";
            cout << "------------------------\n";
        }
    }
}

// CARGO SHIPMENT
struct Parcel
{
    double weight;
    double profit;
};

void bubbleSort(Parcel parcels[], int numParcels)
{
    for (int i = 0; i < numParcels - 1; i++)
    {
        for (int j = 0; j < numParcels - i - 1; j++)
        {
            if (parcels[j].profit < parcels[j + 1].profit)
            {
                Parcel temp = parcels[j];
                parcels[j] = parcels[j + 1];
                parcels[j + 1] = temp;
            }
        }
    }
}

void shipCargo(Parcel parcels[], int numParcels, double maxWeight)
{
    double totalWeight = 0.0;
    double totalProfit = 0.0;
    Parcel selectedParcels[50];
    int selectedParcelIndex = 0;

    // Sort parcels based on profitability using bubble sort
    bubbleSort(parcels, numParcels);

    // Select parcels with higher profit and weight within the constraints
    for (int i = 0; i < numParcels; i++)
    {
        if (totalWeight + parcels[i].weight <= maxWeight)
        {
            selectedParcels[selectedParcelIndex++] = parcels[i];
            totalWeight += parcels[i].weight;
            totalProfit += parcels[i].profit;
        }
    }

    // Display the selected parcels and total profit
    cout << "Selected Parcels:\n";
    for (int i = 0; i < selectedParcelIndex; i++)
    {
        cout << "Weight: " << selectedParcels[i].weight << "kg | Profit: $" << selectedParcels[i].profit << "\n";
    }
    cout << "Total Weight: " << totalWeight << "kg\n";
    cout << "Total Profit: $" << totalProfit << "\n";
}

int main()
{
    Bus buses[MAX_BUSES] = {
        {"Karachi", "Lahore", "Scheduled", 50, 50, "08:00 AM", "10:30 AM"},
        {"Lahore", "Islamabad", "Delayed", 40, 40, "09:30 AM", "12:00 PM"},
        {"Karachi", "Islamabad", "Scheduled", 35, 35, "10:00 AM", "01:30 PM"},
        {"Lahore", "Karachi", "Scheduled", 60, 60, "11:30 AM", "03:00 PM"}};
    int numBuses = 4;

    int choice = 0;
mainmenu:
    cout << "PRESS 1 FOR SEARCHING THE BUS\n";
    cout << "PRESS 2 FOR ROUTE MAP(CAPTAIN)\n";
    cout << "PRESS 3 FOR CARGO SHIPMENT\n";
    cin >> choice;

    if (choice == 1)
    {
        string departure, arrival, date;
        cout << "Enter departure city: ";
        cin >> departure;
        cout << "Enter arrival city: ";
        cin >> arrival;
        cout << "Enter desired date of travel: ";
        cin >> date;

        int searchResult = searchBuses(departure, arrival, date, buses, numBuses);

        if (searchResult == 0)
        {
            cout << "No buses found for the given search criteria.\n";
        }
        else
        {
            int busIndex;
            cout << "Enter the bus number you want to book: ";
            cin >> busIndex;

            if (busIndex < 1)
            {
                cout << "Invalid bus number.\n";
            }
            else
            {
                Bus &selectedBus = buses[busIndex - 1];
                initializeSeats(selectedBus);

                while (true)
                {
                    int choice;
                    cout << "\nMenu:\n";
                    cout << "1. View available seats\n";
                    cout << "2. Book a seat\n";
                    cout << "3. Add to standby list\n";
                    cout << "4. Allocate standby seat\n";
                    cout << "5. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        cout << "Available Seats: " << selectedBus.availableSeats << "\n";
                        break;
                    case 2:
                        bookSeat(selectedBus);
                        break;
                    case 3:
                        addStandbyPassenger(selectedBus);
                        break;
                    case 4:
                        allocateStandbySeat(selectedBus);
                        break;
                    case 5:
                        cout << "Thank you for using the bus booking system!\n";
                        return 0;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
        }
        goto mainmenu;
    }
    else if (choice == 2)
    {
        Location locations[MAX_LOCATIONS] = {
            {"Karachi", "Terminal A"},
            {"Hyderabad", "Terminal B"},
            {"Sukkur", "Terminal C"},
            {"Multan", "Terminal D"},
            {"Lahore", "Terminal E"},
            {"Islamabad", "Terminal F"},
            {"Peshawar", "Terminal G"}
            // Add more locations as needed
        };
        int numLocations = 7;

        displayRouteMap(locations, numLocations);

        // Retrieve bus captain's input (departure and arrival locations)
        string departure, arrival;
        cout << "Enter departure location: ";
        cin >> departure;
        cout << "Enter arrival location: ";
        cin >> arrival;

        Route routes[MAX_LOCATIONS];
        int numRoutes = 0;

        findRoutes(locations, numLocations, departure, arrival, routes, numRoutes);

        if (numRoutes == 0)
        {
            cout << "No routes found from " << departure << " to " << arrival << ".\n";
        }
        else
        {
            displayRoutes(routes, numRoutes);
        }

        // Additional code for bus captains' functionality can be added here
        // For example, calculating the most efficient route based on the current conditions
        goto mainmenu;
    }
    else if (choice == 3)
    {
        int numParcels;
        cout << "Enter the number of parcels: ";
        cin >> numParcels;

        Parcel parcels[50];

        for (int i = 0; i < numParcels; i++)
        {
            cout << "Enter weight for parcel " << i + 1 << ": ";
            cin >> parcels[i].weight;
            cout << "Enter profit for parcel " << i + 1 << ": ";
            cin >> parcels[i].profit;
        }

        // MAX WEIGHT CAPACITY OF THE BUS
        double maxWeight = 200.0;

        shipCargo(parcels, numParcels, maxWeight);
        goto mainmenu;
    }

    system("pause");
    return 0;
}
