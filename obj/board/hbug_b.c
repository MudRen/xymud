#include "ansi.h"

inherit BULLETIN_BOARD;

void create()
{
        set_name("秘密"+HIR+"BUG"+NOR+"报告板", ({ "board" }) );
        set("location", "/d/wiz/baobao");
        set("board_id", "hbug_b");
        set("long", "这是一个用来报告秘密BUG的留言板，只有巫师能看到。\n" );
        setup();
        set("capacity", 200);
 	replace_program(BULLETIN_BOARD);
}
