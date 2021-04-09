inherit __DIR__"yaoguai.c";

void set_skills(int j)
{
	create_family("火云洞",4,"");
	set_level(j);
        set_skill("unarmed",j*10);
        set_skill("dodge",j*10);
        set_skill("parry",j*10);
        set_skill("force",j*10);
        set_skill("spells",j*10);
        set_skill("moyun-shou",j);
        set_skill("moshenbu",j);
        set_skill("huomoforce",j*10);
        set_skill("pingtian-dafa",j*10);
        set_skill("dali-bang",j*10);
        switch(random(3))
        {
        	case 0 :
        		set_skill("stick",j*10);
			map_skill("stick","dali-bang");
			map_skill("parry", "dali-bang");
			carry_object(0,"stick",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"stick", "shenli" :),
        			(: perform_action,"stick", "back" :),
        			(: exert_function, "budong" :),
        		}));	
			break;	
		default :
        		set_skill("spear",j*10);
        		set_skill("wuyue-spear",j*10);
			map_skill("spear","wuyue-spear");
			map_skill("parry","wuyue-spear");
			carry_object(0,"spear",1)->wield();	
        		set("chat_msg_combat", ({
        			(: perform_action,"spear", "buhui" :),
        			(: perform_action,"spear", "chongxiu" :),
        			(: exert_function, "budong" :),
        		}));	
			break;	
	}		
        map_skill("force", "huomoforce");
        map_skill("spells", "pingtian-dafa");
        map_skill("dodge", "moshenbu");
        map_skill("unarmed", "moyun-shou");
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("class","yaomo");
}
