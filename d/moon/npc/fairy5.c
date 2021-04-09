inherit SUPER_NPC;
#include "guanli.h"

void create()
{
       set_name("扫红",({"shao hong","red", "fairy"}));
       set("long",
"披罗衣之璀粲兮，珥瑶碧之华琚。戴金翠之首饰，缀明珠以耀躯。践
远游之文履，曳雾绡之轻裾。微幽兰之芳蔼兮，步踟蹰于山隅。\n");
       set("title", "月宫伺女");
       set("gender", "女性");
       set("age", 18);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "仙姑");
	set_level(80);
	set_skill("literate",800);
	set_skill("unarmed",800);
	set_skill("dodge",800);
	set_skill("force",800);
	set_skill("parry",800);
	set_skill("sword",800);
	set_skill("spells",800);
 	set_skill("moonshentong",800);
 	set_skill("baihua-zhang",800);
 	set_skill("moonforce",800);
 	set_skill("snowsword",800);
 	set_skill("moondance",800);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");
	create_family("月宫", 3, "弟子");
	set_temp("weapon_level",30+random(20));
	set_temp("armor_level",30+random(20));
	set("inquiry", ([
   		"青鸾" : (: ask_guanli :),
	]));
	setup();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"sword",random(10))->wield();
	powerup();
}

void die()
{
	if( environment() )
	{
		message_vision("\n$N脸色一变，勉力逼住伤势，念动月华真言，化作一道霞光直冲太阴而去！\n\n");
		if( query_temp("last_damage_from") )
			lose_inventory();
	}
	destruct(this_object());
}