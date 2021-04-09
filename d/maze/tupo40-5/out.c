#include <ansi.h>
inherit "/d/maze/tupo40-5/room.c";

string *gg = ({
	"yg-baihuagu","yg-dragon","yg-moon","yg-putuo",
	"yg-shushan","yg-wudidong","yg-xueshan",
});	

void create() 
{ 
        set("short","幽谷至极");
        set("long",YEL+@LONG
这里便是幽谷深处，来到这里仿若进入了一个苍黄的世界。此地植被全无，放眼望去，除了土还是土。
    空气中流连着肉眼可见的土色之气，你站立片刻，便染了一身的泥巴色，变成了土人。
    
LONG+NOR);
        set("virtual_room", 1); 
        set("exits", ([
                "south" :__DIR__"maze/exit",
        ])); 
        set("alternative_die",1);   
        setup();
} 

void create_guai(object who)
{
	object guai;
	remove_call_out("creat_guai");
	if( !who || !living(who) || !present(who,this_object()) )
		return;
	guai = new("/d/maze/tupo40-5/npc/"+ gg[random(sizeof(gg))] );
	guai->remove_all();
	guai->init_name( ({6,7,7,6})[random(4)] );
	guai->init_texing();
	if( guai->move(this_object()) )
	{
		message_vision(YEL"\n脚下泥土翻动，你正迟疑间，忽然从底下窜出一个奇形怪状的怪物！\n"NOR,this_player());
		set("create",1);
		guai->kill_ob(this_player());
		this_player()->fight_ob(guai);
	}
	else if( guai )
		destruct(guai);	
}

void init()
{
	add_action("do_cmds","",1);
        add_action("do_drop","drop");	
        
	if( userp(this_player()) 
	 && !query("create") )
	{
		remove_call_out("creat_guai");
		call_out("create_guai",3+random(4),this_player());
	}	 
}

int do_drop(string arg)
{
	return ("/d/city/droproom.c")->do_main(arg);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "recall","move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}

int valid_leave(object who,string dir)
{
	return ROOM->valid_leave(who,dir);
}