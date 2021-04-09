//bagua.c
#include <ansi.h>
inherit SSERVER;
inherit F_CLEAN_UP;

string name(){return "「八卦护体」";}

string *bagua = ({
        "乾","坤","震","巽","坎","离","艮","兑",
});

void bagua(object,int);
void freeze_ob(object);

int cast(object me, object target)
{
	string msg;
	int time;

	if( me->query_level()<15 )
		return notify_fail("你的人物等级不够。\n");
	if( me->query("family/family_name") != "五庄观" )
		return notify_fail(name()+"乃五庄观密修之法。\n");
	if( me->query_skill("taiyi", 1)<150)
        	return notify_fail("你的太乙仙法修为不深，使不了"+name()+"。\n");
	if( me->query("mana")<500 )
        	return notify_fail("你的法力不够，使不了"+name()+"。\n");
	if( me->is_fighting())
        	return notify_fail("战斗中施展"+name()+"恐怕有些危险。\n");
	if( me->query("sen")<200 )
        	return notify_fail("你现在神智不清，难以施展"+name()+"。\n");
	if( time()<me->query_temp("wzg_bagua")+8 )
        	return notify_fail("你刚刚用过"+name()+"，还是歇歇再试吧。\n");
        if( me->query_temp("bagua") )
        	return notify_fail("你已经在运功中了。\n");	

	me->add("mana",-200);
	me->receive_damage("sen",100);
	if( random(me->query("max_mana")) < 50 ) 
        {
        	write("咦？这一次好像不灵。\n");
        	return 1;
        }
	time = me->query_skill("taiyi",1);
	time/= 50;
	time+= me->query("mana")/60;
	if( time>120 )
        	time = 120;
	if( time<10 )
        	time = 10;      
	message_vision(HIC"$N"HIC"左手捏咒，口中喃喃念叨了几句真言，右手掐指往背后一指，大喝一声“立”！只见$P身后渐渐现出一幅巨大的八卦图！\n"NOR,me);
	me->set_temp("bagua",1);
	call_out("bagua",0,me,time);
	return 1;
}

void bagua(object me,int time)
{
	int flag=0;      
	if( !me || !me->query_temp("bagua") )
        	return;
	time--;
	if( time<=0 || me->query("mana")<80 )
        {
        	freeze_ob(me);
        	return;
        }
	while( me->query("max_kee")>me->query("eff_kee") )
        {
        	if( me->query("mana")<50 )
                	break;          
        	flag++; 
        	me->receive_curing("kee",(50+me->query_skill("taiyi",1)/10));
        	me->add("mana",-30);
        }
	if( flag )
	        message_combatd(HIC"$N"HIC"背后八卦图一闪，"+bagua[random(sizeof(bagua))]+"方生门中一道金光射入$N"HIC"体内。$N"HIC"身上的伤势似乎得到了治疗。\n"NOR,me);           
	call_out("bagua",0,me,time);
}

void freeze_ob(object me)
{
	if( me )
	{
		message_vision(CYN"\n$N"CYN"左手捏咒，口中喃喃念叨了几句真言，右手掐指往背后一指，大喝一声“解”。只见隐约间一幅巨大的八卦图在$P身后一闪而没！\n"NOR,me);
		me->delete_temp("bagua");
		me->set_temp("wzg_bagua",time());
	}	
}

int help(object me)
{
        string str;
        if( !me )  return 0;
        str = @STR

        法术名称：八卦护体
        法术所属：太乙仙法
        法术效果：以护体八卦在一定时间内自动治疗气血
        	  每治疗一次，消耗50法力
                  护体状态结束后冷却8秒
        法术条件：
        	  五庄观弟子
        	  人物等级15级	
                  法力500点，消耗200点
                  精神200点，消耗100点
                  太乙仙法 150 级
STR;
        me->start_more(str);
        return 1;
}