#include <ansi.h>
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("东海龙宫",4,"");
        if(query("guai_type")==1)	
        	set("nickname",HIR"漾漾泛菱荇  澄澄映葭苇"NOR);
        else	set("nickname",HIM"言入黄花川  每逐青溪水"NOR);
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
        set_skill("fork", j);
        set_skill("fengbo-cha", j);
        set_skill("dragonstep", j);
        set_skill("dragonfight", j);
        set_skill("dragonforce", j);
        set_skill("seashentong", j);

        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "dragonfight");
        map_skill("spells", "seashentong");
        map_skill("dodge", "dragonstep");
        map_skill("unarmed", "dragonfight");
	
        setup();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"unarmed",random(10))->wield();
	delete("env/wimpy");
	set("class","dragon");
}  