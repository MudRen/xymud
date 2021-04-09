inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("陷空山无底洞",3,"");	
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
	set_skill("blade",j*10);
        set_skill("kugu-blade",j*10);
        map_skill("parry", "kugu-blade");
        map_skill("blade", "kugu-blade");
        set("chat_msg_combat", ({
        	(: perform_action,"blade", "pozhan" :),
        	(: perform_action,"blade", "diyu" :),
	}));
        set_skill("lingfu-steps",j*10);
        set_skill("yaofa",j*10);
        set_skill("huntian-qigong",j*10);
        set_skill("yinfeng-zhua",j*10);
        map_skill("force", "huntian-qigong");
        map_skill("spells", "yaofa");
        map_skill("dodge", "lingfu-steps");
        map_skill("unarmed", "yinfeng-zhua");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"blade",1)->wield();
	set("class","yaomo");
}
