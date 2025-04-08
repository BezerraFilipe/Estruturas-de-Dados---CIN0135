#include <iostream> 
#include <fstream>
#include <vector>
#include <algorithm>


using key_t = int;  // DO NOT CHANGE THIS

struct grave_t {    // DO NOT CHANGE THIS 
    bool deleted;   // soft-deleted marker (tombstone)
    key_t key;     
};

struct location_t { // DO NOT CHANGE THIS 
    int floor;  // floor number 0,1,2..., M-1
    int grave;  // grave position within the floor 0,1,2,..., L-1
};

using namespace std;

class Cemetery {
private:
    key_t floors;
    key_t gravesPerFloor;

    vector<vector<grave_t>> cemetery;
    key_t hashFcnt(key_t key);

    void rebuild();

public:
    Cemetery(int floors, int gravesPerFloor);
    ~Cemetery(){};
    bool has(key_t key);
    location_t add(key_t key);
    location_t del(key_t key);
    location_t qry(key_t key);
};


// ADD IMPLEMENTATION CODE


Cemetery::Cemetery(int floors, int gravesPerFloor){
    this->floors = floors;
    this->gravesPerFloor = gravesPerFloor;
    cemetery.resize(this->floors);
}

key_t Cemetery::hashFcnt(key_t key){
    return key % this->floors;
}   

bool Cemetery::has(key_t key) {
    key_t floor = hashFcnt(key);
    for (int j = 0; j < cemetery[floor].size(); j++) {
        if (cemetery[floor][j].key == key && cemetery[floor][j].deleted == false) {
            return true;
        }
    }
    return false;
}

location_t Cemetery::add(key_t key){
    key_t floor = hashFcnt(key);
    if (cemetery[floor].size() == this->gravesPerFloor){
        rebuild();
        floor = hashFcnt(key);
    }

    for (key_t j = 0; j < cemetery[floor].size(); j++){
        if (key < cemetery[floor][j].key){
            cemetery[floor].insert(cemetery[floor].begin() + j, {false, key});
            
            return {floor, j};
        }
        
        
    }
    cemetery[floor].push_back({false, key});
    return {floor, static_cast<int>(cemetery[floor].size() - 1)};
    
}
location_t Cemetery::del(key_t key){
    
    key_t floor = hashFcnt(key);
    for (key_t j = 0; j < cemetery[floor].size(); j++){
        if (cemetery[floor][j].key == key){
            cemetery[floor][j].deleted = true;
            return {floor, j};
        }
    }
    return {-1,-1};
    

}
location_t Cemetery::qry(key_t key){
    
    key_t floor = hashFcnt(key);
    for (key_t j = 0; j < cemetery[floor].size(); j++){
        if (cemetery[floor][j].key == key && cemetery[floor][j].deleted == false){
            return {floor, j};
        }
    }
    return {-1,-1};
}

void Cemetery::rebuild(){
    key_t newFloors = this->floors * 2 + 1;
    key_t newGravesPerFloor = this->gravesPerFloor * 2;
    vector<vector<grave_t>> newGraves(newFloors);

    vector<key_t> keys;
        for (int i = 0; i < this->floors; i++) {
            for (int j = 0; j < cemetery[i].size(); j++) {
                if (!cemetery[i][j].deleted) {
                    keys.push_back(cemetery[i][j].key);
                }
            }
        }

    sort(keys.begin(), keys.end());

    for (key_t key : keys) {
        key_t newFloor = key % newFloors;
        newGraves[newFloor].push_back({false, key});
    }

    this->floors = newFloors;
    this->gravesPerFloor = newGravesPerFloor;
    this->cemetery = move(newGraves);

}