#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("大雪山",4,"");
        if(query("guai_type")==1)	
        	set("nickname",HIG"燕草如碧丝 秦桑低绿枝"NOR);
        else	set("nickname",HIW"当君怀归日 是妾断肠时"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	set("chat_chance_combat", 1+2*level);
 	switch(random(2))
 	{
 		case 1 :
 			set_skill("blade", j);
        		set_skill("bingpo-blade", j);
        		map_skill("blade", "bingpo-blade");
        		map_skill("parry", "bingpo-blade");
        		carry_object(0,"blade",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "bingxue" :),
        			(: perform_action,"blade", "daobo" :),
        			(: perform_action,"blade", "ningxie" :),
        			(: perform_action,"blade", "qianshe" :),
        			(: exert_function, "ninxie" :),
        		}));	
			break;
		default :
			set_skill("sword",j);
			set_skill("sword",j);
			map_skill("sword", "bainiao-jian");
        		map_skill("parry", "bainiao-jian");
        		carry_object(0,"sword",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "chaofeng" :),
        			(: perform_action,"sword", "feijian" :),
        			(: perform_action,"sword", "fengwu" :),
        			(: perform_action,"sword", "qijue" :),
        			(: exert_function, "ninxie" :),
        		}));	
			break;	
	}
	add("chat_msg_combat",({
		(: cast_spell, "hufa" :),
		(: cast_spell, "juanbi" :),
		(: cast_spell, "tuntian" :),
	       	(: exert_function, "ningxie" :),
	}));		
        set_skill("xiaoyaoyou", j);
        set_skill("dengxian-dafa", j);
        set_skill("ningxie-force", j);
        set_skill("cuixin-zhang", j);
        map_skill("force", "ningxie-force");
        map_skill("spells", "dengxian-dafa");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("unarmed", "cuixin-zhang");
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"fork",random(10))->wield();
	powerup(0,1);
	delete("env/wimpy");
	set("class","yaomo");
}       

