#ifndef CONFIG_ENTITY_H
#define CONFIG_ENTITY_H

#include <stdbool.h>

#include "../map.h"
#include "../config.h"

enum FaceDirection {
    FACE_UP,
    FACE_DOWN,
    FACE_LEFT,
    FACE_RIGHT
};

enum Location {
    MAP1,
    MAP2
};

#endif // CONFIG_ENTITY_H