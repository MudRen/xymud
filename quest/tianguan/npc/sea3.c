#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

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

set_skill("huntian-hammer",700);
set_skill("hammer",700);
set_skill("literate", 700);
set_skill("unarmed",700);
set_skill("dodge",700);
set_skill("force",700);
set_skill("parry",700);
set_skill("fork",700);
set_skill("spells",700);
set_skill("seashentong",700);
set_skill("dragonfight",700);
set_skill("dragonforce",700);
set_skill("fengbo-cha",700);
set_skill("dragonstep",700);
map_skill("hammer", "huntian-hammer");
map_skill("spells", "seashentong");
map_skill("unarmed", "dragonfight");
map_skill("force", "dragonforce");
map_skill("fork", "fengbo-cha");
map_skill("parry", "fengbo-cha");
map_skill("dodge", "dragonstep");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	carry_object(0,"unarmed",1)->wield();
}

int is_job(){return 1;}