// qinbing.c
// created 6-4-97 pickle
inherit NPC;

void create()
{
	int i = 19+random(20);
	mapping name = NAME_D->random_name2(0, 1,"程",0,"二");
  	set_name(name["name"],name["id"]);
  	set_level(i);
  	set("gender", "男性");
  	set("age", 19+random(30));
  	create_family("将军府", 3, "蓝");
  	set("title", "将军府亲兵");
  	set ("long", @LONG
这些亲兵都是在沙场上立过无数汗马功劳的强将。
他们不原受封为官，宁肯跟随保护旧主。
LONG);
  	set("per",20+random(20));
  	set_skill("blade", i*10);
  	set_skill("force", i*10);
  	set_skill("dodge", i*10);
  	set_skill("parry", i*10);
  	set_skill("wuhu-blade", i*10);
  	set_skill("lengquan-force", i*10);
  	set_skill("unarmed", i*10);
  	map_skill("force", "lengquan-force");
  	map_skill("parry", "wuhu-blade");
  	map_skill("blade", "wuhu-blade");
  	set("force_factor", 15);
  	set("chat_chance_combat", 30);
  	set("chat_msg_combat", ({
        	(: perform_action, "blade", "duan" :),
  	}) );
  	setup();
  	carry_object(0,"blade",random(3))->wield();
  	carry_object(0,"armor",random(3))->wear();
  	carry_object(0,"pifeng",random(3))->wear();
}
	


