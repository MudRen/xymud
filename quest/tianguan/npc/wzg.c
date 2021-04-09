#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 
      
void setname() 
{
	set_name("镇元大仙",({"zhenyuan daxian","daxian","zhenyuan"}));
	set("long",@LONG
交游遍三界，桃李漫五行。好一位地仙之祖！
LONG);
	set("gender", "男性");
	set("age", 45);
	set("per", 40);
	set("int", 100);
	set("con", 100);
	set("title","五庄观观主");
	set("rank_info/respect", "观主");
	create_family("五庄观",1,"丝");	
	set_skill("unarmed",420);
	set_skill("wuxing-quan", 420);
	set_skill("dodge",420);
	set_skill("baguazhen",420);
	set_skill("parry",420);
	set_skill("sword",420);
	set_skill("sanqing-jian",420);
	set_skill("staff",420);
	set_skill("fumo-zhang",420);
	set_skill("hammer",420);
	set_skill("kaishan-chui",420);
	set_skill("blade",420);
	set_skill("yange-blade",420);
	set_skill("force",420);   
	set_skill("zhenyuan-force",420);
	set_skill("literate",420);
	set_skill("spells", 420);
	set_skill("taiyi", 420);
   	map_skill("spells", "taiyi");
   	map_skill("force", "zhenyuan-force");
   	map_skill("unarmed", "wuxing-quan");
   	map_skill("sword", "sanqing-jian");
   	map_skill("dodge", "baguazhen");
   	map_skill("staff", "fumo-zhang");
   	map_skill("blade", "yange-blade");
   	map_skill("hammer", "kaishan-chui");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",14817600);
	set("daoxing",14817600);
	i = 5000+random(5000);
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
		powerup(1);
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