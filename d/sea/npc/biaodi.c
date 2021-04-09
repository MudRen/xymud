inherit SUPER_NPC;

void create()
{
       	set_name("龙表弟", ({"long biaodi", "long", "biaodi"}));
       	set_level(40);
	set("long","龙少爷的表弟和死党．\n");
       	set("gender", "男性");
       	set("age", 26);
       	set("attitude", "peaceful");
       	set("shen_type", 1);
       	
	set_skill("literate", 400);
       	set_skill("unarmed", 400);
       	set_skill("dodge", 400);
       	set_skill("force", 400);
       	set_skill("parry", 400);
       	set_skill("fork", 400);
       	set_skill("spells", 400);
        set_skill("seashentong", 400);
        set_skill("dragonfight", 400);
        set_skill("dragonforce", 400);
        set_skill("fengbo-cha", 400);
        set_skill("dragonstep", 400);
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");
	set_temp("weapon_level",20+random(15));
	set_temp("armor_level",20+random(15));
	setup();
        carry_object(0,"cloth",1)->wear();        
        carry_object(0,"neck",1)->wear();        
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"ring",1)->wear();
        add_money("gold", 3);
        powerup(0,1);
}