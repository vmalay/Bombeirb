#include <SDL/SDL_image.h>
#include <assert.h>

#include <sprite.h>
#include <misc.h>

// Sprites general
#define MAP_CASE        "sprite/wood_box.png"
#define MAP_CASE2        "sprite/leaf_box.png"
#define MAP_KEY			"sprite/key.png"
#define MAP_DOOR_OPENED	"sprite/door_opened.png"
#define MAP_DOOR_OPENED2	"sprite/door_opened2.png"
#define MAP_DOOR_OPENED3	"sprite/door_opened3.png"
#define MAP_DOOR_CLOSED	"sprite/door_closed.png"
#define FOND1        "sprite/fond1.png"
#define FOND2       "sprite/fond2.png"
#define FOND3        "sprite/fond3.png"
// Scenery elements
#define MAP_STONE		"sprite/stone.png"
#define MAP_STONE2		"sprite/stone2.png"
#define MAP_TREE        "sprite/tree.png"
#define MAP_TREE2        "sprite/tree2.png"
#define MAP_TREE3        "sprite/tree3.png"
#define PRINCESS		"sprite/bomberwoman.png"
#define BANANA 			"sprite/big_monster.png"
#define SNOWMAN 			"sprite/snow_man.png"
#define SNOWBLOCK 			"sprite/block_snow.png"


#define BANNER_VIRGULE		"sprite/virgule.png"

// Sprites of Banner
#define BANNER_LINE		"sprite/banner_line.png"
#define BANNER_LIFE		"sprite/banner_life.png"
#define BANNER_BOMB		"sprite/bomb4.png"
#define BANNER_RANGE	"sprite/banner_range.png"
#define BANNER_KEY      "sprite/banner_key.png"
#define BANNER_0		"sprite/banner_0.jpg"
#define BANNER_1		"sprite/banner_1.jpg"
#define BANNER_2		"sprite/banner_2.jpg"
#define BANNER_3		"sprite/banner_3.jpg"
#define BANNER_4		"sprite/banner_4.jpg"
#define BANNER_5		"sprite/banner_5.jpg"
#define BANNER_6		"sprite/banner_6.jpg"
#define BANNER_7		"sprite/banner_7.jpg"
#define BANNER_8		"sprite/banner_8.jpg"
#define BANNER_9		"sprite/banner_9.jpg"
#define BANNER__0		"sprite/banner__0.png"
#define BANNER__1		"sprite/banner__1.png"
#define BANNER__2		"sprite/banner__2.png"
#define BANNER__3		"sprite/banner__3.png"
#define BANNER__4		"sprite/banner__4.png"
#define BANNER__5		"sprite/banner__5.png"
#define BANNER__6		"sprite/banner__6.png"
#define BANNER__7		"sprite/banner__7.png"
#define BANNER__8		"sprite/banner__8.png"
#define BANNER__9		"sprite/banner__9.png"

// Sprites of Bombs
#define BOMB_TTL1       "sprite/bomb1.png"
#define BOMB_TTL2       "sprite/bomb2.png"
#define BOMB_TTL3       "sprite/bomb3.png"
#define BOMB_TTL4       "sprite/bomb4.png"

//Sprite of fire
#define FIRE			"sprite/explosion.png"

// Sprites of Bonus
#define IMG_BONUS_BOMB_RANGE_INC  "sprite/bonus_bomb_range_inc1.png"
#define IMG_BONUS_BOMB_RANGE_DEC  "sprite/bonus_bomb_range_dec1.png"
#define IMG_BONUS_BOMB_NB_INC     "sprite/bonus_bomb_range_inc.png"
#define IMG_BONUS_BOMB_NB_DEC     "sprite/bonus_bomb_nb_dec.png"
#define IMG_BONUS_LIFE            "sprite/life.png"
#define IMG_BONUS_MONSTER            "sprite/monster_down.png"
#define IMG_BONUS_LIFE_DEC            "sprite/life_dec.png"
#define IMG_BONUS_DEAD            "sprite/dead_face.png"
#define IMG_BONUS_PUSH            "sprite/bonus_push.png"
#define IMG_BONUS_SHIELD            "sprite/bonus_shield.png"


// Sprites of Players
#define PLAYER_LEFT     "sprite/player_left.png"
#define PLAYER_UP       "sprite/player_up.png"
#define PLAYER_RIGHT    "sprite/player_right.png"
#define PLAYER_DOWN     "sprite/player_down.png"

// Sprites of Monsters
#define MONSTER_LEFT	"sprite/monster_left.png"
#define MONSTER_UP		"sprite/monster_up.png"
#define MONSTER_RIGHT	"sprite/monster_right.png"
#define MONSTER_DOWN	"sprite/monster_down.png"

#define MONSTER_LEFT2	"sprite/monster_left2.png"
#define MONSTER_UP2		"sprite/monster_up2.png"
#define MONSTER_RIGHT2	"sprite/monster_right2.png"
#define MONSTER_DOWN2	"sprite/monster_down2.png"

