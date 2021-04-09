#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname()
{
set_name("菩提祖师", ({"master puti","puti", "master"}));
set("long", "大觉金仙没垢姿，西方妙相祖菩提\n");
set("gender", "男性");
set("age", 100);
set("class", "taoist");
set("rank_info/respect", "老师祖");
set("per", 26);
set("looking", "玉面多光润，苍髯颌下飘，金睛飞火焰，长目过眉梢。");

set_skill("literate",700);
set_skill("unarmed",700);
set_skill("dodge",700);
set_skill("force",700);
set_skill("parry",700);
set_skill("stick",700);
set_skill("spells",700);
set_skill("whip",700);
set_skill("dao",700);
set_skill("puti-zhi",700);
set_skill("wuxiangforce",700);
set_skill("qianjun-bang",700);
set_skill("jindouyun",700);
map_skill("spells", "dao");
map_skill("unarmed", "puti-zhi");
map_skill("force", "wuxiangforce");
map_skill("stick", "qianjun-bang");
map_skill("parry", "qianjun-bang");
map_skill("dodge", "jindouyun");
create_family("方寸山三星洞", 1, "蓝");
set("fangcun/panlong_accept","done");
}

void setup()
{
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	carry_object(0,"stick",1)->wield();
}

int is_job(){return 1;}