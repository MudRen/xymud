#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
set_name("观音菩萨", ({ "guanyin pusa", "guanyin", "pusa" }));
set("title", "救苦救难大慈大悲");
set("long", @LONG
理圆四德，智满金身。眉如小月，眼似双星。兰心欣紫竹，
蕙性爱得藤。她就是落伽山上慈悲主，潮音洞里活观音。
LONG);
set("gender", "女性");
set("age", 35);
set("rank_info/self", "贫僧");
set("rank_info/respect", "菩萨娘娘");
set("class", "bonze");
create_family("南海普陀山",2, "菩萨");
set("chushi/chushi_putuo","yes");        
set("class", "bonze");
set_skill("jienan-zhi", 600);
set_skill("lotusmove", 600);
set_skill("staff", 600);
set_skill("lunhui-zhang", 600);
set_skill("lotusforce", 600);
set_skill("literate", 800);
set_skill("buddhism", 600);
set_skill("blade", 600);
set_skill("cibeidao", 600);
set_skill("dodge", 600);
set_skill("force", 600);
set_skill("spells", 600);
set_skill("parry", 600);

map_skill("blade","cibeidao");
map_skill("spells", "buddhism");
map_skill("force", "lotusforce");
map_skill("unarmed", "jienan-zhi");
map_skill("staff", "lunhui-zhang");
map_skill("parry", "lunhui-zhang");
map_skill("dodge", "lotusmove");
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
	if( random(2) )
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","cibeidao");
	}
	else
	{
		carry_object(0,"staff",1)->wield();
		map_skill("parry","lunhui-zhang");
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
		command("cast yinshen");
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("anti_magic") )
		command("cast lianhua");
	if( !this_object()->is_yinshen() )
		command("cast yinshen");
					
	weapon = query_temp("weapon");
	if( weapon )
	{
		if( random(3)==1 )
		{
			command("unwield "+weapon->query("id"));
			QUEST_D->randomPfm(this_object());
			this_object()->stop_busy();	
			command("wield "+weapon->query("id"));
		}
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
		
	if( random(30)>15 )
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
		ar = ({ "staff","blade",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 2800+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",280+random(100));
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
	else if( random(20)>11 )
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