#define MONSTER_LEFT3	"sprite/monster_left3.png"
#define MONSTER_UP3	"sprite/monster_up3.png"
#define MONSTER_RIGHT3	"sprite/monster_right3.png"
#define MONSTER_DOWN3	"sprite/monster_down3.png"


#define DRAGON_LEFT	"sprite/dragon_left.png"
#define DRAGON_UP		"sprite/dragon_up.png"
#define DRAGON_RIGHT	"sprite/dragon_right.png"
#define DRAGON_DOWN	"sprite/dragon_down.png"

#define VAMPIRE_LEFT	"sprite/vampire_left.png"
#define VAMPIRE_UP		"sprite/vampire_up.png"
#define VAMPIRE_RIGHT	"sprite/vampire_right.png"
#define VAMPIRE_DOWN	"sprite/vampire_down.png"

#define SKELETON_LEFT	"sprite/skeleton_left.png"
#define SKELETON_UP		"sprite/skeleton_up.png"
#define SKELETON_RIGHT	"sprite/skeleton_right.png"
#define SKELETON_DOWN	"sprite/skeleton_down.png"

#define DOG_LEFT	"sprite/dog_left.png"
#define DOG_UP		"sprite/dog_up.png"
#define DOG_RIGHT	"sprite/dog_right.png"
#define DOG_DOWN	"sprite/dog_down.png"

#define SKELETON2_LEFT	"sprite/skeleton2_left.png"
#define SKELETON2_UP		"sprite/skeleton2_up.png"
#define SKELETON2_RIGHT	"sprite/skeleton2_right.png"
#define SKELETON2_DOWN	"sprite/skeleton2_down.png"

#define ORC_LEFT	"sprite/orc_left.png"
#define ORC_UP		"sprite/orc_up.png"
#define ORC_RIGHT	"sprite/orc_right.png"
#define ORC_DOWN	"sprite/orc_down.png"

#define chelou_LEFT	"sprite/chelou_left.png"
#define chelou_UP		"sprite/chelou_up.png"
#define chelou_RIGHT	"sprite/chelou_right.png"
#define chelou_DOWN	"sprite/chelou_down.png"

#define ryuk_LEFT	"sprite/ryuk_left.png"
#define ryuk_UP		"sprite/ryuk_up.png"
#define ryuk_RIGHT	"sprite/ryuk_right.png"
#define ryuk_DOWN	"sprite/ryuk_down.png"

#define bandage_LEFT	"sprite/bandage_left.png"
#define bandage_UP		"sprite/bandage_up.png"
#define bandage_RIGHT	"sprite/bandage_right.png"
#define bandage_DOWN	"sprite/bandage_down.png"

#define naked_LEFT	"sprite/naked_left.png"
#define naked_UP		"sprite/naked_up.png"
#define naked_RIGHT	"sprite/naked_right.png"
#define naked_DOWN	"sprite/naked_down.png"

#define mario_LEFT	"sprite/mario_left.png"
#define mario_UP		"sprite/mario_up.png"
#define mario_RIGHT	"sprite/mario_right.png"
#define mario_DOWN	"sprite/mario_down.png"

#define NARUTO_LEFT	"sprite/naruto_left.png"
#define NARUTO_UP		"sprite/naruto_up.png"
#define NARUTO_RIGHT	"sprite/naruto_right.png"
#define NARUTO_DOWN	"sprite/naruto_down.png"

#define NEGA_LEFT	"sprite/playerneg_left.png"
#define NEGA_UP		"sprite/playerneg_up.png"
#define NEGA_RIGHT	"sprite/playerneg_right.png"
#define NEGA_DOWN	"sprite/playerneg_down.png"

#define EMPTY	"sprite/empty.png"

// Sprites of Menu

#define VICTORY_RECORD "sprite/victory_best_score.png"
#define MENU "sprite/pannel.png"
#define MENU_OPTION0 "sprite/pannel_option1.png"
#define MENU_OPTION1 "sprite/pannel_option2.png"
#define MENU_OPTION2 "sprite/pannel_option3.png"
#define MENU_OPTION3 "sprite/pannel_option4.png"

#define MENU_FIRST "sprite/menu_bis.png"
#define MENU_0 "sprite/menu_0.png"
#define MENU_1 "sprite/menu_1.png"
#define MENU_2 "sprite/menu_2.png"
#define MENU_3 "sprite/menu_3.png"
#define MENU_4 "sprite/menu_4.png"
#define MENU_5 "sprite/menu_5.png"
#define MENU_6 "sprite/menu_6.png"
#define MENU_7 "sprite/menu_7.png"
#define MENU_8 "sprite/menu_8.png"
#define MENU_9 "sprite/menu_9.png"
#define MENU_10 "sprite/menu_10.png"
#define MENU_11 "sprite/menu_11.png"
#define MENU_12 "sprite/menu_12.png"
#define MENU_13 "sprite/menu_13.png"

