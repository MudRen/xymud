// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("蜀山派",3,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 	set_skill("sword",j*10);
        set_skill("mindsword",j*10);
        map_skill("sword","mindsword");
        map_skill("parry","mindsword");
        set("chat_msg_combat", ({
        	(: perform_action,"sword", "jianqi" :),
        	(: perform_action,"sword", "tanzhi" :),
        	(: perform_action,"sword", "taohua" :),
        }));
        set_skill("sevensteps",j*10);
        set_skill("taoism",j*10);
        set_skill("hunyuan-zhang",j*10);
        set_skill("zixia-shengong",j*10);

        map_skill("force", "zixia-shengong");
        map_skill("spells", "taoism");
        map_skill("dodge", "sevensteps");
        map_skill("unarmed", "hunyuan-zhang");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"sword",1)->wield();
	set("class","xian");
}
