// xiaojie.c
inherit NPC;

string *ns = ({"秦","罗","尉迟","程",});

void create()
{
	int i = 10+random(20);
	mapping name = NAME_D->random_name2(0, 1, ns[random(sizeof(ns))],"国",0);
	set_name(name["name"],name["id"]);
	set("title","将军府校尉");
       	set_level(i);
       	set("long","将军府的家将，看起来神气凛然．\n");
       	set("gender", "男性");
       	set("age", 28);
       	set("per",15+random(15));
       	set("attitude", "peaceful");
        set("force_factor", 15);
	
        set("shen_type", 1);
        set_skill("spear", i*10);
        set_skill("parry", i*10);
	set_skill("move", i*10);
	set_skill("yanxing-steps",i*10);
	set_skill("bawang-qiang",i*10);
	map_skill("dodge", "yanxing-steps");
	map_skill("spear", "bawang-qiang");
	map_skill("parry", "bawang-qiang");
        set_skill("dodge", i*10);

        setup();
	carry_object(0,"spear",random(2))->wield();
  	carry_object(0,"armor",random(2))->wear();
  	carry_object(0,"pifeng",random(2))->wear();
}
