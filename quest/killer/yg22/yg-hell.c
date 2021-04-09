inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("阎罗地府",4,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
	set_skill("whip", j);
        set_skill("hellfire-whip", j);
        map_skill("whip", "hellfire-whip");
        map_skill("parry", "hellfire-whip");
	set_skill("kusang-bang",j);
	set_skill("zhuihun-sword",j);
        set_skill("ghost-steps", j);
        set_skill("jinghun-zhang", j);
        set_skill("tonsillit", j);
        set_skill("gouhunshu", j);
        map_skill("force", "tonsillit");
        map_skill("spells", "gouhunshu");
        map_skill("dodge", "ghost-steps");
        map_skill("unarmed", "jinghun-zhang");
        set("env/test","HIB");
        setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"whip",1)->wield();	
	powerup(1,1);
	set("env/wimpy",0);
	set("class","ghost");
}