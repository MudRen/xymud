inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("方寸山三星洞",4,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
	set_skill("stick", j);
        set_skill("qianjun-bang", j);
        map_skill("stick","qianjun-bang");
        map_skill("parry", "qianjun-bang");
        set_skill("jindouyun", j);
        set_skill("wuxiangforce", j);
        set_skill("puti-zhi", j);
        set_skill("dao", j);
        map_skill("force", "wuxiangforce");
        map_skill("spells", "dao");
        map_skill("dodge", "jindouyun");
        map_skill("unarmed", "puti-zhi");
        set("env/test","HIB");
        setup();
        carry_object(0,"stick",1)->wield();	
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	powerup(1,1);
	set("env/wimpy",0);
	set("class","taoist");
}