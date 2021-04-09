inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("火云洞",4,"");
	set("title","离火三重");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("moyun-shou",j+random(2));
        set_skill("moshenbu",j+random(2));
        set_skill("huomoforce", j+random(2));
        set_skill("pingtian-dafa", j+random(2));
        set_skill("dali-bang", j+random(2));
        set_skill("huoyun-qiang",j+random(2));
        switch(random(2))
        {
        	case 0 :
        		set_skill("stick", j+random(2));
			map_skill("stick","dali-bang");
			map_skill("parry", "dali-bang");
			carry_object(0,"stick",random(10))->wield();	
			break;	
		default :
			set_skill("spear", j+random(2));
			map_skill("spear","huoyun-qiang");
			map_skill("parry","huoyun-qiang");
			carry_object(0,"spear",random(10))->wield();	
			break;	
	}		
        map_skill("force", "huomoforce");
        map_skill("spells", "pingtian-dafa");
        map_skill("dodge", "moshenbu");
        map_skill("unarmed", "moyun-shou");
        setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	set("env/wimpy",10);
	set("class","yaomo");
}
