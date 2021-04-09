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
		set_name("弟子",({"dizi","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"gui "+id,id,"gui","di zi"});
			else
				ids = ({"gui","di zi",});	
			name = "龟"+name;			
		}
		else if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"xia "+id,id,"xia","di zi"});
			else
				ids = ({"xia","di zi",});	
			name = "虾"+name;			
		}
		else
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"xie "+id,id,"xie","di zi"});
			else
				ids = ({"xie","di zi",});	
			name = "蟹"+name;			
		}				
		set_name(name,ids);	
	}	
	set("my_master","ao guang");
	set("gender", "男性");
	set("age", 16+random(20));
	set("class","dragon");
	set("per", 15);
	create_family("东海龙宫", 2+random(3), "巡海夜叉");

set_skill("huntian-hammer", 600+random(50));
set_skill("hammer", 600+random(50));
set_skill("literate", 600+random(50));
set_skill("unarmed", 600+random(50));
set_skill("dodge", 600+random(50));
set_skill("force", 600+random(50));
set_skill("parry", 600+random(50));
set_skill("fork", 600+random(50));
set_skill("spells", 600+random(50));
set_skill("seashentong", 600+random(50));
set_skill("dragonfight", 600+random(50));
set_skill("dragonforce", 600+random(50));
set_skill("fengbo-cha", 600+random(50));
set_skill("dragonstep", 600+random(50));
map_skill("hammer", "huntian-hammer");
map_skill("spells", "seashentong");
map_skill("unarmed", "dragonfight");
map_skill("force", "dragonforce");
map_skill("fork", "fengbo-cha");
map_skill("parry", "fengbo-cha");
map_skill("dodge", "dragonstep");

}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",27462500);
	set("daoxing",27462500);
	i = 3000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
		carry_object(0,"unarmed",1)->wield();
	else if( random(2) )
		carry_object(0,"fork",1)->wield();	
	else
		carry_object(0,"hammer",1)->wield();	
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
	if( !query_temp("powerup") )
		command("exert shield");
	QUEST_D->randomPfm(this_object());	
	call_out("tiaozhan_hit",3,who);
}

void tell_object(object who,string arg)
{
	arg = HIG"【星月挑战】"+arg+NOR;
	return efun::tell_object(who,arg);
}

void reward_ob(object who)
{
	remove_call_out("tiaozhan_hit");
	if( !who || !userp(who) )
		return;

	if( time()<who->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	 || who->query("combat_exp")<10000
	 || who->query("daoxing")<10000 
	 || !who->query("obstacle/reward") )	
	{	 	
		tell_object(who,"你条件不够，无法在此地图得到任何附加奖励。\n");
		return;
	}

	if( random(30)>10 )
	{
		who->add("potential",30000);	
		tell_object(who,"你获得了30000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
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
                 && !npc->is_fighting(who)                   //在战斗的
                 && npc!=this_object()                    //..
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
