#ifndef _video_handler_
#define _video_handler_




void video_init();
void video_string(char * string);
void video_enter();
void video_backspace();
void video_input(char input);
void video_clear();
void video_update_cursor(int cursor_pos);
void video_screen_up();
void display_more();
void update_mouse(int x, int y, int color);
void k_clear_screen();
#endif
