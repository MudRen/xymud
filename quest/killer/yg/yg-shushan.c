#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("蜀山",4,"");
	if(query("guai_type")==1)	
        	set("nickname",HIR"草木有本心 何求美人折"NOR);
        else	set("nickname",HIG"谁知林栖者 闻风坐相悦"NOR);	
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
 	set("chat_chance_combat", 1+2*level);
        set("chat_msg_combat", ({
		(: perform_action,"sword", "fly" :),
       		(: perform_action,"sword", "qijue" :),
       		(: perform_action,"sword", "wanjian" :),
       		(: perform_action,"sword", "zhan" :),
       		(: exert_function, "chaoyuan" :),
       		(: exert_function, "guixin" :),
       		(: exert_function, "huti" :),
       		(: exert_function, "zhanqi" :),
       		(: cast_spell, "zhan" :),
       		(: cast_spell, "ding" :),
       		(: cast_spell, "feng" :),
	}));
	setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"sword",random(10))->wield();
	carry_object("/obj/paper_seal")->set_amount(500);
	powerup(0,1);
	delete("env/wimpy");
	set("class","taoist");
}