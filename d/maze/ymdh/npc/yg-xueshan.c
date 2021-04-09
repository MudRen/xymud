inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("大雪山",3,"");
	set_level(j);
	set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 	switch(random(2))
 	{
 		case 1 :
 			set_skill("blade",j*10);
        		set_skill("bingpo-blade",j*10);
        		map_skill("blade", "bingpo-blade");
        		map_skill("parry", "bingpo-blade");
        		carry_object(0,"blade",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "ninxie" :),
        			(: perform_action,"blade", "daobo" :),
        			(: perform_action,"blade", "bingxue" :),
        		}));	
			break;
		default :
			set_skill("sword",j*10);
			set_skill("bainiao-jian",j*10);
			map_skill("sword", "bainiao-jian");
        		map_skill("parry", "bainiao-jian");
        		carry_object(0,"sword",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"sword", "chaofeng" :),
        			(: perform_action,"sword", "feijian" :),
        			(: perform_action,"sword", "fengwu" :),
        		}));	
			break;	
	}		
        set_skill("xiaoyaoyou",j*10);
        set_skill("dengxian-dafa",j*10);
        set_skill("ningxie-force",j*10);
        set_skill("cuixin-zhang",j*10);
        map_skill("force", "ningxie-force");
        map_skill("spells", "dengxian-dafa");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("unarmed", "cuixin-zhang");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"fork",1)->wield();
	set("class","yaomo");
}       