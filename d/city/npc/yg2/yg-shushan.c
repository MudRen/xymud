// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("蜀山",4,"");
	set("title","万剑齐驭");
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
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	powerup(0,1);
	set("env/wimpy",10);
	set("class","xian");
}
