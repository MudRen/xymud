#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
	set_name("玉鼠精", ({"yu shu","yushu", "shu", "monster"}));
    set("gender", "女性" );
    set("age", 23);
    set("long", 
"她就是这无底洞的洞主了。她从修道成人行以来，吃人无数，\n"
"也不知为什么玉皇还未曾派兵来围剿。听说她在天宫有亲，也\n"
"不知真假。\n");
    set("title", "地涌夫人");
  	create_family("陷空山无底洞", 1, "弟子");
	set("per",30);
    set_skill("unarmed",580);
    set_skill("dodge", 580);
    set_skill("parry", 580);
    set_skill("spells", 580); 
    set_skill("yaofa", 580);
    set_skill("sword",580);
    set_skill("qixiu-jian",580);
    set_skill("blade", 580);
    set_skill("kugu-blade",580);
    set_skill("lingfu-steps",580);
    set_skill("yinfeng-zhua",580);
    set_skill("force", 580);   
    set_skill("huntian-qigong", 580);
    set_skill("literate",580);
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
  	set("env/brief_message",2);
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",39022400);
	set("daoxing",39022400);
	i = 5000+random(5000);
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
	if( !query_temp("powerup") )
		command("perform dodge.bianfu");
	if( time()>query_temp("last_shuliao")+8 )
	{
		command("cast suliao");		
		if( this_object()->is_busy() )
			set_temp("last_shuliao",time());
	}
	weapon = query_temp("weapon");
	if( (!weapon || weapon->query("skill_type")!="blade")
	 && time()>query_temp("last_pozhan")+10 && !who->is_busy() )
	{
		msg = CYN "$N"CYN"的招式突然一变，变得全无章法，浑身上下破绽百出，$n"CYN"想攻，却不知道哪个破绽是真，哪个是假。结果$p被$P攻了个措手不及！\n" NOR;
		message_vision(msg,this_object(),who);
		who->start_busy(1+random(3));
		set_temp("last_pozhan",time());
	}
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
		
	if( random(30)>16 )
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
		ar = ({ "sword","blade",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 2500+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",250+random(100));
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
	else if( random(20)>12 )
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