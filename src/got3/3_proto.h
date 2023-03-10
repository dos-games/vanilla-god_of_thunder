// THOR - The God of Thunder
//Source code released to the public domain on March 27th, 2020.


//G_LIB.LIB

void xsetmode(void);
void xshowpage(unsigned page);
void xline(int x0,int y0,int x1,int y1,int page,int color);
void xfillrectangle(int StartX, int StartY, int EndX, int EndY,
                    unsigned int PageBase, int Color);
void xpset(int X, int Y, unsigned int PageBase, int Color);
int  xpoint(int X, int Y, unsigned int PageBase);
void xget(int x1,int y1,int x2,int y2,unsigned int pagebase,
          char far *buff,int invis);
void xput(int x,int y,unsigned int pagebase,char *buff);
void xput2(int x,int y,unsigned int pagebase,char *buff);
void xtext(int x,int y,unsigned int pagebase,char far *buff,int color);
void xtext1(int x,int y,unsigned int pagebase,char far *buff,int color);
void xtextx(int x,int y,unsigned int pagebase,char far *buff,int color);

void xfput(int x,int y,unsigned int pagebase,char far *buff);
void xfarput(int x,int y,unsigned int pagebase,char far *buff);
void xcopyd2dmasked(int SourceStartX,
     int SourceStartY, int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MASK_IMAGE * Source,
     unsigned int DestPageBase, int DestBitmapWidth);
void xcopyd2dmasked2(
     int SourceEndX, int SourceEndY,
     int DestStartX, int DestStartY, MASK_IMAGE *Source,
     unsigned int DestPageBase);
void xcopys2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, char* SourcePtr, unsigned int DestPageBase,
     int SourceBitmapWidth, int DestBitmapWidth);
void xcopyd2d(int SourceStartX, int SourceStartY,
     int SourceEndX, int SourceEndY, int DestStartX,
     int DestStartY, unsigned int SourcePageBase,
     unsigned int DestPageBase, int SourceBitmapWidth,
     int DestBitmapWidth);
unsigned int xcreatmaskimage(MASK_IMAGE * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask);
unsigned int xcreatmaskimage2(MASK_IMAGE * ImageToSet,
     unsigned int DispMemStart, char * Image, int ImageWidth,
     int ImageHeight, char * Mask);

void xddfast(int source_x,int source_y, int width, int height,
             int dest_x, int dest_y,
             unsigned int source_page,unsigned int dest_page);
xsetpal(unsigned char color, unsigned char R,unsigned char G,unsigned char B);
xgetpal(char far * pal, int num_colrs, int start_index);

//G_MAIN.C
void run_gotm(void);
void printt(int val);
void thor_dies(void);
void thor_spins(int flag);
void thor_spins(int flag);
void pause(int delay);
void rotate_pal(void);
int  rnd(int max);

//G_GRP.C

void xprint(int x,int y,char *string,unsigned int page,int color);
void xprintx(int x,int y,char *string,unsigned int page,int color);
void split_screen(void);
int  load_palette(void);
void xbox(int x1,int y1,int x2,int y2,unsigned page,int color);
void fade_in(void);
void fade_out(void);
void unsplit_screen(void);
void screen_dump(void);
void d_restore(void);

//G_INIT.C
int initialize(void);
void exit_code(int ex_flag);
void interrupt keyboard_int();              // interrupt prototype
void demo_key_set(void);
void wait_not_response(void);
int  wait_response(void);
int  get_response(void);
void wait_key(int index);
void wait_not_key(int index);
int  wait_ekey(int index);
int  wait_not_ekey(int index);
void joy_key(void);
void set_joy(void);
void merge_keys(void);
int  setup_boss(int num);
void story(void);

//G_FILE.C
long file_size(char *path);
unsigned int read_file(char *filename,char far *buff,
              long offset, unsigned int amount,int key);
int  load_bg_data(void);
int  load_sd_data(void);
int  load_objects(void);
int  load_actor(int file,int num);
int  load_picture(int index,char *buff);
void setup_filenames(int level);
int  load_speech(int index);
long file_size(char *path);
void far *get_file(char *filename,int key);
void save_game(void);
int  load_game(int flag);
void help(void);
long res_read(char *name,char far *buff);
int  load_music(int num);

