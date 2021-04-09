#include <ansi.h>
inherit __DIR__"guai.c";

void set_skills()
{
	int j = 390;
	create_family("蜀山",4,"");
	set_level(39);
	set("env/test","HIM");
	
  	set_skill("spells",j);
        set_skill("force", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("sword", j);
        set_skill("xianfeng-yunti", j);
        set_skill("zuixian-wangyue", j);
        set_skill("chuanyun-zhang", j);
        set_skill("literate", j);
        set_skill("unarmed", j);
	set_skill("yujianshu", j);
        set_skill("tianshi-fufa",j);
        map_skill("spells", "tianshi-fufa");
        map_skill("dodge", "zuixian-wangyue");
        map_skill("force", "xianfeng-yunti");
        map_skill("parry", "yujianshu");
        map_skill("sword", "yujianshu");
        map_skill("unarmed", "chuanyun-zhang");
 	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"sword",1)->wield();
	carry_object("/obj/paper_seal")->set_amount(500);
	powerup(0,1);
	delete("env/wimpy");
	set("class","taoist");
}