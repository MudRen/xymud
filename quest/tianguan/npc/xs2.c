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
		set_name("巨鸟",({"ju niao","niao","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({id+" niao",id,"niao","di zi"});
		else
			ids = ({"niao","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = name+"鸟";			
		set_name(name,ids);
	}	
	set("my_master","dapeng mingwang");	
	set("age", 45);
	set("per", 20);
	set("str", 30);
	set("class", "yaomo");
	create_family("大雪山",3, "巡山小妖");

	set_skill("unarmed", 500+random(50));
	set_skill("cuixin-zhang", 500+random(50));
	set_skill("dodge", 500+random(50));
	set_skill("xiaoyaoyou", 500+random(50));
	set_skill("parry", 500+random(50));
	set_skill("sword", 500+random(50));
	set_skill("bainiao-jian", 500+random(50));
	set_skill("blade", 500+random(50));
	set_skill("bingpo-blade", 500+random(50));
	set_skill("throwing", 500+random(50));
	set_skill("force", 500+random(50));   
	set_skill("ningxie-force", 500+random(50));
	set_skill("literate", 150);
	set_skill("spells", 500+random(50));
	set_skill("dengxian-dafa", 500+random(50));
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",16637500);
	set("daoxing",16637500);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","bainiao-jian");
	}
	else
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","bingpo-blade");
	}
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object *inv,weapon;
	string msg,*msgs;
	int d,i,k;
	remove_call_out("tiaozhan_hit");
	this_object()->stop_busy();	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(0,1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",4,who);
}

void help_kill(object who)
{
	int i,f=0;
	object *inv,npc;
	if( !who )      return;
	inv = all_inventory(environment());
	for(i=0;i<sizeof(inv);i++)
	{
		npc = inv[random(sizeof(inv))]; 
		if( npc && living(npc) && !userp(npc) //玩家或昏迷的
		 && !npc->is_fighting(who)		     //在战斗的
		 && npc!=this_object()			  //..
		 && f< 1
		 && npc->query("my_master") )
		{
			say( sprintf("%s在旁说道：%s道友，休要惊慌，我来助你一臂之力。\n",npc->name(),this_object()->name(1)[0..1]));
			npc->set_temp("help_kill",1);
			npc->kill_ob(who);
			npc->set_temp("help_kill",0);
			f++;
		}
	}
	return;       
}

void kill_ob(object who)
{
	if( who && present(who,environment()) && userp(who)
	 && !this_object()->is_fighting()
	 && !query_temp("help_kill") )
	{	
		powerup(0,1);
		help_kill(who);
	}	
	::kill_ob(who);
}

void heart_beat()
{
	object me = this_object();
	if( me->query("force")>100 && me->is_fighting() )
	{
     	if( query("eff_kee") < query("max_kee") )
        	QUEST_D->addEffKee(me);
        if( query("kee") < query("eff_kee") )
        	QUEST_D->addKee(me);
        if( query("sen") < query("eff_sen") )
        	QUEST_D->addSen(me);
        if( query("eff_sen") < query("max_sen") )
        	QUEST_D->addEffSen(me);
        me->stop_busy();
        QUEST_D->randomPfm(this_object());		
	}
	::heart_beat();
}