#define MENU_14 "sprite/menu_14.png"
#define MENU_15 "sprite/menu_15.png"
#define MENU_16 "sprite/menu_16.png"
#define MENU_17 "sprite/menu_17.png"
#define MENU_18 "sprite/menu_18.png"
#define MENU_19 "sprite/menu_19.png"
#define MENU_20 "sprite/menu_20.png"
#define MENU_21 "sprite/menu_21.png"
#define MENU_22 "sprite/menu_22.png"
#define MENU_23 "sprite/menu_23.png"
#define MENU_24 "sprite/menu_24.png"
#define MENU_25 "sprite/menu_25.png"
#define MENU_26 "sprite/menu_26.png"
#define MENU_27 "sprite/menu_27.png"
#define MENU_28 "sprite/menu_28.png"
#define MENU_29 "sprite/menu_29.png"
#define MENU_30 "sprite/menu_30.png"
#define MENU_31 "sprite/menu_31.png"
#define MENU_32 "sprite/menu_32.png"
#define MENU_33 "sprite/menu_33.png"
#define MENU_34 "sprite/menu_34.png"
#define MENU_35 "sprite/menu_35.png"

#define PLAYER1_WIN_FINAL "sprite/player1_win_final.png"
#define PLAYER2_WIN_FINAL "sprite/player2_win_final.png"
#define PLAYER1_WIN_SCORE "sprite/player1_win_score.png"
#define PLAYER2_WIN_SCORE "sprite/player2_win_score.png"

#define QUICKPAUSE "sprite/pause.png"
#define QUICKSAVE "sprite/save.png"
#define QUICKLOAD "sprite/load.png"


#define SAVE "sprite/saving.png"
#define GAME_OVER "sprite/game_over.png"
#define GAME_WIN "sprite/game_win.png"

#define SAITAMA_LEFT	"sprite/saitama_left.png"
#define SAITAMA_UP		"sprite/saitama_up.png"
#define SAITAMA_RIGHT	"sprite/saitama_right.png"
#define SAITAMA_DOWN	"sprite/saitama_down.png"

#define PLAYER_P_LEFT	"sprite/player_left_p.png"
#define PLAYER_P_UP		"sprite/player_up_p.png"
#define PLAYER_P_RIGHT	"sprite/player_right_p.png"
#define PLAYER_P_DOWN	"sprite/player_down_p.png"

#define MARIO_P_LEFT	"sprite/mario_left_p.png"
#define MARIO_P_UP		"sprite/mario_up_p.png"
#define MARIO_P_RIGHT	"sprite/mario_right_p.png"
#define MARIO_P_DOWN	"sprite/mario_down_p.png"

#define SAITAMA_P_LEFT	"sprite/saitama_left_p.png"
#define SAITAMA_P_UP		"sprite/saitama_up_p.png"
#define SAITAMA_P_RIGHT	"sprite/saitama_right_p.png"
#define SAITAMA_P_DOWN	"sprite/saitama_down_p.png"

#define NARUTO_P_LEFT	"sprite/naruto_left_p.png"
#define NARUTO_P_UP		"sprite/naruto_up_p.png"
#define NARUTO_P_RIGHT	"sprite/naruto_right_p.png"
#define NARUTO_P_DOWN	"sprite/naruto_down_p.png"

#define GHOST_LEFT	"sprite/ghost_left.png"
#define GHOST_UP		"sprite/ghost_up.png"
#define GHOST_RIGHT	"sprite/ghost_right.png"
#define GHOST_DOWN	"sprite/ghost_down.png"


SDL_Surface* ghost_img[4];
SDL_Surface* player_p_img[4];
SDL_Surface* mario_p_img[4];
SDL_Surface* naruto_p_img[4];
SDL_Surface* saitama_p_img[4];


// banner
SDL_Surface* numbers[10];
SDL_Surface* numbers2[10];
SDL_Surface* banner_life;
SDL_Surface* banner_bomb;
SDL_Surface* banner_range;
SDL_Surface* banner_line;

// map
SDL_Surface* box;
SDL_Surface* box2;
SDL_Surface* goal;
SDL_Surface* key;
SDL_Surface* door_opened;
SDL_Surface* door_opened2;
SDL_Surface* door_opened3;
SDL_Surface* door_closed;
SDL_Surface* stone;
SDL_Surface* stone2;
SDL_Surface* tree;
SDL_Surface* tree2;
SDL_Surface* tree3;
SDL_Surface* princess;
SDL_Surface* banana;
SDL_Surface* snowman;
SDL_Surface* snowblock;
SDL_Surface* bomb_img[6];
SDL_Surface* fond1;
SDL_Surface* fond2;
SDL_Surface* fond3;
//fire
SDL_Surface* fire;


// bonus #define NB_BONUS 10

SDL_Surface* bonus[10+1];

// player
SDL_Surface* player_img[4];
SDL_Surface* naruto_img[4];
SDL_Surface* empty_img;
SDL_Surface* mario_img[4];
SDL_Surface* saitama_img[4];
SDL_Surface* nega_img[4];
// monster
SDL_Surface* monster_img[4];
SDL_Surface* monster2_img[4];
SDL_Surface* monster3_img[4];

SDL_Surface* dragon_img[4];
SDL_Surface* vampire_img[4];
SDL_Surface* skeleton_img[4];
SDL_Surface* dog_img[4];
SDL_Surface* skeleton2_img[4];
SDL_Surface* orc_img[4];
SDL_Surface* naked_img[4];

