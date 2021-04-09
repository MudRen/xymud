inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("百花谷",3,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
 	set_skill("sword",j*10);
        set_skill("zongheng-sword",j*10);
        map_skill("sword","zongheng-sword");
        map_skill("parry","zongheng-sword");
        if( random(2) )
        {
		set("chat_msg_combat", ({
        		(: perform_action,"sword", "yumei" :),
        		(: perform_action,"sword", "zongheng" :),
        		(: perform_action,"sword", "zong" :),
        		(: perform_action,"sword", "qijian" :),
        		(: exert_function, "feng" :),
		}));
	}
	else
	{
		set("chat_msg_combat", ({
        		(: perform_action,"sword", "yumei" :),
        		(: perform_action,"sword", "zongheng" :),
        		(: perform_action,"sword", "heng" :),
        		(: perform_action,"sword", "qijian" :),
        		(: exert_function, "feng" :),
		}));
	}	
        set_skill("wuyou-steps",j*10);
        set_skill("baihua-xianfa",j*10);
        set_skill("rainbow-zhi",j*10);
        set_skill("brightjade-force",j*10);

        map_skill("force", "brightjade-force");
        map_skill("spells", "baihua-xianfa");
        map_skill("dodge", "wuyou-steps");
        map_skill("unarmed", "rainbow-zhi");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
        carry_object(0,"sword",1)->wield();
	set("class","xian");
}
