#ifndef STRUCTURES_H
#define STRUCTURES_H

// Estructura obligatoria para representar un punto espacial tridimensional
struct Coord_3D {
    double x;
    double y;
    double z;
};

// Estructura útil para asociar coordenadas con su cluster final
struct Labeled {
    Coord_3D coord;
    char label;
};

#endif