inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("南海普陀山",4,"");		
	set("title","普陀恶僧");
	set_skill("unarmed", j);
	set_skill("dodge", j);
	set_skill("parry", j);
	set_skill("force", j);
	set_skill("spells", j);
	set("chat_chance_combat", 1+2*level);
	switch(random(3))
	{
		case 1 :  
			set_skill("staff", j);
			set_skill("lunhui-zhang", j);
			map_skill("staff", "lunhui-zhang");
        		map_skill("parry", "lunhui-zhang");
        		carry_object(0,"staff",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: exert_function, "huti" :),
        			(: exert_function, "life" :),
        			(: cast_spell, "lianhua" :),
        		}));	
			break;
		default :
			set_skill("blade", j);
			set_skill("cibeidao", j);
			map_skill("blade", "cibeidao");
        		map_skill("parry", "cibeidao");
        		carry_object(0,"blade",random(10))->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"blade", "cibei" :),
        			(: perform_action,"blade", "sheshen" :),
        		}));	
			break;
	}				
	set_skill("lotusmove", j);
	set_skill("buddhism", j);
	set_skill("jienan-zhi", j);
	set_skill("lotusforce", j);
	map_skill("force", "lotusforce");
	map_skill("spells", "buddhism");
	map_skill("dodge", "lotusmove");
	map_skill("unarmed", "jienan-zhi");
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",0);
	set("class","bonze");
}
