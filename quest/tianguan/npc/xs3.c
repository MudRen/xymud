#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname() 
{
	set_name("大鹏明王", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
	set("title", "雪山之祖");
	set("gender", "男性" );
	set("age", 45);
	set("per", 30);
	set("str", 30);
	set("long", "这位大鹏明王的确大有来历，说起来跟佛祖如来也有点亲戚关系，\n算是如来的“舅舅”。他不似其兄孔雀明王作恶多端，却也并非善类，\n且因其兄之故跟佛门结下深仇。生平最讨厌的就是和尚。\n");
	set("class", "yaomo");
	create_family("大雪山", 1, "祖师");
	set("rank_info/respect", "明王");
	set_skill("unarmed", 700);
	set_skill("cuixin-zhang", 700);
	set_skill("dodge", 700);
	set_skill("xiaoyaoyou", 700);
	set_skill("parry", 700);
	set_skill("sword", 700);
	set_skill("bainiao-jian", 700);
	set_skill("blade", 700);
	set_skill("bingpo-blade", 700);
	set_skill("throwing", 700);
	set_skill("force", 700);   
	set_skill("ningxie-force", 700);
	set_skill("literate", 700);
	set_skill("spells", 700);
	set_skill("dengxian-dafa", 700);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","bainiao-jian");
	}
	else
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","bingpo-blade");
	}
}
int is_job(){return 1;}