#ifndef WRITER_H
#define WRITER_H
#include <vector>
#include <string>
#include "structures.h"
#include "kmeans.h"

void write_results(const std::string& csv_file, const std::vector<Labeled>& points,
                   const std::string& summary_file, const std::vector<ClusterInfo>& summary);
#endif