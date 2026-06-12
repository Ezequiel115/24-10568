#include "loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Coord_3D> load_data(const std::string& filename) {
    std::vector<Coord_3D> points;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error corporativo: No se pudo abrir el archivo de entrada: " << filename << std::endl;
        return points;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // Ignorar líneas vacías de seguridad
        std::stringstream ss(line);
        std::string val;
        Coord_3D p;
        
        if (std::getline(ss, val, ',')) p.x = std::stod(val);
        if (std::getline(ss, val, ',')) p.y = std::stod(val);
        if (std::getline(ss, val, ',')) p.z = std::stod(val);
        
        points.push_back(p);
    }
    file.close();
    return points;
}