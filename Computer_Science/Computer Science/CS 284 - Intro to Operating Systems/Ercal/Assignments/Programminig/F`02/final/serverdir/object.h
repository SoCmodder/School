
#ifndef OBJECT_H
#define OBJECT_H

#include "../global/proto.h"

typedef struct {
	BlockType type;
	int width;
	int height;
	int activatable;
} ObjectDataType;

extern const ObjectDataType objectDataMap[];

#endif

