#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c";

void setname()
{
set_name("西王母", ({"xi wangmu", "xi", "wangmu","master"}));
set("long", "西华至妙生伊川，穆王八骑访昆仑。\n");
set("title", "月宫祖师");
set("gender", "女性");
set("age", 100);
set("class","xian");
set("attitude", "friendly");
set("rank_info/respect", "老太太");
set("cor", 30);
set("per", 30);
set("looking", "面色红润，满脸福态。");
set_skill("literate", 200);
set_skill("unarmed",480);
set_skill("dodge",480);
set_skill("force",480);
set_skill("parry",480);
set_skill("sword",480);
set_skill("spells",480);
set_skill("whip",480);
set_skill("jueqingbian",480);
set_skill("moonshentong",480);
set_skill("baihua-zhang",480);
set_skill("moonforce",480);
set_skill("snowsword",480);
set_skill("moondance",480);
map_skill("spells", "moonshentong");
map_skill("unarmed", "baihua-zhang");
map_skill("force", "moonforce");
map_skill("sword", "snowsword");
map_skill("parry", "snowsword");
map_skill("dodge", "moondance");
map_skill("whip","jueqingbian");
create_family("月宫", 1, "红");
}

int is_boss() {return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",22118400);
	set("daoxing",22118400);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","snowsword");
		set("force_factor",0);
	}
	else
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","jueqingbian");
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
	if( !query_temp("shenli") && random(4)==2 )
	{
		message_vision(HIW"$N"HIW"略一提气，运起轻功，拔剑起舞。只见$P足不沾地，手中剑越舞越快，逐渐幻做一团白雾，满堂滚动。\n" NOR,this_object());
		d = query_skill("sword")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/dodge",d);    
        set_temp("shenli", 1);
    }
    if( !query_temp("my_moon_invocation") )
    	command("cast invocation");
	QUEST_D->randomPfm(this_object());
	call_out("tiaozhan_hit",4,who);
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
		
	if( random(30)>20 )
	{
		who->add("potential",50000);	
		tell_object(who,"你获得了50000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	pp = who->query_temp("tiaozhan_armor_get");
	if( random(pp)==0 )
	{
		ar = ({
				"armor","hand","cloth","kui","neck","pifeng",
				"ring","shoes","waist","wrists",
		});	
		gift = new("/d/obj/narmor/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 1000+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",60+random(450));
		gift->init_armor(this_object());
		add_temp("apply/karma",-i);
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add_temp("tiaozhan_armor_get",1);
			who->add("combat_exp",-3000);
			who->add("daoxing",-3000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	else if( random(20)==15 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	return;
}	