SDL_Surface* ryuk_img[4];
SDL_Surface* chelou_img[4];
SDL_Surface* bandage_img[4];
SDL_Surface* banner_virgule;



// menu
SDL_Surface* menu_img[4];
SDL_Surface* system_menu_img[36];
SDL_Surface* save_img;
SDL_Surface* player_win[4];


SDL_Surface* quicksave_img;
SDL_Surface* quickpause_img;
SDL_Surface* quickload_img;
SDL_Surface* game_over_img;
SDL_Surface* game_win_img;

SDL_Surface* score_record;


static void banner_load() {
	// numbers imgs
	numbers[0] = load_image(BANNER_0);
	numbers[1] = load_image(BANNER_1);
	numbers[2] = load_image(BANNER_2);
	numbers[3] = load_image(BANNER_3);
	numbers[4] = load_image(BANNER_4);
	numbers[5] = load_image(BANNER_5);
	numbers[6] = load_image(BANNER_6);
	numbers[7] = load_image(BANNER_7);
	numbers[8] = load_image(BANNER_8);
	numbers[9] = load_image(BANNER_9);
	numbers2[0] = load_image(BANNER__0);
	numbers2[1] = load_image(BANNER__1);
	numbers2[2] = load_image(BANNER__2);
	numbers2[3] = load_image(BANNER__3);
	numbers2[4] = load_image(BANNER__4);
	numbers2[5] = load_image(BANNER__5);
	numbers2[6] = load_image(BANNER__6);
	numbers2[7] = load_image(BANNER__7);
	numbers2[8] = load_image(BANNER__8);
	numbers2[9] = load_image(BANNER__9);

	// other banner sprites
	banner_life = load_image(BANNER_LIFE);
	banner_bomb = load_image(BANNER_BOMB);
	banner_range = load_image(BANNER_RANGE);
	banner_line = load_image(BANNER_LINE);
	banner_virgule = load_image(BANNER_VIRGULE);
}

static void banner_unload() {
	// numbers imgs
	for (int i = 0; i < 10; i++) {
		SDL_FreeSurface(numbers[i]);
	}

	// other banner sprites
	SDL_FreeSurface(banner_life);
	SDL_FreeSurface(banner_bomb);
	SDL_FreeSurface(banner_range);
	SDL_FreeSurface(banner_life);
}

static void map_load() {
	// Sprite loading

	princess = load_image(PRINCESS);
	tree = load_image(MAP_TREE);
	box = load_image(MAP_CASE);
	box2 = load_image(MAP_CASE2);
	key = load_image(MAP_KEY);
	stone = load_image(MAP_STONE);
	banana = load_image(BANANA);
	snowman = load_image(SNOWMAN);
	snowblock = load_image(SNOWBLOCK);
	tree2 = load_image(MAP_TREE2);
	tree3 = load_image(MAP_TREE3);
	stone2 = load_image(MAP_STONE2);
	door_opened = load_image(MAP_DOOR_OPENED);
	door_opened2 = load_image(MAP_DOOR_OPENED2);
	door_opened3 = load_image(MAP_DOOR_OPENED3);
	door_closed = load_image(MAP_DOOR_CLOSED);

	fond1 = load_image(FOND1);
	fond2 = load_image(FOND2);
	fond3 = load_image(FOND3);
	// pause & save:

	quickpause_img = load_image(QUICKPAUSE);
	quicksave_img = load_image(QUICKSAVE);
	quickload_img = load_image(QUICKLOAD);
}

static void bonus_load() {
	bonus[0] = NULL;
	bonus[BONUS_BOMB_RANGE_DEC] = load_image(IMG_BONUS_BOMB_RANGE_DEC);
	bonus[BONUS_BOMB_RANGE_INC] = load_image(IMG_BONUS_BOMB_RANGE_INC);
	bonus[BONUS_BOMB_NB_DEC] = load_image(IMG_BONUS_BOMB_NB_DEC);
	bonus[BONUS_BOMB_NB_INC] = load_image(IMG_BONUS_BOMB_NB_INC);
	bonus[BONUS_MONSTER] = load_image(IMG_BONUS_MONSTER);
	bonus[BONUS_LIFE] = load_image(IMG_BONUS_LIFE);
	bonus[BONUS_LIFE_DEC] = load_image(IMG_BONUS_LIFE_DEC);
	bonus[BONUS_DEAD] = load_image(IMG_BONUS_DEAD);
	bonus[BONUS_PUSH] = load_image(IMG_BONUS_PUSH);
	bonus[BONUS_SHIELD] = load_image(IMG_BONUS_SHIELD);
}

static void bonus_unload() {
	for (int i = 0; i < 8; i++)
		SDL_FreeSurface(bonus[i]);
}

static void player_load() {
	player_img[WEST] = load_image(PLAYER_LEFT);
	player_img[EAST] = load_image(PLAYER_RIGHT);
	player_img[NORTH] = load_image(PLAYER_UP);
	player_img[SOUTH] = load_image(PLAYER_DOWN);
}

