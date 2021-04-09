inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("东海龙宫",3,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("fork", j);
        set_skill("fengbo-cha", j);
        set_skill("dragonstep", j);
        set_skill("dragonfight", j);
        set_skill("dragonforce", j);
        set_skill("seashentong", j);

        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("spells", "seashentong");
        map_skill("dodge", "dragonstep");
        map_skill("unarmed", "dragonfight");
	set("chat_msg_combat", ({
        	(: perform_action,"unarmed", "sheshen" :),
        	(: perform_action,"unarmed", "shenglong" :),
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