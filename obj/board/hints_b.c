#include "ansi.h"

inherit BULLETIN_BOARD;

void create()
{
        set_name("小雨西游"+HIG+"游戏经验"+NOR+"板", ({ "board" }) );
        set("location", "/d/wiz/lunar");
        set("board_id", "hints_b");
        set("long", "这是一个用来给玩家留下自己游戏经验的留言板。\n" );
        setup();
        set("capacity", 200);
 	replace_program(BULLETIN_BOARD);
}