static void monster_load() {
	monster_img[WEST] = load_image(MONSTER_LEFT);
	monster_img[EAST] = load_image(MONSTER_RIGHT);
	monster_img[NORTH] = load_image(MONSTER_UP);
	monster_img[SOUTH] = load_image(MONSTER_DOWN);
}

static void monster2_load() {
	monster2_img[WEST] = load_image(MONSTER_LEFT2);
	monster2_img[EAST] = load_image(MONSTER_RIGHT2);
	monster2_img[NORTH] = load_image(MONSTER_UP2);
	monster2_img[SOUTH] = load_image(MONSTER_DOWN2);
}

static void monster3_load() {
	monster3_img[WEST] = load_image(MONSTER_LEFT3);
	monster3_img[EAST] = load_image(MONSTER_RIGHT3);
	monster3_img[NORTH] = load_image(MONSTER_UP3);
	monster3_img[SOUTH] = load_image(MONSTER_DOWN3);
}

static void dragon_load() {
	dragon_img[WEST] = load_image(DRAGON_LEFT);
	dragon_img[EAST] = load_image(DRAGON_RIGHT);
	dragon_img[NORTH] = load_image(DRAGON_UP);
	dragon_img[SOUTH] = load_image(DRAGON_DOWN);
}

static void vampire_load() {
	vampire_img[WEST] = load_image(VAMPIRE_LEFT);
	vampire_img[EAST] = load_image(VAMPIRE_RIGHT);
	vampire_img[NORTH] = load_image(VAMPIRE_UP);
	vampire_img[SOUTH] = load_image(VAMPIRE_DOWN);
}

static void skeleton_load() {
	skeleton_img[WEST] = load_image(SKELETON_LEFT);
	skeleton_img[EAST] = load_image(SKELETON_RIGHT);
	skeleton_img[NORTH] = load_image(SKELETON_UP);
	skeleton_img[SOUTH] = load_image(SKELETON_DOWN);
}

static void dog_load() {
	dog_img[WEST] = load_image(DOG_LEFT);
	dog_img[EAST] = load_image(DOG_RIGHT);
	dog_img[NORTH] = load_image(DOG_UP);
	dog_img[SOUTH] = load_image(DOG_DOWN);
}

static void skeleton2_load() {
	skeleton2_img[WEST] = load_image(SKELETON2_LEFT);
	skeleton2_img[EAST] = load_image(SKELETON2_RIGHT);
	skeleton2_img[NORTH] = load_image(SKELETON2_UP);
	skeleton2_img[SOUTH] = load_image(SKELETON2_DOWN);
}

static void orc_load() {
	orc_img[WEST] = load_image(ORC_LEFT);
	orc_img[EAST] = load_image(ORC_RIGHT);
	orc_img[NORTH] = load_image(ORC_UP);
	orc_img[SOUTH] = load_image(ORC_DOWN);
}

static void chelou_load() {
	chelou_img[WEST] = load_image(chelou_LEFT);
	chelou_img[EAST] = load_image(chelou_RIGHT);
	chelou_img[NORTH] = load_image(chelou_UP);
	chelou_img[SOUTH] = load_image(chelou_DOWN);
}

static void ryuk_load() {
	ryuk_img[WEST] = load_image(ryuk_LEFT);
	ryuk_img[EAST] = load_image(ryuk_RIGHT);
	ryuk_img[NORTH] = load_image(ryuk_UP);
	ryuk_img[SOUTH] = load_image(ryuk_DOWN);
}

static void bandage_load() {
	bandage_img[WEST] = load_image(bandage_LEFT);
	bandage_img[EAST] = load_image(bandage_RIGHT);
	bandage_img[NORTH] = load_image(bandage_UP);
	bandage_img[SOUTH] = load_image(bandage_DOWN);
}

static void naked_load() {
	naked_img[WEST] = load_image(naked_LEFT);
	naked_img[EAST] = load_image(naked_RIGHT);
	naked_img[NORTH] = load_image(naked_UP);
	naked_img[SOUTH] = load_image(naked_DOWN);
}

static void mario_load() {
	mario_img[WEST] = load_image(mario_LEFT);
	mario_img[EAST] = load_image(mario_RIGHT);
	mario_img[NORTH] = load_image(mario_UP);
	mario_img[SOUTH] = load_image(mario_DOWN);
}

static void naruto_load() {
	naruto_img[WEST] = load_image(NARUTO_LEFT);
	naruto_img[EAST] = load_image(NARUTO_RIGHT);
	naruto_img[NORTH] = load_image(NARUTO_UP);
	naruto_img[SOUTH] = load_image(NARUTO_DOWN);
}

static void saitama_load() {
	saitama_img[WEST] = load_image(SAITAMA_LEFT);
	saitama_img[EAST] = load_image(SAITAMA_RIGHT);
	saitama_img[NORTH] = load_image(SAITAMA_UP);
	saitama_img[SOUTH] = load_image(SAITAMA_DOWN);
}

static void naruto_p_load() {
	naruto_p_img[WEST] = load_image(NARUTO_P_LEFT);
	naruto_p_img[EAST] = load_image(NARUTO_P_RIGHT);
	naruto_p_img[NORTH] = load_image(NARUTO_P_UP);
	naruto_p_img[SOUTH] = load_image(NARUTO_P_DOWN);
}

