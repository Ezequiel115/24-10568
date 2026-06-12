#ifndef KMEANS_H
#define KMEANS_H
#include <vector>
#include "structures.h"

// Estructura corporativa interna para empaquetar el resumen estadístico
struct ClusterInfo {
    char label;
    int count;
    Coord_3D centroid;
    double dispersion;
};

std::vector<Labeled> run_kmeans(const std::vector<Coord_3D>& data, int k, std::vector<ClusterInfo>& summary);
#endif