#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit BOSS;

int chat()
{ 
	mixed bz; 
	int damage;
	object weapon2,target,weapon,me=this_object(); 
	if( !environment() 
	 || !living(this_object()) 
	 || !this_object()->is_fighting() 
	 || query("force")<100 ) 
	 	return 0; 
	if( me->is_busy() ) 
		me->stob_busy(1+random(3)); 
	if( me->is_busy() ) 
		return 0; 
	target = me->select_opponent(); 
	if( !target )
        	return 0;
        
        if( random(5)==0 && !target->is_busy() )
        {
        	message_vision("\n\n"HIW"$N"HIW"后退几步，张口吐出一道白光，直直射向$n"HIW"！"NOR"\n",me,target);
        	if( random(3)==0 )
        		message_vision("结果被$N闪开了。\n",target);
        	else
        	{
        		target->start_busy(5);
        		message_vision(HIW"结果$N"HIW"被白光定住了身形，动弹不得！"NOR"\n",target);
        	}	
        }
        	
	if( random(3)==0 && !me->query_temp("powerup") )
	{
		if( random(2) )
			command("exert jin");
		else	command("exert shield");
	}	
	
	if( random(5)==0 )
		command("exert heal");                                   
        
        if( !objectp(me->query_temp("invocation")) && random(6)==0 )
        	command("cast hufa");
        
        if( valid_move(target) && random(5)==0 )
        	command("cast freez");
        
        if( random(5)==0 )
        	command("cast water");
        	
        weapon = query_temp("weapon");
	if( weapon && !me->is_busy() )
	{
		if( weapon->query("skill_type")=="unarmed" )
		{
			weapon2 = present("fork",me);
			if( weapon2 && random(5)==0 )
			{
				weapon->unequip();
				weapon2->wield();
				if( random(3)==0 && !target->is_busy() )
					command("perform fengbo");
				if( !me->is_busy() )
				{
					if( random(3)==0 && me->query_temp("sea_wuliang")<=0 )
						command("perform dhwl");
					if( random(3)==0 )
						command("perform bibo");
					else if( random(3)==0 )
						command("perform chuhai");	
				}
				weapon2->unequip();
				if( weapon && present(weapon,me) ) 
					weapon->wield();
			}
			if( !me->is_busy() )
			{
				if( random(3)==0 )
					command("perform leidong");
				if( random(3)==0 )
					command("perform shenlong");
				if( random(3)==0 )
					command("perform sheshen");
				if( random(5)==0 )
					command("perform yansha");			
			}
		}
		else if( weapon->query("skill_type")=="fork" )
		{
			if( random(3)==0 && !target->is_busy() )
				command("perform fengbo");
			if( !me->is_busy() )
			{
				if( random(3)==0 && me->query_temp("sea_wuliang")<=0 )
					command("perform dhwl");
				if( random(3)==0 )
					command("perform bibo");
				else if( random(3)==0 )
					command("perform chuhai");	
			}
			weapon2 = present("unarmed",me);
			if( weapon2 )
			{
				weapon->unequip();
				weapon2->wield();
				if( random(3)==0 )
					command("perform leidong");
				if( random(3)==0 )
					command("perform shenlong");
				if( random(3)==0 )
					command("perform sheshen");
				if( random(5)==0 )
					command("perform yansha");
				weapon2->unequip();
				if( weapon && present(weapon,me) )
					weapon->wield();
			}
		}
		else	destruct(weapon);
	}
	else
	{
		if( query("eff_kee") < me->query_maxkee() )
			QUEST_D->addEffKee(me);
		if( query("kee") < query("eff_kee") )
                	QUEST_D->addKee(me);
		if( query("sen") < query("eff_sen") )
                	QUEST_D->addSen(me);
		if( query("eff_sen") < me->query_maxsen() )
                	QUEST_D->addEffSen(me);
		QUEST_D->randomPfm(me);
	}
	if( !me->is_busy() )
	{
		if( query("eff_kee")<me->query_maxkee() )
		 	command("eat yao");
		if( query("eff_sen")<me->query_maxsen() )
			command("eat dan");
		if( query("force")>30 )
		{
			if( query("kee")<query("eff_kee") )
				command("exert recover");
			if( query("sen")<query("eff_sen") )	
		 		command("exert refresh");
		 }		
	}			
	return 1;
}

