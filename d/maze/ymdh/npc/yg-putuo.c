inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("南海普陀山",3,"");
	set_level(j);
	set_skill("unarmed",j*10);
	set_skill("dodge",j*10);
	set_skill("parry",j*10);
	set_skill("force",j*10);
	set_skill("spells",j*10);
	set_skill("staff",j*10);
	set_skill("lunhui-zhang",j*10);
	map_skill("staff", "lunhui-zhang");
        map_skill("parry", "lunhui-zhang");
	set("chat_msg_combat", ({
        	(: exert_function, "huti" :),
        	(: exert_function, "life" :),
        	(: cast_spell, "lianhua" :),
        	(: perform_action,"staff", "chaodu" :),
        	(: perform_action,"staff", "pudu" :),
        	(: perform_action,"staff", "fire" :),
	}));	
	set_skill("lotusmove",j*10);
	set_skill("buddhism",j*10);
	set_skill("jienan-zhi",j*10);
	set_skill("lotusforce",j*10);
	map_skill("force", "lotusforce");
	map_skill("spells", "buddhism");
	map_skill("dodge", "lotusmove");
	map_skill("unarmed", "jienan-zhi");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"staff",1)->wield();	
	set("class","bonze");
}
