#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 
      
void setname() 
{
	set_name("李白", ({"li bai","li",}));
	set("long",@LONG
大诗人李白，清高飘逸，剑术通神。
LONG);
	set("gender", "男性");
	set("age", 35);
	set("rank_info/respect", "李谪仙");
	set("per", 35);
	create_family("散仙派",2,"剑仙");

	set_skill("unarmed", 700);
	set_skill("dodge", 700);
	set_skill("parry", 700);
	set_skill("force", 700);
	set_skill("spells", 700);
	set_skill("sword",700);	
	set_skill("blade",700);
	set_skill("literate",700);
	set_skill("yinyang-zhang",700);
	map_skill("unarmed","yinyang-zhang");
	set_skill("bolomiduo",700);
	set_skill("five-avoid",700);
	set_skill("wuzheng-force",700);
	map_skill("force","bolomiduo");
	map_skill("dodge","five-avoid");
	set_skill("pomo-blade",700);
	map_skill("blade","pomo-blade");
	set_skill("qinglian-jian",700);
	map_skill("sword","qinglian-jian");
	set_skill("scratmancy",700);
	map_skill("spells","scratmancy");	
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","qinglian-jian");
	}
	else
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","pomo-blade");
	}
}
int is_job(){return 1;}
