#include "kmeans.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

// Función matemática auxiliar para calcular la Distancia Euclidiana en 3 dimensiones
double euclidean_distance(const Coord_3D& p1, const Coord_3D& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2) + std::pow(p1.z - p2.z, 2));
}

/*
 * CONDICIÓN DE PARADA ENCAPSULADA:
 * Esta función evalúa si los centroides se han estabilizado usando un margen de tolerancia estricto (1e-6)
 * o si se ha alcanzado el límite máximo de iteraciones preventivas para romper ciclos infinitos.
 * Es una buena condición porque detiene la computación inmediatamente cuando los clusters dejan de cambiar,
 * optimizando el rendimiento computacional del ejecutable en producción.
 */
bool should_stop(const std::vector<Coord_3D>& old_centroids, const std::vector<Coord_3D>& new_centroids, int iter, int max_iters) {
    if (iter >= max_iters) return true;
    
    double tolerance = 1e-6;
    for (size_t i = 0; i < old_centroids.size(); ++i) {
        if (euclidean_distance(old_centroids[i], new_centroids[i]) > tolerance) {
            return false; // Un centroide se movió; el algoritmo debe continuar refinando
        }
    }
    return true; // Los centroides se estabilizaron por completo
}

std::vector<Labeled> run_kmeans(const std::vector<Coord_3D>& data, int k, std::vector<ClusterInfo>& summary) {
    int n = data.size();
    std::vector<Labeled> labeled_points(n);
    for (int i = 0; i < n; ++i) {
        labeled_points[i].coord = data[i];
    }

    // Inicialización aleatoria controlada de Centroides iniciales
    std::vector<Coord_3D> centroids(k);
    std::srand(std::time(0));
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[std::rand() % n];
    }

    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int max_iterations = 150;
    int iter = 0;
    bool stop = false;

    while (!stop) {
        std::vector<Coord_3D> old_centroids = centroids;

        // --- PASO A: ASIGNACIÓN ---
        for (int i = 0; i < n; ++i) {
            double min_dist = std::numeric_limits<double>::max();
            int best_cluster = 0;
            for (int j = 0; j < k; ++j) {
                double dist = euclidean_distance(labeled_points[i].coord, centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }
            labeled_points[i].label = alphabet[best_cluster];
        }

        // --- PASO B: ACTUALIZACIÓN (Cálculo del centro geométrico medio) ---
        std::vector<Coord_3D> sum_coords(k, {0.0, 0.0, 0.0});
        std::vector<int> counts(k, 0);

        for (int i = 0; i < n; ++i) {
            int c_idx = labeled_points[i].label - 'A';
            sum_coords[c_idx].x += labeled_points[i].coord.x;
            sum_coords[c_idx].y += labeled_points[i].coord.y;
            sum_coords[c_idx].z += labeled_points[i].coord.z;
            counts[c_idx]++;
        }

        for (int j = 0; j < k; ++j) {
            if (counts[j] > 0) {
                centroids[j].x = sum_coords[j].x / counts[j];
                centroids[j].y = sum_coords[j].y / counts[j];
                centroids[j].z = sum_coords[j].z / counts[j];
            }
        }

        iter++;
        stop = should_stop(old_centroids, centroids, iter, max_iterations);
    }

    // --- CÁLCULO DE LA MEDIDA DE DISPERSIÓN (MD: Desviación Media del Cluster) ---
    summary.clear();
    for (int j = 0; j < k; ++j) {
        ClusterInfo info;
        info.label = alphabet[j];
        info.centroid = centroids[j];
        info.count = 0;
        
        double total_distance = 0.0;
        for (int i = 0; i < n; ++i) {
            if (labeled_points[i].label == alphabet[j]) {
                total_distance += euclidean_distance(labeled_points[i].coord, centroids[j]);
                info.count++;
            }
        }
        // MD es la distancia promedio de los elementos asignados con respecto a su propio centroide
        info.dispersion = (info.count > 0) ? (total_distance / info.count) : 0.0;
        summary.push_back(info);
    }

    return labeled_points;
}