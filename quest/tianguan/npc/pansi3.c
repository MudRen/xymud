#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 
      
void setname() 
{
	set_name("紫霞仙子", ({"zixia xianzi","zixia","xianzi","girl",}));
	set("long",@LONG
她就是盘丝洞的开山祖师,传说她是佛祖的一棵灯芯。随佛祖修道悟
真,后来思凡下界占了花果山一处洞府,开山立派,传授门徒。
她看起来约二十多岁。

LONG);
	set("gender", "女性");
	set("age", 25);
	set("per", 40);
	create_family("盘丝洞",1,"丝");
	set_skill("literate",700);
	set_skill("unarmed", 700);
	set_skill("dodge", 700);
	set_skill("zhuyan", 700);
	set_skill("force",700);
	set_skill("parry",700);
	set_skill("sword", 700);
	set_skill("spells", 700);
	set_skill("whip", 700);
	set_skill("pansi-dafa", 700);
	set_skill("lanhua-shou",700);
	set_skill("jiuyin-xinjing",700);
	set_skill("chixin-jian",700);
	set_skill("qin",700);
	set_skill("yueying-wubu",700);
	set_skill("yinsuo-jinling", 700);
	map_skill("spells", "pansi-dafa");
	map_skill("unarmed", "lanhua-shou");
	map_skill("force", "jiuyin-xinjing");
	map_skill("sword", "chixin-jian");
	map_skill("parry", "yinsuo-jinling");
	map_skill("dodge", "yueying-wubu");
	map_skill("whip", "yinsuo-jinling");
	set("pansi/zhenfa",1);
	carry_object("/d/pansi/obj/qin");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","chixin-jian");
	}
	else
	{
		carry_object(0,"whip",1)->wield();
		map_skill("parry","yinsuo-jinling");
	}
}
int is_job(){return 1;}