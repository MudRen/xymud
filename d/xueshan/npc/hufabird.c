#include <ansi.h>
#include <combat.h>
inherit HUFA;

int types;
string *names = ({ "乌鸦", "老鹰", "孔雀","大鹏鸟","凤凰","不死鸟"});
string *ids = ({ "wu ya","lao ying","kong que","dapeng niao","feng huang","busi niao"});
string *msg_in=({HIB"半空中传来一阵嘈杂的声音，一只乌鸦飞了过来。",
		HIC"只见天空中划出一道黑色闪电，一只兀鹰飞扑而来。",
                HIM"你只觉得眼前一阵五彩缤纷，一只美丽的孔雀出现在你的面前。",
                HIY"顷刻间一阵飞沙走石，日月无光，一只翼长足有十丈的大鹏鸟从天而降。",
                HIG"突然间四周百鸟齐鸣，一只凤凰傲然站立在你的面前。",
                HIR"充满热情的火焰燃烧起来，不死鸟从火焰中飞了出来......"
});

string *msg_out=({HIB"乌鸦闭紧嘴巴，一声不响的溜了。",
		HIC"老鹰看见远处有只兔子，双翅一振，直向兔子扑去。",
                HIM"孔雀懒洋洋地甩了甩尾巴，一步三摇地踱走了。",
                HIY"大鹏鸟扑腾了几下翅膀，高叫一声“我去也”，就踪迹不见了。",
                HIG"凤凰无聊地打了个哈欠，无聊地朝四周看了看，无聊地飞走了。",
                HIR"充满伤感的火焰燃烧起来，不死鸟冲进火焰中飞走了......"
});

string *combat_msg=({"乌鸦呱呱地叫了几声，吵的$n心烦气燥。",
		"老鹰飞到半空，嗖的一声投出一颗鸟粪炸弹，正砸在$n的头上。",
                "孔雀把尾巴在$n面前晃来晃去，搅的$p眼花缭乱。",
                "大鹏鸟鼓起双翅，朝着$n奋力扇风，吹得$p连眼睛都睁不开。",
                "凤凰冲到$n的面前，骄傲地看着$p,$n自惭形秽，不由一阵气馁。",
                "不死鸟喷出一阵火焰，差点把$n烧成烤面包。"
});

varargs void setskills(int i)
{
	int lvl = this_object()->query_level();
	lvl/=30;
	if( lvl>5 )
		lvl = 5;
	set_name(names[lvl],({ids[lvl],"hu fa","hufa"}));
	set("env",([
		"msg_min" : msg_in[lvl]+"\n"NOR,
		"msg_mout": msg_out[lvl]+"\n"NOR,
		"msg_attack" : combat_msg[lvl]+"\n"NOR,
	]));
	create_family("大雪山", 3, "护法");
        set("title", "雪山护法");
        set("gender", "男性" );
        set("class", "yaomo");
	set("look_msg", "一只得道多年的"+names[lvl]+"，传说是大鹏明王手下的得力干将。\n");
	set_skill("unarmed", i);
	set_skill("cuixin-zhang", i);
	set_skill("dodge", i);
	set_skill("xiaoyaoyou", i);
	set_skill("parry", i);
	set_skill("force", i);   
	set_skill("ningxie-force", i);
	set_skill("spells", i);
	set_skill("dengxian-dafa", i);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("parry", "cuixin-zhang");
	map_skill("dodge", "xiaoyaoyou");
	set("max_force",query_skill("force")*10);
	set("max_mana",query_skill("spells")*10);
	add_temp("apply/combat_damage",10);
	add_temp("apply/spells_damage",10);
	if( this_object()->query_level()<70 )
	{
		add_temp("apply/combat_damage",30);
		add_temp("apply/spells_damage",30);
	}
	else if( this_object()->query_level()<90 )
	{
		add_temp("apply/combat_damage",50);
		add_temp("apply/spells_damage",50);
	}
	else
	{
		add_temp("apply/combat_damage",80);
		add_temp("apply/spells_damage",80);
	}	
	
}

//恢复
void die() 
{
	if( this_object()->name()=="不死鸟" )
	{
		message_vision(HIG"$N长鸣几声，立刻神采奕弈，振作起来。\n"NOR,this_object());
            	set("kee",2000);
            	set("sen",2000);
            	set("eff_kee",2000);
            	set("eff_sen",2000);
              	return;
        } 
        else	return ::die();
}
   
void unconcious() 
{
	die();
}

mixed hit_ob(object me, object target, int damage)
{
	string str;
	object who;
	if( !me || !living(me) )
		return 0;
	if( !target || !me->is_fighting(target) )
		return 0;
	who = me->query_owner();
	if( !who || !living(who) || !present(who,environment(me)) )
		return 0;
	if( who->query("mana")<10 )
		return 0;
	str = me->query("env/msg_attack");
	if( !str || !stringp(str) )
		return 0;
	if( random(damage)<5 )
		return 0;
	damage = damage/5;
	damage = damage/2+random(damage/2);
	if( damage<1 )
		return 0;
	who->add("mana",-2-random(3));	
	target->receive_damage("kee",damage,who,TYPE_CAST);
	return str;
}