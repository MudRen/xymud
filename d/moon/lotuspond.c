//Cracked by Roath
// Room: /moon/ontop.c
//cglaem...12/13/96.
inherit ROOM;
#include <ansi.h>

void create ()
{
	set ("short", "湖边");
  	set ("long", @LONG
湖面绿波上飘着一叶小舟，一个绿衫少女手执双桨，缓缓划水而来，
口中唱着小曲，听那曲子是：“采莲人语隔秋烟，波静如横练。入手风光
莫流转，共留连，画船一笑春风面。江山信美，终非吾土，问何日是归
年？”
    歌声娇柔无邪，却有一丝淡淡的的伤感。两滩上衰草残菱(lotus)更
助秋意。

LONG);

	set("item_desc", ([ 
  		"lotus" : "荷花已经谢了，莲梗上孤零零的吊着莲蓬。\n",
	]));
  	set("objects", ([ 
  		__DIR__"npc/chimeng" : 1,
	]));
  	set("exits", ([ 
  		"north" : __DIR__"rain",
	]));

  	setup();
}

void init()
{
  	add_action("do_cai", "cai");
}

int query_Pot(object who)
{
	if( !who || who->query("potential")<=0 )
		return 0;
	return (int)who->query("potential")-(int)who->query("learned_points");		
}	

int do_cai(string arg)
{
	int need_p,lvl,pp;
	mapping skills;
	object m, me=this_player();

	if( (!arg) || !((arg == "lotus") || (arg == "lian")))
    	return notify_fail("采什么？\n");
    if( me->is_busy() )
    	return notify_fail("你正忙着呢。\n");	
 	if( me->query("kee") < (int)(me->query("max_kee")/3) )
		return notify_fail("您先歇歇吧，别那么馋:)\n");
  	
  	message_vision("$N见那莲蓬诱人，便伸手去摘．\n", me);
 	me->receive_damage("kee", 20);

	if( random(6) < 1 && !wizardp(me) )
	{
		message_vision("$N脚下一滑，扑通一声掉进了莲花池．\n",me);
		me->move(__DIR__"hudi");
		me->start_busy(2);
		return 1;
	}
	if( me->query("gender") == "男性")
		return notify_fail("你突然意识到采莲不免有失英雄本色，不禁又把手缩了回来\n");	
	skills = me->query_skills();
	if( !skills || !mapp(skills) || undefinedp(skills["moondance"]) )
		 me->improve_skill("moondance", 40-me->query("str"));
	else
	{
		lvl = skills["moondance"];
		if( lvl>100 )
		{
			m = new(__DIR__"obj/lianzi.c");
	    	if( m->move(this_player()) )
	    		message_vision("$N双脚在莲叶上一点，身子轻轻在水上掠过，回来时手中已多了一只莲蓬。\n", me);
	    	else 
	    		destruct(m);		
	    	me->start_busy(1);
	    	return 1;
		}
		
		if( me->query("combat_exp")<(lvl+1)*(lvl+1)*(lvl+1)/10 )
			return notify_fail("也许实战经验不够，你采了半天，一无所获。\n");
		need_p = (lvl+1)*(lvl+1);
		pp = me->query("int")/5+me->query_int()/10+random(me->query_skill("literate",1))/100;
		pp-= random(me->query("str"))/5;
                if( pp<1 ) pp = 1;
		need_p = need_p/pp;
		if( need_p<100 ) need_p = 100;
		if( query_Pot(me)<need_p )
			return notify_fail("也许因为潜能不够，你采了半天，一无所获。\n");
		if( me->query("learned_points")>0 )
			me->add("learned_points",need_p);
		else
			me->add("potential",-need_p);
		skills["moondance"] = lvl+1;
		write("
你试着运用所学的轻功纵身跳上荷叶，发现不妙又赶紧跳了回来．
你领悟出一些冷月凝香舞的技巧。\n");
		tell_object(me,HIC"你的「冷月凝香舞」进步了！\n"NOR);
		if( wizardp(me) )
			tell_object(me,HIR"消耗"+need_p+"潜能\n"NOR);
		me->save();
		me->start_busy(1);
		return 1;			
	}
	return 1;
}
