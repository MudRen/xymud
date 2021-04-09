#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIR"死牢"NOR);
	set("long",HIW+@LONG

        面      壁      思      过
        
LONG
);
	set("valid_startroom",1);
	setup();
}

void init ()
{
	object me=this_player();
	if(!wizardp(me))
        {
        	add_action("block_cmd","",1);      
        	me->set("startroom","/d/wiz/jail.c");
        	me->save();
        }
}

int block_cmd()
{
	string verb = query_verb();
   	if (verb=="say") return 0; //allow say
	if (verb=="help") return 0;
	if (verb=="look") return 0;
	if (verb=="hp") return 0;
	if (verb=="chat") return 0;
	if (verb=="chat*") return 0;
	if (verb=="tell") return 0;
	write(HIR"面壁思过吧！你。。。。\n"NOR);
	return 1;
}

