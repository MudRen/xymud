// sgzl
inherit NPC;

string *names = ({ "黄莺侍儿","黄鹂侍儿","黄鹤侍儿",});

void create()
{
	int i = 40+random(11);
        set_name(names[random(sizeof(names))], ({"shi er", "shier"}));
        set_level(i);
	set("gender", "女性" );
	set("age", 16);
	set("long", "雪山门下公主侍卫。\n");
	set("class", "yaomo");
	set("attitude", "peaceful");
	create_family("大雪山", 4, "弟子");
	set_skill("unarmed",i*10);
	set_skill("cuixin-zhang",i*10);
	set_skill("dodge",i*10);
	set_skill("parry", 20);
	set_skill("blade",i*10);
	set_skill("bingpo-blade",i*10);
	set_skill("xiaoyaoyou",i*10);
	set_skill("force",i*10);   
	set_skill("ningxie-force",i*10);
	
	map_skill("force", "ningxie-force");
	map_skill("blade", "bingpo-blade");
	map_skill("parry", "cuixin-zhang");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("dodge", "xiaoyaoyou");
	set("force_factor", 100);
	set("nkgain", 20);
	setup();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"shoes",random(3))->wear();
	carry_object(0,"neck",random(3))->wear();
	carry_object(0,"ring",random(3))->wear();
	carry_object(0,"blade",random(3))->wield();
	setup();
}
