// jjf_b.c

#include <ansi.h>
inherit BULLETIN_BOARD;


void create()
{
        set_name(HIW"无量玉壁"NOR, ({ "sword board", "board" }) );
        set("location", "/d/emei/xianjing.c");
        set("board_id", "emei_b");
        setup();
        set("capacity", 100);
        replace_program(BULLETIN_BOARD);
}
