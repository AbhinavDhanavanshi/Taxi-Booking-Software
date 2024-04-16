#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
// #include <bits/stdc++.h>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;

class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time, vector<string> passengerNames = {})
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

    void addPassengerName(std::string name)
    {
        passengerNames.push_back(name);
    }

    void removePassengerName(std::string name)
    {
        for (int i = 0; i < passengerNames.size(); i++)
        {
            if (passengerNames[i] == name)
            {
                passengerNames.erase(passengerNames.begin() + i);
                break;
            }
        }
    }

    vector<string> getPassengerNames() const
    {
        return passengerNames;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
    vector<string> passengerNames;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void inOrderTraversal(BinaryTreeNode *root, vector<BinaryTreeNode *> &result)
    {
        if (root == nullptr)
        {
            return;
        }

        // Recursively traverse the left subtree
        inOrderTraversal(root->getLeftPtr(), result);

        // Visit the current node (push it into the result vector)
        result.push_back(root);

        // Recursively traverse the right subtree
        inOrderTraversal(root->getRightPtr(), result);
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    BinaryTreeNode *searchWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode *temp = BSThead;
        while (temp != nullptr && temp->getDepartureTime() != key)
        {
            if (temp->getDepartureTime() > key)
            {
                temp = temp->getLeftPtr();
            }
            else
            {
                temp = temp->getRightPtr();
            }
        }
        return temp;
    }

    void addTrip(int key, Trip *trip, BinaryTreeNode *BSThead)
    {
        // cout<<"inside addTrip"<<endl;
        // cout<<key<<endl;
        BinaryTreeNode *t = BSThead;
        BinaryTreeNode *t1 = new BinaryTreeNode(key, trip, nullptr);
        if (t == nullptr)
        {
            // cout<<"setting head to->"<<endl;
            setBSTHead(t1);
            t1->setParentPtr(nullptr);
            t1->setLeftPtr(nullptr);
            t1->setRightPtr(nullptr);
            return;
        }
        else
        {
            // cout<<"inside else"<<endl;
            BinaryTreeNode *t2 = t;
            // this is correct for visible cases but not for hidden cases
            // while (t != nullptr)
            // {
            //     if (t->getDepartureTime() > key)
            //     {
            //         t2 = t;
            //         t = t->getLeftPtr();
            //     }
            //     else
            //     {
            //         t2 = t;
            //         t = t->getRightPtr();
            //     }
            // }
            // if(key>t2->getDepartureTime())
            // {
            //     t2->setRightPtr(t1);
            //     t1->setParentPtr(t2);
            //     t1->setLeftPtr(nullptr);
            //     t1->setRightPtr(nullptr);
            // }

            // trying this new one
            while (t != nullptr)
            {
                if (t->getDepartureTime() > key)
                {
                    t2 = t;
                    t = t->getLeftPtr();
                }
                else if (t->getDepartureTime() == key)
                {
                    t->setTripNodePtr(trip);
                    return;
                }
                else
                {
                    t2 = t;
                    t = t->getRightPtr();
                }
            }
            if (key > t2->getDepartureTime())
            {
                t2->setRightPtr(t1);
                t1->setParentPtr(t2);
                t1->setLeftPtr(nullptr);
                t1->setRightPtr(nullptr);
            }
            else
            {
                t2->setLeftPtr(t1);
                t1->setParentPtr(t2);
                t1->setLeftPtr(nullptr);
                t1->setRightPtr(nullptr);
            }
        }
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

    vector<Trip *> getTrips() const
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        if (serviceptrs.size() == 0)
        {
            return nullptr;
        }
        else
        {
            for (int i = 0; i < serviceptrs.size(); i++)
            {
                if (serviceptrs[i]->getName() == droplocation)
                {
                    return serviceptrs[i];
                }
            }
        }
        return nullptr;
    }

    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation)
    {
        if (getServicePtr(droplocation) == nullptr)
        {
            TransportService *t = new TransportService(droplocation);
            serviceptrs.push_back(t);
            t->setName(droplocation);
            t->setBSTHead(nullptr);
            return t;
        }
        else
        {
            return getServicePtr(droplocation);
        }
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

    vector<TransportService *> getServicePtrs() const
    {
        return serviceptrs;
    }

    int getNumberOfServices() const
    {
        return serviceptrs.size();
    }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    void insert(int departuretime, Trip *tripnodeptr)
    {
        BinaryTreeNode *temp = new BinaryTreeNode(departuretime, tripnodeptr);
        if (root == nullptr)
        {
            root = temp;
        }
        else
        {
            BinaryTreeNode *temp1 = root;
            while (temp1 != nullptr)
            {
                if (temp1->getDepartureTime() > departuretime)
                {
                    if (temp1->getLeftPtr() == nullptr)
                    {
                        temp1->setLeftPtr(temp);
                        temp->setParentPtr(temp1);
                        break;
                    }
                    else
                    {
                        temp1 = temp1->getLeftPtr();
                    }
                }
                else
                {
                    if (temp1->getRightPtr() == nullptr)
                    {
                        temp1->setRightPtr(temp);
                        temp->setParentPtr(temp1);
                        break;
                    }
                    else
                    {
                        temp1 = temp1->getRightPtr();
                    }
                }
            }
        }
    }

    int calHeight(BinaryTreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            int lheight = calHeight(node->getLeftPtr());
            int rheight = calHeight(node->getRightPtr());
            if (lheight > rheight)
            {
                return lheight + 1;
            }
            else
            {
                return rheight + 1;
            }
        }
    }

    int calSize(BinaryTreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return calSize(node->getLeftPtr()) + calSize(node->getRightPtr()) + 1;
        }
    }
    int getHeight()
    {
        // Implement this function to return the height of the tree
        return calHeight(root);
    }

    int getNumberOfNodes()
    {
        // Implement this function to return the number of nodes in the tree
        return calSize(root);
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode *temp = root;
        while (temp->getLeftPtr() != nullptr)
        {
            temp = temp->getLeftPtr();
        }
        return temp;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode *temp = root;
        while (temp->getRightPtr() != nullptr)
        {
            temp = temp->getRightPtr();
        }
        return temp;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode *temp = root;
        while (temp != nullptr)
        {
            if (temp->getDepartureTime() == key)
            {
                return temp;
            }
            else if (temp->getDepartureTime() > key)
            {
                temp = temp->getLeftPtr();
            }
            else
            {
                temp = temp->getRightPtr();
            }
        }
        return nullptr;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        BinaryTreeNode *temp = node;
        if (temp->getRightPtr() != nullptr)
        {
            temp = temp->getRightPtr();
            while (temp->getLeftPtr() != nullptr)
            {
                temp = temp->getLeftPtr();
            }
            return temp;
        }
        else
        {
            BinaryTreeNode *temp1 = temp->getParentPtr();
            while (temp1 != nullptr && temp == temp1->getRightPtr())
            {
                temp = temp1;
                temp1 = temp1->getParentPtr();
            }
            return temp1;
        }
        return nullptr; // Placeholder
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        // Implement this function to return the successor node by key
        BinaryTreeNode *temp = searchNodeWithKey(key);
        return getSuccessorNode(temp);
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the predecessor node of the given node
        BinaryTreeNode *temp = node;
        if (temp->getLeftPtr() != nullptr)
        {
            temp = temp->getLeftPtr();
            while (temp->getRightPtr() != nullptr)
            {
                temp = temp->getRightPtr();
            }
            return temp;
        }
        else
        {
            BinaryTreeNode *temp1 = temp->getParentPtr();
            while (temp1 != nullptr && temp == temp1->getLeftPtr())
            {
                temp = temp1;
                temp1 = temp1->getParentPtr();
            }
            return temp1;
        }
        return nullptr; // Placeholder
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode *temp = searchNodeWithKey(key);
        return getPredecessorNode(temp);
    }
};

