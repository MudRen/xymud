#include <ansi.h>
inherit __DIR__"guai.c";

void set_skills()
{
	int j = 390;
	create_family("百花谷",4,"");
	set_level(39);
	set("env/test","HIM");
	set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set_skill("sword", j);
        set_skill("zongheng-sword", j);
        map_skill("sword","zongheng-sword");
        map_skill("parry","zongheng-sword");
        	
        set_skill("wuyou-steps", j);
        set_skill("baihua-xianfa", j);
        set_skill("rainbow-zhi", j);
        set_skill("brightjade-force", j);

        map_skill("force", "brightjade-force");
        map_skill("spells", "baihua-xianfa");
        map_skill("dodge", "wuyou-steps");
        map_skill("unarmed", "rainbow-zhi");
	setup();
	carry_object(0,"sword",1)->wield();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	powerup(0,1);
	delete("env/wimpy");
	set("class","xian");
}