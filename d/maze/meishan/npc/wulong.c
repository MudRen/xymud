#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit BOSS;

int chat()
{ 
	mixed bz; 
	object weapon2,you_weapon,target,weapon,me=this_object(); 
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
        	
	if( random(3)==0 && !me->query_temp("powerup") )
		command("exert anti");
			
        if( random(5)==0 && me->query("eff_kee")<me->query_maxkee() )
        	command("cast suliao");
        
        if( random(4)==0 && !me->is_busy() )
        {
        	if( random(2) )
        		command("cast zhanqi");		
        	else	command("cast huanying");
        }	
        
	weapon = query_temp("weapon");
	if( weapon )
	{	
		if( weapon->query("skill_type")=="blade" )
		{
			weapon2 = present("sword",me);
			if( !me->is_busy() )
			{
				if( random(4)==0 && !target->is_busy() )
					command("perform pozhan");
				if( random(3)==0 )
					command("perform xiao");
				if( random(5)==0 )
					command("perform shendao");
				else if( random(4)==0 && weapon2 && present(weapon2,me) )
				{
					weapon->unequip();
					weapon2->wield();
					reset_action();
					if( !me->query_temp("zxzx") )
						command("perform zxzx");
					if( random(2) )
						command("perform yaowu");
					if( weapon2 && present(weapon2,me) ) 
						weapon2->unequip();
					if( weapon && present(weapon,me) ) 
					{
						weapon->wield();
						reset_action();
					}	
				}
				else if( random(3)==0 )
					command("perform diyu");
			}
		}
		else
		{
			weapon2 = present("blade",me);
			if( !me->is_busy() )
			{
				if( !me->query_temp("zxzx") )
					command("perform zxzx");
				if( random(2) )
					command("perform yaowu");
				else if( weapon2 && present(weapon2,me) )
				{
					weapon->unequip();
					weapon2->wield();
					reset_action();
					if( random(4)==0 && !target->is_busy() )
						command("perform pozhan");
					if( random(3)==0 )
						command("perform xiao");
					if( random(5)==0 )
						command("perform shendao");
					else if( random(3) )
						command("perform diyu");
					weapon2->unequip();
					if( weapon && present(weapon,me) ) 
					{
						weapon->wield();
						reset_action();
					}
				}	
			
			}
		}	
		
		you_weapon = target->query_temp("weapon");
		if( you_weapon && random(5)==0 && !me->is_busy() )
		{
			weapon = query_temp("weapon");
			if( weapon )
			{
				weapon->unequip();
				reset_action();
			}	
			command("perform duo");
			if( weapon && present(weapon,me) ) 
			{
				weapon->wield();
				reset_action();
			}	
		}
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
	set_name("??????",({"wu long","wu","long"}));
  	set_level(110);
  	set("title", HIC"????????????"NOR);
  	set("title","????????????");
  	set("gender", "??????" );
  	set("age", 30);
  	set("long", "
	????????????????????????????????????????????????????????????????????????????????????????????????  	
\n");
	create_family("??????????????????", 2, "??????");
  	set_skill("unarmed",1100);
  	set_skill("dodge", 1100);
  	set_skill("parry", 1100);
  	set_skill("spells", 1100); 
  	set_skill("yaofa", 1100);
  	set_skill("sword",1100);
  	set_skill("qixiu-jian",1100);
  	set_skill("blade", 1100);
  	set_skill("kugu-blade", 1100);
  	set_skill("lingfu-steps",1100);
  	set_skill("yinfeng-zhua",1100);
  	set_skill("force", 1100);   
  	set_skill("huntian-qigong", 1100);
	set_skill("literate",1100);
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
	set("env/test",({"HIB","HIR","HIM"})[random(3)]);
	setup();
	add_temp("apply/max_kee",10000);
	add_temp("apply/max_sen",10000);
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"hand",1)->wear();
	carry_object(0,"blade",1)->wield();
	carry_object(0,"sword",1);
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
	message_vision("\n$N?????????????????????????????????????????????????????????????????????\n",this_object());
	message_vision(HIY"??????????????????????????????????????????????????????\n\n"NOR,this_object());
	corpse = new("/obj/corpse");
	corpse->set_name("????????????",({"wugong's corpse","corpse"}));
	corpse->set("long","????????????????????????\n");
	if( corpse->move(environment()) )
		message_vision("\n????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????\n",this_object());
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
			message("vision",HIW"??????????????????"+team[i]->query("name")+HIW"?????????"+p+"???????????????????????????????????????"+pp+"%"NOR"\n",team);
			re = 0;
			re = reward_ob(team[i]);
			if( re && re!="" )
				message("vision",HIW"??????????????????"+team[i]->query("name")+HIW"?????????"+re+HIW"???"NOR"\n",team);
			if( team[i]==who )
			{
				re = 0;
				re = reward_ob(team[i]);
				if( re && re!="" )
					message("vision",HIW"??????????????????"+team[i]->query("name")+HIW"?????????"+re+HIW"???"NOR"\n",team);
			}				
		}
	}
	else	
	{
		who->set_temp("pending/"+query("name"),1);
		who->add_temp("maze/meishan_kill",1);
		p = base;
		who->add("combat_exp",p);
		tell_object(who,HIC"??????????????????????????????"+p+"??????????????????"NOR"\n");
		re = reward_ob(who);
		if( re && re!="" )
			tell_object(who,HIC"??????????????????????????????"+re+HIC"???"NOR"\n");
	}
	destruct(this_object());
	return;	
}	

int is_meishan(){ return 1;}

string obj_from(){ return "????????????????????????";}