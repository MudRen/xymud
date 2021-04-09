// sgzl, 99.0.15.

inherit NPC;

void create()
{
	int i = 79+random(20);
   	set_name("黄雀侍儿", ({"huangque shier", "shier", "huangque"}));
   	set_level(i);
   	set("gender", "女性" );
   	set("age", 22);

   	set("long", "孔雀公主的贴身侍卫头领。\n");
   	set("class", "yaomo");
	set("attitude", "heroism");
   	create_family("大雪山", 3, "弟子");
   
   	set_skill("unarmed",i*10);
   	set_skill("cuixin-zhang",i*10);
   	set_skill("dodge",i*10);
   	set_skill("xiaoyaoyou",i*10);
   	set_skill("parry",i*10);
   	set_skill("sword",i*10);
   	set_skill("bainiao-jian",i*10);
   	set_skill("throwing",i*10);
   	set_skill("force", i*10);
   	set_skill("ningxie-force",i*10);
   	set_skill("literate",i*10);
   	set_skill("spells", i*10);
   	set_skill("dengxian-dafa",i*10);

   	map_skill("spells", "dengxian-dafa");
   	map_skill("force", "ningxie-force");
   	map_skill("unarmed", "yingzhaogong");
   	map_skill("sword", "bainiao-jian");
   	map_skill("parry", "bainiao-jian");
   	map_skill("throwing", "bainiao-jian");
	map_skill("dodge", "xiaoyaoyou");
   	set("force_factor", 150);
   	set("mana_factor", 100);

   	setup();

	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"shoes",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"pifeng",random(2))->wear();
	carry_object(0,"sword",random(3))->wield();
}