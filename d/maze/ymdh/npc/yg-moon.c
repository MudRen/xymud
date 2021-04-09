inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("月宫",3,"");	
	set_level(j);		
	set("gender","女性");
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
        set_skill("sword",j*10);
        set_skill("snowsword",j);
        set_skill("moondance",j*10);
        set_skill("moonshentong",j*10);
        set_skill("baihua-zhang",j*10);
        set_skill("moonforce",j*10);

        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("spells", "moonshentong");
        map_skill("dodge", "moondance");
        map_skill("unarmed", "baihua-zhang");
	
	carry_object(0,"sword",1)->wield();
	set("chat_msg_combat", ({
        	(: perform_action,"sword", "tian" :),
        	(: perform_action,"sword", "qin" :),
        	(: perform_action,"sword", "dance" :),
        	(: exert_function, "heal" :),
	}));
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("force_factor",0);
	set("class","xian");
}
