#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname()
{
set_name("菩提祖师", ({"master puti","puti", "master"}));
set("long", "大觉金仙没垢姿，西方妙相祖菩提\n");
set("gender", "男性");
set("age", 100);
set("class", "taoist");
set("rank_info/respect", "老师祖");
set("per", 26);
set("looking", "玉面多光润，苍髯颌下飘，金睛飞火焰，长目过眉梢。");

set_skill("literate",620);
set_skill("unarmed",620);
set_skill("dodge",620);
set_skill("force",620);
set_skill("parry",620);
set_skill("stick",620);
set_skill("spells",620);
set_skill("whip",620);
set_skill("dao",620);
set_skill("puti-zhi",620);
set_skill("wuxiangforce",620);
set_skill("qianjun-bang",620);
set_skill("jindouyun",620);
map_skill("spells", "dao");
map_skill("unarmed", "puti-zhi");
map_skill("force", "wuxiangforce");
map_skill("stick", "qianjun-bang");
map_skill("parry", "qianjun-bang");
map_skill("dodge", "jindouyun");
create_family("方寸山三星洞", 1, "蓝");
set("fangcun/panlong_accept","done");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",47665600);
	set("daoxing",47665600);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"stick",1)->wield();
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
	if( !query_temp("jldl") )
		command("exert jldl");
	if( !query_temp("powerup") )
		command("exert shenjia");
	command("cast fenshen");
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
	object gift,weapon;    
	mapping skill;
	string *skills,temp,*ar;
	int i,pp;
	
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

	if( !is_pass(who) )
	{
		who->set("mark/tiaozhan/"+query("name"),1);
		who->add("mark/tiaozhan/num",1);
	}
		
	if( random(30)>14 )
	{
		who->add("potential",50000);	
		tell_object(who,"你获得了50000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	pp = who->query_temp("tiaozhan_weapon_get");
	pp+= 1;			
	if( random(pp)==0 )
	{
		ar = ({ "stick","sword",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 3000+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",300+random(150));
		gift->init_weapon(this_object());
		add_temp("apply/karma",-i);
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add_temp("tiaozhan_weapon_get",1);
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}	
	else if( random(20)>10 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	return;
}
