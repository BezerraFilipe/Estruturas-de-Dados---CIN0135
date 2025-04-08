#include <iostream>
#include <fstream>

#include "cemetery.hpp" 

int main() {
    int M, L;
    cin >> M >> L;
    Cemetery cemetery(M, L);
    
    string command;
    while (cin >> command) {
        if (command == "END") break;
        
        key_t key;
        cin >> key;
        
        location_t result;
        if (command == "ADD") {
            result = cemetery.add(key);
        } else if (command == "REM") {
            result = cemetery.del(key);
        } else if (command == "QRY") {
            result = cemetery.qry(key);
        }
        
        if (result.floor == -1 && result.grave == -1) {
            cout << "?.?" << endl;
        } else {
            cout << result.floor << "." << result.grave << endl;
        }
    }
    
    return 0;
}