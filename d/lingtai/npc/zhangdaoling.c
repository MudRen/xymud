//puti.c
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
	set_name("张道陵", ({"zhang daoling", "zhang", "daoling"}));
	set_level(135);
	set("long", "张道陵乃是天上的天师，此刻偷闲在山边观观景色。\n");
	set("title", "天师");
	set("gender", "男性");
	set("class", "taoist");
	set("age", 60);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("rank_info/respect", "老神仙");
	set("force_factor", 40);
	set("mana_factor", 50);

 	set("eff_dx", 250000);
 	set("nkgain", 400);

	set_skill("literate", 1300);
	set_skill("unarmed", 1050);
	set_skill("dodge", 1350);
	set_skill("parry", 1350);
	set_skill("sword", 1350);
	set_skill("spells", 1350);
	set_skill("dao", 1200);
	set_skill("changquan", 1200);
	set_skill("wuxiangforce", 1200);
	set_skill("force", 1200);
	set_skill("sanqing-jian", 1350);
	set_skill("chaos-steps", 1350);
	map_skill("spells", "dao");
	map_skill("unarmed", "changquan");
	map_skill("force", "wuxiangforce");
	map_skill("sword", "sanqing-jian");
	map_skill("parry", "sanqing-jian");
	map_skill("dodge", "chaos-steps");
	set_temp("armor_level",30+random(30));
	set_temp("weapon_level",30+random(30));
	setup();
        carry_object(0,"cloth",random(2))->wear();
        carry_object(0,"pifeng",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
        carry_object(0,"sword",random(3))->wield();
}

void die()
{
        if( environment() ) 
        {
        	message("sound", "\n\n张道陵脸色突变，道：天上点卯，恕不奉陪！\n\n", environment());
		command("drop all");
		message("sound", "\n张道陵化成一股紫烟冲上天去。。。\n\n", environment());
        }
        destruct(this_object());
}

int accept_fight(object me)
{	
        command("say 良景如斯，无心斗而。\n");
        return 0;
}

