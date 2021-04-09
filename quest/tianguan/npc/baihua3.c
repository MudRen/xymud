#include <combat.h>
#include <ansi.h>
inherit __DIR__"n2.c"; 

void setname() 
{
set_name("凝眸仙子", ({"ningmou xianzi", "ningmou", "xianzi"}));
set("long",@LONG
百花谷主一直是个迷一样的人物，甚至仍然有人说她是仙子。大
约五十年前，一个采药的小童在林间迷路，在饥渴绝望的时刻，花丛
中翩翩飘下一美丽女子，为他指明了出去的道路。时间飞逝，当年的
小童也变成了白发老翁，但在他心中一直把当年救她的女子当成上天
派下来拯救他的仙子，因为她在花间飞舞那轻盈的身姿，根本就不象
凡人......
LONG);
set("gender", "女性");
set("age", 25);
set("rank_info/respect", "神仙");
set("per", 35);

create_family("百花谷",2,"百花谷主");

set_skill("unarmed", 700);
set_skill("dodge", 700);
set_skill("parry", 700);
set_skill("force", 700);
set_skill("spells", 700);

set_skill("whip", 700);
set_skill("jueqingbian", 700);
set_skill("sword",700);
set_skill("zongheng-sword",700);
set_skill("wuyou-steps", 700);
set_skill("baihua-xianfa", 700);
set_skill("rainbow-zhi", 700);
set_skill("siji-zhang", 700);
set_skill("brightjade-force", 700);

map_skill("force", "brightjade-force");
map_skill("sword", "zongheng-sword");
map_skill("whip","jueqingbian");
map_skill("parry", "zongheng-sword");
map_skill("spells", "baihua-xianfa");
map_skill("dodge", "wuyou-steps");
map_skill("unarmed", "rainbow-zhi");
set("skillmark/zongheng-sword",({"heng","zong"})[random(2)]); 
set("skillmark/brightjade-force","yes");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",120000000);
	set("daoxing",120000000);
	carry_object(0,"sword",1)->wield();
}