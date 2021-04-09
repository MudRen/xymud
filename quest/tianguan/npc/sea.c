#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
set_name("敖广", ({"ao guang", "ao","guang","longwang","wang"}));
set("long","敖广是东海的龙王，其兄弟分别掌管东，西，南，北四海。
由余其水族众多，声势浩大，俨然独霸一方。\n");
set("gender", "男性");
set("age", 66);
set("title", "东海龙王");
set("class","dragon");
set("per", 15);
create_family("东海龙宫", 1, "水族");

set_skill("huntian-hammer",650);
set_skill("hammer",650);
set_skill("literate", 650);
set_skill("unarmed",650);
set_skill("dodge",650);
set_skill("force",650);
set_skill("parry",650);
set_skill("fork",650);
set_skill("spells",650);
set_skill("seashentong",650);
set_skill("dragonfight",650);
set_skill("dragonforce",650);
set_skill("fengbo-cha",650);
set_skill("dragonstep",650);
map_skill("hammer", "huntian-hammer");
map_skill("spells", "seashentong");
map_skill("unarmed", "dragonfight");
map_skill("force", "dragonforce");
map_skill("fork", "fengbo-cha");
map_skill("parry", "fengbo-cha");
map_skill("dodge", "dragonstep");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",54925000);
	set("daoxing",54925000);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"unarmed",1)->wield();
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
	command("cast hufa");
	if( random(5)==1 && !who->is_busy() )
	{
		msg = "$N抄起一柄钢叉，还拿衣服擦了擦叉尖。\n";
		message_vision(msg,this_object(),who);
		message_vision(HIC"$N"HIC"挥展开来，左一叉，右一叉，幻出无数大小光环向$n"HIC"绕去。虽看起来柔弱无力，却宛若秋波般连绵不绝，实是暗藏杀机！\n\n"NOR,this_object(),who);
		if( random(3) )
		{
			message_combatd(HIR"$N"HIR"果然被这光环套住，当时目瞪口呆，不知所措！\n"NOR,who);
			who->start_busy(2+random(3));
		}
		else
			message_vision(HIR"不料确被$N看破，攻其不备，$n反被打了个措手不及！\n"NOR,who,this_object());		
	}
	else
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
		
	if( random(30)>13 )
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
		ar = ({ "fork","unarmed",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 5500+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",380+random(100));
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
	else if( random(20)>9 )
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