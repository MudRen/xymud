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
		set_name("丹辰子",({"danchen zi","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		if( sscanf(id,"%s %s",tmp,id)==2 )
			ids = ({id+" zi",id,"di zi"});
		else
			ids = ({"di zi",});	
		i = strlen(name);
		if( i<=2 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		name = name+"子";			
		set_name(name,ids);
	}	
	set("my_master","zhenyuan daxian");
	set("gender", "男性");
	set("age", 35);
	set("per", 20+random(20));
	set("int", 100);
	set("con", 100);
	create_family("五庄观",3,"弟子");	
	set_skill("unarmed",350+random(70));
	set_skill("wuxing-quan", 350+random(70));
	set_skill("dodge",350+random(70));
	set_skill("baguazhen",350+random(70));
	set_skill("parry",350+random(70));
	set_skill("sword",350+random(70));
	set_skill("sanqing-jian",350+random(70));
	set_skill("staff",350+random(70));
	set_skill("fumo-zhang",350+random(70));
	set_skill("hammer",350+random(70));
	set_skill("kaishan-chui",350+random(70));
	set_skill("blade",350+random(70));
	set_skill("yange-blade",350+random(70));
	set_skill("force",350+random(70));   
	set_skill("zhenyuan-force",350+random(70));
	set_skill("literate",350+random(70));
	set_skill("spells", 350+random(70));
	set_skill("taiyi", 350+random(70));
   	map_skill("spells", "taiyi");
   	map_skill("force", "zhenyuan-force");
   	map_skill("unarmed", "wuxing-quan");
   	map_skill("sword", "sanqing-jian");
   	map_skill("dodge", "baguazhen");
   	map_skill("staff", "fumo-zhang");
   	map_skill("blade", "yange-blade");
   	map_skill("hammer", "kaishan-chui");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",7408800);
	set("daoxing",7408800);
	i = 1000+random(5000);
	add_temp("apply/karma",i);	
	if( random(2) )
		carry_object(0,"sword",1)->wield();	
	else if( random(2) )
		carry_object(0,"blade",1)->wield();	
	else
		carry_object(0,"staff",1)->wield();	
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
		powerup(0,1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( random(5)==0 )
	{
		SPELL_D->attacking_cast(
			this_object(),
			who,
			300,
			250,
			"eff_kee", 		
			HIC "$N"HIC"几个指头迅速捻动，突然张嘴一喷！红橙黄三道火焰呼！地一声向$n"HIC"卷去！\n" NOR,
			HIC "结果$n"HIC"被烧得焦头烂额！\n" NOR, 
			HIC "但是$n"HIC"轻轻一跳就躲了开来。\n" NOR, 
			HIC "但是火焰被$n"HIC"以法力一逼，反向$P回卷而去！\n" NOR, 
			HIC "结果太乙真火反噬，$n"HIC"被烧得焦头烂额！\n" NOR
		);
	}
	else
		QUEST_D->randomPfm(this_object());
	
	call_out("tiaozhan_hit",8,who);
}