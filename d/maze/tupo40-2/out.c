#include <ansi.h>
inherit "/d/maze/tupo40-2/room.c";

string *gg = ({
	"yg-baihuagu","yg-dragon","yg-moon","yg-putuo",
	"yg-shushan","yg-wudidong","yg-xueshan",
});	

void create() 
{ 
        set("short","万木之地");
        set("long",HIG+@LONG
到处郁郁葱葱，千万片绿叶从枝头婉转曼妙的飘落而下，原本别具风情的森林，在转眼间变得凄迷如梦，千万片绿叶交织落索，一场绿雨在林中渐渐弥漫，直到遮掩住空气，遮掩住视线，遮掩住呼吸。
    无数长藤与并不算粗大的树木纠缠成浓浓的一团。就那么乱七八糟的生长着。
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
	guai = new("/d/maze/tupo40-2/npc/"+ gg[random(sizeof(gg))] );
	guai->remove_all();
	guai->init_name( ({6,7,7,6})[random(4)] );
	guai->init_texing();
	if( guai->move(this_object()) )
	{
		message_vision(HIG"\n树木一阵晃动，从里面走出一个奇形怪状的怪物！\n"NOR,this_player());
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