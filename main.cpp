#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
class User {
protected:
    int userID;
    string name;
    string contact;

public:
    User(int id = 0, string n = "", string c = "")
        : userID(id), name(n), contact(c) {}

    virtual void displayInfo() const = 0;   // Abstraction

    int getUserID() const {
        return userID;
    }

    string getName() const {
        return name;
    }

    virtual ~User() {}
};