//G_PANEL.C
void status_panel(void);
void display_health(void);
void display_magic(void);
void display_jewels(void);
void display_score(void);
void display_keys(void);
void display_item(void);
int  init_status_panel(void);
void add_jewels(int num);
void add_score(int num);
void add_magic(int num);
void add_health(int num);
void add_keys(int num);
void fill_health(void);
void fill_magic(void);
void fill_score(int num);
void score_for_inv(void);
void boss_status(int health);
int  select_option(char *option[],char *title,int ipos);
int  option_menu(void);
int  ask_exit(void);
int  select_sound(void);
int  select_music(void);
int  select_slow(void);
int  select_scroll(void);
void select_fastmode(void);
void select_skill(void);
void hammer_smack(int x,int y);
void show_scr(void);


//G_BACK.C
void build_screen(unsigned int pg);
void show_level(int new_level);
void scroll_level_left(void);
void scroll_level_up(void);
void scroll_level_right(void);
void scroll_level_down(void);
void phase_level(void);
void copy_bg_icon(int num,unsigned int src_page,unsigned int dst_page);
int  odin_speaks(int index,int item);
int  actor_speaks(ACTOR *actr,int index,int item);
int  display_speech(int item, char *pic,int tf);
void select_item(void);
void show_item(int item);
int  use_thunder(int flag);
int  use_hourglass(int flag);
int  use_boots(int flag);
void use_item(void);
int  switch_icons(void);
int  rotate_arrows(void);
void kill_enemies(int iy,int ix);
void remove_objects(int y,int x);
void place_tile(int x,int y,int tile);
int  bgtile(int x,int y);

//G_IMAGE.C
unsigned int make_mask(MASK_IMAGE * image,
     unsigned int page_start, char * Image, int image_width,
     int image_height);
int  load_standard_actors(void);
void setup_actor(ACTOR *actr,char num,char dir,int x, int y);
void show_enemies(void);
int  load_enemy(int type);
int  actor_visible(int invis_num);
void setup_magic_item(int item);
void load_new_thor(void);

//G_MOVE.C
void next_frame(ACTOR *actr);
int  point_within(int x,int y,int x1,int y1,int x2,int y2);
int  overlap(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
int  reverse_direction(ACTOR *actr);
void thor_shoots(void);
void actor_damaged(ACTOR *actr,int damage);
void thor_damaged(ACTOR *actr);
void actor_destroyed(ACTOR *actr);
int  actor_shoots(ACTOR *actr,int dir);
void actor_always_shoots(ACTOR *actr,int dir);
void move_actor(ACTOR *actr);

//G_MOVPAT.C
int  check_move0(int x,int y, ACTOR *actr);
int  check_move1(int x,int y, ACTOR *actr);
int  check_move2(int x,int y, ACTOR *actr);
int  check_move3(int x,int y, ACTOR *actr);
int  check_move4(int x,int y, ACTOR *actr);
int  check_thor_move(int x,int y, ACTOR *actr);
void set_thor_vars(void);

//G_OBJECT.C
void show_objects(int level,unsigned int pg);
void pick_up_object(int p);
int  drop_object(ACTOR *actr);
int  _drop_obj(ACTOR *actr,int o);
void delete_object(void);

//G_SPTILE.C
int special_tile_thor(int x,int y,int icon);
int special_tile(ACTOR *actr,int x,int y,int icon);

//G_SBFX.C
int  sbfx_init(void);
void sbfx_exit(void);

//G_SOUND.C
int  sound_init(void);
void sound_exit(void);
void play_sound(int index, int priority_override);
int  sound_playing(void);

//G_MUSIC.C
int  music_init(void);
void music_play(int num,int override);
void music_pause(void);
void music_resume(void);
int  music_is_on(void);

//G_SCRIPT.C
void execute_script(long index,char *pic);

//G_BOSS.C

int  boss_movement(ACTOR *actr);
void check_boss_hit(void);
void boss_level(void);
int  boss_die(void);
void closing_sequence(void);
void ending_screen(void);
int  endgame_movement(void);

//G_ASM.ASM
void xdisplay_actors(ACTOR *act,unsigned int page);
void xerase_actors(ACTOR *act,unsigned int page);
void pal_fade_in(char *buff);
void pal_fade_out(char *buff);
void read_joystick(void);
void UnLZSS(char far *src,char far *dest,int len);
#define REPEAT(a) for(rep=0;rep<a;rep++)
#define IN_RANGE(v,l,h) (v>=l && v<=h)
