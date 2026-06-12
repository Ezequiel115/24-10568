#include "writer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void write_results(const std::string& csv_file, const std::vector<Labeled>& points,
                   const std::string& summary_file, const std::vector<ClusterInfo>& summary) {
    
    // Escritura de clasificados.csv
    std::ofstream csv(csv_file);
    if (csv.is_open()) {
        for (const auto& p : points) {
            csv << p.coord.x << "," << p.coord.y << "," << p.coord.z << "," << p.label << "\n";
        }
        csv.close();
    }

    // Escritura de summary.txt según el patrón de diseño requerido
    std::ofstream txt(summary_file);
    if (txt.is_open()) {
        txt << std::fixed << std::setprecision(4);
        for (const auto& info : summary) {
            txt << info.label << ": " << info.count << ", ("
                << info.centroid.x << ", " << info.centroid.y << ", " << info.centroid.z << "), "
                << info.dispersion << "\n";
        }
        txt.close();
    }
}