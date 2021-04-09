#include <ansi.h>
inherit "/d/maze/dayan-ta/room.c";

void create_dong()
{
	if( query("create") )
		return;
        set("short", "秘洞"); 
        set("long", @LONG 
这里是大雁塔地宫的一个秘密洞穴，四周洞壁上摆满了祝融雕像。
    地上摆着一个大火盆，四周涂着杂七杂八的符号，迎面则摆放着一个
巨大的火神雕像，狰狞的目光紧紧注视着你。
    
LONG
);
	set("create",1);
	set("item_desc",0);
}

void create() 
{ 
        set("short", "洞口"); 
        set("long", @LONG 
洞内四面纵横十余丈，其中错牙交错的甬道连接四方，两名的
石壁上画满佛符，闪烁着微弱的金光。        
    前方是个深深的洞穴，看情形好似最近才刚刚开凿而成。
洞口用一个铁栅栏挡住，铁链缠绕，用一个青铜锁(suo)锁着。
    
LONG
);
	set("alternative_die",1);
	set("virtual_room",1);	
	set("item_desc",([
		"suo" : "一把青铜做成的大锁，上面有个机关盘，上面布满天干地支方块：
 甲、乙、丙、丁、戊、己、庚、辛、壬、癸、子、丑、寅、卯、辰、巳、午、未、申、酉、戌、亥
    每个方块好似都可以按(push)下去。\n",
    	])); 
        setup();
}

void init()
{
	add_action("do_push","push");
}

void create_guai(object who)
{
	object npc;
	remove_call_out("create_guai");
	if( !who || !living(who) || !present(who,this_object()) )
		return;
	npc = new("/d/maze/dayan-ta/npc/blade");
	npc->move(this_object());
	message_vision(HIR"\n$N"HIR"从洞内窜了出来！\n"NOR,npc);
	message_vision(HIW"$N"HIW"大叫一声：兀那小贼，敢窥视本教密地，纳命来！\n"NOR,npc);
	npc->kill_ob(who);
}

void jiguan_fail(object who)
{
	object npc;
	remove_call_out("create_guai");
	if( !who || !living(who) || !present(who,this_object()) )
		return;
	set("create",1);
	set("item_desc",([
		"suo" : "一把青铜做成的大锁。\n",
    	])); 		
	npc = new("/d/maze/dayan-ta/npc/guai");
	npc->set("no_obj",1);
	npc->move(this_object());
	message_vision(HIR"\n$N"HIR"从洞内窜了出来！\n"NOR,npc);
	message_vision(HIW"$N"HIW"大叫一声：兀那小贼，敢窥视本教密地，纳命来！\n"NOR,npc);
	npc->kill_ob(who);
}

int do_push(string arg)
{
	string *msg;
	object me = this_player();
	if( query("create") )
		return 0;
	if( me->query_temp("pending/qt_key")>=4 )
		return 0;
	if( me->is_busy() || me->is_fighting() )
		return err_msg("你现在正忙着呢。\n");
	msg = ({"甲","乙","丙","丁","戊","己","庚","辛","壬","癸","子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥",});
	if( !arg )
		return err_msg("你要按什么？\n");
	if( member_array(arg,msg)==-1 )
		return err_msg("你象中了邪一般，摆弄着青铜锁。\n");
	me->start_busy(1);		
	if( !me->query_temp("pending/qt_key") )
	{
		if( arg!=me->query_temp("maze/qt_key1") )
		{
			jiguan_fail(me);
			return err_msg("你按了一下"+arg+"，结果什么反应也没有。\n"HIR"坏了，你惊动了贼人！\n"NOR);
		}
		write(HIY"你按下了"+arg+"，青铜锁内传来一阵机括之声。\n"NOR);
		me->set_temp("pending/qt_key",1);
	}
	else if( me->query_temp("pending/qt_key")==1 )
	{
		if( arg!=me->query_temp("maze/qt_key2") )
		{
			jiguan_fail(me);
			return err_msg("你按了一下"+arg+"，结果什么反应也没有。\n"HIR"坏了，你惊动了贼人！\n"NOR);
		}
		write(HIY"你按下了"+arg+"，青铜锁内传来一阵机括之声。\n"NOR);
		me->set_temp("pending/qt_key",2);
	}
	else if( me->query_temp("pending/qt_key")==2 )
	{
		if( arg!=me->query_temp("maze/qt_key3") )
		{
			jiguan_fail(me);
			return err_msg("你按了一下"+arg+"，结果什么反应也没有。\n"HIR"坏了，你惊动了贼人！\n"NOR);
		}
		write(HIY"你按下了"+arg+"，青铜锁内传来一阵机括之声。\n"NOR);
		me->set_temp("pending/qt_key",3);
	}
	else
	{
		if( arg!=me->query_temp("maze/qt_key4") )
		{
			jiguan_fail(me);
			return err_msg("你按了一下"+arg+"，结果什么反应也没有。\n"HIR"坏了，你惊动了贼人！\n"NOR);
		}
		write(HIY"你按下了"+arg+"，青铜锁内传来一阵机括之声。\n"NOR);
		me->set_temp("pending/qt_key",4);
		write(HIC"但听一声“吧嗒”声，青铜锁应声而开！\n"NOR);
		write(HIR"你赶紧信步冲进洞内。\n"NOR);
		create_dong();
		remove_call_out("create_guai");
		call_out("create_guai",1+random(3),me);
	}
	return 1;
}	