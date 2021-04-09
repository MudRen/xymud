#include <ansi.h>
inherit "/d/maze/tupo40-1/room.c";

string *gg = ({
	"yg-baihuagu","yg-dragon","yg-moon","yg-putuo",
	"yg-shushan","yg-wudidong","yg-xueshan",
});	

void create() 
{ 
        set("short","万金之地");
        set("long",@LONG
一片毫无生气地广漠空地，越向深处走，巨石和树木颜色也就越像金属。形状也越来越犀利。
渐渐地在石头上都出现了劲锐地锋刃。树木也是上窄下粗。好像一根根指天地长梭。
    这些土石和植物上千年被销金窝中地气势侵袭。都被磨砺出了锋锐。小一些地石块干脆都被
磨砺成一把把插在地面上地尖刀。偶尔发出一声清脆地震鸣。听在耳朵里让人不寒而栗。
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
	guai = new("/d/maze/tupo40-1/npc/"+ gg[random(sizeof(gg))] );
	guai->remove_all();
	guai->init_name( ({6,7,7,6})[random(4)] );
	guai->init_texing();
	if( guai->move(this_object()) )
	{
		message_vision(HIY"\n一旁的金石裂开，从里面走出一个奇形怪状的怪物！\n"NOR,this_player());
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