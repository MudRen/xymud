#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("百花谷",4,"");
	set("title",HIR"绝情毒花"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
 	set_skill("sword", j);
        set_skill("zongheng-sword", j);
        map_skill("sword","zongheng-sword");
        map_skill("parry","zongheng-sword");
        carry_object(0,"sword",random(10))->wield();
	set("chat_msg_combat", ({
        	(: perform_action,"sword", "yumei" :),
        	(: perform_action,"sword", "qijian" :),
        	(: perform_action,"sword", "zongheng" :),
        	(: exert_function, "feng" :),
        	(: cast_spell, "flower" :),
	}));
		
        set_skill("wuyou-steps", j);
        set_skill("baihua-xianfa", j);
        set_skill("rainbow-zhi", j);
        set_skill("brightjade-force", j);

        map_skill("force", "brightjade-force");
        map_skill("spells", "baihua-xianfa");
        map_skill("dodge", "wuyou-steps");
        map_skill("unarmed", "rainbow-zhi");
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	powerup(0,1);
	delete("env/wimpy");
	set("class","xian");
}