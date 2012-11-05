// delete : x
// undo : u, redo: ctrl+r
// append : a
// append end of line : A 
// append start of line : I
// insert below line : o
// insert upward line : O
// cut line : dd
// paste below line : p
// paste upward line : P
// yak  copy : y 
// copy line : yy 
// gogo thing  go top line : gg
// go end lines :G 
// block : v 
// line block : V 
// auto indentation upward : =gg
// auto indentation downward : =G
// split : :sp 
// switch window : ctrl+ww
// split vertical :  :vs
// find syntax : 3 K
// open header file : ctrl-wf
// replace :  :%s/hello/world/g
// ctags : ctags -R *
// find reference : g]
// return form reference : ctrl-t


#include <stdio.h>

#define TEXT "hello,world\n"
int main()
{
    printf(TEXT);
    return 0;
}

