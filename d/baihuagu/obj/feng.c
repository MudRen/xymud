inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR"《寒玉灵风秘籍》"NOR, ({"lingfeng miji","feng","miji","book"}));
        set_weight(1000);
        set("num",3);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "册");
	set("long",
	"一本小册子，封面上《寒玉灵风》龙飞凤舞，气势不凡。\n");
        set("material", "paper");
        set("no_put",1);
        set("no_give",1);
	set("no_drop", 1);                
        set("no_get",1);
        set("value", 0);
        }
}

void init()
{
	add_action("do_read", "read");
	add_action("do_read", "study");
}

void finish(object me)
{
	remove_call_out("finish");
	if( !me || !living(me) || !present(this_object(),me) )
		return;
	me->delete_temp("reading");	
	if( random(me->query_kar())<15 || random(me->query_per())<15
	 || random(me->is_knowing("bhg_feng"))>3 )
	{
		write("你研读了半天寒玉灵风秘籍，只觉得头晕脑胀，什么也没领悟到。\n");
	}
	else
	{
		write("你读了半天，不禁豁然开朗，连声说道：好个造化！\n");
		me->set_knowing("bhg_feng",1);
		me->save();
		if( me->is_knowing("bhg_feng")==1 )
			write(HIG"你领悟了「寒玉灵风」的妙用！\n"NOR);
		write(HIY"你的「寒玉灵风」的基础伤害增加了，目前为"+me->is_knowing("bhg_feng")*50+"。\n"NOR);	
	}
	add("num",-1);
	if( query("num")<=0 )
	{
		write("\n一阵香风拂过，"+name()+"化作了朵朵花瓣，散落在夜风中。。。。\n\n");
		destruct(this_object());
	}
}			

int do_read(string arg)
{
	object me;
	int sen_cost, gain;
	if( !arg || !id(arg) )
		return 0;	
	me=this_player();
	if( !present(arg,me) )
		return 0;
	if(me->query("family/family_name")!= "百花谷")        
		return err_msg("上面的东西你似乎看不懂？");
    	if( me->is_busy() )
		return err_msg("你现在忙着呢，哪有可能静心研读...\n");
   	if( me->is_fighting() )
        	return err_msg("现在才想到精研纵横剑法，太晚了吧？\n");
	if( (int)me->query_skill("literate", 1) < 50 ) 
		return err_msg("你看了半天，里面不少字都是它认得你你不认得它。\n");
	if( (int)me->query_skill("brightjade-force",1)<200 )
		return err_msg("你在明玉神功方面造诣还不够精深，这本书不会让你长进多少。\n");
	if( me->query_temp("reading") )
		return err_msg("你正在读着呢。\n");
		
	sen_cost = 25 + random((30-(int)me->query("int")));
	if( sen_cost < 50 ) sen_cost = 50;
	if( (int)me->query("sen")<sen_cost )
		return err_msg("你现在头晕脑胀，该休息休息了。\n");	
	me->receive_damage("sen", sen_cost);
	gain = (int)me->query_skill("literate", 1)/60+(int)me->query_int()/30+1;
	if( gain>5 ) gain = 5;
	gain = 10-gain;
	message_vision("$N开始专心潜读寒玉灵风秘籍。\n", me);
	me->set_temp("reading",1);
	remove_call_out("finish");
	call_out("finish",gain,me);		
	return 1;
}
