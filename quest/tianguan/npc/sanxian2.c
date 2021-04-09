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
		set_name("李小遥",({"li xiaoyao","li","xiaoyao","di zi"}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
                        ids = ({"yu "+id,id,"yu","di zi"});
		else
                        ids = ({"yu","di zi",});        
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
                name = "御"+name;                       
		set_name(name,ids);
	}	
	set("my_master","li bai");
	set("gender", "男性");
	set("age", 20+random(10));
	set("per", 35);
	set("int", 100);
	set("con", 100);
	create_family("散仙派",4,"弟子");

	set_skill("unarmed", 300+random(50));
	set_skill("dodge", 300+random(50));
	set_skill("parry", 300+random(50));
	set_skill("force", 300+random(50));
	set_skill("spells", 300+random(50));
	set_skill("sword",300+random(50));	
	set_skill("blade",300+random(50));
	set_skill("literate",300+random(50));
	set_skill("yinyang-zhang",300+random(50));
	map_skill("unarmed","yinyang-zhang");
	set_skill("bolomiduo",300+random(50));
	set_skill("five-avoid",300+random(50));
	set_skill("wuzheng-force",300+random(50));
	map_skill("force","bolomiduo");
	map_skill("dodge","five-avoid");
	set_skill("pomo-blade",300+random(50));
	map_skill("blade","pomo-blade");
	set_skill("qinglian-jian",300+random(50));
	map_skill("sword","qinglian-jian");
	set_skill("scratmancy",300+random(50));
	map_skill("spells","scratmancy");	
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",5400000);
	set("daoxing",5400000);
	i = 1000+random(1000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","qinglian-jian");
	}
	else
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","pomo-blade");
	}
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	remove_call_out("tiaozhan_hit");	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("powerup") )
		command("exert lian");
	if( random(8)==0 )
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			msg = HIM "$N"HIM"将全身每个气海光球各涌出三分之一，分为两道纳入两条手臂中，眼看劲力逐渐凝聚，身旁的气劲却越旋越快，回旋的劲力与其护身的气劲碰触到，直是嘎然作响，忽然同时轰然的爆裂开来，两道粗大凝结如实物一般的光束，撕裂空间般的往$n"HIM"狂奔而去。。\n"NOR; 
			message_combatd(msg,this_object(),who);
			if( random(3) )
			{
				message_combatd(HIR"两种能量相击之下，$n"HIR"马上被$N"HIR"狂龙一般的内劲瞬间吞噬，阴阳两股光柱轰然的击到了$p的身上。\n"NOR,this_object(),who);
				who->receive_wound("kee",250,this_object(),TYPE_PERFORM);
				who->receive_damage("kee", 400,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who,1);
				COMBAT_D->report_status(who);
			}
			else	message_combatd(HIC"可是$n"HIC"看破了$P的企图，闪在了一边。\n"NOR,this_object(),who);
		}
		else if( weapon->query("skill_type")=="sword" )
		{
			msg = HIC"\n$N大袖飘飘，身行突展，手中的$w"HIC"划出一片片白云，正是青莲剑绝技“苍茫云海间”!\n"NOR;
			set_temp("pfm_msg",1);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
			set_temp("pfm_msg",0);
			if( random(3) )
			{
				message_combatd(HIR"$n"HIR"身中一剑，顿时鲜血淋漓！\n"NOR,this_object(),who);
				who->receive_damage("kee", 300,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who);
			}
		}
		else
		{
			msg = HIC"\n$N大袖飘飘，身行突展，手中的$w"HIC"突发剑意，划出一片片白云，正是青莲剑绝技“苍茫云海间”!\n"NOR;
			set_temp("pfm_msg",1);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
			set_temp("pfm_msg",0);
			if( random(3) )
			{
				message_combatd(HIR"$n"HIR"身中一剑，顿时鲜血淋漓！\n"NOR,this_object(),who);
				who->receive_damage("kee", 300,this_object(),TYPE_PERFORM);
				COMBAT_D->report_status(who);
			}
		}	
	}
	else
		QUEST_D->randomPfm(this_object());
	
	call_out("tiaozhan_hit",6,who);
}
