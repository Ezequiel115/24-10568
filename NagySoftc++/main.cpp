#include <iostream>
#include <string>
#include "loader.h"
#include "kmeans.h"
#include "writer.h"

int main(int argc, char* argv[]) {
    // Verificación obligatoria de firma de invocación
    if (argc < 3) {
        std::cerr << "Error de sintaxis corporativa. Use: cluster <k> <datos>" << std::endl;
        return 1;
    }

    int k = std::stoi(argv[1]);
    std::string dataset_path = argv[2];

    // Control de Overfitting según políticas de NagySoft
    if (k < 1 || k > 6) {
        std::cerr << "Error: El Dr. Szilard limito la ejecucion entre 1 y 6 clusters." << std::endl;
        return 1;
    }

    // Carga inmutable (Uso de const garantiza que los datos originales no cambien)
    const std::vector<Coord_3D> original_data = load_data(dataset_path);
    if (original_data.empty()) return 1;

    std::cout << "[NagySoft] Procesando " << original_data.size() << " puntos tridimensionales..." << std::endl;

    // Procesamiento matemático
    std::vector<ClusterInfo> summary_metrics;
    std::vector<Labeled> final_classification = run_kmeans(original_data, k, summary_metrics);

    // Persistencia de los entregables de la empresa
    write_results("clasificados.csv", final_classification, "summary.txt", summary_metrics);

    std::cout << "[NagySoft] Archivos corporativos 'clasificados.csv' y 'summary.txt' generados con exito." << std::endl;
    return 0;
}