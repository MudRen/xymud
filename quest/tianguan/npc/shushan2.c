#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 
      
void setname() 
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("male");
	if( !names )
		set_name("丹辰子",({"danchen zi","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({id+" zi",id,"di zi"});
		else
			ids = ({"di zi",});	
		i = strlen(name);
		if( i<=2)
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = name+"子";			
		set_name(name,ids);
	}	
	set("my_master","bai mei");
	set("gender", "男性");
	set("age", 35);
	set("per", 20+random(20));
	set("int", 100);
	set("con", 100);
	create_family("蜀山派",3,"弟子");	
	set_skill("spells",350+random(50));
	set_skill("force", 350+random(50));
	set_skill("dodge", 350+random(50));
	set_skill("parry", 350+random(50));
	set_skill("sword", 350+random(50));
	set_skill("zixia-shengong", 350+random(50));
	set_skill("sevensteps", 350+random(50));
	set_skill("hunyuan-zhang", 350+random(50));
	set_skill("literate", 350+random(50));
	set_skill("unarmed", 350+random(50));
	set_skill("mindsword", 350+random(50));
	set_skill("yujianshu", 350+random(50));
	set_skill("taoism",350+random(50));
	map_skill("spells", "taoism");
	map_skill("dodge", "sevensteps");
	map_skill("force", "zixia-shengong");
	map_skill("parry", "mindsword");
	map_skill("sword", "mindsword");
	map_skill("unarmed", "hunyuan-zhang");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",10000000);
	set("daoxing",10000000);
	i = 3000+random(2000);
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
	if( random(10)==0 )
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
	
	call_out("tiaozhan_hit",4,who);
}