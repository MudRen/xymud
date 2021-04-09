inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "祭祀厅");
        set("long", @LONG
这是蜀山剑派祭祀的地方，正中间只有一个大炉(lu)，上面挂着多串佛珠。
炉前有祭祀桌，上面供放着许多祭祀的食物和香烛，供奉蜀山历届祖师。如果你
收服过妖怪，你可以上前祭拜(jibai)，以求祖先保佑你得道升仙。

LONG
        );
        set("item_desc", ([
                "lu": @TEXT
用来对付低等妖魔的炉，低等妖魔被困在里面，不出一个时辰，就会尽失道行！
你如果有擒拿住的妖魔，可以在这里化妖(hua)。
TEXT        ]));
        set("exits", ([
                "south" : __DIR__"houdian",
        ]));
        set("objects", ([
                __DIR__"npc/daozhen" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_jibai", "jibai");
        add_action("do_hua", "hua");
        if( !userp(this_player()) && this_player()->query("id")!="dao zhen" )  this_player()->command("go south");
}

int do_hua(string arg)
{
	object who,me = this_player();
	if( !arg || !userp(me) )
		return err_msg("你要化什么妖？\n");
	if( me->is_busy() )
		return err_msg("你现在正忙着呢。\n");	 	
	who = present(arg,me);
	if( !who || !who->is_character() )
		return err_msg("你身上没有"+arg+"，或者该对象不是活物。\n");
	if( userp(who) )
		return err_msg("你不可对付异人。\n");
	if( who->query("class")!="yaomo" )
		return err_msg("这可不是妖魔啊？！\n");
	if( who->query_level()-me->query_level()>15
	 || me->query_level()-who->query_level()>15 )
	 	return err_msg("它与你的等级差距太大，不能化妖。\n");
	message_vision("$N念动真言，将化妖炉打开！\n",me);
	me->start_busy(3);
	message_vision("但见霞光一闪，一道青气卷起$n，须臾间便缩回炉中。顿时青烟弥漫，隐约有血光夹带着嘶吼之声传出。\n\n",who);
	destruct(who);
	me->add_temp("shushan_huayao",1);
	return 1;
}

int do_jibai()
{
	int wx,pot,dx;
	object me = this_player();
	if( me->is_busy() )
		return err_msg("你现在正忙着呢。\n");
	if( me->query("family/family_name")!="蜀山派" )
	{
		message_vision("$N跪下来，诚心诚意向蜀山派历届祖师祭拜。\n",me);
		me->start_busy(2);
		return 1;
	}	
	message_vision("$N跪下来，向蜀山历届祖师祭拜。\n",me); 
	me->start_busy(1);
	if((int)me->query_temp("shushan_huayao") > 0)
	{ 
		wx = (int)me->query_temp("shushan_huayao")*1000;
		wx = wx/2+random(wx/2);
		dx = wx*2/3+1;
		pot = wx/10+1;
		me->add("combat_exp",wx);
		me->add("daoxing",dx);
		me->add("potential",pot);
		write("你的降妖除魔行为感动上苍，获得了"HIR+wx+NOR"点武学经验、"HIR+pot+NOR"点潜能以及"HIR+COMBAT_D->chinese_daoxing(dx)+NOR"道行。\n");
		me->delete_temp("shushan_huayao");
		me->save(1);		
	}
	else tell_object(me,"只要你降妖除魔之心永在，祖师爷一定会保佑你。\n"); 
	return 1;
}
