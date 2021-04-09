#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("月宫",4,"");			
	set("nickname",HIG"千娇百媚"NOR);
	set("gender","女性");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
        set_skill("sword",j);
        set_skill("snowsword",j);
        set_skill("moondance", j);
        set_skill("moonshentong", j);
        set_skill("baihua-zhang", j);
        set_skill("moonforce", j);

        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("spells", "moonshentong");
        map_skill("dodge", "moondance");
        map_skill("unarmed", "baihua-zhang");
	
	carry_object(0,"sword",random(10))->wield();
	set("chat_msg_combat", ({
        	(: perform_action,"sword", "dance" :),
        	(: perform_action,"sword", "lei" :),
        	(: perform_action,"sword", "qin" :),
        	(: perform_action,"sword", "tian" :),
        	(: cast_spell, "mihun" :),
        	(: cast_spell, "huimeng" :),
        	(: cast_spell, "arrow" :),
	}));
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("force_factor",0);
	delete("env/wimpy");
	set("class","xian");
}