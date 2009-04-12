#ifndef NodeID_h
#define NodeID_h

// these defines translate IDs that are put on nodes in the level, into position markers for various actors

#define NODE_ID_ENEMYSPAWNER 1
#define NODE_ID_DYNAMITEPICKUP 2
#define NODE_ID_SNOWPLOWPICKUP 3
#define NODE_ID_TREE 4

//for NODE ID=-1, no triangle selector should be added
#define NODE_ID_FENCE_TO_FALL -1
#define NODE_ID_ENEMYSPAWNER2 6
#define NODE_ID_PLAYERSPAWN_ONE 7
#define NODE_ID_PLAYERSPAWN_TWO 8
#define NODE_ID_TRI_NEEDED 2

//Scene 1
#define NODE_ID_SCENE1 110
#define NODE_ID_SCENE1_TRI_NEEDED 112
#define NODE_ID_SCENE1_FALL -111
//Scene 2
#define NODE_ID_SCENE2 220
#define NODE_ID_SCENE2_TRI_NEEDED 222
#define NODE_ID_SCENE2_FALL -221
//Scene 3
#define NODE_ID_SCENE3 330
#define NODE_ID_SCENE3_TRI_NEEDED 332
#define NODE_ID_SCENE3_FALL -331
//Scene 4
#define NODE_ID_SCENE4 440
#define NODE_ID_SCENE4_TRI_NEEDED 442
#define NODE_ID_SCENE4_FALL -441

//house ID = 20
#define NODE_ID_HOUSE 20

#endif // NodeID_h
