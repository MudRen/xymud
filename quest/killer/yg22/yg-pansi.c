// bula and mon@xyj
inherit __DIR__"yaoguai.c";

void set_skills(int j, int level)
{
	create_family("盘丝洞",4,"");
        set_skill("unarmed", j);
        set_skill("dodge", j);
        set_skill("parry", j);
        set_skill("force", j);
        set_skill("spells", j);
 	switch(random(2))
 	{
 		case 0 :
        		set_skill("sword", j);
        		set_skill("qingxia-jian", j);
        		map_skill("sword","qingxia-jian");
        		map_skill("parry","qingxia-jian");
        		carry_object(0,"sword",1)->wield();
       		break;
        	default :
        		set_skill("whip",j);
        		set_skill("yinsuo-jinling",j);
        		map_skill("whip","yinsuo-jinling");
        		map_skill("parry","yinsuo-jinling");
        		carry_object(0,"whip",1)->wield();
        		break;
        }				
        set_skill("yueying-wubu", j);
        set_skill("pansi-dafa", j);
        set_skill("lanhua-shou", j);
        set_skill("jiuyin-xinjing", j);

        map_skill("force", "jiuyin-xinjing");
        map_skill("spells", "pansi-dafa");
        map_skill("dodge", "yueying-wubu");
        map_skill("unarmed", "lanhua-shou");
        set("env/test","HIB");
	setup();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
	set("env/wimpy",0);
	set("class","yaomo");
	powerup(1,1);
}
