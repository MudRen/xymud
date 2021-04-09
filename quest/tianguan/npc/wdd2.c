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
		set_name("老鼠精",({"laoshu jing","jing","shu","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({id+" shujing",id,"shu jing","jing","shu","di zi"});
		else
			ids = ({"shujing","shu jing","jing","shu","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = name+"鼠精";			
		set_name(name,ids);
	}	
	set("my_master","yu shu");
	create_family("陷空山无底洞",3, "弟子");	
    set_skill("unarmed",550+random(30));
    set_skill("dodge", 550+random(30));
    set_skill("parry", 550+random(30));
    set_skill("spells", 550+random(30)); 
    set_skill("yaofa", 550+random(30));
    set_skill("sword",550+random(30));
    set_skill("qixiu-jian",550+random(30));
    set_skill("blade", 550+random(30));
    set_skill("kugu-blade",550+random(30));
    set_skill("lingfu-steps",550+random(30));
    set_skill("yinfeng-zhua",550+random(30));
    set_skill("force", 550+random(30));   
    set_skill("huntian-qigong", 550+random(30));
    set_skill("literate",550+random(30));
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
  	set("env/brief_message",2);
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",19511200);
	set("daoxing",19511200);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","kugu-blade");
	}
	else
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","qixiu-jian");
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
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( random(5)==1 && !who->is_busy() )
	{
		msg = CYN "$N"CYN"的招式突然一变，变得全无章法，浑身上下破绽百出，$n"CYN"想攻，却不知道哪个破绽是真，哪个是假。结果$p被$P攻了个措手不及！\n" NOR;
		message_vision(msg,this_object(),who);
		who->start_busy(1+random(3));
	}
	else
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
		powerup(1);
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
