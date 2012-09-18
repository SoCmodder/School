
#include "object.h"
#include "../global/proto.h"
#include "../global/debug.h"

const ObjectDataType objectDataMap[] = {

	/* type,				width,	height,	activatable */
	{ TYPE_HOUSE,		1,			1,			0		},
	{ TYPE_GRASS,		1,			1,			0		},
	{ TYPE_FLOOR,		1,			1,			0		},
	{ TYPE_WALL,		1,			1,			0		},
	{ TYPE_BED,			5,			2,			0		},
	{ TYPE_BIGBED,		5,			4,			0		},
	{ TYPE_DRESSER,	4,			4,			0		},
	{ TYPE_SOFA,		4,			2,			0		},
	{ TYPE_TABLE,		8,			8,			0		},
	{ TYPE_CHAIR,		3,			3,			0		},
	{ TYPE_DOOR,		1,			1,			1		},
	{ TYPE_WINDOW,		1,			1,			1		},
	{ TYPE_SINK,		2,			2,			1		},
	{ TYPE_TOILET,		2,			2,			1		},
	{ TYPE_FRIDGE,		3,			5,			1		},
	{ TYPE_STOVE,		4,			4,			1		},
	{ TYPE_SHOWER,		2,			4,			1		},
	{ TYPE_LAMP,		1,			1,			1		},
	{ TYPE_TV,			2,			2,			1		},
	{ TYPE_KID,			1,			1,			0		},
	{ TYPE_PERSON,		1,			1,			0		}

};

