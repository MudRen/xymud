#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c";

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("female");
	if( !names )
		set_name("幽魂",({"you hun","hun","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({id+" gui",id,"gui","di zi"});
		else
			ids = ({"gui","di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = name+"鬼";			
		set_name(name,ids);
	}	
	set("my_master","yanluo wang");
set("gender", "女性");
set("age", 16+random(20));
set("class","youling");
set("per", 15);
set("int", 100);
set("con", 100);
set("str", 100);
set("national","鬼族");
create_family("阎罗地府", 3+random(3), "鬼魂");

set_skill("whip", 480+random(40));
set_skill("hellfire-whip", 480+random(40));
set_skill("stick",480+random(40));
set_skill("kusang-bang",480+random(40));
set_skill("ghost-steps", 480+random(40));
set_skill("jinghun-zhang", 480+random(40));
set_skill("tonsillit", 480+random(40));
set_skill("gouhunshu", 480+random(40));
set_skill("zhuihun-sword", 480+random(40));
set_skill("sword", 480+random(40));
set_skill("force", 480+random(40));
set_skill("spells", 480+random(40));
set_skill("literate", 480+random(40));
set_skill("parry", 480+random(40));
set_skill("dodge", 480+random(40));
map_skill("sword","zhuihun-sword");
map_skill("force", "tonsillit");
map_skill("whip", "hellfire-whip");
map_skill("stick","kusang-bang");
map_skill("parry", "kusang-bang");
map_skill("spells", "gouhunshu");
map_skill("dodge", "ghost-steps");
map_skill("unarmed", "jinghun-zhang");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",14060800);
	set("daoxing",14060800);
	i = 3000+random(3000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","zhuihun-sword");
	}
	else if( random(2) )
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","hellfire-whip");
	}
	else
	{
		carry_object(0,"stick",1)->wield();
		map_skill("parry","kusang-bang");
	}
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d,k;
	this_object()->stop_busy();	
	remove_call_out("tiaozhan_hit");	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("shenli") )
	{
		message_vision(HIR"$N"HIR"微一凝神，运起反五行摄气诀，头上冒出一股青气，脸部现出一个鬼形。。。\n" NOR,this_object());
		d = query_skill("force")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/dodge",d);    
        add_temp("apply/parry",d);
        add_temp("apply/strength",d);
        set_temp("shenli", 1);
    }
	QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",3+random(3),who);
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