void create()
{
        set_name("杨显",({"yang xian","yang","xian"}));
        set_level(110);
        set("nickname", HIC"三阳开泰"NOR);
        set("title","长角大仙");
        set("gender", "男性" );
        set("age", 30);
        set("long", "
	顶上金冠生杀气，柳叶甲挂龙鳞砌。
	头生双角气峥嵘，白面长须声更细。\n");
	set("class", "yaomo");
        set("attitude", "aggressive");
	set("force_factor", 300);
	set("mana_factor", 500);
	set("per",10);
	create_family("东海龙宫", 2, "弟子");
	set_skill("literate", 1100);
	set_skill("unarmed", 1100);
	set_skill("dodge", 1100);
	set_skill("force", 1100);
	set_skill("parry", 1100);
	set_skill("fork", 1100);
	set_skill("spells", 1100);
	set_skill("seashentong", 1100);
	set_skill("dragonfight", 1100);
	set_skill("dragonforce", 1100);
	set_skill("fengbo-cha", 1100);
	set_skill("dragonstep", 1100);
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
	set("env/test",({"HIB","HIR","HIM"})[random(3)]);
	setup();
	add_temp("apply/max_kee",10000);
	add_temp("apply/max_sen",10000);
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"unarmed",1)->wield();
	carry_object(0,"fork",1);
	carry_object("/d/obj/drug/jinchuang")->set_amount(300);
	carry_object("/d/obj/drug/hunyuandan")->set_amount(300);
	powerup(0,1);
}

string query_maze_file(){return "meishan";}

void dies()
{
	string *ids,re;
	int pp,p,i,base,damage_total;
	mapping hurt;
	object *team,corpse,who = query_temp("last_damage_from");
	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",this_object());
	message_vision(HIR"一道红光从尸身上窜出，直奔天际而去。\n\n"NOR,this_object());
	corpse = new("/obj/corpse");
	corpse->set_name("山羊尸体",({"shanyang's corpse","corpse"}));
	corpse->set("long","一只山羊的尸体。\n");
	if( corpse->move(environment()) )
		message_vision("\n红光散去，但见那遗下的尸骸却是一只山羊，原来是谁的一缕神识栖宿于此肉身作怪而已。\n",this_object());
	else	destruct(corpse);	
	if( !who || !present(who,environment()) || (who->query_level()>=120 && !wizardp(who)) 
	 || !userp(who) || who->query_temp("pending/"+query("name")) )
	{
		destruct(this_object());
		return;	
	}
	base = 200000;
	damage_total = 0;
	hurt = this_object()->query_hurt();
	if( hurt && mapp(hurt) )
	{
		ids = keys(hurt);
		if( ids && arrayp(ids) && sizeof(ids)>1 )
		{
			for(i=0;i<sizeof(ids);i++)
				damage_total+= hurt[ids[i]];	
		}
	}
	
	team = who->query_team();
	if( team && arrayp(team) && sizeof(team)>1 && damage_total>0 )
	{
		for(i=0;i<sizeof(team);i++)
		{
			if( !team[i] || !living(team[i]) || !present(team[i],environment())
			 || !userp(team[i]) || !team[i]->query_temp("maze/meishan") )
				continue;
			team[i]->set_temp("pending/"+query("name"),1);
			team[i]->add_temp("maze/meishan_kill",1);
			if( !undefinedp(hurt[team[i]->query("id")]) )
				pp = hurt[team[i]->query("id")]*100/damage_total;
			else	pp = 0;
			if( team[i]==who )
				pp+= 10;
			p = base;
			p+= p*pp/100;
			team[i]->add("combat_exp",p);
			message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+p+"点武学经验，其中附加经验为"+pp+"%"NOR"\n",team);
			re = 0;
			re = reward_ob(team[i]);
			if( re && re!="" )
				message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+re+HIW"。"NOR"\n",team);
			if( team[i]==who )
			{
				re = 0;
				re = reward_ob(team[i]);
				if( re && re!="" )
					message("vision",HIW"【梅山七圣】"+team[i]->query("name")+HIW"得到了"+re+HIW"。"NOR"\n",team);
			}				
		}
	}
	else	
	{
		who->set_temp("pending/"+query("name"),1);
		who->add_temp("maze/meishan_kill",1);
		p = base;
		who->add("combat_exp",p);
		tell_object(who,HIC"【梅山七圣】你得到了"+p+"点武学经验。"NOR"\n");
		re = 0;
		re = reward_ob(who);
		if( re && re!="" )
			tell_object(who,HIC"【梅山七圣】你得到了"+re+HIC"。"NOR"\n");
	}
	destruct(this_object());
	return;	
}	

int is_meishan(){ return 1;}

string obj_from(){ return "【梅山七圣副本】";}