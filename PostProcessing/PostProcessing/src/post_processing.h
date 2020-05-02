#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

void post_processing_start();
void post_processing_update();
void post_processing_keyup(int scancode);
void post_processing_keydown(int scancode);
void post_processing_mousemotion(int new_x, int new_y, int x_rel, int y_rel);
void post_processing_mousebuttondown();
void post_processing_mousebuttonup();
void post_processing_end();

#endif // POST_PROCESSING_H