#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname() 
{
set_name("白发老人", ({"lao ren", "ren","baifa"}));
set("long","这是一位鹤发童颜的老人。他看起来似乎很老的样子，
但偏又是红光满面。看到你打量他，他对你和蔼地笑了一笑。\n");
set("gender", "男性");
set("age", 86);
set("title", "神仙");
set("per", 5);
set("int", 100);
set("con", 100);
set("str", 100);
create_family("将军府",1, "将");
set("faith",10000);
set_skill("changquan",700);
set_skill("yanxing-steps",700);
set_skill("spear",700);
set_skill("mace",700);
set_skill("axe",700);
set_skill("force",700);
set_skill("unarmed",700);
set_skill("dodge",700);
set_skill("parry",700);
set_skill("spells",700);
set_skill("xuanyuan-archery",700);
set_skill("jinglei-mace",700);
set_skill("sanban-axe",700);
set_skill("archery",700);
set_skill("bawang-qiang",700);
set_skill("lengquan-force",700);
set_skill("literate",700);
set_skill("baguazhou",700);
map_skill("spells", "baguazhou");
map_skill("force", "lengquan-force");
map_skill("unarmed", "changquan");
map_skill("spear", "bawang-qiang");
map_skill("parry", "jinglei-mace");
map_skill("mace", "jinglei-mace");
map_skill("archery", "xuanyuan-archery");
map_skill("axe", "sanban-axe");
map_skill("dodge", "yanxing-steps");
set("chushi/chushi_jjf","yes");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
	{
		carry_object(0,"axe",1)->wield();
		map_skill("parry","sanban-axe");
		set("family/jjf_type","axe");
	}
	else if( random(2) )
	{
		carry_object(0,"spear",1)->wield();
		map_skill("parry","bawang-qiang");
		set("family/jjf_type","spear");		
	}
	else
	{
		carry_object(0,"mace",1)->wield();
		map_skill("parry","jinglei-mace");
		set("family/jjf_type","mace");		
	}
}
int is_job(){return 1;}