static void saitama_p_load() {
	saitama_p_img[WEST] = load_image(SAITAMA_P_LEFT);
	saitama_p_img[EAST] = load_image(SAITAMA_P_RIGHT);
	saitama_p_img[NORTH] = load_image(SAITAMA_P_UP);
	saitama_p_img[SOUTH] = load_image(SAITAMA_P_DOWN);
}

static void mario_p_load() {
	mario_p_img[WEST] = load_image(MARIO_P_LEFT);
	mario_p_img[EAST] = load_image(MARIO_P_RIGHT);
	mario_p_img[NORTH] = load_image(MARIO_P_UP);
	mario_p_img[SOUTH] = load_image(MARIO_P_DOWN);
}

static void player_p_load() {
	player_p_img[WEST] = load_image(PLAYER_P_LEFT);
	player_p_img[EAST] = load_image(PLAYER_P_RIGHT);
	player_p_img[NORTH] = load_image(PLAYER_P_UP);
	player_p_img[SOUTH] = load_image(PLAYER_P_DOWN);
}

static void ghost_load() {
	ghost_img[WEST] = load_image(GHOST_LEFT);
	ghost_img[EAST] = load_image(GHOST_RIGHT);
	ghost_img[NORTH] = load_image(GHOST_UP);
	ghost_img[SOUTH] = load_image(GHOST_DOWN);
}

static void nega_load() {
	nega_img[WEST] = load_image(NEGA_LEFT);
	nega_img[EAST] = load_image(NEGA_RIGHT);
	nega_img[NORTH] = load_image(NEGA_UP);
	nega_img[SOUTH] = load_image(NEGA_DOWN);
}




static void map_unload() {
	SDL_FreeSurface(tree);
	SDL_FreeSurface(tree2);
	SDL_FreeSurface(tree3);
	SDL_FreeSurface(box);
	SDL_FreeSurface(box2);
	SDL_FreeSurface(goal);
	SDL_FreeSurface(key);
	SDL_FreeSurface(stone);
	SDL_FreeSurface(stone2);
	SDL_FreeSurface(banana);
	SDL_FreeSurface(door_opened);
	SDL_FreeSurface(door_opened2);
	SDL_FreeSurface(door_opened3);
	SDL_FreeSurface(door_closed);
	SDL_FreeSurface(princess);
	SDL_FreeSurface(snowman);
	SDL_FreeSurface(snowblock);
	SDL_FreeSurface(quickload_img);
	SDL_FreeSurface(quickpause_img);
	SDL_FreeSurface(quicksave_img);

	SDL_FreeSurface(fond1);
	SDL_FreeSurface(fond2);
	SDL_FreeSurface(fond3);
}


static void player_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(player_img[i]);
}

static void monster_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(monster_img[i]);
}

static void monster2_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(monster2_img[i]);
}

static void monster3_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(monster3_img[i]);
}

static void mario_unload() {
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(mario_img[i]);
}


void menu_load(){
	menu_img[0] = load_image(MENU_OPTION0);
	menu_img[1] = load_image(MENU_OPTION1);
	menu_img[2] = load_image(MENU_OPTION2);
	menu_img[3] = load_image(MENU_OPTION3);

	system_menu_img[0] = load_image(MENU_0);
	system_menu_img[1] = load_image(MENU_1);
	system_menu_img[2] = load_image(MENU_2);
	system_menu_img[3] = load_image(MENU_3);
	system_menu_img[4] = load_image(MENU_4);
	system_menu_img[5] = load_image(MENU_5);

	system_menu_img[6] = load_image(MENU_6);
	system_menu_img[7] = load_image(MENU_7);
	system_menu_img[8] = load_image(MENU_8);
	system_menu_img[9] = load_image(MENU_9);
	system_menu_img[10] = load_image(MENU_10);
	system_menu_img[11] = load_image(MENU_11);
	system_menu_img[12] = load_image(MENU_12);
	system_menu_img[13] = load_image(MENU_13);
	system_menu_img[14] = load_image(MENU_14);
	system_menu_img[15] = load_image(MENU_15);
	system_menu_img[16] = load_image(MENU_16);
	system_menu_img[17] = load_image(MENU_17);
	system_menu_img[18] = load_image(MENU_18);
	system_menu_img[19] = load_image(MENU_19);
	system_menu_img[20] = load_image(MENU_20);
	system_menu_img[21] = load_image(MENU_21);
	system_menu_img[22] = load_image(MENU_22);
	system_menu_img[23] = load_image(MENU_23);
	system_menu_img[24] = load_image(MENU_24);
	system_menu_img[25] = load_image(MENU_25);
	system_menu_img[26] = load_image(MENU_26);
	system_menu_img[27] = load_image(MENU_27);
	system_menu_img[28] = load_image(MENU_28);
	system_menu_img[29] = load_image(MENU_29);
	system_menu_img[30] = load_image(MENU_30);
	system_menu_img[31] = load_image(MENU_31);
	system_menu_img[32] = load_image(MENU_32);
	system_menu_img[33] = load_image(MENU_33);
	system_menu_img[34] = load_image(MENU_34);
	system_menu_img[35] = load_image(MENU_35);


	//Change 2
	score_record = load_image(VICTORY_RECORD);
	save_img = load_image(SAVE);
	game_over_img = load_image(GAME_OVER);
	game_win_img = load_image(GAME_WIN);
	player_win[0]= load_image(PLAYER1_WIN_FINAL);
	player_win[1]= load_image(PLAYER2_WIN_FINAL);
	player_win[2]= load_image(PLAYER1_WIN_SCORE);
	player_win[3]= load_image(PLAYER2_WIN_SCORE);

}

