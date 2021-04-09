#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c";

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
set("per", 30);
set("looking", "面色红润，满脸福态。");
set_skill("literate", 700);
set_skill("unarmed",700);
set_skill("dodge",700);
set_skill("force",700);
set_skill("parry",700);
set_skill("sword",700);
set_skill("spells",700);
set_skill("whip",700);
set_skill("jueqingbian",700);
set_skill("moonshentong",700);
set_skill("baihua-zhang",700);
set_skill("moonforce",700);
set_skill("snowsword",700);
set_skill("moondance",700);
map_skill("spells", "moonshentong");
map_skill("unarmed", "baihua-zhang");
map_skill("force", "moonforce");
map_skill("sword", "snowsword");
map_skill("parry", "snowsword");
map_skill("dodge", "moondance");
map_skill("whip","jueqingbian");
create_family("月宫", 1, "红");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
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
}
int is_job(){return 1;}