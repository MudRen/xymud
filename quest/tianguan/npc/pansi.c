#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 
      
void setname() 
{
	set_name("紫霞仙子", ({"zixia xianzi","zixia","xianzi","girl",}));
	set("long",@LONG
她就是盘丝洞的开山祖师,传说她是佛祖的一棵灯芯。随佛祖修道悟
真,后来思凡下界占了花果山一处洞府,开山立派,传授门徒。
她看起来约二十多岁。

LONG);
	set("gender", "女性");
	set("age", 25);
	set("per", 40);
	set("int", 100);
	set("con", 100);
	create_family("盘丝洞",1,"丝");
	set_skill("literate",380);
	set_skill("unarmed", 380);
	set_skill("dodge", 380);
	set_skill("zhuyan", 380);
	set_skill("force",380);
	set_skill("parry",380);
	set_skill("sword", 380);
	set_skill("spells", 380);
	set_skill("whip", 380);
	set_skill("pansi-dafa", 380);
	set_skill("lanhua-shou",380);
	set_skill("jiuyin-xinjing",380);
	set_skill("chixin-jian",380);
	set_skill("qin",380);
	set_skill("yueying-wubu",380);
	set_skill("yinsuo-jinling", 380);
	map_skill("spells", "pansi-dafa");
	map_skill("unarmed", "lanhua-shou");
	map_skill("force", "jiuyin-xinjing");
	map_skill("sword", "chixin-jian");
	map_skill("parry", "yinsuo-jinling");
	map_skill("dodge", "yueying-wubu");
	map_skill("whip", "yinsuo-jinling");
	set("pansi/zhenfa",1);
	carry_object("/d/pansi/obj/qin");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",10974400);
	set("daoxing",10974400);
	i = 2000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"whip",1)->wield();	
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d;
	remove_call_out("tiaozhan_hit");	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( random(5)==0 )
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			msg = HIB "$N"HIB"默运神功，脸色白得吓人，突然使出兰花手的一记阴招「九阴绝户手」，企图当场把$n"HIB"废于掌下。\n\n"NOR;
			message_vision(msg,this_object(),who);
			if( random(3) )
			{
				message_combatd(RED"结果$N"RED"一击命中，$n"RED"只感到下体一阵刺痛，体内精元不断外泄，顿时觉的四肢无力，两腿不停颤抖。\n"NOR,this_object(),who);
				who->receive_wound("kee",300,this_object(),TYPE_PERFORM);
				who->receive_damage("kee", 450,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
				COMBAT_D->report_status(who);
			}
			else	message_combatd(CYN"可是$n"CYN"看破了$P的企图，闪在了一边。\n"NOR,this_object(),who);
		}
		else 
		{
			msg = HIM  "$N"HIM"脚踏［月影舞步］，曼歌轻舞，使出［痴心情长剑法］的精髓－－
\n"HIR"             『红颜"HIW"白发』\n"NOR;
			message_vision(msg, this_object(),who);
			msg = NOR"\n"MAG"－－只见$N"MAG"长发飘飘，裙裾袂袂，清丽哀怨不可方物！\n\n使到动情尽意处，索性抛了手中的"+ weapon->name() +MAG"，双指轮弹，无边气韵氤氲般卷向$n！\n\n" NOR;
			message_combatd(msg, this_object(),who);
			msg =  HIW ""+ weapon->name() +HIW"犹如长虹浸空，仿佛消失．．．．\n\n" NOR;
			message_combatd(msg, this_object(),who);
			set_temp("pfm_msg",1);
			msg = HIY "\n$N"HIY"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
			if( COMBAT_D->do_attack(this_object(), who, query_temp("weapon"),TYPE_PERFORM,msg)>0 )
				COMBAT_D->report_status(who);
			msg = HIY "\n$N"HIY"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
			if( COMBAT_D->do_attack(this_object(), who, query_temp("weapon"),TYPE_PERFORM,msg)>0 )
				COMBAT_D->report_status(who);
			msg = HIY "\n$N"HIY"吟哦长啸“问世间－－－－情为何物？”，频思遗恨喷薄而发！\n" NOR;
			if( COMBAT_D->do_attack(this_object(), who, query_temp("weapon"),TYPE_PERFORM,msg)>0 )
				COMBAT_D->report_status(who);
				
			set_temp("pfm_msg",0);
		}
	}
	else
		QUEST_D->randomPfm(this_object());
	
	call_out("tiaozhan_hit",3+random(3),who);
}