void menu_unload(){
	SDL_FreeSurface(system_menu_img[0]);
	SDL_FreeSurface(system_menu_img[1]);
	SDL_FreeSurface(system_menu_img[2]);
	SDL_FreeSurface(system_menu_img[3]);
	SDL_FreeSurface(system_menu_img[4]);

	SDL_FreeSurface(system_menu_img[5]);
	SDL_FreeSurface(system_menu_img[6]);
	SDL_FreeSurface(system_menu_img[7]);
	SDL_FreeSurface(system_menu_img[8]);
	SDL_FreeSurface(system_menu_img[9]);
	SDL_FreeSurface(system_menu_img[10]);
	SDL_FreeSurface(system_menu_img[11]);
	SDL_FreeSurface(system_menu_img[12]);
	SDL_FreeSurface(system_menu_img[13]);
	SDL_FreeSurface(system_menu_img[14]);
	SDL_FreeSurface(system_menu_img[15]);
	SDL_FreeSurface(system_menu_img[16]);
	SDL_FreeSurface(system_menu_img[17]);
	SDL_FreeSurface(system_menu_img[18]);
	SDL_FreeSurface(system_menu_img[19]);
	SDL_FreeSurface(system_menu_img[20]);
	SDL_FreeSurface(system_menu_img[21]);
	SDL_FreeSurface(system_menu_img[22]);
	SDL_FreeSurface(system_menu_img[23]);
	SDL_FreeSurface(system_menu_img[24]);
	SDL_FreeSurface(system_menu_img[25]);
	SDL_FreeSurface(system_menu_img[26]);
	SDL_FreeSurface(system_menu_img[27]);
	SDL_FreeSurface(system_menu_img[28]);
	SDL_FreeSurface(system_menu_img[29]);
	SDL_FreeSurface(system_menu_img[30]);
	SDL_FreeSurface(system_menu_img[31]);
	SDL_FreeSurface(system_menu_img[32]);
	SDL_FreeSurface(system_menu_img[33]);
	SDL_FreeSurface(system_menu_img[34]);

	SDL_FreeSurface(menu_img[0]);
	SDL_FreeSurface(menu_img[1]);
	SDL_FreeSurface(menu_img[2]);
	SDL_FreeSurface(menu_img[3]);

	SDL_FreeSurface(player_win[0]);
	SDL_FreeSurface(player_win[1]);
	SDL_FreeSurface(player_win[2]);
	SDL_FreeSurface(player_win[3]);
}

void bomb_load() {
	bomb_img[0] = NULL;
	bomb_img[4] = load_image(BOMB_TTL4);
	bomb_img[3] = load_image(BOMB_TTL3);
	bomb_img[2] = load_image(BOMB_TTL2);
	bomb_img[1] = load_image(BOMB_TTL1);

	fire = load_image(FIRE);
}

void bomb_unload() {
	for (int i = 0; i < 5; i++)
		SDL_FreeSurface(bomb_img[i]);

	SDL_FreeSurface(fire);

}


void sprite_load() {
	map_load();
	bonus_load();
	banner_load();
	player_load();
	monster_load();
	monster2_load();
	monster3_load();
	dragon_load();
	vampire_load();
	skeleton_load();
	dog_load();
	skeleton2_load();
	orc_load();
	mario_load();
	chelou_load();
	ryuk_load();
	bandage_load();
	naked_load();
	menu_load();
	bomb_load();
	naruto_load();
	saitama_load();
	empty_img = load_image(EMPTY);
	mario_p_load();
	naruto_p_load();
	saitama_p_load();
	player_p_load();
	ghost_load();
	nega_load();

}

void sprite_free() {
	map_unload();
	bonus_unload();
	banner_unload();
	player_unload();
	monster_unload();
	monster2_unload();
	monster3_unload();
	menu_unload();
	bomb_unload();
	mario_unload();
}

SDL_Surface* sprite_get_player_win(short number) {
	if (number > 3)
		return player_win[3];
	else
		return player_win[number];
}


SDL_Surface* sprite_get_number(short number) {
	if (number > 8)
		return numbers[8];
	else
		return numbers[number];
}
SDL_Surface* sprite_get__number(short number) {
	if (number > 8)
		return numbers2[8];
	else
		return numbers2[number];
}

