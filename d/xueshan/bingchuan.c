#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "冰川");
	set ("long", @LONG

等上了冰川，你才觉得世界在你脚下又拔高了一层。放眼望去，
一面是延绵不尽的雪峰，但此时都好像到了你的脚下。一面是浩
翰无垠的冰原，如大海中的波涛一样起伏在你的面前。而几条巨
大的冰缝也在冰原中穿行，深不可测地等待着失足的旅人。
LONG);
	set("long2",HIY"    这里地平原川，倒也是个舞刀(wudao)的好地方。\n"NOR);
	set("exits", ([
		"south" : __DIR__"xueshan6",
		"north" : __DIR__"binggukou",
		"west" : __DIR__"bingchuan",
		"east" : __DIR__"bingchuan",
	]));
	set("outdoors", "xueshan");
	setup();
}

void init()
{
	add_action("do_wudao","wudao");
}

void finish_dao(object who)
{
	int damage,succ;
	if( !who || !present(who,this_object())
	 || !who->query_temp("pending/wudaoing") )
		return;
	who->delete_temp("pending/wudaoing");	
	if( random(10)<5 )
	{
		tell_object(who,HIY"\n忽然脚下传来一阵”嘎嘣“的声音，你低头一看，不好！却原来是脚下的冰川碎了个大窟窿！\n"NOR);
		who->move(__DIR__"binggu");
		message_vision("\n\n随着一阵阵响声和碎冰块，$N从上方冰川掉了下来！\n",who);
		damage = who->query("kee")/10;
		if( damage<50 )
			damage = 50;
		who->receive_damage("kee",damage,who);	
		COMBAT_D->report_status(who);
		return;
	}	
	succ = 50-who->query("family/xueshan_daobo");
	if( succ<=0 )
	{
		tell_object(who,HIC"\n你舞了半天的刀，结果毫无心得，不由得兴致索然。\n"NOR);
		return;
	}
        succ = random(who->query_kar()/3);
	if( succ<=2 )
	{
		tell_object(who,YEL"\n你舞了半天的刀，结果毫无心得，不由得兴致索然。\n"NOR);
		return;
	}
	succ = 200-who->query_skill("bingpo-blade",1)/10;
	if( succ<=0 )
	{
		tell_object(who,HIW"\n你舞了半天的刀，结果毫无心得，不由得兴致索然。\n"NOR);
		return;
	}
	succ = random(who->query_skill("blade")/10);
	if( succ<=1 )
	{
		tell_object(who,WHT"\n你舞了半天的刀，结果毫无心得，不由得兴致索然。\n"NOR);
		return;
	}
	who->improve_skill("bingpo-blade",1000,1);
	tell_object(who, "\n"HIY"【系统】你的冰魄寒刀熟练度增加了！\n" NOR);
        if( who->query("family/xueshan_daobo")>=50 ) who->set("family/xueshan_daobo",50);
        else        who->add("family/xueshan_daobo",1);
	tell_object(who, HIY"【系统】你的"HIC"「雪风刀波」"HIY"的攻击威力增加了！"NOR"\n");
}

int do_wudao()
{
	mapping act;
	string str;
	object weapon,me = this_player();
	if( !objectp(weapon=me->query_temp("weapon"))
	 || (weapon->query("skill_type")!="blade"
	  && weapon->query("use_apply_skill")!="blade") )
	  	return err_msg("你手里没刀，舞个神马？！\n");
	if( me->query("kee")<100 )
		return err_msg("你现在体力不支。\n");	  	
        if( me->query("family/xueshan_daobo")>50 )
        {
                me->set("family/xueshan_daobo",50);
                return err_msg("你领悟得够多的了，再舞也没啥用了。\n");
        }
	if( me->is_busy() || me->query_temp("pending/wudaoing") )
		return err_msg("你现在正忙着呢。\n");
	if( me->query_skill_mapped("blade")!="bingpo-blade" )
	{
		me->receive_damage("kee",100,me);
		return err_msg(HIY"你拿起"+weapon->name()+HIY"舞得不亦乐乎。\n"NOR);
	}
	act = me->query("actions");
	str = HIY"$N"HIY"兴致盎然的提起$w"HIY"，耍了个刀花，兴致勃勃的舞起刀来。\n"NOR;
	str+= act["action"];
	str = replace_string(str,"$w",weapon->name());
	str = replace_string(str,"$n","假想敌");
	str = replace_string(str,"$l","要害");
	str = replace_string(str,"$p","它");
	message_vision(str,me);
	me->receive_damage("kee",50,me);
	me->start_busy(1);
	me->set_temp("pending/wudaoing",1);
	me->start_call_out( (: call_other, __FILE__, "finish_dao", me :), 2+random(3));
	return 1;
}
