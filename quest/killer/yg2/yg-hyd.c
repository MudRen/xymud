#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("火云洞",4,"");
	set("nickname",HIR"来往不逢人 长歌楚天碧"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("moyun-shou",j);
        set_skill("moshenbu",j);
        set_skill("huomoforce", j);
        set_skill("pingtian-dafa", j);
        set_skill("wuyue-spear", j);
        set_skill("spear", j);
        map_skill("spear","wuyue-spear");		
        map_skill("force", "huomoforce");
        map_skill("parry", "wuyue-spear");
        map_skill("spells", "pingtian-dafa");
        map_skill("dodge", "moshenbu");
        map_skill("unarmed", "moyun-shou");
	set("env/test","HIB");	
        setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"spear",1)->wield();
	set("env/wimpy",0);
	set("class","yaomo");
	powerup(1,1);
}
