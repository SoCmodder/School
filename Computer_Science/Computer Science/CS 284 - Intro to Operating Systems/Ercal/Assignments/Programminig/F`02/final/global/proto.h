
#ifndef PROTO_H
#define PROTO_H

#define SERVER_PORT		2782

#define LEVEL_COUNT		2

#define HOUSE_WIDTH		30
#define HOUSE_HEIGHT		30

#define MESSAGE_LENGTH	64

typedef enum {
	TYPE_HOUSE		= 0,
	TYPE_GRASS		= 1,
	TYPE_FLOOR		= 2,
	TYPE_WALL		= 3,
	TYPE_BED			= 4,
	TYPE_BIGBED		= 5,
	TYPE_DRESSER	= 6,
	TYPE_SOFA		= 7,
	TYPE_TABLE		= 8,
	TYPE_CHAIR		= 9,
	TYPE_DOOR		= 10,
	TYPE_WINDOW		= 11,
	TYPE_SINK		= 12,
	TYPE_TOILET		= 13,
	TYPE_FRIDGE		= 14,
	TYPE_STOVE		= 15,
	TYPE_SHOWER		= 16,
	TYPE_LAMP		= 17,
	TYPE_TV			= 18,
	TYPE_KID			= 19,
	TYPE_PERSON		= 20
} BlockType;

typedef enum {
	TYPE_DOOR_OPEN		= 21,
	TYPE_WINDOW_OPEN	= 22,
	TYPE_SINK_ON1		= 23,
	TYPE_SINK_ON2		= 24,
	TYPE_SINK_ON3		= 25,
	TYPE_TOILET_DIRTY	= 26,
	TYPE_FRIDGE_ON1	= 27,
	TYPE_FRIDGE_ON2	= 28,
	TYPE_FRIDGE_ON3	= 29,
	TYPE_STOVE_ON		= 30,
	TYPE_SHOWER_ON1	= 31,
	TYPE_SHOWER_ON2	= 32,
	TYPE_SHOWER_ON3	= 33,
	TYPE_LAMP_ON		= 34,
	TYPE_TV_ON1			= 35,
	TYPE_TV_ON2			= 36,
	TYPE_TV_ON3			= 37,
	TYPE_KID1			= 38,
	TYPE_KID2			= 39,
	TYPE_KID3			= 40,
	TYPE_PERSON1		= 41,
	TYPE_PERSON2		= 42,
	TYPE_PERSON3		= 43
} AnimatedBlockType;

typedef struct {
	BlockType type;
	int active;
	int locked ;
	int level[LEVEL_COUNT];
} ObjectType;

typedef struct {
	int oldx, oldy;
	int newx, newy;
	ObjectType oldObject;
	ObjectType newObject;
} UpdateObjectType;

extern ObjectType map[HOUSE_HEIGHT][HOUSE_WIDTH];
extern ObjectType houseObject;

#endif

