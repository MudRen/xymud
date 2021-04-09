#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

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
    set_skill("unarmed",700);
    set_skill("dodge", 700);
    set_skill("parry", 700);
    set_skill("spells", 700); 
    set_skill("yaofa", 700);
    set_skill("sword",700);
    set_skill("qixiu-jian",700);
    set_skill("blade", 700);
    set_skill("kugu-blade",700);
    set_skill("lingfu-steps",700);
    set_skill("yinfeng-zhua",700);
    set_skill("force", 700);   
    set_skill("huntian-qigong", 700);
    set_skill("literate",700);
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
  	set("env/brief_message",2);
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
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
}

int is_job(){return 1;}