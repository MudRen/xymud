#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 
      
void setname() 
{
	set_name("白眉",({"bai mei","bai",}));
	set("long",@LONG
这位满头白发的老人，一双银白的长眉低垂。
LONG);
	set("gender", "男性");
	set("age", 125);
	set("per", 40);
	set("int", 100);
	set("con", 100);
	create_family("蜀山派",1,"丝");
	set_skill("spells",400);
	set_skill("force", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("sword", 400);
	set_skill("zixia-shengong", 400);
	set_skill("sevensteps", 400);
	set_skill("hunyuan-zhang", 400);
	set_skill("literate", 400);
	set_skill("unarmed", 400);
	set_skill("mindsword", 400);
	set_skill("yujianshu", 400);
	set_skill("taoism",400);
	map_skill("spells", "taoism");
	map_skill("dodge", "sevensteps");
	map_skill("force", "zixia-shengong");
	map_skill("parry", "mindsword");
	map_skill("sword", "mindsword");
	map_skill("unarmed", "hunyuan-zhang");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",12800000);
	set("daoxing",12800000);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"sword",1)->wield();	
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d,k;
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
			message_vision(HIW"\n$N如痴如狂，口中喃喃自语：挫其锐，解其纷，和其光，同其尘。\n"NOR,this_object(),who);
			message_combatd(HIW"\n$N一张脸突然变得惨白，右掌直出，猛地对准$n的膻中大穴按了上去！\n"NOR,this_object(),who);
			if( random(3) )
			{
				message_combatd(HIR"\n$n脚下一个不稳，踉跄几步，呕出几口鲜血，面色苍白了许多！\n"NOR,this_object(),who);
				who->receive_wound("kee",350,this_object(),TYPE_PERFORM);
				who->receive_damage("kee", 500,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
				COMBAT_D->report_status(who);
			}
			else	message_combatd(CYN"可是$n"CYN"看破了$P的企图，闪在了一边。\n"NOR,this_object(),who);
		}
		else 
		{
			message_vision(HIB"\n$N仰天大喝了一声：助我克敌者赏神剑一柄！\n"NOR,this_object(),who);
			message_combatd(HIB"\n一刹那间千万剑光破空而来，劈面罩向$n！\n"NOR,this_object(),who);
			k = 4+random(6);
			for(d=0;d<k;d++)
			{
				if( random(3) )
				{
					message_combatd(HIY"\n$n一个不慎，中了一剑。\n"NOR,this_object(),who);
					who->receive_damage("kee",100+random(200),this_object(),TYPE_PERFORM);
					COMBAT_D->report_status(who);
				}
				else	message_combatd(HIY"\n$n左跳右闪，好不容易避开了一轮剑雨"NOR,this_object(),who);
			}
		}
	}
	else
		QUEST_D->randomPfm(this_object());
	
	call_out("tiaozhan_hit",2+random(3),who);
}