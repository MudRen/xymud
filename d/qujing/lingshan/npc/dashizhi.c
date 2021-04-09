inherit SUPER_NPC;

void create()
{
  	set_name("大势至菩萨", ({"dashizhi pusa", "dashizhi", "dashi", "pusa"}));
  	set_level(169);
  	set ("long", @LONG
南无阿弥陀佛次徒，观世音菩萨的师弟，三
人并称西方三神。
LONG);
	create_family("南海普陀山", 1, "菩萨");
  	set("title", "西方三神之");
  	set("gender", "男性");
	set("age", 400);
       	set_skill("literate",1690);
	set_skill("spells", 1690);
	set_skill("buddhism", 1690);
	set_skill("unarmed",1690);
	set_skill("jienan-zhi",1690);
	set_skill("dodge",1690);
	set_skill("lotusmove",1690);
	set_skill("parry",1690);
	set_skill("force", 1690);
	set_skill("lotusforce", 1690);
	set_skill("hammer", 1690);
	set_skill("bighammer", 1690);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "bighammer");
	map_skill("hammer", "bighammer");
	set("force_factor",1690);
	set("mana_factor",1690);
	set_skill("tianlong-chanchang",1690);
	set_skill("longxiang-li",1690);

	setup();
	carry_object("/d/obj/cloth/jia_sha")->wear();
}

void die()
{
        if( environment() ) {
        	message("sound", "\n\n大势至菩萨摇头叹道：冤孽！真是冤孽！n\n", environment());
        	command("sigh");
        	message("sound", "\n大势至菩萨驾祥云，登彩雾，径往西方去了。。。\n\n", environment());	
	}
	destruct(this_object());
}
