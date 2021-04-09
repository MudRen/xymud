#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("守城官兵",({"guan bing","bing"}));
	set_level(39);      
	set("env/brief_message",3);
	set("max_kee",100000);
	set("max_sen",100000);
	set("fangcun/panlong_accept","done");
	set("no_sleep",1);
	set("gender", "男性");
	set("age", 36);
	set("class","dragon");
	create_family("东海龙宫", 2, "水族");
	set("title","长安城");
	set_skill("huntian-hammer",390);
	set_skill("hammer",390);
	set_skill("literate", 150);
	set_skill("unarmed",390);
	set_skill("dodge",390);
	set_skill("force",390);
	set_skill("parry",390);
	set_skill("fork",390);
	set_skill("spells",390);
	set_skill("seashentong",390);
	set_skill("dragonfight",390);
	set_skill("dragonforce",390);
	set_skill("fengbo-cha",390);
	set_skill("dragonstep",390);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
	set("env/test","HIY");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"unarmed",1)->wield();
	powerup(1,1);
}

int accept_fight(object who)
{
return 0;
}

void die()
{
	message_vision("\n$N恶狠狠道：你等着！待某家叫军侯过来治你！！\n$N急急忙忙的离开了。\n\n",this_object());
	destruct(this_object());
}

void unconcious()
{
	die();
}

