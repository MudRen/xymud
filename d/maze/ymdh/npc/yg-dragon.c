inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("东海龙宫",3,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
        set_skill("fork",j*10);
        set_skill("fengbo-cha",j*10);
        set_skill("dragonstep",j*10);
        set_skill("dragonfight",j*10);
        set_skill("dragonforce",j*10);
        set_skill("seashentong",j*10);

        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("spells", "seashentong");
        map_skill("dodge", "dragonstep");
        map_skill("unarmed", "dragonfight");
	set("chat_msg_combat", ({
        	(: perform_action,"unarmed", "sheshen" :),
        	(: perform_action,"unarmed", "shenglong" :),
        	(: perform_action,"unarmed", "leidong" :),
        	(: exert_function, "shield" :),
	}));
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"unarmed",1)->wield();
	set("class","dragon");
}        