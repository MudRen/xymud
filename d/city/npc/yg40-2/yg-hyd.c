#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("火云洞",4,"");
	set("nickname",REV HIB"横冲直撞"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("moyun-shou",j);
        set_skill("moshenbu",j);
        set_skill("huomoforce", j);
        set_skill("pingtian-dafa", j);
        set_skill("dali-bang", j);
        switch(random(2))
        {
        	case 0 :
        		set_skill("stick", j);
			map_skill("stick","dali-bang");
			map_skill("parry", "dali-bang");
			carry_object(0,"stick",1)->wield();	
			break;	
		default :
			set_skill("spear", j+random(2));
			map_skill("spear","huoyun-qiang");
			map_skill("parry","huoyun-qiang");
			carry_object(0,"spear",1)->wield();		
			break;	
	}		
        map_skill("force", "huomoforce");
        map_skill("spells", "pingtian-dafa");
        map_skill("dodge", "moshenbu");
        map_skill("unarmed", "moyun-shou");
        setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("env/wimpy",0);
	set("class","yaomo");
}
