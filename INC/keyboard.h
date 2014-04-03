#ifndef DEF_KEYBOARD
#define DEF_KEYBOARD

void kbUp(unsigned char key, int x, int y);
void kbDown(unsigned char key, int x, int y);
void kbManage();
void mouseMoveManager(int x, int y);
void clickManager(int key, int state, int x, int y);

#endif