SDL_Surface* sprite_get_player(enum direction way, int character, int state) {
	assert(player_img[way]);
	if (state == 0 || state == 5){
		if (character==0)
			return player_img[way];
		if (character==1)
			return mario_img[way];
		if (character==2)
			return naruto_img[way];
		if (character==3)
			return saitama_img[way];
	}

	if (state==1)
		return ghost_img[way];

	if (state==2)
		return nega_img[way];

	if (state==3){
		if (character==0)
			return player_p_img[way];
		if (character==1)
			return mario_p_img[way];
		if (character==2)
			return naruto_p_img[way];
		if (character==3)
			return saitama_p_img[way];
	}
	if (state==4)  // State 4 and 5 are reserved for "player get attacked".
		return empty_img;

	else
		return player_img[way];
}


SDL_Surface* sprite_get_monster(enum direction way, int world, int sub_type) {

	assert(monster_img[way]);
	if (sub_type == 1)
		return chelou_img[way];
	if (sub_type == 2)
		return dragon_img[way];
	if (sub_type == 3)
		return vampire_img[way];
	if (sub_type == 4)
		return skeleton_img[way];
	if (sub_type == 5)
		return dog_img[way];
	if (sub_type == 6)
		return skeleton2_img[way];
	if (sub_type == 8)
		return orc_img[way];
	if (sub_type == 9)
		return bandage_img[way];
	if (sub_type == 10)
		return ryuk_img[way];
	if (sub_type == 11)
		return naked_img[way];
	else
	{
		if (world == 1)
			return monster_img[way];

		else if (world == 2)
			return monster2_img[way];

		else
			return monster3_img[way];
	}
}

SDL_Surface* sprite_get_bomb(int bomb_state) {
	assert(bomb_img[bomb_state]);
	return bomb_img[bomb_state];
}

SDL_Surface* sprite_get_banner_life() {
	assert(banner_life);
	return banner_life;
}

SDL_Surface* sprite_get_banner_bomb() {
	assert(banner_bomb);
	return banner_bomb;
}

//Change 2
SDL_Surface* sprite_record_victory() {
	assert(score_record);
	return score_record;
}

SDL_Surface* sprite_get_banner_line() {
	assert(banner_line);
	return banner_line;
}

SDL_Surface* sprite_virgule() {
	assert(banner_virgule);
	return banner_virgule;
}

SDL_Surface* sprite_get_banner_range() {
	assert(banner_range);
	return banner_range;
}

SDL_Surface* sprite_get_bonus(enum bonus_type bonus_type) {
	assert(bonus[bonus_type]);
	return bonus[bonus_type];
}

SDL_Surface* sprite_get_tree(int world) {
	assert(tree);

	if (world==1)
		return tree;

	else if (world==2)
		return tree2;
	else if (world==3)
		return tree3;
	else
		return tree;
}

SDL_Surface* sprite_get_tree2() {
	assert(tree2);
	return tree2;
}


SDL_Surface* sprite_get_princess() {
	assert(princess);
	return princess;
}

SDL_Surface* sprite_get_box(int world) {
	assert(box);

	if (world==1)
		return box;
	else if (world==2)
		return box2;
	else if (world==3)
		return snowman;
	else
		return box;
}

SDL_Surface* sprite_get_key() {
	assert(key);
	return key;
}

SDL_Surface* sprite_get_stone(int world) {
	assert(stone);

	if (world==1)
		return stone;

	else if (world==2)
		return stone2;

	else if (world==3)
		return snowblock;
	else
		return stone;
}

SDL_Surface* sprite_get_stone2() {
	assert(stone2);
	return stone2;
}

SDL_Surface* sprite_get_fire() {
	assert(fire);
	return fire;
}


SDL_Surface* sprite_get_door_opened(int number) {
	assert(door_opened3);
	if (number==1)
		return door_opened;
	else if (number==2)
		return door_opened2;
	else
		return door_opened3;

}

SDL_Surface* sprite_get_door_closed() {
	assert(door_closed);
	return door_closed;
}

SDL_Surface* sprite_get_menu(int number) {
	assert(menu_img[number]);
	return menu_img[number];
}

SDL_Surface* sprite_get_system_menu(int number) {
	assert(system_menu_img[number]);
	return system_menu_img[number];
}

SDL_Surface* sprite_get_saving() {
	assert(save_img);
	return save_img;
}

SDL_Surface* sprite_get_quicksave() {
	assert(quicksave_img);
	return quicksave_img;
}

SDL_Surface* sprite_get_quickpause() {
	assert(quicksave_img);
	return quickpause_img;
}

SDL_Surface* sprite_get_quickload() {
	assert(quickload_img);
	return quickload_img;
}


SDL_Surface*sprite_get_game_over() {
	assert(game_over_img);
	return game_over_img;
}

SDL_Surface*sprite_get_game_win() {
	assert(game_win_img);
	return game_win_img;
}

SDL_Surface* sprite_get_banana() {
	assert(banana);
	return banana;
}

SDL_Surface* sprite_get_snowman() {
	assert(snowman);
	return snowman;
}

SDL_Surface* sprite_get_snowblock() {
	assert(snowblock);
	return snowblock;
}

SDL_Surface* sprite_get_fond(int world) {
	assert(fond1);
	if (world==1)
		return fond1;

	else if (world==2)
		return fond2;

	else if (world==3)
		return fond3;

	else
		return fond1;
}
