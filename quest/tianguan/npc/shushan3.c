#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname() 
{
	set_name("白眉",({"bai mei","bai",}));
	set("long",@LONG
这位满头白发的老人，一双银白的长眉低垂。
LONG);
	set("gender", "男性");
	set("age", 125);
	set("per", 40);
	create_family("蜀山派",1,"丝");
	set_skill("spells",700);
	set_skill("force", 700);
	set_skill("dodge", 700);
	set_skill("parry", 700);
	set_skill("sword", 700);
	set_skill("zixia-shengong", 700);
	set_skill("sevensteps", 700);
	set_skill("hunyuan-zhang", 700);
	set_skill("literate", 700);
	set_skill("unarmed", 700);
	set_skill("mindsword", 700);
	set_skill("yujianshu", 700);
	set_skill("taoism",700);
	map_skill("spells", "taoism");
	map_skill("dodge", "sevensteps");
	map_skill("force", "zixia-shengong");
	map_skill("parry", "mindsword");
	map_skill("sword", "mindsword");
	map_skill("unarmed", "hunyuan-zhang");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	carry_object(0,"sword",1)->wield();
}

int is_job(){return 1;}