class TravelDesk
{
public:
    Location *getLocation(std::string location)
    {
        // cout << "getLocation" << endl;
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == location)
            {
                return locations[i];
            }
        }
        return nullptr;
    }
    int getSize()
    {
        return vehicles.size();
    }

    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Implement this function to add a trip
        int cnt1 = 0, cnt2 = 0;
        Vehicle *v = new Vehicle(vehicle_number, seating_capacity);
        Location *l = new Location(pick_up_location);
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i]->getVehicleNumber() == vehicle_number)
            {
                cnt1++;
                v = vehicles[i];
            }
        }
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                cnt2++;
                l = locations[i];
            }
        }
        if (cnt1 == 0)
        {
            vehicles.push_back(v);
        }
        if (cnt2 == 0)
        {
            locations.push_back(l);
        }
        Trip *t = new Trip(v, pick_up_location, drop_location, departure_time);
        v->addTrip(t);
        l->addTrip(t);
        int count = 0;
        if (l->getServicePtr(drop_location) == nullptr)
        {
            l->setServicePtr(drop_location);
            l->getServicePtr(drop_location)->addTrip(departure_time, t, l->getServicePtr(drop_location)->getBSTHead());
        }
        else
        {
            for (int i = 0; i < l->getNumberOfServices(); i++)
            {
                if (l->getServicePtrs()[i]->getName() == drop_location)
                {
                    l->getServicePtrs()[i]->addTrip(departure_time, t, l->getServicePtrs()[i]->getBSTHead());
                    count++;
                }
            }
            if (count == 0)
            {
                l->setServicePtr(drop_location);
                l->getServicePtr(drop_location)->addTrip(departure_time, t, l->getServicePtr(drop_location)->getBSTHead());
            }
        }
        for (int i = 0; i < l->getNumberOfServices(); i++)
        {
            if (l->getServicePtrs()[i]->getName() == drop_location)
            {
                l->getServicePtrs()[i]->addTrip(departure_time, t, l->getServicePtrs()[i]->getBSTHead());
                count++;
            }
        }
        if (count == 0)
        {
            l->setServicePtr(drop_location);
            l->getServicePtr(drop_location)->addTrip(departure_time, t, l->getServicePtr(drop_location)->getBSTHead());
        }
    }

    void showTrips(string pick_up_location, int after_time, int before_time, vector<Trip *> &v)
    {
        if (after_time > before_time)
        {
            return;
        }
        else
        {
            for (int i = 0; i < locations.size(); i++)
            {
                if (locations[i]->getName() == pick_up_location)
                {
                    for (int j = 0; j < locations[i]->getNumberOfServices(); j++)
                    {
                        if (locations[i]->getServicePtrs()[j]->getBSTHead() == nullptr)
                        {
                            return;
                        }
                        else
                        {
                            BinaryTreeNode *temp = locations[i]->getServicePtrs()[j]->getBSTHead();
                            vector<BinaryTreeNode *> q;
                            temp->inOrderTraversal(temp, q);
                            for (int k = 0; k < q.size(); k++)
                            {
                                if (q[k]->getDepartureTime() >= after_time && q[k]->getDepartureTime() <= before_time)
                                {
                                    v.push_back(q[k]->getTripNodePtr());
                                }
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    void showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time, vector<Trip *> &v)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        if (after_time > before_time)
        {
            return;
        }
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                for (int j = 0; j < locations[i]->getNumberOfServices(); j++)
                {
                    if (locations[i]->getServicePtrs()[j]->getName() == destination)
                    {
                        BinaryTreeNode *temp = locations[i]->getServicePtrs()[j]->getBSTHead();
                        vector<BinaryTreeNode *> q;
                        temp->inOrderTraversal(temp, q);
                        for (int k = 0; k < q.size(); k++)
                        {
                            if (q[k]->getDepartureTime() >= after_time && q[k]->getDepartureTime() < before_time)
                            {
                                v.push_back(q[k]->getTripNodePtr());
                            }
                        }
                    }
                }
            }
        }
        return;
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time, string name)
    {
        // Implement this function to book a trip
        if (departure_time < 0)
        {
            return nullptr;
        }
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i]->getVehicleNumber() == vehicle_number)
            {
                for (int j = 0; j < vehicles[i]->getTrips().size(); j++)
                {
                    if (vehicles[i]->getTrips()[j]->getPickUpLocation() == pick_up_location && vehicles[i]->getTrips()[j]->getDropLocation() == drop_location && vehicles[i]->getTrips()[j]->getDepartureTime() == departure_time)
                    {
                        if (vehicles[i]->getTrips()[j]->getBookedSeats() < vehicles[i]->getSeatingCapacity())
                        {
                            vehicles[i]->getTrips()[j]->setBookedSeats(vehicles[i]->getTrips()[j]->getBookedSeats() + 1);
                            vehicles[i]->getTrips()[j]->addPassengerName(name);
                            return vehicles[i]->getTrips()[j];
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    std::vector<Vehicle *> vehicles;

    std::vector<Location *> locations;

private:
};

int getUserInput()
{
    int userInteger;

    while (true)
    {

        if (!(cin >> userInteger))
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            cout << "Invalid input. Please enter an integer.\n";
        }
        else
        {
            // Check if there are any trailing characters after the integer
            char nextChar = cin.peek();
            if (nextChar == '\n' || isspace(nextChar))
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character
                break;                                               // Valid input
            }
            else
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

                cout << "Invalid input. Please enter a valid integer.\n";
            }
        }
    }

    return userInteger;
}

void toupper(string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (i == 0)
        {
            s[i] = toupper(s[i]);
        }
        else if (s[i] == ' ')
        {
            continue;
        }
        else
        {
            s[i] = tolower(s[i]);
        }
    }
}

int main()
{
    cout << "Welcome to TravelDesk!" << endl;
    TravelDesk *travelDesk = new TravelDesk();
    cout << "\nPlease enter the password to startup the software as an administrator" << endl;
    string password;
    int tries = 4;
    cout << "password : ";
    getline(cin, password);
    while (password != "admin")
    {
        cout << "\nIncorrect password. Please try again. You have " << tries << " tries left." << endl;
        cout << "password : ";
        getline(cin, password);
        tries--;
        if (tries == 0)
        {
            cout << "You have exceeded the maximum number of tries. security shutdown" << endl;
            return 0;
        }
        cout<<endl;
    }
    cout << endl;
    cout << "Welcome Administrator!" << endl;
    cout << "Loading trips information" << endl;
    ifstream ip("trips.txt");
    if (!ip.is_open())
    {
        cout << "Error: File not found" << endl;
        return 0;
    }
    string vehicle_number, pick_up_location, drop_location, departure_time, seating_capacity;
    string line;
    while (getline(ip, line))
    {
        int cnt = -2;
        int prev = 0;
        int current = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ' ')
            {
                prev = current;
                current = i;
                cnt++;
            }
            else if (i == line.size() - 1)
            {
                departure_time = line.substr(current + 1, line.size() - current - 1);
            }
            if (cnt == 0)
            {
                vehicle_number = line.substr(prev + 1, current - prev - 1);
            }
            else if (cnt == 1)
            {
                seating_capacity = line.substr(prev + 1, current - prev - 1);
            }
            else if (cnt == 2)
            {
                pick_up_location = line.substr(prev + 1, current - prev - 1);
            }
            else if (cnt == 3)
            {
                drop_location = line.substr(prev + 1, current - prev - 1);
            }
        }
        travelDesk->addTrip(vehicle_number, 4, pick_up_location, drop_location, stoi(departure_time));
        // cout<<"trip added"<<endl;
    }
    cout << "Trips information loaded successfully" << endl;
    cout << "\nPlease enter the password to startup the software as a user" << endl;
    cout << "password : ";
    getline(cin, password);
    tries = 4;
    while (password != "user")
    {
        cout << "\nIncorrect password. Please try again. You have " << tries << " tries left." << endl;
        cout << "password : ";
        getline(cin, password);
        tries--;
        if (tries == 0)
        {
            cout << "\nYou have exceeded the maximum number of tries. security shutdown" << endl;
            return 0;
        }
        cout<<endl;
    }
    cout << endl;
    cout << "Welcome User!" << endl;
    cout << "\nTo book a trip : enter 1" << endl;
    cout << "To view trips : enter 2" << endl;
    cout << "To enter administrator mode: enter 3" << endl;
    int choice;
    while (true)
    {
        cout<<"choice : ";
        choice = getUserInput();
        if (choice == 1 || choice == 2 || choice == 3)
        {
            break;
        }
        else
        {
            cout << "\nError: Invalid choice\n" << endl;
        }
    }
    while (true)
    {
        if (choice == 1)
        {
            cout << "\nPlease enter the pick up location : ";
            string pick_up_location;
            getline(cin, pick_up_location);
            toupper(pick_up_location);
            cout << "\nPlease enter the drop location : ";
            string drop_location;
            getline(cin, drop_location);
            toupper(drop_location);
            cout << "\nPlease enter the departure time (24 hour format without ':' eg: '1600'): ";
            int departure_time = getUserInput();
            cout << "\nPlease enter the vehicle number : ";
            string vehicle_number;
            getline(cin, vehicle_number);
            cout << "\nPlease enter the number of seats to book : ";
            int number_of_seats_to_book = getUserInput();
            if (number_of_seats_to_book <= 0)
            {
                cout << "\nError: Invalid number of seats" << endl;
                continue;
            }
            if (departure_time < 0)
            {
                cout << "\nError: Invalid departure time" << endl;
                continue;
            }
            if (travelDesk->getLocation(pick_up_location) == nullptr)
            {
                cout << "\nError: Pick up location not found" << endl;
                continue;
            }
            if (travelDesk->getLocation(pick_up_location)->getServicePtr(drop_location) == nullptr)
            {
                cout << "\nError: Drop location not found" << endl;
                continue;
            }
            // check if the required seats are available or not
            int cnt = 0;
            for (int i = 0; i < travelDesk->vehicles.size(); i++)
            {
                if (travelDesk->vehicles[i]->getVehicleNumber() == vehicle_number)
                {
                    for (int j = 0; j < travelDesk->vehicles[i]->getTrips().size(); j++)
                    {
                        if (travelDesk->vehicles[i]->getTrips()[j]->getPickUpLocation() == pick_up_location && travelDesk->vehicles[i]->getTrips()[j]->getDropLocation() == drop_location && travelDesk->vehicles[i]->getTrips()[j]->getDepartureTime() == departure_time)
                        {
                            if (travelDesk->vehicles[i]->getTrips()[j]->getBookedSeats() + number_of_seats_to_book > travelDesk->vehicles[i]->getSeatingCapacity())
                            {
                                cout << "\nError: Seats not available" << endl;
                                cout << "\nAvailable seats : " << travelDesk->vehicles[i]->getSeatingCapacity() - travelDesk->vehicles[i]->getTrips()[j]->getBookedSeats() << endl;
                                cnt++;
                                break;
                            }
                        }
                    }
                }
            }
            if (cnt != 0)
            {
                continue;
            }
            for (int i = 0; i < number_of_seats_to_book; i++)
            {
                cout << "\nPlease enter the name of passenger " << i + 1 << " : ";
                string name;
                getline(cin, name);
                toupper(name);
                Trip *t = travelDesk->bookTrip(pick_up_location, drop_location, vehicle_number, departure_time, name);
                if (t == nullptr)
                {
                    cout << "\nError: Trip not found" << endl;
                    break;
                }
                else
                {
                    cout << "\nTrip booked successfully" << endl;
                    cout << "Remaining seats : " << t->getVehicle()->getSeatingCapacity() - t->getBookedSeats() << endl;
                }
            }
        }
        else if (choice == 2)
        {
            cout << "\nTo view trips from a location in your time range : enter 1" << endl;
            cout << "To view trips by time range : enter 2" << endl;
            int choice1;
            while (true)
            {
                cout<<"choice : ";
                choice1 = getUserInput();
                if (choice1 == 1 || choice1 == 2)
                {
                    break;
                }
                else
                {
                    cout << "Error: Invalid choice" << endl;
                }
            }
            if (choice1 == 1)
            {
                cout << "\nPlease enter the pick up location : ";
                string pick_up_location;
                getline(cin, pick_up_location);
                toupper(pick_up_location);
                cout << "Please enter the drop location : ";
                string drop_location;
                getline(cin, drop_location);
                toupper(drop_location);
                cout << "Please enter the departure time range (24 hour format without ':' eg: '1600')"<<endl;
                int after_time, before_time;
                cout<<"after time : ";
                after_time = getUserInput();
                cout<<"before time : ";
                before_time = getUserInput();
                vector<Trip *> v;
                travelDesk->showTripsbydestination(pick_up_location, drop_location, after_time, before_time, v);
                if (v.size() == 0)
                {
                    cout << "No trips found" << endl;
                }
                else
                {
                    cout<<endl;
                    cout << "Trips found:" << endl;
                    for (int i = 0; i < v.size(); i++)
                    {
                        cout << "trip " << i + 1 << ":" << endl;
                        cout << "vehicle number -> " << v[i]->getVehicle()->getVehicleNumber() << endl;
                        cout << "seating capacity -> " << v[i]->getVehicle()->getSeatingCapacity() << endl;
                        cout << "pickup location -> " << v[i]->getPickUpLocation() << endl;
                        cout << "drop location -> " << v[i]->getDropLocation() << endl;
                        cout << "departure time -> " << v[i]->getDepartureTime() << endl;
                        cout << "remaining seats -> " << v[i]->getVehicle()->getSeatingCapacity() - v[i]->getBookedSeats() << endl;
                        cout << endl;
                    }
                }
            }
            else if (choice1 == 2)
            {
                cout << "\nPlease enter the pick up location : ";
                string pick_up_location;
                getline(cin, pick_up_location);
                toupper(pick_up_location);
                cout << "\nPlease enter the departure time range (24 hour format without ':' eg: '1600')" << endl;
                int after_time, before_time;
                cout<<"after time : ";
                after_time = getUserInput();
                cout<<"before time : ";
                before_time = getUserInput();
                vector<Trip *> v;
                travelDesk->showTrips(pick_up_location, after_time, before_time, v);
                if (v.size() == 0)
                {
                    cout << "Sorry!! No such trip found" << endl;
                }
                else
                {
                    cout<<endl;
                    cout << "Trips found:" << endl;
                    for (int i = 0; i < v.size(); i++)
                    {
                        cout << "trip " << i + 1 << ":" << endl;
                        cout << "vehicle number -> " << v[i]->getVehicle()->getVehicleNumber() << endl;
                        cout << "seating capacity -> " << v[i]->getVehicle()->getSeatingCapacity() << endl;
                        cout << "pickup location -> " << v[i]->getPickUpLocation() << endl;
                        cout << "drop location -> " << v[i]->getDropLocation() << endl;
                        cout << "departure time -> " << v[i]->getDepartureTime() << endl;
                        cout << "remaining seats -> " << v[i]->getVehicle()->getSeatingCapacity() - v[i]->getBookedSeats() << endl;
                        cout << endl;
                    }
                }
            }
            else
            {
                cout << "Error: Invalid choice" << endl;
            }
        }
        else if (choice == 3)
        {
            cout<<endl;
            cout << "Please enter the password to enter administrator mode" << endl;
            cout<<"password : ";
            getline(cin, password);
            tries = 4;
            while (password != "admin")
            {
                cout << "\nIncorrect password. Please try again. You have " << tries << " tries left." << endl;
                cout<<"password : ";
                getline(cin, password);
                tries--;
                if (tries == 0)
                {
                    cout << "\nYou have exceeded the maximum number of tries. security shutdown" << endl;
                    return 0;
                }
            }
            cout << "\nWelcome Administrator!" << endl;
            cout << "\nTo shutdown : enter 1" << endl;
            cout << "To enter user mode : enter 2" << endl;
            cout << "To check the status of a vehicle : enter 3" << endl;
            cout << "To add a trip : enter 4" << endl;
            cout << "To get the trip of a passenger : enter 5" << endl;

            while (true)
            {
                cout<<"choice : ";
                choice = getUserInput();
                if (choice == 1)
                {
                    cout << "Exiting" << endl;
                    return 0;
                }
                else if (choice == 2)
                {
                    cout << "\nWelcome User!" << endl;
                    break;
                }
                else if (choice == 3)
                {
                    cout << "\nPlease enter the vehicle number : ";
                    string vehicle_number;
                    getline(cin, vehicle_number);
                    int cnt = 0;
                    for (int i = 0; i < travelDesk->vehicles.size(); i++)
                    {
                        if (travelDesk->vehicles[i]->getVehicleNumber() == vehicle_number)
                        {
                            cnt++;
                            cout << "\nvehicle number -> " << travelDesk->vehicles[i]->getVehicleNumber() << endl;
                            cout << "seating capacity -> " << travelDesk->vehicles[i]->getSeatingCapacity() << endl;
                            cout << "details of trips : " << endl;
                            for (int j = 0; j < travelDesk->vehicles[i]->getTrips().size(); j++)
                            {
                                cout << "\ntrip " << j + 1 << ":" << endl;
                                cout << "pickup location -> " << travelDesk->vehicles[i]->getTrips()[j]->getPickUpLocation() << endl;
                                cout << "drop location -> " << travelDesk->vehicles[i]->getTrips()[j]->getDropLocation() << endl;
                                cout << "departure time -> " << travelDesk->vehicles[i]->getTrips()[j]->getDepartureTime() << endl;
                                cout << "passengers -> ";
                                if (travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames().size() == 0)
                                {
                                    cout << "No passengers" << endl;
                                }
                                for (int k = 0; k < travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames().size(); k++)
                                {
                                    if (k == travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames().size() - 1)
                                    {
                                        cout << travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames()[k];
                                        break;
                                    }
                                    cout << travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames()[k] << " ,";
                                }
                            }
                        }
                    }
                    if (cnt == 0)
                    {
                        cout << "Error: Vehicle not found" << endl;
                    }
                }
                else if (choice == 4)
                {
                    cout << "\nPlease enter the vehicle number : ";
                    string vehicle_number;
                    getline(cin, vehicle_number);
                    cout << "\nPlease enter the seating capacity : ";
                    int seating_capacity;
                    cin >> seating_capacity;
                    cout << "\nPlease enter the pick up location : ";
                    string pick_up_location;
                    getline(cin, pick_up_location);
                    toupper(pick_up_location);
                    cout << "\nPlease enter the drop location : ";
                    string drop_location;
                    getline(cin, drop_location);
                    toupper(drop_location);
                    cout << "\nPlease enter the departure time (24 hour format without ':' eg: '1600'): ";
                    int departure_time;
                    departure_time = getUserInput();
                    travelDesk->addTrip(vehicle_number, seating_capacity, pick_up_location, drop_location, departure_time);
                }
                else if (choice == 5)
                {
                    cout << "\nPlease enter the name of the passenger :";
                    string name;
                    getline(cin, name);
                    toupper(name);
                    int cnt = 0;
                    for (int i = 0; i < travelDesk->vehicles.size(); i++)
                    {
                        for (int j = 0; j < travelDesk->vehicles[i]->getTrips().size(); j++)
                        {
                            for (int k = 0; k < travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames().size(); k++)
                            {
                                if (travelDesk->vehicles[i]->getTrips()[j]->getPassengerNames()[k] == name)
                                {
                                    cnt++;
                                    cout << "\nvehicle number -> " << travelDesk->vehicles[i]->getVehicleNumber() << endl;
                                    cout << "seating capacity -> " << travelDesk->vehicles[i]->getSeatingCapacity() << endl;
                                    cout << "pickup location -> " << travelDesk->vehicles[i]->getTrips()[j]->getPickUpLocation() << endl;
                                    cout << "drop location -> " << travelDesk->vehicles[i]->getTrips()[j]->getDropLocation() << endl;
                                    cout << "departure time -> " << travelDesk->vehicles[i]->getTrips()[j]->getDepartureTime() << endl;                            }
                            }
                        }
                    }
                    if (cnt == 0)
                    {
                        cout << "\nError: Passenger not found" << endl;
                    }
                }
                else
                {
                    cout << "\nError: Invalid choice" << endl;
                }
                cout << "\nTo shutdown : enter 1" << endl;
                cout << "To enter user mode : enter 2" << endl;
                cout << "To check the status of a vehicle : enter 3" << endl;
                cout << "To add a trip : enter 4" << endl;
                cout << "To get the trip of a passenger : enter 5" << endl;
            }
        }

        else
        {
            cout << "\nError: Invalid choice" << endl;
        }
        cout << "\nTo book a trip : enter 1" << endl;
        cout << "To view trips : enter 2" << endl;
        cout << "To enter administrator mode: enter 3" << endl;
        while (true)
        {
            cout<<"choice : ";
            choice = getUserInput();
            if (choice == 1 || choice == 2 || choice == 3)
            {
                break;
            }
            else
            {
                cout << "Error: Invalid choice" << endl;
            }
        }
    }
    cout << "\nExiting" << endl;
    return 0;
}
