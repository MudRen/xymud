#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("陷空山无底洞",4,"");	
        set("nickname",HIR"破绽百出"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
 	switch(random(3))
 	{
 		case 1 : 
        		set_skill("blade", j);
        		set_skill("kugu-blade", j);
        		map_skill("parry", "kugu-blade");
        		map_skill("blade", "kugu-blade");
        		carry_object(0,"blade",random(10))->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "pozhan" :),
        			(: perform_action,"blade", "diyu" :),
        			(: perform_action,"blade", "shendao" :),
        			(: perform_action,"blade", "xiao" :),
        		}));
        		break;
        	default :
        		set_skill("sword",j);
        		set_skill("qixiu-jian",j);
        		map_skill("parry", "qixiu-jian");
        		map_skill("sword", "qixiu-jian");
        		carry_object(0,"sword",random(10))->wield();
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "yaowu" :),
        			(: perform_action,"sword", "zxzx" :),
        			(: perform_action,"sword", "duoming" :),
        		}));
	       		break;
        }
        add("chat_msg_combat",({
		(: cast_spell, "huanying" :),
		(: cast_spell, "bite" :),
		(: cast_spell, "suliao" :),
	       	(: exert_function, "anti" :),
	}));		
        set_skill("lingfu-steps", j);
        set_skill("yaofa", j);
        set_skill("huntian-qigong", j);
        set_skill("yinfeng-zhua", j);
        map_skill("force", "huntian-qigong");
        map_skill("spells", "yaofa");
        map_skill("dodge", "lingfu-steps");
        map_skill("unarmed", "yinfeng-zhua");
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	delete("env/wimpy");
	set("class","yaomo");
}
